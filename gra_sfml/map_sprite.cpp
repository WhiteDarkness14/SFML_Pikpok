#include "map_sprite.h"

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
    for(int i=0;i<3;i++)
    {
        float size=rand()%40+60;
        size/=100;
        map_cloud.emplace_back("cloud",550*(i+1)+rand()%200-100,200+rand()%300-150,210,0);
    }
}
void move_background(const float speed, vector<map_Sprite> &map_cloud, map_Sprite &map_ground)
{
    for(auto &cloud:map_cloud)
    {
        cloud.move(-0.35*speed,0);
        if(cloud.getPosition().x<-100)
        {
            cloud.setPosition(2200,200+rand()%300-150);
            float scale=rand()%40+60;
            scale/=100;
            cloud.setScale(scale,scale);
        }
    }

    map_ground.move(-speed,0);
    if(map_ground.getPosition().x<0)
    {
        map_ground.setPosition(2045,900);
    }
}
void draw_sky(RenderWindow &window, const map_Sprite map_sky, const vector<map_Sprite>map_cloud)
{
    window.draw(map_sky);
    for( auto &cloud:map_cloud)
    {
        window.draw(cloud);
    }
}


