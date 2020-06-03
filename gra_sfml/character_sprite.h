#ifndef character_Sprite_H
#define character_Sprite_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace std;
using namespace sf;



class character_Sprite: public Sprite
{
private:
    vector<Texture>texture;

public:
    character_Sprite(string title, float OriginX, float OriginY, float PosX, float PosY);

};
void set_character_frames(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character_dead(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character_jump(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
#endif // character_Sprite_H
