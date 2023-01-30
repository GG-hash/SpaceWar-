#pragma once
#include "Actor.h"
#include<vector>
#include"glm/glm.hpp"
using namespace std;
using namespace glm;

//爆発に出現する点の数の最大値
#define MAX_GENERATE_EXPLOSION_POINTS 20

class Explosion :public Actor
{
private:
	//弾と爆発の位置
	vec2 _pos;
	//弾と爆発の速さ
	vec2 _speed;
	//弾と爆発の消滅するまでのカウント
	float _removeCount;
public:
	//コンストラクタ
	Explosion();

	//更新する関数
	void Update() override;
	static void AllUpdate();
	//描画する関数
	void Draw() override;
	static void AllDraw();
	//爆発を発生させる関数
	static void GenerateExplosion(vec2 const& pos, int count, float power);
	//位置のゲッタとセッタ
	vec2& GetPosition() { return _pos; }
	void SetPosition(vec2& pos) { _pos = pos; }

	//速さのゲッタとセッタ
	vec2& GetSpeed() { return _speed; }
	void SetSpeed(vec2& speed) { _speed = speed; }

	//カウントのゲッタとセッタ
	float GetRemoveCount()const { return _removeCount; }
	void SetRemoveCount(float count) { _removeCount = count; }
};//class Explosion :public Actor


//Explosionのデータを管理する配列
extern vector<Explosion> gExplosions;