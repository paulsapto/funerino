#include <iostream>
#include "Sprite_B.h"

Sprite_B::Sprite_B(const std::string & name, float newX, float newY, float vel ) :
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  origin( cocos2d::Director::getInstance()->getVisibleOrigin() ),	
	sprite(cocos2d::Sprite::create(name)),
	velocity(vel)
{		
	sprite->setPosition(cocos2d::Point(newX, newY));
	
}

void Sprite_B :: update (float x) {
  
	cocos2d::Vec2 position=sprite->getPosition();
	sprite->setPosition(position.x-velocity, position.y);
	if(sprite->getPositionX() <= -150)  sprite->setPosition(1600, position.y);  

}
