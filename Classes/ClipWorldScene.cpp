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
#include "ClipWorldScene.h"
#include "MenuLevelScene.h"

USING_NS_CC;

Scene* ClipWorld::createScene()
{
    return ClipWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ClipWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool ClipWorld::init()
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


    auto menu_item_1= MenuItemImage::create("st/home_btn.png","st/home_btn.png", CC_CALLBACK_1(ClipWorld::Home,this));

    //para agregar las posiciones de los elementos
    menu_item_1-> setPosition(Point(visibleSize.width/11.4*.7,(visibleSize.height/16)*15));
 
    auto *menu2 = Menu::create(menu_item_1,NULL);
    menu2->setPosition(Point(0,0));
    this->addChild(menu2,1);
    
    
    auto mySprite = Sprite::create("hstory/story.png");
    mySprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(mySprite,0);

    // now lets animate the sprite we moved
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(21);
    animFrames.pushBack(SpriteFrame::create("hstory/story.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-1_1.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-1.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-1.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-1.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-2.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-3.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-4.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-5.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-6.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-7.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-8.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-9.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-10.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-11.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-12.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-13.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-14.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-15.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-16.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("hstory/story-16.png",Rect(0,0,visibleSize.width, visibleSize.height)));


    /* BOY ANIMATION
     animFrames.pushBack(SpriteFrame::create("boy/Starboy_1.png", Rect(0,0,visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)));
    animFrames.pushBack(SpriteFrame::create("boy/Starboy_2.png", Rect(0,0,visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)));
     */

    // create the animation out of the frames
    Animation* animation = Animation::createWithSpriteFrames(animFrames,1.5f);
    Animate* animate = Animate::create(animation);

    // run it and repeat it forever
    mySprite->runAction(RepeatForever::create(animate));
    
    return true;
}

void ClipWorld::menuCloseCallback(Ref* pSender)
{
    //auto * scene = ClipWorld::createScene();
    //Director::getInstance()->pushScene(scene);
    //Director::getInstance()-> replaceScene(scene);
}

void ClipWorld::Home(cocos2d::Ref* sPender){
    CCLOG("Home");
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}
 
