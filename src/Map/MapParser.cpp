#include "MapParser.h"
#include "../Assets/AssetsManager.h"
MapParser *MapParser::instance = nullptr;

const std::string MapParser::worldName = "overworld";
const std::string MapParser::worldAsset = Assets::maps+worldName+".tmx";
const std::string MapParser::blocksAsset = Assets::sprites+"blocks.tga";

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

bool MapParser::load()
{
    return parse(worldName,worldAsset);
}

bool MapParser::parse(const std::string &id, const std::string &source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
        throw "Failed to load: " + source + " Error(" + to_string(xml.ErrorId()) + "):";

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
    const std::string source = Assets::maps+xmlTileset->Attribute("source");
    tileset.source = MapParser::blocksAsset;

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
        throw "Failed to load: " + source;

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

    throw "Error al intentar leer el archivo de bloques: " + string(xmlTileset->Attribute("source"));
}

TileLayer *MapParser::parseTileLayer(TiXmlElement *xmlLayer, Tileset tileset, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data = xmlLayer->FirstChildElement("data");

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

