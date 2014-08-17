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

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("GameBackground.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameSceneSprite.plist","GameSceneSprite.png");
    playerSprite = Sprite::createWithSpriteFrameName("planeBlue1.png");
    playerSprite->setPosition(Point(visibleSize.width * 0.2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(playerSprite);
    
    // Test function
    initAction();
    initAnimation();
    return true;
}

void GameScene::initAction()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto windowSize = Director::getInstance()->getWinSize();
    
    // Move the hero across the screen
    auto movePlayerUp = MoveBy::create(1, Point(0 , windowSize.height * 0.2));
    auto movePlayerDown = movePlayerUp->reverse();
    auto delay = DelayTime::create(0.25f);
   
	// Create a cardinal action
	auto trajectoryArray = PointArray::create(9);
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.9 + origin.x, visibleSize.height * 0.6 + origin.y));
    trajectoryArray->addControlPoint(Point(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.7 + origin.y));
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.7 + origin.x, visibleSize.height * 0.6 + origin.y));
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.6 + origin.x, visibleSize.height * 0.5 + origin.y));
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.6 + origin.y));
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.6 + origin.x, visibleSize.height * 0.7 + origin.y));
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.7 + origin.x, visibleSize.height * 0.6 + origin.y));
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.5 + origin.y));
	trajectoryArray->addControlPoint(Point(visibleSize.width * 0.9 + origin.x, visibleSize.height * 0.6 + origin.y));
    
	auto cardinalAction = CardinalSplineBy::create(3, trajectoryArray, 0);
	
    auto sequencePlayer = Sequence::create(movePlayerUp, delay, movePlayerDown, delay->clone(), NULL);
    playerSprite->runAction(RepeatForever::create(sequencePlayer));
    
}

void GameScene::initAnimation()
{
    // Plane animation
    auto planeAnimation = Animation::create();
    for(int index = 1; index < 4; index++ )
    {
        char name[50] = {0};
        sprintf(name, "planeBlue%i.png", index);
        SpriteFrame* planeSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        planeAnimation->addSpriteFrame(planeSpriteFrame);
    }
    
    planeAnimation->setDelayPerUnit(0.3f / 3.0f);
    planeAnimation->setRestoreOriginalFrame(true);
    auto planeAnimate = Animate::create(planeAnimation);
    auto planeRepeatForever = RepeatForever::create(planeAnimate);
    playerSprite->runAction(planeRepeatForever);
    
    // Puff animation
    auto puffAnimation = Animation::create();
    char name[50] = {0};
    SpriteFrame* puffSpriteFrame;
    sprintf(name, "puffLarge.png");
    puffSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
    puffAnimation->addSpriteFrame(puffSpriteFrame);
    sprintf(name, "puffSmall.png");
    puffSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
    puffAnimation->addSpriteFrame(puffSpriteFrame);
    
    puffAnimation->setDelayPerUnit(0.2f / 2.0f);
    puffAnimation->setRestoreOriginalFrame(true);
    auto puffAnimate = Animate::create(puffAnimation);
    auto puffRepeatForever = RepeatForever::create(puffAnimate);
    auto puffSprite = Sprite::create();
    puffSprite->runAction(puffRepeatForever);
    puffSprite->setPosition(Point(-playerSprite->getContentSize().width * 0.3, playerSprite->getContentSize().height * 0.7));
    playerSprite->addChild(puffSprite);
}
