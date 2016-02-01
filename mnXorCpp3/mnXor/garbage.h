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
#ifndef __MY_GARBAGE_H__
#define __MY_GARBAGE_H__
namespace Garbage{
	bool start();
	bool close();
	bool setNews(char *c);
	bool setNews(wchar_t *wc);
}
#endif