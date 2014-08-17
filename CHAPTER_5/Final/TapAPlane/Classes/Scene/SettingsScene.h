#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class SettingsScene : public Layer
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(SettingsScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

private:
    // initialize sprites and other nodes for the layer
    void initNodes();
    // initialize controllers for the layer
    void initControllers();
    // Click back button callback
    void clickBackButton(Ref* sender);
    
    MenuItemSprite* backMenuItem;
    MenuItemSprite* creditMenuItem;
    MenuItemSprite* socialMenuItem;
    MenuItemSprite* soundMenuItem;
};

#endif // __SETTINGS_SCENE_H__
