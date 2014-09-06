#include "AppDelegate.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SettingsScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Tap A Plane");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // Start music
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3");
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MenuScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    Director::getInstance()->startAnimation();
}
