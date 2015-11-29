//
//  math.cpp
//
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "utility.h"

Vector2 Vector2::operator+(const Vector2& param) {
    Vector2 temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return temp;
}

Vector2& Vector2::operator=(const Vector2& param) {
    y = param.y;
    x = param.x;
    return *this;
}

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "TTF_OpenFont");
		return nullptr;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr) {
		TTF_CloseFont(font);
		SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "TTF_RenderText");
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "CreateTexture");
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}