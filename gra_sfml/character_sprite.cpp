#include "character_sprite.h"
#include "collision.h"

character_Sprite::character_Sprite(string title, float OriginX, float OriginY, float PosX, float PosY)
{
    string file_name="picture/"+title+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    texture.emplace_back(text);
    setTexture(texture[0]);
    setPosition(PosX,PosY);
    setOrigin(OriginX,OriginY);
    setScale(0.6,0.6);
}

void set_character_frames(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation)
{
    for(int i=1;i<=nr_of_animation;i++)
    {
        string f_name=file_name+"(";
        f_name+=to_string(i);
        f_name+=")";
        ch_vec.emplace_back(f_name,OriginX,OriginY, PosX, PosY);
    }
}

void set_character_jump(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation)
{
    set_character_frames(ch_vec, file_name, OriginX, OriginY, PosX, PosY, nr_of_animation);
    int posY=0;
    for(int i=0;i<ch_vec.size();i++)
    {
        if(i<8)
        {
            ch_vec[i].move(0,posY);
            posY-=22;
        }
        else
        {
            ch_vec[i].move(0,posY);
            posY+=22;
        }
    }
}
void set_character_dead(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation)
{
    set_character_frames(ch_vec, file_name, OriginX, OriginY, PosX, PosY, nr_of_animation);
    int posX=300;
    for(auto &b:ch_vec)
    {
        b.setPosition(posX,917);
        posX+=10;
    }

}
void move_to_positon(vector<character_Sprite> &ch_vec,float PosX, float PosY)
{
    for(auto &b:ch_vec)
    {
        b.setPosition(PosX,PosY);
     }
}
