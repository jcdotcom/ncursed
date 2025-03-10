#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Item.h"

#include <bitset> // 0.01b testing for new room gen

class Area{
    public:
        Area();
        Area(std::string name, int mapY, int mapX,
            std::array<std::array<int, 13>, 7> inputmap,
            std::vector<Item*> room_inventory, std::bitset<4> doors);

        char get_char(int x, int y);
        std::string get_name();
        std::string get_description() const;
        int get_mapX();
        int get_mapY();
        std::array<std::array<int, 13>, 7>* get_intmap();
        std::vector<Item*>& get_room_inventory();
        bool get_door(int direction);

        void set_name(std::string name);
        void set_description(std::string description);
        void set_mapX(int mapX);
        void set_mapY(int mapY);
        void set_intmap(std::array<std::array<int, 13>, 7> intmap);
        void set_room_inventory(std::vector<Item*>);
        void add_room_inventory(Item*);
        void rm_room_inventory(Item*);

        int collision(int x, int y);

    private:
        std::string name;
        std::string description;
        int mapX;
        int mapY;
        std::array<std::array<int, 13>, 7> intmap;
        std::vector<Item*> room_inventory;

        std::bitset<4> doors;   //0.01b testing changes
                                // 0 = N, 1 = E, 2 = S, 3 = W
};