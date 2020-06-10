#include "map_sprite.h"
#include "character_sprite.h"
#include "obstacle_sprite.h"
#include "my_text.h"
#include "collision.h"
#include "boss_sprite.h"
#include "general.h"
#include <iostream>
#include <memory>
#include <cstdlib>
int main()
{
    // Tworzenie okna
    RenderWindow window;
    window_set(window);

//    window.setFramerateLimit(3);

    // Tworzenie tła
    map_Sprite map_ground("grass",2045,900,2100,0);
    map_Sprite map_sky("sky",0,0,0,0);
    vector <map_Sprite> map_cloud;
    set_clouds(map_cloud);

    // Tworzenie przeszkód
    vector <obstacle_Sprite> mushrooms;
    vector<vector<obstacle_Sprite>> birds;
    set_obstacle(mushrooms,birds);

    // Tworzenie postaci
    vector<vector<vector<character_Sprite>>> character_animation;
    set_character(character_animation);

    // Tworzenie Bossa
    vector<vector<boss_Sprite>> boss;
    set_boss(boss);

    // Tworzenie pocisków
    vector<obstacle_Sprite>flame_dino;
    vector<obstacle_Sprite> flame_character;
    set_flames(flame_dino,flame_character);

    srand(time(NULL));

    my_text score_text("Pacifico",100,1750,50);

    bool run=false; // czy gra działa
    int animation=0; // która animacja idle/walk/run/jump/dead<
    int animation_move=1; //aktualna animacja biegania
    int actual_animation=0; // aktualna animacja
    Clock clock;
    float actual_clock=0, speed_clock=1, bird_clock=0, obstacle_clock=0, total_time=0, jump_clock=0; // liczniki czasów
    float speed=0; // predkosc gry
    float frame=0; // klatka animacji Pikpoka
    float frame_bird=0; // klatka animacji Brida
    float break_speed; // hamowanie kiedy ginie
    float refresh_animation=40; // częstotliwość zmiany animacji
    float scale=0.5; // unikanie latajacych obiektów
    int score=0;
    int score_boss=0;
    float o_c_time=1;
    int which_character=0;
    int  nr_frame_idle=15;
    int nr_frame_move=15;
    int nr_frame_dead=15;
    bool boss_MODE=false;
    bool attack=false;
    bool first_jump=true;
    float boss_animation=1;
    float frame_boss=0;
    float boss_life=4;
    vector <float> time_jump_distance(3,0);
    float time_jump=300;

    while (window.isOpen())
    {
        sf::Event event;
        attack=false;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Tab && !run)
            {
                if(which_character==0)
                {
                    which_character=1;
                    nr_frame_idle=16;
                    nr_frame_move=20;
                    nr_frame_dead=30;
                }
                else
                {
                    which_character=0;
                    nr_frame_idle=15;
                    nr_frame_move=15;
                    nr_frame_dead=15;
                }
                animation=0;
                frame=0;
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)&& !run)
            {
                time_jump=300;
                boss_MODE=false;
                score_boss=0;
                speed=7;
                animation=1;
                run=true;
                animation_move=1;
                actual_clock=0;
                speed_clock=0;
                score=0;
                bird_clock=0;
                obstacle_clock=0;
                for(unsigned i=0;i<birds.size();i++)
                {
                    birds[i][0].to_move=false;
                    mushrooms[i].to_move=false;
                }
            }
            if(scale==0.5&&event.type ==Event::KeyPressed && event.key.code == Keyboard::Up && run)
            {
                animation=3;
            }
            if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Down && run)
            {
                scale=0.25;
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down && run)
            {
                scale=0.5;
            }
            if(event.type == Event::KeyReleased && event.key.code == Keyboard::A)
            {
                attack=true;
            }

        }

        //TIME
        const sf::Time elapsed = clock.restart();
        actual_clock+=elapsed.asMilliseconds();
        speed_clock+=elapsed.asSeconds();
        bird_clock+=elapsed.asSeconds();
        obstacle_clock+=elapsed.asSeconds();
        total_time+=elapsed.asMilliseconds();

        //LOGIC
        if(total_time>=100&&run) // counter
        {
            total_time=0;
            score++;
            if(!boss_MODE)
            {
                score_boss++;
            }
        }
        score_text.setString(to_string(score));
        if(speed_clock>0.5&&animation!=4&&run)  // speed+
        {
            speed_clock=0;
            speed+=0.5;
        }

        if(bird_clock>0.06) // bird animation and boss
        {
            bird_clock=0;
            frame_bird++;
            if(frame_bird==10)
            {
                frame_bird=0;
            }
            if(boss_animation==0) // boss idle
            {
                frame_boss++;
                if(frame_boss==10) frame_boss=0;
            }
            else if (boss_animation==1) // boss run
            {
                frame_boss++;
                if(frame_boss==8) frame_boss=0;
            }
            else if(boss_animation==2) // boss jump
            {
                frame_boss++;
                if(frame_boss==12)
                {
                    frame_boss=0;
                    //  boss_animation=1;
                }
            }
            else if(boss_animation==3) // boss dead
            {
                if(frame_boss<7)
                {
                    frame_boss++;
                }
            }
        }

        if(actual_animation!=animation) // change animation
        {
            frame=0;
            actual_animation=animation;
        }
        if(speed>15&&animation_move==1)  // change walk to run
        {
            animation_move=2;
            refresh_animation=32;
        }
        if(actual_clock>=refresh_animation&&animation==0) // idle animation
        {
            actual_clock=0;
            frame++;
            if(frame==nr_frame_idle) frame=0;
        }
        if(actual_clock>=refresh_animation&&(animation==1||animation==2)) // walk/run animation
        {
            actual_clock=0;
            frame++;
            if(frame==nr_frame_move) frame=0;
        }
        else if(actual_clock>=refresh_animation&& animation==3) // jump animation
        {
            if(first_jump)
            {
                actual_clock=0;
                first_jump=false;
            }
            else if(frame==2)
            {
                animation=animation_move;
                first_jump=true;
                actual_clock=0;
            }
            else if(set_time_jump(jump_clock)>jump_clock)
            {
                jump_clock+=elapsed.asMilliseconds();
                frame=1;
                actual_clock=0;
            }
            else
            {
                frame=2;
                jump_clock=0;
                actual_clock=0;
            }
        }
        else if(animation==4) //dead animation
        {
            if(actual_clock>0.09)
            {
                if(frame==0)
                {
                    break_speed=speed/(nr_frame_dead-1);
                }
                if(frame<nr_frame_dead-1)
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

        character_animation[which_character][animation][frame].setScale(scale,scale); // dodge

        map_ground.move(-speed,0); // move ground
        if(map_ground.getPosition().x<0) // looped ground
        {
            map_ground.setPosition(2045,900);
        }

        if(!boss_MODE) //generate obstacle
        {
            if(obstacle_clock>o_c_time&&run)
            {
                obstacle_clock=0;
                generate_obstacle(birds,mushrooms,time_jump_distance);
                o_c_time=rand()%10+9;
                o_c_time/=10;
            }

            if(animation!=0 && animation!=4)
            {
                for(unsigned i=0;i<birds.size();i++)
                {
                    if(birds[i][0].to_move)
                    {
                        for(unsigned j=0;j<birds[i].size();j++)
                        {
                            birds[i][j].move(-speed,0);
                        }
                        if(Collision::PixelPerfectTest(character_animation[which_character][animation][frame],birds[i][frame_bird]))
                        {
                            animation=4;
                        }
                    }
                    if(mushrooms[i].to_move)
                    {
                        mushrooms[i].move(-speed,0);
                        if(mushrooms[i].getPosition().x<650 && mushrooms[i].getPosition().x>=500)
                        {
                            time_jump_distance[i]+=elapsed.asMilliseconds();
                            //                            cout<<i<<"   "<<time_jump_distance[i]<<endl;
                        }
                        else if(mushrooms[i].getPosition().x<=500)
                        {
                            if(time_jump>time_jump_distance[i])
                            {
                                time_jump=time_jump_distance[i];
                                cout<<speed<<"  "<<time_jump<<endl;
                            }
                        }
                        if(Collision::PixelPerfectTest(character_animation[which_character][animation][frame],mushrooms[i]))
                        {
                            animation=4;
                        }
                    }
                }
            }
        }

        if(!(score_boss%1000) && score_boss>10) // boss fight
        {
            boss_MODE=true;
            if(obstacle_clock>o_c_time)
            {
                obstacle_clock=0;
                generate_flame(flame_dino);
                o_c_time=rand()%10+30;
                o_c_time/=10;
            }
            if(attack)
            {
                for(unsigned i=0;i<flame_character.size();i++)
                {
                    if(flame_character[i].getPosition().x>1920)
                    {
                        flame_character[i].to_move=false;
                    }
                    if(flame_character[i].to_move==false)
                    {
                        flame_character[i].to_move=true;
                        flame_character[i].setPosition(-100,600);
                        break;
                    }
                }
            }
            for(unsigned i=0;i<flame_dino.size();i++)
            {
                if(flame_dino[i].to_move)
                {
                    flame_dino[i].move(-speed,0);
                    if(Collision::PixelPerfectTest(character_animation[which_character][animation][frame],flame_dino[i]))
                    {
                        animation=4;
                        flame_character[i].setPosition(1920,600);
                    }
                }
                if(flame_character[i].to_move)
                {
                    flame_character[i].move(speed,0);
                    if(Collision::PixelPerfectTest(boss[boss_animation][frame_boss],flame_character[i]))
                    {
                        boss_life--;
                        flame_character[i].to_move=false;
                    }
                }
            }
            if(boss_life==0)
            {
                frame_boss=0;
                boss_life--;
                boss_animation=3; //dead
            }
            if(boss_animation==3 && frame_boss==7) //zjazd ze sceny bossa
            {
                boss[3][7].move(-speed,0);
                if(boss[3][7].getPosition().x<-500)
                {
                    boss[3][7].setPosition(1910,972);
                    boss_MODE=false;
                    boss_animation=1;
                    score_boss=0;
                    boss_life=4;
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
        window.draw(character_animation[which_character][animation][frame]);
        if(!boss_MODE)
        {
            for(unsigned i=0;i<birds.size();i++)
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
        }

        if(boss_MODE)
        {
            window.draw(boss[boss_animation][frame_boss]);
            for(unsigned i=0;i<flame_dino.size();i++)
            {
                if(flame_dino[i].to_move)
                {
                    window.draw(flame_dino[i]);
                }
                if(flame_character[i].to_move)
                {
                    window.draw(flame_character[i]);
                }

            }
        }
        window.draw(map_ground);
        window.draw(score_text);
        window.display();

    }


    return 0;
}
