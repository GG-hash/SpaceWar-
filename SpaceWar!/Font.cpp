#include "Font.h"

//Font()
//{
//	/*_pos = {};
//	_size = FONT_DEFAULT_SIZE;
//	_color[0] = 1;
//	_color[1] = 1;
//	_color[2] = 1;*/
//}

void FontInitialize(float width, float height)
{
	FontScreenSize(width, height);
	FontSetXYSize(8, 8);
}//FontInitialize(float width, float height)

void FontScreenSize(float width, float height)
{
	_screenSize = vec2(width, height);
}// FontScreenSize(float width, float height)


void FontBegin()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//GLint viewport[4];
	////The params parameter returns four values: 
	////the x and y window coordinates of the viewport, 
	////followed by its width and height. See glViewport.
	//glGetIntegerv(GL_VIEWPORT, viewport);

	//二次元空間を定義
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void FontEnd()
{
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}

//void FontSetFont(int font)
//{
//	switch (font)
//	{
//	case FONT_FONT_ROMAN:
//		FONT = GLUT_STROKE_ROMAN;
//		break;
//	case FONT_FONT_MONO_ROMAN:
//		FONT = GLUT_STROKE_MONO_ROMAN;
//		break;
//	}
//}//FontSetFont(int font)


void FontSetPosition(float x, float y)
{
	FontSetPosition(vec2(x, y));
}

void FontSetPosition(vec2 const& pos)
{
	_originPos = _pos = pos;
}


float FontGetSize()
{
	return _size;
}

vec2 FontGetXYSize()
{
	return _sizeXY;
}

//float FontGetSize()
//{
//	return _size + FONT_DEFAULT_LINE_SPACE * _size/FONT_DEFAULT_SIZE;
//}

void FontSetSize(float size)
{
	_size = size;
}

void FontSetXYSize(vec2 const& sizeXY)
{
	_sizeXY = sizeXY;
}

void FontSetXYSize(float width, float height)
{
	FontSetXYSize(vec2(width, height));
}

float FontGetThicknessMin()
{
	GLfloat thickness[2];
	//フォントの太さの範囲を取得する
	glGetFloatv(GL_LINE_WIDTH_RANGE, thickness);
	//一番小さいフォントの太さを返す
	return thickness[0]; // return 0.5
}

float FontGetThicknessMax()
{
	GLfloat thickness[2];
	//フォントの太さの範囲を取得する
	glGetFloatv(GL_LINE_WIDTH_RANGE, thickness);
	//一番大きいフォントの太さを返す
	//return thickness[1];//
	return 10.0;
}

float FontGetThickness(int charactor)
{
	return glutStrokeWidth(FONT, charactor) * _sizeXY.x / FONT_DEFAULT_THICKNESS;
}

float FontGetLength(const unsigned char* str)
{
	return glutStrokeLength(FONT, str) * _sizeXY.x / FONT_DEFAULT_THICKNESS;
}

float FontGetLength(const char* str)
{
	return FontGetLength((unsigned char*)str);
}

void FontSetThickness(float thickness)
{
	_thickness = thickness;
}

void FontColor(unsigned char r, unsigned char g, unsigned char b)
{
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
}

void FontColor(unsigned char* color)
{
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];
}

void FontDraw(const char* charactor, ...)
{
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	//フォントの太さをスクリーンのサイズに合わせる
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLineWidth(_thickness * viewport[3] / _screenSize.y);

	char* ptr = str;


	for (; (*ptr != '\0') && (*ptr != '\n'); ptr++)
	{


		glPushMatrix();
		glTranslatef(_pos.x, _pos.y + _sizeXY.y, 0);
		//float s = _size / FONT_DEFAULT_SIZE;
		glScalef(_sizeXY.x / FONT_DEFAULT_THICKNESS, -_sizeXY.y / FONT_DEFAULT_SIZE, 0);
		glutStrokeCharacter(FONT, *ptr);
		_pos.x += FontGetThickness(*ptr);
		glPopMatrix();
	}


	if (*ptr == '\n')
	{
		_pos.x = _originPos.x;
		_pos.y += FontGetXYSize().y;
		FontDraw(++ptr);
	}


}

