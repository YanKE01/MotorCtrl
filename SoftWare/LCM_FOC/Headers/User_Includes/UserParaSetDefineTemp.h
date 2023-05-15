/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : UserParaSetDefine.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : Users set all control parameters in this h file
*******************************************************************************/
#ifndef __USERPARASETDEFINETEMP_H_INCLUDED__
#define __USERPARASETDEFINETEMP_H_INCLUDED__

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

//系统时钟
#define UPDS_CKTIM						((u32)96000000uL)	// 系统主频

//调试模式
#define UPDS_KEIL_DEBUG				(0)						//用Keil调试，参数从UserParaSetDefine读取
#define UPDS_SOFTTOOL_DEBUG		(1)						//用上位机调试，参数从上位机下载写到Flash
#define UPDS_DEBUG_MODE				(UPDS_KEIL_DEBUG)

//功率环反馈选择
#define UPDS_POWER_CONTROL_SOFTWARE 							(0)  //利用内部电流和电压给定   
#define UPDS_POWER_CONTROL_HARDWARE								(1)	 //idc*udc
#define UPDS_POWER_CONTROL_SEL	 									(UPDS_POWER_CONTROL_HARDWARE)

//Systick中断频率（次中断）
#define UPDS_SYS_TICK_HZ			(10000)			// 次中断频率，单位：Hz，fsystick		
#define UPDS_SYS_TASK_HZ  		(u16)(UPDS_SYS_TICK_HZ/UPDS_SPD_LOOP_COUNT)
#define UPDS_SAMPLE_AD_MAX		(4.0f)			// ADC采样量程		


//七五段式SVPWM切换速度滞环
#define UPDS_5STAGE_SPD_H           _IQ(0.6)							// 七段式SVPWM->五段式SVPWM,滞环高速切换点
#define UPDS_7STAGE_SPD_H           _IQ(0.5)							// 五段式SVPWM->七段式SVPWM,滞环低速切换点	

//PWM开关频率切换速度滞环
#define UPDS_PWM_SWITCH_SPEED_LOW 	_IQ(0.2)							// 频率速度,滞环低速切换点，fpwm2->fpwm1
#define UPDS_PWM_SWITCH_SPEED_HIGH 	_IQ(0.3)							// 频率速度,高速切换点，fpwm1->fpwm2			

//电流环数据格式
#define UPDS_CUR_IQ24 							(0)  //常规使用   
#define UPDS_CUR_IQ12								(1)	 //高PWM主频时用，高转速的应用，如吸尘器等
#define UPDS_CUR_IQ		 							(UPDS_CUR_IQ24)

//电流环PI参数限幅
#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
	#define UPSD_PI_ID_MAX 						_IQ(0.95)		// d轴电压PI正限幅
	#define UPSD_PI_ID_MIN 						_IQ(-0.95)	// d轴电压PI负限幅
																														
	#define UPSD_PI_IQ_MAX 						_IQ(0.95)		// q轴电压PI正限幅
	#define UPSD_PI_IQ_MIN 						_IQ(-0.95)	// q轴电压PI正限幅
#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
	#define UPSD_PI_ID_MAX 						(s16)(0.95*16384)		// d轴电压PI正限幅
	#define UPSD_PI_ID_MIN 						(s16)(-0.95*16384)		// d轴电压PI负限幅
																														
	#define UPSD_PI_IQ_MAX 						(s16)(0.95*16384)		// q轴电压PI正限幅
	#define UPSD_PI_IQ_MIN 						(s16)(-0.95*16384)		// q轴电压PI正限幅
#endif

#define UPDS_UABC_MEAS_DISABLE		(0)
#define UPDS_UABC_MEAS_ENABLE			(1)
#define UPDS_UABC_MEAS_SEL				(UPDS_UABC_MEAS_DISABLE)

//VSP开启和关闭电压点（标幺）
#define UPDS_VSP_START 		(0.25f)
#define UPDS_VSP_OFF  		(0.15f)

//VSP最小和最大电压（V）
#define UPDS_VSP_MIN_V 		(1.57f)
#define UPDS_VSP_MAX_V  	(3.54f)

//电流采样窗口宽度（ns）,三电阻时候用
#define UPDS_SAMPLE_WINDOW_TIME_US (3.0f)		//Unit:us

