//
//  GameLayer.h
//  LightsOut
//
//  Created by 吉田　理貴 on 2015/07/14.
//
//

#ifndef __LightsOut__GameLayer__
#define __LightsOut__GameLayer__

#include "cocos2d.h"
#include "GridSprite.h"

#define GRID_NUM_X 5
#define GRID_NUM_Y 5

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ

class GameLayer : public cocos2d::Layer
{
protected:
    enum ZOrder
    {
        Z_Background,
        Z_Grid,
    };
    
    enum Tag
    {
        T_Background,
        T_Grid,
    };
    
    void initBackground(); // 背景の初期化
    void initGrids(); // グリッドの初期表示
    
    void changeAroundGrid(GridSprite* grid); // Grid周辺の画像を変更する
    void changeGridTexture(GridSprite* grid); // Gridの画像を変更する
    
    GridSprite* newGrid(GridSprite::GridType gridType, GridSprite::PositionIndex positionIndex); // 新規グリッド作成
    GridSprite* getTouchGrid(cocos2d::Point touchPos, GridSprite::PositionIndex withoutPosIndex = GridSprite::PositionIndex()); // タッチしたグリッドを取得
    
public:
    GameLayer(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GameLayer); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__LightsOut__GameLayer__) */
