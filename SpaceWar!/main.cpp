//�w�b�_�[
#include<iostream>
#include"Audio.h"
#include<time.h>
#include"GameHeader.h"

//�L�[���i�[����z��̗v�f��
#define MAX_KEY 256

//�L�[�{�[�h�̓��͂�ۑ����邷��z��
bool gKeys[MAX_KEY];
//1�t���[���O�̓���
bool gLastKeys[MAX_KEY];
//�����ꂽ�L�[�̓���
bool gDownKeys[MAX_KEY];

//�^�C�g����ʂ̃J�[�\���̈ʒu
vec2 gCursorPos[] = {
	vec2(),
	vec2()
};

void Display()
{
	//��ʂ��N���A����
	//glClear(GL_COLOR_BUFFER_BIT);
	//2D�ϊ�
	//�ˉe�s�񃂁[�h���g�p����
	glMatrixMode(GL_PROJECTION);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//�񎟌���Ԃ��`
	gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);

	//���f���r���[�s�񃂁[�h���g�p����
	glMatrixMode(GL_MODELVIEW);
	//�s��𖈃t���[��������
	glLoadIdentity();

	//ViewPort�̎擾
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	//�c������
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(0x00, 0x00, 0x00, 0x15);
	glRectf(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	glDisable(GL_BLEND);



	//�F��߂�
	glColor3ub(0xff, 0xff, 0xff);

	//�w�i�̕`��
	gMainBG.Draw();
	//���z�̕`��
	gSun.Draw();


	//�_�̃T�C�Y��ݒ肷��
	float scale = 1.0f;
	glPointSize((float)viewport[3] / SCREEN_HEIGHT + 1);
	glTranslatef(1, 1, 0);
	glScalef(scale, scale, 0);


	//�����̕`��
	Explosion::AllDraw();
	//Ship�̕`��
	Ship::AllDraw();

	//�^�C�g����ʂ̃e�L�X�g
	if ((gGame._demoSceen == true) &&
		(gGame._1P == false) &&
		(gGame._2P == false))
	{
	
		//�^�C�g���̃e�L�X�g
		{
			vec2 sizeTitle = vec2(32, 32);
			Color color;
			const char* title = "SPACE WAR";
			float stdWidth = FontGetLength(title);
			Text2D(((float)SCREEN_WIDTH - stdWidth) / 2.0f + 150.0f, (float)SCREEN_HEIGHT / 4.0f,
				color.White, sizeTitle, sizeTitle.x / 16.0f, title);
		}

		//��l�ŗV�Ԃ���l�ŗV�Ԃ��̃e�L�X�g
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

	//	//�����̓_��
	//	static unsigned int count = 0;

	//	Text2D(((float)SCREEN_WIDTH - stdWidth) / 2.0f + 320,
	//		(float)SCREEN_HEIGHT * 5.0f / 8.0f, color.White, size, size.x / 8.0f, str);

	//}//if ((gGame._demoSceen == true) && (gGame.GetCount() % 64 == 4))

	//�X�R�A�̕`��
	{
		vec2 size = vec2(64, 64);
		Color color;
		for (int i = 0; i < MAX_INDEX_SHIP; i++)
		{
			Text2D(SCREEN_WIDTH / 2.0f * (float)i + (SCREEN_WIDTH / 2.0f - size.x * 2.0f) / 2.0f
				, 8.0f, color.White, size, 4.0f, "%02d", gShips[i].GetScore());
		}//for (int i = 0; i < MAX_INDEX_SHIP; i++)


	}

	//�`��̎��s
	glFlush();

	//�o�b�t�@��؂�ւ���
	//glutSwapBuffers();

}//Display()

//PC�̏������x�Ɉˑ����Ȃ��悤�ɂ��鏈��
void Timer(int value)
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		//���݃L�[��������Ă��āA1�t���[���O�ɃL�[��������Ă��Ȃ����
		//���̎��_�ŏ��߂ăL�[�������ꂽ���ɂȂ�
		//����ɂ��1��̔��˃{�^�����͂ɂ��e��1�����˂���
		gDownKeys[i] = gKeys[i] && (gLastKeys[i] == false);
	}//for (int i = 0; i < MAX_KEY; i++)

	//�ċN
	glutTimerFunc(1000 / 60, Timer, 0);

	//�I�[�f�B�I�̃A�b�v�f�[�g
	AudioUpdate();

	//�e�Ɣ����̕\���̍X�V
	Explosion::AllUpdate();
	//�v���C���[�̍X�V
	Ship::AllUpdate();
	//�Q�[���̏����̃A�b�v�f�[�g
	gGame.Update();

	//�ĕ`��
	glutPostRedisplay();

	//lastKeys��1�t���[���O�̃L�[��ۑ�����
	memcpy(gLastKeys, gKeys, sizeof(gKeys));
}//Timer(int value)