//Text2D(float X座標, float Y座標, unsigned char* 色, float 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, vec2 sizeXY, const char* charactor, ...)
{
	FontSetPosition(posX, posY);

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//色の設定
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//文字サイズ
	_sizeXY = sizeXY;

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);
	//フォントの太さをスクリーンのサイズに合わせる
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLineWidth(_thickness * viewport[3] / _screenSize.y);

	char* ptr = str;
	for (; (*ptr != '\0') && (*ptr != '\n'); ptr++)
	{


		glPushMatrix();
		glTranslatef(_pos.x, _pos.y + _sizeXY.y, 0);
		//float s = _size / FONT_DEFAULT_SIZE;
		glScalef(_sizeXY.x / FONT_DEFAULT_THICKNESS, -_sizeXY.y / FONT_DEFAULT_SIZE, 0);
		glutStrokeCharacter(FONT, *ptr);
		_pos.x += FontGetThickness(*ptr);
		glPopMatrix();
	}


	if (*ptr == '\n')
	{
		_pos.x = _originPos.x;
		_pos.y += FontGetXYSize().y;
		FontDraw(++ptr);
	}

	//FontEnd();
	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す

	/*FontBegin();

	FontColor(Color.LightGray);
	FontSetPosition(0, WINDOW_HEIGHT - FontGetSize() * 1.5);
	FontSetSize(FONT_DEFAULT_SIZE / 2);
	FontDraw("angle : %f", angle);

	FontEnd();*/
}

void Text2D(float posX, float posY, unsigned char* color, vec2 sizeXY, float thickness, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//色の設定
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//文字サイズ
	_sizeXY = sizeXY;

	//文字の太さ
	_thickness = thickness;
	glLineWidth(_thickness);

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	//フォントの太さをスクリーンのサイズに合わせる
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLineWidth(_thickness * viewport[3] / _screenSize.y);

	char* ptr = str;
	for (; (*ptr != '\0') && (*ptr != '\n'); ptr++)
	{


		glPushMatrix();
		glTranslatef(_pos.x, _pos.y + _sizeXY.y, 0);
		//float s = _size / FONT_DEFAULT_SIZE;
		glScalef(_sizeXY.x / FONT_DEFAULT_THICKNESS, -_sizeXY.y / FONT_DEFAULT_SIZE, 0);
		glutStrokeCharacter(FONT, *ptr);
		_pos.x += FontGetThickness(*ptr);
		glPopMatrix();
	}


	if (*ptr == '\n')
	{
		_pos.x = _originPos.x;
		_pos.y += FontGetXYSize().y;
		FontDraw(++ptr);
	}

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す

}


//Text2D(float X座標, float Y座標, unsigned char* 色, float 文字の太さ, const char* 文字列, ...)
void Text2D(float posX, float posY, unsigned char* color, float thickness, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//色の設定
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];


	//文字の太さ
	_thickness = thickness;
	glLineWidth(_thickness);

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	//フォントの太さをスクリーンのサイズに合わせる
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLineWidth(_thickness * viewport[3] / _screenSize.y);

	char* ptr = str;
	for (; (*ptr != '\0') && (*ptr != '\n'); ptr++)
	{


		glPushMatrix();
		glTranslatef(_pos.x, _pos.y + _sizeXY.y, 0);
		//float s = _size / FONT_DEFAULT_SIZE;
		glScalef(_sizeXY.x / FONT_DEFAULT_THICKNESS, -_sizeXY.y / FONT_DEFAULT_SIZE, 0);
		glutStrokeCharacter(FONT, *ptr);
		_pos.x += FontGetThickness(*ptr);
		glPopMatrix();
	}


	if (*ptr == '\n')
	{
		_pos.x = _originPos.x;
		_pos.y += FontGetXYSize().y;
		FontDraw(++ptr);
	}

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}

