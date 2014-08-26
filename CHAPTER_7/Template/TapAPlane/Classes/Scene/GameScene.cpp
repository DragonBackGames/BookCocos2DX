#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    this->initNodes();
    this->initPhysics();
    
    // Add touch event callbacks
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
    
    return true;
}

void GameScene::initNodes()
{
    // Load game sprite sheet
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameSceneSprite.plist","GameSceneSprite.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // Load background textures
    auto bg = Sprite::create("GameBackground.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    // Load player textures
    playerSprite = Sprite::createWithSpriteFrameName("planeRed1.png");
    playerSprite->setPosition(Point(visibleSize.width * 0.2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(playerSprite);
}

void GameScene::initPhysics()
{
    
}

void GameScene::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    
}

void GameScene::update(float dt)
{

}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
    
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{
    
}
