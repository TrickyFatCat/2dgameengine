#include "./FontManager.h"

TTF_Font* FontManager::LoadFont(const char* fileName, const int fontSize)
{
	return TTF_OpenFont(fileName, fontSize);
}

void FontManager::Draw(SDL_Texture* texture, const SDL_Rect position)
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}