//
//  TitleLayer.cpp
//  LightsOut
//
//  Created by 吉田　理貴 on 2015/07/28.
//
//

#include "TitleLayer.h"
#include "GameLayer.h"

USING_NS_CC;

// コンストラクタ
TitleLayer::TitleLayer()
{
}

// シーンの生成
Scene* TitleLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleLayer::create();
    scene->addChild(layer);
    
    return scene;
}

// 初期化
bool TitleLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TitleLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TitleLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(TitleLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initBackground(); // 背景の初期化
    
    return true;
}

// 背景の初期化
void TitleLayer::initBackground()
{
    auto background = Sprite::create("title.png");
    background->setAnchorPoint(Point::ZERO);
    background->setPosition(Point::ZERO);
    addChild(background, Z_Background, T_Background);
}

bool TitleLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    return true;
}

void TitleLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void TitleLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
    createAndMoveGameScene();
}

void TitleLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}

// ゲームシーンを作成し、移動
void TitleLayer::createAndMoveGameScene()
{
    auto scene = GameLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}
