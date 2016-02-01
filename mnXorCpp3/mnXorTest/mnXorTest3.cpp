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
	char srcFileA[]="srcFile";
	char keyFileA[]="keyFile";
	char dstFileA[]="dstFileA";
	char dstFileRA[]="dstFileRA";

	wchar_t srcFileW[]=L"srcFile";
	wchar_t keyFileW[]=L"keyFile";
	wchar_t dstFileW[]=L"dstFileW";
	wchar_t dstFileRW[]=L"dstFileRW";

	const char *cFiles[3]={srcFileA,keyFileA,dstFileA};
	const char *cFilesR[3]={dstFileA,keyFileA,dstFileRA};

	const wchar_t *wcFiles[3]={srcFileW,keyFileW,dstFileW};
	const wchar_t *wcFilesR[3]={dstFileW,keyFileW,dstFileRW};

	int iXorEncW1=xOrEncryptDecryptW(wcFiles,sizeof(wcFiles)/sizeof(wchar_t*));
	int iXorDecW1=xOrEncryptDecryptW(wcFilesR,sizeof(wcFilesR)/sizeof(wchar_t*));

	int iXorEncA1=xOrEncryptDecryptA(cFiles,sizeof(cFiles)/sizeof(char*));
	int iXorDecA1=xOrEncryptDecryptA(cFilesR,sizeof(cFilesR)/sizeof(char*));
	closeGarbage();

	getchar();
	return 0;
}

