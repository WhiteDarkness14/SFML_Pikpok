#pragma once
#include "general.h"


class obstacle_Sprite: public general
{
public:
    bool to_move=false;
    obstacle_Sprite();
    //obstacle_Sprite(string title, float scale);
    obstacle_Sprite(string name, const float scale);

};
void set_flames(vector<obstacle_Sprite> &flame_dino, vector<obstacle_Sprite> &flame_character);
void generate_obstacle(vector<vector<obstacle_Sprite> > &birds, vector<obstacle_Sprite> &mushrooms);
void generate_flame(vector<obstacle_Sprite> &flame_dino);
void make_flame(obstacle_Sprite & flame, string name);
void set_obstacle(vector<obstacle_Sprite>&mushrooms, vector<vector<obstacle_Sprite> > &birds);

