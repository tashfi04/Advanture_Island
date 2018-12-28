#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;


int main()
{
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML Practice - 1");
    sf::RenderWindow window(sf::VideoMode(1920, 960), "SFML Practice - 1");
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

    sf::Texture texture, texture2, texture_menu, texture_arrow;
    texture.loadFromFile("assets/images/firen_0_test.png");//, sf::FloatRect(0 ,0, 80, 80));
    //texture2.loadFromFile("assets/images/environment-preview.png");
    texture2.loadFromFile("assets/images/map_1_test.png");
    texture_menu.loadFromFile("assets/images/Main_menu.jpg");
    texture_arrow.loadFromFile("assets/images/menu_arrow.png");

    sf::IntRect sprite_size(0, 0, 80, 80);
    sf::Sprite sprite(texture, sprite_size), sprite2(texture2), sprite_menu(texture_menu), sprite_arrow(texture_arrow);
    //sprite.setPosition(200, 700);
    sprite.setPosition(445, 574-80);
    //sprite2.setPosition(0, 462);
    sprite2.setPosition(0, 0);
    sf::Vector2f sprite_arrow_pos(text2.getPosition().x-28, text2.getPosition().y+2);
    //sprite_arrow.setPosition(sprite_arrow_pos.x, sprite_arrow_pos.y);

    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false); //if it's true then holding down jump key
    //cause the player to constantly keep jumping.
    int jump_velocity = 25, animatin_change_time = 75;//14
    float jump_animation_time = jump_velocity - 3;
    bool iskeypressed;
    bool left = false, right = true, jump = false, inair = false, isdead = false, collision_up, collision_down, collision_left, collision_right;


    //current maximum distance covered while jumping is 125 pixels
    sf::Clock clock;
    int elapsed_time;

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 960.0f));

    //sf::View view;
    //view.setCenter(400.f, 200.f);

    //area of platform is 20 pixels less in left and right directions
    //and 1 pixel more in up and down directions from the area of the sprite
    //Collision
    sf::FloatRect platform_1(420, 573, 1240, 427);
    sf::FloatRect platform_2(1900, 654, 140, 107);
    sf::FloatRect player;


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
                    sprite_arrow_pos.y += 50;
                    if(sprite_arrow_pos.y > text6.getPosition().y+2)
                        sprite_arrow_pos.y = text2.getPosition().y+2;
                }
                else if(event_menu.key.code == sf::Keyboard::Up)
                {
                    sprite_arrow_pos.y -= 50;
                    if(sprite_arrow_pos.y < text2.getPosition().y+2)
                        sprite_arrow_pos.y = text6.getPosition().y+2;
                }
            }
        }

        sprite_arrow.setPosition(sprite_arrow_pos.x, sprite_arrow_pos.y);

        /*
        if(sf::Keyboard::isKeyPressed((sf::Keyboard::Down)))
            sprite_arrow_pos.y+=50;
        else if(sf::Keyboard::isKeyPressed((sf::Keyboard::Up)))
            sprite_arrow_pos.y-=50;
        */

        window.clear();
        window.draw(sprite_menu);
        window.draw(sprite_arrow);
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
            if(sprite_arrow_pos.y == text6.getPosition().y+2)
                window.close();
            if(sprite_arrow_pos.y == text2.getPosition().y+2)
            {
                window.clear();

                while(!isdead)
                {
                    while(window.pollEvent(event_ingame))
                    {
                        if(event_ingame.type==sf::Event::Closed)
                            window.close();
                        if(event_ingame.type==sf::Event::KeyPressed)
                        {
                            //to make the character turn instantly without waiting for the
                            //usual delay(animation_change_time) between animation change
                            if(event_ingame.key.code==sf::Keyboard::Right && !right && !collision_right)
                            {
                                sprite_size.top=80;
                                sprite_size.left=0;
                                sprite.setTextureRect(sprite_size);
                            }
                            else if(event_ingame.key.code==sf::Keyboard::Left && !left && !collision_left)
                            {
                                sprite_size.top=80;
                                sprite_size.left=480;
                                sprite.setTextureRect(sprite_size);
                            }
                            //iskeypressed = true;
                            if(event_ingame.key.code==sf::Keyboard::Space && !jump)
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
                    player=sprite.getGlobalBounds();

                    if(player.intersects(platform_1))
                    {
                        if(player.top<platform_1.top)
                            collision_down = true;
                        else if(player.top+80>platform_1.top+platform_1.height)
                            collision_up = true;
                        if(player.left<platform_1.left && player.top+80>platform_1.top+1)
                            collision_right = true;
                        else if(player.left+80>platform_1.left+platform_1.width && player.top+80>platform_1.top+1)
                            collision_left = true;
                        /*if(player.left+80-platform_1.left == 5 && player.top+80>platform_1.top+1)
                            collision_right = true;
                        else if(platform_1.left+platform_1.width-player.left == 5)
                            collision_left = true;*/
                    }
                    else if(player.intersects(platform_2))
                    {
                        if(player.top<platform_2.top)
                            collision_down = true;
                        else if(player.top+80>platform_2.top+platform_2.height)
                            collision_up = true;
                        if(player.left<platform_2.left)
                            collision_right = true;
                        else if(player.left+80>platform_2.left+platform_2.width)
                            collision_left = true;
                    }
                    //cout<<sprite.getPosition().y+80<<"---"<<collision_down<<"---"<<player.top<<"---"<<platform_1.top<<endl;
                    cout<<collision_down<<"--"<<collision_left<<"--"<<collision_right<<"--"<<collision_up<<"--"<<sprite.getPosition().x+80<<endl;
                    //cout<<player.top+80<<"--"<<platform_1.top+1<<endl;


                    //forward movement and animation
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !collision_right)
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
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !collision_left)
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
                    if(jump)
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
                            jump_velocity=25;
                        }
                        else
                            sprite.move(0, -(jump_velocity--));
                    }
                    //cout<<sprite.getPosition().y+80<<"---"<<collision_down<<"---"<<player.top<<"---"<<platform_1.top<<endl;

                    //no movement animation
                    if(!iskeypressed)
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
                        sprite.setTextureRect(sprite_size);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        return 0;
                        //window.close();
                    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                    //   cout<<sprite.getPosition().x+80<<endl;

                    view.setCenter(sprite.getPosition().x, 574);

                    window.clear();
                    window.setView(view);
                    window.draw(sprite2);
                    window.draw(sprite);
                    window.display();
                }
            }
        }
    }


    return 0;
}
