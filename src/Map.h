#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{
	public:
		Map(std::string textureId, int scale, int tileSize);
		~Map() {};
		void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
		void AddTile(int sourceRectX, int sourceRectY, int x, int y);

	private:
		std::string textureId;
		int scale;
		int tileSize;
};

#endif