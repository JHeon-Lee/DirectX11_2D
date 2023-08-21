#include "Framework.h"
#include "String.h"

#include <iomanip> // ����� ��Ʈ���� �����ڸ� �����ϴ� ���, ��Ʈ���� ��� ������ �����ϴµ� ���
#include <sstream> // ���ڿ� ��Ʈ���� ����, �޸� ���ۿ� �����͸� �а� ���µ� ���
#include <atlconv.h>

// ���ڿ��� ������ �����ڷ� �����ϴ� ���
void String::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();
	int cutAt = 0; // �ڷ� ��ġ
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0)
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0)
		result->push_back(origin.substr(0, cutAt));
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();
	int cutAt = 0;
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0)
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0)
		result->push_back(origin.substr(0, cutAt));
}

// Ư�� ���ڷ� �����ϴ��� üũ
bool String::StartWith(string str, string comp)
{
	wstring::size_type index = str.find(comp); // string�̾ �Ȱ��� �ǹ�

	if (index != wstring::npos && (int)index == 0)
		return true;
	return false;
}

bool String::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);

	if (index != wstring::npos && (int)index == 0)
		return true;
	return false;
}

// Ư�� ���ڸ� �����ϴ��� üũ
bool String::Contain(string str, string comp)
{
	size_t found = str.find(comp);
	return found != wstring::npos;
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);
	return found != wstring::npos;
}

// Ư�� ���ڵ��� �ٸ� ���ڵ�� ��ü
void String::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

void String::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

// ���͸� ���ڿ��� �ٲ㼭 ��½�����
string String::VectorToString(Vector3 vec3, int precision)
{
	string temp;
	stringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;

	temp = "X : " + stream1.str() + " Y + " + stream2.str() + " Z : " + stream3.str();
	return temp;
}

wstring String::VectorToWstring(Vector3 vec3, int precision)
{
	wstring temp;
	wstringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x; // setprecision : �ε��Ҽ����� ���е� ����
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;

	temp = L"X : " + stream1.str() + L" Y + " + stream2.str() + L" Z : " + stream3.str();
	return temp;
}

wstring String::ToWstring(string str)
{
	USES_CONVERSION;
	wstring temp = A2W(str.c_str());
	return temp;
}

string String::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());
	return temp;
}
