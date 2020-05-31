#ifndef BOY_SPRITE_H
#define BOY_SPRITE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace std;
using namespace sf;



class boy_Sprite: public Sprite
{
private:
    vector<Texture>texture;

public:
    boy_Sprite(string title, float OriginX, float OriginY);

};
void set_boy_frames(vector<boy_Sprite> &boy_vec, string file_name, float OriginX, float OriginY);
void set_boy_dead(vector<boy_Sprite> &boy_vec, string file_name, float OriginX, float OriginY);
void set_boy_jump(vector<boy_Sprite> &boy_vec, string file_name, float OriginX, float OriginY);
#endif // BOY_SPRITE_H
