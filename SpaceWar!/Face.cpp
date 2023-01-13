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
	//	読み込みモードでファイルを開く
	fopen_s(&fp, fileName, "r");

	if (fp == NULL)
	{
		printf("ファイルはありません\n");
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
	//光源を有効にする
	glEnable(GL_LIGHT0);
	//光源の位置
	float pos[4] = { x, y, z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}//ParallelLightSource(double x, double y, double z)


void SetColorWithLight(float r, float g, float b)
{

	//面属性の設定
	float mat_diffuse[4] = { r,g,b,1.0f }; //拡散反射係数
	float mat_specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f }; //鏡面反射係数
	float mat_ambient[4] = { r,g,b,1.0f }; //環境光反射係数
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
	//ベクトルp0p1,p1p2を求める
	VECTOR3D a = { p[face.n1].x - p[face.n0].x, p[face.n1].y - p[face.n0].y, p[face.n1].z - p[face.n0].z };
	VECTOR3D b = { p[face.n2].x - p[face.n1].x, p[face.n2].y - p[face.n1].y, p[face.n2].z - p[face.n1].z };

	//単位ベクトル
	a = Normalize(a);
	//printf(" Normalize a      a.x = %f, a.y = %f, a.z = %f\n",a.x,a.y,a.z);
	b = Normalize(b);
	//printf(" Normalize b      b.x = %f, b.y = %f, b.z = %f\n",b.x,b.y,b.z);
	//外積を求める
	VECTOR3D vec = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };

	return vec;
}

void DrawFace(FACE face, float r, float g, float b)
{

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	SetColorWithLight(r, g, b);


	//単位法線ベクトル
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

	glEnd();//描画モードの終了
}

