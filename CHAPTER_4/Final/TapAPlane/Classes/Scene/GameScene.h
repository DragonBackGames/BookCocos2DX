#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
private:
    void initAction();
    void initAnimation();
    
    Sprite* playerSprite;};

#endif // __GAME_SCENE_H__
