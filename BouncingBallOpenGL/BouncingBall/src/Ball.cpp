#include "Ball.h"
#include "Utility.h"

void Ball::Move(float x, float y)
{
    SetPosition({ GetPosition().x + x,
                  GetPosition().y + y });
}

void Ball::Update(const RectangleShape& W1, const RectangleShape& W2)
{
    if (m_D == 0)
        m_Rotation /= 1.01f;

    if (m_Speed < 0) // rising up
    {
        if (m_D > -0.5 && m_D < 0.5)
        {
            m_Speed /= 1.02f;
            Move(0, m_Speed);
            m_Speed += m_Mod;
        }
        else
        {
            m_Speed /= 1.02f;
            Move(m_D, m_Speed);
            m_Speed += m_Mod;
        }

    }
    else //is falling down
    {
        m_Speed *= 1.002f;
        if (m_D > -0.5 && m_D < 0.5)
        {
            Move(0, m_Speed);
            m_Speed += m_Mod;
        }
        else
        {
            Move(m_D, m_Speed);
            m_Speed += m_Mod;
        }
    }

    this->CheckIfWallHit(W1, W2);
    this->m_Rotation /= 1.0005f;
    Rotate(m_D);
}


void Ball::CheckIfWallHit(const RectangleShape& W1, const RectangleShape& W2)
{
    if (GetPosition().x - 43 <= W1.GetPosition().x)
    {
        m_D *= -1;
        SetPosition({ 43, GetPosition().y });
    }
    else if (GetPosition().x + 43 >= W2.GetPosition().x + 2)
    {
        m_D *= -1;
        SetPosition({ 407, GetPosition().y });
    }
}


void Ball::Reset(void)
{
    m_D = 0;
    m_Rotation = 0;
    SetPosition({ GetPosition().x, 100 });
    m_Speed = 0.05f;
    m_Mod = 0.05f;
    SetPosition({ 450 / 2.0f, 150 });
}

void Ball::Jump(void)
{
    m_Mod = 0.1f;

    if (m_Speed >= 0) // is falling
    {
        m_Speed += 5;
        m_Speed *= -1;
    }
    else // is rising up
        m_Speed -= 2;
}

bool Ball::IsBallClicked(void)
{
    glm::vec2 mousePos = En::Input::GetMousePosition();
    glm::vec2 ballPos = GetPosition();

    double X = abs(ballPos.x - mousePos.x);
    double Y = abs(ballPos.y - mousePos.y);
    double d = sqrt(X * X + Y * Y);

    if (d > 43)  // not clicked
        return false;
    else        // clicked
    {
        // setting up new horizontal speed accordingly to the cursor distance 
        // from the vertical axis of symmetry of the ball
        if (ballPos.x - mousePos.x > 0)
            m_D = ballPos.x - mousePos.x;     
        else if (ballPos.x - mousePos.x < 0)
            m_D = ballPos.x - mousePos.x;
        m_D /= 7.0f;              

        if (ballPos.x - mousePos.x > 0) // cliked at the left side of the center
        {
            if (m_D < -0.5 || m_D>0.5)
            {
                if (m_Rotation < 3) m_Rotation++;   // rotation incrementation, maximally to 3
            }
            else
                m_D = 0;                      // if it got clicked nearby to the center, there is no rotation added
        }
        else // /clicked at the right side of the center
        {
            if (m_D < -0.5 || m_D>0.5)
            {
                if (m_Rotation > -3)
                    m_Rotation--;  // rotation decrementation, not less than -3
            }
            else
                m_D = 0;                      // if it got clicked nearby to the center, there is no rotation added
        }
        return true;
    }
}