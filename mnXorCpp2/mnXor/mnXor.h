/*
 * Copyright © exc-jdbi 2016
 *
 * © mnXor 2016
 *
 * mnXor - www.github.com/exc-jdbi/xOr
 *
 * mnXor is Free and Opensource Software
*/

#pragma once
#ifndef __MY_XOR_DLL_H__
#define __MY_XOR_DLL_H__
#define EXP32  extern "C" __declspec(dllexport)

//Widestrings
EXP32 int xOr_EncryptDecryptW(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut);
EXP32 int _stdcall xOrEncryptDecryptW(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut);

//Ansistrings
EXP32 int xOr_EncryptDecryptA(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut);
EXP32 int _stdcall xOrEncryptDecryptA(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut);

//Garbage
EXP32 bool start_Garbage();
EXP32 bool _stdcall startGarbage();

EXP32 bool close_Garbage();
EXP32 bool _stdcall closeGarbage();
#endif