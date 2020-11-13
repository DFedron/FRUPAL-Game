// grovnick.h
   

#include <string>
using namespace std;


class Terrain{

    private:
       int color_value;
       int energy_cost; 

    public:
       Terrain();
       void input_terrain(int c_value, int e_cost);
       void print_terrain();
       int get_energy_cost();
       int get_color_value();       
};



class Grovnick{

    private:
        Terrain terrain;
//      Item item; 

    public:
        Grovnick();
        void input_terrain(int c_value, int e_cost);
        int get_terrain_energy_cost();
        void print();
        int get_terrain_color_value();
};

