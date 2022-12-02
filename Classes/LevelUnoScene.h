/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __LEVELUNO_SCENE_H__
#define __LEVELUNO_SCENE_H__

#include "cocos2d.h"

class LevelUno : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(); 
    virtual bool init();
    void TimeScore(float);
    unsigned int score1;
    cocos2d::Label* _scoreLabel;
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    cocos2d::Sprite *mySprite;
    cocos2d::Sprite *player_boy;
    cocos2d::Sprite *vill;
    cocos2d::Sprite *border;
    cocos2d::Sprite *platam1;
    cocos2d::Sprite *platam2;
    cocos2d::Sprite *platam3;
    cocos2d::Sprite *platam4;
    cocos2d::Sprite *platam5; 
    cocos2d::Sprite *platam6;
    CREATE_FUNC(LevelUno);
    
    void initPhysics(cocos2d::Sprite* sprite);
    void initplatforms(cocos2d::Sprite* sprite);
    void initVillano(cocos2d::Sprite* sprite);
    void initborder(cocos2d::Sprite* sprite);
    
    //sprite villanos
    void addVillains1(float); //villanos
    void addVillains2(float); //villanos
    void addVillains3(float); //villanos

    void doRemoveFromParentAndCleanup(Node* sender, bool cleanup);
    
    //void update(float);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void StopEffect(float dt);
    unsigned int soundInt;
};

#endif // __LevelUno_SCENE_H__
