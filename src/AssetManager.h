#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>

#include "./TextureManager.h"
#include "./FontManager.h"
#include "./EntityManager.h"

class AssetManager
{
	public:
		AssetManager(EntityManager* manager);
		~AssetManager();
		void ClearData();
		
		void AddTexture(std::string textureId, const char* filePath);
		SDL_Texture* GetTexture(std::string textureId);
		
		void AddFont(const std::string fontId, const char* filePath, const int fontSize);
		TTF_Font* GetFont(std::string fondId);

	private:
		EntityManager* manager = nullptr;
		std::map<std::string, SDL_Texture*> textures;
		std::map<std::string, TTF_Font*> fonts;
};

#endif