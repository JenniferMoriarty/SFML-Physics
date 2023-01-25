// A simple jumper program
#include<iostream>
using namespace std;
#include "SFML/Graphics.hpp"

int main() {

    //game set up----------------------------------------------------------------------
    sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Simple Jumper"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    renderWindow.setFramerateLimit(FPS); //set FPS

    //player setup----------------------------------------------------------------------
    sf::RectangleShape player(sf::Vector2f(30, 30));//size of player (30x30 square)
    player.setFillColor(sf::Color::White);
    float xpos = 25;
    float ypos = 25;
    player.setPosition(xpos, ypos); //set position: this is where the top left corner will be
    //player velocity
    float vx = .0;
    float vy = .0;
    bool isOnGround = false; //needed to apply gravity
    bool keys[] = { false, false, false, false };

    //platform 1 set up----------------------------------------------------------------------
    sf::RectangleShape platform1(sf::Vector2f(100, 30)); //size of platform (100 x 30 rectangle)
    platform1.setFillColor(sf::Color::Red);
    platform1.setPosition(100, 700);

    //TODO: Add more platforms here!

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (renderWindow.isOpen()) {//keep window open until user shuts it down 

        while (renderWindow.pollEvent(event)) { //input section-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) keys[2] = true;
            else keys[2] = false;
            
       
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) keys[0] = true;
            else keys[0] = false;
          
            //TODO: add left movement here

        }//end event loop---------------------------------------------------------------

        //physics-----------------------------------------------------------------------
        
        //jumping
        if (keys[2] == true) 
            if (isOnGround == true) {
                vy = -15;
                isOnGround = false;
            }

        //right movement
        if (keys[0] == true)
            vx = 8;
        else
            vx = 0;

        //TODO: alter the above code to handle left movement too!

        //GRAVITY
        if (ypos + 30 > 800) {//check if we've reached the bottom of the screen
            isOnGround = true;
            ypos = 800 - 30; //reset position so feet are on ground
        }
        else
            isOnGround = false;

        //apply gravity if not on ground
        if (isOnGround == false) {
            vy += 1; //notice we're ACCELERATING (set equal for steady falling pace)
            if (vy > 5) //set TERMINAL VELOCITY
                vy = 5;
        }

        //FRICTION-----------------------------------------------------------------------
        if (isOnGround == true)
            vx *= .85;
        else
            vx *= .95; //less friction in the air



        //Collide with platform 1-----------------------------------------------------
        if (ypos + 30 >= 700 && ypos <= 700 + 30 && xpos + 30 >= 100 and xpos <= 200) {
            isOnGround = true;
            ypos = 700 - 30; //counteract gravity
        }
        //TODO: add more collision checks with the other platforms you make

        //actually move the player!---------------------------------------------------------
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);
        cout << "speed is" << vy << endl;
        //cout << "isOnGround is " << isOnGround << endl; //for testing purposes
        //cout << "player x and y are " << xpos << " , " << ypos << endl;

        clock.restart();
        //render section-----------------------------------------
        renderWindow.clear(); //wipes screen, without this things smear 
        renderWindow.draw(player); //you gotta drew each object
        renderWindow.draw(platform1); //you gotta drew each object
        renderWindow.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end game
