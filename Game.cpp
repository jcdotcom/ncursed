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

#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "Game.h"
#include <iostream>

//-----[ GAME CONSTS ]-----//

    const int HEIGHT = 15;
    const int WIDTH = 66;
    const int BOUNDYU = 2;
    const int BOUNDYD = 8;
    const int BOUNDXL = 4;
    const int BOUNDXR = 28;
    const int DISPHEIGHT = 11;

//-----[ GAME VAR INITIALIZATION ]-----//

    void Game::initGame(){
        tickSpeed = 10; // milliseconds
        elapsedTime = 0;
        p_posy = 3;
        p_posx = 6;
        m_posy = 1;
        m_posx = 1;
        inventory_used = 0;
        isRunning = true;
        canTransition = true;

        mapYs = 4;
        mapXs = 4;

        map.resize(mapYs, std::vector<Area>(mapXs));

        debug_msg = "none";
        int count = 0;
        for (int y = 0; y < mapYs; y++) {
            for (int x = 0; x < mapXs; x++) {
                map[y][x] = generateRoom(y, x, -1); // -1 = no direction (initial gen)
                count++;
            }
        }
        //debug_msg = std::to_string(count);
        current_area = &map[1][1]; // Start in center of 3x3 grid
    }

//-----[ GENERATOR FUNCTIONS ]-----//

Area Game::generateRoom(int y, int x, int d) {
    std::array<std::array<int,13>, 7> layout{};

    // Outer walls
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 13; col++) {
            layout[row][col] = (row == 0 || row == 6 || col == 0 || col == 12) ? 2 : 0;
        }
    }

        /*
        
            !!! door generation is broken here
        
        */

    bool isNorthEdge = (y == 3);
    bool isSouthEdge = (y == 1);
    bool isWestEdge  = (x == 1);
    bool isEastEdge  = (x == 3);

    // --- Determine doors from existing adjacent rooms --- //
    bool northDoor = (y > 0 && y + 1 < mapYs && x < map[y - 1].size() &&
                      map[y - 1][x].hasDoorSouth());
    bool southDoor = (y + 1 < mapYs && x < mapXs &&
                      map[y + 1][x].hasDoorNorth());
    bool westDoor =  (x > 0 && map[y][x - 1].hasDoorEast());
    bool eastDoor =  (x < mapXs && map[y][x + 1].hasDoorWest());

    // --- Random doors, only if within bounds and not already set by neighbor --- //
    if (!northDoor && y > 0 && !isNorthEdge && rand() % 2) northDoor = true;
    if (!southDoor && y < map.size() && !isSouthEdge && rand() % 2) southDoor = true;
    if (!westDoor  && x > 0 && !isWestEdge  && rand() % 2) westDoor  = true;
    if (!eastDoor  && x < map[y].size() && !isEastEdge  && rand() % 2) eastDoor  = true;

    // Apply doors
    if (northDoor) {
    layout[0][5] = layout[0][6] = layout[0][7] = 0;
    layout[1][5] = layout[1][6] = layout[1][7] = 0;
}

// South door (bottom wall), open row 6 and row 5
if (southDoor) {
    layout[6][5] = layout[6][6] = layout[6][7] = 0;
    layout[5][5] = layout[5][6] = layout[5][7] = 0;
}

// West door (left wall), open col 0 and col 1
if (westDoor) {
    layout[2][0] = layout[3][0] = layout[4][0] = 0;
    layout[2][1] = layout[3][1] = layout[4][1] = 0;
}

// East door (right wall), open col 12 and col 11
if (eastDoor) {
    layout[2][12] = layout[3][12] = layout[4][12] = 0;
    layout[2][11] = layout[3][11] = layout[4][11] = 0;
}

    // --- Save this info in the Area (so future rooms can reference it) --- //
    std::vector<Item*> inv;
    Area newRoom(std::to_string(y) + " " + std::to_string(x), y, x, layout, inv);
    newRoom.setDoors(northDoor, southDoor, eastDoor, westDoor); // You'll implement this

    return newRoom;
}

