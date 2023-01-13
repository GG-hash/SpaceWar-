#include"Texture.h"
#include "Rect.h"

//テクスチャのIDを格納する配列
#define MAX_TEX 100
unsigned int gTexIDs[MAX_TEX];


int TextureFromBMP(const char* fileName, unsigned char* colorKey)
{
	FILE* file;

	//ファイルを開く
	fopen_s(&file, fileName, "rb");
	//ファイルがなかった場合
	if (file == nullptr)
	{
		printf("%s open failed !\n", fileName);
		return -1;
	}
	printf("%s has been successfully loaded.\n", fileName);

	//ヘッダーのデータを格納する
	BITMAPFILEHEADER bitFile;
	fread(&bitFile, sizeof BITMAPFILEHEADER, 1, file);
	//画像サイズの表示
	//printf("BITMAPFILEHEADER : %d\n", bitFile.bfSize);

	BITMAPINFOHEADER bitInfo;
	fread(&bitInfo, sizeof BITMAPINFOHEADER, 1, file);
	printf("bitInfo Width : %d bitInfo Height : %d\n", bitInfo.biWidth, bitInfo.biHeight);
	//1pixleあたり何ビットか
	printf("BitCount : %d\n", bitInfo.biBitCount);


	//ピクセルデータの読み込み
	typedef struct
	{
		//RGBAの定義
		unsigned char r, g, b, a;
	}RGBA;

	//ピクセルの作成　メモリの確保
	RGBA* pixels = (RGBA*)malloc(sizeof(RGBA) * bitInfo.biWidth * bitInfo.biHeight);
	if (pixels == nullptr)
	{
		return -1;
	}
	printf("OK\n");
	//パディング:
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


	//BMPファイルはRGBAでなくBGRで保存されている為、RGBAに修正する
	for (int y = 0; y < bitInfo.biHeight; y++)
	{
		for (int x = 0; x < bitInfo.biWidth; x++)
		{
			//修正するピクセルのアドレス
			RGBA* pPixel = &pixels[y * bitInfo.biWidth + x];
			unsigned char tmp = pPixel->r;
			pPixel->r = pPixel->b;
			pPixel->b = tmp;
		}
	}

	//画像の上下反転を修正する 画像の中心より上の画像と下の画像を入れ替えることで修正する
	for (int y = 0; y < bitInfo.biHeight / 2; y++)
	{
		for (int x = 0; x < bitInfo.biWidth; x++)
		{
			//修正するピクセルのアドレス
			//上のピクセル
			RGBA* modPixUp = &pixels[y * bitInfo.biWidth + x];
			//下のピクセル
			RGBA* modPixDown = &pixels[(bitInfo.biHeight - 1 - y) * bitInfo.biWidth + x];

			RGBA tmp = *modPixUp;
			*modPixUp = *modPixDown;
			*modPixDown = tmp;

		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitInfo.biWidth, bitInfo.biHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	//拡大時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //画像を拡大したときの処理
		GL_NEAREST //補完をしない
	);
	//縮小時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //画像を縮小したときの処理
		GL_NEAREST //補完をしない
	);

	//クランプの設定　画像の一番下のデータが画像の一番上のデータを参照しないようにする
	//横のクランプ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//縦のクランプ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	//データの開放
	free(pixels);
	//ファイルを閉じる
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

	//ファイルを開く
	fopen_s(&file, fileName, "rb");
	//ファイルがなかった場合
	if (file == nullptr)
	{
		printf("%s open failed !\n", fileName);
		return;
	}
	printf("%s has been successfully loaded.\n", fileName);

	fread(&tex[texNo].bf, sizeof BITMAPFILEHEADER, 1, file);
	fread(&tex[texNo].bi, sizeof BITMAPINFOHEADER, 1, file);

	printf("bitInfo Width : %d bitInfo Height : %d\n", tex[texNo].bi.biWidth, tex[texNo].bi.biHeight);
	//1pixleあたり何ビットか
	printf("BitCount : %d\n", tex[texNo].bi.biBitCount);

	typedef struct
	{
		unsigned char b, g, r;
	}BGR;

	BGR* bits = (BGR*)malloc(sizeof(BGR) * tex[texNo].bi.biWidth * tex[texNo].bi.biHeight);
	fread(bits, sizeof(BGR), tex[texNo].bi.biWidth * tex[texNo].bi.biHeight, file);

	//ピクセルデータの読み込み
	typedef struct
	{
		//RGBAの定義
		unsigned char r, g, b, a;
	}RGBA;

	//ピクセルの作成　メモリの確保
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
		//カラーキーが一致したら透明にする
		/*pixels[i].a = ((colorKey != nullptr) &&
			(pixels[i].r == colorKey[0]) &&
			(pixels[i].g == colorKey[1]) &&
			(pixels[i].b == colorKey[2])) ? 0x00 : 0xff;*/
			//pixels[i].a = (bits[i].r == 0x00 && bits[i].g == 0xff && bits[i].b == 0x00)? 0x00 : 0xff;
	}

	glGenTextures(1, &tex[texNo].texture);
	glBindTexture(GL_TEXTURE_2D, tex[texNo].texture);


	//拡大時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //画像を拡大したときの処理
		GL_NEAREST //補完をしない
	);
	//縮小時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //画像を縮小したときの処理
		GL_NEAREST //補完をしない
	);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex[texNo].bi.biWidth, tex[texNo].bi.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	free(bits);
	free(pixels);
	fclose(file);
}

