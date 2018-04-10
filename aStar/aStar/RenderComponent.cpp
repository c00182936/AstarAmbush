#include "RenderComponent.h"

void RenderComponent::Render(SDL_Renderer * Renderer, SDL_Texture * Texture, SDL_Rect * SrcRect, SDL_Rect * DstRect, float Angle,
	SDL_Point * Origin)
{
	SDL_RenderCopyEx(Renderer, Texture, SrcRect, DstRect, Angle, Origin, SDL_FLIP_NONE);
}
