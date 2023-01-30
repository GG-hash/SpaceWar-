#pragma once
#include"Actor.h"
//ゲームリスタートまでの待機時間の最大値
//3秒
#define MAX_RESTART_WAIT_TIME (60 * 3)

class Game : public Actor
{
private:
	//リスタート時までの待機時間
	int _restartWaitTime;
	//ゲームの経過時間によるカウンタ
	unsigned int _count;
public:
	//コンストラクタ
	Game();

	//更新する関数
	void Update() override;

	//描画する関数)
	void Draw() override;

	//ゲーム開始時に呼ばれる関数
	void GameStart();

	//ゲームのリスタートの処理
	void GameRestart();

	//ゲームのリセット
	void GameReset();

	//リスタート時の待機時間を取得する関数
	int GetrestartWaitTime()const { return _restartWaitTime; }

	//カウンタのゲッタとセッタ
	unsigned int GetCount() const { return _count; }
	void SetCount(unsigned int count) { _count = count; }

	//デモ画面かを判定するフラグ
	bool _demoSceen;

	//1Pで遊ぶ時にtrueとなるフラグ
	bool _1P;
	//2Pで遊ぶ時にtrueとなるフラグ
	bool _2P;

};//class Game : public Actor

//ゲーム自体を管理する配列
extern Game gGame;