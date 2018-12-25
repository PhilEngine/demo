#include<memory.h>
#include<math.h>
#include"mystring.h"

using std::vector;
using namespace My3D;

namespace MyTool
{
	_uint StrArrLen(StrArr arr)
	{
		if (arr == nullptr)
		{
			return 0;
		}
		_uint result = 0;


			while (arr[result] != DEFAULT_END_STRARR)
			{
				result++;
			}



		return result;
	}

	char * CloneStr(const char * str)
	{
		_uint len = StrLen(str);
		char *result = new char[len + 1];
		result[len] = DEFAULT_END_CHAR;
		memcpy(result, str, len*SIZE_CHAR);
		return result;
	}
	
	bool StrEqual(const char*str1, const char*str2)
	{
		_uint len1 = StrLen(str1);
		_uint len2 = StrLen(str2);

		if (len1 != len2)
		{
			return false;
		}

		for (_uint i = 0; i < len1; i++)
		{
			if (str1[i] != str2[i])
			{
				return false;
			}
		}

		return true;

	}

	_uint StrLen(const char*str)
	{
		if (str == nullptr)
		{
			return 0;
		}
		_uint result = 0;
		while (str[result] != DEFAULT_END_CHAR)
		{
			result++;
		}

		return result;
	}

	_uint StrLen(const char*str,char endChar)
	{
		if (str == nullptr)
		{
			return 0;
		}
		_uint result = 0;
		while (str[result] != endChar)
		{
			result++;
		}

		return result;
	}

	int FindStr(const char*sourcStr, const char*destStr)
	{
		_uint lenS = StrLen(sourcStr);
		_uint lenD = StrLen(destStr);

		if (lenS == 0 || lenD == 0)
		{
			return -1;
		}
		// just simple to do it,maybe cost more time
		_uint result;
		bool findFlag = false;
		for (_uint i = 0; i < lenS; i++)
		{
			findFlag = true;
			result = i;
			for (_uint j = 0; j < lenD&&i+j<lenS; j++)
			{
				if (sourcStr[i + j] != destStr[j])
				{
					findFlag = false;
					break;
				}
			}
			if (findFlag)
			{
				break;
			}

		}
		if (findFlag)
		{
			return result;
		}
		return -1;
	}

	int FindStr(_uint begin, _uint end, const char* sourcStr, const char* destStr)
	{
		_uint lenS = StrLen(sourcStr);
		_uint lenD = StrLen(destStr);

		if (lenS == 0 || lenD == 0)
		{
			return -1;
		}
		if (begin >= lenS || begin > end)
		{
			return -1;
		}

		end = end >= lenS ? lenS - 1 : end;

		// just simple to do it,maybe cost more time
		_uint result;
		bool findFlag = false;
		for (_uint i = begin; i <= end; i++)
		{
			findFlag = true;
			result = i;
			for (_uint j = 0; j < lenD&&i + j <= end; j++)
			{
				if (sourcStr[i + j] != destStr[j])
				{
					findFlag = false;
					break;
				}
			}
			if (findFlag)
			{
				break;
			}

		}
		if (findFlag)
		{
			return result;
		}
		return -1;
	}

