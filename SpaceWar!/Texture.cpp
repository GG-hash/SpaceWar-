#include"Texture.h"
#include "Rect.h"

//�e�N�X�`����ID���i�[����z��
#define MAX_TEX 100
unsigned int gTexIDs[MAX_TEX];


int TextureFromBMP(const char* fileName, unsigned char* colorKey)
{
	FILE* file;

	//�t�@�C�����J��
	fopen_s(&file, fileName, "rb");
	//�t�@�C�����Ȃ������ꍇ
	if (file == nullptr)
	{
		printf("%s open failed !\n", fileName);
		return -1;
	}
	printf("%s has been successfully loaded.\n", fileName);

	//�w�b�_�[�̃f�[�^���i�[����
	BITMAPFILEHEADER bitFile;
	fread(&bitFile, sizeof BITMAPFILEHEADER, 1, file);
	//�摜�T�C�Y�̕\��
	//printf("BITMAPFILEHEADER : %d\n", bitFile.bfSize);

	BITMAPINFOHEADER bitInfo;
	fread(&bitInfo, sizeof BITMAPINFOHEADER, 1, file);
	printf("bitInfo Width : %d bitInfo Height : %d\n", bitInfo.biWidth, bitInfo.biHeight);
	//1pixle�����艽�r�b�g��
	printf("BitCount : %d\n", bitInfo.biBitCount);


	//�s�N�Z���f�[�^�̓ǂݍ���
	typedef struct
	{
		//RGBA�̒�`
		unsigned char r, g, b, a;
	}RGBA;

	//�s�N�Z���̍쐬�@�������̊m��
	RGBA* pixels = (RGBA*)malloc(sizeof(RGBA) * bitInfo.biWidth * bitInfo.biHeight);
	if (pixels == nullptr)
	{
		return -1;
	}
	printf("OK\n");
	//�p�f�B���O:
	int padding = (4 - bitInfo.biWidth * (bitInfo.biBitCount / 8) % 4) % 4;
	for (int y = 0; y < bitInfo.biHeight; y++)
	{
		for (int x = 0; x < bitInfo.biWidth; x++)
		{
			RGBA* tmpPix = &pixels[y * bitInfo.biWidth + x];
			//printf("OK\n");
			fread(tmpPix, 3, 1, file);
			//printf("fread OK\n");
			tmpPix->a = ((colorKey != nullptr) &&
				(tmpPix->r == colorKey[0]) &&
				(tmpPix->g == colorKey[1]) &&
				(tmpPix->b == colorKey[2])) ? 0x00 : 0xff;
			//printf("alpha OK\n");
		}
		fseek(file, padding, SEEK_CUR);
	}


	//BMP�t�@�C����RGBA�łȂ�BGR�ŕۑ�����Ă���ׁARGBA�ɏC������
	for (int y = 0; y < bitInfo.biHeight; y++)
	{
		for (int x = 0; x < bitInfo.biWidth; x++)
		{
			//�C������s�N�Z���̃A�h���X
			RGBA* pPixel = &pixels[y * bitInfo.biWidth + x];
			unsigned char tmp = pPixel->r;
			pPixel->r = pPixel->b;
			pPixel->b = tmp;
		}
	}

	//�摜�̏㉺���]���C������ �摜�̒��S����̉摜�Ɖ��̉摜�����ւ��邱�ƂŏC������
	for (int y = 0; y < bitInfo.biHeight / 2; y++)
	{
		for (int x = 0; x < bitInfo.biWidth; x++)
		{
			//�C������s�N�Z���̃A�h���X
			//��̃s�N�Z��
			RGBA* modPixUp = &pixels[y * bitInfo.biWidth + x];
			//���̃s�N�Z��
			RGBA* modPixDown = &pixels[(bitInfo.biHeight - 1 - y) * bitInfo.biWidth + x];

			RGBA tmp = *modPixUp;
			*modPixUp = *modPixDown;
			*modPixDown = tmp;

		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitInfo.biWidth, bitInfo.biHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	//�g�厞�̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //�摜���g�債���Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);
	//�k�����̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //�摜���k�������Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);

	//�N�����v�̐ݒ�@�摜�̈�ԉ��̃f�[�^���摜�̈�ԏ�̃f�[�^���Q�Ƃ��Ȃ��悤�ɂ���
	//���̃N�����v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//�c�̃N�����v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	//�f�[�^�̊J��
	free(pixels);
	//�t�@�C�������
	fclose(file);

	return 0;
}
//TextureFromBMP(const char* fileName)

int TextureFromBMP(const char* fileName, unsigned char colorKeyR, unsigned char colorKeyG, unsigned char colorKeyB)
{
	unsigned char colorKey[] = { colorKeyR, colorKeyG,  colorKeyB };
	return TextureFromBMP(fileName, colorKey);
}
// TextureFromBMP(const char* fileName, unsigned char colorKeyR, unsigned char colorKeyG, unsigned char colorKeyB)

TEX tex[TEX_MAX];

void TexFromFile(const char* fileName, int texNo)
{
	FILE* file;

	//�t�@�C�����J��
	fopen_s(&file, fileName, "rb");
	//�t�@�C�����Ȃ������ꍇ
	if (file == nullptr)
	{
		printf("%s open failed !\n", fileName);
		return;
	}
	printf("%s has been successfully loaded.\n", fileName);

	fread(&tex[texNo].bf, sizeof BITMAPFILEHEADER, 1, file);
	fread(&tex[texNo].bi, sizeof BITMAPINFOHEADER, 1, file);

	printf("bitInfo Width : %d bitInfo Height : %d\n", tex[texNo].bi.biWidth, tex[texNo].bi.biHeight);
	//1pixle�����艽�r�b�g��
	printf("BitCount : %d\n", tex[texNo].bi.biBitCount);

	typedef struct
	{
		unsigned char b, g, r;
	}BGR;

	BGR* bits = (BGR*)malloc(sizeof(BGR) * tex[texNo].bi.biWidth * tex[texNo].bi.biHeight);
	fread(bits, sizeof(BGR), tex[texNo].bi.biWidth * tex[texNo].bi.biHeight, file);

	//�s�N�Z���f�[�^�̓ǂݍ���
	typedef struct
	{
		//RGBA�̒�`
		unsigned char r, g, b, a;
	}RGBA;

	//�s�N�Z���̍쐬�@�������̊m��
	RGBA* pixels = (RGBA*)malloc(sizeof RGBA * tex[texNo].bi.biWidth * tex[texNo].bi.biHeight);
	if (pixels == nullptr)
	{
		return;
	}

	for (int i = 0; i < tex[texNo].bi.biWidth * tex[texNo].bi.biHeight; i++)
	{
		pixels[i].r = bits[i].r;
		pixels[i].g = bits[i].g;
		pixels[i].b = bits[i].b;
		//�J���[�L�[����v�����瓧���ɂ���
		/*pixels[i].a = ((colorKey != nullptr) &&
			(pixels[i].r == colorKey[0]) &&
			(pixels[i].g == colorKey[1]) &&
			(pixels[i].b == colorKey[2])) ? 0x00 : 0xff;*/
			//pixels[i].a = (bits[i].r == 0x00 && bits[i].g == 0xff && bits[i].b == 0x00)? 0x00 : 0xff;
	}

	glGenTextures(1, &tex[texNo].texture);
	glBindTexture(GL_TEXTURE_2D, tex[texNo].texture);


	//�g�厞�̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //�摜���g�債���Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);
	//�k�����̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //�摜���k�������Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex[texNo].bi.biWidth, tex[texNo].bi.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	free(bits);
	free(pixels);
	fclose(file);
}

int TextureAlphaFromBMP(const char* fileName, unsigned char* buffer)
{
	FILE* file;

	//�t�@�C�����J��
	fopen_s(&file, fileName, "rb");
	//�t�@�C�����Ȃ������ꍇ
	if (file == nullptr)
	{
		printf("%s open failed !\n", fileName);
		return -1;
	}
	printf("%s has been successfully loaded.\n", fileName);

	//�w�b�_�[�̃f�[�^���i�[����
	BITMAPFILEHEADER bitFile;
	fread(&bitFile, sizeof BITMAPFILEHEADER, 1, file);
	//�摜�T�C�Y�̕\��
	//printf("BITMAPFILEHEADER : %d\n", bitFile.bfSize);

	BITMAPINFOHEADER bitInfo;
	fread(&bitInfo, sizeof BITMAPINFOHEADER, 1, file);
	printf("bitInfo Width : %d bitInfo Height : %d\n", bitInfo.biWidth, bitInfo.biHeight);
	//1pixle�����艽�r�b�g��
	printf("BitCount : %d\n", bitInfo.biBitCount);

	//�p�f�B���O:
	int padding = (4 - bitInfo.biWidth * (bitInfo.biBitCount / 8) % 4) % 4;

	for (int i = 0; i < bitInfo.biHeight; i++)
	{
		for (int j = 0; j < bitInfo.biWidth; j++)
		{
			fread(&buffer[i * bitInfo.biWidth + j], 1, 1, file);
			//2�o�C�g�ǂݔ�΂�
			fseek(file, 2, SEEK_CUR);
		}
		//�p�f�B���O
		fseek(file, padding, SEEK_CUR);
	}

	//�摜�̏㉺���]���C������ �摜�̒��S����̉摜�Ɖ��̉摜�����ւ��邱�ƂŏC������
	for (int y = 0; y < bitInfo.biHeight / 2; y++)
	{
		for (int x = 0; x < bitInfo.biWidth; x++)
		{
			//�C������s�N�Z���̃A�h���X
			//��̃s�N�Z��
			unsigned char* modPixUp = &buffer[y * bitInfo.biWidth + x];
			//���̃s�N�Z��
			unsigned char* modPixDown = &buffer[(bitInfo.biHeight - 1 - y) * bitInfo.biWidth + x];

			unsigned char tmp = *modPixUp;
			*modPixUp = *modPixDown;
			*modPixDown = tmp;

		}//for (int x = 0; x < bitInfo.biWidth; x++)
	}//for (int y = 0; y < bitInfo.biHeight / 2; y++)

	//�s�N�Z���̃A���C�����g����
	//�������̃T�C�Y��1�P�ʂɂ��� �f�t�H���g��4�P��
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//�]��
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, bitInfo.biWidth, bitInfo.biHeight,
		0, GL_ALPHA, GL_UNSIGNED_BYTE, buffer);*/

		//�g�厞�̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //�摜���g�債���Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);
	//�k�����̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //�摜���k�������Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);

	//�N�����v�̐ݒ�@�摜�̈�ԉ��̃f�[�^���摜�̈�ԏ�̃f�[�^���Q�Ƃ��Ȃ��悤�ɂ���
	//���̃N�����v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//�c�̃N�����v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	return 0;
}//int TextureAlphaFromBMP(const char* fileName, unsigned char* buffer)


void DrawTexture(vec2 const& pos, vec2 const& size, unsigned int texture, const GLubyte* color)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3ubv(color);
	//SetColorWithPosition(GetPosition());
	Rect rect(pos, size);
	rect.Draw();
}//void DrawTexture2D(vec2 const& pos,vec2 const& size,unsigned int texture)


