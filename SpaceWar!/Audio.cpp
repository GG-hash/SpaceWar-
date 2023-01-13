#include "Audio.h"
#include <corecrt_math.h>

////�o�b�t�@�[��ID
ALuint buffersID[AUDIO_WAVEFORM_MAX];
//CHANNEL�^�̃C���X�^���X
CHANNEL _channels[AUDIO_CHANNEL_MAX];

int AudioInit()
{
	//�f�o�C�X���J��
	ALCdevice* device = alcOpenDevice(NULL); //*devicename

	//NULL�`�F�b�N
	if (device == NULL)
	{
		return -1;
	}

	//�R���e�L�X�g�̍쐬 ��Ԃ̕ێ�
	ALCcontext* context = alcCreateContext(device, NULL);

	//NULL�`�F�b�N
	if (context == NULL)
	{
		return -1;
	}

	//���݂̃R���e�L�X�g��ݒ�
	alcMakeContextCurrent(context);



	//�g�`�f�[�^���Ǘ�����o�b�t�@�[�̍쐬
	alGenBuffers(AUDIO_WAVEFORM_MAX, buffersID);//glGenBuffers(�o�b�t�@�[���쐬���鐔, �o�b�t�@�[�̃|�C���^);


	{
		//�o�b�t�@�[�Ƀf�[�^���Z�b�g����
		//��`�g�̃f�[�^
		unsigned char pulseData[4][8] =
		{
			{ 0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },//12.5�@�p���X�g
			{ 0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00 },//25.0�@�p���X�g
			{ 0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00 },//50.0�@�p���X�g
			{ 0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00 } //75.0�@�p���X�g

		};

		for (int i = AUDIO_WAVEFORM_PULSE_12_5; i <= AUDIO_WAVEFORM_PULSE_75; i++)
		{
			ALsizei size = sizeof pulseData[0];

			alBufferData(buffersID[i], AL_FORMAT_MONO8,//��̃f�[�^��8bit
				pulseData[i], size,
				size  //ALsizei freq  440Hz(���K�̊)�ɐݒ�
			);
		}
	}

	//�O�p�g�̐���
	{
		//32�V�[�P���X�̒ǉ�
		unsigned char triangleData[32] =
		{
			0xff,0xee,0xdd,0xcc,0xbb,0xaa,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,0x00,
			0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff
		};

		alBufferData(buffersID[AUDIO_WAVEFORM_TRIANGLE], AL_FORMAT_MONO8,//��̃f�[�^��8bit
			triangleData, sizeof triangleData,
			sizeof triangleData  //ALsizei freq  440Hz(���K�̊)�ɐݒ�
		);
	}

	//�������m�C�Y�̔g�`�f�[�^�̐���
	{
		//������
		const int length = 32767;
		unsigned char longnoiseData[length] = {};
		//�^�������̐���//////////////////////
		//�V�t�g���W�X�^�𐶐�����
		int shiftReg = 1 << 14;

		//�f�[�^�̏�������
		for (int i = 0; i < length; i++)
		{
			//���ʂ����߂�
			int result = (shiftReg ^ (shiftReg >> 1)) & 1;//�V�t�g����1���ڂ��󂯎��
			//���W�X�^���E�V�t�g����
			shiftReg >>= 1;
			shiftReg |= result << 14;//OR
			longnoiseData[i] = 0xff * result;
		}
		////////////////////////////////////

		alBufferData(buffersID[AUDIO_WAVEFORM_NOISE_LONG], AL_FORMAT_MONO8,//��̃f�[�^��8bit
			longnoiseData, sizeof longnoiseData,
			1//sizeof longnoiseData  //ALsizei freq  440Hz(���K�̊)�ɐݒ�
		);
	}

	//�Z�����m�C�Y�̔g�`�f�[�^�̐���
	{
		//�Z����
		const int length = 93;
		unsigned char shortnoiseData[length] = {};

		//�^�������̐���//////////////////////
		//�V�t�g���W�X�^�𐶐�����
		int shiftReg = 1 << 14;
		//�f�[�^�̏�������
		for (int i = 0; i < length; i++)
		{
			//���ʂ����߂�
			int result = (shiftReg ^ (shiftReg >> 6)) & 1;//�V�t�g����1���ڂ��󂯎��
			//���W�X�^���E�V�t�g����
			shiftReg >>= 1;
			shiftReg |= result << 14;//OR
			shortnoiseData[i] = 0xff * result;
		}
		/////////////////////////////////////
		alBufferData(buffersID[AUDIO_WAVEFORM_NOISE_SHORT], AL_FORMAT_MONO8,//��̃f�[�^��8bit
			shortnoiseData, sizeof shortnoiseData,
			1  //ALsizei freq  440Hz(���K�̊)�ɐݒ�
		);
	}

	//�\�[�X��ID
	//ALuint sourceID;

	//�`�����l���̏�����
	for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)
	{
		//�\�[�X�̍쐬
		alGenSources(1, &_channels[i].sourceID);

		//�Q�C���̏�����
		AudioGain(i, AUDIO_DEFAULT_GAIN);

		//���[�v������
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
	//�\�[�X�Ƀo�b�t�@�[���Z�b�g���� int�^
	alSourcei(_channels[channel].sourceID, AL_BUFFER, buffersID[_channels[channel]._waveform]);
}//void AudioWaveForm(int channel, int waveform)


