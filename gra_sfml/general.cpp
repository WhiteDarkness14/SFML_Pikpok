#include "general.h"

general::general()
{

}

void general::LoadTexture(shared_ptr<sf::Texture> text)
{
    texture = text;
    setTexture(*texture);
}
void window_set(RenderWindow &window)
{
    window.create(sf::VideoMode(1920, 1080), "Run Pikpok!");
    window.setActive(true);
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(60);
    srand(time(NULL));
}
void counter(float &total_time, int &score, int &score_boss, const bool boss_MODE, const bool run)
{
    if(total_time>=100&&run)
    {
        total_time=0;
        score++;
        if(!boss_MODE)
        {
            score_boss++;
        }
    }
}



