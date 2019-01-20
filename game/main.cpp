#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;


int main()
{
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML Practice - 1");
    sf::RenderWindow window(sf::VideoMode(1300, 620), "Adventure Island");//(1920, 960), "SFML Practice - 1");
    sf::Event event_menu, event_ingame;

    //sf::Font font;
    //font.loadFromFile("assets/fonts/Lobster-Regular.ttf");

    //sf::Text text("Hello World", font, 64);
    //text.setFillColor(sf::Color::Cyan);

    sf::Font font1, font2;
    font1.loadFromFile("assets/fonts/LobsterTwo-Bold.ttf");
    font2.loadFromFile("assets/fonts/Orbitron-Regular.ttf");
    sf::Text text1("ADVENTURE ISLAND", font1, 72);
    sf::Text text2("New Game", font2, 18), text3("Controls", font2, 18), text4("High Score", font2, 18), text5("Credits", font2, 18), text6("Exit", font2, 18);
    text1.setPosition(window.getSize().x/3, window.getSize().y/3);
    text2.setPosition(text1.getPosition().x, text1.getPosition().y+100);
    text3.setPosition(text2.getPosition().x, text2.getPosition().y+50);
    text4.setPosition(text3.getPosition().x, text3.getPosition().y+50);
    text5.setPosition(text4.getPosition().x, text4.getPosition().y+50);
    text6.setPosition(text5.getPosition().x, text5.getPosition().y+50);

    sf::Texture texture, texture2, texture_menu, texture_menu_arrow, texture_arrow, texture_enemy;
    //texture.loadFromFile("assets/images/firen_0_test.png");//, sf::FloatRect(0 ,0, 80, 80));
    texture.loadFromFile("assets/images/henry_0_test.png");
    texture_arrow.loadFromFile("assets/images/henry_arrow_test_2.png");
    texture_enemy.loadFromFile("assets/images/Enemy_1.png");
    texture2.loadFromFile("assets/images/map_1_tes_fixed_2t.png");
    //texture2.loadFromFile("assets/images/map_1_test.png");
    texture_menu.loadFromFile("assets/images/Main_menu.jpg");
    texture_menu_arrow.loadFromFile("assets/images/menu_arrow.png");

    sf::IntRect sprite_size(0, 0, 80, 80);
    sf::IntRect sprite_arrow_size(0, 0, 48, 48);
    sf::Sprite sprite(texture, sprite_size), sprite2(texture2), sprite_menu(texture_menu), sprite_menu_arrow(texture_menu_arrow), sprite_arrow(texture_arrow, sprite_arrow_size);
    sf::IntRect sprite_enemy_size[3];

    sf::Sprite sprite_enemy[3];
    for(int i=0; i<3; i++)
    {
        sprite_enemy_size[i].left = 0;
        sprite_enemy_size[i].top = 0;
        sprite_enemy_size[i].width = 80;
        sprite_enemy_size[i].height = 80;
        sprite_enemy[i].setTexture(texture_enemy);
    }
//    sprite.setPosition(445, 360-80);
    //sprite.setPosition(445, 574-80);
    //sprite2.setPosition(0, 462);
    sprite2.setPosition(0, 0);
    sf::Vector2f sprite_menu_arrow_pos(text2.getPosition().x-28, text2.getPosition().y+2);
    //sprite_arrow.setPosition(sprite_arrow_pos.x, sprite_arrow_pos.y);

    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false); //if it's true then holding down jump key
    //cause the player to constantly keep jumping.
    int jump_velocity = 14, animatin_change_time = 75, now, lives, arrow_direction = 0;//14
    float jump_animation_time = jump_velocity - 3;
    bool iskeypressed;
    bool left = false, right = true, jump = false, inair = false, fall = false, collision_up, collision_down, collision_left, collision_right;
    bool attack = false;


    //current maximum distance covered while jumping is 125 pixels
    sf::Clock clock ,attack_clock;
    int elapsed_time;

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1300.0f, 620.0f));//sf::Vector2f(1920.0f, 960.0f));

    //sf::View view;
    //view.setCenter(400.f, 200.f);

    //area of platform is 20 pixels less in left and right directions
    //and 1 pixel more in up and down directions from the area of the sprite
    //Collision

    sf::FloatRect platform[7];
    /*platform[0].left=420;
    platform[0].top=573;
    platform[0].width=1240;
    platform[0].height=427;

    platform[1].left=1900;
    platform[1].top=654;
    platform[1].width=140;
    platform[1].height=107;*/
    //sf::FloatRect platform_1(420, 573, 1240, 427);
    //sf::FloatRect platform_2(1900, 654, 140, 107);

    platform[0].left=320;
    platform[0].top=359;
    platform[0].width=920;
    platform[0].height=241;

    platform[1].left=1400;
    platform[1].top=309;
    platform[1].width=110;
    platform[1].height=152;

    platform[2].left=1710;
    platform[2].top=359;
    platform[2].width=400;
    platform[2].height=241;

    platform[3].left=2220;
    platform[3].top=492;
    platform[3].width=100;
    platform[3].height=49;

    platform[4].left=2420;
    platform[4].top=409;
    platform[4].width=30;
    platform[4].height=42;

    platform[5].left=2530;
    platform[5].top=309;
    platform[5].width=100;
    platform[5].height=92;

    platform[6].left=2740;
    platform[6].top=359;
    platform[6].width=1380;
    platform[6].height=241;
    sf::FloatRect player, arrow;


    while(window.isOpen())
    {
        while(window.pollEvent(event_menu))
        {
            if(event_menu.type == sf::Event::Closed)
                window.close();
            else if(event_menu.type == sf::Event::KeyPressed)
            {
                if(event_menu.key.code == sf::Keyboard::Escape)
                    window.close();
                else if(event_menu.key.code == sf::Keyboard::Down)
                {
                    sprite_menu_arrow_pos.y += 50;
                    if(sprite_menu_arrow_pos.y > text6.getPosition().y+2)
                        sprite_menu_arrow_pos.y = text2.getPosition().y+2;
                }
                else if(event_menu.key.code == sf::Keyboard::Up)
                {
                    sprite_menu_arrow_pos.y -= 50;
                    if(sprite_menu_arrow_pos.y < text2.getPosition().y+2)
                        sprite_menu_arrow_pos.y = text6.getPosition().y+2;
                }
            }
        }

        sprite_menu_arrow.setPosition(sprite_menu_arrow_pos.x, sprite_menu_arrow_pos.y);

        /*
        if(sf::Keyboard::isKeyPressed((sf::Keyboard::Down)))
            sprite_arrow_pos.y+=50;
        else if(sf::Keyboard::isKeyPressed((sf::Keyboard::Up)))
            sprite_arrow_pos.y-=50;
        */

        window.clear();
        window.draw(sprite_menu);
        window.draw(sprite_menu_arrow);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.draw(text6);
        window.display();

        //cout<<text2.getGlobalBounds().height<<"----"<<sprite_arrow.getGlobalBounds().height<<endl;
        //cout<<text2.getGlobalBounds().top<<"----"<<sprite_arrow.getGlobalBounds().top<<endl;
        //cout<<text2.getPosition().y<<"----"<<sprite_arrow.getPosition().y<<endl;
        //cout<<sprite_arrow_pos.y<<"----"<<text2.getPosition().y<<endl;


        if(sf::Keyboard::isKeyPressed((sf::Keyboard::Enter)))
        {
            if(sprite_menu_arrow_pos.y == text6.getPosition().y+2)
                window.close();
            if(sprite_menu_arrow_pos.y == text2.getPosition().y+2)
            {
                lives = 3;
                sprite.setPosition(445, 360-80);
                sprite_arrow.setPosition(0, 700);
                window.clear();

                while(lives != 0)
                {
                    while(window.pollEvent(event_ingame))
                    {
                        if(event_ingame.type==sf::Event::Closed)
                            window.close();
                        if(event_ingame.type==sf::Event::KeyPressed)
                        {
                            if(event_ingame.key.code==sf::Keyboard::Z && !jump && !fall &&!attack)
                            {
                                attack = true;
                                if(right)
                                {
                                    sprite_size.left = 0;
                                    arrow_direction = 1;
                                }
                                else if(left)
                                {
                                    sprite_size.left = 480;
                                    arrow_direction = -1;
                                }
                                //cout<<"attack!!!"<<endl;
                            }
                            //to make the character turn instantly without waiting for the
                            //usual delay(animation_change_time) between animation change
                            if(event_ingame.key.code==sf::Keyboard::Right && !right && !collision_right && !attack)
                            {
                                sprite_size.top=80;
                                sprite_size.left=0;
                                sprite.setTextureRect(sprite_size);
                            }
                            else if(event_ingame.key.code==sf::Keyboard::Left && !left && !collision_left && !attack)
                            {
                                sprite_size.top=80;
                                sprite_size.left=480;
                                sprite.setTextureRect(sprite_size);
                            }
                            //iskeypressed = true;
                            if(event_ingame.key.code==sf::Keyboard::Space && !jump && !fall && !attack)
                            {
                                jump = true;
                                inair = true;
                            }
                        }
                    }

                    iskeypressed = false;

                    //
                    //
                    //collision
                    collision_up = collision_down = collision_left = collision_right = false;
                    now = -1;
                    player=sprite.getGlobalBounds();
                    arrow=sprite_arrow.getGlobalBounds();
                    for(int i=0; i<7; i++)
                    {
                        if(player.left<platform[i].left+platform[i].width && player.left+80>platform[i].left)
                        {
                            now = i;
                            break;
                        }
                    }

                    for(int i=0; i<7; i++)
                    {
                        if(player.intersects(platform[i]))
                        {
                            if(player.top<platform[i].top && (player.top+80-platform[i].top)==1)
                                collision_down = true;
                            else if(player.top+80>platform[i].top+platform[i].height)
                                collision_up = true;
                            if(player.left<platform[i].left && player.top+80>platform[i].top+1)
                                collision_right = true;
                            else if(player.left+80>platform[i].left+platform[i].width && player.top+80>platform[i].top+1)
                                collision_left = true;
                            /*if(player.left+80-platform_1.left == 5 && player.top+80>platform_1.top+1)
                                collision_right = true;
                            else if(platform_1.left+platform_1.width-player.left == 5)
                                collision_left = true;*/
                        }
                        if(arrow.intersects(platform[i]))
                        {
                            sprite_arrow.setPosition(0, 700);
                            arrow_direction = 0;
                        }
                        else
                        {
                            if(arrow_direction==1)
                            {
                                sprite_arrow.move(3, .3);
                                //cout<<"R"<<endl;
                            }
                            else if(arrow_direction==-1)
                            {
                                sprite_arrow.move(-3, .3);
                                //cout<<"L"<<endl;
                            }
                            //cout<<"*((*("<<endl;
                        }
                    }

                    if(collision_down  && fall)
                    {
                        fall = false;
                        jump_velocity = 14;
                    }

                    //cout<<sprite.getPosition().y+80<<"---"<<collision_down<<"---"<<player.top<<"---"<<platform_1.top<<endl;
                //cout<<collision_down<<"--"<<collision_left<<"--"<<collision_right<<"--"<<collision_up<<"--"<<sprite.getPosition().y+80<<endl;
                    //cout<<player.top+80<<"--"<<platform_1.top+1<<endl;
                //cout<<sprite.getPosition().y+80<<"<>"<<platform[now].top-player.top-80<<"<>"<<now<<endl;


                    //forward movement and animation
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !collision_right && !attack)
                    {
                        iskeypressed = true;
                        right = true;
                        left = false;
                        if(!jump)
                        {
                            if(clock.getElapsedTime().asMilliseconds()>animatin_change_time)
                            {
                                if(sprite_size.top!=80)
                                    sprite_size.top=80;
                                if(sprite_size.left>=400)
                                    sprite_size.left=0;
                                else
                                    sprite_size.left+=80;
                                sprite.setTextureRect(sprite_size);
                                clock.restart();
                            }
                        }
                        sprite.move(5, 0);
                    }
                    //backward movement and animation
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !collision_left && !attack)
                    {
                        iskeypressed = true;
                        left = true;
                        right = false;
                        if(!jump)
                        {
                            if(clock.getElapsedTime().asMilliseconds()>animatin_change_time)
                            {
                                if(sprite_size.top!=80)
                                    sprite_size.top=80;
                                if(sprite_size.left>=880 || sprite_size.left<100)
                                    sprite_size.left=480;
                                else
                                    sprite_size.left+=80;
                                sprite.setTextureRect(sprite_size);
                                clock.restart();
                            }
                        }
                        sprite.move(-5, 0);
                    }
                    //jumping and animation
                    if(jump && !fall)
                    {
                        iskeypressed = true;
                        if(jump_velocity==0)
                            inair = false;
                        if(sprite_size.top!=160)
                        {
                            sprite_size.top=160;
                        }
                        if(right)
                        {
                            if(jump_velocity>=jump_animation_time)
                                sprite_size.left=80;
                            else if(jump_velocity<jump_animation_time)
                                sprite_size.left=160;
                        }
                        else if(left)
                        {
                            if(jump_velocity>=jump_animation_time)
                                sprite_size.left=480;
                            else if(jump_velocity<jump_animation_time)
                                sprite_size.left=560;
                        }

                        sprite.setTextureRect((sprite_size));

                        //sprite.move(0, -(jump_velocity--));

                        if(/*sprite.getPosition().y+80>=574*/collision_down && !inair)
                        {
                            jump = false;
                            jump_velocity=14;
                        }
                        else if(now!= -1 && (platform[now].top-player.top-80)>=0 && (platform[now].top-player.top-80)<=14 && !inair)//player.top-80 because -(player.top+80)=-player.top-80
                        {
                            //cout<<"jump >> "<<platform[now].top-player.top-80<<endl;
                            sprite.move(0, (platform[now].top-player.top-80+1));
                            //cout<<"***"<<endl;
                        }
                        else
                            sprite.move(0, -(jump_velocity--));

                    }
                    //cout<<sprite.getPosition().y+80<<"---"<<collision_down<<"---"<<player.top<<"---"<<platform_1.top<<endl;

                    if(!jump && !collision_down)
                    {
                        fall = true;
                        if(now!= -1 && (platform[now].top-player.top-80)>=0 && (platform[now].top-player.top-80)<=14 && !inair)
                        {
                            //cout<<"fall >> "<<platform[now].top-player.top-80<<endl;
                            sprite.move(0, (platform[now].top-player.top-80+1));
                        }
                        else
                            sprite.move(0, jump_velocity++);
                    }

                    //no movement animation
                    if(!iskeypressed && !attack)
                    {
                        if(sprite_size.top!=0)
                            sprite_size.top=0;
                        if(right)
                        {
                            if(clock.getElapsedTime().asMilliseconds()>animatin_change_time)
                            {
                                if(sprite_size.left>=400)
                                    sprite_size.left=0;
                                else
                                    sprite_size.left+=80;
                                clock.restart();
                            }
                        }
                        else if(left)
                        {
                            if(clock.getElapsedTime().asMilliseconds()>animatin_change_time)
                            {
                                if(sprite_size.left>=880 || sprite_size.left<480)
                                    sprite_size.left=480;
                                else
                                    sprite_size.left+=80;
                                clock.restart();
                            }
                        }
                        //cout<<sprite_size.left<<endl;
                        sprite.setTextureRect(sprite_size);
                    }

                    //attack animation
                    if(attack)
                    {
                        iskeypressed = true;
                        if(sprite_size.top!=240)
                            sprite_size.top=240;
                        if(right)
                        {
                            sprite_arrow_size.left = 0;
                            if(clock.getElapsedTime().asMilliseconds()>animatin_change_time)
                            {
                                if(sprite_size.left>=400)
                                {
                                    sprite_size.left = 0;
                                    attack = false;
                                    //cout<<player.top+80<<"<><>"<<player.top/2<<endl;
                                    sprite_arrow.setPosition(player.left+80, player.top+20);
                                    //cout<<sprite_arrow.getGlobalBounds().top<<endl;
                                }
                                else
                                    sprite_size.left+=80;
                                clock.restart();
                            }

                        }
                        else if(left)
                        {
                            sprite_arrow_size.left = 48;
                            if(clock.getElapsedTime().asMilliseconds()>animatin_change_time)
                            {
                                if(sprite_size.left>=880 || sprite_size.left<480)
                                {
                                    sprite_size.left=480;
                                    attack = false;
                                    sprite_arrow.setPosition(player.left, player.top+20);
                                }
                                else
                                    sprite_size.left+=80;
                                clock.restart();
                            }
                        }
                        //cout<<sprite_size.left<<endl;
                        sprite_arrow.setTextureRect(sprite_arrow_size);
                        sprite.setTextureRect(sprite_size);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        return 0;

                    if(sprite.getPosition().y>=620)
                    {
                        sprite.setPosition(445, 360-80);
                        lives--;
                    }
                        //window.close();
                    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                    //   cout<<sprite.getPosition().x+80<<endl;

                    view.setCenter(sprite.getPosition().x, 360);

                    window.clear();
                    window.setView(view);
                    window.draw(sprite2);
                    window.draw(sprite);
                    window.draw(sprite_arrow);
                    window.display();
                }
                window.clear();
            }
        }
    }


    return 0;
}
