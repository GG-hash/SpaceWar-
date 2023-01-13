#include "Ship.h"
#include"Color.h"
#include"Audio.h"

//Shipのインスタンス
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
    //インデックスを代入する
    _index = index;
    //デフォルトの位置と回転をセット
    _defaultPos = defaultPos;
    _defaultRotate = defaultRotate;

    //ファイル読み込みの処理
    FILE* fp;

    fopen_s(&fp, fileName, "rb");

    //エラーチェック
    if (fp == nullptr)
    {
        printf("No %s", fileName);
        return -1;
    }

    printf("open %s \n", fileName);

    //ファイルを読み込む
    BITMAPFILEHEADER fHeader;
    BITMAPINFOHEADER iHeader;

    fread(&fHeader, sizeof BITMAPFILEHEADER, 1, fp);
    fread(&iHeader, sizeof BITMAPINFOHEADER, 1, fp);

    _size = vec2(iHeader.biWidth, iHeader.biHeight);
    printf("Ship size : %f, %f\n", _size.x, _size.y);

    //パディングの定義
    //bmpは幅が4バイト単位になるように調整する
    //余ったピクセルを求める
    int padding = (4 - iHeader.biWidth * 3 % 4) % 4;

    for (int i = 0; i < iHeader.biHeight; i++)
    {
        for (int j = 0; j < iHeader.biWidth; j++)
        {
            unsigned char buffer[3];
            fread(buffer, sizeof buffer, 1, fp);

            //緑でなければ点を追加
            if (buffer[0] > 0)
            {
                _points.push_back(vec2(j, i));
                _transPoints.push_back(vec2(j, i));
            }
        }// for (int j = 0; j < iHeader.biWidth; j++)
        //現在のポインタからpadding分読み進める
        fseek(fp, padding, SEEK_CUR);

    }//for (int i = 0; i < iHeader.biHeight; i++)

    fclose(fp);
    //ゲームをリセットする
    Reset();
    return 0;
}//Ship::ReadDataBMP(const char* fileName)



int Ship::Initialize(const char* fileName, int index, vec2 defaultPos, float defaultRotate)
{
    //インデックスを代入する
    _index = index;
    //デフォルトの位置と回転をセット
    _defaultPos = defaultPos;
    _defaultRotate = defaultRotate;


    //ファイル読み込みの処理
    FILE* fp;

    fopen_s(&fp, fileName, "rb");

    //エラーチェック
    if (fp == nullptr)
    {
        printf("No %s", fileName);
        return -1;
    }

    printf("open %s \n", fileName);

    //ファイルを読み込む
    BITMAPFILEHEADER fHeader;
    BITMAPINFOHEADER iHeader;

    fread(&fHeader, sizeof BITMAPFILEHEADER, 1, fp);
    fread(&iHeader, sizeof BITMAPINFOHEADER, 1, fp);

    _size = vec2(iHeader.biWidth, iHeader.biHeight);
    printf("Ship size : %f, %f\n", _size.x, _size.y);

    //パディングの定義
    //bmpは幅が4バイト単位になるように調整する
    //余ったピクセルを求める
    int padding = (4 - iHeader.biWidth * 3 % 4) % 4;

    for (int i = 0; i < iHeader.biHeight; i++)
    {
        for (int j = 0; j < iHeader.biWidth; j++)
        {
            unsigned char buffer[3];
            fread(buffer, sizeof buffer, 1, fp);

            //緑でなければ点を追加
            if (buffer[0] > 0)
            {
                _points.push_back(vec2(j, i));
                _transPoints.push_back(vec2(j, i));
            }
        }// for (int j = 0; j < iHeader.biWidth; j++)
        //現在のポインタからpadding分読み進める
        fseek(fp, padding, SEEK_CUR);

    }//for (int i = 0; i < iHeader.biHeight; i++)

    fclose(fp);
    //Shipに使用するAIの初期化
    _ai.Initialize(_index);
    //ゲームをリセットする
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
    //やられていたら入力処理を受け付けない
    if (_isDead)
    {
        return;
    }

    //左に旋回するときの処理
    if (turnLeft)
    {
        _rotate += (float)M_PI / 60.0f;
    }
    //右に旋回するときの処理
    if (turnRight)
    {
        _rotate -= (float)M_PI / 60.0f;
    }
    //加速する時の処理
    if (_lastKeys[SHIP_KEY_ACCEL] = acceleration)
    {
        //_accel = acceleration;
        //Shipの回転させる
        _speed += vec2(-sin(_rotate), cos(_rotate)) * SHIP_ACCELERATION;
    }
    //攻撃する時の処理
    if (attack)
    {
        Attack();
    }

}
//Ship::Input(bool turnLeft, bool turnRight, bool thurust

