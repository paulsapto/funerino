#ifndef _MULTI_SPRITE_H__
#define _MULTI_SPTITE_H__

#include <string>
#include "cocos2d.h"
#include "Sprite_B.h"

class multi_sprite : public base {
	public :
	multi_sprite(const std::string& , int , cocos2d::Point);
	cocos2d::Sprite* getSprite()const { return sprite;}
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void jump();
	void run();
	void update(float);
	bool getJumping()const { return jumping;}
	private:
	bool jumping;
	cocos2d::EventListenerTouchOneByOne *listener; 
	std::string name; 
	cocos2d::Sprite* sprite;
	cocos2d::Animation* runAnim;
	cocos2d::Animation* jumpAnim;
	cocos2d::Vector<cocos2d::SpriteFrame*> getFrames(const char *, int, int);
};
#endif
	
