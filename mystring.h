#pragma once
#include<vector>
#include"basedefine.h"
#ifdef MY_STEING
#error has been defined 'MY_STRING'
#endif
#define MY_STRING

#define DEFAULT_END_CHAR '\0'
#define NEW_STRING(strptr,len) strptr=new char[len+1];strptr[len]='\0';
#define DEFAULT_END_STRARR nullptr
#define DEFAULT_DIV_CHAR ' '
#define LINE_END_CHAR '\n'
#define CLONE_STRING(str) CloneStr(str)
#define NEW_STRING_ARRAY(arrptr,len) arrptr=new char*[len+1];arrptr[len]=nullptr;
#define DEFAULT_LEN_ADD 1024
#define DEFAULT_LEN_CONSTOR 1024

#define STRING_TYPE_NOT_NUMBER 0x0
#define STRING_TYPE_NAGETIVE 0x01
#define STRING_TYPE_INTEGER 0x02
#define STRING_TYPE_FLOAT 0x04

using namespace My3D;
namespace MyTool
{
	typedef char** StrArr; //the array of the string(char*)

	class MyString;
	class MyStringVector;

	/*
	fun:get the StrArr's length
	*/
	_uint StrArrLen(StrArr);
	/*
		delete all the arr which make by before
	*/
	void FreeStrArr(const StrArr arr);
	
	/*
		@autor mr.yi
		fun:clone a string from 'str'
		arg:
			str:a string
		return:
			the clone string
	*/
	char* CloneStr(const char*str);

	/*
		@atuor mr.yi
		fun:
			to compare two string is equal or not
		arg:
			str1: a compare string
			str2: a compare string
		return:
			if str1==str2 return true
			else return false
	*/
	bool StrEqual(const char* str1, const char* str2);

	/*
		@atuor mr.yi
		fun:
			to get the string length
		arg: 
			str: a string
		return:
			the str's length with default end char'\0'
	*/
	_uint StrLen(const char*str);

	/*
		@atuor mr.yi
		fun: to get the string length
		arg:
			str: a string that you want to get it's length
			endChar: a char to end with 'str'
		return:
			the str's length with the end char 'endChar'
	*/
	_uint StrLen(const char*str,char endChar);

	/*
		@autor mr.yi
		fun: get the destination string's position
		arg:
			sourcStr: the source of the string
			dastStr: the destination of the string
		return:
			the array place(begin with 0) that the dastStr in sourcStr,
			if can't find it,return arg is -1
	*/
	int FindStr(const char*sourcStr, const char*destStr);

	/*
		@autor mr.yi
		fun:fin the 'desStr' postion from 'sourceStr' ,begin with 'begin', end with 'end'
		arg:
			sourceStr:the source string
			destStr:the destion string
			bein: find begin with 'begin'
			end:find end with 'end'
		return:
			the 'destStr' postion
	*/
	int FindStr(_uint begin, _uint end, const char* sourceStr, const char* destStr);

	/*
		@autor mr.yi
		fun:to change some string with anthor string
		arg:
			sourceStr: the source string
			destStr: the destination string that it should find
			replaStr: the string  that you want to it is the target
		return:
			the new string
	*/
	char* ReplaceStr(const char* sourceStr,const char* destStr,const char* replaStr);

	/*
		@autor mr.yi
		fun:to cut the empty char
		arg:
			sourceStr:the source of the string
		return:
			the new string
	*/
	char* Trim(const char* sourceStr);

	/*
		@autor mr.yi
		fun:to get a string witch is from begin position to end position
		arg:
			sourceStr:ths source of the string
			begin:the cut begin position
			end:the end begin position
		return:
			a string form begin to end
	*/
	char* SubStr(const char* sourceStr, _uint begin, _uint end);

	/*
		fun:get the string number type 
	*/
	_byte GetStringNumberType(const char*str);

	/*
		fun:translate string to float,maybe cuse the data lose
	*/
	float Stof(const char*str);

	/*
		fun:translate string to in
	*/
	int Stoi(const char* str);

	/*
		fun:split the string witht the divchar,get a string array
	*/
	StrArr Split(const char* str, char divChar);

	StrArr GetStrArr(std::vector<char*>&arg);


	/*
		@autor mr.yi
		a class for the string ,just have some simple function
	*/
	class MyString
	{
	private:
		char* data;
		_uint length;
	public:
		MyString();
		MyString(const char*str);
		MyString(MyString&str);
		MyString(MyStringVector&str);
		virtual ~MyString();

		void operator=(const char*str);
		void operator=(MyString&str);
		void operator=(MyStringVector&str);

		bool operator==(MyStringVector&str);
		bool operator==(MyString&str);
		bool operator==(const char*str);

		char& operator[](_uint nb);

		/*
			return the char array's ptr
		*/
		char* C_Str();

		_uint Length();

		char* subStr(_uint begin, _uint end);
		int findStr(const char*str);
		int findStr(_uint begin, _uint end, const char*str);
		char* replaceStr(const char* destStr, const char* replaStr);
		char* trim();
		char* clone();
		StrArr split(char divChar);
	};

	
	/*
		@autor mr.yi
		fun: the plus for the class 'MyString',it can do some add memroy operator
	*/
	class MyStringVector
	{
	private:
		char* data;
		_uint strLen;// the length of string
		_uint memoryLen;//the length of the memory
		_uint addLen;//the length of the add once length while the memory can't save the add string
		_uint cnstorLen;//while the class constor ,it will make cnstorLen size memory
		/*
			//while you out the str,it while dived this string 
			like:
				MyStringVector vt("fuck the world");
				MyString str1;
				MyString str2;
				MyString str3;
				//if you set the divChar=' '
				vt>>str1>>str2>>str3;
				//the str1 =="fuck", str2=="the",str3=="world"
		*/
		char divChar;
	public:
		MyStringVector();
		MyStringVector(const char*str);
		MyStringVector(MyString&str);
		MyStringVector(MyStringVector&strv);
		MyStringVector(_uint addLen, _uint cnstorLen);
		virtual ~MyStringVector();

		MyStringVector& operator<<(const char*str);
		MyStringVector& operator<<(MyString&str);
		MyStringVector& operator<<(MyStringVector&strv);
		MyStringVector& operator<<(char ch);

		MyStringVector& operator>>(char*str);
		MyStringVector& operator>>(MyString&str);
		MyStringVector& operator>>(MyStringVector&strv);
		MyStringVector& operator>>(int &arg);
		MyStringVector& operator>>(float&arg);
		MyStringVector& operator>>(char &ch);

		bool operator==(MyString&str);
		bool operator==(const char*str);
		bool operator==(MyStringVector&strv);

		void operator=(const char*str);
		void operator=(MyString&str);
		void operator=(MyStringVector&str);

		char& operator[](_uint nb);

		void SetDivChar(char divChar);

		void Clear();

		char* C_Str();

		_uint Length();

		char* subStr(_uint begin, _uint end);
		int findStr(const char*str);
		int findStr(_uint begin, _uint end, const char*str);
		char* replaceStr(const char* destStr, const char* replaStr);
		char* trim();
		char* clone();
		StrArr split();

	};
	
}