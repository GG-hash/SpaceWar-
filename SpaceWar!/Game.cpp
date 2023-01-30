#include "Game.h"
#include"Ship.h"
#include"Audio.h"
//ゲームの状態を管理するグローバル変数
Game gGame = {};

Game::Game() :_demoSceen(true)
			 , _count(0)
			 ,_restartWaitTime(0)
			 ,_1P(false)
			 ,_2P(false)
{
}//Game::Game()

void Game::Update()
{
	//カウンタをインクリメントする
	_count++;

	//リスタート時間がセットされたらデクリメントする
	if (_restartWaitTime > 0)
	{
		_restartWaitTime--;
		if (_restartWaitTime <= 0)
		{
			GameReset();

		}//if (_restartWaitTime <= 0)
	}//if (_restartWaitTime > 0)


	for (int i = 0; i < ShipType::MAX_INDEX_SHIP; i++)
	{
		//Shipのスコアが最大になったら1P, 2Pの選択を初期化
		if (gShips[i].GetScore() >= MAX_SHIP_SCORE)
		{
			//1P, 2Pの選択を初期化
			_1P = false;
			_2P = false;
		}//if (gShips[i].GetScore() >= MAX_SHIP_SCORE)

	}//for (int i = 0; i < ShipType::MAX_SHIP; i++)

	


}//void Game::Update()


void Game::Draw()
{
}
//void Game::Draw()

void Game::GameStart()
{
	gGame._demoSceen = false;

	for (int i = 0; i < MAX_INDEX_SHIP; i++)
	{
		//スコアの初期化
		gShips[i].SetScore(0);

		//ゲームのリセット
		gGame.GameReset();

	}//for (int i = 0; i < MAX_INDEX_SHIP; i++)
}//void Game::GameStart()



void Game::GameRestart()
{
	//待機時間でない時の処理
	if (_restartWaitTime <= 0)
	{
		//待機時間をセットする
		_restartWaitTime = MAX_RESTART_WAIT_TIME;

		//デモ画面でなければ、得点を入れる
		if (gGame._demoSceen == false)
		{
			//WEDGE側が勝った時の処理
			if ((gShips[SHIP_INDEX_WEDGE]._isDead == false) &&
				(gShips[SHIP_INDEX_NEEDLE]._isDead == true))
			{
				gShips[SHIP_INDEX_WEDGE].SetScore(gShips[SHIP_INDEX_WEDGE].GetScore() + 1);
			}
			//NEEDLE側が勝った時の処理
			else if ((gShips[SHIP_INDEX_WEDGE]._isDead == true) &&
				(gShips[SHIP_INDEX_NEEDLE]._isDead == false))
			{
				gShips[SHIP_INDEX_NEEDLE].SetScore(gShips[SHIP_INDEX_NEEDLE].GetScore() + 1);
			}
			//両方ともやられた場合
			else if ((gShips[SHIP_INDEX_WEDGE]._isDead == true) &&
				(gShips[SHIP_INDEX_NEEDLE]._isDead == true))
			{
				for (int i = 0; i < MAX_INDEX_SHIP; i++)
				{
					gShips[i].SetScore(gShips[i].GetScore() + 1);
				}//for (int i = 0; i < MAX_INDEX_SHIP; i++)
			}
		}//if (gGame._demoSceen == false)

	}//if (_restartWaitTime <= 0)

}//void Game::RestartGame()

void Game::GameReset()
{
	//カウンタの初期化
	_count = 0;
	for (int i = 0; i < ShipType::MAX_INDEX_SHIP; i++)
	{
		//Shipを初期化
		gShips[i].Reset();

		

		//Shipのスコアが最大になったらデモへ遷移する
		if (gShips[i].GetScore() >= MAX_SHIP_SCORE)
		{
			gGame._demoSceen = true;
			//効果音をオフにする
			for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)
			{
				AudioStop(i);
			}//for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)



		}//if (gShips[i].GetScore() >= MAX_SHIP_SCORE)

	}//for (int i = 0; i < ShipType::MAX_SHIP; i++)
	//爆発のエフェクトを消す
	gExplosions.clear();
}//void Game::GameReset()





