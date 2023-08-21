#include "Framework.h"
#include "Path.h"

bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWstring(path));
}

bool Path::ExistFile(wstring path)
{
	DWORD fileValue = GetFileAttributes(path.c_str());
	return fileValue != INVALID_FILE_ATTRIBUTES;
}

bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWstring(path));
}

bool Path::ExistDirectory(wstring path)
{
	DWORD attribute = GetFileAttributes(path.c_str()); // 파일의 속성을 알아보는 함수
	
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES &&
		attribute & FILE_ATTRIBUTE_DIRECTORY);

	return temp == TRUE;
}

string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

string Path::GetDirectoryName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}