void Text2D(float posX, float posY, unsigned char* color, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	//初期化
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);



	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//色の設定
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//文字サイズ
	_size = FONT_DEFAULT_SIZE / 2;

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	//フォントの太さをスクリーンのサイズに合わせる
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLineWidth(_thickness * viewport[3] / _screenSize.y);

	char* ptr = str;
	for (; (*ptr != '\0') && (*ptr != '\n'); ptr++)
	{


		glPushMatrix();
		glTranslatef(_pos.x, _pos.y + _sizeXY.y, 0);
		//float s = _size / FONT_DEFAULT_SIZE;
		glScalef(_sizeXY.x / FONT_DEFAULT_THICKNESS, -_sizeXY.y / FONT_DEFAULT_SIZE, 0);
		glutStrokeCharacter(FONT, *ptr);
		_pos.x += FontGetThickness(*ptr);
		glPopMatrix();
	}


	if (*ptr == '\n')
	{
		_pos.x = _originPos.x;
		_pos.y += FontGetXYSize().y;
		FontDraw(++ptr);
	}

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}

//Text2D(float X座標, float Y座標, float 文字のサイズ, const char* 文字列, ...)
void Text2D(float posX, float posY, vec2 sizeXY, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	//初期化
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//白色の設定
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//文字サイズ
	_sizeXY = sizeXY;

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	//フォントの太さをスクリーンのサイズに合わせる
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLineWidth(_thickness * viewport[3] / _screenSize.y);

	char* ptr = str;
	for (; (*ptr != '\0') && (*ptr != '\n'); ptr++)
	{


		glPushMatrix();
		glTranslatef(_pos.x, _pos.y + _sizeXY.y, 0);
		//float s = _size / FONT_DEFAULT_SIZE;
		glScalef(_sizeXY.x / FONT_DEFAULT_THICKNESS, -_sizeXY.y / FONT_DEFAULT_SIZE, 0);
		glutStrokeCharacter(FONT, *ptr);
		_pos.x += FontGetThickness(*ptr);
		glPopMatrix();
	}


	if (*ptr == '\n')
	{
		_pos.x = _originPos.x;
		_pos.y += FontGetXYSize().y;
		FontDraw(++ptr);
	}

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}

//Text2D(float X座標, float Y座標,const char* 文字列, ...)
void Text2D(float posX, float posY, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//全ての描画特性を有効

	//2D変換
	//射影行列モードを使用する
	glMatrixMode(GL_PROJECTION);
	//行列を毎フレーム初期化
	glLoadIdentity();

	//二次元空間を定義
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//モデルビュー行列モードを使用する
	glMatrixMode(GL_MODELVIEW);
	//行列を毎フレーム初期化
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//白色の設定
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//文字サイズ
	float size = FONT_DEFAULT_SIZE / 2;

	//文字の描画
	//個数と型が可変のリスト
	va_list argList;
	va_start(argList, charactor);
	//変更できる引数から文字列を生成する
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//新しい色の設定
	glColor3ub(_color[0], _color[1], _color[2]);

	//フォントの太さをスクリーンのサイズに合わせる
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLineWidth(_thickness * viewport[3] / _screenSize.y);

	char* ptr = str;
	for (; (*ptr != '\0') && (*ptr != '\n'); ptr++)
	{


		glPushMatrix();
		glTranslatef(_pos.x, _pos.y + _sizeXY.y, 0);
		//float s = _size / FONT_DEFAULT_SIZE;
		glScalef(_sizeXY.x / FONT_DEFAULT_THICKNESS, -_sizeXY.y / FONT_DEFAULT_SIZE, 0);
		glutStrokeCharacter(FONT, *ptr);
		_pos.x += FontGetThickness(*ptr);
		glPopMatrix();
	}


	if (*ptr == '\n')
	{
		_pos.x = _originPos.x;
		_pos.y += FontGetXYSize().y;
		FontDraw(++ptr);
	}

	//文字の描画終了
	glPopMatrix();
	glPopAttrib();//全ての描画属性を元に戻す
}
