#pragma once

#define CONFIG  _T("config.ini")

char* UnicodeToBIG5(const wchar_t* szUnicodeString);
char* UnicodeToGB2312(const wchar_t* szUnicodeString);
wchar_t* GB2312ToUnicode(const char* szGBString);
char* GB2312ToBIG5(const char* szGBString);

BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
