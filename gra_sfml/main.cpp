#include "map_sprite.h"
#include "boy_sprite.h"
#include "obstacle_sprite.h"
#include "collision.h"
#include <iostream>
int main()
{
    //    tworzenie okna
    RenderWindow window;
    window_set(window);

    //    tworzenie tła
    map_Sprite map_ground("grass",2045,900,2100,0);
    map_Sprite map_sky("sky",0,0,0,0);
    vector <map_Sprite> map_cloud;
    set_clouds(map_cloud);

    //    tworzenie przeszkód
    vector <obstacle_Sprite> mushrooms;
    vector<vector<obstacle_Sprite>> birds;
    set_mushrooms(mushrooms);
    vector<obstacle_Sprite> bird1;
    vector<obstacle_Sprite> bird2;
    vector<obstacle_Sprite> bird3;
    set_bird(bird1);
    set_bird(bird2);
    set_bird(bird3);
    birds.emplace_back(bird1);
    birds.emplace_back(bird2);
    birds.emplace_back(bird3);

    //     tworzenie postaci
    vector <boy_Sprite> boy_idle;
    set_boy_frames(boy_idle,"b_idle/idle",150,480);
    vector <boy_Sprite> boy_walk;
    set_boy_frames(boy_walk,"b_walk/P_walk",145,490);
    vector <boy_Sprite> boy_run;
    set_boy_frames(boy_run,"b_run/run",145,490);
    vector <boy_Sprite> boy_jump;
    set_boy_jump(boy_jump,"b_jump/jump",182,500);
    vector <boy_Sprite> boy_dead;
    set_boy_dead(boy_dead,"b_dead/dead",270,440);
    vector <vector <boy_Sprite>> boy_animation;
    boy_animation.emplace_back(boy_idle);
    boy_animation.emplace_back(boy_walk);
    boy_animation.emplace_back(boy_run);
    boy_animation.emplace_back(boy_jump);
    boy_animation.emplace_back(boy_dead);

    bool run=false; // czy gra działa
    int animation=0; // która animacja idle/walk/run/jump/dead<
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
                    animation_move=1;
                    actual_clock=0;
                    speed_clock=0;
                    bird_clock=0;
                    obstacle_clock=0;
                    for(int i=0;i<birds.size();i++)
                    {
                        birds[i][0].to_move=false;

                        mushrooms[i].to_move=false;
                    }
                }
            }
            else if(scale==0.5&&event.type ==Event::KeyPressed && event.key.code == Keyboard::Up && run)
            {
                animation=3;
            }
            else if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Down && run)
            {
                scale=0.25;
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down && run)
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

        boy_animation[animation][frame].setScale(scale,scale); // dodge bird

        map_ground.move(-speed,0); // move ground
        if(map_ground.getPosition().x<0) // looped ground
        {
            map_ground.setPosition(2045,900);
        }

        if(obstacle_clock>1.2&&run)
        {
            obstacle_clock=0;
            generate_obstacle(birds,mushrooms);
        }


        for(int i=0;i<birds.size();i++)
        {
            if(birds[i][0].to_move)
            {
                for(int j=0;j<birds[i].size();j++)
                {
                    birds[i][j].move(-speed,0);
                }
                if(Collision::PixelPerfectTest(boy_animation[animation][frame],birds[i][frame_bird]))
                {
                    animation=4;
                }
            }
            if(mushrooms[i].to_move)
            {
                mushrooms[i].move(-speed,0);
                if(Collision::PixelPerfectTest(boy_animation[animation][frame],mushrooms[i]))
                {
                    animation=4;
                }
            }

        }


        //DRAW

        window.clear();
        window.draw(map_sky);
        for( auto &cloud:map_cloud)
        {
            window.draw(cloud);
        }
        window.draw(boy_animation[animation][frame]);
        for(int i=0;i<birds.size();i++)
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
        window.draw(map_ground);

        window.display();

    }

    return 0;
}
