/*
    #####################################################
    #                                                   #
    #   NCursed                                         #
    #       A Simple TUI Game written in C++            #
    #       using the NCurses library                   #
    #                                                   #
    #       Written by jcdotcom, started 01/26/2025     #
    #               current ver: 0.01    02/02/2025     #
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
    const int BOUNDXL = 3;
    const int BOUNDXR = 29;
    const int DISPHEIGHT = 11;

//-----[ GAME VAR INITIALIZATION ]-----//

    void Game::initGame(){
        begin = Area();
        std::array<std::array<int,13>, 7> mapBegin = {{
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,0,0,0,2,0,0,0,0,0,0,0,2},
        {2,0,0,0,2,0,0,0,0,0,0,0,0},
        {2,2,0,2,2,0,0,0,0,0,0,0,0},
        {2,0,0,0,0,0,0,0,0,0,0,0,0},
        {2,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2}
        }};
        begin.set_name("start");
        begin.set_description("the starting room");
        begin.set_mapX(0);
        begin.set_mapY(0);
        begin.set_intmap(mapBegin);
        begin.set_room_inventory(
            {{new HealthItem("bandage","a basic bandage",25,4,18,'+')}, 
            {new Key("rusty key","a rusty key", 1, 3, 24, 'k')}}
        );
        map;
        map[0][0] = begin;
        current_area = &map[0][0];
        tickSpeed = 10; // milliseconds
        elapsedTime = 0;
        p_posy = 3;     // starting player position Y axis
        p_posx = 6;     // starting player position X axis
        inventory_used = 0; // amount of inventory space used / 10
        isRunning = true;
    }

//-----[ GENERATOR FUNCTIONS ]-----//

    Area Game::generateRoom(int x, int y, int d){   //  x co-ord of new room
        Area newArea = Area();                      //  y co-ord of new room
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
            mvwprintw(win_stat,4,2,"[roll =%d]",roll);
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

        return newArea;
    }

//-----[ GAME FUNCTIONS ]-----//

    void Game::update(){
        if(p_posx==BOUNDXL){
          getRoom((current_area->get_mapX())-1, current_area->get_mapY(), 4);  
        }
        else if(p_posx==BOUNDXR){
          getRoom((current_area->get_mapX())+1, current_area->get_mapY(), 4);
        }
        else if(p_posy==BOUNDYU){
          getRoom(current_area->get_mapX(), (current_area->get_mapY())-1, 4);
        }
        else if(p_posy==BOUNDYD){
          getRoom(current_area->get_mapX(), (current_area->get_mapY())+1, 4);
        }
    }

    Area Game::getRoom(int x, int y, int d){
        //if(){

        //}
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
                mvwprintw(win_stat,1,2,"[y/real =%2d /%2d]", translateY(),p_posy);
                mvwprintw(win_stat,2,2,"[x/real =%2d /%2d]", translateX(), p_posx);
                mvwprintw(win_stat,3,2,"[inv=%2d /%2d]", inventory_used, INVENTORY_SIZE);
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
        switch(ch) {
            case 'w':
                if(p_posy > BOUNDYU){
                    if(current_area->collision(translateY()-1, translateX())<=1){
                        p_posy--;
                    }
                }
                break;
            case 's':
                if(p_posy < BOUNDYD){
                    if(current_area->collision(translateY()+1, translateX())<=1){
                        p_posy++;
                    }
                }
                break;
            case 'a':
                if(p_posx > BOUNDXL+2){
                    if(current_area->collision(translateY(),translateX()-1)<=1){
                        p_posx-=2;
                    }
                }
                break;
            case 'd':
                if(p_posx < BOUNDXR-2){
                    if(current_area->collision(translateY(), translateX()+1)<=1){
                        p_posx+=2;
                    }
                }
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
        getch(); // Wait for user input before closing
        endwin(); // End ncurses mode
    }

//-----[ GAME CONSTRUCTOR ]-----//

    Game::Game(){
        initscr();            // Initialize ncurses
        noecho();             // Disable key echoing
        curs_set(FALSE);      // Hide the cursor
    }