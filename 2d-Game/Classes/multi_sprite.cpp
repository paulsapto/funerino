#include <iostream>
#include "multi_sprite.h"

multi_sprite::multi_sprite(const std::string& nameI, int noFrames, cocos2d::Point pos) : name(nameI) {
	jumping = false;  
	std::string plistName = name + ".plist";
	cocos2d::SpriteFrameCache::
		getInstance()->addSpriteFramesWithFile(plistName.c_str());
	std::string filename = name + "%ld.png";
	cocos2d::Vector<cocos2d::SpriteFrame*>
		frames = getFrames(filename.c_str(), 1, 10);
	sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
	sprite->setPosition(pos);
	
	//set run animation
	runAnim = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/15);
	runAnim->retain(); 
	//set jump animation
	frames = getFrames(filename.c_str(), 10, 15);
	jumpAnim = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/4);
	jumpAnim->retain();

	sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(runAnim)));
	listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(multi_sprite::onTouchBegan, this); 
	listener->onTouchEnded = CC_CALLBACK_2(multi_sprite::onTouchEnded, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->
	  addEventListenerWithSceneGraphPriority(listener, sprite); 
}

bool multi_sprite::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){	
	jumping = true; 
	return true; 
}

void multi_sprite::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
	jumping = false;  
}

void multi_sprite::run() {
	sprite->stopAllActions();
	sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(runAnim)));
	sprite->setPosition(400,110);
}


void multi_sprite::jump() {
	sprite->stopAllActions();
	cocos2d::JumpBy* jump = cocos2d::JumpBy::create(1.5, cocos2d::Vec2(0,0), 150, 1);
	cocos2d::Spawn* spawn = cocos2d::Spawn::createWithTwoActions(jump, cocos2d::Animate::create(jumpAnim));
	cocos2d::FiniteTimeAction* run = cocos2d::CallFunc::create([this]() { this->run(); }); 
	cocos2d::Sequence* sequence = cocos2d::Sequence::create(spawn, run, NULL);
	sprite->runAction(sequence);	
}

void multi_sprite::update(float dt) {
dt = 10;

  if(jumping) {
	jump();
        jumping = false;  
  }
}

cocos2d::Vector<cocos2d::SpriteFrame*> 
multi_sprite::getFrames(const char *format, int start, int end) {
  cocos2d::SpriteFrameCache* 
  spritecache = cocos2d::SpriteFrameCache::getInstance();
  cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
  char str[100];
  while(start <= end) {
    sprintf(str, format, start);
    animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    start++;
  }
  return animFrames;
}
