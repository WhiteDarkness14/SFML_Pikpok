#include "boy_sprite.h"
#include "collision.h"

boy_Sprite::boy_Sprite(string title, float OriginX, float OriginY)
{
    string file_name="picture/"+title+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    texture.emplace_back(text);
    setTexture(texture[0]);
    setPosition(300,923);
    setOrigin(OriginX,OriginY);
    setScale(0.6,0.6);
}

void set_boy_frames(vector<boy_Sprite> &boy_vec, string file_name, float OriginX, float OriginY)
{
    for(int i=1;i<=15;i++)
    {
        string f_name=file_name;
        f_name+=to_string(i);
        boy_vec.emplace_back(f_name,OriginX,OriginY);
    }
}

void set_boy_jump(vector<boy_Sprite> &boy_vec, string file_name, float OriginX, float OriginY)
{
    set_boy_frames(boy_vec, file_name, OriginX, OriginY);
    int PosY=0;
    for(int i=0;i<boy_vec.size();i++)
    {
        if(i<8)
        {
            boy_vec[i].move(0,PosY);
            PosY-=22;
        }
        else
        {
            boy_vec[i].move(0,PosY);
            PosY+=22;
        }
    }
}
void set_boy_dead(vector<boy_Sprite> &boy_vec, string file_name, float OriginX, float OriginY)
{
    set_boy_frames(boy_vec, file_name, OriginX, OriginY);
    int PosX=300;
    int PosY=923;
    for(auto &b:boy_vec)
    {
        b.setPosition(PosX,PosY+7);
        PosX+=10;
    }

}
