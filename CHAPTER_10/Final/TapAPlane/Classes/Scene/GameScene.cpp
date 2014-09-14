#include "GameScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    scene->addChild(layer->setupForegroundLayer(), 1);
    
    scene->addChild(layer->setupBackgroundLayer(), -1);
    
    // return the scene
    return scene;
}

BackgroundGameLayer* GameScene::setupBackgroundLayer()
{
    this->backgroundGameLayer = BackgroundGameLayer::create();
    return this->backgroundGameLayer;
}

ForegroundGameLayer* GameScene::setupForegroundLayer()
{
    this->foregroundGameLayer = ForegroundGameLayer::create();
    this->foregroundGameLayer->setGetReadySplash(true);
    return this->foregroundGameLayer;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    gameOverFlag = false;
    gameStartFlag = false;
    impulseFlag = false;
    
    this->initNodes();
    this->initPhysics();
    
    // Add the obstacle layer
    obstacleLayer = ObstacleLayer::create(world);
    this->addChild(obstacleLayer);
    
    // Add touch event callbacks
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
    
    return true;
}

void GameScene::initNodes()
{
    // Load game sprite sheet
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameSceneSprite.plist","GameSceneSprite.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
        
    // Load player textures
    auto heroAnimation = CCAnimation::create();
    for(int index = 1; index < 4; index++ )
    {
        char name[100] = {0};
        sprintf(name, "planeRed%i.png", index);
        auto heroSpriteFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
        heroAnimation->addSpriteFrame(heroSpriteFrame);
    }
    heroAnimation->setDelayPerUnit(0.3f / 3.0f);
    heroAnimation->setRestoreOriginalFrame(true);
    auto heroAnimate = Animate::create(heroAnimation);
    auto heroRepeatForever = RepeatForever::create(heroAnimate);
    playerSprite = Sprite::create();
    playerSprite->runAction(heroRepeatForever);
    playerSprite->setPosition(Point(visibleSize.width * 0.2f, visibleSize.height * 0.5f));
    this->addChild(playerSprite);
    
    auto puffAnimation = Animation::create();
    auto puffLargeSpriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName("puffLarge.png");
    puffAnimation->addSpriteFrame(puffLargeSpriteFrame);
    auto puffSmallSpriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName("puffSmall.png");
    puffAnimation->addSpriteFrame(puffSmallSpriteFrame);
    puffAnimation->setDelayPerUnit(0.4f / 2.0f);
    puffAnimation->setRestoreOriginalFrame(true);
    auto puffAnimate = Animate::create(puffAnimation);
    auto puffRepeatForever = RepeatForever::create(puffAnimate);
    auto puffSprite = Sprite::create();
    puffSprite->runAction(puffRepeatForever);
    puffSprite->setPosition(Point(-visibleSize.width * 0.02f, visibleSize.height * 0.06f));
    playerSprite->addChild(puffSprite);
}

void GameScene::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    
    // Configure physics debug
    debugDraw = new GLESDebugDraw( PTM_RATIO );
    debugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit );
    world->SetDebugDraw(debugDraw);
    
    GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("GameSceneObjects.plist");
    
    // Create hero body
    auto screenSize = Director::getInstance()->getWinSize();
    
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(screenSize.width * 0.2 / PTM_RATIO, screenSize.height * 0.5 / PTM_RATIO);
    myBodyDef.angle = 0;
    playerBody = world->CreateBody(&myBodyDef);
    
	ObstacleUserData* playerUserData = new ObstacleUserData;
	playerUserData->body = playerBody;
	playerUserData->sprite = playerSprite;
	playerUserData->fixtureType = FT_PLAYER;
	playerBody->SetUserData((void*)playerUserData);
    
    GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(playerBody, "planeRed1");
    playerSprite->setAnchorPoint(GB2ShapeCache::sharedGB2ShapeCache()->anchorPointForShape("planeRed1"));
    
    for (b2Fixture* f = playerBody->GetFixtureList(); f; f = f->GetNext())
    {
        playerFixture = f;
    }
    
    // Create contact listener
    contactListener = new GameSceneContactListener();
    world->SetContactListener(contactListener);
    contactListener->m_layer = this;
}

void GameScene::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    // Standard Cocos2d method
    if (!world)
    {
        return;
    }
    
    // debug draw display will be on top of anything else
    
    Layer::draw(renderer, transform, transformUpdated);
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    world->DrawDebugData();
    kmGLPopMatrix();
}

