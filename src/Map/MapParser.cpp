#include "MapParser.h"
#include "../Assets/AssetsManager.h"
#include "Chunk.h"
#include "GameMap.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
MapParser *MapParser::instance = nullptr;

const std::string MapParser::worldName = "overworld";
const std::string MapParser::worldAsset = ASSETS_MAPS_PATH+worldName+".tmx";
const std::string MapParser::blocksAsset = std::string(ASSETS_SPRITES_PATH)+"blocks.bmp";

MapParser::MapParser() {
    // Inicializa cualquier miembro necesario en el constructor
    // Puedes poner tu código de inicialización aquí
}

MapParser::~MapParser()
{
    std::map<std::string, GameMap*>::iterator i;
    for(i = mapDict.begin(); i != mapDict.end();++i){
        delete i->second;
    }

    mapDict.clear();
}

void MapParser::load()
{
    parse(worldName,worldAsset);
}

void MapParser::parse(const std::string &id, const std::string &source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
        throw "Failed to load: " + source + " Error(" + to_string(xml.ErrorId()) + "):";

    TiXmlElement *root = xml.RootElement();
    int rowCount,colCount;
    root->Attribute("width",&colCount);
    root->Attribute("height",&rowCount);

    for(TiXmlElement* e=root->FirstChildElement(); e != nullptr;e=e->NextSiblingElement()){
        if(e->Value() == std::string("tileset")){
            AssetsManager::get()->setTileset(parseTileSet(e));
            break;
        }
    }

    GameMap *gameMap = new GameMap(colCount/8, rowCount/8);
    for(TiXmlElement* e=root->FirstChildElement(); e != nullptr;e=e->NextSiblingElement()){
        if(e->Value() == std::string("layer")){
            parseChunks( e, gameMap, (e->Attribute("name") == std::string("background")?0:1), colCount, rowCount );
        }
    }

    mapDict[id] = gameMap;
}

Tileset *MapParser::parseTileSet(TiXmlElement *xmlTileset)
{
    Tileset *tileset = new Tileset();
    const std::string source = std::string(ASSETS_MAPS_PATH)+xmlTileset->Attribute("source");
    tileset->source = MapParser::blocksAsset;


    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        delete tileset;
        throw "Failed to load: " + source;
    }

    for(TiXmlElement* e=xml.RootElement(); e != nullptr;e=e->NextSiblingElement()){
        if(strcmp(e->Value(),"tileset") == 0){
            tileset->name = e->Attribute("name");

            AssetsManager::get()->loadTexture(tileset->name,tileset->source,true);
            e->Attribute("tilecount",&tileset->tileCount);

            e->Attribute("columns",&tileset->colCount);
            tileset->rowCount = (tileset->tileCount/tileset->colCount);
            
            tileset->srcRect = { 0, 0, (float)TILE_SIZE, (float)TILE_SIZE};

            tileset->textures.reserve(tileset->tileCount);
            tileset->textures.push_back(nullptr);
            for (int tileId = 0; tileId < tileset->tileCount; ++tileId) {
                tileset->textures.push_back( 
                    AssetsManager::get()->loadTexture(
                        tileset->name,
                        tileset->source,
                        false,
                        false, 
                        {
                            (tileId % tileset->colCount)*TILE_SIZE, 
                            (tileId / tileset->colCount)*TILE_SIZE, 
                            TILE_SIZE, 
                            TILE_SIZE
                        }
                    )
                );
            }

            return tileset;
        }
    }

    throw "Error al intentar leer el archivo de bloques: " + string(xmlTileset->Attribute("source"));
}

void MapParser::parseChunks( TiXmlElement* xmlLayer, GameMap *gameMap, const ChunkSize depth, const int colCount, const int rowCount )
{
    TiXmlElement* data = xmlLayer->FirstChildElement("data");

    std::string matrix(data->GetText());
    std::stringstream iss(matrix);
    std::string id;
    
    for( int y = 0; y < rowCount; ++y ){
        for( int x = 0; x < colCount; ++x ){
            getline(iss,id,',');

            if( id != "0" )
                gameMap->setTile( x, y, depth, stoul(id));

            if(!iss.good())
                break;
        }
    }
}