void Ship::Attack()
{
    //やられていたら攻撃しない
    if (_isDead == true)
    {
        return;
    }

    //デモ画面でなければ、音を鳴らす
    if (gGame._demoSceen == false)
    {
        //攻撃音を生成
        int channel = AUDIO_CHANNEL_PULSE0 + _index;
        AudioStop(channel);
        AudioWaveForm(channel, AUDIO_WAVEFORM_PULSE_12_5);
        AudioFreq(channel, 440 * 4);
        AudioGain(channel, AUDIO_DEFAULT_GAIN);
        AudioSweep(channel, 0.9f);
        AudioDecay(channel, 0.9f);
        AudioPlay(channel);
    }//if (gGame._demoSceen == false)

    //バレットのインスタンスを生成
    Bullet bullet;
    //弾の位置をセット
    bullet.SetPosition(_pos);
    //弾の速さをセット
    //プレイヤーと同じ向きに撃つ
    vec2 bulletSpeed = bullet.GetSpeed() + vec2(-sin(_rotate), cos(_rotate)) * BULLET_SPEED;
    bullet.SetSpeed(bulletSpeed);
    //弾が消滅するまでのカウントをセットする
    //10秒間弾が表示される
    bullet.SetRemoveCount(MAX_BULLET_COUNT);
    //_bulletsへデータを先頭に追加する
    _bullets.insert(_bullets.begin(), bullet);



}// Ship::Attack()

void Ship::Turn()
{
    //変換行列の生成
    _transMatrix = translate(mat4(1), vec3(_pos, 0))
        * rotate(mat4(1), _rotate, vec3(0, 0, 1))
        * translate(mat4(1), vec3(-_size.x / 2.0f, -_size.y / 2.0f, 0.0f)); //回転の中心を画像の中心に設定する

    for (auto iter = _points.begin(), iterTrans = _transPoints.begin();
        iter != _points.end(); iter++, iterTrans++)
    {
        (*iterTrans) = _transMatrix * vec4((*iter).x, (*iter).y, 0, 1);
        //(*iterTrans) = (vec2)vec;
    }
}//void Ship::Turn()




