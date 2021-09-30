#pragma once

#include <Engine.h>

struct RectangleShape;

class Ball : public En::Sprite
{
private:
	float m_Speed = 0.05f;
	float m_Mod = 0.05f;
public:
    float m_Rotation = 0, m_D = 0;      
    unsigned int m_JumpCounter = 0;
    bool m_IsJumping = false;

private:
    void Move(float x, float y);

public:

    void Update(const RectangleShape& W1, const RectangleShape& W2);
    void Reset(void);                                                               
    void Jump(void);   
    void CheckIfWallHit(const RectangleShape& W1, const RectangleShape& W2);    
    bool IsBallClicked(void);
};
