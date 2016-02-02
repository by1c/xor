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

#define FIX1 64
#define FIX2 1024
#define FIX3 2048
#define FIX4 4096

inline bool checkLen(char const *ch,int const &iLen){
	if((ch)&&(iLen>0)){if(iLen<=(int)std::strlen(ch))return true;}
	return false;
};
inline bool checkLen(wchar_t const *wch,int const &iLen){
	if((wch) && (iLen>0)){if(iLen<=(int)std::wcslen(wch))return true;}
	return false;
};
inline bool checkLen(char const **ch,int const &iLen){
	if((ch) && (iLen>0)){
		for(int i=0;i<iLen;i++){
			if(!checkLen(ch[i],std::strlen(ch[i]))){return false;};
		}
	}
	return true;
};
inline size_t checkSize(FILE* fp){
	fseek(fp, 0L, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	return sz;
};
inline bool checkLen(wchar_t const **wch,int const &iLen){
	if((wch) && (iLen>0)){
		for(int i=0;i<iLen;i++){
			if(!checkLen(wch[i],std::wcslen(wch[i]))){return false;};
		}
	}
	return true;
};
class myXor{
private:
	myXor(const myXor &obj);
	myXor& operator=(const myXor&){}	
private:	
	int pFileCrypt(FILE *_fd,FILE *_fdk,FILE *_fdo);
	bool pSetBuffer(FILE *f1,unsigned char *b,int &l1,const int &l2);

	void pOutText(const errno_t &cE,const char *const cFileName);
	void pOutText(const errno_t &cE,const wchar_t *const cFileName);
	
	int pXOrEncryptDecrypt(const char **cSrc,const int &iLent);
	int pXOrEncryptDecrypt(const wchar_t **wcSrc,const int &iLen);	
public:
	myXor();
	~myXor();
public:
	int xOrEncryptDecrypt(const char **cSrc,const int &iLen);
	int xOrEncryptDecrypt(const wchar_t **wcSrc,const int &iLen);
};
myXor::myXor(){}
myXor::~myXor(){}
myXor::myXor(const myXor &obj){}
void myXor::pOutText(const errno_t &cE,const char *const cFileName){
	std::cout<<"Error: "<<cE<<" - "<<cFileName<<": File was not opened"<<std::endl;
}
void myXor::pOutText(const errno_t &cE,const wchar_t *const cFileName){
	std::wcout<<L"Error: "<<cE<<L" - "<<cFileName<<L": File was not opened"<<std::endl;
}
bool myXor::pSetBuffer(FILE *f1,unsigned char *b,int &l1,const int &l2){
	while(l1<l2){
		unsigned char *buff1=new unsigned char[l2+1];
		unsigned char *buff2=new unsigned char[l2+1];
		memset(buff1,0,l2+1);memset(buff2,0,l2+1);
		memcpy(buff1,b,l1);

		fseek(f1,0L,SEEK_SET);
		int is=fread(buff2,sizeof(unsigned char),l2-l1,f1);

		memcpy(&buff1[l1],buff2,is);
		memcpy(b,buff1,l2);

		delete [] buff2;
		delete [] buff1;

		l1+=is;
		if(l1==l2)return true;		
	}
	return false;
}
int myXor::pFileCrypt(FILE *_fd,FILE *_fdk,FILE *_fdo){
	int ret=-1;
	try{
		if((_fd)&&(_fdk)&&(_fdo)){
			int counter=0;
			unsigned char d1,d2;
			unsigned char *p1,*p2;
			int fix=FIX1,len=0,len2=0;
			size_t fileLen=checkSize(_fd);

			if(fileLen>0xA000){fix=FIX4;}
			else if(fileLen>0x5000){fix=FIX3;}
			else if(fileLen>0x2800){fix=FIX2;}

			unsigned char *buffer1=new unsigned char[fix+1];
			unsigned char *buffer2=new unsigned char[fix+1];
			memset(buffer1,0,(fix+1));memset(buffer2,0,(fix+1));

			if((buffer1)&&(buffer2)){
				while((len=fread(buffer1,sizeof(char),fix,_fd))){
					len2=fread(buffer2,sizeof(char),fix,_fdk);
					if(len2<fix){
						if(pSetBuffer(_fdk,buffer2,len2,fix)){
							buffer2[fix]=0;
						}
					}
					int i=0;
					p2=buffer2;
					for(p1=buffer1,i=0;i<len;i++,p1++,p2++){
						d1=Additional::getAdditional((const char)*p2,counter);
						d2=*p1^d1;
						if(d2!=0){
							fputc(d2,_fdo);
						}else{fputc(d1,_fdo);}
						counter++;
					}
				}
				if(_fd!=stdin)fclose(_fd);
				if(_fdo!=stdout)fclose(_fdo);
				if(_fdk!=stdin)fclose(_fdo);
				delete [] buffer2;
				delete [] buffer1;
				if(counter>0)
					ret=counter;
			}
		}
		return ret;
		}
	catch(std::exception &ex){
		std::cout<<"myXor::pFileCrypt: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myXor::pXOrEncryptDecrypt(const char **cSrc,const int &iLen){
	int ret=-1;
	try{
		if((checkLen(cSrc,iLen))){
			if(iLen!=3){return ret;}
			
			errno_t err;
			FILE *fd=stdin,*fdo=stdout,*fdk=stdin;

			err=fopen_s(&fd,cSrc[0],"rb");
			if((!err==0)||(!fd)){pOutText(err,cSrc[0]);return ret;}
			err=fopen_s(&fdk,cSrc[1],"rb");
			if((!err==0)||(!fd)){pOutText(err,cSrc[1]);return ret;}
			err=fopen_s(&fdo,cSrc[2],"wb");
			if((!err==0)||(!fd)){pOutText(err,cSrc[2]);return ret;}
			ret=pFileCrypt(fd,fdk,fdo);
		}
		return ret;
	}
	catch(std::exception &ex){
		std::cout<<"myXor::pXOrEncryptDecryptA: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myXor::pXOrEncryptDecrypt(const wchar_t **const wcSrc,const int &iLen){
	int ret=-1;
	try{
		if((checkLen(wcSrc,iLen))){
			if(iLen!=3){return ret;}
			
			errno_t err;
			FILE *fd=stdin,*fdo=stdout,*fdk=stdin;

			err=_wfopen_s(&fd,wcSrc[0],L"rb");
			if((!err==0)||(!fd)){pOutText(err,wcSrc[0]);return ret;}
			err=_wfopen_s(&fdk,wcSrc[1],L"rb");
			if((!err==0)||(!fd)){pOutText(err,wcSrc[1]);return ret;}
			err=_wfopen_s(&fdo,wcSrc[2],L"wb");
			if((!err==0)||(!fd)){pOutText(err,wcSrc[2]);return ret;}
			ret=pFileCrypt(fd,fdk,fdo);
		}
		return ret;
	}
	catch(std::exception &ex){
		std::cout<<"myXor::pXOrEncryptDecryptW: "<<ex.what()<<std::endl;
		return ret;
	}
}
int myXor::xOrEncryptDecrypt(const char **cSrc,const int &iLen){
	return pXOrEncryptDecrypt(cSrc,iLen);
}
int myXor::xOrEncryptDecrypt(const wchar_t **const wcSrc,const int &iLen){
	return pXOrEncryptDecrypt(wcSrc,iLen);
}
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
int xOr_EncryptDecryptW(const wchar_t **const wcSrc,const int &iLen){
	return xOrEncryptDecryptW(wcSrc,iLen);
}
int _stdcall xOrEncryptDecryptW(const wchar_t **const wcSrc,const int &iLen){
	myXor xor;
	return xor.xOrEncryptDecrypt(wcSrc,iLen);
}
int xOr_EncryptDecryptA(const char **cSrc,const int &iLen){
	return xOrEncryptDecryptA(cSrc,iLen);
}
int _stdcall xOrEncryptDecryptA(const char **cSrc,const int &iLen){
	myXor xor;
	return xor.xOrEncryptDecrypt(cSrc,iLen);
}
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */
/* ------------------------- ------------------------- ------------------------- ------------------------- */