//单电阻是移相时间
#define UPDS_SINGLE_SHUNT_WINDOW_TIME_US (3.0f)		//Unit:us

//带速重启（有电压检测，暂未开放） 
#define UPDS_STARTUP_SPD_LIMIT_MIN				(30.0f)     // 最低转速
#define UPDS_STARTUP_SPD_LIMIT_MID				(600.0f)    // 最高转速
#define UPDS_STARTUP_SPD_LIMIT_MAX				(1800.0f)   //Unit: rpm(mechanical)
#define UPDS_SRATRUP_SPD_LIMIT_NEG_MIN		(-20.0f)
#define UPDS_SRATRUP_SPD_LIMIT_NEG_MID		(-600.0f)

////下桥臂全开刹车（仅下桥臂全开刹车时使用）
//#define UPDS_BREAK_ON					  (1)
//#define UPDS_BREAK_OFF					(2)
//#define UPDS_BREAK_MODE					(UPDS_BREAK_OFF)

//#define UPDS_BREAK_STRENGTH 		(0.28f)
//#define UPDS_BREAK_STRENGTH_MAX	(0.99f)
//#define UPDS_BREAK_STRENGTH_MIN	(0.01f)
//#define UPDS_BREAK_LOW_SPEED		_IQ(0.005)


//Usart通信
#define UPDS_USARTBANDRATE 			256000

//电压调制度
//#define MAX_MODULATION_100_PER_CENT     
//#define MAX_MODULATION_99_PER_CENT      // up to 11.8 kHz
//#define MAX_MODULATION_98_PER_CENT      // up to 12.2 kHz  
//#define MAX_MODULATION_97_PER_CENT      // up to 12.9 kHz  
//#define MAX_MODULATION_96_PER_CENT      // up to 14.4 kHz  
#define MAX_MODULATION_95_PER_CENT      // up to 14.8 kHz
//#define MAX_MODULATION_94_PER_CENT      // up to 15.2 kHz  
//#define MAX_MODULATION_93_PER_CENT      // up to 16.7 kHz
//#define MAX_MODULATION_92_PER_CENT      // up to 17.1 kHz
//#define MAX_MODULATION_89_PER_CENT      // up to 17.5 kHz
//#define MAX_MODULATION_85_PER_CENT      // up to 17.5 kHz

#define UPDS_SPEED_MIN_PROTECT_RPM     				(200.0f) // 电机运行最低转速

//保护后重启时间
#define UPDS_RE_STARTUP_OVERCURR_TIME_S		(5.0f)
#define UPDS_RE_STARTUP_OVERVOLT_TIME_S		(3.0f)
#define UPDS_RE_STARTUP_UNDERVOLT_TIME_S	(3.0f)
#define UPDS_RE_STARTUP_LONG_TIME_S				(10.0f)		//unit: s;
#define UPDS_RE_STARTUP_IPM_FAULT_RECOVERY_TIME_S		(7.0f)
#define UPDS_LOSEPHASE_A									(1.0f)			// 电流不平衡保护(缺相)
#define UPDS_LOSEPHASE_TIME_MS						(5000.0f)			// 触发缺相保护所需时间(s) 
#define US_RE_STARTUP_NOWATER_TIME_S			(5.0f)

//定义基准值

#define UPDS_SQRT3   				(1.7320508f)
#define UPDS_ONE_DIV_SQRT3 	(0.57735027)
#define UPDS_PI							(3.1415926f)
#define UPDS_2PI						(6.2831853f)
#define UPDS_SQRT3_IQ24			_IQ(UPDS_SQRT3)
#define UPDS_2_IQ12					_IQ12(1.5)
#define UPDS_0POINT8_IQ12		_IQ12(0.8)
#define UPDS_S32_ABS(A) 		((A>0)?A:(-A)) 

#define UPDS_PWM_TS 			((f32)1000000.0/UPDS_PWM_FREQ) 	// Unit: s
#define UPDS_PWM_TS_S			((f32)1.0/UPDS_PWM_FREQ)
#define UPDS_PWM_TS2 			((f32)1000000.0/UPDS_PWM_FREQ2) // Unit: s
#define UPDS_PWM_TS_S2		((f32)1.0/UPDS_PWM_FREQ2)

#define UPDS_PWM_MODE1		(1)   //七段式
#define UPDS_PWM_MODE2		(2)		//五段式

