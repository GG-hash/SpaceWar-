//ヘッダー
#include<iostream>
#include"Audio.h"
#include<time.h>
#include"GameHeader.h"

//キーを格納する配列の要素数
#define MAX_KEY 256

//キーボードの入力を保存するする配列
bool gKeys[MAX_KEY];
//1フレーム前の入力
bool gLastKeys[MAX_KEY];
//押されたキーの入力
bool gDownKeys[MAX_KEY];

//タイトル画面のカーソルの位置
vec2 gCursorPos[] = {
	vec2(),
	vec2()
};

void Display()
{
	//画面をクリアする
	//glClear(GL_COLOR_BUFFER_BIT);
	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//ViewPortの取得
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	//残像処理
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0x00, 0x00, 0x00, 0x15);
	glRectf(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	glDisable(GL_BLEND);



	//色を戻す
	glColor3ub(0xff, 0xff, 0xff);

	//背景の描画
	gMainBG.Draw();
	//太陽の描画
	gSun.Draw();


	//点のサイズを設定する
	float scale = 1.0f;
	glPointSize((float)viewport[3] / SCREEN_HEIGHT + 1);
	glTranslatef(1, 1, 0);
	glScalef(scale, scale, 0);


	//爆発の描画
	Explosion::AllDraw();
	//Shipの描画
	Ship::AllDraw();

	//タイトル画面のテキスト
	if ((gGame._demoSceen == true) &&
		(gGame._1P == false) &&
		(gGame._2P == false))
	{
	
		//タイトルのテキスト
		{
			vec2 sizeTitle = vec2(32, 32);
			Color color;
			const char* title = "SPACE WAR";
			float stdWidth = FontGetLength(title);
			Text2D(((float)SCREEN_WIDTH - stdWidth) / 2.0f + 150.0f, (float)SCREEN_HEIGHT / 4.0f,
				color.White, sizeTitle, sizeTitle.x / 16.0f, title);
		}

		//一人で遊ぶか二人で遊ぶかのテキスト
		//1P
		{
			vec2 size1PText = vec2(20, 20);
			const char* Text1P = "1P PRESS [W] ";
			Color color;
			float stdWidth = FontGetLength(Text1P);
			Text2D(((float)SCREEN_WIDTH - stdWidth) / 2.0f + 80.0f, (float)-SCREEN_HEIGHT / 4.0f + 400,
				color.White, size1PText, size1PText.x / 20.0f, Text1P);
		}
		//2P
		{
			vec2 size1PText = vec2(20, 20);
			const char* Text1P = "2P PRESS [S] ";
			Color color;
			float stdWidth = FontGetLength(Text1P);
			Text2D(((float)SCREEN_WIDTH - stdWidth) / 2.0f + 1.0f, (float)-SCREEN_HEIGHT / 4.0f + 430,
				color.White, size1PText, size1PText.x / 20.0f, Text1P);
		}


	}//if ((gGame._demoSceen == true) &&(gGame._1P == false) &&(gGame._2P == false))

	//if ((gGame._demoSceen == true) && (gGame.GetCount() % 64 == 4))
	//{
	//	vec2 size = vec2(16, 16);
	//	Color color;
	//	const char* str = "PRESS ANY KEY";
	//	float stdWidth = FontGetLength(str);

	//	//文字の点滅
	//	static unsigned int count = 0;

	//	Text2D(((float)SCREEN_WIDTH - stdWidth) / 2.0f + 320,
	//		(float)SCREEN_HEIGHT * 5.0f / 8.0f, color.White, size, size.x / 8.0f, str);

	//}//if ((gGame._demoSceen == true) && (gGame.GetCount() % 64 == 4))

	//スコアの描画
	{
		vec2 size = vec2(64, 64);
		Color color;
		for (int i = 0; i < MAX_INDEX_SHIP; i++)
		{
			Text2D(SCREEN_WIDTH / 2.0f * (float)i + (SCREEN_WIDTH / 2.0f - size.x * 2.0f) / 2.0f
				, 8.0f, color.White, size, 4.0f, "%02d", gShips[i].GetScore());
		}//for (int i = 0; i < MAX_INDEX_SHIP; i++)


	}

	//描画の実行
	glFlush();

	//バッファを切り替える
	//glutSwapBuffers();

}//Display()

