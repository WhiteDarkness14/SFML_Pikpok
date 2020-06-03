#ifndef OBSTACLE_SPRITE_H
#define OBSTACLE_SPRITE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "collision.h"
#include "character_sprite.h"
using namespace std;
using namespace sf;


class obstacle_Sprite: public Sprite
{
private:
    vector<Texture>texture_obstacle;

public:
    bool to_move=false;
    obstacle_Sprite(string title, float scale);

};
void set_mushrooms(vector<obstacle_Sprite> &mushrooms);
void set_bird(vector<obstacle_Sprite> &bird);
void generate_obstacle(vector<vector<obstacle_Sprite> > &birds, vector<obstacle_Sprite> &mushrooms);

#endif // OBSTACLE_SPRITE_H
