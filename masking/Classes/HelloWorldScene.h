//
//  HelloWorldScene.h
//  masking
//
//  Created by saiy2k on 15/03/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer {
public:
    virtual bool init();
    
    // the actual world map that gets masked
    cocos2d::CCSprite                   *map;
    
    // the keyhole picture that masks the `map`
    cocos2d::CCSprite                   *mask;
    
    // the masked output of `map`
    cocos2d::CCSprite                   *masked;
    
    // a shade over the globe to give an impression of depth
    cocos2d::CCSprite                   *shade;
    
    // amount of x-offset to shift the map (for animation)
    float                               xoff;
    
    // function that created the masked sprite
    // Credits and Explanation: http://codewars.net/294/masking-sprites-with-cocos2d-x/
    cocos2d::CCSprite*                  maskedSpriteWithSprite(cocos2d::CCSprite* pTextureSprite,
                                                               cocos2d::CCSprite* pMaskSprite,
                                                               float xoffset,
                                                               float yoffset);
    
    // creates and returns a scene holding a `HelloWorld` layer
    static cocos2d::CCScene*            scene();
    
    // game loop that animates the globe
    void                                update(float dt);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
