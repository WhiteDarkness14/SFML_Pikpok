#ifndef MY_SOUND_H
#define MY_SOUND_H
#include "headers.h"

class my_sound: public Sound
{
public:
    my_sound();
    my_sound(string title);
private:
    SoundBuffer buffer;
};

#endif // MY_SOUND_H
