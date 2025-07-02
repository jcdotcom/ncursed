/*
    #####################################################
    #                                                   #
    #   NCursed                                         #
    #       A Simple TUI Game written in C++            #
    #       using the NCurses library                   #
    #                                                   #
    #       Written by jcdotcom, started 01/26/2025     #
    #               current ver: 0.03a   07/02/2025     #
    #                                                   #
    #####################################################
*/

#define INVENTORY_SIZE 10

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
        Area generateRoom(int x, int y, roomdata rooms);

        void update();
        Area& getRoom(int x, int y, int d);

        void drawFrame();   // Rendering Functions
        void drawFloor();
        void drawPlayer();
        int translateX();
        int translateY();
        void update_message(std::string);
        int checkForItems();
        int checkForLock();
        int checkForClear();
        
        void input();       // Input Handler

        std::array<Item*,INVENTORY_SIZE> get_inventory();
        void add_inventory(Item*);      // Inventory Functions
        void rm_inventory(std::string);
        bool hasKey();

        void play();        // Main Game Loop
        std::string debug_msg;
    
    private:
        WINDOW *win_main;
        WINDOW *win_game;
        WINDOW *win_stat;
        WINDOW *win_msg;
        bool isRunning;
        int tickSpeed,
        elapsedTime,
        mapYs, mapXs,
        p_posy, p_posx, //  Player Position in room
        m_posy, m_posx, //  Player Position in map
        player_health;

        int keyRoomY;
        int keyRoomX;
        int lockRoomY;
        int lockRoomX;

        int wins;

        bool cleared;

        std::vector<std::vector<Area>> map;
        Area* current_area;
        Area begin;

        std::array<Item*,INVENTORY_SIZE> inventory;
        int inventory_used;
};