//��ʃT�C�Y���ύX���ꂽ���̏���
void Reshape(int width, int height)
{
	std::cout << "reshshape: width:" << width << " height:" << height << std::endl;
	//��ʃT�C�Y��ύX�����Ƃ��ɁA���؂�镔�����Ȃ���
	glViewport(0, 0, width, height);//GLint x, GLint y, GLsizei width, GLsizei height


}//Reshape(int width,int height)

//�L�[�{�[�h���������Ƃ��̏���
//x y �̓}�E�X�̍��W
void Keyboard(unsigned char key, int x, int y)
{
	//Esc�ŃQ�[�����I������
	if (key == 0x1b)
	{
		exit(0);
	}

	gKeys[key] = true;

	//�f�����ł���ΔC�ӂ̃L�[����͂��邱�Ƃ�
	if ((gGame._demoSceen == true) && 
		(gLastKeys[key] == false))
	{
		//1P�̑I��
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
			//�����������Ȃ�
		}//else
	}//if (gGame._demoSceen == true)

	//printf("KeyboradDown  : \'%c\' (%#x)\n", key, key);
}//Keyboard(unsigned char key, int x, int y)

//�L�[�{�[�h�𗣂������̏���
void KeyboardUp(unsigned char key, int x, int y)
{
	//printf("KeyboradUp    : \'%c\' (%#x)\n", key, key);
	gKeys[key] = false;
}//KeyboardUp(unsigned char key, int x, int y)



int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE);//�_�u���o�b�t�@��L���ɂ���
	glutInitWindowPosition(0, 0);
	{
		//�E�B���h�E�̃T�C�Y 4:3�ɂ���
		int width = (720 - 32) * 4 / 3;
		int height = 720 - 32;
		glutInitWindowSize(width, height);
	}
	glutCreateWindow("Space War");//�E�B���h�E�̃^�C�g��

	//�����̏�����
	srand((unsigned int)time(NULL));

	//Audio�̏�����
	if (AudioInit() == -1)
	{
		return -1;
	}
	//Font�̏�����
	FontInitialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//FontSetXYSize(2, 7);

	//�f���̃t���O��true�ɂ���
	gGame._demoSceen = true;

	//Ship�̏�����
	Ship::AllInitialize();
	//�w�i�̏�����
	gMainBG.Initialize();

	//���_�z���L���ɂ���
	glEnableClientState(GL_VERTEX_ARRAY);

	glutDisplayFunc(Display);
	//glutIdleFunc(Idle);
	glutTimerFunc(0, Timer, 0);//0�~���b���Timer�֐����J�n����,value��0
	//��ʃT�C�Y���ύX���ꂽ���ɌĂяo�����A�R�[���o�b�N�֐�
	glutReshapeFunc(Reshape);
	//�L�[�{�[�h����
	glutKeyboardFunc(Keyboard);// void (* callback)( unsigned char, int, int ) 
	//�L�[�{�[�h�𗣂������̏���
	glutKeyboardUpFunc(KeyboardUp);


	//�L�[�{�[�h�̃��s�[�g�i�]��ɂ������A�����́j�𖳌��ɂ���
	//��񂵂����͂���Ȃ�
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore


	//�Q�[�����[�v
	glutMainLoop();

	return 0;
}//main(int argc,char* argv[])