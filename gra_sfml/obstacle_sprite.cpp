#include "obstacle_sprite.h"
#include "collision.h"

obstacle_Sprite::obstacle_Sprite(string title, float scale)
{
    string file_name="picture/"+title+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    texture_obstacle.emplace_back(text);
    setTexture(texture_obstacle[0]);
    setScale(scale,scale);
}
void set_mushrooms(vector<obstacle_Sprite>&mushrooms)
{
    for(int i=0;i<3;i++)
    {
        mushrooms.emplace_back("mushroom",0.25);
    }
}
void set_bird(vector<obstacle_Sprite>&bird)
{
    string file_name="bird/brid";
    for(int i=1;i<=10;i++)
    {
        string f_name=file_name;
        f_name+=to_string(i);
        bird.emplace_back(f_name,0.5);
    }
}
void generate_obstacle(vector<vector<obstacle_Sprite>>&birds, vector<obstacle_Sprite>&mushrooms)
{
    for(int i=0;i<birds.size();i++)
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
    if(randomize>5)
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

