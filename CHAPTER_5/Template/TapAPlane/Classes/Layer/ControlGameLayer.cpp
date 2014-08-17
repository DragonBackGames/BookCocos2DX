#include "ControlGameLayer.h"
#include "MenuScene.h"

ControlGameLayer::~ControlGameLayer()
{
    
}

ControlGameLayer* ControlGameLayer::create()
{
    ControlGameLayer* layer = new ControlGameLayer();
    layer->init();
    return layer;
}

bool ControlGameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}

void ControlGameLayer::update(float dt)
{

}

void ControlGameLayer::clickPauseButton(Ref* sender)
{
    
}