int TextureAlphaFromBMP(const char* fileName, unsigned char* buffer)
{
	FILE* file;

	//ファイルを開く
	fopen_s(&file, fileName, "rb");
	//ファイルがなかった場合
	if (file == nullptr)
	{
		printf("%s open failed !\n", fileName);
		return -1;
	}
	printf("%s has been successfully loaded.\n", fileName);

	//ヘッダーのデータを格納する
	BITMAPFILEHEADER bitFile;
	fread(&bitFile, sizeof BITMAPFILEHEADER, 1, file);
	//画像サイズの表示
	//printf("BITMAPFILEHEADER : %d\n", bitFile.bfSize);

	BITMAPINFOHEADER bitInfo;
	fread(&bitInfo, sizeof BITMAPINFOHEADER, 1, file);
	printf("bitInfo Width : %d bitInfo Height : %d\n", bitInfo.biWidth, bitInfo.biHeight);
	//1pixleあたり何ビットか
	printf("BitCount : %d\n", bitInfo.biBitCount);

	//パディング:
	int padding = (4 - bitInfo.biWidth * (bitInfo.biBitCount / 8) % 4) % 4;

	for (int i = 0; i < bitInfo.biHeight; i++)
	{
		for (int j = 0; j < bitInfo.biWidth; j++)
		{
			fread(&buffer[i * bitInfo.biWidth + j], 1, 1, file);
			//2バイト読み飛ばす
			fseek(file, 2, SEEK_CUR);
		}
		//パディング
		fseek(file, padding, SEEK_CUR);
	}

	//画像の上下反転を修正する 画像の中心より上の画像と下の画像を入れ替えることで修正する
	for (int y = 0; y < bitInfo.biHeight / 2; y++)
	{
		for (int x = 0; x < bitInfo.biWidth; x++)
		{
			//修正するピクセルのアドレス
			//上のピクセル
			unsigned char* modPixUp = &buffer[y * bitInfo.biWidth + x];
			//下のピクセル
			unsigned char* modPixDown = &buffer[(bitInfo.biHeight - 1 - y) * bitInfo.biWidth + x];

			unsigned char tmp = *modPixUp;
			*modPixUp = *modPixDown;
			*modPixDown = tmp;

		}//for (int x = 0; x < bitInfo.biWidth; x++)
	}//for (int y = 0; y < bitInfo.biHeight / 2; y++)

	//ピクセルのアライメント調整
	//メモリのサイズを1単位にする デフォルトは4単位
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//転送
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, bitInfo.biWidth, bitInfo.biHeight,
		0, GL_ALPHA, GL_UNSIGNED_BYTE, buffer);*/

		//拡大時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //画像を拡大したときの処理
		GL_NEAREST //補完をしない
	);
	//縮小時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //画像を縮小したときの処理
		GL_NEAREST //補完をしない
	);

	//クランプの設定　画像の一番下のデータが画像の一番上のデータを参照しないようにする
	//横のクランプ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//縦のクランプ
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

	//画像データの格納領域を確保
	//Imageは1次元配列として使用可能(Image[i]のように)
	//多元配列としては扱えない
	texImage = (unsigned char*)malloc(imageWidth * imageHeight * 3);
	//ビットマップファイルでは、1ラインのバイト数が4の倍数になるように調整している
	//足りない分は0を挿入してある
	//byteWidthが1ラインのバイト数
	//RGB画像(1ピクセル当たり24バイトの場合)
	byteWidth = imageWidth * 3 + imageHeight % 4;
	line = (unsigned char*)malloc(byteWidth);//1ライン分のデータの格納領域を確保
	//画像データの格納アドレスをセット
	//読み込んだ画像データをこのアドレスを先頭に順々に格納
	pd = texImage;
	for (i = 0; i < imageHeight; i++)
	{

		//格納されて理宇データを下から1ラインずつ読み込む
		fread(line, sizeof(unsigned char), byteWidth, fp);
		//読み込んだ1ラインのデータの格納領域のアドレスをセット
		//このアドレスの先頭から順にデータを読み取り画像データの格納領域にコピー
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
	//拡大時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //画像を拡大したときの処理
		GL_LINEAR //補完をしない
	);
	//縮小時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //画像を縮小したときの処理
		GL_LINEAR //補完をしない
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
	//拡大時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, //画像を拡大したときの処理
		GL_NEAREST //補完をしない
	);
	//縮小時のフィルタの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, //画像を拡大したときの処理
		GL_NEAREST //補完をしない
	);
	//テクスチャの読み込み
	glEnable(GL_TEXTURE_2D);
}// SetTextureMode(unsigned char* pixcels)
