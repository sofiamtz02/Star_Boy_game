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
#include "LevelDosScene.h"
#include "GameOverTwoScene.h"
#include "ui/CocosGUI.h"
#include <stdlib.h> //For rand()
#include "cocostudio/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


Scene* LevelDos::createScene()
{
    // create the scene with physics enabled
    auto scene = Scene::createWithPhysics();

    // set gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0, -100));
    scene->getPhysicsWorld()->setSpeed(1.0f);

    // optional: set debug draw //para poner los cuadritos rojos
    //scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

    auto layer = LevelDos::create();
    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool LevelDos::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    //audio
    auto effects = SimpleAudioEngine::getInstance();
    effects -> stopAllEffects();
    
    auto musica = SimpleAudioEngine::getInstance();
    effects -> stopBackgroundMusic(true);
    //musica -> playBackgroundMusic("audio/Run_Amok.wav", false);
    musica -> setBackgroundMusicVolume(0.01);
    musica -> playBackgroundMusic("audio/Run_Amok.wav", true);
    //Physics
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //Event Listener
    auto listener = EventListenerKeyboard().create();
    listener->onKeyPressed = CC_CALLBACK_2(LevelDos::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(LevelDos::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //Collisions
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelDos::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //BackGround
    auto background = Sprite::create("fondo/back_3.png");
    if(background == nullptr)
    {
        problemLoading("'fondo/back_3.png'");
    }
    else{
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(background,-4);
    }
    score2 = 0;

    //barrera invisible
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,2);
    auto edgeNode = Node::create();
    edgeNode -> setPosition(Point (visibleSize.width / 2 + origin.x, visibleSize.height /2 + origin.y));
    edgeNode -> setPhysicsBody(edgeBody);
    this-> addChild(edgeNode, 5);
    
    //Sprite Personaje
    auto director = Director::getInstance();
    player_boy = Sprite::create("boy/Starboy_4.png");
    player_boy -> setAnchorPoint(Vec2::ZERO);
    player_boy -> setPosition(Point(visibleSize.width/6.3 + origin.x, origin.y+24));
    initPhysics(player_boy); //para poner physica en el monito
    this -> addChild(player_boy, 5);
  
    platam1 = Sprite::create("st/yw_crayon.png");
    platam2 = Sprite::create("st/yw_crayon.png");
    platam3 = Sprite::create("st/yw_crayon.png");
    platam4 = Sprite::create("st/yw_crayon.png");
    platam5 = Sprite::create("st/yw_crayon.png");
    platam6 = Sprite::create("st/yw_crayon.png");

    platam1 -> setAnchorPoint(Vec2::ZERO);
    platam2 -> setAnchorPoint(Vec2::ZERO);
    platam3 -> setAnchorPoint(Vec2::ZERO);
    platam4 -> setAnchorPoint(Vec2::ZERO);
    platam5 -> setAnchorPoint(Vec2::ZERO);
    platam6 -> setAnchorPoint(Vec2::ZERO);

    platam1 -> setPosition(Point(visibleSize.width/8.1 + origin.x, origin.y*5));
    platam2 -> setPosition(Point(visibleSize.width/1.6 + origin.x*.1, visibleSize.height/6.5 +origin.y));
    platam3 -> setPosition(Point(visibleSize.width/10 + origin.x, visibleSize.height/4.1 +origin.y));
    platam4 -> setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/3.3 +origin.y+90));
    platam5 -> setPosition(Point(visibleSize.width/8 + origin.x +15, visibleSize.height/3 +origin.y+170));
    platam6 -> setPosition(Point(visibleSize.width/2.8 + origin.x, visibleSize.height/2 +origin.y+175));
    //platam7 -> setPosition(Point(visibleSize.width/2.3 + origin.x, origin.y*5));

    //estática plataforma
    initplatforms(platam1);
    initplatforms(platam2);
    initplatforms(platam3);
    initplatforms(platam4);
    initplatforms(platam5);
    initplatforms(platam6);
    
    this -> addChild(platam1, 4);
    this -> addChild(platam2, 4);
    this -> addChild(platam3, 4);
    this -> addChild(platam4, 4);
    this -> addChild(platam5, 4);
    this -> addChild(platam6, 4);
    
    border = Sprite::create("fondo/trs_border.png");
    border -> setAnchorPoint(Vec2::ZERO);
    border -> setPosition(Point(0, 0));
    initborder(border);
    this -> addChild(border, 3);
    
    schedule(CC_SCHEDULE_SELECTOR(LevelDos::TimeScore), 1.7f);
    auto CLabel2 = Label::createWithTTF("Score: ", "fonts/Marker Felt.ttf", 20);
    _scoreLabel2 = Label::createWithTTF(std::to_string(score2),"fonts/Marker Felt.ttf",20);

    CLabel2->setPosition(Vec2(50, visibleSize.height - 30));
    _scoreLabel2->setPosition(Vec2(CLabel2->getPosition().x + 40, visibleSize.height - 30));

    _scoreLabel2->setTextColor(Color4B::BLACK);
    _scoreLabel2->enableOutline(Color4B::WHITE, 1);
    CLabel2->setTextColor(Color4B::BLACK);
    CLabel2->enableOutline(Color4B::WHITE, 1);
    
    this->addChild(_scoreLabel2, 1);
    this->addChild(CLabel2, 1);

    
    scheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    schedule(CC_SCHEDULE_SELECTOR(LevelDos::addVillains1), 7.0f); //derecha a izq
    //DelayTime *pause = DelayTime::create(2);
    schedule(CC_SCHEDULE_SELECTOR(LevelDos::addVillains2), 7.0f); //izq a derecha
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    return true;
}
 
void LevelDos::StopEffect(float dt){
    CocosDenshion::SimpleAudioEngine::getInstance()-> stopEffect(soundInt);
    
}
void LevelDos::initPhysics(cocos2d::Sprite* sprite) //el monito
{
   auto body = PhysicsBody::createBox(Size(32,83), PhysicsMaterial(0,0,1));
   body->setContactTestBitmask(1);
   body->setCollisionBitmask(1);
   body->setDynamic(true);
   sprite->setPhysicsBody(body);

}

void LevelDos::initplatforms(cocos2d::Sprite* sprite2)
{
   auto spriteBody = PhysicsBody::createBox(sprite2->getContentSize(), PhysicsMaterial(0,0,1)); //Physics Material
   spriteBody->setContactTestBitmask(3);
   spriteBody->setCollisionBitmask(3);
   spriteBody->setDynamic(false);
   sprite2->setPhysicsBody(spriteBody);
   
}

void LevelDos::initVillano(cocos2d::Sprite* sprite)
{
   auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 5 +10);
   spriteBody->setContactTestBitmask(2);
   spriteBody->setCollisionBitmask(2);
   spriteBody->setDynamic(false);
   sprite->setPhysicsBody(spriteBody);
}

void LevelDos::initborder(cocos2d::Sprite* sprite){
   auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0,0,0));
   spriteBody->setContactTestBitmask(2);
   spriteBody->setCollisionBitmask(2);
   spriteBody->setDynamic(false);
   sprite->setPhysicsBody(spriteBody);
}


void LevelDos::addVillains1(float delta) //de derecha a izq
{
   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();
   auto director = Director::getInstance();
   
   vill = Sprite::create("villano/villain_AA.png");
   vill -> setAnchorPoint(Vec2::ZERO);
   vill->setPosition(Point(visibleSize.width+20,  visibleSize.height/(random(0,6))  ));
   initVillano(vill);
   vill->getPhysicsBody();
   this->addChild(vill, 1);

    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    soundInt = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav",true);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav");


   auto action = Sequence::create(
       MoveBy::create((random(4,7)), Vec2(-visibleSize.width - 200, 0+(random(-1,700)) )),
       CallFuncN::create(CC_CALLBACK_1(LevelDos::doRemoveFromParentAndCleanup, this, true)), NULL);
   vill->runAction(action);
}

void LevelDos::addVillains2(float delta)// de izq a derecha
{
   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();
   auto director = Director::getInstance();
   
   vill = Sprite::create("villano/villain_A.png");
   vill -> setAnchorPoint(Vec2::ZERO);
   vill-> setPosition(Point(visibleSize.width/10-100,  (random(0,600))));
   initVillano(vill);
   vill->getPhysicsBody();
   this->addChild(vill, 1);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    soundInt = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav",true);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav");

   auto action = Sequence::create( //el 6, es para la velocidad
       MoveBy::create((random(4,7)), Vec2(+ visibleSize.width + 200, 0)),
       CallFuncN::create(CC_CALLBACK_1(LevelDos::doRemoveFromParentAndCleanup, this, true)), NULL);
   DelayTime *pause = DelayTime::create(2);
   vill->runAction(action);
}

void LevelDos::doRemoveFromParentAndCleanup(Node* sender, bool cleanup)
{
   sender->removeFromParentAndCleanup(cleanup);
}

void LevelDos::TimeScore(float delta)
{
    score2++;
    _scoreLabel2->setString(std::to_string(score2));
}


bool LevelDos::onContactBegin(cocos2d::PhysicsContact& contact) {
   PhysicsBody *a = contact.getShapeA()->getBody();
   PhysicsBody *b = contact.getShapeB()->getBody();

   //Check if the bodies have collided
    if ( (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        CCLOG("Collision A has occured");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
        CocosDenshion::SimpleAudioEngine::getInstance()-> stopAllEffects();
        
        CCLOG("Score: %i", score2);

        auto scene = GameOverTwo::createScene(score2);
        Director::getInstance()->pushScene(TransitionFade::create(0.2f, scene));
        removeFromParentAndCleanup(true);

    }
   return true;
}



void LevelDos::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
   auto visibleSize = Director::getInstance()->getVisibleSize();
   auto position_ = player_boy->getPosition();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();
   if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
       CCLOG("Key flecha derecha pressed");
       if (position_.x <= visibleSize.width) {
           auto action = RepeatForever::create(MoveBy::create(.1, Vec2(12, 0)));
           player_boy->setRotation(0);
           player_boy->runAction(action);
       }
   }

   if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
       if (position_.x >= origin.x){
           auto action = RepeatForever::create(MoveBy::create(.1, Vec2(-12, 0)));
           player_boy->setRotation(0);
           player_boy->runAction(action);
       }
   }

   if (key == EventKeyboard::KeyCode::KEY_UP_ARROW){
       if (position_.y >= 0){
           auto action = RepeatForever::create(MoveBy::create(.09, Vec2(0, 18)));
           player_boy->setRotation(0);
           player_boy->runAction(action);

       }
   }
}

void LevelDos::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event){
   if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
       CCLOG("Key derecha pressed");
       player_boy->stopAllActions();
   }

   if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
       CCLOG("Key izquierda pressed");
       player_boy->stopAllActions();
   }

   if (key == EventKeyboard::KeyCode::KEY_UP_ARROW){
       CCLOG("Key arriba pressed");
       player_boy->stopAllActions();
   }

}
