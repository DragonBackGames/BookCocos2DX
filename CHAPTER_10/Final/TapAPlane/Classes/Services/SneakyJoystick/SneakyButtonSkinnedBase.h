#ifndef __SNEAKY_BUTTON_SKINNED_H__
#define __SNEAKY_BUTTON_SKINNED_H__

#include "SneakyButton.h"

USING_NS_CC;

class SneakyButtonSkinnedBase : public cocos2d::Layer 
{
	CC_SYNTHESIZE_READONLY(Sprite *, defaultSprite, DefaultSprite);
	CC_SYNTHESIZE_READONLY(Sprite *, activatedSprite, ActivatedSprite);
	CC_SYNTHESIZE_READONLY(Sprite *, disabledSprite, DisabledSprite);
	CC_SYNTHESIZE_READONLY(Sprite *, pressSprite, PressSprite);

	CC_SYNTHESIZE_READONLY(SneakyButton *, button, Button); //Not sure about this

	//Public methods
	CREATE_FUNC(SneakyButtonSkinnedBase);
	virtual ~SneakyButtonSkinnedBase();
	bool init();
	void watchSelf(float delta);
	void setContentSize(Size s);
	void setDefaultSprite(Sprite *aSprite);
	void setActivatedSprite(Sprite *aSprite);
	void setDisabledSprite(Sprite *aSprite);
	void setPressSprite(Sprite *aSprite);
	void setButton(SneakyButton *aButton);
};

#endif