	char * ReplaceStr(const char * sourceStr, const char * destStr, const char * replaStr)
	{
		_uint lenS = StrLen(sourceStr);
		_uint lenD = StrLen(destStr);
		_uint lenR = StrLen(replaStr);

		vector<char*> strList;
		vector<_uint> lenList;

		char *result = nullptr;
		//find the destStr position,copy not desStr string to a new array,copy the replaStr to the destStr postion
		int pos = 0;
		_uint pre = 0;
		_uint flag = 0;
		while (true)
		{
			pos = FindStr(pos, lenS, sourceStr, destStr);
			if (pos == -1)
			{
				if (flag != 0)
				{
					char *temp;
					NEW_STRING(temp, lenS-pre);
					memcpy(temp, sourceStr + pre, SIZE_CHAR*(lenS - pre));
					strList.push_back(temp);
					lenList.push_back(lenS - pre);
				}
				break;
			}
			else
			{
				flag++;
				_uint len = pos - pre;
				char *temp = new char[len+ 1];
				temp[len] = '\0';
				memcpy(temp, sourceStr + pre, SIZE_CHAR*len);
				strList.push_back(temp);
				lenList.push_back(len);
				strList.push_back(CloneStr(replaStr));
				lenList.push_back(lenR);
				pos = pos + lenD;
				pre = pos;
			}

		}
		if (flag!=0)
		{
			_uint len = 0;
			vector<_uint>::iterator it = lenList.begin();
			while (it != lenList.end())
			{
				len += *it++;
			}
			NEW_STRING(result,len);
			vector<char*>::iterator that = strList.begin();
			_uint temp = 0;
			_uint templen = 0;
			while (that != strList.end())
			{
				char* str = *that;
				*that = nullptr;
				*that++;
				templen = StrLen(str);
				memcpy(result + temp, str, templen*SIZE_CHAR);
				temp += templen;
				delete[]str;
			}
		}
		else
		{
			result = CloneStr(sourceStr);
		}
		return result;
	}

	char * Trim(const char * sourceStr)
	{
		char* result = nullptr;
		_uint end = StrLen(sourceStr);
		if (end == 0)
		{
			return result;
		}
		end--;
		_uint start = 0;
		while (sourceStr[start] == ' ' || sourceStr[start]=='\n'||sourceStr[start]=='\r' || sourceStr[start] == '\t')
		{
			start++;
		}
		while (sourceStr[end] == ' ' || sourceStr[end] == '\n' ||sourceStr[start]=='\r' || sourceStr[start] == '\t')
		{
			end--;
		}
		_uint len = end-start+1;
		if (len > 0)
		{
			NEW_STRING(result, len);
			memcpy(result, sourceStr+start, SIZE_CHAR*len);
		}
		return result;
	}

	char * SubStr(const char * sourceStr, _uint begin, _uint end)
	{
		char* result = nullptr;
		_uint len = StrLen(sourceStr);
		if (!len)
		{
			return nullptr;
		}
		if (begin >= len || begin > end || end >= len)
		{
			return nullptr;
		}
		
		_uint lenR = end - begin+1;
		NEW_STRING(result, lenR);
		memcpy(result, sourceStr + begin, lenR*SIZE_CHAR);

		return result;
	}

	_byte GetStringNumberType(const char*str)
	{
		_uint len = StrLen(str);
		if (!len)
		{
			return STRING_TYPE_NOT_NUMBER;
		}

		int pointFlag = 0;
		bool startZeroFlag = str[0] == '0' ? true : false;//signed to the '0'
		bool nagFlag = str[0] == '-' ? true : false;//signed to the '-'
		if (nagFlag&&len>3)
		{
			startZeroFlag = str[1] == '0' ? true : false;
		}
		
		for (_uint i = nagFlag ? 1 : 0; i < len; i++)
		{
			if (str[i] == '.')
			{
				pointFlag++;
			}
			else if (str[i] >= '0'&&str[i] <= '9')
			{
				continue;
			}
			else
			{
				return STRING_TYPE_NOT_NUMBER;
			}
		}

		if (pointFlag == 1)
		{
			if (nagFlag)
			{
				if (len < 4)
				{
					return STRING_TYPE_NOT_NUMBER;
				}
				else if (startZeroFlag&&str[2] != '.')
				{
					return STRING_TYPE_NOT_NUMBER;
				}
				else if (str[len - 1] == '.'||str[1]=='.')
				{
					return STRING_TYPE_NOT_NUMBER;
				}
				return STRING_TYPE_FLOAT|STRING_TYPE_NAGETIVE;
			}
			else
			{
				if (len < 3)
				{
					return STRING_TYPE_NOT_NUMBER;
				}
				else if (startZeroFlag&&str[1] != '.')
				{
					return STRING_TYPE_NOT_NUMBER;
				}
				else if (str[len - 1] == '.'||str[0]=='.')
				{
					return STRING_TYPE_NOT_NUMBER;
				}
				return STRING_TYPE_FLOAT;
			}
		}
		else if (pointFlag == 0)
		{
			if (startZeroFlag)
			{
				return STRING_TYPE_NOT_NUMBER;
			}
			else if (nagFlag)
			{
				return STRING_TYPE_INTEGER | STRING_TYPE_NAGETIVE;
			}
			else
			{
				return STRING_TYPE_INTEGER;
			}		
		}
		else
		{
			return STRING_TYPE_NOT_NUMBER;
		}
	}

