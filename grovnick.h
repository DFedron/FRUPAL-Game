// grovnick.h

#include <string>

using namespace std;

class Grovnick {
    public:
        Grovnick();
        void input_terrain(int c_value, int e_cost);
        int get_terrain_energy_cost();
        void print();
        int get_terrain_color_value();

    private:
        int color_value;
        int energy_cost;
//      Item item; 

//      void input_item(Item item);
//      bool has_item();
//      Item & get_item();

};
