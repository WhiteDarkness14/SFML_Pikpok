#pragma once
#include "headers.h"



class my_text :public Text
{
private:
    Font font;
public:
    my_text(string name_font,int size,int posX,int posY);
};
void draw_text(RenderWindow &window, const string which_animation, const Text info_text, const Text final_text, const Text final_score, const Text score_text);

