//
//  HelloWorldScene.cpp
//  masking
//
//  Created by saiy2k on 15/03/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene() {
    CCScene                             *scene;
    HelloWorld                          *layer;
    
    scene                           =   CCScene::create();
    layer                           =   HelloWorld::create();
    scene->addChild(layer);

    return                              scene;
}

bool HelloWorld::init() {
    CCSprite                            *bg;
    
    if ( !CCLayer::init() )             return false;
    
    bg                              =   CCSprite::create("space.png");
    bg->setPosition( ccp(512, 768/2) );
    addChild(bg);
        
    map                             =   CCSprite::create("worldmap2d.jpg");
    map->setPosition( ccp(512, 768/2) );
    map->retain();
    
    mask                            =   CCSprite::create("worldmapmask.png");
    mask->setPosition( ccp(512, 768/2) );
    mask->retain();
    
    masked                          =   maskedSpriteWithSprite(map, mask, 0, 100);
    addChild(masked);
    
    shade                           =   CCSprite::create("worldmapshade.png");
    shade->setPosition( ccp(512, 768/2) );
    addChild(shade);
    
    this->scheduleUpdate();
    
    return                              true;
}

void HelloWorld::update(float dt) {
    CCSprite                            *m;
    xoff                            +=  dt * 100;
    if (xoff > 1024) {
        xoff                        =   0;
    }
    m                               =   maskedSpriteWithSprite(map, mask, xoff, 120);
    masked->setTexture(m->getTexture());
}

// Credits and Explanation: http://codewars.net/294/masking-sprites-with-cocos2d-x/
CCSprite* HelloWorld::maskedSpriteWithSprite(CCSprite* pTextureSprite, CCSprite* pMaskSprite, float xoffset, float yoffset)
{
    // store the original positions of both sprites
    CCPoint textureSpriteOrigPosition(pTextureSprite->getPosition().x, pTextureSprite->getPosition().y);
    CCPoint maskSpriteOrigPosition(pMaskSprite->getPosition().x, pMaskSprite->getPosition().y);
    
    // convert the texture sprite position into mask sprite coordinate system
    pTextureSprite->setPosition(ccp(pTextureSprite->getContentSize().width/2 - pMaskSprite->getPosition().x + pMaskSprite->getContentSize().width/2 - xoffset, pTextureSprite->getContentSize().height/2 - pMaskSprite->getPosition().y + pMaskSprite->getContentSize().height/2 + yoffset));
    
    // position the mask sprite so that the bottom left corner lies on the (o,o) coordinates
    pMaskSprite->setPosition(ccp(pMaskSprite->getContentSize().width/2, pMaskSprite->getContentSize().height/2));
    
    CCRenderTexture* rt = CCRenderTexture::renderTextureWithWidthAndHeight((int)pMaskSprite->getContentSize().width, (int)pMaskSprite->getContentSize().height);
    
    ccBlendFunc bfMask = ccBlendFunc();
    bfMask.src = GL_ONE;
    bfMask.dst = GL_ZERO;
    pMaskSprite->setBlendFunc(bfMask);
    
    // turn off anti-aliasing around the mask sprite
    pMaskSprite->getTexture()->setAliasTexParameters();
    
    ccBlendFunc bfTexture = ccBlendFunc();
    bfTexture.src = GL_DST_ALPHA;
    bfTexture.dst = GL_ZERO;
    pTextureSprite->setBlendFunc(bfTexture);
    
    rt->begin();
    pMaskSprite->visit();
    pTextureSprite->visit();
    rt->end();
    
    // generate the resulting sprite
    CCSprite* pOutcome = CCSprite::spriteWithTexture(rt->getSprite()->getTexture());
    pOutcome->setFlipY(true);
    
    // restore the original sprite positions
    pTextureSprite->setPosition(textureSpriteOrigPosition);
    pMaskSprite->setPosition(maskSpriteOrigPosition);
    pOutcome->setPosition(maskSpriteOrigPosition);
    
    return pOutcome;
}
