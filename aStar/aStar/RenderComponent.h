#pragma once
#include <SDL.h>
#include "ECS.h"

/// <class> RenderComponent </class>
/// <summary>
/// This class inherits from the Component class.
/// The purpose of this class is take in information
/// from other objects and to use that information
/// to render to the screen.
/// </summary>
/// <author>Jack Keogh</author>

class RenderComponent : public Component
{
public:
	/// <summary>
	/// This method is used to render a texture.
	/// </summary>
	/// <param name="Renderer">SDL_Renderer ptr used to draw the texture.</param>
	/// <param name="Texture">SDL_Texture ptr of the image to render.</param>
	/// <param name="SrcRect">SDL_Rect ptr to the position and size on the sprite sheet. NULL will use entire sprite sheet.</param>
	/// <param name="DstRect">SDL_Rect ptr to the position and size on screen. NULL will use the entire screen.</param>
	/// <param name="Angle">float for the rotation of the object.</param>
	/// <param name="Origin">SDL_Point ptr for the origin of the object. NULL will place the origin to center of texture.</param>
	void Render(SDL_Renderer * Renderer, SDL_Texture * Texture, SDL_Rect * SrcRect = NULL, SDL_Rect * DstRect = NULL, float Angle = 0.0f,
		SDL_Point * Origin = NULL);
};