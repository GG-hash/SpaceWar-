#include"ThreeVector.h"


ThreeVector::ThreeVector(float ex, float why, float zee)
{
	x = ex; y = why; z = zee;
}//ThreeVector::ThreeVector(float ex, float why, float zee)


ThreeVector::~ThreeVector() {}

float ThreeVector::GetMagnitude()const
{
	return sqrt(x * x + y * y + z * z);
}//float ThreeVector::GetMagnitude()const


ThreeVector ThreeVector::operator*(float num) const
{
	return ThreeVector(num * x, num * y, num * z);
}//ThreeVector ThreeVector::operator*(float num) const


ThreeVector  ThreeVector::operator+(const ThreeVector& vec)const
{
	return ThreeVector(x + vec.x, y + vec.y, z + vec.z);
}//ThreeVector  ThreeVector::operator+(const ThreeVector& vec)const


ThreeVector  ThreeVector::operator-(const ThreeVector& vec)const
{
	return ThreeVector(x - vec.x, y - vec.y, z - vec.z);
}//ThreeVector  ThreeVector::operator-(const ThreeVector& vec)const


void  ThreeVector::Normalize3DVector(void)
{
	float SQRT = sqrt(x * x + y * y + z * z);
	x /= SQRT; y /= SQRT; z /= SQRT;
}//void  ThreeVector::Normalize3DVector(void)


float  ThreeVector::Dot3Dvector(const ThreeVector& vec)const
{
	return x * vec.x + y * vec.y + z * vec.z;
}//float  ThreeVector::Dot3Dvector(const ThreeVector& vec)const


ThreeVector  ThreeVector::Cross3Dvector(const ThreeVector& vec)const
{
	return ThreeVector(y * vec.z - z * vec.y,
		z * vec.x - x * vec.z,
		x * vec.y - y * vec.x);
}//ThreeVector  ThreeVector::Cross3Dvector(const ThreeVector& vec)const


ThreeVector operator*(float num, const ThreeVector& vec)
{
	return ThreeVector(num * vec.x, num * vec.y, num * vec.z);
}//ThreeVector operator*(float num, const ThreeVector& vec)


float ThreeVector::AngleBetween3dvectors(const ThreeVector& vec) const
{
	return (acos(Dot3Dvector(vec) / (GetMagnitude() * vec.GetMagnitude()))) * (180.0f / PI);
}//float ThreeVector::AngleBetween3dvectors(const ThreeVector& vec) const
