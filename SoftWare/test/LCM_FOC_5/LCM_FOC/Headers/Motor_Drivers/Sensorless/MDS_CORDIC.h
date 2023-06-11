#ifndef SOURCE_MDS_CORDIC_H_
#define SOURCE_MDS_CORDIC_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_MDS_OBSERVER_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

#define DSP32_Q(x) ((int) ((x)*(((unsigned) (1 << (20))))))
	

EXTERN int MDS_s32Sin(int zi);
EXTERN int MDS_s32Cos(int zi);
EXTERN int MDS_s32Atan2(int xi, int yi);

#undef EXTERN	
#endif

