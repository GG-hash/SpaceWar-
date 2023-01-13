#include"Rect.h"

Rect::Rect() :_pos(vec2(0, 0))
, _size(vec2(0, 0))
{

}

Rect::Rect(vec2 const& pos, vec2 const& size) :_pos(pos)
, _size(size)
{

}

vec2& Rect::GetPosition()
{
	return _pos;
}

vec2& Rect::GetSize()
{
	return _size;
}

void Rect::Update()
{

}//Rect::Update()

void Rect::Draw()
{
	glBegin(GL_QUADS);
	{
		//テクスチャ座標の設定
		glTexCoord2f(0, 0);
		glVertex2fv((GLfloat*)&_pos);//const GLfloat *v;
		vec2 leftBottom = _pos + vec2(0, _size.y);

		//テクスチャ座標の設定
		glTexCoord2f(0, 1);
		glVertex2fv((GLfloat*)&leftBottom);//const GLfloat *v;
		vec2 rightDownBottom = (_pos + _size);

		//テクスチャ座標の設定
		glTexCoord2f(1, 1);
		glVertex2fv((GLfloat*)&rightDownBottom);           //const GLfloat *v;

		//テクスチャ座標の設定
		glTexCoord2f(1, 0);
		vec2 rightup = _pos + vec2(_size.x, 0);
		glVertex2fv((GLfloat*)&rightup); //const GLfloat *v;
	}
	glEnd();

}//Rect::Draw()

//四角形と点の当たり判定
bool Rect::IntersectRect(vec2 const& _point)
{
	if ((_point.x >= _pos.x) && (_point.x <= _pos.x + _size.x)
		&& (_point.y >= _pos.y) && (_point.y <= _pos.y + _size.y))
	{
		return true;
	}
	return false;
}//Rect::IntersectRect(vec2 const& _point)


//四角形同士の当たり判定
bool Rect::IntersectRect(Rect const& rect)
{
	if (
		(_pos.x + _size.x >= rect._pos.x) &&        //四角形の左端
		(_pos.x < rect._pos.x + rect._size.x) &&	//四角形の右端
		(_pos.y + _size.y >= rect._pos.y) &&		//四角形の下
		(_pos.y < rect._pos.y + rect._size.y)		//四角形の上
		)
	{
		return true;
	}

	return false;
}//Rect::IntersectRect(Rect const& rect)

