#include "Ship.h"
#include"Color.h"
#include"Audio.h"

//Ship�̃C���X�^���X
class Ship gShips[MAX_INDEX_SHIP];

Ship::Ship() :_index(0)
, _isDead(false)
, _transPoints()
, _defaultRotate(0.0f)
, _lastAttack(false)
, _pos(vec2(0, 0))
, _rotate(0.0f)
, _size(vec2(0, 0))
, _speed(vec2(0, 0))
, _transMatrix()
, _score(0)
{
}//Ship::Ship()


int Ship::ReadDataBMP(const char* fileName, int index, vec2 defaultPos, float defaultRotate)
{
    //�C���f�b�N�X��������
    _index = index;
    //�f�t�H���g�̈ʒu�Ɖ�]���Z�b�g
    _defaultPos = defaultPos;
    _defaultRotate = defaultRotate;

    //�t�@�C���ǂݍ��݂̏���
    FILE* fp;

    fopen_s(&fp, fileName, "rb");

    //�G���[�`�F�b�N
    if (fp == nullptr)
    {
        printf("No %s", fileName);
        return -1;
    }

    printf("open %s \n", fileName);

    //�t�@�C����ǂݍ���
    BITMAPFILEHEADER fHeader;
    BITMAPINFOHEADER iHeader;

    fread(&fHeader, sizeof BITMAPFILEHEADER, 1, fp);
    fread(&iHeader, sizeof BITMAPINFOHEADER, 1, fp);

    _size = vec2(iHeader.biWidth, iHeader.biHeight);
    printf("Ship size : %f, %f\n", _size.x, _size.y);

    //�p�f�B���O�̒�`
    //bmp�͕���4�o�C�g�P�ʂɂȂ�悤�ɒ�������
    //�]�����s�N�Z�������߂�
    int padding = (4 - iHeader.biWidth * 3 % 4) % 4;

    for (int i = 0; i < iHeader.biHeight; i++)
    {
        for (int j = 0; j < iHeader.biWidth; j++)
        {
            unsigned char buffer[3];
            fread(buffer, sizeof buffer, 1, fp);

            //�΂łȂ���Γ_��ǉ�
            if (buffer[0] > 0)
            {
                _points.push_back(vec2(j, i));
                _transPoints.push_back(vec2(j, i));
            }
        }// for (int j = 0; j < iHeader.biWidth; j++)
        //���݂̃|�C���^����padding���ǂݐi�߂�
        fseek(fp, padding, SEEK_CUR);

    }//for (int i = 0; i < iHeader.biHeight; i++)

    fclose(fp);
    //�Q�[�������Z�b�g����
    Reset();
    return 0;
}//Ship::ReadDataBMP(const char* fileName)



int Ship::Initialize(const char* fileName, int index, vec2 defaultPos, float defaultRotate)
{
    //�C���f�b�N�X��������
    _index = index;
    //�f�t�H���g�̈ʒu�Ɖ�]���Z�b�g
    _defaultPos = defaultPos;
    _defaultRotate = defaultRotate;


    //�t�@�C���ǂݍ��݂̏���
    FILE* fp;

    fopen_s(&fp, fileName, "rb");

    //�G���[�`�F�b�N
    if (fp == nullptr)
    {
        printf("No %s", fileName);
        return -1;
    }

    printf("open %s \n", fileName);

    //�t�@�C����ǂݍ���
    BITMAPFILEHEADER fHeader;
    BITMAPINFOHEADER iHeader;

    fread(&fHeader, sizeof BITMAPFILEHEADER, 1, fp);
    fread(&iHeader, sizeof BITMAPINFOHEADER, 1, fp);

    _size = vec2(iHeader.biWidth, iHeader.biHeight);
    printf("Ship size : %f, %f\n", _size.x, _size.y);

    //�p�f�B���O�̒�`
    //bmp�͕���4�o�C�g�P�ʂɂȂ�悤�ɒ�������
    //�]�����s�N�Z�������߂�
    int padding = (4 - iHeader.biWidth * 3 % 4) % 4;

    for (int i = 0; i < iHeader.biHeight; i++)
    {
        for (int j = 0; j < iHeader.biWidth; j++)
        {
            unsigned char buffer[3];
            fread(buffer, sizeof buffer, 1, fp);

            //�΂łȂ���Γ_��ǉ�
            if (buffer[0] > 0)
            {
                _points.push_back(vec2(j, i));
                _transPoints.push_back(vec2(j, i));
            }
        }// for (int j = 0; j < iHeader.biWidth; j++)
        //���݂̃|�C���^����padding���ǂݐi�߂�
        fseek(fp, padding, SEEK_CUR);

    }//for (int i = 0; i < iHeader.biHeight; i++)

    fclose(fp);
    //Ship�Ɏg�p����AI�̏�����
    _ai.Initialize(_index);
    //�Q�[�������Z�b�g����
    Reset();
    return 0;
}//int Ship::Initialize(const char* fileName, int index, vec2 defaultPos, float defaultRotate)


