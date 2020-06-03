#include "my_text.h"

my_text::my_text(string name_font, int size, int posX, int posY)
{
    string f_name="font/"+name_font+".ttf";
    font.loadFromFile(f_name);
    setFont(font);
    setCharacterSize(size);
    setPosition(posX,posY);
    setFillColor(Color::Black);
}
