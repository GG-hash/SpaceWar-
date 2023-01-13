#include "Face.h"
#include"GameHeader.h"



POINT2D Perspective(POINT3D p)
{
	POINT2D point2 = { 0,0 };
	double viewpointZ = 200.0;
	point2.x = (viewpointZ * p.x) / (viewpointZ - p.z);
	point2.y = (viewpointZ * p.y) / (viewpointZ - p.z);
	return point2;
}//Perspective(POINT3D p)



int ReadSurfaceTxtData(const char* fileName)
{
	FILE* fp;
	//	�ǂݍ��݃��[�h�Ńt�@�C�����J��
	fopen_s(&fp, fileName, "r");

	if (fp == NULL)
	{
		printf("�t�@�C���͂���܂���\n");
		return -1;
	}


	fscanf_s(fp, "%d", &np);



	for (int i = 0; i < np; i++)
	{
		fscanf_s(fp, "%lf,%lf,%lf", &p[i].x, &p[i].y, &p[i].z);
		printf("%f,%f,%f\n", p[i].x, p[i].y, p[i].z);
	}


	fscanf_s(fp, "%d", &nf);
	printf("\n");

	for (int i = 0; i < nf; i++)
	{
		fscanf_s(fp, "%d,%d,%d,%d", &f[i].n0, &f[i].n1, &f[i].n2, &f[i].n3);
		printf("%d,%d,%d,%d\n", f[i].n0, f[i].n1, f[i].n2, f[i].n3);
	}

	fclose(fp);
	return 0;
}




void ParallelLightSource(float x, float y, float z)
{
	glEnable(GL_LIGHTING);
	//������L���ɂ���
	glEnable(GL_LIGHT0);
	//�����̈ʒu
	float pos[4] = { x, y, z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}//ParallelLightSource(double x, double y, double z)


void SetColorWithLight(float r, float g, float b)
{

	//�ʑ����̐ݒ�
	float mat_diffuse[4] = { r,g,b,1.0f }; //�g�U���ˌW��
	float mat_specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f }; //���ʔ��ˌW��
	float mat_ambient[4] = { r,g,b,1.0f }; //�������ˌW��
	float mat_shininess = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

}//etColorWithLight(double r, double g, double b)


VECTOR3D Normalize(VECTOR3D n)
{
	double dis = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	VECTOR3D vec = { n.x / dis, n.y / dis, n.z / dis };
	//printf(" Normalize vec.x = %f, vec.y = %f, vec.z = %f\n",vec.x,vec.y,vec.z);
	return vec;
}


VECTOR3D Normal(FACE face)
{
	//�x�N�g��p0p1,p1p2�����߂�
	VECTOR3D a = { p[face.n1].x - p[face.n0].x, p[face.n1].y - p[face.n0].y, p[face.n1].z - p[face.n0].z };
	VECTOR3D b = { p[face.n2].x - p[face.n1].x, p[face.n2].y - p[face.n1].y, p[face.n2].z - p[face.n1].z };

	//�P�ʃx�N�g��
	a = Normalize(a);
	//printf(" Normalize a      a.x = %f, a.y = %f, a.z = %f\n",a.x,a.y,a.z);
	b = Normalize(b);
	//printf(" Normalize b      b.x = %f, b.y = %f, b.z = %f\n",b.x,b.y,b.z);
	//�O�ς����߂�
	VECTOR3D vec = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };

	return vec;
}

void DrawFace(FACE face, float r, float g, float b)
{

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	SetColorWithLight(r, g, b);


	//�P�ʖ@���x�N�g��
	glEnable(GL_NORMALIZE);
	VECTOR3D n = Normal(face);
	glBegin(GL_POLYGON);
	glNormal3d(n.x, n.y, n.z);

	//glTexCoord2d(50, 50);
	glTexCoord2d(0, 1);
	glVertex3d(p[face.n0].x, p[face.n0].y, p[face.n0].z);

	glTexCoord2d(1, 1);
	glVertex3d(p[face.n1].x, p[face.n1].y, p[face.n1].z);

	glTexCoord2d(1, 0);
	glVertex3d(p[face.n2].x, p[face.n2].y, p[face.n2].z);

	glTexCoord2d(0, 0);
	glVertex3d(p[face.n3].x, p[face.n3].y, p[face.n3].z);

	glEnd();//�`�惂�[�h�̏I��
}

