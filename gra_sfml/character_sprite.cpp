#include "character_sprite.h"
//#include "collision.h"

character_Sprite::character_Sprite(string title, float OriginX, float OriginY, float PosX, float PosY)
{
    string file_name="picture/"+title+".png";
    Texture text;
    Collision::CreateTextureAndBitmask(text,file_name);
    shared_ptr<Texture> object_ptr = make_shared<Texture>(text);
    LoadTexture(object_ptr);
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
    ch_vec[0].move(0,-100);
    ch_vec[1].move(0,-200);
    ch_vec[2].move(0,-100);
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
void set_character(vector <vector<vector <character_Sprite>>> &character_animation)
{
    vector <character_Sprite> boy_idle;
    set_character_frames(boy_idle,"boy/b_idle/Idle ",307,500,300,924,15);
    vector <character_Sprite> boy_walk;
    set_character_frames(boy_walk,"boy/b_walk/Walk ",307,500,300,924,15);
    vector <character_Sprite> boy_run;
    set_character_frames(boy_run,"boy/b_run/Run ",307,500,300,924,15);
    vector <character_Sprite> boy_jump;
    set_character_jump(boy_jump,"boy/b_jump/Jump ",307,500,300,924,3);
    vector <character_Sprite> boy_dead;
    set_character_dead(boy_dead,"boy/b_dead/Dead ",307,500,300,924,15);

    vector <character_Sprite> girl_idle;
    set_character_frames(girl_idle,"girl/g_idle/Idle ",208,445,300,921,16);
    vector <character_Sprite> girl_walk;
    set_character_frames(girl_walk,"girl/g_walk/Walk ",208,445,300,921,20);
    vector <character_Sprite> girl_run;
    set_character_frames(girl_run,"girl/g_run/Run ",208,445,300,921,20);
    vector <character_Sprite> girl_jump;
    set_character_jump(girl_jump,"girl/g_jump/Jump ",208,445,300,921,3);
    vector <character_Sprite> girl_dead;
    set_character_dead(girl_dead,"girl/g_dead/Dead ",208,445,300,921,30);

    vector <vector <character_Sprite>> character_boy;
    vector <vector <character_Sprite>> character_girl;

    character_boy.emplace_back(boy_idle);
    character_boy.emplace_back(boy_walk);
    character_boy.emplace_back(boy_run);
    character_boy.emplace_back(boy_jump);
    character_boy.emplace_back(boy_dead);

    character_girl.emplace_back(girl_idle);
    character_girl.emplace_back(girl_walk);
    character_girl.emplace_back(girl_run);
    character_girl.emplace_back(girl_jump);
    character_girl.emplace_back(girl_dead);

    character_animation.emplace_back(character_boy);
    character_animation.emplace_back(character_girl);

}
