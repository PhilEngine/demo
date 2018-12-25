#pragma once

#ifdef BASE_DEFINE
#error hase been defined the 'BASE_DEFINE'
#endif // BASE_DEFINE

#ifndef BASE_DEFINE
#define BASE_DEFINE

#ifndef NULL
#define NULL 0
#endif // !NULL

#define SIZE_CHAR sizeof(char)
#define SIZE_INT sizeof(int)
#define SIZE_SHORT sizeof(short)
#define SIZE_LONG sizeof(long)
#define SIZE_FLOAT sizeof(float)
#define SIZE_DOUBLE sizeof(double)
// base data struct define
typedef unsigned char _byte8, _byte;
typedef unsigned short _byte16, _ushort;
typedef unsigned int _byte3, _uint;
typedef unsigned long _byte64, _ulong;

namespace MyTool
{
	typedef void* _anything;
}

namespace My3D
{

	// data struct define

	template<typename T> union Vector2
	{
		T arr[2];
		struct
		{
			T x;
			T y;
		};
	};

	template<typename T>union Vector3
	{
		T arr[3];
		struct
		{
			T x;
			T y;
			T z;
		};
		struct
		{
			T r;
			T g;
			T b;
		};
	};

	template<typename T>union Vector4
	{
		T arr[4];
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		struct
		{
			T r;
			T g;
			T b;
			T a;
		};
	};

#define SIZE_VECTOR2(T) sizeof(Vector2<T>)
#define SIZE_VECTOR3(T) sizeof(Vector3<T>)
#define SIZE_VECTOR4(T) sizeof(Vector4<T>)
}

#endif // !BASE_DEFINE
