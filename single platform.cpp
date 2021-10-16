// A simple jumper program
#include<iostream>
using namespace std;
#include "SFML/Graphics.hpp"

int main() {

    //game set up 
    sf::RenderWindow renderWindow(sf::VideoMode(800,800), "Simple Jumper"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    renderWindow.setFramerateLimit(FPS); //set FPS
 
    //player setup----------------------------------------------------------------------
    sf::RectangleShape player(sf::Vector2f(30, 30));//size of player (30x30 square)
    player.setFillColor(sf::Color::White); 
    float playerX = 25;
    float playerY = 25;
    player.setPosition(playerX, playerY); //set position: this is where the top left corner will be
    //player velocity
    float pVelx = .0;
    float pVely = .0;
    bool isOnGround = false; //needed to apply gravity

    //platform 1 set up----------------------------------------------------------------------
    sf::RectangleShape platform1(sf::Vector2f(100, 30)); //size of platform (100 x 30 rectangle)
    platform1.setFillColor(sf::Color::Red); 
    platform1.setPosition(100, 700); 

    //TODO: Add more platforms here!

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (renderWindow.isOpen()) {//keep window open until user shuts it down 
   
        while (renderWindow.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();

            //KEYBOARD INPUT 
            //code note: I'm not sure why this slows down when the mouse moves, 
            //or why it works better when this is in the event loop and the other input is not :/

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //checks if "W" is pressed
                if (isOnGround == true) { //turns off flying
                    pVely = -15;
                    isOnGround = false;
                }
            }
            else
                pVely = 0;
                       
        }//end event loop---------------------------------------------------------------

        //More keyboard input-----------------------------------------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //checks if "D" is pressed
            pVelx = 8;
        }
        //TODO: add left movement here


        //GRAVITY----------------------------------------------------------------------
        if (playerY + 30 > 800) {//check if we've reached the bottom of the screen
            isOnGround = true;
            playerY = 800 - 30; //reset position so feet are on ground
        }
        else
            isOnGround = false;

        //apply gravity if not on ground
        if (isOnGround == false) {
            pVely += .4; //notice we're ACCELERATING (set equal for steady falling pace)
            if (pVely > 5) //set TERMINAL VELOCITY
                pVely = 5;
        }
        
        //FRICTION-----------------------------------------------------------------------
        if (isOnGround == true)
            pVelx *= .85;
        else
            pVelx *= .95; //less friction in the air



        //Collide with platform 1-----------------------------------------------------
        if (playerY+30 >= 700 && playerY <= 700 + 30 && playerX+30 >= 100 and playerX <= 200) {
            isOnGround = true;
            playerY = 700 - 30; //counteract gravity
        }
        //TODO: add more collision checks with the other platforms you make

        //actually move the player!---------------------------------------------------------
        playerX += pVelx;
        playerY += pVely;
        player.setPosition(playerX, playerY);
        //cout << "isOnGround is " << isOnGround << endl; //for testing purposes
        cout << "player x and y are " << playerX << " , " << playerY << endl;

        clock.restart();
        //render section-----------------------------------------
        renderWindow.clear(); //wipes screen, without this things smear 
        renderWindow.draw(player); //you gotta drew each object
        renderWindow.draw(platform1); //you gotta drew each object
        renderWindow.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end game