int Ship::AllInitialize()
{
    //1P
    gShips[SHIP_INDEX_WEDGE].Initialize("image/wedge.bmp", SHIP_INDEX_WEDGE,
        vec2(-SCREEN_WIDTH / 4.0f, -SCREEN_HEIGHT / 4.0f), 0);
    gShips[SHIP_INDEX_WEDGE]._bulletCount = 0;


    //2P
    gShips[SHIP_INDEX_NEEDLE].Initialize("image/needle.bmp", SHIP_INDEX_NEEDLE,
        vec2(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f), (float)M_PI);
    gShips[SHIP_INDEX_NEEDLE]._bulletCount = 0;




    return 0;
}
//Ship::AllInitialize(const char* fileName)

void Ship::Input(bool turnLeft, bool turnRight, bool acceleration, bool attack)
{
    //����Ă�������͏������󂯕t���Ȃ�
    if (_isDead)
    {
        return;
    }

    //���ɐ��񂷂�Ƃ��̏���
    if (turnLeft)
    {
        _rotate += (float)M_PI / 60.0f;
    }
    //�E�ɐ��񂷂�Ƃ��̏���
    if (turnRight)
    {
        _rotate -= (float)M_PI / 60.0f;
    }
    //�������鎞�̏���
    if (_lastKeys[SHIP_KEY_ACCEL] = acceleration)
    {
        //_accel = acceleration;
        //Ship�̉�]������
        _speed += vec2(-sin(_rotate), cos(_rotate)) * SHIP_ACCELERATION;
    }
    //�U�����鎞�̏���
    if (attack)
    {
        Attack();
    }

}
//Ship::Input(bool turnLeft, bool turnRight, bool thurust

void Ship::Attack()
{
    //����Ă�����U�����Ȃ�
    if (_isDead == true)
    {
        return;
    }

    //�f����ʂłȂ���΁A����炷
    if (gGame._demoSceen == false)
    {
        //�U�����𐶐�
        int channel = AUDIO_CHANNEL_PULSE0 + _index;
        AudioStop(channel);
        AudioWaveForm(channel, AUDIO_WAVEFORM_PULSE_12_5);
        AudioFreq(channel, 440 * 4);
        AudioGain(channel, AUDIO_DEFAULT_GAIN);
        AudioSweep(channel, 0.9f);
        AudioDecay(channel, 0.9f);
        AudioPlay(channel);
    }//if (gGame._demoSceen == false)

    //�o���b�g�̃C���X�^���X�𐶐�
    Bullet bullet;
    //�e�̈ʒu���Z�b�g
    bullet.SetPosition(_pos);
    //�e�̑������Z�b�g
    //�v���C���[�Ɠ��������Ɍ���
    vec2 bulletSpeed = bullet.GetSpeed() + vec2(-sin(_rotate), cos(_rotate)) * BULLET_SPEED;
    bullet.SetSpeed(bulletSpeed);
    //�e�����ł���܂ł̃J�E���g���Z�b�g����
    //10�b�Ԓe���\�������
    bullet.SetRemoveCount(MAX_BULLET_COUNT);
    //_bullets�փf�[�^��擪�ɒǉ�����
    _bullets.insert(_bullets.begin(), bullet);



}// Ship::Attack()

void Ship::Turn()
{
    //�ϊ��s��̐���
    _transMatrix = translate(mat4(1), vec3(_pos, 0))
        * rotate(mat4(1), _rotate, vec3(0, 0, 1))
        * translate(mat4(1), vec3(-_size.x / 2.0f, -_size.y / 2.0f, 0.0f)); //��]�̒��S���摜�̒��S�ɐݒ肷��

    for (auto iter = _points.begin(), iterTrans = _transPoints.begin();
        iter != _points.end(); iter++, iterTrans++)
    {
        (*iterTrans) = _transMatrix * vec4((*iter).x, (*iter).y, 0, 1);
        //(*iterTrans) = (vec2)vec;
    }
}//void Ship::Turn()




