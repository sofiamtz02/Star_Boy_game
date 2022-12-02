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
#include "GameOverThreeScene.h"
#include "cocostudio/SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include "MenuLevelScene.h"
#include "HighScoreScene.h"

USING_NS_CC;

Scene* HighScore::createScene( )
{
    return HighScore::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverThreeScene.cpp\n");
}
// on "init" you need to initialize your instance
bool HighScore::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();


    //BackGround
    auto background = Sprite::create("fondo/score_bck.png");
    if(background == nullptr)
    {
        problemLoading("'fondo/score_bck.png'");
    }
    else{
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(background,-4);
    }

        auto menu_item_1 = MenuItemImage::create("st/back_Button_1.png","st/back_Button_2.png", CC_CALLBACK_1(HighScore::Back,this));
        auto menu_item_2 = MenuItemImage::create("st/btn_Reset_1.png","st/btn_Reset_2.png", CC_CALLBACK_1(HighScore::Reset,this));
        auto red = Sprite::create("st/level1_Button_2.png");
        auto yellow = Sprite::create("st/level2_Button_2.png");
        auto black = Sprite::create("st/level3_Button_2.png");
    
        menu_item_1->setScale(.8);
        menu_item_2->setScale(.8);
        red->setScale(.8);
        yellow->setScale(.8);
        black->setScale(.8);
    
        //add positions
        menu_item_1-> setPosition(Point((visibleSize.width/7)*2,(visibleSize.height/8)*3));
        menu_item_2-> setPosition(Point((visibleSize.width/7)*4+20,(visibleSize.height/8)*3));
    
        red-> setPosition(Point((visibleSize.width/4)*1-8,(visibleSize.height/8)*5));
        yellow-> setPosition(Point((visibleSize.width/4)*2,(visibleSize.height/8)*5));
        black-> setPosition(Point((visibleSize.width/4)*3+8,(visibleSize.height/8)*5));
    
        auto *menu2 = Menu::create(menu_item_1,menu_item_2, NULL);
        menu2->setPosition(Point(0,0));
        this->addChild(menu2,4);
        this->addChild(red,2);
        this->addChild(yellow,2);
        this->addChild(black,2);
    
        UserDefault* def = UserDefault::getInstance();
        auto highScore_RED = def->getIntegerForKey("HIGHSCORE_ONE");
        auto highScore_YELLOW = def->getIntegerForKey("HIGHSCORE_TWO");
        auto highScore_BLACK = def->getIntegerForKey("HIGHSCORE_THREE");
        def->flush();
    
        auto scoreRED = Label::createWithTTF(std::to_string(highScore_RED), "fonts/Marker Felt.ttf", 25);
        scoreRED->setTextColor(Color4B::BLACK);
        scoreRED->enableOutline(Color4B::WHITE, 1);
        scoreRED->setPosition(Vec2((visibleSize.width/4)*1-8, (visibleSize.height/8)*4+20));
        this->addChild(scoreRED, 1);

        auto scoreYELLOW = Label::createWithTTF(std::to_string(highScore_YELLOW), "fonts/Marker Felt.ttf", 25);
        scoreYELLOW->setTextColor(Color4B::BLACK);
        scoreYELLOW->enableOutline(Color4B::WHITE, 1);
        scoreYELLOW->setPosition(Vec2((visibleSize.width/4)*2, (visibleSize.height/8)*4+20));
        this->addChild(scoreYELLOW, 1);

        auto scoreBLACK = Label::createWithTTF(std::to_string(highScore_BLACK), "fonts/Marker Felt.ttf", 25);
        scoreBLACK->setTextColor(Color4B::BLACK);
        scoreBLACK->enableOutline(Color4B::WHITE, 1);
        scoreBLACK->setPosition(Vec2((visibleSize.width/4)*3+8, (visibleSize.height/8)*4+20));
        this->addChild(scoreBLACK, 1);
 
    
        //ANIMATION
        auto fondo2 = Sprite::create("fondo/back_highScr-2.png");
        if(fondo2 == nullptr){
            problemLoading("'fondo/back_highScr-2.png'");
        } else{
            fondo2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            this->addChild(fondo2,3);
        }
    
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(3);
        animFrames.pushBack(SpriteFrame::create("fondo/back_highScr-3.png",Rect(0,0,visibleSize.width, visibleSize.height)));
        animFrames.pushBack(SpriteFrame::create("fondo/back_highScr-2.png",Rect(0,0,visibleSize.width, visibleSize.height)));
        animFrames.pushBack(SpriteFrame::create("fondo/back_highScr-3.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    
        Animation* animation = Animation::createWithSpriteFrames(animFrames,.5f);
        Animate* animate = Animate::create(animation);

        // run it and repeat it forever
        fondo2->runAction(RepeatForever::create(animate));
        
    
        return true;
}

void HighScore::Reset(cocos2d::Ref* sPender){
    CCLOG("Reset");
    UserDefault* def = UserDefault::getInstance();
    def->deleteValueForKey("HIGHSCORE_ONE");
    def->deleteValueForKey("HIGHSCORE_TWO");
    def->deleteValueForKey("HIGHSCORE_THREE");
    
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}
void HighScore::Back(cocos2d::Ref* pSender){
    CCLOG("HighScores");
    auto scene2 = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene2));
}
