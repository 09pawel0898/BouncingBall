#include "ball.hpp"

/* rotates, moves and checks for collision */
void Ball::update(const RectangleShape& R, const RectangleShape& W1, const RectangleShape& W2)
{
    if (this->D == 0)
        this->rotation /= 1.01f;
    
    if (this->speed < 0) //is rising up
    {
        if (this->D > -0.5 && this->D < 0.5)
        {
            this->speed /= 1.02f;
            this->move(0, this->speed);
            this->speed += this->mod;
        }
        else if (this->D < -0.5)
        {
            this->speed /= 1.02f;
            this->move(this->D, this->speed);
            this->speed += this->mod;
        }
        else
        {
            this->speed /= 1.02f;
            this->move(this->D, this->speed);
            this->speed += this->mod;
        }

    }
    else //is falling down
    {
        this->speed *= 1.002f;
        if (this->D > -0.5 && this->D < 0.5)
        {
            this->move(0, this->speed);
            this->speed += this->mod;
        }
        else if (D < -0.5)
        {
            this->move(this->D, this->speed);
            this->speed += this->mod;
        }
        else
        {
            this->move(this->D, this->speed);
            this->speed += this->mod;
        }
    }

    this->checkIfWallHit(W1, W2);
    this->rotation /= 1.0005f;
    this->rotate(this->D);
}

/* checks if ball is hitting one of the walls */
void Ball::checkIfWallHit(const RectangleShape& W1, const RectangleShape& W2)
{
    if (this->getPosition().x - 43 <= W1.getPosition().x)
    {
        this->D *= -1;
        this->setPosition(43, this->getPosition().y);
    }
    else if (this->getPosition().x + 43 >= W2.getPosition().x + 2)
    {
        this->D *= -1;
        this->setPosition(407, this->getPosition().y);
    }
}

/* sets the default position for the ball*/
void Ball::reset(void)
{
    this->D = 0;
    this->rotation = 0;
    this->setPosition(this->getPosition().x, 100);
    this->speed = 0.05f;
    this->mod = 0.05f;
    this->setPosition(450 / 2.0f, 150);
}

/* jump after onclick*/
void Ball::jump(void)
{

    this->mod = 0.1f;

    if (this->speed >= 0) //spada
    {
        this->speed += 5;
        this->speed *= -1;
    }
    else
    {
        this->speed -= 2;
    }
}

/* controls all actions after ball onclick, starting from onclick by itself through setting up new speed and rotation, both depends on the distance 
from the cursor to the center of the ball */
bool Ball::checkIfOnClicked(const Ball& ball, const sf::Vector2i& mouseposition)
{
    float mx, my, bx, by;
    double d = 0;  // distance from the cursor to the ball center
    double X, Y;
    mx = (float)mouseposition.x;
    my = (float)mouseposition.y;
    bx = (float)ball.getPosition().x;
    by = (float)ball.getPosition().y;
    X = abs(bx - mx);
    Y = abs(by - my);
    d = sqrt(X * X + Y * Y);

    /* if the ball is onclicked */
    if (d > 43)  // its not
        return false;
    else        // it is
    {
        if (bx - mx > 0)                
            this->D = bx - mx;          // setting up new horizontal speed accordingly to the cursor distance from the vertical axis of symmetry of the ball
        else if (bx - mx < 0)
            this->D = bx - mx;
        this->D /= 7.0f;                // dividing by 7 in order to slow down the ball

        /* checks for wchich side the ball should be rotating */
        if (bx - mx > 0) // cliked at the left side of the center
        {
            if (this->D < -0.5 || this->D>0.5)
            {
                if (this->rotation < 3) this->rotation++;   // rotation incrementation, maximally to 3
            }
            else
                this->D = 0;                      // if it got clicked nearby to the center, there is no rotation added
        }
        else // /clicked at the right side of the center
        {
            if (this->D < -0.5 || this->D>0.5)
            {
                if (this->rotation > -3)this->rotation--;  // rotation decrementation, not less than -3
            }
            else
                this->D = 0;                      // if it got clicked nearby to the center, there is no rotation added
        }
        return true;
    }
}