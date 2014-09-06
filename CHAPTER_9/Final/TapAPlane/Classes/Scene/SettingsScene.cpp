#include "SettingsScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

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
    
    auto backLbl1 = Sprite::createWithSpriteFrameName("subLayerLbl.png");
    backLbl1->setPosition(Point(screenSize.width * 0.5, screenSize.height * 0.5));
    this->addChild(backLbl1, 0);
    
    auto backLbl2 = Sprite::createWithSpriteFrameName("subLayerLbl.png");
    backLbl2->setPosition(Point(screenSize.width * 0.5, screenSize.height * 0.2));
    this->addChild(backLbl2, 0);
    
    // Create back menu
    auto backOn = Sprite::createWithSpriteFrameName("backOnBtn.png");
    auto backOff = Sprite::createWithSpriteFrameName("backOffBtn.png");
    backMenuItem = MenuItemSprite::create(backOn, backOff, CC_CALLBACK_1(SettingsScene::clickBackButton, this));
    
    auto backMenu = Menu::create(backMenuItem, NULL);
    backMenu->setPosition(Point(screenSize.width * 0.1f, screenSize.height * 0.9f));
    this->addChild(backMenu, 1);
    
    // Configure Credits Menu
    auto creditsOn = Sprite::createWithSpriteFrameName("creditOnBtn.png");
    auto creditsOff = Sprite::createWithSpriteFrameName("creditOffBtn.png");
    auto creditsMenuItem = MenuItemSprite::create(creditsOn, creditsOff, CC_CALLBACK_1(SettingsScene::clickCreditButton, this));
    
    auto creditMenu = Menu::create(creditsMenuItem, NULL);
    creditMenu->setPosition(Point(screenSize.width * 0.5, screenSize.height * 0.75f));
    this->addChild(creditMenu);
    
    // Configure Social Menu
    auto facebookOn = Sprite::createWithSpriteFrameName("facebookButton.png");
    auto facebookOff = Sprite::createWithSpriteFrameName("facebookButton.png");
    auto facebookMenuItem = MenuItemSprite::create(facebookOn, facebookOff, CC_CALLBACK_1(SettingsScene::clickFacebookButton, this));
    
    auto twitterOn = Sprite::createWithSpriteFrameName("twitterButton.png");
    auto twitterOff = Sprite::createWithSpriteFrameName("twitterButton.png");
    auto twitterMenuItem = MenuItemSprite::create(twitterOn, twitterOff, CC_CALLBACK_1(SettingsScene::clickTwitterButton, this));
    
    auto youtubeOn = Sprite::createWithSpriteFrameName("youtubeButton.png");
    auto youtubeOff = Sprite::createWithSpriteFrameName("youtubeButton.png");
    auto youtubeMenuItem = MenuItemSprite::create(youtubeOn, youtubeOff, CC_CALLBACK_1(SettingsScene::clickYoutubeButton, this));
    
    auto socialMenu = Menu::create(facebookMenuItem, twitterMenuItem, youtubeMenuItem, NULL);
    socialMenu->setPosition(Point(screenSize.width * 0.5, screenSize.height * 0.5f));
    socialMenu->alignItemsHorizontallyWithPadding(20);
    this->addChild(socialMenu);
    
    // Configure Sound Menu
    auto soundOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundOnButton.png"),  Sprite::createWithSpriteFrameName("soundOffButton.png"));
    auto soundOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundOffButton.png"), Sprite::createWithSpriteFrameName("soundOnButton.png"));
    auto soundMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingsScene::clickSoundButton, this), soundOn, soundOff, NULL);
    
    auto musicOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("musicOnButton.png"), Sprite::createWithSpriteFrameName("musicOffButton.png"));
    auto musicOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("musicOffButton.png"), Sprite::createWithSpriteFrameName("musicOnButton.png"));
    auto musicMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingsScene::clickMusicButton, this), musicOn, musicOff, NULL);
    
    auto soundMenu = Menu::create(soundMenuItem, musicMenuItem, NULL);
    soundMenu->setPosition(Point(screenSize.width * 0.5, screenSize.height * 0.2f));
    soundMenu->alignItemsHorizontallyWithPadding(20);
    this->addChild(soundMenu);
    
    effectFlag = true;
	musicFlag = true;

}

void SettingsScene::clickBackButton(Ref* sender)
{
    Scene* newScene = TransitionMoveInR::create(0.2f, MenuScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}

void SettingsScene::clickCreditButton(Ref* sender)
{

}

void SettingsScene::clickFacebookButton(Ref* sender)
{
    
}

void SettingsScene::clickTwitterButton(Ref* sender)
{
    
}

void SettingsScene::clickYoutubeButton(Ref* sender)
{
    
}

void SettingsScene::clickSoundButton(Ref* sender)
{
    if(effectFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0);
		effectFlag = false;
	}
	else
	{
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
		effectFlag = true;
	}
}

void SettingsScene::clickMusicButton(Ref* sender)
{
    if(musicFlag)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0);
		musicFlag = false;
	}
	else
	{
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
		musicFlag = true;
	}
}
