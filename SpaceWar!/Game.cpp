#include "Game.h"
#include"Ship.h"
#include"Audio.h"
//�Q�[���̏�Ԃ��Ǘ�����O���[�o���ϐ�
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
	//�J�E���^���C���N�������g����
	_count++;

	//���X�^�[�g���Ԃ��Z�b�g���ꂽ��f�N�������g����
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
		//Ship�̃X�R�A���ő�ɂȂ�����1P, 2P�̑I����������
		if (gShips[i].GetScore() >= MAX_SHIP_SCORE)
		{
			//1P, 2P�̑I����������
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
		//�X�R�A�̏�����
		gShips[i].SetScore(0);

		//�Q�[���̃��Z�b�g
		gGame.GameReset();

	}//for (int i = 0; i < MAX_INDEX_SHIP; i++)
}//void Game::GameStart()



void Game::GameRestart()
{
	//�ҋ@���ԂłȂ����̏���
	if (_restartWaitTime <= 0)
	{
		//�ҋ@���Ԃ��Z�b�g����
		_restartWaitTime = MAX_RESTART_WAIT_TIME;

		//�f����ʂłȂ���΁A���_������
		if (gGame._demoSceen == false)
		{
			//WEDGE�������������̏���
			if ((gShips[SHIP_INDEX_WEDGE]._isDead == false) &&
				(gShips[SHIP_INDEX_NEEDLE]._isDead == true))
			{
				gShips[SHIP_INDEX_WEDGE].SetScore(gShips[SHIP_INDEX_WEDGE].GetScore() + 1);
			}
			//NEEDLE�������������̏���
			else if ((gShips[SHIP_INDEX_WEDGE]._isDead == true) &&
				(gShips[SHIP_INDEX_NEEDLE]._isDead == false))
			{
				gShips[SHIP_INDEX_NEEDLE].SetScore(gShips[SHIP_INDEX_NEEDLE].GetScore() + 1);
			}
			//�����Ƃ����ꂽ�ꍇ
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
	//�J�E���^�̏�����
	_count = 0;
	for (int i = 0; i < ShipType::MAX_INDEX_SHIP; i++)
	{
		//Ship��������
		gShips[i].Reset();

		

		//Ship�̃X�R�A���ő�ɂȂ�����f���֑J�ڂ���
		if (gShips[i].GetScore() >= MAX_SHIP_SCORE)
		{
			gGame._demoSceen = true;
			//���ʉ����I�t�ɂ���
			for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)
			{
				AudioStop(i);
			}//for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)



		}//if (gShips[i].GetScore() >= MAX_SHIP_SCORE)

	}//for (int i = 0; i < ShipType::MAX_SHIP; i++)
	//�����̃G�t�F�N�g������
	gExplosions.clear();
}//void Game::GameReset()





