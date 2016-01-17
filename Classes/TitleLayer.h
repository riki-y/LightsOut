//
//  TitleLayer.h
//  LightsOut
//
//  Created by 吉田　理貴 on 2015/07/28.
//
//

#ifndef __LightsOut__TitleLayer__
#define __LightsOut__TitleLayer__

#include "cocos2d.h"

class TitleLayer : public cocos2d::Layer
{
protected:
    enum ZOrder
    {
        Z_Background,
    };
    
    enum Tag
    {
        T_Background,
    };
    
    void initBackground(); // 背景の初期化
    void createAndMoveGameScene(); // ゲームシーンを作成し、移動

public:
    TitleLayer(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(TitleLayer); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__LightsOut__TitleLayer__) */
