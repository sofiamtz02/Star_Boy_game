//
//  MenuScene.cpp
//  CocoGame
//
//  Created by Sofía Mtz. on 15/11/22.
//

#include "MenuScene.hpp"
#include "HelloWorldScene.h"

    
USING_NS_CC;

Scene* MenuScene::createScene(){
    return MenuScene::create();
};
 
// on "init" you need to initialize your instance
bool MenuScene::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    startMenu = MenuItemImage::create("st/btn-Play_1.png", "st/btn-Play_2.png", CC_CALLBACK_1(MenuScene::changeScene,this)); 
    
    auto menu = Menu::create(startMenu, exitMenu, nullptr);
    //auto menu ->setPosition(Point::Zero);
    startMenu -> setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    
    
    return true;
}
void MenuScene::changeScene(Ref* pSender)
{
    auto scene = HelloWorld::createScene();
     Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}

void MenuScene::exitGame(Ref* pSender)
{
    auto scene = HelloWorld::createScene();
     Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}

//void MenuScene::clipGame(Ref* pSender) { }
  
