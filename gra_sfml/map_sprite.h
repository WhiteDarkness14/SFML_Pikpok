#pragma once
#include "general.h"

class map_Sprite: public general
{
public:
    map_Sprite(string title, int posX, int posY, int originX, int originY);
};

void set_clouds(vector <map_Sprite> &map_cloud);

