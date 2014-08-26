#ifndef __CONTROL_GAME_LAYER_H__
#define __CONTROL_GAME_LAYER_H__

#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"

USING_NS_CC;

class ControlGameLayer : public Layer
{
public:
    // Destructor
    ~ControlGameLayer();
    // Create a layer
    static ControlGameLayer* create();
    // Returns state of buttons
    CC_SYNTHESIZE_READONLY(Point, stickPosition,
                           StickPosition);
    CC_SYNTHESIZE_READONLY(bool, attackButtonValue,
                           AttackButtonValue);
    
private:
    // standard Cocos2d layer method
    virtual bool init();
    // standard Cocos2d layer method
    virtual void update(float dt);
    // Click play button callback
    void clickPauseButton(Ref* sender);
    
    // Joystick
    SneakyJoystick* leftJoystick;
    // Attack button
    SneakyButton *attackButton;
    // Pause menu item
    MenuItemSprite* pauseMenuItem;
};

#endif // __CONTROL_GAME_LAYER_H__
