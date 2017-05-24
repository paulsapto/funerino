#ifndef _MOVING_P_H_
#define _MOVING_P_H_
#include <iostream>
#include "cocos2d.h"
#include "Sprite_B.h"

class moving_p : public Sprite_B {
public:
	
	moving_p(const std::string &, float, float, float,float, float);
	cocos2d::Vec2 getVelocity() const { return velocity; }
  void setVelocity( const cocos2d::Vec2& v ) { velocity.set(v); }
  float VelX() { return velocity.x; }
  void VelX( float x ) { velocity.x = x; }
  float VelY() { return velocity.y; }
  void VelY( float y ) { velocity.y = y; }
	cocos2d::Sprite* getSprite()const { return Sprite_B::getSprite();}
	void update(float);


	
private:
	cocos2d::Vec2 velocity;
};

#endif
