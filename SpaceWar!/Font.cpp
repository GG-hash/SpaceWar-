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
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//GLint viewport[4];
	////The params parameter returns four values: 
	////the x and y window coordinates of the viewport, 
	////followed by its width and height. See glViewport.
	//glGetIntegerv(GL_VIEWPORT, viewport);

	//�񎟌���Ԃ��`
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void FontEnd()
{
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
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
	//�t�H���g�̑����͈̔͂��擾����
	glGetFloatv(GL_LINE_WIDTH_RANGE, thickness);
	//��ԏ������t�H���g�̑�����Ԃ�
	return thickness[0]; // return 0.5
}

float FontGetThicknessMax()
{
	GLfloat thickness[2];
	//�t�H���g�̑����͈̔͂��擾����
	glGetFloatv(GL_LINE_WIDTH_RANGE, thickness);
	//��ԑ傫���t�H���g�̑�����Ԃ�
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
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	//�t�H���g�̑������X�N���[���̃T�C�Y�ɍ��킹��
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

//Text2D(float X���W, float Y���W, unsigned char* �F, float �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, vec2 sizeXY, const char* charactor, ...)
{
	FontSetPosition(posX, posY);

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//�F�̐ݒ�
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//�����T�C�Y
	_sizeXY = sizeXY;

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);
	//�t�H���g�̑������X�N���[���̃T�C�Y�ɍ��킹��
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
	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�

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
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//�F�̐ݒ�
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//�����T�C�Y
	_sizeXY = sizeXY;

	//�����̑���
	_thickness = thickness;
	glLineWidth(_thickness);

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	//�t�H���g�̑������X�N���[���̃T�C�Y�ɍ��킹��
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

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�

}


//Text2D(float X���W, float Y���W, unsigned char* �F, float �����̑���, const char* ������, ...)
void Text2D(float posX, float posY, unsigned char* color, float thickness, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//�F�̐ݒ�
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];


	//�����̑���
	_thickness = thickness;
	glLineWidth(_thickness);

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	//�t�H���g�̑������X�N���[���̃T�C�Y�ɍ��킹��
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

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
}

void Text2D(float posX, float posY, unsigned char* color, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	//������
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);



	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//�F�̐ݒ�
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];

	//�����T�C�Y
	_size = FONT_DEFAULT_SIZE / 2;

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	//�t�H���g�̑������X�N���[���̃T�C�Y�ɍ��킹��
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

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
}

//Text2D(float X���W, float Y���W, float �����̃T�C�Y, const char* ������, ...)
void Text2D(float posX, float posY, vec2 sizeXY, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	//������
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//���F�̐ݒ�
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//�����T�C�Y
	_sizeXY = sizeXY;

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	//�t�H���g�̑������X�N���[���̃T�C�Y�ɍ��킹��
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

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
}

//Text2D(float X���W, float Y���W,const char* ������, ...)
void Text2D(float posX, float posY, const char* charactor, ...)
{
	FontSetPosition(posX, posY);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);//�S�Ă̕`�������L��

	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(0, _screenSize.x, _screenSize.y, 0);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//���F�̐ݒ�
	_color[0] = 0xff;
	_color[1] = 0xff;
	_color[2] = 0xff;

	//�����T�C�Y
	float size = FONT_DEFAULT_SIZE / 2;

	//�����̕`��
	//���ƌ^���ς̃��X�g
	va_list argList;
	va_start(argList, charactor);
	//�ύX�ł���������當����𐶐�����
	char str[256];
	vsprintf_s(str, charactor, argList);
	va_end(argList);

	//�V�����F�̐ݒ�
	glColor3ub(_color[0], _color[1], _color[2]);

	//�t�H���g�̑������X�N���[���̃T�C�Y�ɍ��킹��
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

	//�����̕`��I��
	glPopMatrix();
	glPopAttrib();//�S�Ă̕`�摮�������ɖ߂�
}
