#include "obstacle_sprite.h"
obstacle_Sprite::obstacle_Sprite(){}
obstacle_Sprite::obstacle_Sprite(string name, const float scale)
{
    string file_name="picture/"+name+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    shared_ptr<Texture> object_ptr = make_shared<Texture>(text);
    LoadTexture(object_ptr);
    setScale(scale,scale);
}

void set_obstacle(vector<obstacle_Sprite> &mushrooms,vector<vector<obstacle_Sprite>> &birds)
{
    for(int i=0;i<3;i++)
    {
        mushrooms.emplace_back("mushroom",0.25);
        vector<obstacle_Sprite> bird;
        string file_name="bird/brid";
        for(int i=1;i<=10;i++)
        {
            string f_name=file_name;
            f_name+=to_string(i);
            bird.emplace_back(f_name,0.5);
        }
        birds.emplace_back(bird);
    }
}
void set_flames(vector<obstacle_Sprite> &flame_dino, vector<obstacle_Sprite> &flame_character)
{
    for(int i=0;i<3;i++)
    {
        obstacle_Sprite flame;
        make_flame(flame,"picture/flame.png");
        obstacle_Sprite flame2;
        make_flame(flame2,"picture/flame_character.png");
        flame.setPosition(rand()%1920,rand()%1080);
        flame_dino.emplace_back(flame);
        flame_character.emplace_back(flame2);
    }
}
void generate_obstacle(vector<vector<obstacle_Sprite>>&birds, vector<obstacle_Sprite>&mushrooms,vector<float>&time_jump_distance)
{
    for(unsigned i=0;i<birds.size();i++)
    {
        if(birds[i][0].getPosition().x<0)
        {
            birds[i][0].to_move=false;
        }
        if(mushrooms[i].getPosition().x<0)
        {
            mushrooms[i].to_move=false;
            time_jump_distance[i]=0;
        }
    }

    int randomize=rand()%10+1;
    if(randomize>7)
    {
        for(unsigned i=0;i<birds.size();i++)
        {
            if(birds[i][0].to_move==false)
            {
                birds[i][0].to_move=true;
                for(unsigned j=0;j<birds[i].size();j++)
                {
                    birds[i][j].setPosition(2000,630);
                }
                break;
            }
        }
    }
    else
    {
        for(unsigned i=0;i<mushrooms.size();i++)
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

void generate_flame(vector<obstacle_Sprite>&flame_dino)
{
    for(unsigned i=0;i<flame_dino.size();i++)
    {
        if(flame_dino[i].getPosition().x<-100)
        {
            flame_dino[i].to_move=false;
        }

    }
    for(unsigned i=0;i<flame_dino.size();i++)
    {
        if(flame_dino[i].to_move==false)
        {
            flame_dino[i].to_move=true;
            flame_dino[i].setPosition(1600,400);
            break;
        }
    }
}

void make_flame(obstacle_Sprite & flame, string name)
{
    Texture text;
    Collision::CreateTextureAndBitmask(text,name);
    shared_ptr<Texture> flame_ptr = make_shared<Texture>(text);
    flame.LoadTexture(flame_ptr);
    flame.setPosition(1000,700);
}

float set_time_jump(const float time_jump)
{
    //float t = 0.0;
    if(time_jump>300)
    {
        return (time_jump-40);
    }
    else if(time_jump>250)
    {
        return (time_jump-30);
    }
    else if(time_jump>200)
    {
        return (time_jump-20);
    }
    else if(time_jump>150)
    {
        return time_jump;
    }
    else if(time_jump>100)
    {
        return (time_jump+30);
    }
    else
    {
        return (time_jump+50);
    }
}
