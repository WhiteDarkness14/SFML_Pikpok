#include <headers.h>
int main()
{
    srand(time(NULL));
    // Tworzenie okna i wyświetlenie ekranu ładowania
    RenderWindow window;
    window_set(window);
    Texture loading_T;
    loading_T.loadFromFile("picture/loading.png");
    Sprite loading;
    loading.setTexture(loading_T);
    window.draw(loading);
    window.display();

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
    character_Sprite character;

    // Tworzenie Bossa
    vector<vector<boss_Sprite>> boss;
    set_boss(boss);

    // Tworzenie pocisków
    vector<obstacle_Sprite>flame_dino;
    vector<obstacle_Sprite> flame_character;
    set_flames(flame_dino,flame_character);

    // Dźwięk
    my_sound jump_sound("sfx/jump.wav");
    my_sound dead_sound("sfx/dead.wav");
    my_sound bomb_sound("sfx/bomb.wav");
    my_sound dodge_sound("sfx/dodge.flac");
    my_sound dinosaur_sound("sfx/dinosaur.wav");

    // Napisy
    my_text score_text("Pacifico",100,1750,50);
    my_text info_text("Pacifico",75,400,50);
    info_text.setString("Space - start \n Tab - character change \n Up - jump \n Down - dodge \n Alt - attack");
    my_text final_text("Pacifico",75,700,200);
    final_text.setString("  GAME OVER\n      SCORE: \n \n    Space - restart \nTab - character change");
    my_text final_score("Pacifico",250,850,350);

    // Zmienne
    bool run=false;
    bool sound_dino_bool=true;
    bool sound_dodge_bool=true;
    bool boss_MODE=false;
    bool attack=false;
    Clock clock;
    float actual_clock=0, speed_clock=1, bird_clock=0, obstacle_clock=0, total_time=0, jump_clock=0; // liczniki czasów
    float speed=0;
    float frame_bird=0;
    float break_speed;
    float scale=0.5;
    float boss_animation=0;
    float frame_boss=0;
    float boss_life=4;
    float time_jump=300;
    vector <float> time_jump_distance(3,0);
    int score=0;
    int score_boss=0;
    string which_animation="idle";

    //Główna pętla gry
    while (window.isOpen())
    {
        sf::Event event;
        attack=false;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) //Zamknięcie okna
            {
                window.close();
            }
            if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Tab && !run) // Zmiana postaci
            {
                character.change_character();
                which_animation="idle";
            }

            if (Keyboard::isKeyPressed(Keyboard::Space)&& !run)  // Restartowanie wszystkich zmiennych
            {
                character.start();
                which_animation="move";

                time_jump=300;
                boss_MODE=false;
                score_boss=0;
                speed=7;
                run=true;
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
                for(unsigned i=0;i<flame_dino.size();i++)
                {
                    flame_dino[i].to_move=false;
                }
                boss[1][7].setPosition(1910,972);
                boss_MODE=false;
                boss_animation=0;
                score_boss=0;
                boss_life=4;
                for(unsigned i=0;i<flame_dino.size();i++)
                {
                    flame_dino[i].to_move=false;
                }
                sound_dino_bool=true;
            }
            if(scale==0.5&&event.type ==Event::KeyPressed && event.key.code == Keyboard::Up && run) // Skok
            {
                which_animation="jump";
            }
            if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Down && run) // Zmniejszenie rozmiaru
            {
                scale=0.25;
                if(sound_dodge_bool)
                {
                    sound_dodge_bool=false;
                    dodge_sound.play();
                }
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down && run) // Zwiększenie rozmiaru
            {
                scale=0.5;
                sound_dodge_bool=true;
                dodge_sound.play();
            }
            if(event.type == Event::KeyReleased && (event.key.code == Keyboard::LAlt || event.key.code == Keyboard::RAlt ) && scale==0.5) // Atak postaci
            {
                attack=true;
            }

        }

        //Czas
        const sf::Time elapsed = clock.restart();
        actual_clock+=elapsed.asMilliseconds();
        speed_clock+=elapsed.asSeconds();
        bird_clock+=elapsed.asSeconds();
        total_time+=elapsed.asMilliseconds();
        obstacle_clock+=elapsed.asSeconds();

        //Logika gry
        counter(total_time, score, score_boss, boss_MODE, run); // zliczanie punktów
        score_text.setString(to_string(score));  // Napisy
        final_score.setString(to_string(score));  // Napisy

        if(speed_clock>0.5&&character.alive&&run)  // Przyspieszenie
        {
            speed_clock=0;
            speed+=0.5;
        }

        character.change_animation(speed, actual_clock, jump_clock, elapsed, jump_sound, dead_sound, which_animation, break_speed,run); // Zmiana animacji
        character.dodge(scale); // Unik

        move_background(speed,map_cloud, map_ground); // Przesuwanie tła

        if(bird_clock>0.06) // Animowanie ptaka i Bossa
        {
            bird_clock=0;
            frame_bird++;
            if(frame_bird==10) // Latanie ptaka
            {
                frame_bird=0;
            }

            else if (boss_animation==0) // Bieganie Bossa
            {
                frame_boss++;
                if(frame_boss==8) frame_boss=0;
            }

            else if(boss_animation==1) // Śmierć Bossa
            {
                if(frame_boss<7)
                {
                    frame_boss++;
                }
            }
        }

        if(!boss_MODE) // Etap z przeszkodami
        {
            if(obstacle_clock>25/speed&&run) // Generowanie przeszkód
            {
                obstacle_clock=0;
                generate_obstacle(birds,mushrooms,time_jump_distance);

            }

            if(which_animation!="idle" && which_animation!="dead") // Przesuwanie przeszkód jeśli postać się porusza
            {
                for(unsigned i=0;i<birds.size();i++)
                {
                    if(birds[i][0].to_move)
                    {
                        if(birds[i][0].getPosition().y>660) birds[i][0].updown=-1;
                        if(birds[i][0].getPosition().y<600) birds[i][0].updown=1;

                        for(unsigned j=0;j<birds[i].size();j++)
                        {
                            birds[i][j].move(-speed,birds[i][0].updown);
                        }
                        if(Collision::PixelPerfectTest(character.one_frame(),birds[i][frame_bird])) // Kolizja z ptakiem
                        {
                            which_animation="dead";
                        }
                    }
                    if(mushrooms[i].to_move)
                    {
                        mushrooms[i].move(-speed,0);
                        if(mushrooms[i].getPosition().x<650 && mushrooms[i].getPosition().x>=500)
                        {
                            time_jump_distance[i]+=elapsed.asMilliseconds();
                        }
                        else if(mushrooms[i].getPosition().x<=500)
                        {
                            if(time_jump>time_jump_distance[i])
                            {
                                time_jump=time_jump_distance[i];
                            }
                        }
                        if(Collision::PixelPerfectTest(character.one_frame(),mushrooms[i])) // Kolizja z grzybem
                        {
                            which_animation="dead";
                        }
                    }
                }
            }
        }

        if(!(score_boss%100) && score_boss>10) // Etap walki z Bossem
        {
            boss_MODE=true;
            if(obstacle_clock>50/speed) // Generowanie pocisków Bossa
            {
                obstacle_clock=0;
                generate_flame(flame_dino);
            }
            if(sound_dino_bool) //Dźwięk
            {
                dinosaur_sound.play();
                sound_dino_bool=false;
            }
            if(attack) // Jeśli postać zaatakuje
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
                        flame_character[i].setPosition(200,600);
                        break;
                    }
                }
            }
            for(unsigned i=0;i<flame_dino.size();i++)
            {
                if(flame_dino[i].to_move)
                {
                    flame_dino[i].move(-speed,0);
                    flame_dino[i].rotate(speed/10);
                    if(Collision::PixelPerfectTest(character.one_frame(),flame_dino[i])) // Kolizja postaci
                    {
                        which_animation="dead";
                        flame_character[i].setPosition(1920,600);
                    }
                }
                if(flame_character[i].to_move)
                {
                    flame_character[i].move(speed,0);
                    flame_character[i].rotate(rand()%3+3);
                    if(Collision::PixelPerfectTest(boss[boss_animation][frame_boss],flame_character[i])) // Kolizja Bossa
                    {
                        boss_life--;
                        flame_character[i].to_move=false;
                        bomb_sound.play();
                        for(unsigned i=0;i<birds.size();i++)
                        {
                            birds[i][0].to_move=false;
                            mushrooms[i].to_move=false;
                        }
                    }
                }
            }
            if(boss_life==0) // Jeśli Boss nie ma życia
            {
                frame_boss=0;
                boss_life--;
                boss_animation=1;
            }
            if(boss_animation==1 && frame_boss==7) // Zjazd ze sceny bossa
            {
                dinosaur_sound.stop();
                boss[1][7].move(-speed,0);
                if(boss[1][7].getPosition().x<-500)
                {
                    boss[1][7].setPosition(1910,972);
                    boss_MODE=false;
                    boss_animation=0;
                    score_boss=0;
                    boss_life=4;
                    for(unsigned i=0;i<flame_dino.size();i++)
                    {
                        flame_dino[i].to_move=false;
                    }
                    sound_dino_bool=true;
                }
            }
        }

        //Rysowanie

        window.clear();
        draw_sky(window, map_sky, map_cloud);
        draw_text(window,which_animation, info_text, final_text, final_score, score_text);

        window.draw(character.one_frame());

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
        window.display();
    }
    return 0;
}
