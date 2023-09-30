#include "MapParser.h"
#include "../Graphics/TextureManager.h"

MapParser *MapParser::instance = nullptr;

const std::string MapParser::worldName = "overworld";
const std::string MapParser::worldAsset = TextureManager::assets+"maps/"+worldName+".tmx";
const std::string MapParser::blocksAsset = TextureManager::assets+"blocks.png";

MapParser::~MapParser()
{
    std::map<std::string, GameMap*>::iterator i;
    for(i = mapDict.begin(); i != mapDict.end();++i){
        delete i->second;
    }

    mapDict.clear();
}

bool MapParser::load()
{
    return parse(worldName,worldAsset);
}

bool MapParser::parse(const std::string &id, const std::string &source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error()){
        std::cerr << "Failed to load: " << source;
        std::cerr << " Error(" << xml.ErrorId() << "):" << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    int rowcount,colcount,tilesize = 0;
    root->Attribute("width",&colcount);
    root->Attribute("height",&rowcount);
    root->Attribute("tilewidth",&tilesize);

    Tileset tileset;
    for(TiXmlElement* e=root->FirstChildElement(); e != nullptr;e=e->NextSiblingElement()){
        if(e->Value() == std::string("tileset")){
            tileset = parseTileSet(e);
            break;
        }
    }

    GameMap *gamemap = new GameMap();
    for(TiXmlElement* e=root->FirstChildElement(); e != nullptr;e=e->NextSiblingElement()){
        if(e->Value() == std::string("layer")){
            TileLayer * tilelayer = parseTileLayer(e,tileset,tilesize,rowcount,colcount);
            gamemap->mapLayers.push_back(tilelayer);
        }
    }

    mapDict[id] = gamemap;
    return true;
}

Tileset MapParser::parseTileSet(TiXmlElement *xmlTileset)
{
    Tileset tileset;
    xmlTileset->Attribute("firstgid",&tileset.firstId);
    std::string source = TextureManager::assets+"maps/"+xmlTileset->Attribute("source");
    tileset.source = MapParser::blocksAsset;

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cerr << "Failed to load: " << source << std::endl;
        exit(1) ;
    }

    for(TiXmlElement* e=xml.RootElement(); e != nullptr;e=e->NextSiblingElement()){
        if(e->Value() == std::string("tileset")){
            tileset.name = e->Attribute("name");

            e->Attribute("tilecount",&tileset.tileCount);
            tileset.lastId = (tileset.firstId * tileset.tileCount) - 1;

            e->Attribute("columns",&tileset.colCount);
            tileset.rowCount = (tileset.tileCount/tileset.colCount);
            e->Attribute("tilewidth",&tileset.tileSize);

            return tileset;
        }
    }

    std::cout << "Error al intentar leer el archivo de bloques: " << TextureManager::assets+"maps/"+xmlTileset->Attribute("source");
    exit(1);
}

TileLayer *MapParser::parseTileLayer(TiXmlElement *xmlLayer, Tileset tileset, int tilesize, int rowcount, int colcount)
{
    TiXmlElement *data = nullptr;
    for(TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("data")){
            data = e;
            break;
        }
    }

    std::string matrix(data->GetText());
    std::stringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount,std::vector<unsigned int>(colcount,0));

    for(int row = 0; row < rowcount; row++){
        for(int col = 0; col < colcount;col++){
            getline(iss,id,',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good())
                break;
        }
    }

    return new TileLayer(tilesize,rowcount,colcount,tilemap,tileset);
}

void MapParser::clean()
{
    delete instance;
}







