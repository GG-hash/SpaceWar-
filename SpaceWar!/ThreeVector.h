#pragma once
#include<cmath>
#define PI 3.14159265f

class ThreeVector
{
private:
	float x, y, z;
public:
	ThreeVector(float ex = 0, float why = 0, float zee = 0);
	~ThreeVector();
	float GetMagnitude()const;
	ThreeVector operator*(float num)const;
	friend ThreeVector operator*(float num, const ThreeVector& vec);
	ThreeVector operator+(const ThreeVector& vec)const;
	ThreeVector operator-(const ThreeVector& vec)const;
	void Normalize3DVector();
	float Dot3Dvector(const ThreeVector& vec)const;
	ThreeVector Cross3Dvector(const ThreeVector& vec)const;
	float AngleBetween3dvectors(const ThreeVector& vec) const;
};