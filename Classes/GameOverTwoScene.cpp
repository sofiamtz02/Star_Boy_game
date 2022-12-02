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
#include "GameOverTwoScene.h"
#include "cocostudio/SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include "MenuLevelScene.h"
#include "LevelDosScene.h"

USING_NS_CC;
using namespace CocosDenshion;
unsigned int score2;


Scene* GameOverTwo::createScene(unsigned int tiempSscore2)
{
    score2 = tiempSscore2;
    return GameOverTwo::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverTwoScene.cpp\n");
}
// on "init" you need to initialize your instance
bool GameOverTwo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
     
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    auto menu_item_1= MenuItemImage::create("st/btn_Retry_1.png","st/btn_Retry_2.png", CC_CALLBACK_1(GameOverTwo::Retry,this));
    auto menu_item_2= MenuItemImage::create("st/btn_home_1.png","st/btn_home_2.png", CC_CALLBACK_1(GameOverTwo::Home,this));
    auto menu_item_3= MenuItemImage::create("st/btn_Levels_1.png","st/btn_Levels_2.png", CC_CALLBACK_1(GameOverTwo::Levels,this));

    //para agregar las posiciones de los elementos
    menu_item_1-> setPosition(Point(visibleSize.width/2,(visibleSize.height/7)*3));
    menu_item_2-> setPosition(Point(visibleSize.width/2,(visibleSize.height/7)*2));
    menu_item_3-> setPosition(Point(visibleSize.width/2,(visibleSize.height/7)*1));

    auto *menu2 = Menu::create(menu_item_1,menu_item_2,menu_item_3,NULL);
    menu2->setPosition(Point(0,0));
    this->addChild(menu2,4);
    

    
    auto fondo = Sprite::create("fondo/back_5.png");
    if(fondo == nullptr){
        problemLoading("'fondo/back_5.png'");
    } 
    else{
        fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo);
    }
    
    auto fondo2 = Sprite::create("fondo/game_1.png");
    if(fondo2 == nullptr){
        problemLoading("'fondo/game_1.png'");
    }
    else{
        fondo2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo2,3);
    }
    
    auto scoreLabel = Label::createWithTTF("Score: "+ std::to_string(score2), "fonts/Marker Felt.ttf", 32);
    scoreLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, 650));
    scoreLabel->setColor(Color3B(94,129,88));
    this->addChild(scoreLabel, 1);
    
    //Save Time Scores
    UserDefault* def = UserDefault::getInstance();
    auto _HighScore = def->getIntegerForKey("HIGHSCORE_TWO", 0); //high_one es mi llave para guardar
    if (score2 > _HighScore) {
        _HighScore = score2;
        def->setIntegerForKey("HIGHSCORE_TWO", _HighScore);
    }
    def->flush();
    
    
    
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(3);
    animFrames.pushBack(SpriteFrame::create("fondo/game_2.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("fondo/game_1.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("fondo/game_2.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    
    Animation* animation = Animation::createWithSpriteFrames(animFrames,.5f);
    Animate* animate = Animate::create(animation);

    // run it and repeat it forever
    fondo2->runAction(RepeatForever::create(animate));
    
    return true;
}

void GameOverTwo::Retry(cocos2d::Ref* sPender){
    CCLOG("Retry");
    auto scene = LevelDos::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}
void GameOverTwo::Home(cocos2d::Ref* pSender){
    CCLOG("HighScores");
    auto scene2 = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene2));
}
void GameOverTwo::Levels(Ref* pSender){
    CCLOG("Levels");
    auto scene3 = MenuLevel::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene3));
}
