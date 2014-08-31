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
    
    // This is temporal code, just to show the concept of the scene
    auto label1 = Sprite::createWithSpriteFrameName("subLayerLbl.png");
    label1->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.75 + origin.y));
    label1->setScale(0.8);
    this->addChild(label1);
    
    auto label2 = Sprite::createWithSpriteFrameName("subLayerLbl.png");
    label2->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    label2->setScale(0.8);
    this->addChild(label2);
    
    auto label3 = Sprite::createWithSpriteFrameName("subLayerLbl.png");
    label3->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.25 + origin.y));
    label3->setScale(0.8);
    this->addChild(label3);
    
    auto credits = Sprite::createWithSpriteFrameName("creditOnBtn.png");
    credits->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.75 + origin.y));
    this->addChild(credits);
    
    auto facebook = Sprite::createWithSpriteFrameName("facebookButton.png");
    facebook->setPosition(Point(visibleSize.width * 0.35 + origin.x, visibleSize.height * 0.5 + origin.y));
    this->addChild(facebook);
    
    auto twitter = Sprite::createWithSpriteFrameName("twitterButton.png");
    twitter->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    this->addChild(twitter);
    
    auto youtube = Sprite::createWithSpriteFrameName("youtubeButton.png");
    youtube->setPosition(Point(visibleSize.width * 0.65 + origin.x, visibleSize.height * 0.5 + origin.y));
    this->addChild(youtube);
    
    auto sound = Sprite::createWithSpriteFrameName("soundOnButton.png");
    sound->setPosition(Point(visibleSize.width * 0.40 + origin.x, visibleSize.height * 0.25 + origin.y));
    this->addChild(sound);
    
    auto music = Sprite::createWithSpriteFrameName("musicOnButton.png");
    music->setPosition(Point(visibleSize.width * 0.60 + origin.x, visibleSize.height * 0.25 + origin.y));
    this->addChild(music);
    
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
    Scene* newScene = TransitionMoveInR::create(0.2f, MenuScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}
