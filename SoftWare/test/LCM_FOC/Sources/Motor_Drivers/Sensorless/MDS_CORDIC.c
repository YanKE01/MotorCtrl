#define EXPORT_MDS_CORDIC_H
	#include "MDS_CORDIC.h"    //先定义在声明是允许的
#undef EXPORT_MDS_CORDIC_H

const int atanLUT[20] = {
DSP32_Q(0.78539816340),
DSP32_Q(0.46364760900),
DSP32_Q(0.24497866313),
DSP32_Q(0.12435499455),
DSP32_Q(0.06241881000),
DSP32_Q(0.03123983343),
DSP32_Q(0.01562372862),
DSP32_Q(0.00781234106),
DSP32_Q(0.00390623013),
DSP32_Q(0.00195312252),
DSP32_Q(0.00097656219),
DSP32_Q(0.00048828121),
DSP32_Q(0.00024414062),
DSP32_Q(0.00012207031),
DSP32_Q(0.00006103516),
DSP32_Q(0.00003051758),
DSP32_Q(0.00001525879),
DSP32_Q(0.00000762939),
DSP32_Q(0.00000381470),
DSP32_Q(0.00000190735)
};

int MDS_s32Sin(int zi)
{
  int x, y, z, x_new;
  int i, sign;
  
  x = DSP32_Q(0.60725293500888);
  y = 0;
  z = zi;
   
  for(i=0; i<20; i++)
  {
    if(z >= 0)
    {
      sign = 1;
    }
    else
    {
      sign = -1;
    }
     
    x_new = x - ((sign*y)>>i);
    y = y + ((sign*x)>>i);
    x = x_new;
    z = z - sign*atanLUT[i];
  }
   
  return (y);
}

int MDS_s32Cos(int zi)
{
  int x, y, z, x_new;
  int i, sign;
  
  x = DSP32_Q(0.60725293500888);
  y = 0;
  z = zi;
   
  for(i=0; i<20; i++)
  {
    if(z >= 0)
    {
      sign = 1;
    }
    else
    {
      sign = -1;
    }
     
    x_new = x - ((sign*y)>>i);
    y = y + ((sign*x)>>i);
    x = x_new;
    z = z - sign*atanLUT[i];
  }
   
  return (x);
}
//13.60us int=32bits
int MDS_s32Atan2(int xi, int yi)
{
  int x, y, z, x_new;
  int i; 
	int sign;
	u8  xsign=0;
	u8  ysign=0;
   
  x = xi;
  y = yi;
  z = 0;
  if(x<0){x=-x;xsign=1;}
	if(y<0){ysign=1;}
	
  for(i=0; i<20; i++)
  {
    if(y >= 0)
    {
      sign = -1;
    }
    else
    {
      sign = 1;
    }
     
    x_new = x - ((sign*y)>>(i));
    y = y + ((sign*x)>>(i));
    x = x_new;
    z = z - sign*atanLUT[i];
  }
	
	if(xsign==1)
	{
		if(ysign==1)z=-z-3294198;//3294198=IQ(pi);
		else 				z=3294198-z;
	}
	
	if(z<0)z=z+6588397;//6588397=IQ(2*pi)
  
	z=((s64)z*5343062)>>20;//_IQ20(2^5/(3.14*2))=5343062,result is IQ25
  return (z);
}