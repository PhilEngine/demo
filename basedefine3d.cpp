#include<memory.h>
#include<math.h>

#include"basedefine3d.h"

namespace My3D
{
	Vertex3f::Vertex3f()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vertex3f::Vertex3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vertex3f::Vertex3f(Vector3<float>&v)
	{
		memcpy(data, v.arr, SIZE_VECTOR3(float));
	}
	Vertex3f::Vertex3f(Vertex3f&v)
	{
		memcpy(data, v.data, sizeof(float) * 3);
	}
	Vertex3f::Vertex3f(float* arr)
	{
		memcpy(data, arr, sizeof(float) * 3);
	}
	Vertex3f::~Vertex3f()
	{

		if (data != nullptr)
		{
			delete[]data;
		}
		data = nullptr;
	}
	float* Vertex3f::getDataArray()
	{
		return data;
	}
	Normal* Vertex3f::operator-(Vertex3f&v)
	{
		return new Normal(v.x - x, v.y - y, v.z - z);
	}
	Vertex3f* Vertex3f::getNagtive()
	{
		return new Vertex3f(-x, -y, -z);
	}
	void Vertex3f::toNagtive()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	void Vertex3f::operator+=(Vertex3f&v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	void Vertex3f::operator-=(Vertex3f&v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	void Vertex3f::operator=(Vertex3f&v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	bool Vertex3f::operator==(Vertex3f&v)
	{
		if (fabsf(x - v.x) <= MINI_FLOAT &&
			fabsf(y - v.y) <= MINI_FLOAT &&
			fabsf(z - v.z) <= MINI_FLOAT)
			return true;
		return false;
	}

	Normal::Normal():Vertex3f(0.0f,0.0f,0.0f)
	{

	}
	Normal::Normal(float x, float y, float z) : Vertex3f(x, y, z)
	{

	}
	Normal::Normal(Vector3<float>&v) : Vertex3f(v)
	{

	}
	Normal::Normal(float*arr):Vertex3f(arr)
	{

	}
	Normal::Normal(Normal&v) : Vertex3f(v.getDataArray())
	{

	}
	float Normal::operator*(Normal&n)
	{
		return x * n.x + this->y*n.y + z * n.z;
	}
	Normal* Normal::operator*(Normal* n)
	{
		return new Normal(y*n->z-z*n->y,
			z*n->x-x*n->z,
			x*n->y-y*n->x);
	}
	float Normal::length()
	{
		return sqrtf(this->operator*(*this));
	}
	float Normal::cos(Normal&n)
	{
		return (n*(*this)) / (this->length()*n.length());
	}

	Normal* Normal::operator+(Normal&n)
	{
		return new Normal(n.x + x, n.y + y, n.z + z);
	}
	Normal* Normal::operator-(Normal&n)
	{
		return new Normal(x - n.x, y - n.y, z - n.z);
	}
	Normal* Normal::getNagtive()
	{
		return new Normal(-x, -y, -z);
	}
	void Normal::operator+=(Normal&n)
	{
		this->x += n.x;
		this->y += n.y;
		this->z += n.z;
	}
	void Normal::operator-=(Normal&n)
	{
		x -= n.x;
		y -= n.y;
		z -= n.z;
	}
	void Normal::operator=(Normal&n)
	{
		x = n.x;
		y = n.y;
		z = n.z;
	}
	bool Normal::operator==(Normal&v)
	{
		if (fabsf(x - v.x) <= MINI_FLOAT &&
			fabsf(y - v.y) <= MINI_FLOAT &&
			fabsf(z - v.z) <= MINI_FLOAT)
			return true;
		return false;
	}
	void Normal::toIdentity()
	{
		float len = this->operator*(*this);
		x /= len;
		y /= len;
		z /= len;
	}
	Normal* Normal::getIdentity()
	{
		float len = this->operator*(*this);
		return new Normal(x / len, y / len, z / len);
	}

}