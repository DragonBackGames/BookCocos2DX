#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    this->initNodes();
    this->initPhysics();
    
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
    
    // Load background textures
    auto bg = Sprite::create("GameBackground.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    // Load player textures
    playerSprite = Sprite::createWithSpriteFrameName("planeRed1.png");
    playerSprite->setPosition(Point(visibleSize.width * 0.2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(playerSprite);
}

void GameScene::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    
    // Test code
#if 0
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);
    myBodyDef.angle = 0;
    b2Body* dynamicBody = world->CreateBody(&myBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);
#endif
    
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
            myActor->sprite->setPosition (CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->sprite->setRotation
            ( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }

}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    // Setting velocity
#if 0
    b2Vec2 playerVelocity = playerBody->GetLinearVelocity();
    playerVelocity.y = 10;
    playerBody->SetLinearVelocity(playerVelocity);
#endif
    
    // Applying force
#if 0
    playerBody->ApplyForce( b2Vec2(0,2000), playerBody->GetWorldCenter(), true );
#endif
    
    // Applying linear impulse
    playerBody->ApplyLinearImpulse( b2Vec2(0,70), playerBody->GetWorldCenter(), true );

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
        
	}
    if ( fudB && fudB->fixtureType == FT_PICKUP && fA->GetBody() == layer->getPlayerBody() )
	{

	}
    
	// Player hit a rock
	if ( fudA && fudA->fixtureType == FT_ROCK && fB->GetBody() == layer->getPlayerBody() )
	{
        
	}
    if ( fudB && fudB->fixtureType == FT_ROCK && fA->GetBody() == layer->getPlayerBody() )
	{
        
	}
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void GameSceneContactListener::EndContact(b2Contact* contact)
{
    
}
