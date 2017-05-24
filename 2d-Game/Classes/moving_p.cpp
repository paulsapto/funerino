#include "moving_p.h"


moving_p::moving_p(const std::string &name, float nX, float nY,float vel, float vx, float vy) : 
	Sprite_B(name, nX, nY, vel),
	velocity(vx,vy) {
	cocos2d::Point pos = Sprite_B::getSprite()->getPosition();
	cocos2d::Vec2 incr = getVelocity();
	cocos2d::MoveTo* moveTo2 = cocos2d::MoveTo::create(2*(vx/vy), cocos2d::Vec2(pos.x+incr.x, pos.y-incr.y));
	cocos2d::MoveTo* moveTodiff2 = 
		cocos2d::MoveTo::create(2*(vx/vy), cocos2d::Vec2(pos.x-incr.x, pos.y+incr.y));
	cocos2d::Sequence* new_sequence2 = cocos2d::Sequence::create(moveTo2, moveTodiff2, NULL);
	Sprite_B::getSprite()->runAction(cocos2d::RepeatForever::create(new_sequence2));
}

void moving_p::update(float speed) {

}
 
 
