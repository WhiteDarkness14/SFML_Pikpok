﻿#include "map_sprite.h"
#include "character_sprite.h"
#include "obstacle_sprite.h"
#include "my_text.h"
#include "collision.h"
#include "boss_sprite.h"
#include <iostream>
#include <memory>
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

    vector <character_Sprite> boy_idle;
    set_character_frames(boy_idle,"boy/b_idle/Idle ",307,500,300,924,15);
    vector <character_Sprite> boy_walk;
    set_character_frames(boy_walk,"boy/b_walk/Walk ",307,500,300,924,15);
    vector <character_Sprite> boy_run;
    set_character_frames(boy_run,"boy/b_run/Run ",307,500,300,924,15);
    vector <character_Sprite> boy_jump;
    set_character_jump(boy_jump,"boy/b_jump/Jump ",307,500,300,924,15);
    vector <character_Sprite> boy_dead;
    set_character_dead(boy_dead,"boy/b_dead/Dead ",307,500,300,924,15);

    vector <character_Sprite> girl_idle;
    set_character_frames(girl_idle,"girl/g_idle/Idle ",208,445,300,921,16);
    vector <character_Sprite> girl_walk;
    set_character_frames(girl_walk,"girl/g_walk/Walk ",208,445,300,921,20);
    vector <character_Sprite> girl_run;
    set_character_frames(girl_run,"girl/g_run/Run ",208,445,300,921,20);
    vector <character_Sprite> girl_jump;
    set_character_jump(girl_jump,"girl/g_jump/Jump ",208,445,300,921,15);
    vector <character_Sprite> girl_dead;
    set_character_dead(girl_dead,"girl/g_dead/Dead ",208,445,300,921,30);

    vector <vector <character_Sprite>> character_boy;
    vector <vector <character_Sprite>> character_girl;
    vector <vector<vector <character_Sprite>>> character_animation;

    character_boy.emplace_back(boy_idle);
    character_boy.emplace_back(boy_walk);
    character_boy.emplace_back(boy_run);
    character_boy.emplace_back(boy_jump);
    character_boy.emplace_back(boy_dead);

    character_girl.emplace_back(girl_idle);
    character_girl.emplace_back(girl_walk);
    character_girl.emplace_back(girl_run);
    character_girl.emplace_back(girl_jump);
    character_girl.emplace_back(girl_dead);

    character_animation.emplace_back(character_boy);
    character_animation.emplace_back(character_girl);

    character_boy.clear();
    character_girl.clear();

    // Tworzenie Bossa

    vector<vector<boss_Sprite>> boss;

    vector<boss_Sprite> boss_run;
    set_boss_frames(boss_run,"boss/run/Run ",8);
    vector<boss_Sprite> boss_jump;
    set_boss_jump(boss_jump,"boss/jump/Jump ",12);
    vector<boss_Sprite> boss_dead;
    set_boss_dead(boss_dead,"boss/dead/Dead ",8);
    vector<boss_Sprite> boss_idle;
    set_boss_frames(boss_idle,"boss/idle/Idle ",10);
    boss.emplace_back(boss_idle);
    boss.emplace_back(boss_run);
    boss.emplace_back(boss_jump);
    boss.emplace_back(boss_dead);

    // Tworzenie pocisków
    //    vector<obstacle_Sprite>flame_dino;
    //    set_flame(flame_dino,"flame");
    //    vector<obstacle_Sprite>flame_character;
    //    set_flame(flame_character,"flame_character");


    //    Texture flame_dino_text;
    //    Collision::CreateTextureAndBitmask(flame_dino_text,"picture/flame.png");
    //    shared_ptr<Texture> flame_dino_ptr = make_shared<Texture>(flame_dino_text);
    //    obstacle_Sprite flame;
    //    flame.LoadTexture(flame_dino_ptr);
    //    flame.setPosition(1000,800);

    vector<obstacle_Sprite>flame_dino;
    vector<obstacle_Sprite> flame_character;
    for(int i=0;i<3;i++)
    {
        obstacle_Sprite flame;
        make_flame(flame,"picture/flame.png");
        obstacle_Sprite flame2;
        make_flame(flame2,"picture/flame_character.png");
        flame.setPosition(rand()%1920,rand()%1080);
        flame_dino.emplace_back(flame);
        flame_character.emplace_back(flame2);
    }



    my_text score_text("Pacifico",100,1750,50);

    bool run=false; // czy gra działa
    int animation=0; // która animacja idle/walk/run/jump/dead<
    int animation_move=1; //aktualna animacja biegania
    int actual_animation=0; // aktualna animacja
    Clock clock;
    float actual_clock=0, speed_clock=1, bird_clock=0, obstacle_clock=0, total_time=0; // liczniki czasów
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
    bool control_attack=false;
    int  nr_frame_idle=15;
    int nr_frame_move=15;
    int nr_frame_jump=15;
    int nr_frame_dead=15;
    bool boss_MODE=false;
    bool attack=false;
    float boss_animation=1;
    float frame_boss=0;
    float boss_life=4;


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
                    nr_frame_jump=15;
                    nr_frame_dead=30;
                }
                else
                {
                    which_character=0;
                    nr_frame_idle=15;
                    nr_frame_move=15;
                    nr_frame_jump=15;
                    nr_frame_dead=15;
                }
                animation=0;
                frame=0;
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)&& !run)
            {
                boss_MODE=false;
                score_boss=0;
                speed=7;
                animation=1;
                run=true;
                animation_move=1;
                actual_clock=0;
                speed_clock=0;
                score=0;
                score_boss=90;
                bird_clock=0;
                obstacle_clock=0;
                for(int i=0;i<birds.size();i++)
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
            actual_clock=0;
            frame++;
            if(frame==nr_frame_jump)
            {
                frame=0;
                animation=animation_move;
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
                generate_obstacle(birds,mushrooms);
                o_c_time=rand()%10+9;
                o_c_time/=10;
            }

            if(animation!=0)
            {
                for(int i=0;i<birds.size();i++)
                {
                    if(birds[i][0].to_move)
                    {
                        for(int j=0;j<birds[i].size();j++)
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
                        if(Collision::PixelPerfectTest(character_animation[which_character][animation][frame],mushrooms[i]))
                        {
                            animation=4;
                        }
                    }
                }
            }
        }

        if(!(score_boss%100) && score_boss>10) // boss fight
        {
            boss_MODE=true;
            if(obstacle_clock>o_c_time)
            {
                obstacle_clock=0;
                generate_flame(flame_dino,flame_character,attack);
                o_c_time=rand()%10+30;
                o_c_time/=10;
            }
            if(attack)
            {
                for(int i=0;i<flame_character.size();i++)
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
            for(int i=0;i<flame_dino.size();i++)
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
                        cout<<"dostal "<<i<<endl;
                        flame_character[i].to_move=false;
                    }
                }
            }
            if(boss_life==0)
            {
                frame_boss=0;
                boss_life--;
                boss_animation=3; //dead
                cout<<"zginal"<<endl;
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
        }

        if(boss_MODE)
        {
            window.draw(boss[boss_animation][frame_boss]);
            for(int i=0;i<flame_dino.size();i++)
            {
                if(flame_dino[i].to_move)
                {
                    window.draw(flame_dino[i]);
                }
                if(flame_character[i].to_move)
                {
                    cout<<"PORUSZA SIE "<<i<<endl;
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
