#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2d.h"
#include "GLES-Render.h"
#include "GB2ShapeCache-x.h"
#include "ObstacleLayer.h"

USING_NS_CC;

class GameSceneContactListener : public b2ContactListener
{
public:
    // called by Box2D during the Step function when two fixtures begin touching
	virtual void BeginContact(b2Contact* contact);
    // called by Box2D during the Step function when two fixtures finish touching
	virtual void EndContact(b2Contact* contact);
    
    class GameScene* m_layer;
};

class GameScene : public Layer
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    CC_SYNTHESIZE(b2Fixture*, playerFixture, PlayerFixture);
	CC_SYNTHESIZE(b2Body*, playerBody, PlayerBody);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
private:
    // initialize sprites and other nodes for the layer
    void initNodes();
    // initialize physic bodies
    virtual void initPhysics();
    // standard Cocos2d layer method
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
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
    b2World* world;
    GLESDebugDraw* debugDraw;
    GameSceneContactListener* contactListener;
};

#endif // __GAME_SCENE_H__
