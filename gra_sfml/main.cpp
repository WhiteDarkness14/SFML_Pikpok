#include "other.h"
#include "map.h"
#include "collision.h"
#include <iostream>
int main()
{

    RenderWindow window;
    window_set(window);

    map_Sprite map_ground("grass",2045,900,2100,0,1); // nazwa pliku;posX;posY;originX;originY;scale
    map_Sprite map_sky("sky",0,0,0,0,1);
    vector <map_Sprite> map_cloud;
    set_clouds(map_cloud);
    vector <map_Sprite> mushrooms;
    mushrooms.emplace_back("mushroom",1300,835,0,0,0.25);
    mushrooms.emplace_back("mushroom",1300,835,0,0,0.25);
    vector <map_Sprite> bird1;
    set_frames(bird1,"bird/brid",500,630,0,0,10);
    vector <map_Sprite> bird2;
    set_frames(bird2,"bird/brid",500,630,0,0,10);

    vector<vector<map_Sprite>> birds;
    birds.emplace_back(bird1);
    birds.emplace_back(bird2);




    int PosX=300;
    int PosY=923;
    vector <map_Sprite> boy_walk;
    set_frames(boy_walk,"b_walk/P_walk",PosX,PosY,145,490,15);
    vector <map_Sprite> boy_run;
    set_frames(boy_run,"b_run/run",PosX,PosY,145,490,15);
    vector <map_Sprite> boy_jump;
    set_frames_jump(boy_jump,"b_jump/jump",PosX,PosY,182,500,15);
    vector <map_Sprite> boy_idle;
    set_frames(boy_idle,"b_idle/idle",PosX,PosY,150,480,15);
    vector <map_Sprite> boy_dead;
    set_frames(boy_dead,"b_dead/dead",PosX,PosY,270,440,15);
    for(auto &b:boy_dead)
    {
        b.setPosition(PosX,PosY+7);
        PosX+=10;
    }
    vector <vector <map_Sprite>> boy_animation;
    boy_animation.emplace_back(boy_idle);
    boy_animation.emplace_back(boy_walk);
    boy_animation.emplace_back(boy_run);
    boy_animation.emplace_back(boy_jump);
    boy_animation.emplace_back(boy_dead);

    bool run=false; // czy gra działa
    int animation=0; // która animacja idle/walk/run/jump/dead
    int animation_move=1; //aktualna animacja biegania
    int actual_animation=0; // aktualna animacja
    Clock clock;
    float actual_clock=0, speed_clock=1, bird_clock=0, obstacle_clock=0; // liczniki czasów
    float speed=0; // predkosc gry
    float frame=0; // klatka animacji Pikpoka
    float frame_bird=0; // klatka animacji Brida
    float break_speed; // hamowanie kiedy ginie
    float refresh_animation=40; // częstotliwość zmiany animacji
    bool to_dead=true;
    float scale=0.5; // unikanie latajacych obiektów




    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            else if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                if(run==false)
                {
                    speed=7;
                    animation=1;
                    run=true;
                }
            }
            else if(scale==0.5&&event.type ==Event::KeyPressed && event.key.code == Keyboard::Up)
            {
                if(run) animation=3;
            }
            else if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Down)
            {
                scale=0.25;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down)
            {
                scale=0.5;
            }


        }

        //TIME
        const sf::Time elapsed = clock.restart();
        actual_clock+=elapsed.asMilliseconds();
        speed_clock+=elapsed.asSeconds();
        bird_clock+=elapsed.asSeconds();
        obstacle_clock+=elapsed.asSeconds();




        //LOGIC
        if(speed_clock>0.5&&animation!=4&&run)  // speed+
        {
            speed_clock=0;
            speed+=0.5;
        }
        if(bird_clock>0.05)
        {
            bird_clock=0;
            frame_bird++;
            if(frame_bird==10)
            {
                frame_bird=0;
            }
        }

        if(speed>15&&animation_move==1)  // change walk to run
        {
            animation_move=2;
            animation=2;
            refresh_animation=32;
        }

        if(actual_animation!=animation) // change animation
        {
            frame=0;
            actual_animation=animation;
        }

        if(actual_clock>=refresh_animation&&animation!=4&&animation!=3) // walk/run animation
        {
            actual_clock=0;
            frame++;
            if(frame==15) frame=0;
        }
        else if(actual_clock>=refresh_animation&& animation==3) // jump animation
        {
            actual_clock=0;
            frame++;
            if(frame==15)
            {
                frame=0;
                animation=animation_move;
            }
        }
        else if(animation==4) //dead animation
        {
            if(actual_clock>0.04)
            {
                if(frame==0)
                {
                    break_speed=speed/14;
                }
                if(frame<14)
                {
                    actual_clock=0;
                    frame++;
                    speed-=break_speed;
                    run=false;
                }
            }
        }



        for(auto &cloud:map_cloud) // new clouds and move
        {
            cloud.move(-0.35*speed,0);
            if(cloud.getPosition().x<-100)
            {
                cloud.setPosition(2200,200+rand()%300-150);
                float scale=rand()%40+60;
                scale/=100;
                cloud.setScale(scale,scale);
            }
        }
        //        for(auto &bird:birds) // bird move
        //        {
        //            bird.move(-speed,0);
        //            if(bird.getPosition().x<-100)
        //            {
        //                bird.setPosition(2200,630);
        //            }
        //        }



        map_ground.move(-speed,0); // move ground
        if(map_ground.getPosition().x<0) // looped ground
        {
            map_ground.setPosition(2045,900);
        }

        if(obstacle_clock>1&&run)
        {
            obstacle_clock=0;
            generate_obstacle(birds,mushrooms);
        }
        for( auto &cloud:map_cloud)
        {
            window.draw(cloud);
        }


        for(int i=0;i<2;i++)
        {
            if(birds[i][0].to_move)
            {
                for(auto &bird:birds[i])
                {
                    bird.move(-speed,0);
                }
            }
            if(mushrooms[i].to_move)
            {
                mushrooms[i].move(-speed,0);
            }
        }

        //        mushroom.move(-speed,0); // move mushroms
        //        if(mushroom.getPosition().x<-100) // looped mushroms
        //        {
        //            mushroom.setPosition(2200,835);
        //        }

        boy_animation[animation][frame].setScale(scale,scale); // dodge bird


        //        if(to_dead&&(Collision::PixelPerfectTest(boy_animation[animation][frame],mushroom)||Collision::PixelPerfectTest(boy_animation[animation][frame],birds[frame_bird]))) // collision
        //        {
        //            animation=4;
        //        }


        //DRAW

        window.clear();
        window.draw(map_sky);
        window.draw(boy_animation[animation][frame]);
        for(int i=0;i<2;i++)
        {
            if(birds[i][0].to_move)
            {
                window.draw(birds[i][frame_bird]);
            }
            if(mushrooms[i].to_move)
            {
                window.draw(mushrooms[i]);
            }
        }

        //        window.draw(birds[frame_bird]);
        //        window.draw(mushroom);
        window.draw(map_ground);

        window.display();

    }

    return 0;
}
