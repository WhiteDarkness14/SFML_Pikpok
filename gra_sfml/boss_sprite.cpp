#include "boss_sprite.h"

boss_Sprite::boss_Sprite(string title)
{
    string file_name="picture/"+title+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    texture.emplace_back(text);
    setTexture(texture[0]);
    setPosition(1850,972);
    setOrigin(680,472);
 //   setScale(0.9,0.9);
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
void set_boss_jump(vector<boss_Sprite> &ch_vec, string file_name,float nr_of_animation)
{
    set_boss_frames(ch_vec,file_name,nr_of_animation);
    int posY=0;
    for(int i=0;i<ch_vec.size();i++)
    {
        if(i<6)
        {
            ch_vec[i].move(0,posY);
            posY-=25;
        }
        else
        {
            ch_vec[i].move(0,posY);
            posY+=25;
        }
    }
}
