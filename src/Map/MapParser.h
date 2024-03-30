#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <cstdint>
#include<tinyxml.h>

#include "Chunk.h"
#include "GameMap.h"

#include <map>
#include <string>
class MapParser
{
public:
		static const std::string worldName;
		static const std::string worldAsset;
		static const std::string blocksAsset;

    void load();


    inline GameMap* getMap(std::string id){ return mapDict[id]; }
    inline static MapParser *get(){ return instance = (instance == nullptr)? new MapParser() : instance; }
    inline static void clean(){ delete instance; }

private:
    void parse(const std::string &id,const std::string &source);
    Tileset *parseTileSet( TiXmlElement* xmlTileset );
    void parseChunks( TiXmlElement* xmlLayer, GameMap *gameMap, const ChunkSize depth, const int colCount, const int rowCount );

    MapParser();
    ~MapParser();
    static MapParser *instance;
    std::map<std::string, GameMap*> mapDict;

    bool deleted = false;

};

#endif // MAPPARSER_H
