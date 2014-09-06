#ifndef __OBSTACLE_LAYER_H__
#define __OBSTACLE_LAYER_H__

/* ----------------------------------------------------------------------------
 *
 * Includes
 *
 * ----------------------------------------------------------------------------
 */
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "GB2ShapeCache-x.h"
#include <set>

USING_NS_CC;

#define kMaxObstaclePoints 10000

// broad categories to organize fixtures into
enum FixtureType
{
    FT_PLAYER,
    FT_PICKUP,
    FT_ROCK
};

struct ObstacleUserData
{
    FixtureType fixtureType;
    b2Body* body;
    Sprite* sprite;
};

/* ----------------------------------------------------------------------------
 *
 * Class definition
 *
 * ----------------------------------------------------------------------------
 */
class ObstacleLayer : public Layer
{
public:
    // Constructor
    ObstacleLayer(b2World* world);
    // Destructor
    ~ObstacleLayer();
    // Create a layer
    static ObstacleLayer* create(b2World* world);
	// Generate the obstacles
	void generateObstacle(int quantity);
    
private:
	// Points
	Point obstaclePoints[kMaxObstaclePoints];
	// Obstacle offset
	int offset;
	int offsetRock;
    // Box2d stuff
    b2World* world;
    b2Body* body;
	// Counter of obstacles generated
	int obstacleCounter;
};

#endif // __OBSTACLE_LAYER_H__
