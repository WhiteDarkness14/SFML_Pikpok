﻿#include "boss_sprite.h"

boss_Sprite::boss_Sprite(string title)
{
    string file_name="picture/"+title+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    shared_ptr<Texture> object_ptr = make_shared<Texture>(text);
    LoadTexture(object_ptr);
    setPosition(1850,972);
    setOrigin(680,472);
}
void set_boss_frames(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation)
{

    for(int i=1;i<=nr_of_animation;i++)
    {
        string f_name=file_name+"(";
        f_name+=to_string(i);
        f_name+=")";
        ch_vec.emplace_back(f_name);
    }
}
void set_boss_dead(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation)
{
    set_boss_frames(ch_vec,file_name,nr_of_animation);
    int posX=1850;
    for(auto &b:ch_vec)
    {
        b.setPosition(posX,972);
        posX+=10;
    }
}

void set_boss(vector<vector<boss_Sprite>> &boss)
{
    vector<boss_Sprite> boss_run;
    set_boss_frames(boss_run,"boss/run/Run ",8);
    vector<boss_Sprite> boss_dead;
    set_boss_dead(boss_dead,"boss/dead/Dead ",8);
    boss.emplace_back(boss_run);
    boss.emplace_back(boss_dead);
}
