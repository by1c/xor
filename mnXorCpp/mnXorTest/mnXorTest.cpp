/*
 * Copyright © exc-jdbi 2016
 *
 * © mnXor 2016
 *
 * mnXor - www.github.com/exc-jdbi/xOr
 *
 * mnXor is Free and Opensource Software
*/

#include "stdafx.h"
#include <iostream>

#include "mnXor.h"

int _tmain(int argc, _TCHAR* argv[]){
	char cText[]="A Ansistring with special characters ¾½¼™Þ‰Æ€#èüä$!$£{°§1*-+±'?Øø}[»²³$£/&%ç¬›|‹¢@©®÷«]. ";
	wchar_t wcText[]=L"A Widestring with special characters 日本人, ไทย, Український, עברית, العربية, भारतीय,فارسی, русский, සිංහල, தமிழ். ";

	char cKey[]="KeyString_ü$!*%";
	wchar_t wcKey[]=L"KeyString_日本人";

	std::string sEnc1,sDec1,sEnc2,sDec2;
	std::wstring wsEnc1,wsDec1,wsEnc2,wsDec2;

	std::string s(cText);
	std::wstring ws(wcText);
	for(int i=0;i<100000;i++){
		s+=cText;
		ws+=wcText;
	}

	wchar_t *bufferW1=0,**pOutW1=&bufferW1;
	wchar_t *bufferW2=0,**pOutW2=&bufferW2;
	int iXorEncW1=xOrEncryptDecryptW(wcText,std::wcslen(wcText),wcKey,std::wcslen(wcKey),pOutW1);
	int iXorDecW1=xOrEncryptDecryptW(*pOutW1,iXorEncW1,wcKey,std::wcslen(wcKey),pOutW2);
	wsDec1.assign(*pOutW2);wsEnc1.assign(*pOutW1);

	char *bufferA1=0,**pOutA1=&bufferA1;
	char *bufferA2=0,**pOutA2=&bufferA2;
	int iXorEncA1=xOrEncryptDecryptA(cText,std::strlen(cText),cKey,std::strlen(cKey),pOutA1);
	int iXorDecA1=xOrEncryptDecryptA(*pOutA1,iXorEncA1,cKey,std::strlen(cKey),pOutA2);
	sDec1.assign(*pOutA2);sEnc1.assign(*pOutA1);
	closeGarbage();

	startGarbage();
	wchar_t *bufferW3=0,**pOutW3=&bufferW3;
	wchar_t *bufferW4=0,**pOutW4=&bufferW4;
	int iXorEncW2=xOrEncryptDecryptW(ws.c_str(),ws.length(),wcKey,std::wcslen(wcKey),pOutW3);
	int iXorDecW2=xOrEncryptDecryptW(*pOutW3,iXorEncW2,wcKey,std::wcslen(wcKey),pOutW4);
	wsDec2.assign(*pOutW4);wsEnc2.assign(*pOutW3);

	char *bufferA3=0,**pOutA3=&bufferA3;
	char *bufferA4=0,**pOutA4=&bufferA4;
	int iXorEncA2=xOrEncryptDecryptA(s.c_str(),s.length(),cKey,std::strlen(cKey),pOutA3);
	int iXorDecA2=xOrEncryptDecryptA(*pOutA3,iXorEncA2,cKey,std::strlen(cKey),pOutA4);
	sDec2.assign(*pOutA4);sEnc2.assign(*pOutA3);
	closeGarbage();

	getchar();
	return 0;
}

