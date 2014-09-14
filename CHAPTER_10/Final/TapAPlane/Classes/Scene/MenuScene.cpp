#include "MenuScene.h"
#include "GameScene.h"
#include "SettingsScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->initNodes();
    this->initControllers();
    scheduleUpdate();
    
    return true;
}


void MenuScene::initNodes()
{
    // Load game sprite sheet
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MenuSceneSprite.plist","MenuSceneSprite.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto screenSize = Director::getInstance()->getWinSize();

    
    // Load background textures
    auto bg = Sprite::create("GameBackground.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    // Create parallax background
    parallax = CCParallaxScrollNode::create();

    auto land_green1 = Sprite::createWithSpriteFrameName("groundDirt.png");
    auto land_green2 = Sprite::createWithSpriteFrameName("groundDirt.png");
    auto land_green3 = Sprite::createWithSpriteFrameName("groundDirt.png");
    auto land_green4 = Sprite::createWithSpriteFrameName("groundDirt.png");
    
    parallax->addInfiniteScrollXWithZ(0, Point(0.5,0.2), Point(0,0), land_green1, land_green2, land_green3, land_green4, NULL);
    
    auto land_grey1 = Sprite::createWithSpriteFrameName("groundDirt.png");
    land_grey1->setRotation(180);
    auto land_grey2 = Sprite::createWithSpriteFrameName("groundDirt.png");
    land_grey2->setRotation(180);
    auto land_grey3 = Sprite::createWithSpriteFrameName("groundDirt.png");
    land_grey3->setRotation(180);
    auto land_grey4 = Sprite::createWithSpriteFrameName("groundDirt.png");
    land_grey4->setRotation(180);
    parallax->addInfiniteScrollXWithZ(0, Point(0.5,0.2), Point(0,screenSize.height), land_grey1, land_grey2, land_grey3, land_grey4, NULL);
    
    auto bg1 = Sprite::create("GameBackground.png");
    auto bg2 = Sprite::create("GameBackground.png");
    parallax->addInfiniteScrollXWithZ(-1,Point(0.1,0.1),Point(0, 0), bg1, bg2, NULL);
    
    this->addChild(parallax);
    
    // Load player textures
    auto tileSprite = Sprite::createWithSpriteFrameName("logo.png");
    tileSprite->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.7 + origin.y));
    this->addChild(tileSprite);
    
    // Hero animation
    auto heroAnimation = CCAnimation::create();
    for(int index = 1; index < 4; index++ )
    {
        char name[100] = {0};
        sprintf(name, "planeRed%i.png", index);
        auto heroSpriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName(name);
        heroAnimation->addSpriteFrame(heroSpriteFrame);
    }
    heroAnimation->setDelayPerUnit(0.3f / 3.0f);
    heroAnimation->setRestoreOriginalFrame(true);
    auto heroAnimate = Animate::create(heroAnimation);
    auto heroRepeatForever = RepeatForever::create(heroAnimate);
    auto heroSprite = Sprite::create();
    heroSprite->runAction(heroRepeatForever);
    heroSprite->setPosition(Point(screenSize.width * 0.2f, screenSize.height * 0.5f));
    this->addChild(heroSprite);
    
    auto puffAnimation = Animation::create();
    auto puffLargeSpriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName("puffLarge.png");
    puffAnimation->addSpriteFrame(puffLargeSpriteFrame);
    auto puffSmallSpriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName("puffSmall.png");
    puffAnimation->addSpriteFrame(puffSmallSpriteFrame);
    puffAnimation->setDelayPerUnit(0.4f / 2.0f);
    puffAnimation->setRestoreOriginalFrame(true);
    auto puffAnimate = Animate::create(puffAnimation);
    auto puffRepeatForever = RepeatForever::create(puffAnimate);
    auto puffSprite = Sprite::create();
    puffSprite->runAction(puffRepeatForever);
    puffSprite->setPosition(Point(screenSize.width * 0.135f, screenSize.height * 0.51f));
    this->addChild(puffSprite);
    
}

void MenuScene::initControllers()
{
    Size screenSize = Director::getInstance()->getWinSize();
    
    // Create pause menu
    auto playOn = Sprite::createWithSpriteFrameName("playOnBtn.png");
    auto playOff = Sprite::createWithSpriteFrameName("playOffBtn.png");
    playMenuItem = MenuItemSprite::create(playOn, playOff, CC_CALLBACK_1(MenuScene::clickPlayButton, this));
    
    auto settingsOn = Sprite::createWithSpriteFrameName("settingsOnBtn.png");
    auto settingsOff = Sprite::createWithSpriteFrameName("settingsOffBtn.png");
    settingsMenuItem = MenuItemSprite::create(settingsOn, settingsOff, CC_CALLBACK_1(MenuScene::clickSettingsButton, this));
    
    auto mainMenu = Menu::create(playMenuItem, settingsMenuItem, NULL);
    mainMenu->setPosition(Point(screenSize.width * 0.7f, screenSize.height * 0.4f));
    mainMenu->alignItemsVerticallyWithPadding(20);
    this->addChild(mainMenu, 1);
}

void MenuScene::clickPlayButton(Ref* sender)
{
    Scene* newScene = TransitionMoveInR::create(0.2f, GameScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}

void MenuScene::clickSettingsButton(Ref* sender)
{
    Scene* newScene = TransitionMoveInR::create(0.2f, SettingsScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}

void MenuScene::update(float dt)
{
    // ------------------------------------------------------------------------
    // Update parallax
    // ------------------------------------------------------------------------
    parallax->updateWithVelocity(ccp(-10,0), dt);
}
