#pragma once
#include<cstdio>
#include<alc.h>
#include<al.h>
#include<ctime>

//ライブラリのインポート
#pragma comment(lib,"OpenAL32.lib")

//基準となる音の大きさ
#define AUDIO_DEFAULT_GAIN 0.1f
//基準となる周波数
#define AUDIO_DEFAULT_FREQ 440.0f

//音のモード定義
enum SoundMode
{
	AUDIO_WAVEFORM_PULSE_12_5, //矩形波
	AUDIO_WAVEFORM_PULSE_25,
	AUDIO_WAVEFORM_PULSE_50,
	AUDIO_WAVEFORM_PULSE_75,
	AUDIO_WAVEFORM_TRIANGLE,   //三角波
	AUDIO_WAVEFORM_NOISE_LONG, //長周期ノイズ
	AUDIO_WAVEFORM_NOISE_SHORT,//短周期ノイズ
	AUDIO_WAVEFORM_MAX
};//enum SoundMode

//チャンネル
enum SoundChannel
{
	AUDIO_CHANNEL_PULSE0,
	AUDIO_CHANNEL_PULSE1,
	AUDIO_CHANNEL_TRIANGLE,
	AUDIO_CHANNEL_NOISE,
	AUDIO_CHANNEL_MAX
};//enum SoundChannel



//ノイズ周波数除数 値が大きいほど低い音となる  4068は地響きのような音
//4,8,16,32,64,96,128,160,(202),254,380,508,762,1016,2034,4068
//AudioFreq(1789772.5f/202);//平均的な周波数


typedef struct
{
	//ソースのID 外部からアクセスできるようにする
	ALuint sourceID;

	//波の形の保存
	int _waveform;

	//音の長さ
	unsigned int _length;
	//音の成り始める最初の時刻
	unsigned int _startTime;
	//減衰の長さ
	float _decay;
	//最初のゲイン
	float _startGain;
	//ゲインの大きさ
	float _gain;
	//スイープの長さ
	float _sweep;

	//スウィープの範囲
	float _sweepTarget;
	//最初の周波数
	float _freqStart;
	//現在の周波数
	float _freq;//ファミコンのCPUクロック数は 1789772.5f
   //最後の周波数
	float _freqEnd;
}CHANNEL;




//初期設定をする関数
int  AudioInit();
//音を再生させる関数
void AudioPlay(int channel);
//音を停止させる関数
void AudioStop(int channel);
//波形のセッター 再生中に波形を変更しない
void AudioWaveForm(int channel, int waveform);
//音の長さのセッター ミリ秒をセットする
void AudioLength(int channel, unsigned int milis);
//アップデート用の関数
void AudioUpdate();
//音の減衰の長さをセットする関数 0 < decay < 1
void AudioDecay(int channel, float decay);
//スイープの長さをセットする関数 sweep<1 音が次第に低くなる 0.95　sweep>1 音が次第に高くなる
void AudioSweep(int channel, float sweep, float freqEnd = 0.0f);
//スウィープの範囲を決める
//void AudioPitchTartget(float pitchTarget);
//周波数を設定する関数
void AudioFreq(int channel, float freq);
//テスト用の関数
//void SoundTest(unsigned char key);
//インデックスを周波数に変換する関数 0<=index<=15  return 1789772.5f / divisortable[index];
float AudioIndexToFreq(int index);
//音量をセットする関数
void AudioGain(int channel, float gain);


