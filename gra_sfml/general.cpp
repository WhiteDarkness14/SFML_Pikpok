#include "general.h"

general::general()
{

}

void general::LoadTexture(shared_ptr<sf::Texture> text)
{
    texture = text;
    setTexture(*texture);
}