#define UPDS_UB					(UPDS_UDC_REAL / UPDS_SQRT3)			//Ub = Udc/sqrt(3) = 60/1.73 = 34.641
#define UPDS_IB					(UPDS_SAMPLE_AD_MAX / 2.0f / UPDS_SAMPLE_CURR_R_REAL / UPDS_SAMPLE_CURR_OP_REAL)
#define UPDS_FB					(UPDS_RATED_SPEED*UPDS_PAIRS/60.0)
#define UPDS_WB					(UPDS_2PI * UPDS_FB)							//wb = 2*PI*fb = 1256.64
#define	UPDS_RB					(UPDS_UB / UPDS_IB)								//Rb = Zb = Ub/Ib = 3.4641
#define UPDS_LB					(UPDS_RB / UPDS_WB)			  				//Lb = Rb/wb = 0.002757
#define	UPDS_TB					(1.0f / UPDS_WB)						    	//Tsb = 1/(2*PI*fb) = 0.0007958
#define UPDS_PSIB				(UPDS_UB/UPDS_WB)

#define UPDS_SPEED_BASE_RPM (u32)(UPDS_FB*60.0/UPDS_PAIRS)

#define	UPDS_RSP				(UPDS_RS_REAL / UPDS_RB)								//Rb = Zb = Ub/Ib = 3.4641
#define UPDS_LDP				(UPDS_LD_REAL / UPDS_LB)			  				//Lb = Rb/wb = 0.002757
#define UPDS_LQP				(UPDS_LQ_REAL / UPDS_LB)
#define	UPDS_TP					(UPDS_PWM_TS_S / UPDS_TB)
#define	UPDS_PSIP				(UPDS_PSI_REAL / UPDS_PSIB)
#define	UPDS_PSIP_IQ		_IQ(UPDS_PSIP)
#define UPDS_SAMPLE_VXN_OP_GAIN						(0.09836f)
#define UPDS_UDC_SAMPLE_MAX 							(UPDS_SAMPLE_AD_MAX / UPDS_SAMPLE_VOLT_OP_GAIN)
#define UPDS_UXN_SAMPLE_MAX 							(UPDS_SAMPLE_AD_MAX / UPDS_SAMPLE_VXN_OP_GAIN)
#define UPDS_IQ8_UDC_SAMPLE_PERUNIT 			(s16)(UPDS_UDC_SAMPLE_MAX / UPDS_UB * 0x0100)//IQ8
#define UPDS_IQ12_UDC_SAMPLE_PERUNIT 			(s16)(UPDS_UDC_SAMPLE_MAX / UPDS_UB * 0x1000)//IQ12
#define UPDS_IQ12_UXN_SAMPLE_PERUNIT 			(s16)(UPDS_UXN_SAMPLE_MAX / UPDS_UB * 0x1000)//IQ12
#define UPDS_UALPHA_MEAS_GAIN_IQ12 				(s16)(UPDS_IQ12_UXN_SAMPLE_PERUNIT*2.0/3.0)    						//2/3*gain
#define UPDS_UBETA_MEAS_GAIN_IQ12 				(s16)(UPDS_IQ12_UXN_SAMPLE_PERUNIT*0.57735026918963)			//2/3*gain*sqrt(3)/2)
#define	UPDS_TP2				(UPDS_PWM_TS_S2 / UPDS_TB)

#define UPDS_UDC_SAMPLE_MAX_V 		(UPDS_SAMPLE_AD_MAX / UPDS_SAMPLE_VOLT_OP_GAIN)
#define UPDS_IDC_SAMPLE_MAX_A			(UPDS_SAMPLE_AD_MAX / 2.0f / UPDS_SAMPLE_DCBUS_R_REAL / UPDS_SAMPLE_DCBUS_OP_REAL)
//速度环间隔
#define UPDS_SPD_LOOP_COUNT				(u8)(10)

#define UPDS_CURR_FREQ 				(UPDS_PWM_FREQ)//fcur
#define UPDS_CURR_TS					(1.0f / UPDS_CURR_FREQ)
#define UPDS_CURR_FREQ2 			(UPDS_PWM_FREQ2)//fcur
#define UPDS_CURR_TS2					(1.0f / UPDS_CURR_FREQ2)
#define UPDS_SYS_TICK_FREQ		((u32)10000)//Hz
#define UPDS_SPD_FREQ 				(UPDS_SYS_TICK_FREQ / UPDS_SPD_LOOP_COUNT)//fcur

