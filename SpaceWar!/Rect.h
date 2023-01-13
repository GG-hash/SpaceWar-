#pragma once
#include"Actor.h"
#include"glut.h"
#include"glm/glm.hpp"
using namespace glm;


class  Rect : public Actor
{
private:
	vec2 _pos;
	vec2 _size;

public:
	Rect();
	Rect(vec2 const& _pos, vec2 const& _size);
	vec2& GetPosition();
	void SetPosition(vec2 const& pos) { _pos = pos; }
	vec2& GetSize();
	void SetSize(vec2 const& size) { _size = size; }
	void Update() override;
	void Draw() override;
	virtual bool IntersectRect(vec2 const& point);
	bool IntersectRect(Rect const& rect);
};