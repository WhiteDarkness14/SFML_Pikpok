#include "map_sprite.h"
#include "collision.h"

void window_set(RenderWindow &window)
{
    window.create(sf::VideoMode(1920, 1080), "Run Pikpok!");//,Style::Fullscreen);
    window.setActive(true);
    window.setKeyRepeatEnabled(true);
    window.setVerticalSyncEnabled(true);
    srand(time(NULL));
}

map_Sprite::map_Sprite(string title,int posX, int posY,int originX, int originY)
{
    string file_name="picture/"+title+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    shared_ptr<Texture> object_ptr = make_shared<Texture>(text);
    LoadTexture(object_ptr);
    setPosition(posX,posY);
    setOrigin(originX,originY);
}


void set_clouds(vector <map_Sprite> &map_cloud)
{
    for(int i=0;i<3;i++) //cloud 320x200
    {
        float size=rand()%40+60;
        size/=100;
        map_cloud.emplace_back("cloud",550*(i+1)+rand()%200-100,200+rand()%300-150,210,0);
    }
}