#define UPDS_SYS_TICK_TASK_HZ				(u32)(UPDS_SYS_TICK_HZ/UPDS_SPD_LOOP_COUNT)
#define UPDS_SYS_TICK_PERIOD				(u32)(UPDS_CKTIM/UPDS_SYS_TICK_HZ)

//母线电流采样低通滤波（Hz）
#define UPDS_UDC_LPF_BAND_HZ 					(30000.0f)//Hz
//VSP采样滤波（Hz）
#define UPDS_VSP_LPF_BAND_HZ 					(100.0f)
//电流滤波（Hz）
#define UPDS_CURR_LPF_HZ 							(500.0f)//Unit:Hz

#define UPDS_OBSERVER_FREQ 		(UPDS_CURR_FREQ)
#define UPDS_OBSERVER_FREQ2 	(UPDS_CURR_FREQ2)
#define UPDS_SPD_LPF_GAIN2 		_IQ24(UPDS_SPD_LPF_BAND*UPDS_CURR_TS2 /( 1.0f + UPDS_SPD_LPF_BAND*UPDS_CURR_TS2))

#define UPDS_SPD_MIN_IQ15 		_IQ15(UPDS_SPEED_MIN_PROTECT_RPM*UPDS_PAIRS/60.0/UPDS_FB)

//#define UPDS_SPD_POWER_MAX_IQ     _IQ(UPSD_POWER_MAX/UPDS_POWER_BASE_W)

//#define UPDS_POWER_MAX_IQ			_IQ(UPDS_POWER_MAX_W/UPDS_POWER_BASE_W)
//#define UPDS_POWER_MIN_IQ			_IQ(UPDS_POWER_MIN_W/UPDS_POWER_BASE_W)

//#define UPDS_SPEED_MAX_IQ			_IQ((f32)UPDS_RATED_SPEED/UPDS_SPEED_BASE_RPM)
//#define UPDS_SPEED_MIN_IQ			_IQ(-(f32)UPDS_RATED_SPEED/UPDS_SPEED_BASE_RPM)
//#define UPSD_PI_SPEED_MAX_SQUARE	_IQ(UPDS_RATED_CURRENT*UPDS_RATED_CURRENT/UPDS_IB/UPDS_IB)//限制定子电流幅值

#define UPDS_SYSTEM_START 		(s16)(UPDS_VSP_START*0x7FFF)
#define UPDS_SYSTEM_OFF  			(s16)(UPDS_VSP_OFF*0x7FFF)
#define UPDS_VSP_MIN 					(s16)(UPDS_VSP_MIN_V/UPDS_SAMPLE_AD_MAX*0x7FFF)
#define UPDS_VSP_MAX  				(s16)(UPDS_VSP_MAX_V/UPDS_SAMPLE_AD_MAX*0x7FFF)
#define UPDS_VSP_OFFSET  			(s16)(UPDS_VSP_MIN)
#define UPDS_VSP_GAIN					(s16)(0x7FFF/(UPDS_VSP_MAX-UPDS_VSP_MIN)*0x0FFF) //_IQ12

#define UPDS_MEAS_VOLTAGE_LPF_BAND 		(20.0*UPDS_2PI)//Hz
#define UPDS_MEAS_VOLTAGE_LPF_GAIN 		_IQ15(UPDS_MEAS_VOLTAGE_LPF_BAND*UPDS_2PI*UPDS_CURR_TS /( 1.0f + UPDS_IGBTOVERTEMPERATURE_LPF_HZ*UPDS_2PI*UPDS_CURR_TS)) 

#define UPDS_IQ_LPF_BAND_GAIN 	(s16)(UPDS_IQ_LPF_BAND*UPDS_CURR_TS /( 1.0f + UPDS_IQ_LPF_BAND*UPDS_CURR_TS)*0x7FFF)  //IQ15
#define UPDS_TIME_COMP					(s16)((UPDS_DEADTIME_NS+00)/1000.0/UPDS_PWM_TS*0x7FFF)
#define UPDS_TIME_COMP2					(s16)((UPDS_DEADTIME_NS+00)/1000.0/UPDS_PWM_TS2*0x7FFF)

