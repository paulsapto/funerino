#ifndef __MANLY_H__
#define __MANLY_H__

#include "cocos2d.h"
#include "hh.h"
#include "Sprite_B.h"
#include "moving_p.h"


#include "base.h"
#include <list>
#include "SimpleAudioEngine.h"



class Manly : public cocos2d::Layer {
public:
	~Manly();
	Manly() : score(0) {} 
	void update(float);
  static cocos2d::Scene* createScene();
  virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
  CREATE_FUNC(Manly);
	int scrollSpeed = 1; 
private:
	std::list<base *> hellHounds; 
	cocos2d::Label *scoreL;
	int score; 
	std::list<base *> sprite;
	cocos2d::Vector<cocos2d::SpriteFrame*>
		getAnimation(const char *format, int count);
	cocos2d::Sprite* lava_back1;
	cocos2d::Sprite* lava_back2;
	cocos2d::Sprite* p_1;
	cocos2d::Sprite* p_2;
};

#endif // __MANLY_H__
