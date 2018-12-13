#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;


int main()
{
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML Practice - 1");
    sf::RenderWindow window(sf::VideoMode(1920, 960), "SFML Practice - 1");
    sf::Event event;

    //sf::Font font;
    //font.loadFromFile("assets/fonts/Lobster-Regular.ttf");

    //sf::Text text("Hello World", font, 64);
    //text.setFillColor(sf::Color::Cyan);

    sf::Font font1, font2;
    font1.loadFromFile("assets/fonts/LobsterTwo-Bold.ttf");
    font2.loadFromFile("assets/fonts/Orbitron-Regular.ttf");

    sf::Text text1("ADVENTURE ISLAND", font1, 72);
    sf::Text text2("New Game", font2, 18), text3("Controls", font2, 18), text4("High Score", font2, 18), text5("Exit", font2, 18);
    text1.setPosition(window.getSize().x*2/3, window.getSize().y/3);
    text2.setPosition(text1.getPosition().x, text1.getPosition().y+100);
    text3.setPosition(text2.getPosition().x, text2.getPosition().y+50);
    text4.setPosition(text3.getPosition().x, text3.getPosition().y+50);
    text5.setPosition(text4.getPosition().x, text4.getPosition().y+50);

    sf::Texture texture, texture2, texture_menu, texture_arrow;
    texture.loadFromFile("assets/images/firen_0_test.png");//, sf::FloatRect(0 ,0, 80, 80));
    //texture2.loadFromFile("assets/images/environment-preview.png");
    texture2.loadFromFile("assets/images/map_1_test.png");
    texture_menu.loadFromFile("assets/images/Main_menu.jpg");
    texture_arrow.loadFromFile("assets/images/menu_arrow.png");

    sf::IntRect sprite_size(0, 0, 80, 80);
    sf::Sprite sprite(texture, sprite_size), sprite2(texture2), sprite_menu(texture_menu), sprite_arrow(texture_arrow);
    //sprite.setPosition(400, 634);
    sprite.setPosition(445, 574-80);
    //sprite2.setPosition(0, 462);
    sprite2.setPosition(0, 0);
    sf::Vector2f sprite_arrow_pos(text2.getPosition().x-28, text2.getPosition().y);
    //sprite_arrow.setPosition(sprite_arrow_pos.x, sprite_arrow_pos.y);

    window.setFramerateLimit(30);
    //window.setKeyRepeatEnabled(false); //if it's true then holding down jump key
                                         //cause the player to constantly keep jumping.
    int jump_velocity = 14, animatin_change_time = 75;
    float jump_animation_time = jump_velocity - 3;
    bool iskeypressed;
    bool left = false, right = true, jump = false, inair = false;

    //current maximum distance covered while jumping is 125 pixels

    sf::Clock clock;
    int elapsed_time;

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 960.0f));

    //sf::View view;
    //view.setCenter(400.f, 200.f);

    while(window.isOpen())
    {

        /*sprite_arrow.setPosition(sprite_arrow_pos.x, sprite_arrow_pos.y);

        if(sf::Keyboard::isKeyPressed((sf::Keyboard::Down)))
            sprite_arrow_pos.y+=18;
        else if(sf::Keyboard::isKeyPressed((sf::Keyboard::Up)))
            sprite_arrow_pos.y-=18;


        window.clear();
        window.draw(sprite_menu);
        window.draw(sprite_arrow);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.display();*/

        //if(sf::Keyboard::isKeyPressed((sf::Keyboard::Enter)) && sprite_arrow_pos.y == text2.getPosition().y){


            while(window.pollEvent(event))
            {
                if(event.type==sf::Event::Closed)
                    window.close();
                if(event.type==sf::Event::KeyPressed)
                {
                    //to make the character turn instantly without waiting for the
                    //usual delay(animation_change_time) between animation change
                    if(event.key.code==sf::Keyboard::Right && !right)
                    {
                        sprite_size.top=80;
                        sprite_size.left=0;
                        sprite.setTextureRect(sprite_size);
                    }
                    else if(event.key.code==sf::Keyboard::Left && !left)
                    {
                        sprite_size.top=80;
                        sprite_size.left=480;
                        sprite.setTextureRect(sprite_size);
                    }
                    //iskeypressed = true;
                    if(event.key.code==sf::Keyboard::Space && !jump)
                    {
                        jump = true;
                        inair = true;
                    }
                }
            }

            iskeypressed = false;

            //forward movement and animation
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                iskeypressed = true;
                right = true;
                left = false;
                if(!jump)
                {
                    if(clock.getElapsedTime().asMilliseconds()>animatin_change_time){
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
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                iskeypressed = true;
                left = true;
                right = false;
                if(!jump)
                {
                    if(clock.getElapsedTime().asMilliseconds()>animatin_change_time){
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

                sprite.move(0, -(jump_velocity--));
                if(sprite.getPosition().y+80==574 && !inair)
                {
                    jump = false;
                    jump_velocity=14;
                }
            }
            //no movement animation
            if(!iskeypressed)
            {
                if(sprite_size.top!=0)
                    sprite_size.top=0;
                if(right)
                {
                    if(clock.getElapsedTime().asMilliseconds()>animatin_change_time){
                    if(sprite_size.left>=400)
                        sprite_size.left=0;
                    else
                        sprite_size.left+=80;
                    clock.restart();
                    }
                }
                else if(left)
                {
                    if(clock.getElapsedTime().asMilliseconds()>animatin_change_time){
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

            view.setCenter(sprite.getPosition().x, 574);

            window.clear();
            window.setView(view);
            window.draw(sprite2);
            window.draw(sprite);
            window.display();
        //}
    }


    return 0;
}
