#include <iostream>
#include <ctime>
#include "Manly.h"

Manly::~Manly() {
	std::list<base*>::iterator ptr = sprite.begin();
	while (ptr != sprite.end()) {
		delete (*ptr);
	++ptr;
	}
}

float get_randVel() {
  float x = rand() % 100 + 50;
  
  return x;
}
float get_randPosx() {
	float x = rand() % 550 +100;
	return x;
}
	
float get_randPosy() {
	float y = rand() % 700 + 300;
	return y;
}	 

void Manly::update(float dt) {
	
  lava_back1->setPositionX(lava_back1->getPositionX()-scrollSpeed/1.5);
  lava_back2->setPositionX(lava_back2->getPositionX()-scrollSpeed/1.5);

  if (lava_back1->getPositionX() < -lava_back1->getContentSize().width/2) {
    lava_back1->setPositionX( lava_back2->getPositionX() + lava_back2->getContentSize().width);
  }
  if (lava_back2->getPositionX() < -lava_back2->getContentSize().width/2) {
    lava_back2->setPositionX(lava_back1->getPositionX() + lava_back1->getContentSize().width);
  }

  p_1->setPositionX(p_1->getPositionX()-scrollSpeed*4);
  p_2->setPositionX(p_2->getPositionX()-scrollSpeed*4);

  if (p_1->getPositionX() < -p_1->getContentSize().width/2) {
    p_1->setPositionX( p_2->getPositionX() + p_2->getContentSize().width);
  }
  if (p_2->getPositionX() < -p_2->getContentSize().width/2) {
    p_2->setPositionX(p_1->getPositionX() + p_1->getContentSize().width);
  }
	
	score++;
	std::list<base*>::iterator ptr = sprite.begin();
	while (ptr != sprite.end()) {
		float dt = rand() % 15 + 3;
		(*ptr)->update(dt);
		++ptr;
	}
	ptr = hellHounds.begin();
	while (ptr != hellHounds.end()) {
		float dt = rand() % 15 + 3;
		(*ptr)->update(dt);
		++ptr;
	}
	if(score%10==0)
	scoreL->setString(std::to_string(score));
}

cocos2d::Scene* Manly::createScene() {
  cocos2d::Scene* scene = cocos2d::Scene::create();
  Manly* layer = Manly::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool Manly::init() {
	if ( !Layer::init() ) {
    return false;
  }
	srand(time(NULL));
	cocos2d::Size visibleSize = 
		cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = 
		cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::MenuItemImage* closeItem = 
		cocos2d::MenuItemImage::create("CloseNormal.png","CloseSelected.png",
											CC_CALLBACK_1(Manly::menuCloseCallback, this));
    
	closeItem->setPosition(cocos2d::Vec2(origin.x + 
		visibleSize.width - closeItem->getContentSize().width/2 ,
    origin.y + closeItem->getContentSize().height/2));

	cocos2d::Menu* menu = cocos2d::Menu::create(closeItem, NULL);
  menu->setPosition(cocos2d::Vec2::ZERO);
  addChild(menu, 1);
  
	cocos2d::Label* label = 
		cocos2d::Label::createWithTTF("Paul and Evan's animation", "fonts/Marker Felt.ttf", 24);
	label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));
		
	addChild(label, 1);

	lava_back1 = cocos2d::Sprite::create("lava_background.png");
	
	lava_back1->setPosition(0, visibleSize.height/2);
	addChild(lava_back1, -1);
	lava_back2 = cocos2d::Sprite::create("back2.png");
	addChild(lava_back2, -1);
	
	lava_back2->setPosition(lava_back1->getContentSize().width-1, 
																				visibleSize.height/2);

	p_1 = cocos2d::Sprite::create("main_platform.png");
	
	p_1->setPosition(0, 0);
	addChild(p_1, 1);
	p_2 = cocos2d::Sprite::create("main_platform.png");
	addChild(p_2, 1);
	
	p_2->setPosition(p_1->getContentSize().width-1, 0);

	base *fly_p1 = new Sprite_B("fly_p.png", 522, (visibleSize.height/2+origin.y),1.2f);
	sprite.push_back(fly_p1);
	addChild(fly_p1->getSprite(),2);

	base *fly_p2 = new Sprite_B("fly_p.png", 600, ((visibleSize.height/2+origin.y)+100),0.7f);
	sprite.push_back(fly_p2);
	addChild(fly_p2->getSprite(),1);
	fly_p2->getSprite()->setScale(0.5f);
 	
	base *fly_p3 = new Sprite_B("fly_p.png", 600, ((visibleSize.height/2+origin.y)+200),0.9f);
	sprite.push_back(fly_p3);
	addChild(fly_p3->getSprite(),1);
	fly_p3->getSprite()->setScale(0.8f);	

	std::srand (std::time (0));
		
	base *mov_1 = new moving_p("moving_platform.png",get_randPosx(),250, 2, get_randVel(), get_randVel());
	sprite.push_back(mov_1);
	addChild(mov_1->getSprite(), 4);
	
	base *mov_2 = new moving_p("moving_platform.png", 500,350, 2,get_randVel(), get_randVel());
	sprite.push_back(mov_2);
	addChild(mov_2->getSprite(), 4);

	base *mov_3 = new moving_p("moving_platform.png", 800, 400, 2, 400, 0);
	sprite.push_back(mov_3); 
	addChild(mov_3->getSprite(), 4);

	base *hero = new multi_sprite("hero",15, cocos2d::Point(400,110));
	sprite.push_back(hero);
	addChild(hero->getSprite(), 4);
	
	for(int k = 0; k < 2; k++) {
	  base *hell = new hh("Hell", 4, hero, this);
	  hellHounds.push_back(hell); 
	  addChild(hell->getSprite(), 4); 

	}

	scoreL = 
		cocos2d::Label::createWithTTF(std::to_string(score), "fonts/Marker Felt.ttf", 24);
	scoreL->setAlignment(cocos2d::TextHAlignment::CENTER);
	addChild(scoreL, 1);
	scoreL->setPosition(cocos2d::Vec2(850, 700));
	

	schedule( schedule_selector(Manly::update));//this
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("battle.mp3");
  return true;
}


void Manly::menuCloseCallback(Ref* pSender) {
	cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