void CircleWithShading(double radius, POINT3D center, double viewpoint, LIGHT light)
{
	//���S�̍��W
	POINT3D p3d = center;
	//POINT3D p3d = { 0.0,0.0,-300.0 };
	double zv = viewpoint;
	//double zv = 200.0;

	double Xc = p3d.x;
	double Yc = p3d.y;
	double Zc = p3d.z;

	//�����̕����ƐF
	//LIGHT light = { {-1.0,1.0,1.0},{1.0,1.0,1.0} };
	light.dir = Normalize(light.dir);

	glBegin(GL_POINTS); //�_�̕`�惂�[�h
	for (int i = -SCREEN_WIDTH / 2; i < SCREEN_WIDTH / 2; i++)
	{
		for (int j = -SCREEN_HEIGHT / 2; j < SCREEN_HEIGHT; j++)
		{
			double xs = (double)j;
			double ys = (double)i;
			double A = xs * xs + ys * ys + zv * zv;
			double B = -(xs * Xc + ys * Yc - zv * Zc + zv * zv);
			double C = Xc * Xc + Yc * Yc + (Zc - zv) * (Zc - zv) - radius * radius;
			//���ʎ�
			double D = B * B - A * C;
			if (D >= 0)
			{
				//�񎟕������̉�
				double t1 = (-B + sqrt(D)) / A;
				double t2 = (-B - sqrt(D)) / A;

				//�`��̏���///////////////////////////////////////////////////////////////
				//x ,y ,z
				double x = xs * t1;
				double y = ys * t1;
				double z = zv - zv * t1;

				//���̒��S����(x,y,z)�ւ̃x�N�g��
				VECTOR3D op1 = { x - Xc,y - Yc,z - Zc };

				//�P�ʃx�N�g���ɂ��邱�ƂŒP�ʖ@���x�N�g���Ƃ���
				op1 = Normalize(op1);

				//���_
				VECTOR3D view = { 0.0, 0.0, zv };

				//���_�����f��0�Ԗڂ̒��_�֌������x�N�g��
				VECTOR3D vec = { x - view.x, y - view.y, z - view.z };

				//���ς����߂� l*n cos(x)
				double dot = vec.x * op1.x + vec.y * op1.y + vec.z * op1.z;


				//printf("p1 dot : %f\n",dot);

				//I0 �����̐F�̐���
				VECTOR3D i0 = { light.c.r,light.c.g,light.c.b };

				//�g�U���ˌv��
				VECTOR3D  k = { 1.0, 1.0, 0.0 };

				if (0.0 > dot)
				{
					double dot1 = light.dir.x * op1.x + light.dir.y * op1.y + light.dir.z * op1.z;
					//RGB���Ƃ̌v�Z
					double r = k.x * dot * i0.x;
					double g = k.y * dot * i0.y;
					double b = k.z * dot * i0.z;

					//printf("R : %f , G : %f, B : %f\n\n",r,g,b);


					POINT3D p3_1 = { x,y,z };
					POINT2D p2_1 = Perspective(p3_1);

					//�F�̕ύX
					glColor3d(r, g, b);

					if (p2_1.x * p2_1.x + p2_1.y * p2_1.y <= radius * radius && t1 > 0.0)
					{
						glVertex2d(p2_1.x, p2_1.y); //�`�悷����W�̎w��
					}

				}


				//x ,y ,z
				x = xs * t2;
				y = ys * t2;
				z = zv - zv * t2;

				//���̒��S����(x,y,z)�ւ̃x�N�g��
				VECTOR3D op2 = { x - Xc,y - Yc,z - Zc };

				//�P�ʃx�N�g���ɂ���
				op2 = Normalize(op2);


				//���_�����f��0�Ԗڂ̒��_�֌������x�N�g��
				VECTOR3D vec2 = { x - view.x, y - view.y, z - view.z };

				dot = vec.x * op2.x + vec.y * op2.y + vec.z * op2.z;


				//printf("p2 dot : %f\n",dot2);

				if (0.0 > dot)
				{

					//���ς����߂� l*n cos(x)
					double dot2 = light.dir.x * op2.x + light.dir.y * op2.y + light.dir.z * op2.z;

					//RGB���Ƃ̌v�Z
					double r2 = k.x * dot2 * i0.x;
					double g2 = k.y * dot2 * i0.y;
					double b2 = k.z * dot2 * i0.z;

					//printf("R2 : %f , G2 : %f, B2 : %f\n\n",r2,g2,b2);

					POINT3D p3_2 = { x,y,z };
					POINT2D p2_2 = Perspective(p3_2);

					//�F�̕ύX
					glColor3d(r2, g2, b2);
					if (p2_2.x * p2_2.x + p2_2.y * p2_2.y <= radius * radius && t2 > 0.0)
					{
						glVertex2d(p2_2.x, p2_2.y); //�`�悷����W�̎w��
					}

				}//if (0.0 > dot)
			}//if (D >= 0)
			/////////////////////////////////////////////////////////////////////////


		}//for (int j = -SCREEN_HEIGHT / 2; j < SCREEN_HEIGHT; j++)
	}//for (int i = -SCREEN_WIDTH / 2; i < SCREEN_WIDTH / 2; i++)
	glEnd();//�`�惂�[�h�̏I��

	//�F�𔒂ւƖ߂�
	glColor3d(1, 1, 1);

}//CircleWithShading(double radius, POINT3D center, double viewpoint, LIGHT light)

