#pragma once

class Actor
{
public:
	//Actor���X�V����֐�
	virtual void Update() = 0;
	//Actor��`�悷��֐�
	virtual void Draw() = 0;
};//class Actor