//PCの処理速度に依存しないようにする処理
void Timer(int value)
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		//現在キーが押されていて、1フレーム前にキーが押されていなければ
		//その時点で初めてキーを押された事になる
		//これにより1回の発射ボタン入力により弾を1発発射する
		gDownKeys[i] = gKeys[i] && (gLastKeys[i] == false);
	}//for (int i = 0; i < MAX_KEY; i++)

	//再起
	glutTimerFunc(1000 / 60, Timer, 0);

	//オーディオのアップデート
	AudioUpdate();

	//弾と爆発の表示の更新
	Explosion::AllUpdate();
	//プレイヤーの更新
	Ship::AllUpdate();
	//ゲームの処理のアップデート
	gGame.Update();

	//再描画
	glutPostRedisplay();

	//lastKeysへ1フレーム前のキーを保存する
	memcpy(gLastKeys, gKeys, sizeof(gKeys));
}//Timer(int value)

//画面サイズが変更された時の処理
void Reshape(int width, int height)
{
	std::cout << "reshshape: width:" << width << " height:" << height << std::endl;
	//画面サイズを変更したときに、見切れる部分をなくす
	glViewport(0, 0, width, height);//GLint x, GLint y, GLsizei width, GLsizei height


}//Reshape(int width,int height)

//キーボードを押したときの処理
//x y はマウスの座標
void Keyboard(unsigned char key, int x, int y)
{
	//Escでゲームを終了する
	if (key == 0x1b)
	{
		exit(0);
	}

	gKeys[key] = true;

	//デモ中であれば任意のキーを入力することで
	if ((gGame._demoSceen == true) && 
		(gLastKeys[key] == false))
	{
		//1Pの選択
		if (key == 'w')
		{
			gGame.GameStart();
			gGame._1P = true;
		}//if (key == 'w')
		else if (key == 's')
		{
			gGame.GameStart();
			gGame._2P = true;
		}//else if (key == 's')
		else
		{
			//何も処理しない
		}//else
	}//if (gGame._demoSceen == true)

	//printf("KeyboradDown  : \'%c\' (%#x)\n", key, key);
}//Keyboard(unsigned char key, int x, int y)

//キーボードを離した時の処理
void KeyboardUp(unsigned char key, int x, int y)
{
	//printf("KeyboradUp    : \'%c\' (%#x)\n", key, key);
	gKeys[key] = false;
}//KeyboardUp(unsigned char key, int x, int y)



int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE);//ダブルバッファを有効にする
	glutInitWindowPosition(0, 0);
	{
		//ウィンドウのサイズ 4:3にする
		int width = (720 - 32) * 4 / 3;
		int height = 720 - 32;
		glutInitWindowSize(width, height);
	}
	glutCreateWindow("Space War");//ウィンドウのタイトル

	//乱数の初期化
	srand((unsigned int)time(NULL));

	//Audioの初期化
	if (AudioInit() == -1)
	{
		return -1;
	}
	//Fontの初期化
	FontInitialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//FontSetXYSize(2, 7);

	//デモのフラグをtrueにする
	gGame._demoSceen = true;

	//Shipの初期化
	Ship::AllInitialize();
	//背景の初期化
	gMainBG.Initialize();

	//頂点配列を有効にする
	glEnableClientState(GL_VERTEX_ARRAY);

	glutDisplayFunc(Display);
	//glutIdleFunc(Idle);
	glutTimerFunc(0, Timer, 0);//0ミリ秒後にTimer関数を開始して,valueは0
	//画面サイズが変更された時に呼び出される、コールバック関数
	glutReshapeFunc(Reshape);
	//キーボード入力
	glutKeyboardFunc(Keyboard);// void (* callback)( unsigned char, int, int ) 
	//キーボードを離した時の処理
	glutKeyboardUpFunc(KeyboardUp);


	//キーボードのリピート（余りにも早い連続入力）を無効にする
	//一回しか入力されない
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore


	//ゲームループ
	glutMainLoop();

	return 0;
}//main(int argc,char* argv[])