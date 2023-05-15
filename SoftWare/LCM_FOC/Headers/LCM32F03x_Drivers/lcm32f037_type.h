

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCM32F037_TYPE_H
#define __LCM32F037_TYPE_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef signed long long 	s64;
typedef signed long  			s32;
typedef signed short 			s16;
typedef signed char  			s8;

typedef signed long long const 	sc64;  /* Read Only */
typedef signed long  const 			sc32;  /* Read Only */
typedef signed short const 			sc16;  /* Read Only */
typedef signed char  const 			sc8;   /* Read Only */

typedef volatile signed long long 	vs64;
typedef volatile signed long  			vs32;
typedef volatile signed short 			vs16;
typedef volatile signed char  			vs8;

typedef volatile signed long long const vsc64;  /* Read Only */
typedef volatile signed long  const 		vsc32;  /* Read Only */
typedef volatile signed short const 		vsc16;  /* Read Only */
typedef volatile signed char  const 		vsc8;   /* Read Only */


typedef unsigned long long 	u64;
typedef unsigned long  			u32;
typedef unsigned short 			u16;
typedef unsigned char  			u8;

typedef signed char           SI08;
typedef unsigned char         UI08;  /*new increase*/
typedef signed short int      SI16;
typedef unsigned short int    UI16;
typedef signed int            SI32;
typedef unsigned int          UI32;
typedef signed long long      SI64;
typedef unsigned long long    UI64;


typedef unsigned long long const 	uc64;  /* Read Only */
typedef unsigned long  const 			uc32;  /* Read Only */
typedef unsigned short const 			uc16;  /* Read Only */
typedef unsigned char  const 			uc8;   /* Read Only */


typedef volatile unsigned long long  	vu64;
typedef volatile unsigned long  			vu32;
typedef volatile unsigned short 			vu16;
typedef volatile unsigned char  			vu8;

typedef volatile unsigned long long const vuc64;  /* Read Only */
typedef volatile unsigned long  const 		vuc32;  /* Read Only */
typedef volatile unsigned short const 		vuc16;  /* Read Only */
typedef volatile unsigned char  const 		vuc8;   /* Read Only */

typedef double  	f64;
typedef float  		f32;

typedef volatile double vf64; 
typedef volatile float 	vf32; 

typedef volatile double const vfc64;  /* Read Only */
typedef volatile float const 	vfc32;  /* Read Only */


//typedef enum {FALSE = 0, TRUE = !FALSE} bool;

//typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

//typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
//#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

//typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)
#define U64_MAX    ((u64)18446744073709551615)
#define S64_MAX    ((s64)9223372036854775807)
#define S64_MIN    ((s64)-9223372036854775808)

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif 