void Ship::Update()
{
    //����Ă�����X�V���Ȃ�
    if (_isDead == true)
    {
        return;
    }

    //���ɐ��񂷂�Ƃ��̏���
    if (_keys[SHIP_KEY_LEFT])
    {
        _rotate += (float)M_PI / 60.0f;
    }
    //�E�ɐ��񂷂�Ƃ��̏���
    if (_keys[SHIP_KEY_RIGHT])
    {
        _rotate -= (float)M_PI / 60.0f;
    }

    //��]�͈̔͂� -M_PI < _rotate < M_PI �Ƃ���
    _rotate = FixRadianAngle(_rotate);

    //�������鎞�̏���
    if (_keys[SHIP_KEY_ACCEL])
    {
        //_accel = acceleration;
        //Ship�̉�]������
        _speed += vec2(-sin(_rotate), cos(_rotate)) * SHIP_ACCELERATION;
    }
    //�U�����鎞�̏���
    if ((_keys[SHIP_KEY_ATTACK] == true) &&
        (_lastKeys[SHIP_KEY_ATTACK] == false))
    {
        Attack();
    }//if ((_keys[SHIP_KEY_ATTACK] == true) && (_lastKeys[SHIP_KEY_ATTACK] == false))

    //�f����ʂłȂ��A�O�̃t���[���ŉ����{�^���������Ă��Ȃ�������
    //�G���W������炷
    if (gGame._demoSceen == false)
    {
        int channel = AUDIO_CHANNEL_TRIANGLE + _index;

        if ((_keys[SHIP_KEY_ACCEL] == true) && (_lastKeys[SHIP_KEY_ACCEL] == false))
        {
            //�G���W������ݒ�
            AudioWaveForm(channel, AUDIO_WAVEFORM_NOISE_LONG);
            AudioFreq(channel, AudioIndexToFreq(13));
            AudioGain(channel, AUDIO_DEFAULT_GAIN * 0.5f);
            AudioDecay(channel, 0);
            AudioSweep(channel, 0);
            AudioPlay(channel);
        }//if ((_accel == true) && (_lastAccel == false))
        else if ((_keys[SHIP_KEY_ACCEL] == false) && (_lastKeys[SHIP_KEY_ACCEL] == true))
        {
            AudioStop(channel);
        }//else if ((_accel == false) && (_lastAccel == true))
    }//if (gGame._demoSceen == false)


    //���W�̃A�b�v�f�[�g
    _pos += _speed;

    //���z�ɂ�����(���z�̊T�v�� Sun.h���Q�Ƃ��Ă�������)
    //���z�̈ʒu�͌��_�ɂ���
    if (length(_pos) != 0.0f)
    {
        _speed += -normalize(_pos) / length(_pos) * 0.15f;
    }//if (length(_pos) != 0.0f) 

    //���񂷂鏈��
    Turn();

    //Ship����ʊO�ɏo���Ƃ��̏���
    if ((_pos.x >= SCREEN_WIDTH / 2.0f))
    {
        _pos.x -= SCREEN_WIDTH;
    }
    if ((_pos.x < -SCREEN_WIDTH / 2.0f))
    {
        _pos.x += SCREEN_WIDTH;
    }
    if ((_pos.y >= SCREEN_HEIGHT / 2.0f))
    {
        _pos.y -= SCREEN_HEIGHT;
    }
    if ((_pos.y < -SCREEN_HEIGHT / 2.0f))
    {
        _pos.y += SCREEN_HEIGHT;
    }

    //�G�@�̃f�[�^���擾����
    //XOR�ő���̋@�̂̃C���f�b�N�X���擾����
    Ship& Enemy = gShips[_index ^ 1];
    //�e�̍X�V
    for (auto bullet = _bullets.begin(); bullet != _bullets.end();)
    {
        (*bullet).Update();

        //�e����莞�Ԃ�������폜����悤�ɂ���
        if ((*bullet).GetRemoveCount() <= 0)
        {
            bullet = _bullets.erase(bullet);
        }
        else
        {
            //�G�Ƃ̓����蔻��̃t���O
            bool hit = false;

            if (Enemy._isDead == false)
            {



                for (auto enemy = Enemy._transPoints.begin();
                    enemy != Enemy._transPoints.end(); enemy++)
                {
                    //���g�̒e�̈ʒu�ƓG�̈ʒu���e�̑�����菬������Γ��������Ɣ��肷��
                    //�_�ł̓����蔻��
                    if (distance((*bullet).GetPosition(), *enemy) < length(_speed))
                    {
                        hit = true;
                        break;
                    }//if (distance((*bullet).GetPosition(), *enemy) < _speed.length())
                }//for (auto enemy = Enemy._transPoints.begin(); enemy != Enemy._transPoints.end(); enemy++)
            }//if (Enemy._isDead == false)
            //�����������̏���
            if (hit == true)
            {
                //�e���폜����
                bullet = _bullets.erase(bullet);
                //�G�@�𔚔j������
                Enemy.GenerateExplosion();
                //�Q�[�������X�^�[�g
                gGame.GameRestart();
                return;
            }//if (hit == true)
            else
            {
                bullet++;
            }

        }//else
    }//for (auto bullet = _bullets.begin(); bullet != _bullets.end();)

    //���z�ɂԂ��������̏���
    for (auto transPoints = _transPoints.begin();
        transPoints != _transPoints.end(); transPoints++)
    {
        //�i�񂾐悪���z�ł���A�f����ʂŖ��������特��炷
        if (length(*transPoints) < length(_speed) &&
            (gGame._demoSceen == false))
        {
            //���z�̉��𐶐�
            int channel = AUDIO_CHANNEL_TRIANGLE + _index;
            AudioStop(channel);
            AudioWaveForm(channel, AUDIO_WAVEFORM_NOISE_SHORT);
            AudioFreq(channel, AudioIndexToFreq(15));
            AudioGain(channel, AUDIO_DEFAULT_GAIN);
            AudioSweep(channel, 1.1f);
            AudioDecay(channel, 0.975f);
            AudioPlay(channel);

            _isDead = true;
            gGame.GameRestart();
        }//if (length(_pos) < length(_speed))

    }//for (auto transPoints = _transPoints.begin();transPoints != _transPoints.end();transPoints++)

    //�������������肷��
    memcpy(_lastKeys, _keys, sizeof(_keys));


}//Ship::Update()

