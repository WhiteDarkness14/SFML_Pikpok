#ifndef OBSTACLE_SPRITE_H
#define OBSTACLE_SPRITE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "collision.h"
#include "character_sprite.h"
#include <memory>
using namespace std;
using namespace sf;


class obstacle_Sprite: public Sprite
{
private:
    vector<Texture>texture_obstacle;
    shared_ptr<sf::Texture> texture;

public:
    bool to_move=false;
    obstacle_Sprite();
    obstacle_Sprite(string title, float scale);
    void LoadTexture (shared_ptr<sf::Texture> text);

};
void set_mushrooms(vector<obstacle_Sprite> &mushrooms);
void set_bird(vector<obstacle_Sprite> &bird);
void generate_obstacle(vector<vector<obstacle_Sprite> > &birds, vector<obstacle_Sprite> &mushrooms);
void set_flame(vector<obstacle_Sprite>&flame,string str);
void generate_flame(vector<obstacle_Sprite> &flame_dino, vector<obstacle_Sprite> &flame_character, bool attack);
void make_flame(obstacle_Sprite & flame, string name);
#endif // OBSTACLE_SPRITE_H
