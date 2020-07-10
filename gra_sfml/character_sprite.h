#pragma once
#include "headers.h"

class character_Sprite: public general
{

public:
    character_Sprite(string title, float OriginX, float OriginY, float PosX, float PosY);
    character_Sprite();
    vector<vector<vector<character_Sprite>>> character_animation;
    bool alive=true;

    // ------ metody ------ //
    void change_character();
    void start();
    void change_animation(float &speed, float &actual_clock, float &jump_clock, const sf::Time &elapsed, Sound &jump_sound, Sound &dead_sound, string &which_animation, float &break_speed, bool &run);
    void jump(float &actual_clock, float &jump_clock, const sf::Time &elapsed, Sound &jump_sound, string &which_animation);
    void dead(float &actual_clock, float &break_speed, float &speed, Sound &dead_sound, bool &run);
    void dodge(const float scale);
    Sprite one_frame();
private:
    int animation=0;
    string last_animation;
    int animation_move=1;
    int actual_animation=0;
    int frame=0;
    int which_character=0;
    int nr_frame_idle=15;
    int nr_frame_move=15;
    int nr_frame_dead=15;
    float refresh_animation=40;
    bool first_jump=true;


};
void set_character_frames(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character_dead(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character_jump(vector<character_Sprite> &ch_vec, string file_name, float OriginX, float OriginY, float PosX, float PosY, float nr_of_animation);
void set_character(vector<vector<vector<character_Sprite>>> &character_animation);


