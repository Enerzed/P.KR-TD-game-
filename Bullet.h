#pragma once
#include "Entity.h"
#include "Enemy.h"

class Bullet :
    public Entity
{
protected:
    float targetX, targetY;
    float vX, vY, distanse;
public:
    Bullet(Image& myImage, String myName, Level &myLevel, float myX, float myY, int myWidth, int myHeight, float myTargetX, float myTargetY) : Entity(myImage, myName, myX, myY, myWidth, myHeight)
    {
        obj = myLevel.GetObjects("wall");
        setX(myX);
        setY(myY);
        setSpeed(0.5);
        setWidth(16);
        setHeight(16);
        setLife(true);
        distanse = sqrt((targetX - x) - (targetY - y));
        vX = (targetX - x) / 100;
        vY = (targetY - y) / 100;
    }
    void update(float time)
    {
        x += vX * time * speed;
        y += vY * time * speed;
        if (x <= 0)
            x = 1;
        if (y <= 0)
            y = 1;
        for (int i = 0; i < obj.size(); i++)
        {
            if (getRect().intersects(obj[i].rect))
            {
                life = false;
            }
        }

        sprite.setPosition(x + width / 2, y + height / 2);
    }
};

