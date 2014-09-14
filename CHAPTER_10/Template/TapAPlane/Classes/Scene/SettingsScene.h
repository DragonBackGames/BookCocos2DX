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
    // Apparel layer callback
    void clickCreditButton(Ref* pSender);
    // Gear layer callback
    void clickFacebookButton(Ref* pSender);
    // Profile layer callback
    void clickTwitterButton(Ref* pSender);
    // Coins layer callback
    void clickYoutubeButton(Ref* pSender);
    // Coins layer callback
    void clickSoundButton(Ref* pSender);
    // Coins layer callback
    void clickMusicButton(Ref* pSender);

    MenuItemSprite* backMenuItem;
    MenuItemSprite* creditMenuItem;
    MenuItemSprite* socialMenuItem;
    MenuItemSprite* soundMenuItem;
    
    bool effectFlag;
	bool musicFlag;
};

#endif // __SETTINGS_SCENE_H__