#define UPDS_RAMP_STEP 							(0x0028)				
#define UPDS_ACC_RATE_1kRPM_S_MAX 	(u16)((f32)UPDS_SYS_TICK_TASK_HZ/(1000.0*UPDS_PAIRS/60.0/UPDS_FB/UPDS_ACC_RATE_1kRPM_S*32768/UPDS_RAMP_STEP))

//定位和开环启动
#define UPDS_IQ_ALIGNMENT_AMPL			(0.5f) 		//Unit: A,1.5
#define UPDS_IQ_ALIGNMENT_TIME			(1.5f) 		//Unit: s

#define UPDS_IQ_STARTUP_AMPL				(0.5f) 		//Unit: A,1.75
#define UPDS_IQ_STARTUP_TIME				(4.0f) 		//Unit: s
#define UPDS_SPD_STARTUP_FINA				(60.0f)	//Unit: rpm(mechanical),400
#define UPDS_SPD_FINA_TIME					(5.0f)		//Uint: s
	
#define UPDS_SPD_CLOSEDLOOP_INIT		(200.0f)	//Unit: rpm(mechanical)
#define UPDS_IQ_SWITCH_TIME_MS     	(50.0f)	
#define UPDS_IQ_SWITCH_MIN					(0.05f)		//Unit: A
#define UPDS_THETAERR_SWITCH_MIN		(10.0f)   //Unit: degree
#define UPDS_THETAERR_SWITCH_MAX		(110.0f)  //Unit: degree

#define UPDS_SOFTCLOSE_IQ_DEACC_MS_IQ 			_IQ(1000.0/UPDS_SOFTCLOSE_IQ_DEACC_MS/UPDS_CURR_FREQ)			//1/(UPDS_SOFTCLOSE_IQ_DEACC_MS_IQ*UPDS_CURR_FREQ/1000.0)
#define UPDS_SOFTCLOSE_IQ_LOW_LIMIT_A_IQ		_IQ(UPDS_SOFTCLOSE_IQ_LOW_LIMIT_A/UPDS_IB)  								//Unit:A

#define UPDS_CURR_LPF_IQ15 		_IQ15(UPDS_CURR_LPF_HZ*UPDS_2PI*UPDS_CURR_TS /( 1.0f + UPDS_CURR_LPF_HZ*UPDS_CURR_TS*UPDS_2PI))

#define UPDS_UDC_UPDATA_MAX_IQ12				_IQ12(1.6)
#define UPDS_UDC_UPDATA_MIN_IQ12				_IQ12(0.3)
#define UPDS_UDC_GAIN_UXN_IQ12					_IQ12(UPDS_UDC_SAMPLE_MAX/UPDS_UB*UPDS_ONE_DIV_SQRT3)

#define UPDS_SHORTTIMEIQ 								_IQ(UPDS_WB * 0.000001 * UPDS_SHORTTIME_US/ OB_THETAB)

#define UPDS_INJECT_D_CURRENT_A					(UPDS_INJECT_D_CURRENT_A_PU*UPDS_RATED_CURRENT)
#define UPDS_INJECT_D_CURRENT_IQ				_IQ24(UPDS_INJECT_D_CURRENT_A/UPDS_IB)
#define UPDS_SHORTTIME_US_CNT						(s32)(UPDS_SHORTTIME_US*UPDS_PWM_FREQ*0.000001)
#define UPDS_INTERVAL_US_CNT						(s32)(UPDS_INTERVAL_US*UPDS_PWM_FREQ*0.000001)	
#define UPDS_INTERVAL_FINAL_MS_CNT			(s32)(UPDS_INTERVAL_FINAL_MS*UPDS_PWM_FREQ*0.001)	
#define UPDS_RESTART_DELTA_TIME					(((UPDS_SHORTTIME_US+UPDS_INTERVAL_US)/1000.0)/1000.0)
#define UPDS_RESTART_POS_GAIN						_IQ(UPDS_INTERVAL_US/1000.0/(UPDS_RESTART_DELTA_TIME*0.001+UPDS_INTERVAL_US/1000.0))

#define UPDS_IPD_PULSE_CNT							(u16)(UPDS_IPD_PULSE_US*UPDS_PWM_FREQ*0.000001)
#define UPDS_IPD_INTERVAL_CNT						(u16)(UPDS_IPD_INTERVAL_US*UPDS_PWM_FREQ*0.000001)	

