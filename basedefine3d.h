#pragma once
#include"basedefine.h"
#ifndef BASE_DEFINE_3D
#define BASE_DEFINE_3D
#else 
#error has been defined 'BASE_DEFINE_3D'
#endif // !BASE_DEFINE_3D

namespace My3D
{
	class Vertex3f;
	class Normal;
	//空间点
	class Vertex3f
	{
	private:
		float *data=new float[3];
	public:
		float &x = data[0];
		float &y = data[1];
		float &z = data[2];

		Vertex3f();
		Vertex3f(float x,float y,float z);
		Vertex3f(Vector3<float>&v);
		Vertex3f(float *arr);
		Vertex3f(Vertex3f&v);

		virtual~Vertex3f();
		float* getDataArray();

		Normal* operator-(Vertex3f&v);
		void operator+=(Vertex3f&v);
		void operator-=(Vertex3f&v);
		void operator=(Vertex3f&v);
		bool operator==(Vertex3f&v);
		
		
		Vertex3f* getNagtive();
		void toNagtive();


	};
	//空间矢量
	class Normal:public Vertex3f
	{

	public:
		Normal();
		Normal(float x, float y, float z);
		Normal(Vector3<float>&v);
		Normal(float *arr);
		Normal(Normal&nor);

		~Normal() { };
		//点乘
		float operator*(Normal&nor);
		//叉乘
		Normal* operator*(Normal* n);

		Normal* operator+(Normal&v);
		Normal* operator-(Normal&v);
		void operator+=(Normal&v);
		void operator-=(Normal&v);
		void operator=(Normal&n);
		bool operator==(Normal&n);
		Normal* getNagtive();
		void toIdentity();
		Normal* getIdentity();

		float length();
		float cos(Normal&n);
	};

	//坐标轴 单位方向向量
	const static Normal identityNormalX(1.0f,0.0f,0.0f);
	const static Normal identityNormalXNag(-1.0f, 0.0f, 0.0f);
	const static Normal identityNormalY(0.0f, 1.0f, 0.0f);
	const static Normal identityNormalYNag(0.0f, -1.0f, 0.0f);
	const static Normal identityNormalZ(0.0f, 0.0f, 1.0f);
	const static Normal identityNormalZNag(0.0f, 0.0f, -1.0f);
	//opengl 坐标系 右手坐标 单位方向向量
	const static Normal& glUpNormal = identityNormalY;
	const static Normal& glDownNormal = identityNormalYNag;
	const static Normal& glFrontNoraml = identityNormalZNag;
	const static Normal& glBackNormal = identityNormalZ;
	const static Normal& glLeftNormal = identityNormalXNag;
	const static Normal& glRightNormal = identityNormalX;
	//directx 坐标系 左手坐标 单位方向向量
	const static Normal& dirUpNormal = identityNormalY;
	const static Normal& dirDownNormal = identityNormalYNag;
	const static Normal& dirLeftNormal = identityNormalXNag;
	const static Normal& dirRightNormal = identityNormalX;
	const static Normal& dirBackNoraml = identityNormalZNag;
	const static Normal& dirFrontNormal = identityNormalZ;
}