	float Stof(const char*str)
	{
		float result = 0.0f;
		_byte tp = GetStringNumberType(str);
		bool nagFlag = tp & STRING_TYPE_NAGETIVE;
		if (tp&STRING_TYPE_FLOAT)
		{
			_uint i=0;
			_uint point = 0;
			_uint tempi = 0;
			float tempf = 0.0f;
			if (nagFlag)
			{
				i = 1;
				point = 1;
			}
			while (str[point] != '.')
			{

				point++;
			}
			_uint leni = point - i;
			for (int j = leni - 1,k=i; j >= 0; j--,k++)
			{
				tempi += powl(10, j)*(str[k]-'0');
			}
			for (int j = point + 1,k=1; j < StrLen(str); j++,k++)
			{
				tempf += powf(10, -k)*(str[j]-'0');
			}
			result = nagFlag ? -(tempi + tempf) : tempi + tempf;

		}
		return result;
	}

	int Stoi(const char* str)
	{
		int result = 0;
		_byte tp = GetStringNumberType(str);
		bool nagFlag = tp & STRING_TYPE_NAGETIVE;
		_uint len = nagFlag ? StrLen(str) - 1 : StrLen(str);
		int i = nagFlag ? 1 : 0;
		for (int j = i, k = len-1; k >= 0; j++, k--)
		{
			result += powl(10, k)*(str[j] - '0');
		}

		result = nagFlag ? -result : result;

		return result;
	}

	void FreeStrArr(const StrArr arr)
	{
		_uint i = 0;
		while (arr[i] != nullptr)
		{

				delete[]arr[i];
				arr[i] = nullptr;
				i++;

		}
		delete[] arr;
	}

	StrArr Split(const char* str, char divChar)
	{
		StrArr result = nullptr;
		_uint pre = 0;
		int addr = 0;
		_uint findFlag = false;
		char *ds;
		NEW_STRING(ds,1);
		ds[0] = divChar;
		_uint len = StrLen(str);

		vector<char*> strList;
		vector<_uint> lenList;

		while (true)
		{
			addr = FindStr(addr, len - 1, str, ds);
			if (addr == -1)
			{
				//last one
				if (findFlag)
				{
					
					while (str[pre] == divChar)
					{
						pre++;
						if (pre == len)
						{
							break;
						}
					}

					_uint tempLen = len - pre;
					if (tempLen != 0)
					{
						char* temp;
						NEW_STRING(temp, tempLen);
						memcpy(temp, str + pre, SIZE_CHAR*tempLen);
						strList.push_back(temp);
						lenList.push_back(tempLen);
					}
				}
				else
				{
					char* tp = CloneStr(str);
					strList.push_back(tp);
					lenList.push_back(len);
				}
				break;
			}
			else
			{
				findFlag++;
				if (str[pre] == divChar)
				{
					while (str[pre] == divChar)
					{
						if (pre == len)
						{
							break;
						}
						pre++;
					}
					addr = pre;
					continue;
				}
				else
				{
					_uint tempLen = addr - pre;
					if (tempLen != 0)
					{
						char* temp;
						NEW_STRING(temp, tempLen);
						memcpy(temp, str + pre, SIZE_CHAR*tempLen);
						strList.push_back(temp);
						lenList.push_back(tempLen);
					}
					pre = ++addr;
				}
			}
		}

		_uint relen=lenList.size();

		NEW_STRING_ARRAY(result, relen);

		_uint i = 0;
		for (vector<char*>::iterator it=strList.begin();it!=strList.end();i++)
		{
			char * temp = *it++;
			result[i] = CloneStr(temp);
			delete[]temp;
		}
		delete[]ds;
		ds = nullptr;
		return result;
	}




