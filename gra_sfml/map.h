#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

void window_set(RenderWindow &window);

class map_Sprite: public Sprite
{
private:

    vector<Texture>texture;


public:
    map_Sprite(string title, int posX, int posY, int originX, int originY, float scale);
    bool to_move=true;
};

void set_frames(vector <map_Sprite> & map_vec, string file_name, float PosX, float PosY, float OriginX, float OriginY, int size);
void set_frames_jump(vector<map_Sprite> &map_vec, string file_name, float PosX, float PosY, float OriginX, float OriginY, int size);
void set_clouds(vector <map_Sprite> &map_cloud);
void generate_obstacle(vector<vector<map_Sprite> > &birds, vector<map_Sprite> &mushrooms);
#endif // GAME_H
