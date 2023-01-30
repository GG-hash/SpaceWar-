#pragma once
#include<cstdio>
#include<vector>
#include<Windows.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"glut.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"Actor.h"
#include"GameHeader.h"
#include"Bullet.h"
#include"AI.h"
using namespace std;
using namespace glm;

//Shipの最大の加速度
#define SHIP_ACCELERATION 0.001f
//Shipが得ることのできる最大のスコア
#define MAX_SHIP_SCORE 3


//Shipの数を定義する
//名前はbmpファイルに対応させる
enum ShipType
{
	SHIP_INDEX_WEDGE,
	SHIP_INDEX_NEEDLE,
	MAX_INDEX_SHIP //最大のShipの数
};

//押されているキーのタイプ
enum ShipKey
{
	SHIP_KEY_LEFT,
	SHIP_KEY_RIGHT,
	SHIP_KEY_ACCEL,
	SHIP_KEY_ATTACK,
	MAX_SHIP_KEY
};

class Ship : public Actor
{
private:
	//Shipを描画する点の配列
	vector<vec2> _points;
	//変換後の頂点の座標
	vector<vec2> _transPoints;
	//Shipのサイズ
	vec2 _size;
	//Shipの座標
	vec2 _pos;
	//Shipのデフォルト座標
	vec2 _defaultPos;
	//Shipの回転の角度
	float _rotate;
	//Shipのデフォルトの回転の角度
	float _defaultRotate;
	//Shipのスピード
	vec2 _speed;
	////加速ボタンが押されているかを判定する
	//bool _accel;
	////加速したかを判定する
	//bool _lastAccel;

	//弾の配列
	vector<Bullet> _bullets;
	//弾のカウント
	int _bulletCount;
	//弾の発射状態のフラグ
	bool _lastAttack;
	//Shipのインデックス
	int _index;
	//変換行列
	mat4 _transMatrix;
	//AIのインスタンス
	AI _ai;
	//スコア
	int _score;
public:
	//コンストラクタ
	Ship();
	//ファイルを読み込む
	int ReadDataBMP(const char* fileName, int index, vec2 defaultPos, float defaultRotate);
	//プレイヤーの初期化関数
	int Initialize(const char* fileName, int index, vec2 defaultPos, float defaultRotate);
	static int AllInitialize();
	//Shipの動きを入力する関数
	void Input(bool turnLeft, bool turnRight, bool acceleration, bool attack);
	//攻撃の処理
	void Attack();
	//機体を旋回させる関数
	void Turn();
	//更新する関数
	void Update() override;
	static void AllUpdate();
	//描画関数
	void Draw() override;
	static void AllDraw();
	//位置のゲッタとセッタ
	vec2& GetPosition() { return _pos; }
	void SetPosition(vec2& pos) { _pos = pos; }

	//速さのゲッタとセッタ
	vec2& GetSpeed() { return _speed; }
	void SetSpeed(vec2& speed) { _speed = speed; }

	//角度のゲッタとセッタ
	float GetRotate() const { return _rotate; }
	void SetRotate(float rotate) { _rotate = rotate; }

	//スコアのゲッタとセッタ
	int GetScore() const { return _score; }
	void SetScore(int score) { _score = score; }

	//やられたかどうか判定するフラグ
	bool _isDead;
	//爆発の処理
	void GenerateExplosion();
	//Shipをリセットする関数
	void Reset();
	//キーの状態を格納する配列
	bool _keys[MAX_SHIP_KEY];
	//キーがすでに押されているかを判定する
	bool _lastKeys[MAX_SHIP_KEY];
};//class Ship

//外部から変数を読み込む
extern Ship gShips[MAX_INDEX_SHIP];

