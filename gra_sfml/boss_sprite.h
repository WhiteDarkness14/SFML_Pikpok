#ifndef BOSS_SPRITE_H
#define BOSS_SPRITE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace std;
using namespace sf;
#include "collision.h"

class boss_Sprite :public Sprite
{
private:
    vector<Texture>texture;
public:
    boss_Sprite(string title);
};
void set_boss_frames(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation);
void set_boss_dead(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation);
void set_boss_jump(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation);

#endif // BOSS_SPRITE_H
