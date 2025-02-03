#include <string>

class Item{
    public:
        virtual ~Item() {}
        virtual void set_name(std::string) = 0;
        virtual void set_desc(std::string) = 0;
        virtual void set_value(int) = 0;
        virtual void set_posy(int) = 0;
        virtual void set_posx(int) = 0;
        virtual void set_char(char) = 0;

        virtual std::string get_name(){ return name; };
        virtual std::string get_desc(){ return desc; };
        virtual int get_value(){ return value; };
        virtual int get_posy(){ return posx; };
        virtual int get_posx(){ return posy; };
        virtual char get_char(){ return itemchar; }

        virtual int use(int input = 0) = 0;

    protected:
        std::string name, desc;
        int value, posx, posy;
        char itemchar;
};

class EmptyItem : public Item {
    public:
        EmptyItem(){
            name = "empty";
            desc = "";
            value = 0;
            posx = 0;
            posy = 0;
        };
        int use(int input = 0) override{
            return 0;
        }
        std::string get_name() override{}
        std::string get_desc() override{}
        int get_value() override{}
        int get_posy() override{}
        int get_posx() override{}
        char get_char() override{}
        void set_name(std::string input) override{}
        void set_desc(std::string input) override{}
        void set_value(int input) override{}
        void set_posy(int input) override{}
        void set_posx(int input) override{}
        void set_char(char input) override{}
};

class Key : public Item {
    public:
        Key(){};
        Key(std::string n, std::string d, int v, int y, int x, char c = 'k'){ 
            name = n; 
            desc = d;
            value = v;
            posx = x;
            posy = y;
            itemchar = c;
        };
        int use(int input) override{
            return value;
        }
        std::string get_name() override { return name; }
        std::string get_desc() override { return desc; }
        int get_value() override { return value; }
        int get_posy() override { return posy; }
        int get_posx() override { return posx; }
        char get_char() override { return itemchar; }

        void set_name(std::string input) override { name = input; }
        void set_desc(std::string input) override { desc = input; }
        void set_value(int input) override { value = input; }
        void set_posy(int input) override { posy = input; }
        void set_posx(int input) override { posx = input; }
        void set_char(char input) override { itemchar = input; }
};

class HealthItem : public Item {
    public:
        HealthItem(){};
        HealthItem(std::string n, std::string d, int v, int y, int x, char c){
            name = n; 
            desc = d;
            value = v;
            posx = x;
            posy = y;
            itemchar = '+';
        };
        int use(int input) override{
            return value;
        }
        std::string get_name() override { return name; }
        std::string get_desc() override { return desc; }
        int get_value() override { return value; }
        int get_posy() override { return posy; }
        int get_posx() override { return posx; }
        char get_char() override { return itemchar; }

        void set_name(std::string input) override { name = input; }
        void set_desc(std::string input) override { desc = input; }
        void set_value(int input) override { value = input; }
        void set_posy(int input) override { posy = input; }
        void set_posx(int input) override { posx = input; }
        void set_char(char input) override { itemchar = input; }
};