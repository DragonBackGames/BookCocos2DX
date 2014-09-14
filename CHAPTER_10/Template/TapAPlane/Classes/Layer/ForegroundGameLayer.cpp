/* ----------------------------------------------------------------------------
 *
 * Includes
 *
 * ----------------------------------------------------------------------------
 */
#include "ForegroundGameLayer.h"
#include "GameScene.h"

/* ----------------------------------------------------------------------------
 *
 * Class methods
 *
 * ----------------------------------------------------------------------------
 */
/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
ForegroundGameLayer::~ForegroundGameLayer()
{
    
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
ForegroundGameLayer* ForegroundGameLayer::create()
{
    ForegroundGameLayer* layer = new ForegroundGameLayer();
    layer->init();
    return layer;
}
/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::setGetReadySplash(bool flag)
{
    if (flag == true)
    {
        getReadySprite->setVisible(true);
        tapLeft->setVisible(true);
        tapRight->setVisible(true);
        fingerTap->setVisible(true);
		gameReady = true;
    }
    else
    {
        getReadySprite->setVisible(false);
        tapLeft->setVisible(false);
        tapRight->setVisible(false);
        fingerTap->setVisible(false);
		gameReady = false;
    }
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::setGameOverSplash(bool flag)
{
    if (flag == true)
    {
		// Show sprites
        gameOverSprite->setVisible(true);
		scoreLbl->setVisible(true);
		gameMenu->alignItemsHorizontallyWithPadding(20);
	    gameMenu->setPosition(Point(screenSize.width * 0.5, screenSize.height * 0.20f));
		gameMenu->setVisible(true);
		gameOver = true;
		// Show score
		char szValue[100] = {0};
		sprintf(szValue, "%i", scorePoints);

		auto scoreCurrentDisplay = LabelBMFont::create(szValue, "font.fnt", screenSize.width * 0.3f);
		scoreCurrentDisplay->setAnchorPoint(Point(1,0.5));
	    scoreCurrentDisplay->setPosition(Point(screenSize.width * 0.45f, screenSize.height * 0.51f));
		this->addChild(scoreCurrentDisplay, 2);

		// Save best score with user default data
		if (bestPoints < scorePoints)
        {
            bestPoints = scorePoints;
        }
        this->saveData(bestPoints);
        
		sprintf(szValue, "%i", bestPoints);

		auto scoreBestDisplay = LabelBMFont::create(szValue, "font.fnt", screenSize.width * 0.3f);
		scoreBestDisplay->setAnchorPoint(Point(1,0.5));
	    scoreBestDisplay->setPosition(Point(screenSize.width * 0.65f, screenSize.height * 0.51f));
		this->addChild(scoreBestDisplay, 2);

		// Show medals
		if(scorePoints > 10)
		{
			bronceMedal->setVisible(true);
		}
		if(scorePoints > 20)
		{
			silverMedal->setVisible(true);
		}
		if(scorePoints > 50)
		{
			goldMedal->setVisible(true);
		}
    }
    else
    {
        gameOverSprite->setVisible(false);
		gameOver = false;
    }
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
bool ForegroundGameLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    // Load game sprite sheet
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ScoreSceneSprite.plist","ScoreSceneSprite.png");
    
    // ------------------------------------------------------------------------
    // Configure generic stuff
    // ------------------------------------------------------------------------
    pauseStatus = false;
    screenSize = Director::getInstance()->getWinSize();
    
    // ------------------------------------------------------------------------
    // Configure sprites
    // ------------------------------------------------------------------------
    gameOverSprite = Sprite::createWithSpriteFrameName("textGameOver.png");
    gameOverSprite->cocos2d::CCNode::setPosition(Point(screenSize.width * 0.5, screenSize.width * 0.6));
    gameOverSprite->setVisible(false);
    this->addChild(gameOverSprite, 1);
    
    getReadySprite = Sprite::createWithSpriteFrameName("textGetReady.png");
    getReadySprite->cocos2d::CCNode::setPosition(Point(screenSize.width * 0.5, screenSize.width * 0.55));
    getReadySprite->setVisible(false);
    this->addChild(getReadySprite, 1);

    tapLeft = Sprite::createWithSpriteFrameName("tapLeft.png");
    tapLeft->cocos2d::CCNode::setPosition(Point(screenSize.width * 0.55, screenSize.width * 0.25));
    tapLeft->setVisible(false);
    this->addChild(tapLeft, 1);
    
    tapRight = Sprite::createWithSpriteFrameName("tapRight.png");
    tapRight->cocos2d::CCNode::setPosition(Point(screenSize.width * 0.4, screenSize.width * 0.25));
    tapRight->setVisible(false);
    this->addChild(tapRight, 1);
    
    auto fingerAnimation = Animation::create();
    auto heroSpriteFrame1 = SpriteFrameCache::getInstance()->spriteFrameByName("tap.png");
    fingerAnimation->addSpriteFrame(heroSpriteFrame1);
    auto heroSpriteFrame2 = SpriteFrameCache::getInstance()->spriteFrameByName("tapTick.png");
    fingerAnimation->addSpriteFrame(heroSpriteFrame2);
    
    fingerAnimation->setDelayPerUnit(1.0f / 2.0f);
    fingerAnimation->setRestoreOriginalFrame(true);
    auto fingerAnimate = Animate::create(fingerAnimation);
    auto fingerRepeatForever = RepeatForever::create(fingerAnimate);
    fingerTap= Sprite::create();
    fingerTap->runAction(fingerRepeatForever);
    fingerTap->setPosition(Point(screenSize.width * 0.48f, screenSize.height * 0.35f));
    fingerTap->setVisible(false);
    this->addChild(fingerTap, 1);
    
	scoreLbl = Sprite::createWithSpriteFrameName("scoreLbl.png");
    scoreLbl->setPosition(Point(screenSize.width * 0.5, screenSize.width * 0.4));
    scoreLbl->setVisible(false);
    this->addChild(scoreLbl, 1);

	bronceMedal = Sprite::createWithSpriteFrameName("medalBronze.png");
    bronceMedal->setPosition(Point(screenSize.width * 0.42, screenSize.width * 0.43));
    bronceMedal->setVisible(false);
    this->addChild(bronceMedal, 2);

	silverMedal = Sprite::createWithSpriteFrameName("medalSilver.png");
    silverMedal->setPosition(Point(screenSize.width * 0.42, screenSize.width * 0.43));
    silverMedal->setVisible(false);
    this->addChild(silverMedal, 2);

	goldMedal = Sprite::createWithSpriteFrameName("medalGold.png");
    goldMedal->setPosition(Point(screenSize.width * 0.42, screenSize.width * 0.43));
    goldMedal->setVisible(false);
    this->addChild(goldMedal, 2);
    // ------------------------------------------------------------------------
    // Configure Menu
    // ------------------------------------------------------------------------
    
    // Configure play button
    auto pauseOn = Sprite::createWithSpriteFrameName("pauseBtn.png");
    auto pauseOff = Sprite::createWithSpriteFrameName("pauseBtn.png");
    auto pauseMenuItem = MenuItemSprite::create(pauseOn, pauseOff, this, menu_selector(ForegroundGameLayer::clickPauseButton));
        
    pauseMenu = Menu::create(pauseMenuItem, NULL);
    pauseMenu->setPosition(Point(screenSize.width * 0.1, screenSize.height * 0.9f));
    this->addChild(pauseMenu);
    

	// Configure play button
    auto playOn = Sprite::createWithSpriteFrameName("playOnBtn.png");
    auto playOff = Sprite::createWithSpriteFrameName("playOffBtn.png");
    auto playMenuItem = MenuItemSprite::create(playOn, playOff, this, menu_selector(ForegroundGameLayer::clickPlayButton));

	auto backOn = Sprite::createWithSpriteFrameName("backYellowOnBtn.png");
    auto backOff = Sprite::createWithSpriteFrameName("backYellowOffBtn.png");
    auto backMenuItem = MenuItemSprite::create(backOn, backOff, this, menu_selector(ForegroundGameLayer::clickBackButton));

    gameMenu = CCMenu::create(playMenuItem, backMenuItem, NULL);
    gameMenu->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5f));
	gameMenu->alignItemsVerticallyWithPadding(20);
	gameMenu->setVisible(false);
    this->addChild(gameMenu, 1);
	   
	scoreDisplay = LabelBMFont::create("0", "font.fnt", screenSize.width * 0.3f);
    scoreDisplay->setAnchorPoint(Point(1,0.5));
    scoreDisplay->setPosition(Point(screenSize.width * 0.9f, screenSize.height * 0.94f));
    this->addChild(scoreDisplay);

	char szValue[100] = {0};
    sprintf(szValue, "%i", scorePoints);
    scoreDisplay->setString(szValue);

	pauseStatus = false;
	backStatus = false;
	gameReady = false;
	gameOver = false;

    // Initialize score using User Default Data
	scorePoints = 0;
    this->initData();

    return true;
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::initData()
{

}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::saveData(int score)
{

}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::clickPauseButton(Ref* pSender)
{
	if(gameOver || gameReady)
	{
		return;
	}
    pauseStatus = true;
	gameMenu->setVisible(true);
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::clickPlayButton(Ref* pSender)
{

    pauseStatus = false;
	gameMenu->setVisible(false);

	if (gameOver)
	{
		auto newScene = CCTransitionMoveInR::create(0.2f, GameScene::createScene());
		Director::getInstance()->replaceScene(newScene);
	}
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::clickBackButton(Ref* pSender)
{
    backStatus = true;
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void ForegroundGameLayer::setScore()
{
	scorePoints++;
    char szValue[100] = {0};
    sprintf(szValue, "%i", scorePoints);
    scoreDisplay->setString(szValue);
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
int ForegroundGameLayer::getScore()
{
	return scorePoints;
}
