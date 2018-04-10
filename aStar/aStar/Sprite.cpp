#include "Sprite.h"

Sprite::Sprite(string filepath, SDL_Renderer * renderer, SDL_Rect Source, SDL_Rect Screen)
{
	Texture = IMG_LoadTexture(renderer, filepath.c_str());

	SheetRect.x = Source.x;
	SheetRect.y = Source.y;
	SheetRect.w = Source.w;
	SheetRect.h = Source.h;

	ScreenRect.x = Screen.x;
	ScreenRect.y = Screen.y;
	ScreenRect.w = Screen.w;
	ScreenRect.h = Screen.h;

	setOrigin();

	Flip = SDL_FLIP_NONE;

	Rotation = 0;
}

Sprite::Sprite(SDL_Texture * Text, SDL_Rect Source, SDL_Rect Screen)
{
	SDL_Texture * Temp = Text;

	Texture = Temp;

	SheetRect.x = Source.x;
	SheetRect.y = Source.y;
	SheetRect.w = Source.w;
	SheetRect.h = Source.h;

	ScreenRect.x = Screen.x;
	ScreenRect.y = Screen.y;
	ScreenRect.w = Screen.w;
	ScreenRect.h = Screen.h;

	setOrigin();
	Flip = SDL_FLIP_NONE;

	Rotation = 0;
}

void Sprite::Render(SDL_Renderer * Renderer)
{
	SDL_RenderCopy(Renderer, Texture, &SheetRect, &ScreenRect);
}

void Sprite::setOrigin()
{
	Origin.x = ScreenRect.w / 2;
	Origin.y = ScreenRect.h / 2;
}

void Sprite::setOrigin(float x, float y)
{
	Origin.x = x;
	Origin.y = y;
}

// Set position functions
void Sprite::setPosition(float x, float y)
{
	ScreenRect.x = x;
	ScreenRect.y = y;
}

void Sprite::setPosition(SDL_Rect rect)
{
	ScreenRect.x = rect.x;
	ScreenRect.y = rect.y;
}

// Set sheet position functions
void Sprite::setSheetPosition(float x, float y)
{
	SheetRect.x = x;
	SheetRect.y = y;
}

void Sprite::setSheetPosition(SDL_Rect rect)
{
	SheetRect.x = rect.x;
	SheetRect.y = rect.y;
}

// set size functions
void Sprite::setSize(float x, float y)
{
	ScreenRect.w = x;
	ScreenRect.h = y;
}

void Sprite::setSize(SDL_Rect rect)
{
	ScreenRect.w = rect.w;
	ScreenRect.h = rect.h;
}

void Sprite::setRotation(float angle)
{
	Rotation = angle;
}

void Sprite::addRotation(float value)
{
	Rotation += value;
}
