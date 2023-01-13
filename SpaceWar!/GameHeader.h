#pragma once
#define SCREEN_WIDTH  (320 * 2)
#define SCREEN_HEIGHT (240 * 2)
#include"Math.h"
#include"Font.h"
#include"Ship.h"
#include"Explosion.h"
#include"Game.h"
#include"MainBackGround.h"
#include"Sun.h"


//キーボードの入力を保存するする配列
extern bool gKeys[256];
//1フレーム前の入力
extern bool gLastKeys[256];
//押されたキーの入力
extern bool gDownKeys[256];