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

}

void MenuScene::clickPlayButton(Ref* sender)
{
    
}

void MenuScene::clickSettingsButton(Ref* sender)
{
    
}
