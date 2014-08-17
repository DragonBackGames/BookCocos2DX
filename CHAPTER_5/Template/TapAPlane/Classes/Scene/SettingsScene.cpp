#include "SettingsScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SettingsScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool SettingsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->initNodes();
    this->initControllers();
    
    return true;
}

void SettingsScene::initNodes()
{
    // Load game sprite sheet
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SettingsSceneSprite.plist","SettingsSceneSprite.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // Load background textures
    auto bg = Sprite::create("SettingsBackground.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
}

void SettingsScene::initControllers()
{

    Size screenSize = Director::getInstance()->getWinSize();
    
    // Create back menu
    auto backOn = Sprite::createWithSpriteFrameName("backOnBtn.png");
    auto backOff = Sprite::createWithSpriteFrameName("backOffBtn.png");
    backMenuItem = MenuItemSprite::create(backOn, backOff, CC_CALLBACK_1(SettingsScene::clickBackButton, this));
    
    auto backMenu = Menu::create(backMenuItem, NULL);
    backMenu->setPosition(Point(screenSize.width * 0.1f, screenSize.height * 0.9f));
    this->addChild(backMenu, 1);
}

void SettingsScene::clickBackButton(Ref* sender)
{
    
}
