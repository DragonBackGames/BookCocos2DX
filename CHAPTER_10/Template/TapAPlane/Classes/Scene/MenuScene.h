#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "CCParallaxScrollNode.h"

USING_NS_CC;

class MenuScene : public Layer
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
private:
    // initialize sprites and other nodes for the layer
    void initNodes();
    // initialize controllers for the layer
    void initControllers();
    // Click play button callback
    void clickPlayButton(Ref* sender);
    // Click settings button callback
    void clickSettingsButton(Ref* sender);
    // standard Cocos2d layer method
    virtual void update(float dt);
    
    // Menu item
    MenuItemSprite* playMenuItem;
    MenuItemSprite* settingsMenuItem;
    CCParallaxScrollNode* parallax;
    
};

#endif // __MENU_SCENE_H__
