#include "character_sprite.h"

character_Sprite::character_Sprite()
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
    vector<vector<character_Sprite>> boy;
    vector<vector<character_Sprite>> girl;
    boy.emplace_back(boy_idle);
    boy.emplace_back(boy_walk);
    boy.emplace_back(boy_run);
    boy.emplace_back(boy_jump);
    boy.emplace_back(boy_dead);
    girl.emplace_back(girl_idle);
    girl.emplace_back(girl_walk);
    girl.emplace_back(girl_run);
    girl.emplace_back(girl_jump);
    girl.emplace_back(girl_dead);

    character_animation.emplace_back(boy);
    character_animation.emplace_back(girl);
}
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
void character_Sprite::change_character()
{
    if(which_character==0)
    {
        which_character=1;
        nr_frame_idle=16;
        nr_frame_move=20;
        nr_frame_dead=30;
    }
    else
    {
        which_character=0;
        nr_frame_idle=15;
        nr_frame_move=15;
        nr_frame_dead=15;
    }
    animation=0;
    frame=0;
}
void character_Sprite::start()
{
    animation=1;
    animation_move=1;

}
void character_Sprite::jump(float &actual_clock, float &jump_clock, const sf::Time &elapsed, Sound &jump_sound, string &which_animation)
{
    if(actual_clock>=refresh_animation&& animation==3) // jump animation
    {
        if(first_jump)
        {
            actual_clock=0;
            first_jump=false;
            jump_sound.play();
        }
        else if(frame==2)
        {
            first_jump=true;
            actual_clock=0;
            which_animation="move";
        }
        else if(set_time_jump(jump_clock)>jump_clock)
        {
            jump_clock+=elapsed.asMilliseconds();
            frame=1;
            actual_clock=0;
        }
        else
        {
            frame=2;
            jump_clock=0;
            actual_clock=0;
        }
    }
}
void character_Sprite::dead(float &actual_clock, float &break_speed, float &speed, Sound &dead_sound, bool &run)
{
    if(actual_clock>0.09)
    {
        if(frame==0)
        {
            break_speed=speed/(nr_frame_dead-1);
            dead_sound.play();
        }
        if(frame<nr_frame_dead-1)
        {
            actual_clock=0;
            frame++;
            speed-=break_speed;
            run=false;
        }
    }
}
void character_Sprite::change_animation(float &speed, float &actual_clock, float &jump_clock, const sf::Time &elapsed, Sound &jump_sound, Sound &dead_sound, string &which_animation, float &break_speed, bool &run)
{
    if(which_animation!=last_animation)
    {
        frame=0;
        last_animation=which_animation;
    }
    if(speed>17&&animation_move==1)  // change walk to run
    {
        animation_move=2;
        refresh_animation=32;
    }
    if(actual_clock>=refresh_animation&&which_animation=="idle") // idle animation
    {
        animation=0;
        actual_clock=0;
        frame++;
        if(frame==nr_frame_idle) frame=0;
    }
    else if(actual_clock>=refresh_animation&&which_animation=="move") // walk/run animation
    {
        animation=animation_move;
        actual_clock=0;
        frame++;
        if(frame==nr_frame_move) frame=0;
    }
    else if(which_animation=="jump")
    {
        animation=3;
        jump(actual_clock, jump_clock, elapsed, jump_sound, which_animation);
    }
    else if(which_animation=="dead")
    {
        animation=4;
        dead(actual_clock, break_speed, speed, dead_sound, run);
    }
}
void character_Sprite::dodge(const float scale)
{
    character_animation[which_character][animation][frame].setScale(scale,scale);
}
Sprite character_Sprite::one_frame()
{
    return character_animation[which_character][animation][frame];
}

