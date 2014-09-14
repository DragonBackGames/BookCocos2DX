#ifndef __FOREGROUND_GAME_LAYER_H__
#define __FOREGROUND_GAME_LAYER_H__

/* ----------------------------------------------------------------------------
 *
 * Includes
 *
 * ----------------------------------------------------------------------------
 */
#include "cocos2d.h"
#include "sqlite3.h"

// change macro to use default user data or sqlite3
#define SQLITEDATA 1

USING_NS_CC;

/* ----------------------------------------------------------------------------
 *
 * Class definition
 *
 * ----------------------------------------------------------------------------
 */
class ForegroundGameLayer : public Layer
{
public:
    // Destructor
    ~ForegroundGameLayer();
    // Create a layer
    static ForegroundGameLayer* create();
    // Configure Get Ready splash
    void setGetReadySplash(bool flag);
    // Configure Game Over splash
    void setGameOverSplash(bool flag);
	// Set score
	void setScore();
	// Get score
	int getScore();
    // Status of pause button
    CC_SYNTHESIZE(bool, pauseStatus, PauseStatus);
	CC_SYNTHESIZE(bool, backStatus, BackStatus);

private:
    // Initialize all resources from the layer
    virtual bool init();
    // Initialize data
    void initData();
    // Save data
    void saveData(int score);
    // Click pause button callback
    void clickPauseButton(Ref* pSender);
    // Click play button callback
    void clickPlayButton(Ref* pSender);
	// Click Back button callback
    void clickBackButton(Ref* pSender);

    // Screen size
    Size screenSize;
    // Sprites
    Sprite* gameOverSprite;
    Sprite* getReadySprite;
    Sprite* tapLeft;
    Sprite* tapRight;
    Sprite* fingerTap;
	Sprite* scoreLbl;
	Sprite* bronceMedal;
	Sprite* silverMedal;
	Sprite* goldMedal;

    // Pause menu
    Menu* pauseMenu;
	Menu* gameMenu;
    // Score
	LabelBMFont* scoreDisplay;
    int scorePoints;
	int bestPoints;
	// State machine
	bool gameReady;
	bool gameOver;
    
    sqlite3 *pdb;
    std::string sql;
};

#endif // __FOREGROUND_GAME_LAYER_H__
