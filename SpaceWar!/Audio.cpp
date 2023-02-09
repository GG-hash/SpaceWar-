#include "Audio.h"
#include <corecrt_math.h>

////バッファーのID
ALuint buffersID[AUDIO_WAVEFORM_MAX];
//CHANNEL型のインスタンス
CHANNEL _channels[AUDIO_CHANNEL_MAX];

int AudioInit()
{
	//デバイスを開く
	ALCdevice* device = alcOpenDevice(NULL); //*devicename

	//NULLチェック
	if (device == NULL)
	{
		return -1;
	}

	//コンテキストの作成 状態の保持
	ALCcontext* context = alcCreateContext(device, NULL);

	//NULLチェック
	if (context == NULL)
	{
		return -1;
	}

	//現在のコンテキストを設定
	alcMakeContextCurrent(context);

	//波形データを管理するバッファーの作成
	alGenBuffers(AUDIO_WAVEFORM_MAX, buffersID);//glGenBuffers(バッファーを作成する数, バッファーのポインタ);


	{
		//バッファーにデータをセットする
		//矩形波のデータ
		unsigned char pulseData[4][8] =
		{
			{ 0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },//12.5　パルス波
			{ 0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00 },//25.0　パルス波
			{ 0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00 },//50.0　パルス波
			{ 0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00 } //75.0　パルス波

		};

		for (int i = AUDIO_WAVEFORM_PULSE_12_5; i <= AUDIO_WAVEFORM_PULSE_75; i++)
		{
			ALsizei size = sizeof pulseData[0];

			alBufferData(buffersID[i], AL_FORMAT_MONO8,//一つのデータは8bit
				pulseData[i], size,
				size  //ALsizei freq  440Hz(音階の基準)に設定
			);
		}
	}

	//三角波の生成
	{
		//32シーケンスの追加
		unsigned char triangleData[32] =
		{
			0xff,0xee,0xdd,0xcc,0xbb,0xaa,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,0x00,
			0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff
		};

		alBufferData(buffersID[AUDIO_WAVEFORM_TRIANGLE], AL_FORMAT_MONO8,//一つのデータは8bit
			triangleData, sizeof triangleData,
			sizeof triangleData  //ALsizei freq  440Hz(音階の基準)に設定
		);
	}

	//長周期ノイズの波形データの生成
	{
		//長周期
		const int length = 32767;
		unsigned char longnoiseData[length] = {};
		//疑似乱数の生成//////////////////////
		//シフトレジスタを生成する
		int shiftReg = 1 << 14;

		//データの書き込み
		for (int i = 0; i < length; i++)
		{
			//結果を求める
			int result = (shiftReg ^ (shiftReg >> 1)) & 1;//シフトして1桁目を受け取る
			//レジスタを右シフトする
			shiftReg >>= 1;
			shiftReg |= result << 14;//OR
			longnoiseData[i] = 0xff * result;
		}
		////////////////////////////////////

		alBufferData(buffersID[AUDIO_WAVEFORM_NOISE_LONG], AL_FORMAT_MONO8,//一つのデータは8bit
			longnoiseData, sizeof longnoiseData,
			1//sizeof longnoiseData  //ALsizei freq  440Hz(音階の基準)に設定
		);
	}

	//短周期ノイズの波形データの生成
	{
		//短周期
		const int length = 93;
		unsigned char shortnoiseData[length] = {};

		//疑似乱数の生成//////////////////////
		//シフトレジスタを生成する
		int shiftReg = 1 << 14;
		//データの書き込み
		for (int i = 0; i < length; i++)
		{
			//結果を求める
			int result = (shiftReg ^ (shiftReg >> 6)) & 1;//シフトして1桁目を受け取る
			//レジスタを右シフトする
			shiftReg >>= 1;
			shiftReg |= result << 14;//OR
			shortnoiseData[i] = 0xff * result;
		}
		/////////////////////////////////////
		alBufferData(buffersID[AUDIO_WAVEFORM_NOISE_SHORT], AL_FORMAT_MONO8,//一つのデータは8bit
			shortnoiseData, sizeof shortnoiseData,
			1  //ALsizei freq  440Hz(音階の基準)に設定
		);
	}

	//ソースのID
	//ALuint sourceID;

	//チャンネルの初期化
	for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)
	{
		//ソースの作成
		alGenSources(1, &_channels[i].sourceID);

		//ゲインの初期化
		AudioGain(i, AUDIO_DEFAULT_GAIN);

		//ループさせる
		alSourcei(_channels[i].sourceID, AL_LOOPING, AL_TRUE);
	}

	AudioWaveForm(AUDIO_CHANNEL_PULSE0, AUDIO_WAVEFORM_PULSE_12_5);
	AudioWaveForm(AUDIO_CHANNEL_PULSE1, AUDIO_WAVEFORM_PULSE_12_5);
	AudioWaveForm(AUDIO_CHANNEL_TRIANGLE, AUDIO_WAVEFORM_TRIANGLE);
	AudioWaveForm(AUDIO_CHANNEL_NOISE, AUDIO_WAVEFORM_NOISE_LONG);
	//AudioWaveForm(AUDIO_CHANNEL_NOISE,AUDIO_WAVEFORM_NOISE_LONG);
	AudioFreq(AUDIO_CHANNEL_PULSE0, AUDIO_DEFAULT_FREQ);
	AudioFreq(AUDIO_CHANNEL_PULSE1, AUDIO_DEFAULT_FREQ);
	AudioFreq(AUDIO_CHANNEL_TRIANGLE, AUDIO_DEFAULT_FREQ);
	AudioFreq(AUDIO_CHANNEL_NOISE, AudioIndexToFreq(8));

	return 0;

}//AudioInit()

