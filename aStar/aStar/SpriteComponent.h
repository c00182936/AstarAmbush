#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include <iostream>

/// <class> SpriteComponent </class>
/// <summary>
/// This class inherits from the Component class.
/// The purpose of this class is to draw an image
/// to the screen using data from other components.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class SpriteComponent : public Component
{
public:
	SpriteComponent() {};
	~SpriteComponent() {};
	SpriteComponent(string filepath, SDL_Renderer * renderer, SDL_Rect Source, float W = 64, float H = 64);
	SpriteComponent(SDL_Texture * Texture, SDL_Rect Source, float W = 64, float H = 64);

	void init() override;
	void Draw(SDL_Renderer * Renderer) override;
	void update() override;

	// Set Origin
	void setOrigin();
	void setOrigin(float x, float y);

	// Set Position
	void setPosition(float x, float y);
	void setPosition(SDL_Rect rect);

	// Set Sheet Position
	void setSheetPosition(float x, float y);
	void setSheetPosition(SDL_Rect rect);

	// Set Size
	void setSize(float x, float y);
	void setSize(SDL_Rect rect);

	// Set Rotation
	void setRotation(float angle);
	void addRotation(float value);

	// Get Sheet Coordinates
	SDL_Rect getSpriteDimensions() { return SheetRect; };

	// Get Screen Coordinates
	SDL_Rect getScreenCoords() { return ScreenRect; };

	// Get Origin
	SDL_Point getOrigin() { return Origin; };

	// Get Rotation
	float getRotation() { return Rotation; };

	// Get Flip Flag
	SDL_RendererFlip getFlipFlag() { return Flip; };

	// Get Texture
	SDL_Texture * getTexture() { return Texture; };

private:
	PositionComponent * Position;
	RenderComponent * RenderCom;

	SDL_Texture * Texture;
	SDL_Rect SheetRect;
	SDL_Rect ScreenRect;
	SDL_Point Origin;
	SDL_RendererFlip Flip;
	float Rotation;
};