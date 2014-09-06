/* ----------------------------------------------------------------------------
 *
 * Includes
 *
 * ----------------------------------------------------------------------------
 */
#include "ObstacleLayer.h"

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
ObstacleLayer::ObstacleLayer(b2World* world)
{
    if(this->init())
    {
		/* --------------------------------------------------------------------
         * Configure data members
         * ---------------------------------------------------------------------
         */
        this->world = world;
        this->body = NULL;
        auto screenSize = Director::getInstance()->getWinSize();
		offset = 0;
		offsetRock = 0;
		obstacleCounter = 0;
		/* --------------------------------------------------------------------
         * Generate rock points
         * ---------------------------------------------------------------------
         */
		float x;
		float y;
        
		x = screenSize.width * 2;
		y = screenSize.height * 0.5 + (int)( ((double)rand() / RAND_MAX - 0.5) * screenSize.height * 0.25);
		obstaclePoints[0] = Point(x, y);
        
		for (int i = 1; i < kMaxObstaclePoints; i++)
		{
			x += (int)( ((double)rand() / RAND_MAX - 0.5 ) * screenSize.width * 0.25 ) + screenSize.width * 0.5;
			y = screenSize.height * 0.5 + (int)( ((double)rand() / RAND_MAX - 0.5) * screenSize.height * 0.25);
			obstaclePoints[i] = Point(x, y);
		}
        
		/* --------------------------------------------------------------------
         * Generate obstacles
         * ---------------------------------------------------------------------
         */
        generateObstacle(3);
    }
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
ObstacleLayer::~ObstacleLayer()
{
    
}

/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
ObstacleLayer* ObstacleLayer::create(b2World* world)
{
    ObstacleLayer* layer = new ObstacleLayer(world);
    return layer;
}


/* ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
void  ObstacleLayer::generateObstacle(int quantity)
{
    auto screenSize = Director::getInstance()->getWinSize();
    
	obstacleCounter += quantity;
	// Update offset
	int offsetEnd = offset + quantity;
    
	/* -----------------------------------------------------------------------
     * Generate floor and celing
     * ------------------------------------------------------------------------
     */
	for(; offset < offsetEnd; offset++)
	{
        // Floor
        b2BodyDef floorBodyDef;
        floorBodyDef.position.Set(800 * offset / PTM_RATIO, 0);
        b2Body* floorBody = world->CreateBody(&floorBodyDef);
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(floorBody, "groundDirt");
        Sprite* floorSprite = Sprite::createWithSpriteFrameName("groundDirt.png");
        floorSprite->setAnchorPoint(Point(0,0));
        floorSprite->setPosition(Point(floorBody->GetPosition().x * PTM_RATIO, floorBody->GetPosition().y * PTM_RATIO));
        this->addChild(floorSprite);
        
		ObstacleUserData* floorUserData = new ObstacleUserData;
		floorUserData->body = floorBody;
		floorUserData->sprite = floorSprite;
		floorUserData->fixtureType = FT_ROCK;
		floorBody->SetUserData((void*)floorUserData);
        
		// Ceiling
        b2BodyDef ceilingBodyDef;
		ceilingBodyDef.position.Set(800 * (offset + 1) / PTM_RATIO, screenSize.height / PTM_RATIO);
        b2Body* ceilingBody = world->CreateBody(&ceilingBodyDef);
		float angle = CC_DEGREES_TO_RADIANS(180);
		b2Vec2 pos = ceilingBody->GetPosition();
		ceilingBody->SetTransform(pos, angle);
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(ceilingBody, "groundDirt");
        Sprite* ceilingSprite = Sprite::createWithSpriteFrameName("groundDirt.png");
        ceilingSprite->setAnchorPoint(Point(0,0));
        ceilingSprite->setPosition(Point(ceilingBody->GetPosition().x * PTM_RATIO, ceilingBody->GetPosition().y * PTM_RATIO));
		ceilingSprite->setRotation(180);
        this->addChild(ceilingSprite);
        
		ObstacleUserData* ceilingUserData = new ObstacleUserData;
		ceilingUserData->body = ceilingBody;
		ceilingUserData->sprite = ceilingSprite;
		ceilingUserData->fixtureType = FT_ROCK;
		ceilingBody->SetUserData((void*)ceilingUserData);
    }
    
	if(obstacleCounter >= kMaxObstaclePoints)
	{
		return;
	}
	offsetEnd = offsetRock + quantity;
	/* -----------------------------------------------------------------------
     * Generate rocks and sensor
     * ------------------------------------------------------------------------
     */
    
    for(; offsetRock < offsetEnd; offsetRock++)
	{
		// Upper rock
        b2BodyDef upperBodyDef;
        upperBodyDef.position.Set(obstaclePoints[offsetRock].x / PTM_RATIO, (screenSize.height - obstaclePoints[offsetRock].y + 50 )/ PTM_RATIO);
        b2Body* upperBody = world->CreateBody(&upperBodyDef);
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(upperBody, "rockDown");
        Sprite* upperSprite = Sprite::createWithSpriteFrameName("rockDown.png");
        upperSprite->setAnchorPoint(Point(0,0));
        upperSprite->setPosition(Point(upperBody->GetPosition().x * PTM_RATIO, upperBody->GetPosition().y * PTM_RATIO));
        this->addChild(upperSprite, -1);
        
		ObstacleUserData* upperUserData = new ObstacleUserData;
		upperUserData->body = upperBody;
		upperUserData->sprite = upperSprite;
		upperUserData->fixtureType = FT_ROCK;
		upperBody->SetUserData((void*)upperUserData);
        
		// Down rock
        b2BodyDef downBodyDef;
        downBodyDef.position.Set(obstaclePoints[offsetRock].x / PTM_RATIO, (screenSize.height * 0.3 - obstaclePoints[offsetRock].y )/ PTM_RATIO);
        b2Body* downBody = world->CreateBody(&downBodyDef);
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(downBody, "rock");
        Sprite* downSprite = Sprite::createWithSpriteFrameName("rock.png");
        downSprite->setAnchorPoint(Point(0,0));
        downSprite->setPosition(Point(downBody->GetPosition().x * PTM_RATIO, downBody->GetPosition().y * PTM_RATIO));
        this->addChild(downSprite, -1);
        
		ObstacleUserData* downUserData  = new ObstacleUserData;
		downUserData->body = downBody;
		downUserData->sprite = downSprite;
		downUserData->fixtureType = FT_ROCK;
		downBody->SetUserData((void*)downUserData);
        
		// Star sensor
        b2BodyDef starBodyDef;
		starBodyDef.type = b2_kinematicBody;
        starBodyDef.position.Set((obstaclePoints[offsetRock].x + 85) / PTM_RATIO, (screenSize.height * 1.85 - 2 * obstaclePoints[offsetRock].y) / (2 * PTM_RATIO));
        b2Body* starBody = world->CreateBody(&starBodyDef);
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(starBody, "starGold");
        Sprite* starSprite = Sprite::createWithSpriteFrameName("starGold.png");
        starSprite->setAnchorPoint(Point(0,0));
        starSprite->setPosition(Point(starBody->GetPosition().x * PTM_RATIO, starBody->GetPosition().y * PTM_RATIO));
        this->addChild(starSprite);
        
		ObstacleUserData* starUserData = new ObstacleUserData;
		starUserData->body = starBody;
		starUserData->sprite = starSprite;
		starUserData->fixtureType = FT_PICKUP;
		starBody->SetUserData((void*)starUserData);
    }
    
}
