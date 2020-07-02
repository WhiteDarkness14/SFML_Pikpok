#include "my_sound.h"

my_sound::my_sound()
{

}
my_sound::my_sound (string title)
{
    buffer.loadFromFile(title);
    setBuffer(buffer);
}
