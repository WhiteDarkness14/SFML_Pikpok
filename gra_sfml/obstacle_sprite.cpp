#include "obstacle_sprite.h"
#include "collision.h"
#include <iostream>
obstacle_Sprite::obstacle_Sprite(){}
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
void set_flame(vector<obstacle_Sprite>&flame,string str)
{
    for(int i=0;i<3;i++)
    {
        flame.emplace_back(str,1);
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

void generate_flame(vector<obstacle_Sprite>&flame_dino,vector<obstacle_Sprite>&flame_character,bool attack)
{
    for(int i=0;i<flame_dino.size();i++)
    {
        if(flame_dino[i].getPosition().x<-100)
        {
            flame_dino[i].to_move=false;
        }

    }
    for(int i=0;i<flame_dino.size();i++)
    {
        if(flame_dino[i].to_move==false)
        {
            flame_dino[i].to_move=true;
            cout<<"LECI"<<endl;
            flame_dino[i].setPosition(1600,400);
            break;
        }
    }
}
void obstacle_Sprite::LoadTexture(std::shared_ptr<sf::Texture> text)
{
    texture = text;
    setTexture(*texture);
}
void make_flame(obstacle_Sprite & flame, string name)
{
    Texture text;
    Collision::CreateTextureAndBitmask(text,name);
    shared_ptr<Texture> flame_ptr = make_shared<Texture>(text);
    flame.LoadTexture(flame_ptr);
    flame.setPosition(1000,700);
}