#define UPDS_SOFTCLOSE_IQ_DEACC_MS 			(500.0f)	//the time is needed from IQ1->IQ(0)
#define UPDS_SOFTCLOSE_IQ_LOW_LIMIT_A		(0.02f)  	//Unit:A

#define UPDS_BREAK_TIME_MS							(100.0f) //unit: ms

#define UPDS_PRECHARGE 									(0.2f)
#define UPDS_PRECHARGE_TIME_MS					(13.0f)

#define UPDS_IQ_LPF_BAND 				(100.0*UPDS_2PI)
#define UPDS_IQ_ON_AMP					(s16)(0.05*0x7FFF)
#define UPDS_IQ_OFF_AMP					(s16)(0.025*0x7FFF)

#define UPDS_UART_SIZE 					(11u)
#define UPDS_UART_REC_COMMAND1_LENGTH 								(100u)
#define UPDS_UART_REC_COMMAND1_HALFWOED_LENGTH       ((UPDS_UART_REC_COMMAND1_LENGTH>>1)-1)
#define UPDS_UART_REC_COMMAND2_LENGTH 			(8u)
#define UPDS_UART_DR_ADDRESS 		(0x40014000)
#define UPDS_SYSTICK_DISABLE 		{SysTick->CTRL &= 0xFFFFFFFE;}
#define UPDS_SYSTICK_ENABLE 		{SysTick->CTRL |= 0x00000001;}


//定义IO
#define PA1_SET 					GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define PA1_RESET 				GPIO_ResetBits(GPIOA,GPIO_Pin_1)


#if(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_DISABLE)
	#define UPDS_MOS_TEMP_ADC 		(ADCConvertedRawData[2])

	#define UPDS_UDC_ADC					(ADCConvertedRawData[0])
	#define UPDS_IB_ADC						(ADCConvertedRawData[2])
	#define UPDS_EMPTY2_ADC				(ADCConvertedRawData[4])
	
//	#define UPDS_EMPTY1_ADC				(ADCConvertedRawData[1])

	#define UPDS_IDC_ADC					(ADCConvertedRawData[1])
	#define UPDS_IA_ADC						(ADCConvertedRawData[3])	
	#define UPDS_IDC_LPF_ADC			(ADCConvertedRawData[5])

	#define UPDS_VSP_ADC					(4095)
#elif(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_ENABLE)	
	#define UPDS_VBN_MEAS_ADC			(ADCConvertedRawData[0])
	#define UPDS_VAN_MEAS_ADC			(ADCConvertedRawData[2])	
	#define UPDS_MOS_TEMP_ADC			(ADCConvertedRawData[4]) 		
	#define UPDS_IB_ADC						(ADCConvertedRawData[6])						
	#define UPDS_UDC_ADC					(ADCConvertedRawData[8])								

	#define UPDS_VSP_ADC					(ADCConvertedRawData[1])
	#define UPDS_IA_ADC						(ADCConvertedRawData[3])
	#define UPDS_IDC_ADC					(ADCConvertedRawData[5])
	#define UPDS_IDC_LPF_ADC			(ADCConvertedRawData[7])
	#define UPDS_VCN_MEAS_ADC			(ADCConvertedRawData[9])
#endif

/*****************CUR_LIMLT使能******************/
#define UPDS_CUR_LIMLT_DISABLE			(0)
#define UPDS_CUR_LIMLT_ENABLE				(1)
#define UPDS_CUR_LIMLT_EN_SEL				(UPDS_CUR_LIMLT_ENABLE)

#define UPDS_CUR_LIMLT_MIN					_IQ(0.1)//低速限流电流，标幺值，相对IB
#define UPDS_CUR_LIMLT_SPD_WL				_IQ(0.1)//限流曲线低速度点
#define UPDS_CUR_LIMLT_SPD_WH				_IQ(0.2)//限流曲线高速度点

#define UPDS_UV_FLASHWRITE_10MS		(u16)(UPDS_PWM_FREQ/100)

#define UPDS_ERROR_EMERGENCY				(UPDS_SYS_TICK_FREQ)
#define UPDS_ERROR_NOT_EMERGENCY		(UPDS_SYS_TICK_FREQ) 

/*****************FG速度显示使能******************/
#define UPDS_FG_DISABLE							(0)			
#define UPDS_FG_ENABLE							(1)			
#define UPDS_FG_SEL									(UPDS_FG_DISABLE)

