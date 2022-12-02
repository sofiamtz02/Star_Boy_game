//
//  MenuScene.hpp
//  CocoGame
//
//  Created by Sofía Mtz. on 15/11/22.
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include <stdio.h>

#include "cocos2d.h"

//
class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    cocos2d::MenuItemImage *startMenu;
    cocos2d::MenuItemImage *exitMenu;
    //cocos2d::MenuItemImage *clipMenu;
    
    void changeScene(Ref *pSpender);
    void exitGame(Ref *pSpender);
    //void clipGame(Ref *pSpender);


    CREATE_FUNC(MenuScene);
};
#endif /* MenuScene_hpp */
