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
#include "HelloWorldScene.h"
#include "InstrScene.h"
#include "MenuLevelScene.h"

USING_NS_CC;

Scene* Instr::createScene()
{
    return Instr::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ClipWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool Instr::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
     
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
   
    auto fondo = Sprite::create("fondo/back_1.png");
    if(fondo == nullptr)
    {
        problemLoading("'fondo/back_1.png'");
    }
    else{
        fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo);
    }


    auto menu_item_1= MenuItemImage::create("st/home_btn.png","st/home_btn.png", CC_CALLBACK_1(Instr::Home,this));

    //para agregar las posiciones de los elementos
    menu_item_1-> setPosition(Point(visibleSize.width-50,(visibleSize.height/16)*15));
 
    auto *menu2 = Menu::create(menu_item_1,NULL);
    menu2->setPosition(Point(0,0));
    this->addChild(menu2,1);
    
    auto mySprite = Sprite::create("how/extr_1.png");
    mySprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(mySprite,0);

    // now lets animate the sprite we moved
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(9);
    animFrames.pushBack(SpriteFrame::create("how/extr_1.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_2.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_3.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_4.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_5.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_6.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_7.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_8.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("how/extr_8.png",Rect(0,0,visibleSize.width, visibleSize.height)));

    // create the animation out of the frames
    Animation* animation = Animation::createWithSpriteFrames(animFrames,3.0f);
    Animate* animate = Animate::create(animation);

    // run it and repeat it forever
    mySprite->runAction(RepeatForever::create(animate));
    
    return true;
}

void Instr::menuCloseCallback(Ref* pSender)
{
    //auto * scene = Instr::createScene();
    //Director::getInstance()->pushScene(scene);
    //Director::getInstance()-> replaceScene(scene);
}

void Instr::Home(cocos2d::Ref* sPender){
    CCLOG("Home");
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}
 
