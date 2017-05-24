#ifndef _SPRITE__H
#define _SPRITE__H
#include "cocos2d.h"
#include <string>
#include "base.h"


class Sprite_B : public base {
public:
	Sprite_B(const std::string &, float, float, float);
	~Sprite_B() {};

	void update(float); 
	cocos2d::Point getOrigin()  const { return origin; }
	cocos2d::Size getViewSize() const { return viewSize; }
	cocos2d::Sprite *getSprite() const { return sprite; }

      
private:
 	cocos2d::Size viewSize;
 	cocos2d::Point origin;
 	cocos2d::Sprite* sprite;
	float velocity;
 	
};
#endif
