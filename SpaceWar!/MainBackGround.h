#pragma once
#include "Actor.h"
#include"glm/glm.hpp"
#include<vector>
using namespace std;
using namespace glm;

//背景の星の最大値
#define MAX_STAR     128
//星が煌めく周期
#define TINCLE_CYCLE 2

class MainBackGround :public Actor
{
private:
	//星の位置を格納する配列
	vec2 _points[MAX_STAR];
public:
	//コンストラクタ
	MainBackGround();
	//初期化する関数
	int Initialize();
	//更新する関数
	void Update() override;
	//描画する関数
	void Draw() override;

};//class MainBackGround :public Actor

//グローバルなインスタンス
extern MainBackGround gMainBG;
