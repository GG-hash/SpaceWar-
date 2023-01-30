#include "MainBackGround.h"
#include"glut.h"
#include"GameHeader.h"
#include"Face.h"

//グローバルなインスタンス
MainBackGround gMainBG;

MainBackGround::MainBackGround() :_points()
{
}//MainBackGround::MainBackGround()


int MainBackGround::Initialize()
{
	//星の座標をセットする
	for (int i = 0; i < MAX_STAR; i++)
	{
		_points[i] = vec2(SCREEN_WIDTH * (float)rand() / RAND_MAX - SCREEN_WIDTH / 2.0f,
			SCREEN_HEIGHT * (float)rand() / RAND_MAX - SCREEN_HEIGHT / 2.0f);
	}//for (int i = 0; i > MAX_STAR; i++)
	return 0;
}//int MainBackGround::Initialize()


void MainBackGround::Update()
{
}//void MainBackGround::Update()


void MainBackGround::Draw()
{
	//星を煌かせる
	vector<vec2> vec;
	for (int i = 0; i < MAX_STAR; i++)
	{
		//ランダムで星を選ぶ
		if (rand() % TINCLE_CYCLE == 0)
		{
			vec.push_back(_points[i]);
		}
	}//for (int i = 0; i < MAX_STAR; i++)

	//ランダムで選ばれた星を描画する
	if (vec.size() > 0)
	{
		glVertexPointer(2, GL_FLOAT, 0, vec.data());
		glDrawArrays(GL_POINTS, 0, vec.size());
	}//if (vec.size() > 0)

	//背景の惑星の描画
	POINT3D center = { 0 ,0 ,-1100.0 };
	LIGHT light = { {0.0, 0.0,1.0},{1.0,1.0,1.0} };
	CircleWithShading(200.0, center, 200.0, light);



}//void MainBackGround::Draw()


