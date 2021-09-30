#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <conio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <windows.h>

using sf::RectangleShape;

/* Ball Class */
class Ball : public sf::Sprite
{

private:

    float speed = 0.05f;     // speed of falling or rising
    float mod = 0.05f;       // modifier
    
public:
    float rotation = 0, D = 0;      // rotation modifier and horizontal axis modifier
    unsigned int jump_counter = 0;  // score
    bool is_jumping = false;        
    
    void update(const RectangleShape& R, const RectangleShape& W1, const RectangleShape& W2);      // update ball position 
    void reset(void);                                                               // reset ball position to the default 
    void jump(void);                                                                // jump after ball onlick 
    void checkIfWallHit(const RectangleShape& W1, const RectangleShape& W2);                  // checks if wall got hit
    bool checkIfOnClicked(const Ball& ball, const sf::Vector2i& mouseposition);     // checks if the ball got onclicked
};


#endif