void CircleWithShading(double radius, POINT3D center, double viewpoint, LIGHT light)
{
	//中心の座標
	POINT3D p3d = center;
	//POINT3D p3d = { 0.0,0.0,-300.0 };
	double zv = viewpoint;
	//double zv = 200.0;

	double Xc = p3d.x;
	double Yc = p3d.y;
	double Zc = p3d.z;

	//光源の方向と色
	//LIGHT light = { {-1.0,1.0,1.0},{1.0,1.0,1.0} };
	light.dir = Normalize(light.dir);

	glBegin(GL_POINTS); //点の描画モード
	for (int i = -SCREEN_WIDTH / 2; i < SCREEN_WIDTH / 2; i++)
	{
		for (int j = -SCREEN_HEIGHT / 2; j < SCREEN_HEIGHT; j++)
		{
			double xs = (double)j;
			double ys = (double)i;
			double A = xs * xs + ys * ys + zv * zv;
			double B = -(xs * Xc + ys * Yc - zv * Zc + zv * zv);
			double C = Xc * Xc + Yc * Yc + (Zc - zv) * (Zc - zv) - radius * radius;
			//判別式
			double D = B * B - A * C;
			if (D >= 0)
			{
				//二次方程式の解
				double t1 = (-B + sqrt(D)) / A;
				double t2 = (-B - sqrt(D)) / A;

				//描画の処理///////////////////////////////////////////////////////////////
				//x ,y ,z
				double x = xs * t1;
				double y = ys * t1;
				double z = zv - zv * t1;

				//球の中心から(x,y,z)へのベクトル
				VECTOR3D op1 = { x - Xc,y - Yc,z - Zc };

				//単位ベクトルにすることで単位法線ベクトルとする
				op1 = Normalize(op1);

				//視点
				VECTOR3D view = { 0.0, 0.0, zv };

				//視点から面fの0番目の頂点へ向かうベクトル
				VECTOR3D vec = { x - view.x, y - view.y, z - view.z };

				//内積を求める l*n cos(x)
				double dot = vec.x * op1.x + vec.y * op1.y + vec.z * op1.z;


				//printf("p1 dot : %f\n",dot);

				//I0 光源の色の成分
				VECTOR3D i0 = { light.c.r,light.c.g,light.c.b };

				//拡散反射計数
				VECTOR3D  k = { 1.0, 1.0, 0.0 };

				if (0.0 > dot)
				{
					double dot1 = light.dir.x * op1.x + light.dir.y * op1.y + light.dir.z * op1.z;
					//RGBごとの計算
					double r = k.x * dot * i0.x;
					double g = k.y * dot * i0.y;
					double b = k.z * dot * i0.z;

					//printf("R : %f , G : %f, B : %f\n\n",r,g,b);


					POINT3D p3_1 = { x,y,z };
					POINT2D p2_1 = Perspective(p3_1);

					//色の変更
					glColor3d(r, g, b);

					if (p2_1.x * p2_1.x + p2_1.y * p2_1.y <= radius * radius && t1 > 0.0)
					{
						glVertex2d(p2_1.x, p2_1.y); //描画する座標の指定
					}

				}


				//x ,y ,z
				x = xs * t2;
				y = ys * t2;
				z = zv - zv * t2;

				//球の中心から(x,y,z)へのベクトル
				VECTOR3D op2 = { x - Xc,y - Yc,z - Zc };

				//単位ベクトルにする
				op2 = Normalize(op2);


				//視点から面fの0番目の頂点へ向かうベクトル
				VECTOR3D vec2 = { x - view.x, y - view.y, z - view.z };

				dot = vec.x * op2.x + vec.y * op2.y + vec.z * op2.z;


				//printf("p2 dot : %f\n",dot2);

				if (0.0 > dot)
				{

					//内積を求める l*n cos(x)
					double dot2 = light.dir.x * op2.x + light.dir.y * op2.y + light.dir.z * op2.z;

					//RGBごとの計算
					double r2 = k.x * dot2 * i0.x;
					double g2 = k.y * dot2 * i0.y;
					double b2 = k.z * dot2 * i0.z;

					//printf("R2 : %f , G2 : %f, B2 : %f\n\n",r2,g2,b2);

					POINT3D p3_2 = { x,y,z };
					POINT2D p2_2 = Perspective(p3_2);

					//色の変更
					glColor3d(r2, g2, b2);
					if (p2_2.x * p2_2.x + p2_2.y * p2_2.y <= radius * radius && t2 > 0.0)
					{
						glVertex2d(p2_2.x, p2_2.y); //描画する座標の指定
					}

				}//if (0.0 > dot)
			}//if (D >= 0)
			/////////////////////////////////////////////////////////////////////////


		}//for (int j = -SCREEN_HEIGHT / 2; j < SCREEN_HEIGHT; j++)
	}//for (int i = -SCREEN_WIDTH / 2; i < SCREEN_WIDTH / 2; i++)
	glEnd();//描画モードの終了

	//色を白へと戻す
	glColor3d(1, 1, 1);

}//CircleWithShading(double radius, POINT3D center, double viewpoint, LIGHT light)

void mySolidSphere(float radius, int slices, int stacks)
{
	//半径
	float r = radius;
	//配列の初期化
	for (int i = 0; i < slices + 1; i++)
	{
		for (int j = 0; j < stacks + 1; j++)
		{
			//座標を求める
			float theta = (2.0f * (float)M_PI * (float)i) / (float)slices;
			float fai = ((float)M_PI * (float)j) / (float)stacks - (float)(M_PI / 2);
			//x,y,z座標へ変換する
			float x = r * cos(fai) * cos(theta);
			float y = r * cos(fai) * sin(theta);
			float z = r * sin(fai);
			//代入
			quads[i][j][0] = (int)x;
			quads[i][j][1] = (int)y;
			quads[i][j][2] = (int)z;

		}
	}


	//Normal3dを使えるようにする
	glEnable(GL_NORMALIZE);

	//四角形の描画
	for (int i = 0; i < slices; i++)
	{
		for (int j = 0; j < stacks; j++)
		{
			glBegin(GL_QUADS); //四角形の描画モード


			//1つ目
			glNormal3d(quads[i][j][0],
				quads[i][j][1],
				quads[i][j][2]);

			glVertex3d(quads[i][j][0],
				quads[i][j][1],
				quads[i][j][2]);

			//2つ目
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

			glEnd();//描画モードの終了

		}//for(int j=0;j<stacks + 1;j++)
	}//for(int i=0;i<slices + 1;i++)

}//void mySolidSphere(double radius,int slices,int stacks)