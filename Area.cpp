#include "Area.h"

Area::Area(){
    name = "";
    mapX = 0;
    mapY = 0;
    intmap = {{
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,0,0,0,2,0,0,0,0,0,0,0,2},
        {2,0,0,0,2,0,0,0,0,0,0,0,0},
        {2,2,0,2,2,0,0,0,0,0,0,0,0},
        {2,0,0,0,0,0,0,0,0,0,0,0,0},
        {2,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2}
    }};
    room_inventory = std::vector<Item*>();
    doors = 0b0000;
}

Area::Area(std::string name, int mapY, int mapX, 
            std::array<std::array<int, 13>, 7> inputmap, 
            std::vector<Item*> room_inventory, std::bitset<4> doors){
    this->name = name;
    this->mapY = mapY;
    this->mapX = mapX;
    this->intmap = inputmap;
    this->room_inventory = room_inventory;
    this->doors = doors;
}

std::string Area::get_name(){
    return name;
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

bool Area::get_door(int direction){
    return doors[direction];
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