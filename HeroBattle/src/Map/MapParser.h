#ifndef MAPPARSER_H
#define MAPPARSER_H

#include<map>
#include<string>
#include"GameMap.h"
#include"TileLayer.h"
#include "tinyxml.h"

class MapParser
{
  public:
     bool Load(std::string path, std::string mapName);
     void Clean();


     inline GameMap* GetMap(std::string id){return m_MapDict[id];}
    inline static MapParser* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new MapParser();
  }
  private:
   bool Parse(std::string id,std::string source);
   Tileset ParseTileset(TiXmlElement* xmlTileset);
   TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

  private:
  MapParser(){}
   static MapParser* m_Instance;
   std::map<std::string, GameMap*> m_MapDict;
};





#endif
