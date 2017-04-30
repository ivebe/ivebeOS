/**
 * Standard Definitions library
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#ifndef NULL
#define NULL            ((void *)0)
#endif

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#ifndef BOOL
#define BOOL
typedef enum
{
  false, true
}
bool;
#endif

typedef long int64;
typedef int int32;
typedef short int16;
typedef char int8;

typedef unsigned long int64u;
typedef unsigned int int32u;
typedef unsigned short int16u;
typedef unsigned char int8u;

#endif
