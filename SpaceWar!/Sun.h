#pragma once
#include "Actor.h"

//太陽の処理に関するクラス
//太陽は画面の中心にあり、引力を持っている
//当たってしまうとミスとなる
//太陽の位置は原点(画面の中心である)
class Sun :public Actor
{
private:

public:
	//更新する関数
	void Update() override;
	//描画関数
	void Draw() override;
};//class Sun :public Actor

//グローバルなインスタンス
extern Sun gSun;
