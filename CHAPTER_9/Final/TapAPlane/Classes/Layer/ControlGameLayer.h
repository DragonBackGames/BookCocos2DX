#ifndef __CONTROL_GAME_LAYER_H__
#define __CONTROL_GAME_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ControlGameLayer : public Layer
{
public:
    // Destructor
    ~ControlGameLayer();
    // Create a layer
    static ControlGameLayer* create();
    
private:
    // standard Cocos2d layer method
    virtual bool init();
    // standard Cocos2d layer method
    virtual void update(float dt);
    // Click play button callback
    void clickPauseButton(Ref* sender);
    
    // Pause menu item
    MenuItemSprite* pauseMenuItem;
};

#endif // __CONTROL_GAME_LAYER_H__
