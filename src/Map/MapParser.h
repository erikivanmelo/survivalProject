#ifndef MAPPARSER_H
#define MAPPARSER_H

#include<tinyxml.h>

#include "GameMap.h"
#include "TileLayer.h"

#include <map>
#include <string>
class MapParser
{
public:
		static const std::string worldName;
		static const std::string worldAsset;
		static const std::string blocksAsset;

    bool load();

    ~MapParser();

    inline GameMap* getMap(std::string id){ return mapDict[id]; }
    inline static MapParser *getInstance(){ return instance = (instance == nullptr)? new MapParser() : instance; }

    void clean();

private:
    bool parse(std::string id, std::string source);
    Tileset parseTileSet( TiXmlElement* xmlTileset );
    TileLayer *parseTileLayer( TiXmlElement* xmlLayer, Tileset tileset, int tilesize, int rowcount, int colcount );

    MapParser(){}
    static MapParser *instance;
    std::map<std::string, GameMap*> mapDict;

};

#endif // MAPPARSER_H
