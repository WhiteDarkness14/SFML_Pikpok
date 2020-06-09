#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include "collision.h"
using namespace std;
using namespace sf;
class general :public Sprite
{
protected:
    shared_ptr<sf::Texture> texture;
public:
    general();
    void LoadTexture (shared_ptr<sf::Texture> text);
};

void window_set(RenderWindow &window);