void AudioWaveForm(int channel, int waveform)
{
	_channels[channel]._waveform = waveform;
	//ソースにバッファーをセットする int型
	alSourcei(_channels[channel].sourceID, AL_BUFFER, buffersID[_channels[channel]._waveform]);
}//void AudioWaveForm(int channel, int waveform)


void AudioLength(int channel, unsigned int milis)
{
	_channels[channel]._length = milis;
}
//AudioLength(unsigned int milis)

void AudioUpdate()
{
	//全てのチャンネルをアップデート
	for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)
	{
		//音の長さ(_length)が0より大きく、再生時間をオーバーしたら音を止める
		if ((_channels[i]._length > 0) && (clock() - _channels[i]._startTime >= _channels[i]._length))
		{
			AudioStop(i);
		}

		//音の減衰があるかをチェック
		if ((_channels[i]._decay != 0) && (_channels[i]._decay < 1))
		{
			//減衰させる
			_channels[i]._gain *= _channels[i]._decay;


			//音量を調節する float型
			alSourcef(_channels[i].sourceID, AL_GAIN, _channels[i]._gain);
		}

		//_sweepがセットされているかチェック
		if (_channels[i]._sweep != 0)
		{
			_channels[i]._freq *= _channels[i]._sweep;

			if (_channels[i]._freqEnd != 0)
			{
				if (((_channels[i]._sweep > 1) && (_channels[i]._freq >= _channels[i]._freqEnd))
					|| ((_channels[i]._sweep < 1) && (_channels[i]._freq <= _channels[i]._freqEnd)))
				{
					AudioStop(i);
				}

			}

			//ピッチを設定する float型
			alSourcef(_channels[i].sourceID, AL_PITCH, _channels[i]._freq);
		}//if (_channels[i]._sweep != 0)
	}//for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)


	//エラー対策
	ALenum error = alGetError();
	//エラーがあった場合
	if (error != AL_NO_ERROR)
	{
		printf("%s\n", alGetString(error));
	}

}//AudioUpdate()


void AudioDecay(int channel, float decay)
{
	_channels[channel]._decay = decay;

}
//AudioDecay(int channel,float decay)


void AudioSweep(int channel, float sweep, float freqEnd)
{
	_channels[channel]._sweep = sweep;
	_channels[channel]._freqEnd = freqEnd;
}
//AudioSweep(int channel, float sweep, float freqEnd)



void AudioFreq(int channel, float freq)
{
	_channels[channel]._freqStart = _channels[channel]._freq = freq;
	//ピッチを設定する float型
	//再生中でもピッチを変更できるようにする
	alSourcef(_channels[channel].sourceID, AL_PITCH, _channels[channel]._freq);
}
//AudioFreq(int channel, float freq)



float AudioIndexToFreq(int index)
{
	//除数の表
	/*int divisorTable[] =
	{
		4,8,16,32,64,96,128,160,202,254,380,508,762,1016,2034,4068
	};*/

	float divisorTable[16] =
	{
		4.0f,8.0f,16.0f,32.0f,64.0f,96.0f,128.0f,160.0f,202.0f,254.0f,380.0f,508.0f,762.0f,1016.0f,2034.0f,4068.0f
	};

	
	//1789772.5f はファミコンのCPUクロック周波数
	return 1789772.5f / divisorTable[index];
}//AudioIndexToFreq(int index)

void AudioGain(int channel, float gain)
{
	_channels[channel]._gain = _channels[channel]._startGain = gain;

	//音量を調節する float型
	alSourcef(_channels[channel].sourceID, AL_GAIN, _channels[channel]._gain);


}//AudioGain(int channel, float gain)

void AudioPlay(int channel)
{
	_channels[channel]._gain = _channels[channel]._startGain;
	//音量を調節する float型
	alSourcef(_channels[channel].sourceID, AL_GAIN, _channels[channel]._gain);

	_channels[channel]._freq = _channels[channel]._freqStart;
	//printf("StartFreq : %f\n", _freq);
	//_pitch = _freqStart/DEFAULT_FREQ;
	//ピッチを設定する float型
	alSourcef(_channels[channel].sourceID, AL_PITCH, _channels[channel]._freq);


	alSourcePlay(_channels[channel].sourceID);

	//スタートの時刻を保存する
	_channels[channel]._startTime = clock();
}//AudioPlay(int channel)

void AudioStop(int channel)
{
	alSourceStop(_channels[channel].sourceID);
}
//AudioStop(int channel)