void Ship::AllUpdate()
{
    //�����f����ʂȂ�1P��AI�����삷��
    if (gGame._demoSceen == true)
    {
        //AI�̋@�̂̍X�V
        gShips[SHIP_INDEX_WEDGE]._ai.Update();
    }//if (gGame._demoSceen == true)
    //1P�̓���
    else
    {
        bool* keys = gShips[SHIP_INDEX_WEDGE]._keys;
        keys[SHIP_KEY_LEFT] = gKeys['a'];
        keys[SHIP_KEY_RIGHT] = gKeys['d'];
        keys[SHIP_KEY_ACCEL] = gKeys['w'];
        keys[SHIP_KEY_ATTACK] = gDownKeys['f'];
    }

    //2P�̓���
    if(gGame._2P == true)
    {
        bool* keys = gShips[SHIP_INDEX_NEEDLE]._keys;
        keys[SHIP_KEY_LEFT] = gKeys['k'];
        keys[SHIP_KEY_RIGHT] = gKeys[';'];
        keys[SHIP_KEY_ACCEL] = gKeys['o'];
        keys[SHIP_KEY_ATTACK] = gDownKeys['j'];
    }//if(gGame._2P == true)
    else if (gGame._2P == false)
    {
        //AI�̋@�̂̍X�V
        gShips[SHIP_INDEX_NEEDLE]._ai.Update();
    }//else if (gGame._2P == false)
    
    //Ship�̃A�b�v�f�[�g
    for (int i = 0; i < MAX_INDEX_SHIP; i++)
    {
        gShips[i].Update();
    }

    //Ship���m�̓����蔻��
    //���݂���Ship�������c���Ă����珈������

    //���݂������j���ꂽ�����肷��t���O
    bool check = false;
    if ((gShips[SHIP_INDEX_WEDGE]._isDead == false) && (gShips[SHIP_INDEX_NEEDLE]._isDead == false))
    {
        //���������Ă���Ship�𓖂��鑤�Ƃ���
        float range = std::max(length(gShips[SHIP_INDEX_WEDGE]._speed), length(gShips[SHIP_INDEX_NEEDLE]._speed));

        for (auto wedgeTransPoints = gShips[SHIP_INDEX_WEDGE]._transPoints.begin();
            wedgeTransPoints != gShips[SHIP_INDEX_WEDGE]._transPoints.end(); wedgeTransPoints++)
        {
            for (auto needleTransPoints = gShips[SHIP_INDEX_NEEDLE]._transPoints.begin();
                needleTransPoints != gShips[SHIP_INDEX_NEEDLE]._transPoints.end(); needleTransPoints++)
            {
                //���݂��̏ꏊ���A�ǂ��炩�̑����̑傫�����傫�����
                //���������Ƃ݂Ȃ�
                if ((distance(*wedgeTransPoints, *needleTransPoints) < range) && (check == false))
                {
                    for (int i = 0; i < MAX_INDEX_SHIP; i++)
                    {
                        gShips[i].GenerateExplosion();
                    }
                    //�Q�[�������X�^�[�g����
                    gGame.GameRestart();
                    //���j���������d��for���𔲂��邽�߂�
                    //check��true�ɂ���
                    check = true;
                }//if (distance(*wedgeTransPoints, *needleTransPoints) < range)
            }//for (auto needleTransPoints = gShips[SHIP_NEEDLE]._transPoints.begin();needleTransPoints != gShips[SHIP_NEEDLE]._transPoints.end(); needleTransPoints++)

            //Ship���m�̔��j���I�������for���𔲂���
            if (check == true)
            {
                break;
            }//if (check == true)

        }//for (auto wedgeTransPoints = gShips[SHIP_WEDGE]._transPoints.begin();wedgeTransPoints != gShips[SHIP_WEDGE]._transPoints.end(); wedgeTransPoints++)
    }//if((gShips[SHIP_WEDGE]._isDead == false) && (gShips[SHIP_NEEDLE]._isDead == false))

}//Ship::AllUpdate()

