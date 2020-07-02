#pragma once
#include "headers.h"



class my_text :public Text
{
private:
    Font font;
public:
    my_text(string name_font,int size,int posX,int posY);
};

