/*
    #####################################################
    #                                                   #
    #   NCursed                                         #
    #       A Simple TUI Game written in C++            #
    #       using the NCurses library                   #
    #                                                   #
    #       Written by jcdotcom, started 01/26/2025     #
    #               current ver: 0.021a  06/30/2025     #
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
        tickSpeed = 10;
        elapsedTime = 0;
        p_posy = 3;
        p_posx = 6;
        m_posy = 1;
        m_posx = 1;
        inventory_used = 0;
        isRunning = true;

        mapYs = 3;
        mapXs = 3;

        map.resize(mapYs, std::vector<Area>(mapXs));

        debug_msg = "none";

        generateMap();

        current_area = &map[0][0];
    }

//-----[ GENERATOR FUNCTIONS ]-----//

void Game::generateMap(){
    std::vector<std::vector<roomdata>> doorMap(mapYs, std::vector<roomdata>(mapXs));
    int doorCount = 0;
    for (int y = 0; y < mapYs; y++) {
        for (int x = 0; x < mapXs; x++) {
            doorCount = 0;
            while( doorCount < 1 ){
                if( y < mapYs-1 && rand() % 2){
                    doorCount++;
                    doorMap[y][x].doorN = true;
                    doorMap[y + 1][x].doorS = true;
                }
                if( x < mapXs-1 && rand() % 2) {
                    doorCount++;
                    doorMap[y][x].doorE = true;
                    doorMap[y][x + 1].doorW = true;
                }
                if( y == mapYs-1 && x == mapXs - 1 ){
                    doorCount++;
                }
            }
        }
    }
    for (int y = 0; y < mapYs; y++) {
        for (int x = 0; x < mapXs; x++) {
            map[y][x] = generateRoom(y, x, doorMap[y][x]);
        }
    }
}

Area Game::generateRoom(int y, int x, roomdata rooms) {
    std::array<std::array<int,13>, 7> layout{};

    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 13; col++) {
            layout[row][col] = (row == 0 || row == 6 || col == 0 || col == 12) ? 2 : 0;
        }
    }

    bool dn = rooms.doorN;
    bool ds = rooms.doorS;
    bool de = rooms.doorE;
    bool dw = rooms.doorW;

    if(y == 0){ ds = false; }
    else if(y == mapYs - 1){ dn = false; }
    if(x == 0){ dw = false; }
    else if(x == mapXs - 1){ de = false; }

    if(dn){ layout[0][5] = 0; layout[0][6] = 0; layout[0][7] = 0; }
    if(ds){ layout[6][5] = 0; layout[6][6] = 0; layout[6][7] = 0; }
    if(de){ layout[2][12] = 0; layout[3][12] = 0; layout[4][12] = 0; }
    if(dw){ layout[2][0] = 0; layout[3][0] = 0; layout[4][0] = 0; }

    std::vector<Item*> inv;
    Area newRoom(std::to_string(y) + " " + std::to_string(x), y, x, layout, inv);
    newRoom.setDoors(dn, ds, de, dw);

    return newRoom;
}

//-----[ GAME FUNCTIONS ]-----//
    void Game::update() {
        if (p_posx <= BOUNDXL && m_posx > 0) {
            debug_msg = "left";
            current_area = &getRoom(current_area->get_mapY(), current_area->get_mapX() - 1, 3);
            m_posx--;
            p_posx = BOUNDXR;
        }
        else if (p_posx >= BOUNDXR && m_posx < mapXs) {
            debug_msg = "right";
            current_area = &getRoom(current_area->get_mapY(), current_area->get_mapX() + 1, 1);
            m_posx++;
            p_posx = BOUNDXL;
        }
        else if (p_posy <= BOUNDYU && m_posy < mapYs) {
            debug_msg = "up";
            current_area = &getRoom(current_area->get_mapY() + 1, current_area->get_mapX(), 0);
            m_posy++;
            p_posy = BOUNDYD;
        }
        else if (p_posy >= BOUNDYD && m_posy > 0) {
            debug_msg = "down";
            current_area = &getRoom(current_area->get_mapY() - 1, current_area->get_mapX(), 2);
            m_posy--;
            p_posy = BOUNDYU;
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
        mvwprintw(win_main, 0, 3, "[ ncursed alpha 0.021a ]");
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
                    mvaddch(y, x, current_area->get_char(yi, xi));
                    xi++;
                } else {
                    mvaddch(y, x, ' ');
                }
                // DEBUG MENU STATS
                const char* debug_msg_c = debug_msg.c_str();
                mvwprintw(win_stat,1,2,"[y/real =%2d /%2d]", translateY(),p_posy);
                mvwprintw(win_stat,2,2,"[x/real =%2d /%2d]", translateX(), p_posx);
                mvwprintw(win_stat,3,2,"[inv    =%2d /%2d]", inventory_used, INVENTORY_SIZE);
                mvwprintw(win_stat,4,2,"[room   =%2d /%2d]", m_posy, m_posx);
                mvwprintw(win_stat,5,2,"[map    =%2d /%2d]", mapYs, mapXs);
                //mvwprintw(win_stat,6,2,"[canTran=%2d    ]", canTransition);
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
        mvaddch(p_posy, p_posx, 'O');
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
        srand(time(0));
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
        getch();
        endwin();
    }

//-----[ GAME CONSTRUCTOR ]-----//

    Game::Game(){
        initscr();            // Initialize ncurses
        noecho();             // Disable key echoing
        curs_set(FALSE);      // Hide the cursor
    }