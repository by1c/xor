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
#include <math.h>
#include <iostream>

#include "additional.h"

namespace Additional{
	unsigned int primes[]={0x00FFF1,0x00FFA7,0x00FF0D,0x00FEF3,0x00FE27,
						   0x00FDB7,0x00FD85,0x00FCEB,0x00FC73,0x00FC43};

	int xPow(const int &x,const int &exp){
		int ret=-1;
		if((x>=0)&&(exp>=0)){
			double dX=(double)x;
			double dExp=(double)exp;
			double d=pow(dX,dExp);
			return (int)d;
		}
		return ret;
	}
	wchar_t KeyCrypt(const int &pos,const wchar_t &n){
		if((pos>=0)&&(n>0)){
			int iSizePrime=sizeof(primes)/sizeof(unsigned int);
			int q[20]={0};
			memset(q,0,20*sizeof(int));		
			if(n>=primes[0])return n;

			int m=primes[pos%iSizePrime];		
			if(n>=m){
				for(int i=0;i<iSizePrime;i++){
					if(primes[i]<n){m=primes[i-1];break;}
				}
			}
			if(n<m){
				int _nx=pos,_my=m,t=0,ii=0;
				if(pos==0)_nx=93;
				for(;ii<20;ii++){
					q[ii]=(int)(_nx/_my);
					t=_nx%_my;
					if(t==1)break;
					_nx=_my;_my=t;
				}
				_nx=1;_my=0;
				for(;ii>=0;ii--){
					t=_my-(q[ii]*_nx);
					_my=_nx;_nx=t;
				}
				if(_my<0)_my=m+_my;
				unsigned long long l=(n*_my);
				unsigned long long ret=l%m;
				if(ret<xPow(2,16)-1)
					return (wchar_t)ret;
			}
			std::cout<<"ggt(n,m)=0. Please check it."<<std::endl;
			return 0;
		}
		return -1;
	}
	char KeyCrypt(const int &pos,const char &n){
		if((pos>=0)&&(n>0)){
			int iSizePrime=sizeof(primes)/sizeof(unsigned int);
			int q[20]={0};
			memset(q,0,20*sizeof(int));		
			if((unsigned int)n>=primes[0])return (char)n;

			int m=primes[pos%iSizePrime];		
			if(n>=m){
				for(int i=0;i<iSizePrime;i++){
					if(primes[i]<(unsigned int)n){m=primes[i-1];break;}
				}
			}
			if(n<m){
				int _nx=pos,_my=m,t=0,ii=0;
				if(pos==0)_nx=93;
				for(;ii<20;ii++){
					q[ii]=(int)(_nx/_my);
					t=_nx%_my;
					if(t==1)break;
					_nx=_my;_my=t;
				}
				_nx=1;_my=0;
				for(;ii>=0;ii--){
					t=_my-(q[ii]*_nx);
					_my=_nx;_nx=t;
				}
				if(_my<0)_my=m+_my;
				unsigned long long l=(n*_my);
				unsigned long long ret=l%m;
				if(ret<xPow(2,16)-1)
					return (char)ret;
			}
			std::cout<<"ggt(n,m)=0. Please check it."<<std::endl;
			return 0;
		}
		return -1;
	}
	char getAdditional(const char &c,const int &iPos){
		return KeyCrypt(iPos,c);
	}
	wchar_t getAdditional(const wchar_t &wc,const int &iPos){
		return KeyCrypt(iPos,wc);
	}
}