void Ship::Draw()
{
    //����Ă�����`�悵�Ȃ�
    if (_isDead == true)
    {
        return;
    }

    //�e�̃A�j���[�V����
    if (_bullets.size() > 0)
    {
        vec2& position = _bullets.data()->GetPosition();

        glVertexPointer(2, GL_FLOAT, sizeof(Bullet), &position);
        glDrawArrays(GL_POINTS, 0, _bullets.size());
        //printf("Ship    x : %f, y : %f\n", _pos.x, _pos.y);
        //printf("Bullet     x : %f, y : %f\n", position.x, position.y);
    }


    //stride�i���ԁj��0
    glVertexPointer(2, GL_FLOAT, 0, _transPoints.data());
    glDrawArrays(GL_POINTS, 0, _transPoints.size());


    //�������̃W�F�b�g�����˂���A�j���[�V����
    if (_keys[SHIP_KEY_ACCEL] == true)
    {
        //���_�̃f�[�^
        vec2 v[] = { {(int)_size.x / 2, 0},
                     {(int)_size.x / 2,-16.0f * rand() / RAND_MAX }
        };


        for (int i = 0; i < 2; i++)
        {
            v[i] = (vec2)(_transMatrix * vec4(v[i].x, v[i].y, 0, 1));
        }

        glVertexPointer(2, GL_FLOAT, 0, v);

        glDrawArrays(GL_LINES, 0, 2);
    }//if (_accel)

    //���_�f�[�^�ɂ��`������Z�b�g����
    glDisableClientState(GL_VERTEX_ARRAY);
    //���_�z���L���ɂ���
    glEnableClientState(GL_VERTEX_ARRAY);

}//Ship::Draw()

void Ship::AllDraw()
{
    for (int i = 0; i < MAX_INDEX_SHIP; i++)
    {
        gShips[i].Draw();
    }
}//Ship::AllDraw()

void Ship::GenerateExplosion()
{
    //����Ă�����U�����Ȃ�
    if (_isDead == true)
    {
        return;
    }

    //�f����ʂłȂ���΁A����炷
    if (gGame._demoSceen == false)
    {
        //���j���𐶐�
        int channel = AUDIO_CHANNEL_TRIANGLE + _index;
        AudioStop(channel);
        AudioWaveForm(channel, AUDIO_WAVEFORM_NOISE_LONG);
        AudioGain(channel, AUDIO_DEFAULT_GAIN);
        AudioFreq(channel, AudioIndexToFreq(13));
        AudioSweep(channel, 0.975f);
        AudioDecay(channel, 0.975f);
        AudioPlay(channel);
    }// if (gGame._demoSceen == false)

    _isDead = true;
    //�����̃G�t�F�N�g
    Explosion::GenerateExplosion(_pos, 1000, 1);
    //�ʒu�Ɖ�],�����̏�����
    _pos = _defaultPos;
    _rotate = _defaultRotate;
    _speed = vec2(0, 0);

    gGame.GameRestart();
}//void Ship::GenerateExplosion()

void Ship::Reset()
{
    //�ʒu�Ɖ�],�����̏�����
    _pos = _defaultPos;
    _rotate = _defaultRotate;
    _speed = vec2(0, 0);
    //���Ƃ̌����֐��񂳂���
    Turn();
    //�e����������
    _bullets.clear();
    //�������Ă��Ȃ����Ƃɂ���
    memset(_keys, 0, sizeof(_keys));
    memset(_lastKeys, 0, sizeof(_lastKeys));

    _isDead = false;
}//void Ship::Reset()