/**************Keil固定值调速***********************/
#define UPDS_KEILVALUE        				(u32)(0.99*0x7FFF)

/**********************PUMP***********************/
//恒电流功能使能
#define UPDS_CONCURRENT_DISABLE				(0)			
#define UPDS_CONCURRENT_ENABLE				(1)			
#define UPDS_CONCURRENT_SEL						(UPDS_CONCURRENT_DISABLE)

//缺水保护使能
#define UPDS_NOWATER_DISABLE					(0)			
#define UPDS_NOWATER_ENABLE						(1)			
#define UPDS_NOWATER_SEL							(UPDS_NOWATER_ENABLE)

//缺水保护
#define UPDS_NOWATER_JUDGETIME			(u32)(UPDS_NOWATER_TIME_S*UPDS_ERROR_EMERGENCY)

#define	UPDS_NWONE_VOLLOW_IQ12			(u32)(UPDS_NWONE_VOLLOW_V/UPDS_UDC_REAL*UPDS_SQRT3*0x1000)
#define UPDS_NWONE_VOLHIGH_IQ12			(u32)(UPDS_NWONE_VOLHIGH_V/UPDS_UDC_REAL*UPDS_SQRT3*0x1000)
#define UPDS_NWONE_UDCVALUE         (u32)(UPSD_POWER_MAX*UPDS_SAMPLE_VOLT_OP_GAIN/UPDS_NWONE_CUR_A/UPDS_SAMPLE_AD_MAX*0x1000)
#define	UPDS_NWTWO_VOLLOW_IQ12			(u32)(UPDS_NWTWO_VOLLOW_V/UPDS_UDC_REAL*UPDS_SQRT3*0x1000)
#define UPDS_NWTWO_VOLHIGH_IQ12			(u32)(UPDS_NWTWO_VOLHIGH_V/UPDS_UDC_REAL*UPDS_SQRT3*0x1000)
#define UPDS_NWTWO_UDCVALUE         (u32)(UPSD_POWER_MAX*UPDS_SAMPLE_VOLT_OP_GAIN/UPDS_NWTWO_CUR_A/UPDS_SAMPLE_AD_MAX*0x1000)
#define	UPDS_NWTHREE_VOLLOW_IQ12		(u32)(UPDS_NWTHREE_VOLLOW_V/UPDS_UDC_REAL*UPDS_SQRT3*0x1000)
#define UPDS_NWTHREE_VOLHIGH_IQ12		(u32)(UPDS_NWTHREE_VOLHIGH_V/UPDS_UDC_REAL*UPDS_SQRT3*0x1000)
#define UPDS_NWTHREE_UDCVALUE       (u32)(UPSD_POWER_MAX*UPDS_SAMPLE_VOLT_OP_GAIN/UPDS_NWTHREE_CUR_A/UPDS_SAMPLE_AD_MAX*0x1000)

/**********************刹车**********************/
#define UPDS_BREAK_UDCVALUE       	(u32)(UPSD_POWER_MAX*UPDS_SAMPLE_VOLT_OP_GAIN/(0.5)/UPDS_SAMPLE_AD_MAX*0x1000)
#define UPDS_UDC_KP									_IQ(0.5)			//母线电压Udc的PI参数
#define UPDS_UDC_KI									_IQ(0.002)
#define UPDS_UDC_MAX_V					    (UPDS_NWTHREE_VOLHIGH_V)
#define UPDS_IDC_MAX                _IQ(0.600)
#define UPDS_IDC_MIN					      _IQ(0.00)
#define UPDS_UDC_COMMAND    				_IQ(UPDS_UDC_MAX_V/UPDS_UB)

/*********************MTPA***********************/
#define UPDS_PHIDIVL								((f32)UPDS_PSI_REAL/2/UPDS_IB/(UPDS_LQ_REAL-UPDS_LD_REAL))
#define UPDS_MTPAMAX								(0.0f)
#define UPDS_MTPAMIN								(-0.3f)

//D轴电流控制策略选择
#define UPDS_DCURRENT_ZERO					(0)			//id=0
#define UPDS_DCURRENT_FW						(1)			//弱磁
#define UPDS_DCURRENT_MTPA					(2)			//MTPA
#define UPDS_DCURRENT_CHOOSE      	(UPDS_DCURRENT_FW)

#endif
