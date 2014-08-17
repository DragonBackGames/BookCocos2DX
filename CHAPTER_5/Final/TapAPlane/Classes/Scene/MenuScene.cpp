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
    return true;
}


void MenuScene::initNodes()
{
    // Load game sprite sheet
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MenuSceneSprite.plist","MenuSceneSprite.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // Load background textures
    auto bg = Sprite::create("GameBackground.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    // Load player textures
    auto tileSprite = Sprite::createWithSpriteFrameName("logo.png");
    tileSprite->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.7 + origin.y));
    this->addChild(tileSprite);
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

