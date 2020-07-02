#pragma once
#include "headers.h"
class boss_Sprite :public general
{
public:
    boss_Sprite(string title);
};
void set_boss_frames(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation);
void set_boss_dead(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation);
void set_boss_jump(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation);
void set_boss(vector<vector<boss_Sprite>> &boss);
