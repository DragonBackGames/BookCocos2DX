#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ControlGameLayer.h"

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
    // initialize sprites and other nodes for the layer
    void initNodes();
    // initialize controllers for the layer
    ControlGameLayer* initControllers();
    // standard Cocos2d layer method
    virtual void update(float dt);
    // standard Cocos2d layer method
	virtual bool onTouchBegan(Touch *touch, Event *event);
    // standard Cocos2d layer method
	virtual void onTouchMoved(Touch *touch, Event *event);
    // standard Cocos2d layer method
	virtual void onTouchEnded(Touch *touch, Event *event);
    // standard Cocos2d layer method
	virtual void onTouchCancelled(Touch *touch, Event *event);
    
    Sprite* playerSprite;
    // Game stuff
    ControlGameLayer* controlGameLayer;
    
};

#endif // __GAME_SCENE_H__
