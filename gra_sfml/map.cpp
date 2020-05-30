#include "map.h"
#include "collision.h"

void window_set(RenderWindow &window)
{
    window.create(sf::VideoMode(1920, 1080), "Run Pikpok!");//,Style::Fullscreen);
    window.setActive(true);
    window.setKeyRepeatEnabled(true);
    window.setVerticalSyncEnabled(true);
    srand(time(NULL));
}

map_Sprite::map_Sprite(string title,int posX, int posY,int originX,int originY,float scale)
{
    string file_name="picture/"+title+".png";
    Texture text;
    //text.loadFromFile(file_name);
    Collision::CreateTextureAndBitmask(text,file_name);
    texture.emplace_back(text);
    setTexture(texture[0]);
    setPosition(posX,posY);
    setOrigin(originX,originY);
    setScale(scale,scale);
}

void set_frames(vector<map_Sprite> &map_vec, string file_name,float PosX, float PosY, float OriginX, float OriginY, int size)
{
    for(int i=1;i<=size;i++)
    {
        string f_name=file_name;
        f_name+=to_string(i);
        map_vec.emplace_back(f_name,PosX,PosY,OriginX,OriginY,0.5);
    }
}
void set_frames_jump(vector<map_Sprite> &map_vec, string file_name, float PosX, float PosY, float OriginX, float OriginY, int size)
{
    for(int i=1;i<=size;i++)
    {
        string f_name=file_name;
        f_name+=to_string(i);
        map_vec.emplace_back(f_name,PosX,PosY,OriginX,OriginY,0.5);
        if(i<8)
        {
            PosY-=20;
        }
        else
        {
            PosY+=20;
        }
    }
}

void set_clouds(vector <map_Sprite> &map_cloud)
{
    for(int i=0;i<3;i++) //cloud 320x200
    {
        float size=rand()%40+60;
        size/=100;
        map_cloud.emplace_back("cloud",550*(i+1)+rand()%200-100,200+rand()%300-150,210,0,size);
    }
}
void generate_obstacle(vector<vector<map_Sprite>>&birds, vector<map_Sprite>&mushrooms)
{
    for(int i=0;i<2;i++)
    {
        if(birds[i][0].getPosition().x<0)
        {
            birds[i][0].to_move=false;
        }
        if(mushrooms[i].getPosition().x<0)
        {
            mushrooms[i].to_move=false;
        }
    }

    int randomize=rand()%10+1;
    if(randomize>6)
    {
        for(int i=0;i<birds.size();i++)
        {
            if(birds[i][0].to_move==false)
            {
                birds[i][0].to_move=true;
                for(int j=0;j<birds[i].size();j++)
                {
                    birds[i][j].setPosition(2000,630);
                }
                break;
            }
        }
    }
    else
    {
        for(int i=0;i<mushrooms.size();i++)
        {
            if(mushrooms[i].to_move==false)
            {
                mushrooms[i].to_move=true;
                mushrooms[i].setPosition(2000,835);
                break;
            }

        }
    }
}

