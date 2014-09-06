#include "ControlGameLayer.h"
#include "MenuScene.h"

ControlGameLayer::~ControlGameLayer()
{
    
}

ControlGameLayer* ControlGameLayer::create()
{
    ControlGameLayer* layer = new ControlGameLayer();
    layer->init();
    return layer;
}

bool ControlGameLayer::init()
{
	if (!Layer::init())
	{
        return false;
	}
    
	Size screenSize = Director::getInstance()->getWinSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ControllerSceneSprite.plist","ControllerSceneSprite.png");
    
    auto pauseOn = Sprite::createWithSpriteFrameName("pauseBtn.png");
    auto pauseOff = Sprite::createWithSpriteFrameName("pauseBtn.png");
    pauseMenuItem = MenuItemSprite::create(pauseOn, pauseOff,CC_CALLBACK_1(ControlGameLayer::clickPauseButton, this));
    
    auto pauseMenu = Menu::create(pauseMenuItem, NULL);
    pauseMenu->setPosition(Point(screenSize.width * 0.9f,screenSize.height * 0.9f));
    this->addChild(pauseMenu, 1);
    
    scheduleUpdate();
        
    return true;
}

void ControlGameLayer::update(float dt)
{
}

void ControlGameLayer::clickPauseButton(Ref* sender)
{
    Scene* newScene = TransitionMoveInR::create(0.2f, MenuScene::createScene());Director::getInstance()->replaceScene(newScene);
}
