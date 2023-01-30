#pragma once
#define PI 3.14159265f
#include<cmath>


struct TwoDvector_comp
{
	float x, y;
};//struct TwoDvector_comp


struct TwoDvector_polar
{
	float mag, dir;
};//struct TwoDvector_polar

class TwoVector
{
private:
	float x, y;
public:
	TwoVector(float ex = 0, float why = 0);
	~TwoVector();
	TwoVector operator*(float num)const;
	friend TwoVector operator*(float num, const TwoVector& vec);
	TwoVector operator+(const TwoVector& vec)const;
	TwoVector operator-(const TwoVector& vec)const;
	TwoDvector_comp TwoDvector_comp_PolarToCompConversion(TwoDvector_polar vec);
	TwoDvector_polar TwoDvector_polar_CompToPolarConversion(TwoDvector_comp vec);
};//class TwoVector