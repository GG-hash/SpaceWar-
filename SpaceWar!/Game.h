#pragma once
#include"Actor.h"
//�Q�[�����X�^�[�g�܂ł̑ҋ@���Ԃ̍ő�l
//3�b
#define MAX_RESTART_WAIT_TIME (60 * 3)

class Game : public Actor
{
private:
	//���X�^�[�g���܂ł̑ҋ@����
	int _restartWaitTime;
	//�Q�[���̌o�ߎ��Ԃɂ��J�E���^
	unsigned int _count;
public:
	//�R���X�g���N�^
	Game();

	//�X�V����֐�
	void Update() override;

	//�`�悷��֐�)
	void Draw() override;

	//�Q�[���J�n���ɌĂ΂��֐�
	void GameStart();

	//�Q�[���̃��X�^�[�g�̏���
	void GameRestart();

	//�Q�[���̃��Z�b�g
	void GameReset();

	//���X�^�[�g���̑ҋ@���Ԃ��擾����֐�
	int GetrestartWaitTime()const { return _restartWaitTime; }

	//�J�E���^�̃Q�b�^�ƃZ�b�^
	unsigned int GetCount() const { return _count; }
	void SetCount(unsigned int count) { _count = count; }

	//�f����ʂ��𔻒肷��t���O
	bool _demoSceen;

	//1P�ŗV�Ԏ���true�ƂȂ�t���O
	bool _1P;
	//2P�ŗV�Ԏ���true�ƂȂ�t���O
	bool _2P;

};//class Game : public Actor

//�Q�[�����̂��Ǘ�����z��
extern Game gGame;