void GameScene::update(float dt)
{
    // Erase pickup
    for (std::set<ObstacleUserData*>::iterator it = m_pickupsToProcess.begin(); it != m_pickupsToProcess.end(); ++it)
    {
        ObstacleUserData* fud = *it;
		obstacleLayer->removeChild(fud->sprite, true);
		world->DestroyBody(fud->body);
		m_pickupsToProcess.erase(it);
        foregroundGameLayer->setScore();
		break;
    }
     // Events from forelayer
    if(this->foregroundGameLayer->getBackStatus())
    {
        auto newScene = TransitionMoveInL::create(0.2f, MenuScene::createScene());
        Director::getInstance()->replaceScene(newScene);
        return;
    }
    // If pause return;
	if(this->foregroundGameLayer->getPauseStatus())
    {
        return;
    }
    // Continue only if user press screen
    if(!gameStartFlag)
    {
        return;
    }

    if(gameOverFlag)
    {
        return;
    }
    
    // Update world iteration
    float32 timeStep = dt;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    world->Step( timeStep, velocityIterations, positionIterations);
    
    // Update sprite body decoration
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL)
        {
            //Synchronize the AtlasSprites position
            //and rotation with the corresponding body
            ObstacleUserData * myActor = (ObstacleUserData *)
            b->GetUserData();
            myActor->sprite->setPosition (Point( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->sprite->setRotation
            ( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }

    // Update player position
    auto screenSize = Director::getInstance()->getWinSize();
    if(!impulseFlag)
    {
        // Apply a constant force to the hero
        playerBody->ApplyLinearImpulse( b2Vec2(80,0), playerBody->GetWorldCenter(), true );
        impulseFlag = true;
    }
    // Move the layer at the same speed as the hero
    b2Vec2 cameraCenterInPixels = PTM_RATIO * playerBody->GetPosition();
    Point sceneOffset = Point(screenSize.width * 0.2 - cameraCenterInPixels.x, screenSize.height * 0.5);
    setPositionX(sceneOffset.x);
    
    // Create and destroy objects
    b2Body* bNext;
	bool deleted = false;
    for (b2Body* b = world->GetBodyList(); b; b = bNext)
    {
		bNext = b->GetNext();
        b2Vec2 position = b->GetPosition();
        if (((position.x * PTM_RATIO + sceneOffset.x) < -screenSize.width) && b)
        {
            ObstacleUserData* fud = (ObstacleUserData*)b->GetUserData();
            obstacleLayer->removeChild(fud->sprite, true);
            world->DestroyBody(b);
            
			deleted = true;
        }
    }
	// If any element was deleted, generate more
	if (deleted)
	{
		obstacleLayer->generateObstacle(1);
		deleted = false;
	}
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    if(!gameStartFlag)
    {
        gameStartFlag = true;
        foregroundGameLayer->setGetReadySplash(false);
        return true;
    }
    if(gameOverFlag)
    {
        return true;
    }
    
    // Applying linear impulse
    playerBody->ApplyLinearImpulse( b2Vec2(0,70), playerBody->GetWorldCenter(), true );

    // Play effect
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.wav");
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
    
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{
    
}

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
void GameSceneContactListener::BeginContact(b2Contact* contact)
{
    GameScene* layer = (GameScene*)m_layer;
    b2Fixture* fA = contact->GetFixtureA();
    b2Fixture* fB = contact->GetFixtureB();
    
    if( fA == NULL || fB == NULL || layer == NULL)
    {
        return;
    }
    ObstacleUserData* fudA = (ObstacleUserData*)fA->GetBody()->GetUserData();
    ObstacleUserData* fudB = (ObstacleUserData*)fB->GetBody()->GetUserData();
    
	// Player hit a pick up
	if ( fudA && fudA->fixtureType == FT_PICKUP && fB->GetBody() == layer->getPlayerBody() )
	{
        layer->m_pickupsToProcess.insert(fudA);
        // Play effect
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pickup.wav");
	}
    if ( fudB && fudB->fixtureType == FT_PICKUP && fA->GetBody() == layer->getPlayerBody() )
	{
        layer->m_pickupsToProcess.insert(fudB);
        // Play effect
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pickup.wav");
	}
    
	// Player hit a rock
	if ( fudA && fudA->fixtureType == FT_ROCK && fB->GetBody() == layer->getPlayerBody() )
	{
        layer->setGameOverFlag(true);
        layer->foregroundGameLayer->setGameOverSplash(true);
        // Play effect
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.wav");
	}
    if ( fudB && fudB->fixtureType == FT_ROCK && fA->GetBody() == layer->getPlayerBody() )
	{
        layer->setGameOverFlag(true);
        layer->foregroundGameLayer->setGameOverSplash(true);
        // Play effect
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.wav");
	}
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void GameSceneContactListener::EndContact(b2Contact* contact)
{
    
}
