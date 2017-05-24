#include <iostream>
#include "hh.h"

hh::hh(const std::string& nameI, int noFrames, base* hero0, cocos2d::Layer *layerI) 
		: name(nameI), hero(hero0), firing(false), layer(layerI) {
	 
	std::string plistName = name + ".plist";	
	cocos2d::SpriteFrameCache::
		getInstance()->addSpriteFramesWithFile(plistName.c_str());
	std::string filename = name + "%ld.png";	
	cocos2d::Vector<cocos2d::SpriteFrame*>
		frames = getFrames(filename.c_str(), 1, 10);
	sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
	sprite->setPosition((rand() % 400 + 2000), 110);	
	sprite->setScaleX(-1);
	walkAnim = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/15);
	walkAnim->retain();
	
	frames = getFrames(filename.c_str(), 12, 18);
	fireS = cocos2d::Sprite::createWithSpriteFrame(frames.front());
	fireS->setPosition(sprite->getPositionX() - 20, 110);
	fireS->setScaleX(-1);
	fireS->retain(); 
	
	spitFire = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/10);
	spitFire->retain();

	sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(walkAnim)));

}

void hh::fire() {
        layer->addChild(fireS);	
	fireS->release();
	cocos2d::FiniteTimeAction* walk = cocos2d::CallFunc::create([this]() { this->walk(); }); 
	fireS->runAction(cocos2d::Sequence::create(cocos2d::Animate::create(spitFire),
		walk, NULL));

}

void hh::walk() {
	fireS->retain(); 
	layer->removeChild(fireS);
	firing = false;

}

	
void hh::update(float dt) {
dt = 10;
    cocos2d::Vec2 pos = sprite->getPosition(); 
    cocos2d::Vec2 heropos = hero->getSprite()->getPosition(); 

    if(pos.x - heropos.x <= 150 && !firing){
	firing = true; 
	fire(); 
    }

    if(firing) {
	multi_sprite* guy = static_cast<multi_sprite*>(hero);
	if(collided() && !guy->getJumping()) {
		//hero->getSprite()->retain();
		//layer->removeChild(hero->getSprite());
	}
    }


    
    if(sprite->getPositionX() < 0) {
   	sprite->setPosition((rand() % 400 + 2000), 110);
	fireS->setPosition(sprite->getPositionX() - 100, 110);
    }
    else {	
	sprite->setPosition(sprite->getPositionX() - 4, 110); 
	fireS->setPosition(sprite->getPositionX() - 100, 110);
    }
}

cocos2d::Vector<cocos2d::SpriteFrame*> 
hh::getFrames(const char *format, int start, int end) {
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


bool hh::collided() {
	cocos2d::Point myPos = sprite->getPosition();
	cocos2d::Point oPos = fireS->getPosition();
	float x = myPos.x-oPos.x, y = myPos.y-oPos.y;
	float distance = hypot(x,y);
	float radii = fireS->getContentSize().width/2 + sprite->getContentSize().width/2;
	return distance<radii ;
}