/*
    Area Game::generateRoom(int y, int x, int d){   //  x co-ord of new room
                                                     //  y co-ord of new room
        std::array<std::array<int,13>, 7> base = {{ //  d direction entered from
        {2,2,2,2,2,2,2,2,2,2,2,2,2},                //      0   -   N
        {2,0,0,0,0,0,0,0,0,0,0,0,2},                //      1   -   E
        {2,0,0,0,0,0,0,0,0,0,0,0,2},                //      2   -   S
        {2,0,0,0,0,0,0,0,0,0,0,0,2},                //      3   -   W
        {2,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2}
        }};
        int roll = (rand() >> 5) % 3;
        for(int i=0;i<roll;i++){
            mvwprintw(win_stat,4+i,2,"[roll =%d]",roll);
            wrefresh(win_stat);
        }
        
        roll = (rand() >> 4) % 5;
        while(roll==d){
            roll = (rand() >> 4) % 5;
        }
        if(roll==0){

        }
        else if(roll==1){

        }
        else if(roll==2){

        }
        else{
            
        }

        std::vector<Item*> inv;

        return Area(std::to_string(y) + " " + std::to_string(x),y,x,base,inv); 
    }
*/
//-----[ GAME FUNCTIONS ]-----//
    void Game::update() {
        if (!canTransition) return;
        else if (p_posx <= BOUNDXL && m_posx > 1) {
            debug_msg = "left";
            current_area = &getRoom(current_area->get_mapY(), current_area->get_mapX() - 1, 3);
            m_posx--;
            p_posx = BOUNDXR; // Move slightly inside the new room
            canTransition = false;
        }
        else if (p_posx >= BOUNDXR && m_posx < 4) {
            debug_msg = "right";
            current_area = &getRoom(current_area->get_mapY(), current_area->get_mapX() + 1, 1);
            m_posx++;
            p_posx = BOUNDXL;
            canTransition = false;
        }
        else if (p_posy <= BOUNDYU && m_posy < 4) {
            debug_msg = "up";
            current_area = &getRoom(current_area->get_mapY() + 1, current_area->get_mapX(), 0);
            m_posy++;
            p_posy = BOUNDYD;
            canTransition = false;
        }
        else if (p_posy >= BOUNDYD && m_posy > 1) {
            debug_msg = "down";
            current_area = &getRoom(current_area->get_mapY() + 1, current_area->get_mapX(), 2);
            m_posy--;
            p_posy = BOUNDYU;
            canTransition = false;
        }
    }

    Area& Game::getRoom(int y, int x, int d){
        if (y >= map.size()) {
            map.resize(y + 1, std::vector<Area>(mapXs));
            mapYs = map.size();
        }
        if (x >= map[y].size()) {
            map[y].resize(x + 1);
            mapXs = std::max(mapXs, (int)map[y].size());
        }

        Area& area = map[y][x];
        if (area.get_name() == "") {
            Area newArea = generateRoom(y, x, d);
            map[y][x] = newArea;
        }
        return map[y][x];
    }
//-----[ RENDER FUNCTIONS ]-----//

    void Game::drawFrame(){
        win_main = newwin(14,54,0,0);
        win_game = newwin(9, 29, 1, 2);
        win_stat = newwin(9, 20, 1, 32);
        win_msg = newwin(3, 51, 10, 2);
        refresh();
        box(win_main, 0, 0);
        box(win_game, 0, 0);
        box(win_stat, 0, 0);
        box(win_msg, 0, 0);
        mvwprintw(win_main, 0, 3, "[ ncursed alpha 0.01 ]");
        mvwprintw(win_stat, 0, 3, "[ debug ]");
        wrefresh(win_main);
        wrefresh(win_game);
        wrefresh(win_stat);
        wrefresh(win_msg);
    }

    void Game::drawFloor(){
        for (int y = BOUNDYU, yi = 0; y <= BOUNDYD; y++, yi++){
            for (int x = BOUNDXL, xi = 0; x <= BOUNDXR; x++){
                if (y == p_posy && x == p_posx){
                    xi++;
                } else if (x%2==0 ){
                    mvaddch(y, x, current_area->get_char(yi, xi)); // Draw everything else
                    xi++;
                } else {
                    mvaddch(y, x, ' '); // Draw the background
                }
                // DEBUG MENU STATS
                const char* debug_msg_c = debug_msg.c_str();
                mvwprintw(win_stat,1,2,"[y/real =%2d /%2d]", translateY(),p_posy);
                mvwprintw(win_stat,2,2,"[x/real =%2d /%2d]", translateX(), p_posx);
                mvwprintw(win_stat,3,2,"[inv    =%2d /%2d]", inventory_used, INVENTORY_SIZE);
                mvwprintw(win_stat,4,2,"[room   =%2d /%2d]", m_posy, m_posx);
                mvwprintw(win_stat,5,2,"[map    =%2d /%2d]", mapYs, mapXs);
                mvwprintw(win_stat,6,2,"[canTran=%2d    ]", canTransition);
                mvwprintw(win_stat,7,2,"[debug  = %s ]", debug_msg_c);
                wrefresh(win_stat);
            }
        }
        for(Item* item : current_area->get_room_inventory()){
            mvaddch(item->get_posy(), item->get_posx(), item->get_char());
        }
        refresh();
    }

    void Game::drawPlayer(){
        mvaddch(p_posy, p_posx, 'O'); // Draw the player
        refresh();
    }

    int Game::translateY(){
        return p_posy - 2;
    }

    int Game::translateX(){
        return (p_posx - 4)>>1;
    }

    void Game::update_message(std::string input){
        werase(win_msg);
        box(win_msg, 0, 0);
        mvwprintw(win_msg,1,7,input.c_str());
        wrefresh(win_msg);
    }

    int Game::checkForItems(){
        for(Item* item : current_area->get_room_inventory()){
            if(p_posy==item->get_posy()){
                if(p_posx==item->get_posx()){
                    if(inventory_used<10){
                        update_message("Press [SPACE] to pick up "+item->get_name());
                        return 1;
                    }
                    else{
                        update_message("Can't pick up, inventory full!");
                        return 1;
                    }
                }
            }
        }
        update_message("");
        return 0;
    }

