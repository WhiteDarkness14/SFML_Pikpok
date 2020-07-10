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
void draw_text(RenderWindow &window, string which_animation, Text info_text, Text final_text, Text final_score, Text score_text)
{
    if(which_animation=="idle")
    {
        window.draw(info_text);
    }
    if(which_animation=="dead")
    {
        window.draw(final_text);
        window.draw(final_score);
    }
    else
    {
        window.draw(score_text);
    }
}