void AudioLength(int channel, unsigned int milis)
{
	_channels[channel]._length = milis;
}
//AudioLength(unsigned int milis)

void AudioUpdate()
{
	//�S�Ẵ`�����l�����A�b�v�f�[�g
	for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)
	{
		//���̒���(_length)��0���傫���A�Đ����Ԃ��I�[�o�[�����特���~�߂�
		if ((_channels[i]._length > 0) && (clock() - _channels[i]._startTime >= _channels[i]._length))
		{
			AudioStop(i);
		}

		//���̌��������邩���`�F�b�N
		if ((_channels[i]._decay != 0) && (_channels[i]._decay < 1))
		{
			//����������
			_channels[i]._gain *= _channels[i]._decay;


			//���ʂ𒲐߂��� float�^
			alSourcef(_channels[i].sourceID, AL_GAIN, _channels[i]._gain);
		}

		//_sweep���Z�b�g����Ă��邩�`�F�b�N
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

			//�s�b�`��ݒ肷�� float�^
			alSourcef(_channels[i].sourceID, AL_PITCH, _channels[i]._freq);
		}//if (_channels[i]._sweep != 0)
	}//for (int i = 0; i < AUDIO_CHANNEL_MAX; i++)


	//�G���[�΍�
	ALenum error = alGetError();
	//�G���[���������ꍇ
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

//void AudioPitchTartget(float pitchTarget)
//{
//	_pitchTarget = pitchTarget;
//}//AudioPitchTartget(float pitchTarget)

void AudioFreq(int channel, float freq)
{
	//_channels[channel]._freq
	//printf("AudioFreq : %f\n", freq);
	_channels[channel]._freqStart = _channels[channel]._freq = freq;
	//�s�b�`��ݒ肷�� float�^
	//�Đ����ł��s�b�`��ύX�ł���悤�ɂ���
	alSourcef(_channels[channel].sourceID, AL_PITCH, _channels[channel]._freq);//_freq?
}
//AudioFreq(int channel, float freq)

//void SoundTest(unsigned char key)
//{
//	if ((key >= '0') && (key <= '9'))
//	{
//		AudioStop();
//		//�����𐔒l�֕ϊ�
//		int tmpKey = key - '0';
//		AudioWaveForm(AUDIO_WAVEFORM_PULSE_50);
//		AudioFreq(440 * powf(2, 1 + (tmpKey / 12.0f)));
//		AudioPlay();
//	}
//}
//SoundTest(unsigned char key)


float AudioIndexToFreq(int index)
{
	//�����̕\
	int divisorTable[] =
	{
		4,8,16,32,64,96,128,160,202,254,380,508,762,1016,2034,4068
	};

	/*float divisorTable[16] =
	{
		4.0f,8.0f,16.0f,32.0f,64.0f,96.0f,128.0f,160.0f,202.0f,254.0f,380.0f,508.0f,762.0f,1016.0f,2034.0f,4068.0f
	};*/

	//printf("Freq      : %f\n ", 1789772.5f / divisorTable[index]);
	//1789772.5f �̓t�@�~�R����CPU�N���b�N���g��
	return 1789772.5f / divisorTable[index];
}//AudioIndexToFreq(int index)

void AudioGain(int channel, float gain)
{
	_channels[channel]._gain = _channels[channel]._startGain = gain;

	//���ʂ𒲐߂��� float�^
	alSourcef(_channels[channel].sourceID, AL_GAIN, _channels[channel]._gain);


}//AudioGain(int channel, float gain)

void AudioPlay(int channel)
{
	_channels[channel]._gain = _channels[channel]._startGain;
	//���ʂ𒲐߂��� float�^
	alSourcef(_channels[channel].sourceID, AL_GAIN, _channels[channel]._gain);

	_channels[channel]._freq = _channels[channel]._freqStart;
	//printf("StartFreq : %f\n", _freq);
	//_pitch = _freqStart/DEFAULT_FREQ;
	//�s�b�`��ݒ肷�� float�^
	alSourcef(_channels[channel].sourceID, AL_PITCH, _channels[channel]._freq);


	alSourcePlay(_channels[channel].sourceID);

	//�X�^�[�g�̎�����ۑ�����
	_channels[channel]._startTime = clock();
}//AudioPlay(int channel)

void AudioStop(int channel)
{
	alSourceStop(_channels[channel].sourceID);
}
//AudioStop(int channel)



