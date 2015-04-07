/* 
* @Author: sxf
* @Date:   2015-04-06 20:32:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-04-06 20:36:06
*/

#ifndef MEMERY_H
#define MEMERY_H

#include "stddef.h"

#define EFLAGS_AC_BIT 		0x00040000
#define CR0_CACHE_DISABLE 	0x60000000

uint memtest(unsigned int start, unsigned int end);


#endif // MEMERY_H

