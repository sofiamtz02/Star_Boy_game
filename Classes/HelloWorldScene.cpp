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
#include "cocostudio/SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HighScoreScene.h"
#include "InstrScene.h"


USING_NS_CC;
using namespace CocosDenshion; //audio

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
     
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto effects = SimpleAudioEngine::getInstance();
    effects -> stopAllEffects();
    
    auto musica = SimpleAudioEngine::getInstance();
    musica -> stopBackgroundMusic(true);
    //musica -> playBackgroundMusic("audio/Onion_Capers.wav", false);
    musica -> setBackgroundMusicVolume(0.001);
    musica -> playBackgroundMusic("audio/Onion_Capers.wav", true);
    

    auto fondo = Sprite::create("fondo/back_1.png");
    if(fondo == nullptr)
    {
        problemLoading("'fondo/back_1.png'");
    }
    else{
        fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo);
    }

    /*auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(HelloWorld::Play, this));
    auto menu_item_2 = MenuItemFont::create("HighScores", CC_CALLBACK_1(HelloWorld::HighScores, this));
    auto menu_item_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(HelloWorld::Settings, this));*/
    
    auto menu_item_1= MenuItemImage::create("st/Play_Button_GR.png","st/btn-Play_2.png", CC_CALLBACK_1(HelloWorld::Play,this));
    auto menu_item_2= MenuItemImage::create("st/scores_Button_1.png","st/scores_Button_2.png", CC_CALLBACK_1(HelloWorld::HighScores,this));
    auto menu_item_3= MenuItemImage::create("st/clip_Button_1.png","st/btn_clip_2.png", CC_CALLBACK_1(HelloWorld::clip,this));
    auto menu_item_4= MenuItemImage::create("st/btn_quest_1.png","st/btn_quest_2.png", CC_CALLBACK_1(HelloWorld::Instructions,this));

    //para agregar las posiciones de los elementos
    menu_item_1-> setPosition(Point(visibleSize.width/2,(visibleSize.height/6)*4));
    menu_item_2-> setPosition(Point(visibleSize.width/2,(visibleSize.height/6)*3));
    menu_item_3-> setPosition(Point(visibleSize.width/2,(visibleSize.height/6)*2));
    menu_item_4-> setPosition(Point(visibleSize.width/2,(visibleSize.height/6)*1));

    auto *menu2 = Menu::create(menu_item_1,menu_item_2,menu_item_3,menu_item_4,NULL);
    menu2->setPosition(Point(0,0));
    this->addChild(menu2,5);
    
    
    auto fondo2 = Sprite::create("fondo/back_star_1.png");
    auto fondo3 = Sprite::create("fondo/back_starr_0.png");
    if(fondo2 == nullptr){
        problemLoading("'fondo/back_star_1.png'");
    } else{
        fondo2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo2,3);
    }
    
    if(fondo3 == nullptr){
        problemLoading("'fondo/back_starr_0.png'");
    } else{
        fondo3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo3,2);
    }

    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(3);
    animFrames.pushBack(SpriteFrame::create("fondo/back_star_2.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("fondo/back_star_1.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    animFrames.pushBack(SpriteFrame::create("fondo/back_star_2.png",Rect(0,0,visibleSize.width, visibleSize.height)));
    
    Animation* animation = Animation::createWithSpriteFrames(animFrames,.5f);
    Animate* animate = Animate::create(animation);

    // run it and repeat it forever
    fondo2->runAction(RepeatForever::create(animate));
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //auto * scene = TestScene::createScene();
    //Director::getInstance()->pushScene(scene);
    //Director::getInstance()-> replaceScene(scene);
}

void HelloWorld::Play(cocos2d::Ref* sPender){
    CCLOG("Play");
    auto scene = MenuLevel::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
    //Director::getInstance()-> pushScene(scene);
}
void HelloWorld::HighScores(cocos2d::Ref* pSender){
    CCLOG("HighScores");
    auto score = HighScore::createScene();
    //Director::getInstance()->pushScene(score);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,score));

}
void HelloWorld::Settings(Ref* pSender){
    CCLOG("Settings");
    //auto scene = TestScene::createScene();
    //Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}
void HelloWorld::clip(Ref* pSender){
    CCLOG("clip");
    auto sceneAni = ClipWorld::createScene();
    Director::getInstance()->pushScene(sceneAni);
}

void HelloWorld::Instructions(Ref* pSender){
    CCLOG("clip");
    auto sceneIns = Instr::createScene();
    Director::getInstance()->pushScene(sceneIns);
}
 