	MyString::MyString()
	{
		data = new char[sizeof(char)];
		data[0] = DEFAULT_END_CHAR;
		this->length = 0;
	}

	MyString::MyString(const char*str)
	{
		this->length = StrLen(str);
		data = new char[length + SIZE_CHAR];
		data[length]= DEFAULT_END_CHAR;
		memcpy(data, str, SIZE_CHAR*length);
	}
	
	MyString::MyString(MyString&str)
	{
		this->length = str.length;
		data = new char[length + SIZE_CHAR];
	}

	MyString::~MyString()
	{
		if (data != nullptr)
		{
			delete[]data;
		}
		this->length = 0;
	}

	MyString::MyString(MyStringVector&strv)
	{
		this->data = CloneStr(strv.C_Str());
		this->length = StrLen(data);
	}

	void MyString::operator=(MyStringVector&strv)
	{
		if (data != nullptr)
		{
			delete[]data;
		}
		data = CloneStr(strv.C_Str());
		this->length = StrLen(data);
	}

	char* MyString::C_Str()
	{
		return data;
	}

	bool MyString::operator==(const char*str)
	{
		return StrEqual(data, str);
	}

	bool MyString::operator==(MyString&str)
	{
		return StrEqual(data, str.data);

	}

	bool MyString::operator==(MyStringVector&strv)
	{
		return StrEqual(this->data, strv.C_Str());
	}

	void MyString::operator=(const char* str)
	{
		this->length = StrLen(str);
		if (data != nullptr)
		{
			delete[]data;
			data = new char[length + SIZE_CHAR];
		}
		data[length] = DEFAULT_END_CHAR;
		memcpy(data, str, SIZE_CHAR*length);
	}

	void MyString::operator=(MyString&str)
	{
		this->length = str.length;
		if (data != nullptr)
		{
			delete[]data;
			data = new char[length + SIZE_CHAR];
		}
		data[length] = DEFAULT_END_CHAR;
		memcpy(data, str.data, SIZE_CHAR*length);
	}

	char& MyString::operator[](_uint nb)
	{

		return data[nb];
	}

	_uint MyString::Length()
	{
		return this->length
;
	}

	char* MyString::clone()
	{
		return MyTool::CloneStr(data);
	}

	char* MyString::trim()
	{
		return MyTool::Trim(data);

	}

	char* MyString::subStr(_uint begin, _uint end)
	{
		return MyTool::SubStr(data, begin, end);

	}

	char* MyString::replaceStr(const char* destStr, const char* replaStr)
	{
		return MyTool::ReplaceStr(data, destStr, replaStr);
	}

	int MyString::findStr(const char*str)
	{
		return MyTool::FindStr(data,str);
	}

	int MyString::findStr( _uint begin, _uint end, const char*str)
	{
		return MyTool::FindStr( begin, end, data, str);
	}

	StrArr MyString::split(char divChar)
	{
		return MyTool::Split(data, divChar);
	}

	StrArr GetStrArr(std::vector<char*>&arg)
	{
		StrArr result = nullptr;
		NEW_STRING_ARRAY(result, arg.size());
		int i = 0;
		for (std::vector<char*>::iterator it = arg.begin(); it != arg.end();i++)
		{
			result[i] = CloneStr(*it++);
		}
		return result;
	}


