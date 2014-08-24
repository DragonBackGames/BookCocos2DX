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

	// Configure joystick
	Point joystickBasePosition;
	joystickBasePosition = Point(screenSize.width * 0.2f,screenSize.height*0.2f);
    
	SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite
    (Sprite::createWithSpriteFrameName ("backgroundJoy.png"));
	joystickBase->setThumbSprite
    (Sprite::createWithSpriteFrameName("thumbJoy.png"));
    
	Rect joystickBaseDimensions;
	joystickBaseDimensions = CCRectMake(0, 0, 160.0f, 160.0f);
    
	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);
    
	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	this->addChild(joystickBase);
    
    //Create Attack Button
	Point attackButtonPosition;
	attackButtonPosition = Point
    (screenSize.width * 0.85f, screenSize.height * 0.2f);
    
	SneakyButtonSkinnedBase *attackButtonBase = new SneakyButtonSkinnedBase();
	attackButtonBase->init();
	attackButtonBase->setPosition(attackButtonPosition);
    
	attackButtonBase->setDefaultSprite (Sprite::createWithSpriteFrameName ("attackBtn.png"));
	attackButtonBase->setActivatedSprite(Sprite::createWithSpriteFrameName("attackBtn.png"));
	attackButtonBase->setDisabledSprite(Sprite::createWithSpriteFrameName("attackBtn.png"));
	attackButtonBase->setPressSprite(Sprite::createWithSpriteFrameName("attackBtn.png"));
	Rect attackButtonDimensions = CCRectMake(0, 0, 96.0f, 96.0f);
	SneakyButton *aAttackButton = new SneakyButton();
	aAttackButton->initWithRect(attackButtonDimensions);
	aAttackButton->autorelease();
    
	attackButtonBase->setButton(aAttackButton);
	attackButtonBase->setPosition(attackButtonPosition);
    
	attackButton = attackButtonBase->getButton();
	attackButton->retain();
	this->addChild(attackButtonBase);
    
    auto pauseOn = Sprite::createWithSpriteFrameName("pauseBtn.png");
    auto pauseOff = Sprite::createWithSpriteFrameName("pauseBtn.png");
    pauseMenuItem = MenuItemSprite::create(pauseOn, pauseOff,CC_CALLBACK_1(ControlGameLayer::clickPauseButton, this));
    
    auto pauseMenu = Menu::create(pauseMenuItem, NULL);
    pauseMenu->setPosition(Point(screenSize.width * 0.9f,screenSize.height * 0.9f));
    this->addChild(pauseMenu, 1);
    
    scheduleUpdate();
    setTouchEnabled(true);
    
    return true;
}

void ControlGameLayer::update(float dt)
{
    stickPosition = leftJoystick->getStickPosition();
    attackButtonValue = attackButton->getIsActive();
}

void ControlGameLayer::clickPauseButton(Ref* sender)
{
    Scene* newScene = TransitionMoveInR::create(0.2f, MenuScene::createScene());Director::getInstance()->replaceScene(newScene);
}
