#include<SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <sstream>


int main()
{
    sf::RenderWindow App(sf::VideoMode(800,800),"Test");
    App.setFramerateLimit(60);
    App.setKeyRepeatEnabled(false);

    sf::Event event;
    //states
    bool play = true;
    bool up = false;
    bool down = false;
    
    //variables
    int y_pad1=0,x_ball=-5,y_ball=-5;
    int y_pad2=0;
    int score_pad1=0,score_pad2=0;
    
    
    //font
    sf::Font font;
    if( font.loadFromFile("/Users/yathartharora/Game-pong/data/arial.ttf") == 0) return 1;
    
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    //score.setColor(sf::Color::Red);
    score.setPosition(400,10);
    score.setString("0 : 0");
    
    //Images
    sf::Texture padimage;
    sf::Texture ballimage;
    sf::Texture backimage;
    if( padimage.loadFromFile("/Users/yathartharora/Game-pong/data/pad.png") == false) return 1;
    if( ballimage.loadFromFile("/Users/yathartharora/Game-pong/data/ball.png") == false) return 1;
    if(backimage.loadFromFile("/Users/yathartharora/Game-pong/data/background.png")== false) return 1;
    
    //Soundeffect
    sf::SoundBuffer buf;
    if( buf.loadFromFile("/Users/yathartharora/Game-pong/data/hit.wav")==0) return 1;
    
    sf::Sound hit;
    hit.setBuffer(buf);
    
    
    //Shapes
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(800,800));
    background.setPosition(0,0);
    background.setTexture(&backimage);
    
    sf::RectangleShape pad1;
    pad1.setSize(sf::Vector2f(50,100));
    pad1.setPosition(50,350);
    pad1.setTexture(&padimage);
    
    sf::RectangleShape pad2;
    pad2.setSize(sf::Vector2f(50,100));
    pad2.setPosition(700,350);
    pad2.setTexture(&padimage);
    
    sf::RectangleShape ball;
    ball.setSize(sf::Vector2f(50,50));
    ball.setPosition(400,400);
    ball.setTexture(&ballimage);
    
    
    
    
    while(play==true)
    {
        
        while(App.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::W) up = true;
                if(event.key.code==sf::Keyboard::S) down = true;
                
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code==sf::Keyboard::W) up = false;
                if(event.key.code==sf::Keyboard::S) down = false;
                
            }
           
            
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X)
            {
                play = false;
            }
            
        }
        
        //Logic
        if(up==true)
        {
            y_pad1 = -10;
        }
        if(down==true)
        {
            y_pad1 = 10;
        }
        if(up==true && down==true)
        {
            y_pad1 = 0;
        }
        if(up==false && down==false)
        {
            y_pad1 = 0;
        }
      
        pad1.move(0,y_pad1);
        if(pad1.getPosition().y < 0)
        {
            pad1.setPosition(50,0);
        }
        if(pad1.getPosition().y > 700)
        {
            pad1.setPosition(50,700);
        }
        
        if(ball.getPosition().y < pad2.getPosition().y)
        {
            y_pad2 = -6;
        }
        if(ball.getPosition().y > pad2.getPosition().y)
        {
            y_pad2 = 6;
        }
        
        pad2.move(0,y_pad2);
         
        ball.move(x_ball,y_ball);
        
        if(ball.getPosition().y < 0)
        {
            y_ball = -y_ball;
        }
        if(ball.getPosition().y > 750)
        {
            y_ball = -y_ball;
        }
        if(ball.getPosition().x < -50)
        {
            score_pad2 ++;
            ball.setPosition(400,400);
        }
        if(ball.getPosition().x>750)
        {
            score_pad1++;
            ball.setPosition(400,400);
        }
        
        if(ball.getGlobalBounds().intersects(pad1.getGlobalBounds())==true)
        {
            x_ball = -x_ball;
            hit.play();
        }
        if(ball.getGlobalBounds().intersects(pad2.getGlobalBounds())==true)
        {
            x_ball = -x_ball;
            hit.play();
        }
        
        App.clear();
        App.draw(background);
        App.draw(pad1);
        App.draw(pad2);
        App.draw(ball);
        std::stringstream text;
        text << score_pad1 << " : "<< score_pad2;
        score.setString(text.str());
        App.draw(score);
        App.display();
        
    }
    
    
    
}
