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
#include "garbage.h"
#include "additional.h"

inline bool checkLen(char const *ch,int const &iLen){
	if((ch)&&(iLen>0)){if(iLen<=(int)std::strlen(ch))return true;}
	return false;
};
inline bool checkLen(wchar_t const *wch,int const &iLen){
	if((wch) && (iLen>0)){if(iLen<=(int)std::wcslen(wch))return true;}
	return false;
};
class myXor{
private:
	myXor(const myXor &obj);
	myXor& operator=(const myXor&){}
private:
	int pXOrEncryptDecrypt(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut);
	int pXOrEncryptDecrypt(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut);
public:
	myXor();
	~myXor();
public:
	int xOrEncryptDecrypt(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut);
	int xOrEncryptDecrypt(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut);
};
myXor::myXor(){}
myXor::~myXor(){}
myXor::myXor(const myXor &obj){}
int myXor::pXOrEncryptDecrypt(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut){
	int ret=-1;
	try{
		if((checkLen(cPlainCipher,iLen))&&(checkLen(cKey,iKey))&&(ppOut)){
			unsigned char k[]={0x00000021,0x000000C6,0x000000FC,0x00000024,0x00000023,0x00000024,
							   0x0000007B,0x0000002A,0x000000A7,0x0000002B,0x000000A3,0x000000B0,
							   0x00000031,0x0000002D,0x000000D8,0x0000003F,0x000000B1,0x0000000};
			
			int iK=std::strlen((const char*)k);
			char *pOut=new char[iLen+1];			
			memset(pOut,0,iLen+1);
			Garbage::setNews(pOut);

			char *key=new char[iKey+iK+1];			
			memset(key,0,iKey+iK+1);
			Garbage::setNews(key);

			memcpy(key,cKey,iKey);
			memcpy(&key[iKey],k,iK);			

			int iKey2=std::strlen(key);

			for(int i=0;i<iKey2;i++){
				key[i]=Additional::getAdditional(key[i],i);
			}
			for(int i=0;i<iLen;i++){
				if((cPlainCipher[i]==0)&&(i<iLen)){
					std::cout<<"There are a 'NULL' into the string"<<std::endl;
					break;
				}
				if((cPlainCipher[i]^key[i%iKey2])!=0){
					pOut[i]=cPlainCipher[i]^key[i%iKey2];
				}else{pOut[i]=key[i%iKey2];}
			}
			if(std::strlen(pOut)>0){				
				*ppOut=pOut;
				ret=std::strlen(pOut);
			}
		}
		return ret;
	}
	catch(std::exception &ex){
		std::cout<<"myXor::pXOrEncryptDecryptA: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myXor::pXOrEncryptDecrypt(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut){
	int ret=-1;
	try{
		if((checkLen(wcPlainCipher,iLen))&&(checkLen(wcKey,iKey))&&(ppOut)){
			wchar_t k[]={0x00000021,0x000000C6,0x000000FC,0x00000024,0x00000023,0x00000024,
					     0x0000007B,0x0000002A,0x000000A7,0x0000002B,0x000000A3,0x000000B0,
						 0x00000031,0x0000002D,0x000000D8,0x0000003F,0x000000B1,0x0000000};

			int iK=std::wcslen(k);
			wchar_t *pOut=new wchar_t[iLen+1];			
			wmemset(pOut,0,iLen+1);
			Garbage::setNews(pOut);

			wchar_t *key=new wchar_t[iKey+iK+1];			
			wmemset(key,0,iKey+iK+1);
			Garbage::setNews(key);

			wmemcpy(key,wcKey,iKey);
			wmemcpy(&key[iKey],k,iK);

			int iKey2=std::wcslen(key);

			for(int i=0;i<iKey2;i++){
				key[i]=Additional::getAdditional(key[i],i);
			}
			for(int i=0;i<iLen;i++){
				if((wcPlainCipher[i]==0)&&(i<iLen)){
					std::cout<<"There are a 'NULL' into the string"<<std::endl;
					break;
				}
				if((wcPlainCipher[i]^key[i%iKey2])!=0){
					pOut[i]=wcPlainCipher[i]^key[i%iKey2];
				}else{pOut[i]=key[i%iKey2];}
			}
			if(std::wcslen(pOut)>0){				
				*ppOut=pOut;
				ret=std::wcslen(pOut);
			}
		}
		return ret;
	}
	catch(std::exception &ex){
		std::cout<<"myXor::pXOrEncryptDecryptW: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myXor::xOrEncryptDecrypt(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut){
	return pXOrEncryptDecrypt(cPlainCipher,iLen,cKey,iKey,ppOut);
}
int myXor::xOrEncryptDecrypt(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut){
	return pXOrEncryptDecrypt(wcPlainCipher,iLen,wcKey,iKey,ppOut);
}
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
int xOr_EncryptDecryptW(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut){
	return xOrEncryptDecryptW(wcPlainCipher,iLen,wcKey,iKey,ppOut);
}
int _stdcall xOrEncryptDecryptW(const wchar_t *const wcPlainCipher,const int &iLen,const wchar_t *const wcKey, const int &iKey,wchar_t **ppOut){
	myXor xor;
	return xor.xOrEncryptDecrypt(wcPlainCipher,iLen,wcKey,iKey,ppOut);
}
int xOr_EncryptDecryptA(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut){
	return xOrEncryptDecryptA(cPlainCipher,iLen,cKey,iKey,ppOut);
}
int _stdcall xOrEncryptDecryptA(const char *const cPlainCipher,const int &iLen,const char *const cKey, const int &iKey,char **ppOut){
	myXor xor;
	return xor.xOrEncryptDecrypt(cPlainCipher,iLen,cKey,iKey,ppOut);
}
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */