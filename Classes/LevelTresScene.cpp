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
#include "LevelTresScene.h"
#include "GameOverThreeScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/SimpleAudioEngine.h"
#include <stdlib.h> //For rand()


USING_NS_CC;
using namespace CocosDenshion; //audio

Scene* LevelTres::createScene()
{
    // create the scene with physics enabled
    auto scene = Scene::createWithPhysics();

    // set gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0, -80));
    scene->getPhysicsWorld()->setSpeed(1.0f);

    // optional: set debug draw //para poner los cuadritos rojos
     //scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
    
    auto layer = LevelTres::create();
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
bool LevelTres::init()
{
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    
     //audio
    auto effects = SimpleAudioEngine::getInstance();
    effects -> stopAllEffects();
    
    auto musica = SimpleAudioEngine::getInstance();
    musica -> stopBackgroundMusic(true);
    //musica -> playBackgroundMusic("audio/Le_Grand_Chase.wav", false);
    musica -> setBackgroundMusicVolume(0.01);
    musica -> playBackgroundMusic("audio/Le_Grand_Chase.wav", true);

    //Physics
    //this->getPhysicsWorld()->setGravity(Vect(0,0));
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //para marca roja
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    //Event Listener
    auto listener = EventListenerKeyboard().create();
    listener->onKeyPressed = CC_CALLBACK_2(LevelTres::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(LevelTres::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //Collisions
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelTres::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //fondo inv
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,2); //el 2 es el grosor de borde
    auto edgeNode = Node::create();
    edgeNode -> setPosition(Point (visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode -> setPhysicsBody(edgeBody);
    this-> addChild(edgeNode, 5);
    
    //background sprite
    auto fondo = Sprite::create("fondo/back_4.png");
    if(fondo == nullptr)
    {
        problemLoading("'fondo/back_4.png'");
    }
    else{
        fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(fondo,-4);
    }
    
    score = 0;

    
    //this->scheduleUpdate();

    
    auto director = Director::getInstance();
    //auto tamano = director -> getWinSize();
    player_boy = Sprite::create("boy/Starboy_4.png");
    player_boy -> setAnchorPoint(Vec2::ZERO);
    
    //player_boy -> setPosition(Point(visibleSize.width/2.3 + origin.x,visibleSize.width+2 + origin.y ));
    //player_boy -> setPosition(Point(visibleSize.width/2.3 + origin.x, visibleSize.width/2 +origin.y));
    player_boy -> setPosition(Point(visibleSize.width/1.8 + origin.x,  origin.y+250 ));//para estar arriba

    initPhysics(player_boy); //para poner physica en el monito
//IMPORTANTE VOLVER A AGREGAR
    this -> addChild(player_boy, 5);//agregar al
    
    platam1 = Sprite::create("st/bk_crayon.png");
    platam2 = Sprite::create("st/bk_crayon.png");
    platam3 = Sprite::create("st/bk_crayon.png");
    platam4 = Sprite::create("st/bk_crayon.png");
    platam5 = Sprite::create("st/bk_crayon.png");
    platam6 = Sprite::create("st/bk_crayon.png");

    platam1 -> setAnchorPoint(Vec2::ZERO);
    platam2 -> setAnchorPoint(Vec2::ZERO);
    platam3 -> setAnchorPoint(Vec2::ZERO);
    platam4 -> setAnchorPoint(Vec2::ZERO);
    platam5 -> setAnchorPoint(Vec2::ZERO);
    platam6 -> setAnchorPoint(Vec2::ZERO);

    platam1 -> setPosition(Point(visibleSize.width/2.0 + origin.x, origin.y+50));
    platam2 -> setPosition(Point(visibleSize.width/10 + origin.x*.1, visibleSize.width/5 +origin.y));
    platam3 -> setPosition(Point(visibleSize.width/1.8 + origin.x, visibleSize.width/2.2 +origin.y));
    platam4 -> setPosition(Point(visibleSize.width/6.4 + origin.x, visibleSize.width/1.6 +origin.y));
    platam5 -> setPosition(Point(visibleSize.width/2.8 + origin.x, visibleSize.width/1.1 +origin.y));
    platam6 -> setPosition(Point(visibleSize.width/6.3 + origin.x, visibleSize.width/.9 +origin.y));
    //platam7 -> setPosition(Point(visibleSize.width/2.3 + origin.x, origin.y*5));
    
    initplatforms(platam1); //para poner physica en el monito
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

    border = Sprite::create("fondo/trs_border.png");
    border -> setAnchorPoint(Vec2::ZERO);
    border -> setPosition(Point(0, 0));
    initborder(border);
    this -> addChild(border, 3);
    
    
    //----------------------------------------------------------------------
    schedule(CC_SCHEDULE_SELECTOR(LevelTres::TimeScore), 1.7f);
    auto CLabel2 = Label::createWithTTF("Score: ", "fonts/Marker Felt.ttf", 20);
    _scoreLabel = Label::createWithTTF(std::to_string(score),"fonts/Marker Felt.ttf",20);

    CLabel2->setPosition(Vec2(50, visibleSize.height - 30));
    _scoreLabel->setPosition(Vec2(CLabel2->getPosition().x + 40, visibleSize.height - 30));

    _scoreLabel->setTextColor(Color4B::BLACK);
    _scoreLabel->enableOutline(Color4B::WHITE, 1);
    CLabel2->setTextColor(Color4B::BLACK);
    CLabel2->enableOutline(Color4B::WHITE, 1);
    
    this->addChild(_scoreLabel, 1);
    this->addChild(CLabel2, 1);
    //----------------------------------------------------------------------

    scheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    schedule(CC_SCHEDULE_SELECTOR(LevelTres::addVillains1), 7.0f); //derecha a izq
    DelayTime *pause = DelayTime::create(2);
    schedule(CC_SCHEDULE_SELECTOR(LevelTres::addVillains2), 9.0f); //izq a derecha
    schedule(CC_SCHEDULE_SELECTOR(LevelTres::addVillains3), 9.0f);

    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);

    return true;
}
 
void LevelTres::initPhysics(cocos2d::Sprite* sprite) //el monito
{
    auto body = PhysicsBody::createBox(Size(32,92), PhysicsMaterial(0,0,1)); //Physics Material es para rebotar
    //auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 5 +10);

    body->setContactTestBitmask(1);
    body->setCollisionBitmask(1);
    //body->setDynamic(true);
    body->setDynamic(true);
    sprite->setPhysicsBody(body);

}

void LevelTres::initplatforms(cocos2d::Sprite* sprite2)
{
    auto spriteBody = PhysicsBody::createBox(sprite2->getContentSize(), PhysicsMaterial(0,0,1)); //Physics Material
    spriteBody->setContactTestBitmask(3);
    spriteBody->setCollisionBitmask(3);
    spriteBody->setDynamic(false);
    //spriteBody -> setTag(2);
    sprite2->setPhysicsBody(spriteBody);
    
}

void LevelTres::initVillano(cocos2d::Sprite* sprite)
{
    auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 4 +10);
    spriteBody->setContactTestBitmask(2);
    spriteBody->setCollisionBitmask(2);
    spriteBody->setDynamic(false);
    sprite->setPhysicsBody(spriteBody);
}

void LevelTres::initborder(cocos2d::Sprite* sprite){
    auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0,0,0));
    spriteBody->setContactTestBitmask(2);
    spriteBody->setCollisionBitmask(2);

    spriteBody->setDynamic(false);
    sprite->setPhysicsBody(spriteBody);
}

 
void LevelTres::addVillains1(float delta) //de derecha a izq
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();
    
    vill = Sprite::create("villano/villain_BB.png");
    vill -> setAnchorPoint(Vec2::ZERO);
    vill->setPosition(Point(visibleSize.width+20,  visibleSize.height/(random(1,6))  ));
    initVillano(vill);
    //vill -> setTag(20);
    //vill -> setScale(-1,1);
    vill->getPhysicsBody();
    this->addChild(vill, 1);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
    soundInt = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav",true);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav");

    auto action = Sequence::create(
        MoveBy::create((random(3,5)), Vec2(-visibleSize.width - 200, (random(0,600)) )), //mover en x, y
        CallFuncN::create(CC_CALLBACK_1(LevelTres::doRemoveFromParentAndCleanup, this, true)), NULL);
    //this-> schedule(CC_SCHEDULE_SELECTOR(LevelTres::StopEffect(2)));
    //DelayTime *pause = DelayTime::create(3);
    vill->runAction(action);
    

}

void LevelTres::addVillains2(float delta)// de izq a derecha
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();
    
    vill = Sprite::create("villano/villain_B.png");
    vill -> setAnchorPoint(Vec2::ZERO);
    vill-> setPosition(Point(-visibleSize.width -50,  visibleSize.height/(random(1,6))));
    initVillano(vill);
    //vill -> setTag(20);
    vill->getPhysicsBody();
    this->addChild(vill, 1);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
    soundInt = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav",true);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav");


    //segundo es el angulo visibleSize.width+100 visibleSize.height+100
    auto action = Sequence::create( //el 6, es para la velocidad
        MoveBy::create((random(3,5)), Vec2(+ visibleSize.width + 500, (random(50,500)))), //mover en x, y
        CallFuncN::create(CC_CALLBACK_1(LevelTres::doRemoveFromParentAndCleanup, this, true)), NULL);
    //DelayTime *pause = DelayTime::create(3);
    vill->runAction(action);
}



void LevelTres::addVillains3(float delta)// de izq a derecha
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();
    
    vill = Sprite::create("villano/villain_B.png");
    vill -> setAnchorPoint(Vec2::ZERO);
    vill-> setPosition(Point(-visibleSize.width -50, 0+(random(50,500)) ));
    initVillano(vill);
    vill->getPhysicsBody();
    this->addChild(vill, 1);
    
    //efects
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
    soundInt = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/cat_bell.wav");

    //segundo es el angulo visibleSize.width+100 visibleSize.height+100
    auto action = Sequence::create( //el 6, es para la velocidad
        MoveBy::create((random(3,6)), Vec2(+visibleSize.width +500, (random(0,500)))), //mover en x, y
        CallFuncN::create(CC_CALLBACK_1(LevelTres::doRemoveFromParentAndCleanup, this, true)), NULL);
    DelayTime *pause = DelayTime::create(3);
    vill->runAction(action);

}

void LevelTres::doRemoveFromParentAndCleanup(Node* sender, bool cleanup)
{
    sender->removeFromParentAndCleanup(cleanup);
}

void LevelTres::StopEffect(float dt){
    CocosDenshion::SimpleAudioEngine::getInstance()-> stopEffect(soundInt);
}

void LevelTres::TimeScore(float delta)
{
    score++;
    _scoreLabel->setString(std::to_string(score));
}

bool LevelTres::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    //Check if the bodies have collided
    if ( (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        CCLOG("Collision A has occured");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundInt);
        CocosDenshion::SimpleAudioEngine::getInstance()-> stopAllEffects();
        
        CCLOG("Score: %i", score);

        auto scene = GameOverThree::createScene(score);
        Director::getInstance()->pushScene(TransitionFade::create(0.2f, scene));
        removeFromParentAndCleanup(true);

    }
    return true;
}

void LevelTres::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto position_ = player_boy->getPosition();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        CCLOG("Key flecha derecha pressed");
        if (position_.x <= visibleSize.width)
        {
            auto action = RepeatForever::create(MoveBy::create(.1, Vec2(10, 0)));
            player_boy->setRotation(0);
            player_boy->runAction(action);
            //player_boy->stopAction(action);
        }
    }

    if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        CCLOG("Key flecha izquirda pressed");
        if (position_.x >= origin.x)
        {
            auto action = RepeatForever::create(MoveBy::create(.1, Vec2(-10, 0)));
            player_boy->setRotation(0);
            player_boy->runAction(action);
        }

    }

    if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) //saltar con flecha arriba
    {
        CCLOG("Key flecha arriba pressed");
        if (position_.y >= 0)//origin.y
        {
            auto action = RepeatForever::create(MoveBy::create(.1, Vec2(0, 17)));
            player_boy->setRotation(0);
            player_boy->runAction(action);

        }
    }
}

void LevelTres::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        CCLOG("Key derecha pressed");
        player_boy->stopAllActions();
    }

    if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        CCLOG("Key izquierda pressed");
        player_boy->stopAllActions();
    }

    if (key == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        CCLOG("Key arriba pressed");
        player_boy->stopAllActions();
    }
 
}
