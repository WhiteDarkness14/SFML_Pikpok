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
    window.create(sf::VideoMode(1920, 1080), "Run Pikpok!");//,Style::Fullscreen);
    window.setActive(true);
    window.setKeyRepeatEnabled(true);
  //  window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    srand(time(NULL));
}