void SetUpTexture(const char* fname, int texNo)
{
	int imageWidth, imageHeight;
	unsigned char* texImage;
	BITMAPFILEHEADER fHeader;
	BITMAPINFOHEADER iHeader;
	FILE* fp;
	unsigned char* line;
	int i, j, byteWidth;
	unsigned char* ps, * pd;

	glBindTexture(GL_TEXTURE_2D, gTexIDs[texNo]);

	fopen_s(&fp, fname, "rb");

	if (fp == NULL)
	{
		printf("No Image\n");
		return;
	}

	fread(&fHeader, sizeof(fHeader), 1, fp);
	fread(&iHeader, sizeof(iHeader), 1, fp);

	imageWidth = iHeader.biWidth;
	imageHeight = iHeader.biHeight;

	//�摜�f�[�^�̊i�[�̈���m��
	//Image��1�����z��Ƃ��Ďg�p�\(Image[i]�̂悤��)
	//�����z��Ƃ��Ă͈����Ȃ�
	texImage = (unsigned char*)malloc(imageWidth * imageHeight * 3);
	//�r�b�g�}�b�v�t�@�C���ł́A1���C���̃o�C�g����4�̔{���ɂȂ�悤�ɒ������Ă���
	//����Ȃ�����0��}�����Ă���
	//byteWidth��1���C���̃o�C�g��
	//RGB�摜(1�s�N�Z��������24�o�C�g�̏ꍇ)
	byteWidth = imageWidth * 3 + imageHeight % 4;
	line = (unsigned char*)malloc(byteWidth);//1���C�����̃f�[�^�̊i�[�̈���m��
	//�摜�f�[�^�̊i�[�A�h���X���Z�b�g
	//�ǂݍ��񂾉摜�f�[�^�����̃A�h���X��擪�ɏ��X�Ɋi�[
	pd = texImage;
	for (i = 0; i < imageHeight; i++)
	{

		//�i�[����ė��F�f�[�^��������1���C�����ǂݍ���
		fread(line, sizeof(unsigned char), byteWidth, fp);
		//�ǂݍ���1���C���̃f�[�^�̊i�[�̈�̃A�h���X���Z�b�g
		//���̃A�h���X�̐擪���珇�Ƀf�[�^��ǂݎ��摜�f�[�^�̊i�[�̈�ɃR�s�[
		ps = line;
		for (j = 0; j < imageWidth; j++)
		{
			ps = line + j * 3;
			*pd++ = *(ps + 2);//B
			*pd++ = *(ps + 1);//G
			*pd++ = *ps;//R
		}
	}

	free(line);
	fclose(fp);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//�g�厞�̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //�摜���g�債���Ƃ��̏���
		GL_LINEAR //�⊮�����Ȃ�
	);
	//�k�����̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //�摜���k�������Ƃ��̏���
		GL_LINEAR //�⊮�����Ȃ�
	);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, texImage);

	free(texImage);

}
//SetUpTexture(const char* fname, int texNo)

void SetTextureMode(unsigned char* pixcels)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixcels);
	//�g�厞�̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //�摜���g�債���Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);
	//�k�����̃t�B���^�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //�摜���g�債���Ƃ��̏���
		GL_NEAREST //�⊮�����Ȃ�
	);
	//�e�N�X�`���̓ǂݍ���
	glEnable(GL_TEXTURE_2D);
}// SetTextureMode(unsigned char* pixcels)
