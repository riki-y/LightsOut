//
//  GameLayer.cpp
//  LightsOut
//
//  Created by 吉田　理貴 on 2015/07/14.
//
//

#include "GameLayer.h"

USING_NS_CC;

// コンストラクタ
GameLayer::GameLayer()
{
}

// シーンの生成
Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    
    return scene;
}

// 初期化
bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initBackground(); // 背景の初期化
    initGrids(); // グリッドの初期表示
    
    return true;
}

// 背景の初期化
void GameLayer::initBackground()
{
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Point::ZERO);
    background->setPosition(Point::ZERO);
    addChild(background, Z_Background, T_Background);
}

// ボールの初期表示
void GameLayer::initGrids()
{
    for (int x = 1; x <= GRID_NUM_X; x++) {
        for (int y = 1; y <= GRID_NUM_Y; y++) {
            newGrid(GridSprite::GridType::Dark, GridSprite::PositionIndex(x, y));
        }
    }
    
}

// 新規グリッドの作成
GridSprite* GameLayer::newGrid(GridSprite::GridType gridType, GridSprite::PositionIndex positionIndex)
{
    auto grid = GridSprite::create(positionIndex, gridType);
    grid->setPositionIndex(positionIndex);
    
    addChild(grid, ZOrder::Z_Grid);
    
    return grid;
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    
    GridSprite* touchGrid = getTouchGrid(touch->getLocation());
    
    changeAroundGrid(touchGrid);
    
    return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}

// タップした位置のチェック
GridSprite* GameLayer::getTouchGrid(Point touchPos, GridSprite::PositionIndex withoutPosIndex)
{
    for (int x = 1; x <= GRID_NUM_X; x++) {
        for (int y = 1; y <= GRID_NUM_Y; y++) {
            if (x == withoutPosIndex.x && y == withoutPosIndex.y) {
                // 指定位置のボールの場合は、以下の処理を行わない
                continue;
            }
            
            // タップ位置にあるボールかどうかを判断する
            int tag = GridSprite::getGenerateTag(GridSprite::PositionIndex(x, y));
            
            auto grid = (GridSprite*)(getChildByTag(tag));
            if (grid) {
                // 2点間の距離を求める
                float distance = grid->getPosition().getDistance(touchPos);
                
                if (distance <= GRID_SIZE / 2) {
                    return grid;
                }
            }
        }
    }
    return nullptr;
}

void GameLayer::changeAroundGrid(GridSprite* grid)
{
    int x = grid->getPositionIndex().x;
    int y = grid->getPositionIndex().y;
    
    auto upGrid = (GridSprite*)(getChildByTag(GridSprite::getGenerateTag(GridSprite::PositionIndex(x, y+1))));
    changeGridTexture(upGrid);
    
    auto downGrid = (GridSprite*)(getChildByTag(GridSprite::getGenerateTag(GridSprite::PositionIndex(x, y-1))));
    changeGridTexture(downGrid);
    
    auto rightGrid = (GridSprite*)(getChildByTag(GridSprite::getGenerateTag(GridSprite::PositionIndex(x+1, y))));
    changeGridTexture(rightGrid);
    
    auto leftGrid = (GridSprite*)(getChildByTag(GridSprite::getGenerateTag(GridSprite::PositionIndex(x-1, y))));
    changeGridTexture(leftGrid);
    
    changeGridTexture(grid);
}

void GameLayer::changeGridTexture(GridSprite* grid)
{
    if (grid) {
        switch (grid->getGridType()) {
            case GridSprite::GridType::Light:
                grid->changeTexture(GridSprite::GridType::Dark);
                break;
            case GridSprite::GridType::Dark:
                grid->changeTexture(GridSprite::GridType::Light);
                break;
        }
    }
}
