#pragma once
#include "Actor.h"

//惑星の処理に関するクラス
//惑星は画面の中心にあり、引力を持っている
//当たってしまうとミスとなる
//惑星の位置は原点(画面の中心である)
class Planet :public Actor
{
private:

public:
	//更新する関数
	void Update() override;
	//描画関数
	void Draw() override;
};//class Planet :public Actor

//グローバルなインスタンス
extern Planet gPlanet;
