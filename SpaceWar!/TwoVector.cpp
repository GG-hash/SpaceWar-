#include "TwoVector.h"


TwoVector::TwoVector(float ex, float why)
{
	x = ex; y = why;
}//TwoVector::TwoVector(float ex, float why)

TwoVector::~TwoVector()
{
}//TwoVector::~TwoVector()

TwoVector TwoVector::operator*(float num) const
{
	return TwoVector(num * x, num * y);
}//TwoVector TwoVector::operator*(float num) const

TwoVector operator*(float num, const TwoVector& vec)
{
	return TwoVector(num * vec.x, num * vec.y);
}//TwoVector operator*(float num, const TwoVector& vec)


TwoVector TwoVector::operator+(const TwoVector& vec) const
{
	return TwoVector(x + vec.x, y + vec.y);
}//TwoVector TwoVector::operator+(const TwoVector& vec) const

TwoVector TwoVector::operator-(const TwoVector& vec) const
{
	return TwoVector(x - vec.x, y - vec.y);
}//TwoVector TwoVector::operator-(const TwoVector& vec) const

TwoDvector_comp TwoVector::TwoDvector_comp_PolarToCompConversion(TwoDvector_polar vec)
{
	TwoDvector_comp tmp = { 0,0 };

	tmp.x = vec.mag * cos(vec.dir * PI / 180.0f);
	tmp.y = vec.mag * sin(vec.dir * PI / 180.0f);

	return tmp;
}//TwoDvector_comp TwoVector::TwoDvector_comp_PolarToCompConversion(TwoDvector_polar vec)

TwoDvector_polar TwoVector::TwoDvector_polar_CompToPolarConversion(TwoDvector_comp vec)
{
	TwoDvector_polar tmp = { 0.0f,0.0f };

	tmp.mag = sqrt(vec.x * vec.x + vec.y * vec.y);

	// To prohibit divided by 0 
	if (tmp.mag == 0.0f)
		return tmp;
	//To ask degree
	tmp.dir = (180.0f / PI) * asin(vec.y / tmp.mag);

	// íºåç¿ïWÇãÅÇﬂÇÈ

	// vec.x Ç™ 0 ÇÊÇËÇ‡è¨Ç≥Ç¢èÍçáÅC180 ìxÇà¯Ç≠
	if (vec.x < 0.0f)
		tmp.dir = 180.0f - tmp.dir;


	else if (vec.x > 0.0f && vec.y < 0.0f)
		tmp.dir += 360.0f;

	return tmp;
}//TwoDvector_polar TwoVector::TwoDvector_polar_CompToPolarConversion(TwoDvector_comp vec)

