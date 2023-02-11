#ifndef RTW_HEADER_pmsm_foc_h_
#define RTW_HEADER_pmsm_foc_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap_simtarget.h"
#ifndef pmsm_foc_COMMON_INCLUDES_
#define pmsm_foc_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "pmsm_foc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME pmsm_foc
#define NSAMPLE_TIMES (4) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (28) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T folm1hpmtc ; real_T d5dfrizf0n ; real_T f355cx053z [
8 ] ; real_T bggbcsplfd [ 6 ] ; real_T hxq0cge2eb ; real_T nngk2svk5e ;
real_T jifstquyy4 ; real_T d3oq2drobe ; real_T myvep3thod ; real_T iywefczj2o
; real_T dzr5dszhnp ; real_T ae2uv1iktz ; real_T mqgxorietc ; real_T
pu5kcmmaam ; real_T ms0b4pxmzb ; real_T dnislama02 ; real_T hvzkwf4kwy ;
real_T bhyq5he0ha ; real_T fn0xh01ydm ; real_T adpucdrk5e ; real_T kemy5ryk2k
; real_T m3f2n4vpyl ; real_T nwskhv4rus ; real_T haxxbfz3k0 ; real_T
hpsqvahugn ; real_T aspso4mzoh ; real_T j5evttblx5 ; real32_T lilkkvgaic ; }
B ; typedef struct { real_T gprmqx2cbw ; real_T a5n05qvuz0 ; real_T
mxboqf3skh ; real_T a5yx3v2fjf ; struct { void * AS ; void * BS ; void * CS ;
void * DS ; void * DX_COL ; void * BD_COL ; void * TMP1 ; void * TMP2 ; void
* XTMP ; void * SWITCH_STATUS ; void * SWITCH_STATUS_INIT ; void * SW_CHG ;
void * G_STATE ; void * USWLAST ; void * XKM12 ; void * XKP12 ; void * XLAST
; void * ULAST ; void * IDX_SW_CHG ; void * Y_SWITCH ; void * SWITCH_TYPES ;
void * IDX_OUT_SW ; void * SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; }
kurfkteue0 ; struct { void * LoggedData [ 3 ] ; } froshap0ev ; struct { void
* LoggedData [ 2 ] ; } nnh5tabexs ; struct { void * LoggedData [ 2 ] ; }
pdvcco4hx3 ; struct { void * LoggedData ; } ebdj120vsx ; struct { void *
LoggedData [ 2 ] ; } cahjpjtsy0 ; struct { void * LoggedData ; } my2ngnaiye ;
struct { void * LoggedData ; } li3rp4t4vq ; struct { void * LoggedData ; }
ibwxqslxua ; struct { void * LoggedData [ 2 ] ; } hnmz3t3prs ; int_T
khbtd0f5vb [ 11 ] ; uint8_T moc2zlrmo5 ; uint8_T oug1x01dyp ; uint8_T
c5nse2xfsg ; uint8_T dcrnppafnr ; } DW ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T
DCVoltageSource_Amplitude ; real_T CoulombViscousFriction_gain ; real_T
CoulombViscousFriction_offset ; real_T RepeatingSequence_rep_seq_y [ 3 ] ;
real_T RepeatingSequence1_rep_seq_y [ 2 ] ; real_T
DiscreteTimeIntegrator1_gainval ; real_T DiscreteTimeIntegrator1_IC ; real_T
DiscreteTimeIntegrator_gainval ; real_T DiscreteTimeIntegrator_IC ; real_T
DiscreteTimeIntegrator_gainval_fvzrflbktk ; real_T
DiscreteTimeIntegrator_IC_hkwqbnxdqc ; real_T StateSpace_DS_param [ 72 ] ;
real_T DiscreteTimeIntegrator_gainval_baspqawaub ; real_T
DiscreteTimeIntegrator_IC_m0pormlr1l ; real_T Gain_Gain ; real_T uLd_Gain ;
real_T Gain_Gain_iihdl234dr ; real_T LqLd_Gain ; real_T RLd_Gain ; real_T
uLq_Gain ; real_T LdLq_Gain ; real_T RLq_Gain ; real_T lamLq_Gain ; real_T
Gain2_Gain ; real_T LookUpTable1_bp01Data [ 3 ] ; real_T
LookUpTable1_bp01Data_lskm2xz5pt [ 2 ] ; real_T Constant_Value ; real_T
Constant1_Value ; real_T ud_Value ; real_T uq_Value ; real_T
Constant_Value_gcz0x5uvvw ; real_T Constant_Value_jej44c3gbw ; } ; extern
const real_T pmsm_foc_RGND ; extern const char * RT_MEMORY_ALLOCATION_ERROR ;
extern B rtB ; extern DW rtDW ; extern P rtP ; extern mxArray *
mr_pmsm_foc_GetDWork ( ) ; extern void mr_pmsm_foc_SetDWork ( const mxArray *
ssDW ) ; extern mxArray * mr_pmsm_foc_GetSimStateDisallowedBlocks ( ) ;
extern const rtwCAPI_ModelMappingStaticInfo * pmsm_foc_GetCAPIStaticMap (
void ) ; extern SimStruct * const rtS ; extern const int_T gblNumToFiles ;
extern const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ;
extern rtInportTUtable * gblInportTUtables ; extern const char *
gblInportFileName ; extern const int_T gblNumRootInportBlks ; extern const
int_T gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ;
extern const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [
] ; extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif
