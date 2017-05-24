#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>
#include "cocos2d.h"

class base {
public:
	virtual cocos2d::Sprite* getSprite() const = 0;
	virtual void update(float)=0;
	virtual ~base() {};
};

#endif
