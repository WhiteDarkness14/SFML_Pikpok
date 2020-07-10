#pragma once
#include "general.h"
class map_Sprite: public general
{
public:
    map_Sprite(string title, int posX, int posY, int originX, int originY);

private:

};

void set_clouds(vector <map_Sprite> &map_cloud);
void move_background(const float speed, vector<map_Sprite> &map_cloud, map_Sprite &map_ground);
void draw_sky(RenderWindow &window, const map_Sprite map_sky, const vector<map_Sprite>map_cloud);


