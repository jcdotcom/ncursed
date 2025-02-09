#include "Area.h"

Area::Area(){
    name = "";
    description = "";
    mapX = 0;
    mapY = 0;
    intmap = {{
    {0,0,0,1,0,0,0,0,0,2,0},
    {0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,2,0,0,0},
    {0,0,1,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,2,0,0,0}
    }};
    room_inventory = std::vector<Item*>();
}

Area::Area(std::string name, std::string desription, int mapX, int mapY, std::array<std::array<int, 13>, 7> inputmap, std::vector<Item*> room_inventory){
    this->name = name;
    this->description = description;
    this->mapX = mapX;
    this->mapY = mapY;
    this->intmap = intmap;
    this->room_inventory = room_inventory;
}

std::string Area::get_name(){
    return name;
}

std::string Area::get_description() const{
    return description;
}

int Area::get_mapX(){
    return mapX;
}

int Area::get_mapY(){
    return mapY;
}

std::array<std::array<int, 13>, 7>* Area::get_intmap(){
    return &intmap;
}

std::vector<Item*>& Area::get_room_inventory(){
    return room_inventory;
}

void Area::set_room_inventory(std::vector<Item*> room_inventory){
    this->room_inventory = room_inventory;
}

void Area::add_room_inventory(Item* item){
    room_inventory.push_back(item);
}

void Area::rm_room_inventory(Item* item){
    for(int i=0; i < room_inventory.size();i++){ 
        if(room_inventory[i]->get_name() == item->get_name() && room_inventory[i]->get_value() == item->get_value()){
           room_inventory.erase(room_inventory.begin()+i);
        }
    }
}

char Area::get_char(int yi, int xi){
    switch(intmap[yi][xi]){
        case 0:
            return '.';     // These are all player-blocking obstacles like walls
        case 1:
            return '.';
        case 2:
            return '#';     
        case 3:             
            return '&';    
        default:
            return 'X';     // If this is on screen thats bad news
    }
}

void Area::set_name(std::string name){
    this->name = name;
}

void Area::set_description(std::string description){
    this->description = description;
}

void Area::set_mapX(int mapX){
    this->mapX = mapX;
}

void Area::set_mapY(int mapY){
    this->mapY = mapY;
}

void Area::set_intmap(std::array<std::array<int, 13>, 7> intmap){
    this->intmap = intmap;
}

int Area::collision(int y, int x){
    switch(intmap[y][x]){
        case 0:
            return 0;
        case 1:
            return 2;
        case 2:
            return 2;
        default:
            return 2;
    }
}