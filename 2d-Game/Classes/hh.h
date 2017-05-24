#ifndef _MULTI_SPRITE_H__
#define _MULTI_SPTITE_H__
#include <string>
#include "cocos2d.h"
#include "Sprite_B.h"
#include "multi_sprite.h"
#include <cmath>

class hh : public base {
	public:
	~hh() { delete hero; } 
	hh(const std::string& , int, base*, cocos2d::Layer *layer);
	cocos2d::Sprite* getSprite()const { return sprite;}
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void update(float);
	void fire(); 
	void walk(); 
	bool collided();

	
	private:
	bool firing; 
	base* hero; 
	cocos2d::EventListenerTouchOneByOne *listener; 
	std::string name; 
	cocos2d::Layer* layer;
	cocos2d::Sprite* fireS; 
	cocos2d::Sprite* sprite;
	cocos2d::Animation* walkAnim;
	cocos2d::Animation* spitFire;
	cocos2d::Vector<cocos2d::SpriteFrame*> getFrames(const char *, int, int);
};
#endif
	