void Ship::Update()
{
    //やられていたら更新しない
    if (_isDead == true)
    {
        return;
    }

    //左に旋回するときの処理
    if (_keys[SHIP_KEY_LEFT])
    {
        _rotate += (float)M_PI / 60.0f;
    }
    //右に旋回するときの処理
    if (_keys[SHIP_KEY_RIGHT])
    {
        _rotate -= (float)M_PI / 60.0f;
    }

    //回転の範囲を -M_PI < _rotate < M_PI とする
    _rotate = FixRadianAngle(_rotate);

    //加速する時の処理
    if (_keys[SHIP_KEY_ACCEL])
    {
        //_accel = acceleration;
        //Shipの回転させる
        _speed += vec2(-sin(_rotate), cos(_rotate)) * SHIP_ACCELERATION;
    }
    //攻撃する時の処理
    if ((_keys[SHIP_KEY_ATTACK] == true) &&
        (_lastKeys[SHIP_KEY_ATTACK] == false))
    {
        Attack();
    }//if ((_keys[SHIP_KEY_ATTACK] == true) && (_lastKeys[SHIP_KEY_ATTACK] == false))

    //デモ画面でなく、前のフレームで加速ボタンを押していなかったら
    //エンジン音を鳴らす
    if (gGame._demoSceen == false)
    {
        int channel = AUDIO_CHANNEL_TRIANGLE + _index;

        if ((_keys[SHIP_KEY_ACCEL] == true) && (_lastKeys[SHIP_KEY_ACCEL] == false))
        {
            //エンジン音を設定
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


    //座標のアップデート
    _pos += _speed;

    //太陽による引力(太陽の概要は Sun.hを参照してください)
    //太陽の位置は原点にある
    if (length(_pos) != 0.0f)
    {
        _speed += -normalize(_pos) / length(_pos) * 0.15f;
    }//if (length(_pos) != 0.0f) 

    //旋回する処理
    Turn();

    //Shipが画面外に出たときの処理
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

    //敵機のデータを取得する
    //XORで相手の機体のインデックスを取得する
    Ship& Enemy = gShips[_index ^ 1];
    //弾の更新
    for (auto bullet = _bullets.begin(); bullet != _bullets.end();)
    {
        (*bullet).Update();

        //弾が一定時間たったら削除するようにする
        if ((*bullet).GetRemoveCount() <= 0)
        {
            bullet = _bullets.erase(bullet);
        }
        else
        {
            //敵との当たり判定のフラグ
            bool hit = false;

            if (Enemy._isDead == false)
            {



                for (auto enemy = Enemy._transPoints.begin();
                    enemy != Enemy._transPoints.end(); enemy++)
                {
                    //自身の弾の位置と敵の位置が弾の速さより小さければ当たったと判定する
                    //点での当たり判定
                    if (distance((*bullet).GetPosition(), *enemy) < length(_speed))
                    {
                        hit = true;
                        break;
                    }//if (distance((*bullet).GetPosition(), *enemy) < _speed.length())
                }//for (auto enemy = Enemy._transPoints.begin(); enemy != Enemy._transPoints.end(); enemy++)
            }//if (Enemy._isDead == false)
            //当たった時の処理
            if (hit == true)
            {
                //弾を削除する
                bullet = _bullets.erase(bullet);
                //敵機を爆破させる
                Enemy.GenerateExplosion();
                //ゲームをリスタート
                gGame.GameRestart();
                return;
            }//if (hit == true)
            else
            {
                bullet++;
            }

        }//else
    }//for (auto bullet = _bullets.begin(); bullet != _bullets.end();)

    //太陽にぶつかった時の処理
    for (auto transPoints = _transPoints.begin();
        transPoints != _transPoints.end(); transPoints++)
    {
        //進んだ先が太陽であり、デモ画面で無かったら音を鳴らす
        if (length(*transPoints) < length(_speed) &&
            (gGame._demoSceen == false))
        {
            //太陽の音を生成
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

    //加速したか判定する
    memcpy(_lastKeys, _keys, sizeof(_keys));


}//Ship::Update()

void Ship::AllUpdate()
{
    //もしデモ画面なら1PをAIが操作する
    if (gGame._demoSceen == true)
    {
        //AIの機体の更新
        gShips[SHIP_INDEX_WEDGE]._ai.Update();
    }//if (gGame._demoSceen == true)
    //1Pの入力
    else
    {
        bool* keys = gShips[SHIP_INDEX_WEDGE]._keys;
        keys[SHIP_KEY_LEFT] = gKeys['a'];
        keys[SHIP_KEY_RIGHT] = gKeys['d'];
        keys[SHIP_KEY_ACCEL] = gKeys['w'];
        keys[SHIP_KEY_ATTACK] = gDownKeys['f'];
    }

    //2Pの入力
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
        //AIの機体の更新
        gShips[SHIP_INDEX_NEEDLE]._ai.Update();
    }//else if (gGame._2P == false)
    
    //Shipのアップデート
    for (int i = 0; i < MAX_INDEX_SHIP; i++)
    {
        gShips[i].Update();
    }

    //Ship同士の当たり判定
    //お互いのShipが生き残っていたら処理する

    //お互いが爆破されたか判定するフラグ
    bool check = false;
    if ((gShips[SHIP_INDEX_WEDGE]._isDead == false) && (gShips[SHIP_INDEX_NEEDLE]._isDead == false))
    {
        //速く動いているShipを当たる側とする
        float range = std::max(length(gShips[SHIP_INDEX_WEDGE]._speed), length(gShips[SHIP_INDEX_NEEDLE]._speed));

        for (auto wedgeTransPoints = gShips[SHIP_INDEX_WEDGE]._transPoints.begin();
            wedgeTransPoints != gShips[SHIP_INDEX_WEDGE]._transPoints.end(); wedgeTransPoints++)
        {
            for (auto needleTransPoints = gShips[SHIP_INDEX_NEEDLE]._transPoints.begin();
                needleTransPoints != gShips[SHIP_INDEX_NEEDLE]._transPoints.end(); needleTransPoints++)
            {
                //お互いの場所より、どちらかの速さの大きさが大きければ
                //当たったとみなす
                if ((distance(*wedgeTransPoints, *needleTransPoints) < range) && (check == false))
                {
                    for (int i = 0; i < MAX_INDEX_SHIP; i++)
                    {
                        gShips[i].GenerateExplosion();
                    }
                    //ゲームをリスタートする
                    gGame.GameRestart();
                    //爆破させたら二重のfor文を抜けるために
                    //checkをtrueにする
                    check = true;
                }//if (distance(*wedgeTransPoints, *needleTransPoints) < range)
            }//for (auto needleTransPoints = gShips[SHIP_NEEDLE]._transPoints.begin();needleTransPoints != gShips[SHIP_NEEDLE]._transPoints.end(); needleTransPoints++)

            //Ship同士の爆破が終わったらfor文を抜ける
            if (check == true)
            {
                break;
            }//if (check == true)

        }//for (auto wedgeTransPoints = gShips[SHIP_WEDGE]._transPoints.begin();wedgeTransPoints != gShips[SHIP_WEDGE]._transPoints.end(); wedgeTransPoints++)
    }//if((gShips[SHIP_WEDGE]._isDead == false) && (gShips[SHIP_NEEDLE]._isDead == false))

}//Ship::AllUpdate()

void Ship::Draw()
{
    //やられていたら描画しない
    if (_isDead == true)
    {
        return;
    }

    //弾のアニメーション
    if (_bullets.size() > 0)
    {
        vec2& position = _bullets.data()->GetPosition();

        glVertexPointer(2, GL_FLOAT, sizeof(Bullet), &position);
        glDrawArrays(GL_POINTS, 0, _bullets.size());
        //printf("Ship    x : %f, y : %f\n", _pos.x, _pos.y);
        //printf("Bullet     x : %f, y : %f\n", position.x, position.y);
    }


    //stride（隙間）は0
    glVertexPointer(2, GL_FLOAT, 0, _transPoints.data());
    glDrawArrays(GL_POINTS, 0, _transPoints.size());


    //加速時のジェットが噴射するアニメーション
    if (_keys[SHIP_KEY_ACCEL] == true)
    {
        //頂点のデータ
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

    //頂点データによる描画をリセットする
    glDisableClientState(GL_VERTEX_ARRAY);
    //頂点配列を有効にする
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
    //やられていたら攻撃しない
    if (_isDead == true)
    {
        return;
    }

    //デモ画面でなければ、音を鳴らす
    if (gGame._demoSceen == false)
    {
        //爆破音を生成
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
    //爆発のエフェクト
    Explosion::GenerateExplosion(_pos, 1000, 1);
    //位置と回転,速さの初期化
    _pos = _defaultPos;
    _rotate = _defaultRotate;
    _speed = vec2(0, 0);

    gGame.GameRestart();
}//void Ship::GenerateExplosion()

void Ship::Reset()
{
    //位置と回転,速さの初期化
    _pos = _defaultPos;
    _rotate = _defaultRotate;
    _speed = vec2(0, 0);
    //もとの向きへ旋回させる
    Turn();
    //弾を消去する
    _bullets.clear();
    //加速していないことにする
    memset(_keys, 0, sizeof(_keys));
    memset(_lastKeys, 0, sizeof(_lastKeys));

    _isDead = false;
}//void Ship::Reset()







