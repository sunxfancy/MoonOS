/* 
* @Author: sxf
* @Date:   2015-04-07 09:52:02
* @Last Modified by:   sxf
* @Last Modified time: 2015-04-07 10:05:10
*/

#ifndef STDDEF_H
#define STDDEF_H

#ifndef NULL
#define NULL 0
#endif // NULL

#ifndef null
#define null 0
#endif // null

#ifndef FALSE
#define FALSE 0
#endif 

#ifndef TRUE
#define TRUE 1
#endif

#ifndef false
#define false 0
#endif 

#ifndef true
#define true 1
#endif 

typedef unsigned int 		size_t;

typedef unsigned char 		byte;
typedef unsigned short 		word;
typedef unsigned int 		dword;

typedef unsigned char 		uint8_t;
typedef unsigned short 		uint16_t;
typedef unsigned int 		uint32_t;
typedef unsigned long long 	uint64_t;


#endif // STDDEF_H
