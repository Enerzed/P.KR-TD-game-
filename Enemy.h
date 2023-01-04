#pragma once
#include "Entity.h"

class Enemy :
    public Entity
{
public:
	Enemy(Image& myImage, String myName, Level& myLevel, float myX, float myY, int myWidth, int myHeight) :Entity(myImage, myName, myX, myY, myWidth, myHeight)
	{
		obj = myLevel.GetObjects("tower");
		if (name == "Enemy")
		{
			sprite.setTextureRect(IntRect(0, 0, width, height));
			dx = 0.1;
		}
	}
	void checkCollisionsWithMap(float myDx, float myDy)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "tower")
				{
					if (myDy > 0) { y = obj[i].rect.top - height;  dy = 0; onGround = true; }
					if (myDy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (myDx > 0) { x = obj[i].rect.left - width;  dx = -0.1; sprite.scale(-1, 1); }
					if (myDx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
				}
			}
	}
	void update(float time)
	{
		if (name == "Enemy") {
			checkCollisionsWithMap(dx, 0);
			x += dx * time;
			sprite.setPosition(x + width / 2, y + height / 2);
			if (health <= 0) { life = false; }
		}
	}
};

