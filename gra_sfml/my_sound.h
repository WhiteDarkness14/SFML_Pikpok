#pragma once
#include "headers.h"

class my_sound: public Sound
{
public:
    my_sound();
    my_sound(string title);
private:
    SoundBuffer buffer;
};
