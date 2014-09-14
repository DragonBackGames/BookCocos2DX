#ifndef __BACKGROUND_GAME_LAYER_H__
#define __BACKGROUND_GAME_LAYER_H__

/* ----------------------------------------------------------------------------
 *
 * Includes
 *
 * ----------------------------------------------------------------------------
 */
#include "cocos2d.h"
#include "CCParallaxScrollNode.h"

USING_NS_CC;

/* ----------------------------------------------------------------------------
 *
 * Class definition
 *
 * ----------------------------------------------------------------------------
 */
class BackgroundGameLayer : public Layer
{
public:
    // Destructor
    ~BackgroundGameLayer();
    // Create a layer
    static BackgroundGameLayer* create();
    // Creates the scene of the component
    static Scene* scene();
    
private:
    // Initialize all resources from the layer
    virtual bool init();
    // standard Cocos2d layer method
    virtual void update(float dt);
   
    // Parallax node
    CCParallaxScrollNode* parallax;
};

#endif // __BACKGROUND_GAME_LAYER_H__
