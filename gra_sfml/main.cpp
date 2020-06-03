#include "map_sprite.h"
#include "character_sprite.h"
#include "obstacle_sprite.h"
#include "my_text.h"
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


    my_text score_text("Pacifico",100,1750,50);

    string character="0";
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
    float o_c_time=1;
    int which_character=1;

    int nr_frame_idle=16;
    int nr_frame_move=20;
    int nr_frame_jump=15;
    int nr_frame_dead=30;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Space))
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


        //        if(character=="none")
        //        {

        //            window.clear();
        //            window.draw(map_sky);
        //            for( auto &cloud:map_cloud)
        //            {
        //                window.draw(cloud);
        //            }
        //            window.draw(map_ground);
        //            window.display();

        //        }
        //        else
        //        {

        //TIME
        const sf::Time elapsed = clock.restart();
        actual_clock+=elapsed.asMilliseconds();
        speed_clock+=elapsed.asSeconds();
        bird_clock+=elapsed.asSeconds();
        obstacle_clock+=elapsed.asSeconds();
        total_time+=elapsed.asMilliseconds();




        //LOGIC
        if(total_time>=100&&run)
        {
            total_time=0;
            score++;
        }
        score_text.setString(to_string(score));
        if(speed_clock>0.5&&animation!=4&&run)  // speed+
        {
            speed_clock=0;
            speed+=0.5;
        }

        if(bird_clock>0.05) // bird animation
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
            refresh_animation=32;
        }

        if(actual_animation!=animation) // change animation
        {
            frame=0;
            actual_animation=animation;
        }
        if(actual_clock>=refresh_animation&&animation==0) // idle animation
        {
            actual_clock=0;
            frame++;
            if(frame==nr_frame_idle) frame=0;
        }
        if(actual_clock>=refresh_animation&&animation==animation_move) // walk/run animation
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

        character_animation[which_character][animation][frame].setScale(scale,scale); // dodge bird

        map_ground.move(-speed,0); // move ground
        if(map_ground.getPosition().x<0) // looped ground
        {
            map_ground.setPosition(2045,900);
        }



        if(obstacle_clock>o_c_time&&run)
        {
            obstacle_clock=0;
            generate_obstacle(birds,mushrooms);
            o_c_time=rand()%10+9;
            o_c_time/=10;
        }


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


        //DRAW

        window.clear();
        window.draw(map_sky);
        for( auto &cloud:map_cloud)
        {
            window.draw(cloud);
        }
        window.draw(character_animation[which_character][animation][frame]);
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
        window.draw(score_text);

        window.display();

    }
    //    }

    return 0;
}
