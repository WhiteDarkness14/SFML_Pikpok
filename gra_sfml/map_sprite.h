#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace std;
using namespace sf;

void window_set(RenderWindow &window);

class map_Sprite: public Sprite
{
private:
    vector<Texture>texture;
public:
    map_Sprite(string title, int posX, int posY, int originX, int originY);
};

void set_clouds(vector <map_Sprite> &map_cloud);

#endif // GAME_H
