#pragma once
#include<cstdio>
#include<alc.h>
#include<al.h>
#include<ctime>

//���C�u�����̃C���|�[�g
#pragma comment(lib,"OpenAL32.lib")

//��ƂȂ鉹�̑傫��
#define AUDIO_DEFAULT_GAIN 0.1f
//��ƂȂ���g��
#define AUDIO_DEFAULT_FREQ 440.0f

//���̃��[�h��`
enum SoundMode
{
	AUDIO_WAVEFORM_PULSE_12_5, //��`�g
	AUDIO_WAVEFORM_PULSE_25,
	AUDIO_WAVEFORM_PULSE_50,
	AUDIO_WAVEFORM_PULSE_75,
	AUDIO_WAVEFORM_TRIANGLE,   //�O�p�g
	AUDIO_WAVEFORM_NOISE_LONG, //�������m�C�Y
	AUDIO_WAVEFORM_NOISE_SHORT,//�Z�����m�C�Y
	AUDIO_WAVEFORM_MAX
};//enum SoundMode

//�`�����l��
enum SoundChannel
{
	AUDIO_CHANNEL_PULSE0,
	AUDIO_CHANNEL_PULSE1,
	AUDIO_CHANNEL_TRIANGLE,
	AUDIO_CHANNEL_NOISE,
	AUDIO_CHANNEL_MAX
};//enum SoundChannel



//�m�C�Y���g������ �l���傫���قǒႢ���ƂȂ�  4068�͒n�����̂悤�ȉ�
//4,8,16,32,64,96,128,160,(202),254,380,508,762,1016,2034,4068
//AudioFreq(1789772.5f/202);//���ϓI�Ȏ��g��


typedef struct
{
	//�\�[�X��ID �O������A�N�Z�X�ł���悤�ɂ���
	ALuint sourceID;

	//�g�̌`�̕ۑ�
	int _waveform;

	//���̒���
	unsigned int _length;
	//���̐���n�߂�ŏ��̎���
	unsigned int _startTime;
	//�����̒���
	float _decay;
	//�ŏ��̃Q�C��
	float _startGain;
	//�Q�C���̑傫��
	float _gain;
	//�X�C�[�v�̒���
	float _sweep;

	//�X�E�B�[�v�͈̔�
	float _sweepTarget;
	//�ŏ��̎��g��
	float _freqStart;
	//���݂̎��g��
	float _freq;//�t�@�~�R����CPU�N���b�N���� 1789772.5f
   //�Ō�̎��g��
	float _freqEnd;
}CHANNEL;




//�����ݒ������֐�
int  AudioInit();
//�����Đ�������֐�
void AudioPlay(int channel);
//�����~������֐�
void AudioStop(int channel);
//�g�`�̃Z�b�^�[ �Đ����ɔg�`��ύX���Ȃ�
void AudioWaveForm(int channel, int waveform);
//���̒����̃Z�b�^�[ �~���b���Z�b�g����
void AudioLength(int channel, unsigned int milis);
//�A�b�v�f�[�g�p�̊֐�
void AudioUpdate();
//���̌����̒������Z�b�g����֐� 0 < decay < 1
void AudioDecay(int channel, float decay);
//�X�C�[�v�̒������Z�b�g����֐� sweep<1 ��������ɒႭ�Ȃ� 0.95�@sweep>1 ��������ɍ����Ȃ�
void AudioSweep(int channel, float sweep, float freqEnd = 0.0f);
//�X�E�B�[�v�͈̔͂����߂�
//void AudioPitchTartget(float pitchTarget);
//���g����ݒ肷��֐�
void AudioFreq(int channel, float freq);
//�e�X�g�p�̊֐�
//void SoundTest(unsigned char key);
//�C���f�b�N�X�����g���ɕϊ�����֐� 0<=index<=15  return 1789772.5f / divisortable[index];
float AudioIndexToFreq(int index);
//���ʂ��Z�b�g����֐�
void AudioGain(int channel, float gain);