void mySolidSphere(float radius, int slices, int stacks)
{
	//���a
	float r = radius;
	//�z��̏�����
	for (int i = 0; i < slices + 1; i++)
	{
		for (int j = 0; j < stacks + 1; j++)
		{
			//���W�����߂�
			float theta = (2.0f * (float)M_PI * (float)i) / (float)slices;
			float fai = ((float)M_PI * (float)j) / (float)stacks - (float)(M_PI / 2);
			//x,y,z���W�֕ϊ�����
			float x = r * cos(fai) * cos(theta);
			float y = r * cos(fai) * sin(theta);
			float z = r * sin(fai);
			//���
			quads[i][j][0] = (int)x;
			quads[i][j][1] = (int)y;
			quads[i][j][2] = (int)z;

		}
	}


	//Normal3d���g����悤�ɂ���
	glEnable(GL_NORMALIZE);

	//�l�p�`�̕`��
	for (int i = 0; i < slices; i++)
	{
		for (int j = 0; j < stacks; j++)
		{
			glBegin(GL_QUADS); //�l�p�`�̕`�惂�[�h


			//1��
			glNormal3d(quads[i][j][0],
				quads[i][j][1],
				quads[i][j][2]);

			glVertex3d(quads[i][j][0],
				quads[i][j][1],
				quads[i][j][2]);

			//2��
			glNormal3d(quads[i + 1][j][0],
				quads[i + 1][j][1],
				quads[i + 1][j][2]);

			glVertex3d(quads[i + 1][j][0],
				quads[i + 1][j][1],
				quads[i + 1][j][2]);

			//
			glNormal3d(quads[i + 1][j + 1][0],
				quads[i + 1][j + 1][1],
				quads[i + 1][j + 1][2]);

			glVertex3d(quads[i + 1][j + 1][0],
				quads[i + 1][j + 1][1],
				quads[i + 1][j + 1][2]);

			//
			glNormal3d(quads[i][j + 1][0],
				quads[i][j + 1][1],
				quads[i][j + 1][2]);

			glVertex3d(quads[i][j + 1][0],
				quads[i][j + 1][1],
				quads[i][j + 1][2]);

			glEnd();//�`�惂�[�h�̏I��

		}//for(int j=0;j<stacks + 1;j++)
	}//for(int i=0;i<slices + 1;i++)

}//void mySolidSphere(double radius,int slices,int stacks)