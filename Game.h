/*
    #####################################################
    #                                                   #
    #   NCursed                                         #
    #       A Simple TUI Game written in C++            #
    #       using the NCurses library                   #
    #                                                   #
    #       Written by jcdotcom, started 01/26/2025     #
    #               current ver: 0.01a   02/09/2025     #
    #                                                   #
    #####################################################
*/

#define INVENTORY_SIZE 10

#include <bitset>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Area.h"

class Game{
    public:
        Game();
        
        void initGame();    // Game Variable Initialization
        
        void generateMap();
        Area generateRoom(int x, int y);

        void update();
        Area& getRoom(int x, int y, int d);

        void drawFrame();   // Rendering Functions
        void drawFloor();
        void drawPlayer();
        int translateX();
        int translateY();
        void update_message(std::string);
        int checkForItems();
        std::bitset<4> checkForDoors(int y, int x, std::bitset<4> doors);
        
        void input();       // Input Handler

        std::array<Item*,INVENTORY_SIZE> get_inventory();
        void add_inventory(Item*);      // Inventory Functions
        void rm_inventory(std::string);

        void play();        // Main Game Loop
    
    private:
        WINDOW *win_main;
        WINDOW *win_game;
        WINDOW *win_stat;
        WINDOW *win_msg;
        bool isRunning;
        int tickSpeed,
        elapsedTime,
        //mapYs, mapXs,     // TODO: 0.01b remove this line if new room gen stays
        p_posy, p_posx, //  Player Position Y & X
        player_health;

        //  player pos is real display coordinates 
        //  (ie: y=0,x=0 the top left on the game board is y=2, x=4)
      
        //std::array<std::array<Area, 2>, 2> map;
        std::vector<std::vector<Area>> map;
        Area* current_area;
        //Area begin;

        std::array<Item*,INVENTORY_SIZE> inventory;
        int inventory_used;
};