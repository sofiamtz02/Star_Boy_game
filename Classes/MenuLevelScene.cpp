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
#include "MenuLevelScene.h"

#include "LevelUnoScene.h"
#include "LevelDosScene.h"
#include "LevelTresScene.h"


USING_NS_CC;

Scene* MenuLevel::createScene()
{
    return MenuLevel::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuLevelScene.cpp\n");
}
// on "init" you need to initialize your instance
bool MenuLevel::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
     
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto menu_item_1 = MenuItemImage::create("st/back_Button_1.png","st/back_Button_2.png", CC_CALLBACK_1(MenuLevel::GoBack,this));
    auto menu_item_2 = MenuItemImage::create("st/level1_Button_1.png","st/level1_Button_2.png", CC_CALLBACK_1(MenuLevel::level1,this));
    auto menu_item_3 = MenuItemImage::create("st/level2_Button_1.png","st/level2_Button_2.png", CC_CALLBACK_1(MenuLevel::level2,this));
    auto menu_item_4 = MenuItemImage::create("st/level3_Button_1.png","st/level3_Button_2.png", CC_CALLBACK_1(MenuLevel::level3,this));


    //para agregar las posiciones de los elementos
    menu_item_1-> setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*4));
    menu_item_2-> setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*3));
    menu_item_3-> setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*2));
    menu_item_4-> setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*1));
    
    auto *menu2 = Menu::create(menu_item_1,menu_item_2,menu_item_3,menu_item_4,NULL);
    menu2->setPosition(Point(0,0));
    this->addChild(menu2);
    
    auto fondo = Sprite::create("fondo/back_1.png");
    if(fondo == nullptr)
    {
        problemLoading("'fondo/back_1.png'");
    }
    else{
        fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo,-4);
    }

    return true;
}


void MenuLevel::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

  

void MenuLevel::GoBack(cocos2d::Ref* pSender){
    CCLOG("GoBack");
    Director::getInstance()->popScene();
}

void MenuLevel::level1(cocos2d::Ref* pSender){
    CCLOG("level 1");
    auto scene = LevelUno::createScene();
    Director::getInstance()-> pushScene(TransitionFade::create(1.0f,scene));
}

void MenuLevel::level2(cocos2d::Ref* pSender){
    CCLOG("level 2");
    auto scene2 = LevelDos::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene2));
}

void MenuLevel::level3(cocos2d::Ref* pSender){
    CCLOG("level 3");
    auto scene3 = LevelTres::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene3));
}

