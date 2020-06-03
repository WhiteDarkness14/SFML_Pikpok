#ifndef MY_TEXT_H
#define MY_TEXT_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;


class my_text :public Text
{
private:
    Font font;
public:
    my_text(string name_font,int size,int posX,int posY);
};

#endif // MY_TEXT_H
