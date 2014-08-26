#ifndef __JOYSTICK_SKINNED_H__
#define __JOYSTICK_SKINNED_H__

#include "cocos2d.h"
#include "SneakyJoystick.h"

USING_NS_CC;

class SneakyJoystickSkinnedBase : public cocos2d::Layer
{
public:
	CC_SYNTHESIZE_READONLY(Sprite *, backgroundSprite, BackgroundSprite);
	CC_SYNTHESIZE_READONLY(Sprite *, thumbSprite, ThumbSprite);
	CC_SYNTHESIZE_READONLY(SneakyJoystick *, joystick, Joystick);	

	//Public methods
	CREATE_FUNC(SneakyJoystickSkinnedBase);
	virtual ~SneakyJoystickSkinnedBase();
	bool init();
	void updatePositions(float delta);
	void setContentSize(Size s);
	void setBackgroundSprite(Sprite *aSprite);
	void setThumbSprite(Sprite *aSprite);
	void setJoystick(SneakyJoystick *aJoystick);
};
#endif