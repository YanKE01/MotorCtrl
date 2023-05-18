#ifndef SOURCE_USER_DATATRANSFORM_H_
#define SOURCE_USER_DATATRANSFORM_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_USER_DATATRANSFORM_H_)
  #define EXTERN
#else
  #define EXTERN extern
#endif
	
EXTERN void UD_vDataTransformInit(UGT_S_DATATRANSFORM_STRU *v);	
EXTERN void UD_vDataTransform(UGT_S_DATATRANSFORM_STRU *v);	

	
#undef EXTERN
#endif
	