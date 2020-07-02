#pragma once
#include "headers.h"
class character_Sprite: public general
{

public:
    character_Sprite(string title, float OriginX, float OriginY, float PosX, float PosY);

};
void set_character_frames(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character_dead(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character_jump(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character(vector<vector<vector<character_Sprite> > > &character_animation);
