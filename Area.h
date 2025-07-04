#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Item.h"

struct roomdata{
    bool doorN = false;
    bool doorS = false;
    bool doorE  = false;
    bool doorW  = false;
    bool visited;
    bool key = false;
    bool lock = false;
    int type = 0;
    int itemY = 4;
    int itemX = 8;
};

class Area{
    private:
        std::string name;
        std::string description;
        int mapX;
        int mapY;
        int lockY;
        int roomType;
        std::array<std::array<int, 13>, 7> intmap;
        std::vector<Item*> room_inventory;

        bool doorN = false, doorS = false, doorE = false, doorW = false, lock = false;

    public:
        Area();
        Area(std::string name, int mapY, int mapX,
            std::array<std::array<int, 13>, 7> inputmap,
            std::vector<Item*> room_inventory, int roomType);
            
        char get_char(int x, int y);
        std::string get_name();
        int get_type();
        std::string get_description() const;
        int get_mapX();
        int get_mapY();
        std::array<std::array<int, 13>, 7>* get_intmap();
        std::vector<Item*>& get_room_inventory();
        int get_lockY();
        void set_type(int t);
        void set_lockY(int y);
        void set_lock();
        void unlock();

        void set_name(std::string name);
        void set_description(std::string description);
        void set_mapX(int mapX);
        void set_mapY(int mapY);
        void set_intmap(std::array<std::array<int, 13>, 7> intmap);
        void set_room_inventory(std::vector<Item*>);
        void add_room_inventory(Item*);
        void rm_room_inventory(Item*);

        int collision(int x, int y);

        bool hasDoorNorth() const { return doorN; }
        bool hasDoorSouth() const { return doorS; }
        bool hasDoorEast()  const { return doorE; }
        bool hasDoorWest()  const { return doorW; }
        bool hasLock() const { return lock; }

        void setDoors(bool n, bool s, bool e, bool w) {
            doorN = n; doorS = s; doorE = e; doorW = w;
        }

};