//-----[ INPUT HANDLER ]-----//

    void Game::input(){
        nodelay(stdscr, TRUE);
        int ch = getch();
        if (p_posx >= BOUNDXL + 2 && p_posx <= BOUNDXR - 2 &&
            p_posy > BOUNDYU + 1 && p_posy < BOUNDYD - 1) {
            canTransition = true;
        }
        switch(ch) {
            case 'w':
                if(p_posy > BOUNDYU){
                    if(current_area->collision(translateY()-1, translateX())<=1){
                        p_posy--;
                    }
                    else{
                        debug_msg = "collU";
                    }
                }
                update();
                break;
            case 's':
                if(p_posy < BOUNDYD){
                    if(current_area->collision(translateY()+1, translateX())<=1){
                        p_posy++;
                    }
                    else{
                        debug_msg = "collD";
                    }
                }
                update();
                break;
            case 'a':
                if(p_posx > BOUNDXL || p_posx == 4){
                    if(current_area->collision(translateY(),translateX()-1)<=1){
                        p_posx-=2;
                    }
                    else{
                        debug_msg = "collL";
                    }
                }
                update();
                break;
            case 'd':
                if(p_posx < BOUNDXR){
                    if(current_area->collision(translateY(), translateX()+1)<=1){
                        p_posx+=2;
                    }
                    else{
                        debug_msg = "collR";
                    }
                }
                update();
                break;
            case ' ':
                for(Item* item : current_area->get_room_inventory()){
                    if(p_posy == item->get_posy() && p_posx == item->get_posx()){
                        if(inventory_used<10){
                            inventory[inventory_used] = item;
                            inventory_used++;
                            current_area->rm_room_inventory(item);
                            update_message("");
                        }
                        else{
                            update_message("Inventory full!");
                        }
                    }
                }
                update();
                break;
        }
    }

//-----[ INVENTORY FUNCTIONS ]-----//
    
    std::array<Item*,INVENTORY_SIZE> Game::get_inventory(){
        return this->inventory;
    }

    void Game::add_inventory(Item* item){
        if(inventory_used<10){
            rm_inventory("empty");
            inventory[inventory_used] = item;
            inventory_used++;
        }
    }

    void Game::rm_inventory(std::string itemname){
        for(int i = 0; i < inventory_used; i++){
            if(inventory[i]->get_name() == itemname){
                delete inventory[i]; 
                inventory[i] = new EmptyItem();
                inventory_used--;
            }
        }
    }

//-----[ MAIN GAME LOOP ]-----//
        
    void Game::play(){
        initGame();
        drawFrame();
        drawFloor();
        try{
            while (isRunning){
                drawPlayer();
                drawFloor();
                input();
                checkForItems();
                elapsedTime += 50;
                if (elapsedTime >= tickSpeed){
                    refresh();
                    elapsedTime = 0;
                }
            }
        }catch(std::exception& e){
            endwin();
            printf("Game exited with error %s", e);
        }
        getch(); // Wait for user input before closing
        endwin(); // End ncurses mode
    }

//-----[ GAME CONSTRUCTOR ]-----//

    Game::Game(){
        initscr();            // Initialize ncurses
        noecho();             // Disable key echoing
        curs_set(FALSE);      // Hide the cursor
    }