	MyStringVector::MyStringVector()
	{
		this->addLen = DEFAULT_LEN_ADD;
		this->cnstorLen = DEFAULT_LEN_CONSTOR;
		this->memoryLen = this->addLen;
		this->strLen = 0;
		this->data = new char[memoryLen];
		memset(data, 0, this->memoryLen);
		this->data[0] = '\0';
		divChar = DEFAULT_DIV_CHAR;
	}

	MyStringVector::MyStringVector(const char*str)
	{
		_uint len = StrLen(str);
		this->cnstorLen = len+1 > DEFAULT_LEN_CONSTOR ? len+1 : DEFAULT_LEN_CONSTOR;
		this->strLen = len;
		this->memoryLen = this->cnstorLen;
		this->addLen = DEFAULT_LEN_ADD;
		this->data = new char[this->cnstorLen];
		memcpy(data, str, SIZE_CHAR*len);
		data[len] = '\0';
		divChar = DEFAULT_DIV_CHAR;
	}

	MyStringVector::MyStringVector(MyString&str)
	{
		_uint len = str.Length();
		this->cnstorLen = len + 1 > DEFAULT_LEN_CONSTOR ? len + 1 : DEFAULT_LEN_CONSTOR;
		this->strLen = len;
		this->memoryLen = this->cnstorLen;
		this->addLen = DEFAULT_LEN_ADD;
		this->data = new char[this->cnstorLen];
		memcpy(data, str.C_Str(), SIZE_CHAR*len);
		data[len] = '\0';
		divChar = DEFAULT_DIV_CHAR;
	}

	MyStringVector::MyStringVector(MyStringVector&strv)
	{
		this->addLen = strv.addLen;
		this->cnstorLen = strv.cnstorLen;
		this->memoryLen = strv.memoryLen;
		this->strLen = strv.strLen;
		this->data = new char[this->memoryLen];
		memcpy(data, strv.data, SIZE_CHAR*this->memoryLen);
		this->divChar = strv.divChar;
	}

	MyStringVector::MyStringVector(_uint addLen, _uint cnstorLen)
	{
		this->addLen = addLen==0?DEFAULT_LEN_ADD:addLen;
		this->cnstorLen = cnstorLen==0?DEFAULT_LEN_CONSTOR:cnstorLen;
		this->memoryLen = this->cnstorLen;
		this->strLen = 0;
		this->data = new char[this->cnstorLen];
		memset(data, 0, this->cnstorLen);
		data[0] = '\0';
		this->divChar = DEFAULT_DIV_CHAR;
	}

	char* MyStringVector::C_Str()
	{
		return data;
	}

	MyStringVector::~MyStringVector()
	{
		if (data != nullptr)
		{
			delete[]data;
		}
		data = nullptr;
		this->memoryLen = 0;
		this->strLen = 0;
	}

	void MyStringVector::Clear()
	{
		if (data != nullptr)
		{
			delete[]data;
			data = new char[1];
			data[0] = '\0';
		}
		this->strLen = 0;
		this->memoryLen = 1;
	}

	_uint MyStringVector::Length()
	{
		return this->strLen;
	}

	void MyStringVector::SetDivChar(char dch)
	{
		this->divChar = dch;
	}

	char& MyStringVector::operator[](_uint nb)
	{
		return data[nb];
	}

	MyStringVector& MyStringVector::operator<<(const char*str)
	{
		_uint len = StrLen(str);
		if (len == 0)
		{
			return *this;
		}
		_uint needLen = len + this->strLen;
		bool addFlag = false;
		_uint preMemLen = this->memoryLen;
		while (needLen >= this->memoryLen)
		{
			this->memoryLen += this->addLen;
			addFlag = true;
		}
		if (addFlag)
		{
			char* temp = new char[this->memoryLen];
			memcpy(temp, data, preMemLen);
			delete[]data;
			data = temp;
		}

		memcpy(data + this->strLen, str, len);
		this->strLen += len;
		data[strLen] = '\0';
		return *this;
	}

