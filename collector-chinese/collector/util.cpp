#include <atlstr.h>  
#include <locale.h>  
//#include "stdafx.h"   // // release must  use this  file ,and debug  must not use this file 

#include "util.h"  

using   namespace   std;


/*
char* UnicodeToBIG5(const wchar_t* szUnicodeString);
char* UnicodeToGB2312(const wchar_t* szUnicodeString);
wchar_t* GB2312ToUnicode(const char* szGBString);
char* GB2312ToBIG5(const char* szGBString);
*/


/*
wchar_t* GB2312ToUnicode(const char* szGBString)
{
	UINT nCodePage = 936; //GB2312  
	int nLength = MultiByteToWideChar(nCodePage, 0, szGBString, -1, NULL, 0);
	wchar_t* pBuffer = new wchar_t[nLength + 1];
	MultiByteToWideChar(nCodePage, 0, szGBString, -1, pBuffer, nLength);
	pBuffer[nLength] = 0;
	return pBuffer;
}
//BIG5 转换成 Unicode：  
wchar_t* BIG5ToUnicode(const char* szBIG5String)
{
	UINT nCodePage = 950; //BIG5  
	int nLength = MultiByteToWideChar(nCodePage, 0, szBIG5String, -1, NULL, 0);
	wchar_t* pBuffer = new wchar_t[nLength + 1];
	MultiByteToWideChar(nCodePage, 0, szBIG5String, -1, pBuffer, nLength);
	pBuffer[nLength] = 0;
	return pBuffer;
}
//Unicode 转换成 GB2312：  
char* UnicodeToGB2312(const wchar_t* szUnicodeString)
{
	UINT nCodePage = 936; //GB2312  
	int nLength = WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, NULL, 0, NULL, NULL);
	char* pBuffer = new char[nLength + 1];
	WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, pBuffer, nLength, NULL, NULL);
	pBuffer[nLength] = 0;
	return pBuffer;
}
//Unicode 转换成 BIG5：  
char* UnicodeToBIG5(const wchar_t* szUnicodeString)
{
	UINT nCodePage = 950; //BIG5  
	int nLength = WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, NULL, 0, NULL, NULL);
	char* pBuffer = new char[nLength + 1];
	WideCharToMultiByte(nCodePage, 0, szUnicodeString, -1, pBuffer, nLength, NULL, NULL);
	pBuffer[nLength] = 0;
	return pBuffer;
}
//繁体中文BIG5 转换成 简体中文 GB2312  
char* BIG5ToGB2312(const char* szBIG5String)
{
	LCID lcid = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
	wchar_t* szUnicodeBuff = BIG5ToUnicode(szBIG5String);
	char* szGB2312Buff = UnicodeToGB2312(szUnicodeBuff);
	int nLength = LCMapString(lcid, LCMAP_SIMPLIFIED_CHINESE, (LPCSTR)szGB2312Buff, -1, NULL, 0);
	char* pBuffer = new char[nLength + 1];
	LCMapString(0x0804, LCMAP_SIMPLIFIED_CHINESE, (LPCSTR)szGB2312Buff, -1, pBuffer, nLength);
	pBuffer[nLength] = 0;

	delete[] szUnicodeBuff;
	delete[] szGB2312Buff;
	return pBuffer;
}
//简体中文 GB2312 转换成 繁体中文BIG5  
char* GB2312ToBIG5(const char* szGBString)
{
	LCID lcid = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
	int nLength = LCMapString(lcid, LCMAP_TRADITIONAL_CHINESE, szGBString, -1, NULL, 0);
	char* pBuffer = new char[nLength + 1];
	LCMapString(lcid, LCMAP_TRADITIONAL_CHINESE, szGBString, -1, pBuffer, nLength);
	pBuffer[nLength] = 0;
	wchar_t* pUnicodeBuff = GB2312ToUnicode(pBuffer);
	char* pBIG5Buff = UnicodeToBIG5(pUnicodeBuff);
	delete[] pBuffer;
	delete[] pUnicodeBuff;
	return pBIG5Buff;
}

*/

//Description:
// This function maps a character string to a wide-character (Unicode) string
//
//Parameters:
// lpcszStr: [in] Pointer to the character string to be converted 
// lpwszStr: [out] Pointer to a buffer that receives the translated string. 
// dwSize: [in] Size of the buffer
//
//Return Values:
// TRUE: Succeed
// FALSE: Failed
// 
//Example:
// MByteToWChar(szA,szW,sizeof(szW)/sizeof(szW[0]));
//-----------------------------------------------------

BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	// Get the required size of the buffer that receives the Unicode 
	// string. 
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);

	if (dwSize < dwMinSize)
	{
		return FALSE;
	}


	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
	return TRUE;
}

//-------------------------------------------------------------------------------------
//Description:
// This function maps a wide-character string to a new character string
//
//Parameters:
// lpcwszStr: [in] Pointer to the character string to be converted 
// lpszStr: [out] Pointer to a buffer that receives the translated string. 
// dwSize: [in] Size of the buffer  of lpszStr  
//
//Return Values:
// TRUE: Succeed
// FALSE: Failed
// 
//Example:
// MByteToWChar(szW,szA,sizeof(szA)/sizeof(szA[0]));

//---------------------------------------------------------------------------------------
BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (dwSize < dwMinSize)
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE);
	return TRUE;
}
