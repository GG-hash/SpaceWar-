#pragma once

class Actor
{
public:
	//Actorを更新する関数
	virtual void Update() = 0;
	//Actorを描画する関数
	virtual void Draw() = 0;
};//class Actor