	MyStringVector& MyStringVector::operator<<(MyString&str)
	{
		return this->operator<<(str.C_Str());
	}

	MyStringVector& MyStringVector::operator<<(MyStringVector&strv)
	{
		return this->operator<<(strv.C_Str());
	}

	MyStringVector& MyStringVector::operator<<(char ch)
	{
		char *ds;
		NEW_STRING(ds, 1);
		ds[0] = ch;
		this->operator<<(ds);
		delete[]ds;
		return *this;
	}

	void MyStringVector::operator=(const char*str)
	{
		_uint len = StrLen(str);
		if (data != nullptr)
		{
			delete[]data;
			data = nullptr;
		}
		this->memoryLen = this->cnstorLen;
		this->strLen = len;
		while (this->memoryLen <= this->strLen)
		{
			this->memoryLen += this->addLen;
		}
		data = new char[this->memoryLen];
		memcpy(data, str, SIZE_CHAR*len);
		data[len] = '\0';
	}

	void MyStringVector::operator=(MyString&str)
	{
		this->operator=(str.C_Str());
	}

	void MyStringVector::operator=(MyStringVector&strv)
	{
		this->addLen = strv.addLen;
		this->cnstorLen = strv.cnstorLen;
		this->memoryLen = this->memoryLen;
		this->strLen = strv.strLen;
		this->divChar = strv.divChar;
		memcpy(data, strv.data, this->memoryLen*SIZE_CHAR);
	}

	bool MyStringVector::operator==(const char* str)
	{
		return StrEqual(data, str);
	}

	bool MyStringVector::operator==(MyString&str)
	{
		return StrEqual(data, str.C_Str());
	}

	bool MyStringVector::operator==(MyStringVector&strv)
	{
		return StrEqual(data, strv.data);
	}

	char* MyStringVector::subStr(_uint begin, _uint end)
	{
		return SubStr(data, begin, end);
	}

	int MyStringVector::findStr(const char*str)
	{
		return FindStr(data,str);
	}

	int MyStringVector::findStr(_uint begin, _uint end, const char*str)
	{
		return FindStr(begin, end, data, str);
	}

	char* MyStringVector::replaceStr(const char* destStr, const char* replaStr)
	{
		return ReplaceStr(data, destStr, replaStr);
	}

	char* MyStringVector::trim()
	{
		return Trim(data);

	}

	char* MyStringVector::clone()
	{
		return CloneStr(data);
	}

	StrArr MyStringVector::split()
	{
		return Split(data, this->divChar);
	}

	MyStringVector& MyStringVector::operator>>(char*str)
	{
		_uint lenS = StrLen(str);
		_uint addr, pre;
		pre = this->strLen - 1;
		while (data[pre] == divChar)
		{
			if (pre == 0)
			{
				this->strLen = 0;
				this->data[0] = DEFAULT_END_CHAR;
				return *this;
			}
			pre--;
		}
		addr = pre;
		while (data[addr] != this->divChar)
		{
			if (addr == 0)
			{
				break;
			}
			addr--;
		}
		if (addr == 0)
		{
			if (data[addr] == divChar)
			{
				addr++;
			}
		}
		else
		{
			addr++;
		}
		char *result = subStr(addr, pre);
		this->strLen = addr == 0 ? addr : addr - 1;
		this->data[strLen] = DEFAULT_END_CHAR;
		_uint lenR = StrLen(result);
		if (lenR != 0)
		{
			strcpy(str, result);
			delete[]result;
		}
		return *this;
	}

