#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "pmsm_foc_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "pmsm_foc.h"
#include "pmsm_foc_capi.h"
#include "pmsm_foc_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 1 , TARGET_STRING (
"pmsm_foc/MATLAB Function" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , {
1 , 1 , TARGET_STRING ( "pmsm_foc/MATLAB Function" ) , TARGET_STRING ( "" ) ,
1 , 0 , 0 , 0 , 0 } , { 2 , 2 , TARGET_STRING ( "pmsm_foc/MATLAB Function1" )
, TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 3 , 3 , TARGET_STRING (
"pmsm_foc/MATLAB Function2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 4 , 3 , TARGET_STRING ( "pmsm_foc/MATLAB Function2" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 0 } , { 5 , 4 , TARGET_STRING (
"pmsm_foc/MATLAB Function3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 6 , 4 , TARGET_STRING ( "pmsm_foc/MATLAB Function3" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 0 } , { 7 , 4 , TARGET_STRING (
"pmsm_foc/MATLAB Function3" ) , TARGET_STRING ( "" ) , 2 , 0 , 0 , 0 , 0 } ,
{ 8 , 5 , TARGET_STRING ( "pmsm_foc/MATLAB Function4" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 9 , 5 , TARGET_STRING (
"pmsm_foc/MATLAB Function4" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } ,
{ 10 , 5 , TARGET_STRING ( "pmsm_foc/MATLAB Function4" ) , TARGET_STRING ( ""
) , 2 , 0 , 0 , 0 , 0 } , { 11 , 5 , TARGET_STRING (
"pmsm_foc/MATLAB Function4" ) , TARGET_STRING ( "" ) , 3 , 0 , 0 , 0 , 0 } ,
{ 12 , 5 , TARGET_STRING ( "pmsm_foc/MATLAB Function4" ) , TARGET_STRING ( ""
) , 4 , 0 , 0 , 0 , 0 } , { 13 , 5 , TARGET_STRING (
"pmsm_foc/MATLAB Function4" ) , TARGET_STRING ( "" ) , 5 , 0 , 0 , 0 , 0 } ,
{ 14 , 6 , TARGET_STRING ( "pmsm_foc/MATLAB Function5" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 15 , 6 , TARGET_STRING (
"pmsm_foc/MATLAB Function5" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 1 } ,
{ 16 , 0 , TARGET_STRING ( "pmsm_foc/Repeating Sequence/Output" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 17 , 0 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Discrete-Time Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 18 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Fcn" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 19 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 20 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Gain2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 21 , 0 , TARGET_STRING (
"pmsm_foc/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "" ) , 0
, 0 , 1 , 0 , 1 } , { 22 , 0 , TARGET_STRING (
"pmsm_foc/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING ( "" ) , 1
, 0 , 2 , 0 , 1 } , { 23 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/qd2abc/Fcn" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 24 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/qd2abc/Fcn1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 25 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/qd2abc/Sum" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 26 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/id/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 27 , 0 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/iq/Sum1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 28 , TARGET_STRING ( "pmsm_foc/DC Voltage Source"
) , TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 29 , TARGET_STRING (
"pmsm_foc/Repeating Sequence" ) , TARGET_STRING ( "rep_seq_y" ) , 0 , 3 , 0 }
, { 30 , TARGET_STRING ( "pmsm_foc/Repeating Sequence1" ) , TARGET_STRING (
"rep_seq_y" ) , 0 , 4 , 0 } , { 31 , TARGET_STRING ( "pmsm_foc/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 32 , TARGET_STRING (
"pmsm_foc/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 33 ,
TARGET_STRING ( "pmsm_foc/ud" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , {
34 , TARGET_STRING ( "pmsm_foc/uq" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0
} , { 35 , TARGET_STRING ( "pmsm_foc/Gain" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 36 , TARGET_STRING ( "pmsm_foc/Repeating Sequence/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 37 , TARGET_STRING (
"pmsm_foc/Repeating Sequence/Look-Up Table1" ) , TARGET_STRING (
"BreakpointsForDimension1" ) , 0 , 3 , 0 } , { 38 , TARGET_STRING (
"pmsm_foc/Repeating Sequence1/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 39 , TARGET_STRING ( "pmsm_foc/Repeating Sequence1/Look-Up Table1"
) , TARGET_STRING ( "BreakpointsForDimension1" ) , 0 , 4 , 0 } , { 40 ,
TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Coulomb & Viscous Friction"
) , TARGET_STRING ( "offset" ) , 0 , 0 , 0 } , { 41 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Coulomb & Viscous Friction"
) , TARGET_STRING ( "gain" ) , 0 , 0 , 0 } , { 42 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 43 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Discrete-Time Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 44 , TARGET_STRING
(
 "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Discrete-Time Integrator1"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 45 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Discrete-Time Integrator1"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 46 , TARGET_STRING
( "pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 47 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Mechanical model/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 48 , TARGET_STRING (
"pmsm_foc/powergui/EquivalentModel1/State-Space" ) , TARGET_STRING (
"DS_param" ) , 0 , 5 , 0 } , { 49 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/id/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 50 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/id/Discrete-Time Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 51 , TARGET_STRING
(
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/id/1//Ld"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 52 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/id/Lq//Ld"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 53 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/id/R//Ld"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 54 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/iq/Discrete-Time Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 55 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/iq/Discrete-Time Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 56 , TARGET_STRING
(
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/iq/1//Lq"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 57 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/iq/Ld//Lq"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 58 , TARGET_STRING (
"pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/iq/R//Lq"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 59 , TARGET_STRING (
 "pmsm_foc/Permanent Magnet Synchronous Machine/Electrical model/iq,id/iq/lam//Lq"
) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 ,
0 , 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 ,
( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 0 , ( NULL ) , 0 , 0 , 0
} } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . aspso4mzoh , & rtB . j5evttblx5 ,
& rtB . lilkkvgaic , & rtB . haxxbfz3k0 , & rtB . hpsqvahugn , & rtB .
kemy5ryk2k , & rtB . m3f2n4vpyl , & rtB . nwskhv4rus , & rtB . ms0b4pxmzb , &
rtB . dnislama02 , & rtB . hvzkwf4kwy , & rtB . bhyq5he0ha , & rtB .
fn0xh01ydm , & rtB . adpucdrk5e , & rtB . mqgxorietc , & rtB . pu5kcmmaam , &
rtB . ae2uv1iktz , & rtB . jifstquyy4 , & rtB . nngk2svk5e , & rtB .
d3oq2drobe , & rtB . dzr5dszhnp , & rtB . f355cx053z [ 0 ] , & rtB .
bggbcsplfd [ 0 ] , & rtB . folm1hpmtc , & rtB . d5dfrizf0n , & rtB .
hxq0cge2eb , & rtB . myvep3thod , & rtB . iywefczj2o , & rtP .
DCVoltageSource_Amplitude , & rtP . RepeatingSequence_rep_seq_y [ 0 ] , & rtP
. RepeatingSequence1_rep_seq_y [ 0 ] , & rtP . Constant_Value , & rtP .
Constant1_Value , & rtP . ud_Value , & rtP . uq_Value , & rtP . Gain_Gain , &
rtP . Constant_Value_gcz0x5uvvw , & rtP . LookUpTable1_bp01Data [ 0 ] , & rtP
. Constant_Value_jej44c3gbw , & rtP . LookUpTable1_bp01Data_lskm2xz5pt [ 0 ]
, & rtP . CoulombViscousFriction_offset , & rtP . CoulombViscousFriction_gain
, & rtP . DiscreteTimeIntegrator_gainval_baspqawaub , & rtP .
DiscreteTimeIntegrator_IC_m0pormlr1l , & rtP .
DiscreteTimeIntegrator1_gainval , & rtP . DiscreteTimeIntegrator1_IC , & rtP
. Gain_Gain_iihdl234dr , & rtP . Gain2_Gain , & rtP . StateSpace_DS_param [ 0
] , & rtP . DiscreteTimeIntegrator_gainval_fvzrflbktk , & rtP .
DiscreteTimeIntegrator_IC_hkwqbnxdqc , & rtP . uLd_Gain , & rtP . LqLd_Gain ,
& rtP . RLd_Gain , & rtP . DiscreteTimeIntegrator_gainval , & rtP .
DiscreteTimeIntegrator_IC , & rtP . uLq_Gain , & rtP . LdLq_Gain , & rtP .
RLq_Gain , & rtP . lamLq_Gain , } ; static int32_T * rtVarDimsAddrMap [ ] = {
( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 , 0 } , { "float" ,
"real32_T" , 0 , 0 , sizeof ( real32_T ) , SS_SINGLE , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , {
rtwCAPI_VECTOR , 8 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 10 , 2 , 0 } } ;
static const uint_T rtDimensionArray [ ] = { 1 , 1 , 8 , 1 , 6 , 1 , 1 , 3 ,
1 , 2 , 8 , 9 } ; static const real_T rtcapiStoredFloats [ ] = { 0.0 , 1.0E-6
} ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const rtwCAPI_SampleTimeMap
rtSampleTimeMap [ ] = { { ( const void * ) & rtcapiStoredFloats [ 0 ] , (
const void * ) & rtcapiStoredFloats [ 0 ] , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 1 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , 2 ,
0 } } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals
, 28 , rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 32 ,
rtModelParameters , 0 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap
, rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float"
, { 3708514171U , 3344188691U , 2449843500U , 992344854U } , ( NULL ) , 0 , 0
, rt_LoggedStateIdxList } ; const rtwCAPI_ModelMappingStaticInfo *
pmsm_foc_GetCAPIStaticMap ( void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void pmsm_foc_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void pmsm_foc_host_InitializeDataMapInfo ( pmsm_foc_host_DataMapInfo_T *
dataMap , const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ;
rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ;
rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
