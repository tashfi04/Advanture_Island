#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;


int main()
{
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML Practice - 1");
    sf::RenderWindow window(sf::VideoMode(1000, 960), "SFML Practice - 1");
    sf::Event event;

    //sf::Font font;
    //font.loadFromFile("assets/fonts/Lobster-Regular.ttf");

    //sf::Text text("Hello World", font, 64);
    //text.setFillColor(sf::Color::Cyan);

    sf::Texture texture, texture2;
    texture.loadFromFile("assets/images/firen_0_test.png");//, sf::FloatRect(0 ,0, 80, 80));
    //texture2.loadFromFile("assets/images/environment-preview.png");
    texture2.loadFromFile("assets/images/map_1_test.png");

    sf::IntRect sprite_size(0, 0, 80, 80);
    sf::Sprite sprite(texture, sprite_size), sprite2(texture2);
    //sprite.setPosition(400, 634);
    sprite.setPosition(445, 574-80);
    //sprite2.setPosition(0, 462);
    sprite2.setPosition(0, 0);

    window.setFramerateLimit(15);
    //window.setKeyRepeatEnabled(false); //if it's true then holding down jump key
                                         //cause the player to constantly keep jumping.
    int velocity = 12, animatin_change_time = 75;
    float jump_animation_time = velocity - 0;
    bool iskeypressed;
    bool left = false, right = true, jump = false, inair = false;

    //current maximum distance covered while jumping is 125 pixels

    sf::Clock clock;
    int elapsed_time;

    while(window.isOpen())
    {
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
            if(velocity==0)
                inair = false;
            if(sprite_size.top!=160)
            {
                sprite_size.top=160;
            }
            if(right)
            {
                if(velocity>=jump_animation_time)
                    sprite_size.left=80;
                else if(velocity<jump_animation_time)
                    sprite_size.left=160;
            }
            else if(left)
            {
                if(velocity>=jump_animation_time)
                    sprite_size.left=480;
                else if(velocity<jump_animation_time)
                    sprite_size.left=560;
            }

            sprite.setTextureRect((sprite_size));

            sprite.move(0, -(velocity--));
            if(sprite.getPosition().y+80==714 && !inair)
            {
                jump = false;
                velocity=12;
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
        window.clear();
        window.draw(sprite2);
        window.draw(sprite);
        window.display();
    }


    return 0;
}