	MyStringVector& MyStringVector::operator>>(MyString&str)
	{
		_uint addr, pre;
		pre = this->strLen - 1;
		while (data[pre] == divChar)
		{
			if (pre == 0)
			{
				this->strLen = 0;
				this->data[0] = DEFAULT_END_CHAR;
				return *this;
			}
			pre--;
		}
		addr = pre;
		while (data[addr] != this->divChar)
		{
			if (addr == 0)
			{
				break;
			}
			addr--;
		}
		if (addr == 0)
		{
			if (data[addr] == divChar)
			{
				addr++;
			}
		}
		else
		{
			addr++;
		}
		char *result = subStr(addr, pre);
		this->strLen = addr == 0 ? addr : addr - 1;
		this->data[strLen] = DEFAULT_END_CHAR;
		str = result;
		if (result != nullptr)
		{
			delete[]result;
		}
		return *this;
	}
	
	MyStringVector& MyStringVector::operator>>(MyStringVector&str)
	{
		_uint addr, pre;
		pre = this->strLen - 1;
		while (data[pre] == divChar)
		{
			if (pre == 0)
			{
				this->strLen = 0;
				this->data[0] = DEFAULT_END_CHAR;
				return *this;
			}
			pre--;
		}
		addr = pre;
		while (data[addr] != this->divChar)
		{
			if (addr == 0)
			{
				break;
			}
			addr--;
		}
		if (addr == 0)
		{
			if (data[addr] == divChar)
			{
				addr++;
			}
		}
		else
		{
			addr++;
		}
		char *result = subStr(addr, pre);
		this->strLen = addr == 0 ? addr : addr - 1;
		this->data[strLen] = DEFAULT_END_CHAR;
		str = result;
		if (result != nullptr)
		{
			delete[]result;
		}
		return *this;
	}

	MyStringVector& MyStringVector::operator>>(int&arg)
	{
		_uint addr, pre;
		pre = this->strLen - 1;
		while (data[pre] == divChar)
		{
			if (pre == 0)
			{
				this->strLen = 0;
				this->data[0] = DEFAULT_END_CHAR;
				return *this;
			}
			pre--;
		}
		addr = pre;
		while (data[addr] != this->divChar)
		{
			if (addr == 0)
			{
				break;
			}
			addr--;
		}
		if (addr == 0)
		{
			if (data[addr] == divChar)
			{
				addr++;
			}
		}
		else
		{
			addr++;
		}
		char *result = subStr(addr, pre);
		this->strLen = addr == 0 ? addr : addr - 1;
		this->data[strLen] = DEFAULT_END_CHAR;
		arg = Stoi(result);
		if (result != nullptr)
		{
			delete[]result;
		}
		return *this;
	}
	
	MyStringVector& MyStringVector::operator>>(char&ch)
	{
		_uint pre = this->strLen - 1;
		if (this->strLen - 1 != 0&&this->strLen!=0)
		{
			ch = data[strLen - 1];
			data[strLen - 1] = DEFAULT_END_CHAR;
			this->strLen--;
		}
		else
		{
			ch = data[0];
			data[0] = DEFAULT_END_CHAR;
			this->strLen = 0;
		}
		return *this;
	}

	MyStringVector& MyStringVector::operator>>(float&arg)
	{
		_uint addr, pre;
		pre = this->strLen - 1;
		while (data[pre] == divChar)
		{
			if (pre == 0)
			{
				this->strLen = 0;
				this->data[0] = DEFAULT_END_CHAR;
				return *this;
			}
			pre--;
		}
		addr = pre;
		while (data[addr] != this->divChar)
		{
			if (addr == 0)
			{
				break;
			}
			addr--;
		}
		if (addr == 0)
		{
			if (data[addr] == divChar)
			{
				addr++;
			}
		}
		else
		{
			addr++;
		}
		char *result = subStr(addr, pre);
		this->strLen = addr==0?addr:addr-1;
		this->data[strLen] = DEFAULT_END_CHAR;

		arg = Stof(result);
		if (result != nullptr)
		{
			delete[]result;
		}
		return *this;
	}
}