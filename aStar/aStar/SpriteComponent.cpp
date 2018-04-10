#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(string filepath, SDL_Renderer * renderer, SDL_Rect Source, float W, float H)
{
	Texture = IMG_LoadTexture(renderer, filepath.c_str());

	SheetRect.x = Source.x;
	SheetRect.y = Source.y;
	SheetRect.w = Source.w;
	SheetRect.h = Source.h;

	ScreenRect.w = W;
	ScreenRect.h = H;

	setOrigin();

	Flip = SDL_FLIP_NONE;

	Rotation = 0;
}

SpriteComponent::SpriteComponent(SDL_Texture * Text, SDL_Rect Source, float W, float H)
{
	SDL_Texture * Temp = Text;

	Texture = Temp;

	SheetRect.x = Source.x;
	SheetRect.y = Source.y;
	SheetRect.w = Source.w;
	SheetRect.h = Source.h;

	ScreenRect.w = W;
	ScreenRect.h = H;

	setOrigin();
	Flip = SDL_FLIP_NONE;

	Rotation = 0;
}

void SpriteComponent::init()
{
	// Get Position Component
	Position = &m_owner->getComponent<PositionComponent>();

	ScreenRect.x = Position->GetPosition().x;
	ScreenRect.y = Position->GetPosition().y;

	// Get RenderComponent
	RenderCom = &m_owner->getComponent<RenderComponent>();
}

void SpriteComponent::Draw(SDL_Renderer * Renderer)
{
	this->setPosition(Position->GetXPosition(), Position->GetYPosition());

	if (m_owner->isActive())
	{
		RenderCom->Render(Renderer, this->getTexture(), &this->getSpriteDimensions(), &this->getScreenCoords(), this->getRotation(),
			&this->getOrigin());
	}
}

void SpriteComponent::update()
{
	ScreenRect.x = Position->GetXPosition();
	ScreenRect.y = Position->GetYPosition();
	Rotation = Position->GetRotation();
}

void SpriteComponent::setOrigin()
{
	Origin.x = ScreenRect.w / 2;
	Origin.y = ScreenRect.h / 2;
}

void SpriteComponent::setOrigin(float x, float y)
{
	Origin.x = x;
	Origin.y = y;
}

// Set position functions
void SpriteComponent::setPosition(float x, float y)
{
	ScreenRect.x = x;
	ScreenRect.y = y;
}

void SpriteComponent::setPosition(SDL_Rect rect)
{
	ScreenRect.x = rect.x;
	ScreenRect.y = rect.y;
}

// Set sheet position functions
void SpriteComponent::setSheetPosition(float x, float y)
{
	SheetRect.x = x;
	SheetRect.y = y;
}

void SpriteComponent::setSheetPosition(SDL_Rect rect)
{
	SheetRect.x = rect.x;
	SheetRect.y = rect.y;
}

// set size functions
void SpriteComponent::setSize(float x, float y)
{
	ScreenRect.w = x;
	ScreenRect.h = y;
}

void SpriteComponent::setSize(SDL_Rect rect)
{
	ScreenRect.w = rect.w;
	ScreenRect.h = rect.h;
}

void SpriteComponent::setRotation(float angle)
{
	Rotation = angle;
}

void SpriteComponent::addRotation(float value)
{
	Rotation += value;
}
