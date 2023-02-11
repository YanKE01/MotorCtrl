#include "rt_logging_mmi.h"
#include "pmsm_foc_capi.h"
#include <math.h>
#include "pmsm_foc.h"
#include "pmsm_foc_private.h"
#include "pmsm_foc_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , & stopRequested ) ; }
rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 4 ; const char_T
* gbl_raccel_Version = "9.5 (R2021a) 14-Nov-2020" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 0 ; const int_T
gblNumModelInputs = 0 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ - 1 } ; const int_T gblInportDims [ ] = { - 1 } ; const int_T
gblInportComplex [ ] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1
} ; const int_T gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [
] = { 1 , 1 , 1 , 1 } ; const char * raccelLoadInputsAndAperiodicHitTimes (
SimStruct * S , const char * inportFileName , int * matFileFormat ) { return
rt_RAccelReadInportsMatFile ( S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
const real_T pmsm_foc_RGND = 0.0 ; B rtB ; DW rtDW ; static SimStruct model_S
; SimStruct * const rtS = & model_S ; real_T look1_binlxpw ( real_T u0 ,
const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) { real_T
frac ; real_T yL_0d0 ; uint32_T bpIdx ; uint32_T iLeft ; uint32_T iRght ; if
( u0 <= bp0 [ 0U ] ) { iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ]
- bp0 [ 0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) { bpIdx = maxIndex >> 1U
; iLeft = 0U ; iRght = maxIndex ; while ( iRght - iLeft > 1U ) { if ( u0 <
bp0 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; } bpIdx = ( iRght
+ iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [ iLeft + 1U ] -
bp0 [ iLeft ] ) ; } else { iLeft = maxIndex - 1U ; frac = ( u0 - bp0 [
maxIndex - 1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; } yL_0d0 =
table [ iLeft ] ; return ( table [ iLeft + 1U ] - yL_0d0 ) * frac + yL_0d0 ;
} void MdlInitialize ( void ) { rtDW . gprmqx2cbw = rtP .
DiscreteTimeIntegrator1_IC ; rtDW . a5n05qvuz0 = rtP .
DiscreteTimeIntegrator_IC ; rtDW . mxboqf3skh = rtP .
DiscreteTimeIntegrator_IC_hkwqbnxdqc ; { int32_T i , j ; real_T * Ds = (
real_T * ) rtDW . kurfkteue0 . DS ; for ( i = 0 ; i < 8 ; i ++ ) { for ( j =
0 ; j < 9 ; j ++ ) Ds [ i * 9 + j ] = ( rtP . StateSpace_DS_param [ i + j * 8
] ) ; } { int_T * switch_status = ( int_T * ) rtDW . kurfkteue0 .
SWITCH_STATUS ; int_T * gState = ( int_T * ) rtDW . kurfkteue0 . G_STATE ;
real_T * yswitch = ( real_T * ) rtDW . kurfkteue0 . Y_SWITCH ; int_T *
switchTypes = ( int_T * ) rtDW . kurfkteue0 . SWITCH_TYPES ; int_T * idxOutSw
= ( int_T * ) rtDW . kurfkteue0 . IDX_OUT_SW ; int_T * switch_status_init = (
int_T * ) rtDW . kurfkteue0 . SWITCH_STATUS_INIT ; switch_status [ 0 ] = 0 ;
switch_status_init [ 0 ] = 0 ; gState [ 0 ] = ( int_T ) 0.0 ; yswitch [ 0 ] =
1 / 0.001 ; switchTypes [ 0 ] = ( int_T ) 7.0 ; idxOutSw [ 0 ] = ( ( int_T )
0.0 ) - 1 ; switch_status [ 1 ] = 0 ; switch_status_init [ 1 ] = 0 ; gState [
1 ] = ( int_T ) 0.0 ; yswitch [ 1 ] = 1 / 0.001 ; switchTypes [ 1 ] = ( int_T
) 7.0 ; idxOutSw [ 1 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 2 ] = 0 ;
switch_status_init [ 2 ] = 0 ; gState [ 2 ] = ( int_T ) 0.0 ; yswitch [ 2 ] =
1 / 0.001 ; switchTypes [ 2 ] = ( int_T ) 7.0 ; idxOutSw [ 2 ] = ( ( int_T )
0.0 ) - 1 ; switch_status [ 3 ] = 0 ; switch_status_init [ 3 ] = 0 ; gState [
3 ] = ( int_T ) 0.0 ; yswitch [ 3 ] = 1 / 0.001 ; switchTypes [ 3 ] = ( int_T
) 7.0 ; idxOutSw [ 3 ] = ( ( int_T ) 0.0 ) - 1 ; switch_status [ 4 ] = 0 ;
switch_status_init [ 4 ] = 0 ; gState [ 4 ] = ( int_T ) 0.0 ; yswitch [ 4 ] =
1 / 0.001 ; switchTypes [ 4 ] = ( int_T ) 7.0 ; idxOutSw [ 4 ] = ( ( int_T )
0.0 ) - 1 ; switch_status [ 5 ] = 0 ; switch_status_init [ 5 ] = 0 ; gState [
5 ] = ( int_T ) 0.0 ; yswitch [ 5 ] = 1 / 0.001 ; switchTypes [ 5 ] = ( int_T
) 7.0 ; idxOutSw [ 5 ] = ( ( int_T ) 0.0 ) - 1 ; } } rtDW . a5yx3v2fjf = rtP
. DiscreteTimeIntegrator_IC_m0pormlr1l ; } void MdlStart ( void ) { { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} rtDW . moc2zlrmo5 = 0U ; rtDW . oug1x01dyp = 0U ; rtDW . c5nse2xfsg = 0U ;
{ rtDW . kurfkteue0 . DS = ( real_T * ) calloc ( 8 * 9 , sizeof ( real_T ) )
; rtDW . kurfkteue0 . DX_COL = ( real_T * ) calloc ( 8 , sizeof ( real_T ) )
; rtDW . kurfkteue0 . TMP2 = ( real_T * ) calloc ( 9 , sizeof ( real_T ) ) ;
rtDW . kurfkteue0 . SWITCH_STATUS = ( int_T * ) calloc ( 6 , sizeof ( int_T )
) ; rtDW . kurfkteue0 . SW_CHG = ( int_T * ) calloc ( 6 , sizeof ( int_T ) )
; rtDW . kurfkteue0 . G_STATE = ( int_T * ) calloc ( 6 , sizeof ( int_T ) ) ;
rtDW . kurfkteue0 . Y_SWITCH = ( real_T * ) calloc ( 6 , sizeof ( real_T ) )
; rtDW . kurfkteue0 . SWITCH_TYPES = ( int_T * ) calloc ( 6 , sizeof ( int_T
) ) ; rtDW . kurfkteue0 . IDX_OUT_SW = ( int_T * ) calloc ( 6 , sizeof (
int_T ) ) ; rtDW . kurfkteue0 . SWITCH_STATUS_INIT = ( int_T * ) calloc ( 6 ,
sizeof ( int_T ) ) ; rtDW . kurfkteue0 . USWLAST = ( real_T * ) calloc ( 6 ,
sizeof ( real_T ) ) ; } rtDW . dcrnppafnr = 0U ; MdlInitialize ( ) ; } void
MdlOutputs ( int_T tid ) { real_T Ttemp ; real_T djnq5n2yhg ; real_T
ioq5vo300m ; int32_T sector ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) {
muDoubleScalarSinCos ( rtDW . gprmqx2cbw , & djnq5n2yhg , & ioq5vo300m ) ;
rtB . folm1hpmtc = rtDW . a5n05qvuz0 * ioq5vo300m + rtDW . mxboqf3skh *
djnq5n2yhg ; rtB . d5dfrizf0n = ( ( - rtDW . a5n05qvuz0 - 1.7320508075688772
* rtDW . mxboqf3skh ) * ioq5vo300m + ( 1.7320508075688772 * rtDW . a5n05qvuz0
- rtDW . mxboqf3skh ) * djnq5n2yhg ) * 0.5 ; { real_T accum ; int_T *
switch_status = ( int_T * ) rtDW . kurfkteue0 . SWITCH_STATUS ; int_T *
switch_status_init = ( int_T * ) rtDW . kurfkteue0 . SWITCH_STATUS_INIT ;
int_T * SwitchChange = ( int_T * ) rtDW . kurfkteue0 . SW_CHG ; int_T *
gState = ( int_T * ) rtDW . kurfkteue0 . G_STATE ; real_T * yswitch = (
real_T * ) rtDW . kurfkteue0 . Y_SWITCH ; int_T * switchTypes = ( int_T * )
rtDW . kurfkteue0 . SWITCH_TYPES ; int_T * idxOutSw = ( int_T * ) rtDW .
kurfkteue0 . IDX_OUT_SW ; real_T * DxCol = ( real_T * ) rtDW . kurfkteue0 .
DX_COL ; real_T * tmp2 = ( real_T * ) rtDW . kurfkteue0 . TMP2 ; real_T *
uswlast = ( real_T * ) rtDW . kurfkteue0 . USWLAST ; int_T newState ; int_T
swChanged = 0 ; int loopsToDo = 20 ; real_T temp ; memcpy (
switch_status_init , switch_status , 6 * sizeof ( int_T ) ) ; memcpy (
uswlast , & rtB . f355cx053z [ 0 ] , 6 * sizeof ( real_T ) ) ; do { if (
loopsToDo == 1 ) { swChanged = 0 ; { int_T i1 ; for ( i1 = 0 ; i1 < 6 ; i1 ++
) { swChanged = ( ( SwitchChange [ i1 ] = switch_status_init [ i1 ] -
switch_status [ i1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ i1 ] =
switch_status_init [ i1 ] ; } } } else { real_T * Ds = ( real_T * ) rtDW .
kurfkteue0 . DS ; { int_T i1 ; real_T * y0 = & rtB . f355cx053z [ 0 ] ; for (
i1 = 0 ; i1 < 8 ; i1 ++ ) { accum = 0.0 ; { int_T i2 ; const real_T * u0 ;
for ( i2 = 0 ; i2 < 6 ; i2 ++ ) { accum += * ( Ds ++ ) * 0.0 ; } accum += * (
Ds ++ ) * rtB . folm1hpmtc ; accum += * ( Ds ++ ) * rtB . d5dfrizf0n ; accum
+= * ( Ds ++ ) * rtP . DCVoltageSource_Amplitude ; } y0 [ i1 ] = accum ; } }
swChanged = 0 ; { int_T i1 ; real_T * y0 = & rtB . f355cx053z [ 0 ] ; for (
i1 = 0 ; i1 < 6 ; i1 ++ ) { newState = ( ( y0 [ i1 ] > 0.0 ) && ( gState [ i1
] > 0 ) ) || ( y0 [ i1 ] < 0.0 ) ? 1 : ( ( ( y0 [ i1 ] > 0.0 ) && gState [ i1
] == 0 ) ? 0 : switch_status [ i1 ] ) ; swChanged = ( ( SwitchChange [ i1 ] =
newState - switch_status [ i1 ] ) != 0 ) ? 1 : swChanged ; switch_status [ i1
] = newState ; } } } if ( swChanged ) { real_T * Ds = ( real_T * ) rtDW .
kurfkteue0 . DS ; real_T a1 ; { int_T i1 ; for ( i1 = 0 ; i1 < 6 ; i1 ++ ) {
if ( SwitchChange [ i1 ] != 0 ) { a1 = 1000.0 * SwitchChange [ i1 ] ; temp =
1 / ( 1 - Ds [ i1 * 10 ] * a1 ) ; { int_T i2 ; for ( i2 = 0 ; i2 < 8 ; i2 ++
) { DxCol [ i2 ] = Ds [ i2 * 9 + i1 ] * temp * a1 ; } } DxCol [ i1 ] = temp ;
memcpy ( tmp2 , & Ds [ i1 * 9 ] , 9 * sizeof ( real_T ) ) ; memset ( & Ds [
i1 * 9 ] , '\0' , 9 * sizeof ( real_T ) ) ; { int_T i2 ; for ( i2 = 0 ; i2 <
8 ; i2 ++ ) { a1 = DxCol [ i2 ] ; { int_T i3 ; for ( i3 = 0 ; i3 < 9 ; i3 ++
) { Ds [ i2 * 9 + i3 ] += a1 * tmp2 [ i3 ] ; } } } } } } } } } while (
swChanged > 0 && -- loopsToDo > 0 ) ; if ( loopsToDo == 0 ) { real_T * Ds = (
real_T * ) rtDW . kurfkteue0 . DS ; { int_T i1 ; real_T * y0 = & rtB .
f355cx053z [ 0 ] ; for ( i1 = 0 ; i1 < 8 ; i1 ++ ) { accum = 0.0 ; { int_T i2
; const real_T * u0 ; for ( i2 = 0 ; i2 < 6 ; i2 ++ ) { accum += * ( Ds ++ )
* 0.0 ; } accum += * ( Ds ++ ) * rtB . folm1hpmtc ; accum += * ( Ds ++ ) *
rtB . d5dfrizf0n ; accum += * ( Ds ++ ) * rtP . DCVoltageSource_Amplitude ; }
y0 [ i1 ] = accum ; } } } { int_T i1 ; real_T * y1 = & rtB . bggbcsplfd [ 0 ]
; for ( i1 = 0 ; i1 < 6 ; i1 ++ ) { y1 [ i1 ] = ( real_T ) switch_status [ i1
] ; } } } rtB . hxq0cge2eb = ( 0.0 - rtB . d5dfrizf0n ) - rtB . folm1hpmtc ;
rtB . nngk2svk5e = rtDW . gprmqx2cbw - 1.5707963267948966 ; rtB . jifstquyy4
= rtDW . a5yx3v2fjf ; rtB . mqgxorietc = rtB . folm1hpmtc * 2.0 / 3.0 - ( rtB
. hxq0cge2eb + rtB . d5dfrizf0n ) / 3.0 ; rtB . pu5kcmmaam = ( rtB .
hxq0cge2eb - rtB . d5dfrizf0n ) * 1.7320508075688772 / 3.0 ; rtB . d3oq2drobe
= rtP . Gain_Gain_iihdl234dr * rtB . jifstquyy4 ; rtB . myvep3thod = ( ( (
2.0 * rtB . f355cx053z [ 6 ] + rtB . f355cx053z [ 7 ] ) * djnq5n2yhg + -
1.7320508075688772 * rtB . f355cx053z [ 7 ] * ioq5vo300m ) *
0.33333333333333331 * rtP . uLd_Gain - rtP . RLd_Gain * rtDW . mxboqf3skh ) +
rtB . d3oq2drobe * rtDW . a5n05qvuz0 * rtP . LqLd_Gain ; rtB . iywefczj2o = (
( ( ( 2.0 * rtB . f355cx053z [ 6 ] + rtB . f355cx053z [ 7 ] ) * ioq5vo300m +
1.7320508075688772 * rtB . f355cx053z [ 7 ] * djnq5n2yhg ) *
0.33333333333333331 * rtP . uLq_Gain - rtP . RLq_Gain * rtDW . a5n05qvuz0 ) -
rtDW . mxboqf3skh * rtB . d3oq2drobe * rtP . LdLq_Gain ) - rtP . lamLq_Gain *
rtB . d3oq2drobe ; rtB . dzr5dszhnp = ( ( 0.0 * rtDW . a5n05qvuz0 * rtDW .
mxboqf3skh + 0.034182 * rtDW . a5n05qvuz0 ) * 1.5 - ( rtP .
CoulombViscousFriction_offset * muDoubleScalarSign ( rtB . jifstquyy4 ) + rtP
. CoulombViscousFriction_gain * rtB . jifstquyy4 ) ) * rtP . Gain2_Gain ; }
rtB . ae2uv1iktz = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( rtS ) - 0.0 ,
rtP . Constant_Value_gcz0x5uvvw ) , rtP . LookUpTable1_bp01Data , rtP .
RepeatingSequence_rep_seq_y , 2U ) ; djnq5n2yhg = look1_binlxpw (
muDoubleScalarRem ( ssGetT ( rtS ) - 0.0 , rtP . Constant_Value_jej44c3gbw )
, rtP . LookUpTable1_bp01Data_lskm2xz5pt , rtP . RepeatingSequence1_rep_seq_y
, 1U ) ; rtB . aspso4mzoh = rtP . ud_Value * muDoubleScalarCos ( djnq5n2yhg )
- rtP . uq_Value * muDoubleScalarSin ( djnq5n2yhg ) ; rtB . j5evttblx5 = rtP
. ud_Value * muDoubleScalarSin ( djnq5n2yhg ) + rtP . uq_Value *
muDoubleScalarCos ( djnq5n2yhg ) ; sector = 0 ; if ( rtB . j5evttblx5 > 0.0 )
{ sector = 1 ; } if ( 0.8660254037844386 * rtB . aspso4mzoh - 0.5 * rtB .
j5evttblx5 > 0.0 ) { sector += 2 ; } if ( - 0.8660254037844386 * rtB .
aspso4mzoh - 0.5 * rtB . j5evttblx5 > 0.0 ) { sector += 4 ; } rtB .
lilkkvgaic = ( real32_T ) sector ; rtB . haxxbfz3k0 = 0.0 ; rtB . hpsqvahugn
= 0.0 ; switch ( ( int32_T ) rtB . lilkkvgaic ) { case 1 : rtB . haxxbfz3k0 =
1.7320508075688772 * rtP . Constant_Value / rtP . Constant1_Value * ( -
0.8660254037844386 * rtB . aspso4mzoh + 0.5 * rtB . j5evttblx5 ) ; rtB .
hpsqvahugn = 1.7320508075688772 * rtP . Constant_Value / rtP .
Constant1_Value * ( 0.8660254037844386 * rtB . aspso4mzoh + 0.5 * rtB .
j5evttblx5 ) ; break ; case 2 : rtB . haxxbfz3k0 = 1.7320508075688772 * rtP .
Constant_Value / rtP . Constant1_Value * ( 0.8660254037844386 * rtB .
aspso4mzoh + 0.5 * rtB . j5evttblx5 ) ; rtB . hpsqvahugn = - (
1.7320508075688772 * rtP . Constant_Value / rtP . Constant1_Value * rtB .
j5evttblx5 ) ; break ; case 3 : rtB . haxxbfz3k0 = - ( 1.7320508075688772 *
rtP . Constant_Value / rtP . Constant1_Value * ( - 0.8660254037844386 * rtB .
aspso4mzoh + 0.5 * rtB . j5evttblx5 ) ) ; rtB . hpsqvahugn =
1.7320508075688772 * rtP . Constant_Value / rtP . Constant1_Value * rtB .
j5evttblx5 ; break ; case 4 : rtB . haxxbfz3k0 = - ( 1.7320508075688772 * rtP
. Constant_Value / rtP . Constant1_Value * rtB . j5evttblx5 ) ; rtB .
hpsqvahugn = 1.7320508075688772 * rtP . Constant_Value / rtP .
Constant1_Value * ( - 0.8660254037844386 * rtB . aspso4mzoh + 0.5 * rtB .
j5evttblx5 ) ; break ; case 5 : rtB . haxxbfz3k0 = 1.7320508075688772 * rtP .
Constant_Value / rtP . Constant1_Value * rtB . j5evttblx5 ; rtB . hpsqvahugn
= - ( 1.7320508075688772 * rtP . Constant_Value / rtP . Constant1_Value * (
0.8660254037844386 * rtB . aspso4mzoh + 0.5 * rtB . j5evttblx5 ) ) ; break ;
case 6 : rtB . haxxbfz3k0 = - ( 1.7320508075688772 * rtP . Constant_Value /
rtP . Constant1_Value * ( 0.8660254037844386 * rtB . aspso4mzoh + 0.5 * rtB .
j5evttblx5 ) ) ; rtB . hpsqvahugn = - ( 1.7320508075688772 * rtP .
Constant_Value / rtP . Constant1_Value * ( - 0.8660254037844386 * rtB .
aspso4mzoh + 0.5 * rtB . j5evttblx5 ) ) ; break ; } ioq5vo300m = rtB .
haxxbfz3k0 ; djnq5n2yhg = rtB . hpsqvahugn ; rtB . kemy5ryk2k = 0.0 ; rtB .
m3f2n4vpyl = 0.0 ; rtB . nwskhv4rus = 0.0 ; Ttemp = rtB . haxxbfz3k0 + rtB .
hpsqvahugn ; if ( Ttemp > rtP . Constant_Value ) { ioq5vo300m = rtB .
haxxbfz3k0 / Ttemp * rtP . Constant_Value ; djnq5n2yhg = rtB . hpsqvahugn /
Ttemp * rtP . Constant_Value ; } Ttemp = ( ( rtP . Constant_Value -
ioq5vo300m ) - djnq5n2yhg ) / 4.0 ; ioq5vo300m = ioq5vo300m / 2.0 + Ttemp ;
switch ( ( int32_T ) rtB . lilkkvgaic ) { case 1 : rtB . kemy5ryk2k =
ioq5vo300m ; rtB . m3f2n4vpyl = Ttemp ; rtB . nwskhv4rus = djnq5n2yhg / 2.0 +
ioq5vo300m ; break ; case 2 : rtB . kemy5ryk2k = Ttemp ; rtB . m3f2n4vpyl =
djnq5n2yhg / 2.0 + ioq5vo300m ; rtB . nwskhv4rus = ioq5vo300m ; break ; case
3 : rtB . kemy5ryk2k = Ttemp ; rtB . m3f2n4vpyl = ioq5vo300m ; rtB .
nwskhv4rus = djnq5n2yhg / 2.0 + ioq5vo300m ; break ; case 4 : rtB .
kemy5ryk2k = djnq5n2yhg / 2.0 + ioq5vo300m ; rtB . m3f2n4vpyl = ioq5vo300m ;
rtB . nwskhv4rus = Ttemp ; break ; case 5 : rtB . kemy5ryk2k = djnq5n2yhg /
2.0 + ioq5vo300m ; rtB . m3f2n4vpyl = Ttemp ; rtB . nwskhv4rus = ioq5vo300m ;
break ; case 6 : rtB . kemy5ryk2k = ioq5vo300m ; rtB . m3f2n4vpyl =
djnq5n2yhg / 2.0 + ioq5vo300m ; rtB . nwskhv4rus = Ttemp ; break ; } if ( rtB
. ae2uv1iktz < rtB . kemy5ryk2k ) { rtB . ms0b4pxmzb = 0.0 ; rtB . dnislama02
= 1.0 ; } else { rtB . ms0b4pxmzb = 1.0 ; rtB . dnislama02 = 0.0 ; } if ( rtB
. ae2uv1iktz < rtB . m3f2n4vpyl ) { rtB . hvzkwf4kwy = 0.0 ; rtB . bhyq5he0ha
= 1.0 ; } else { rtB . hvzkwf4kwy = 1.0 ; rtB . bhyq5he0ha = 0.0 ; } if ( rtB
. ae2uv1iktz < rtB . nwskhv4rus ) { rtB . fn0xh01ydm = 0.0 ; rtB . adpucdrk5e
= 1.0 ; } else { rtB . fn0xh01ydm = 1.0 ; rtB . adpucdrk5e = 0.0 ; }
UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID3 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid ) { if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . gprmqx2cbw += rtP .
DiscreteTimeIntegrator1_gainval * rtB . d3oq2drobe ; rtDW . a5n05qvuz0 += rtP
. DiscreteTimeIntegrator_gainval * rtB . iywefczj2o ; rtDW . mxboqf3skh +=
rtP . DiscreteTimeIntegrator_gainval_fvzrflbktk * rtB . myvep3thod ; { int_T
* gState = ( int_T * ) rtDW . kurfkteue0 . G_STATE ; * ( gState ++ ) = (
int_T ) rtB . ms0b4pxmzb ; * ( gState ++ ) = ( int_T ) rtB . dnislama02 ; * (
gState ++ ) = ( int_T ) rtB . hvzkwf4kwy ; * ( gState ++ ) = ( int_T ) rtB .
bhyq5he0ha ; * ( gState ++ ) = ( int_T ) rtB . fn0xh01ydm ; * ( gState ++ ) =
( int_T ) rtB . adpucdrk5e ; } rtDW . a5yx3v2fjf += rtP .
DiscreteTimeIntegrator_gainval_baspqawaub * rtB . dzr5dszhnp ; }
UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID3 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlTerminate ( void ) { { free ( rtDW .
kurfkteue0 . DS ) ; free ( rtDW . kurfkteue0 . DX_COL ) ; free ( rtDW .
kurfkteue0 . TMP2 ) ; free ( rtDW . kurfkteue0 . G_STATE ) ; free ( rtDW .
kurfkteue0 . SWITCH_STATUS ) ; free ( rtDW . kurfkteue0 . SW_CHG ) ; free (
rtDW . kurfkteue0 . SWITCH_STATUS_INIT ) ; } } static void
mr_pmsm_foc_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j ,
const void * srcData , size_t numBytes ) ; static void
mr_pmsm_foc_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j ,
const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_pmsm_foc_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static void
mr_pmsm_foc_restoreDataFromMxArray ( void * destData , const mxArray *
srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( ( uint8_T * )
destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber ( srcArray , i
, j ) ) , numBytes ) ; } static void mr_pmsm_foc_cacheBitFieldToMxArray (
mxArray * destArray , mwIndex i , int j , uint_T bitVal ) ; static void
mr_pmsm_foc_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i , int j
, uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j ,
mxCreateDoubleScalar ( ( double ) bitVal ) ) ; } static uint_T
mr_pmsm_foc_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex i
, int j , uint_T numBits ) ; static uint_T
mr_pmsm_foc_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex i
, int j , uint_T numBits ) { const uint_T varVal = ( uint_T ) mxGetScalar (
mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( ( 1u << numBits
) - 1u ) ; } static void mr_pmsm_foc_cacheDataToMxArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) ; static void mr_pmsm_foc_cacheDataToMxArrayWithOffset (
mxArray * destArray , mwIndex i , int j , mwIndex offset , const void *
srcData , size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_pmsm_foc_restoreDataFromMxArrayWithOffset ( void * destData , const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t numBytes ) ;
static void mr_pmsm_foc_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData (
mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData ,
( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static
void mr_pmsm_foc_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static void
mr_pmsm_foc_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , uint_T fieldVal ) { mxSetCell (
mxGetFieldByNumber ( destArray , i , j ) , offset , mxCreateDoubleScalar ( (
double ) fieldVal ) ) ; } static uint_T
mr_pmsm_foc_extractBitFieldFromCellArrayWithOffset ( const mxArray * srcArray
, mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static uint_T
mr_pmsm_foc_extractBitFieldFromCellArrayWithOffset ( const mxArray * srcArray
, mwIndex i , int j , mwIndex offset , uint_T numBits ) { const uint_T
fieldVal = ( uint_T ) mxGetScalar ( mxGetCell ( mxGetFieldByNumber ( srcArray
, i , j ) , offset ) ) ; return fieldVal & ( ( 1u << numBits ) - 1u ) ; }
mxArray * mr_pmsm_foc_GetDWork ( ) { static const char * ssDWFieldNames [ 3 ]
= { "rtB" , "rtDW" , "NULL_PrevZCX" , } ; mxArray * ssDW =
mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_pmsm_foc_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & ( rtB ) ,
sizeof ( rtB ) ) ; { static const char * rtdwDataFieldNames [ 9 ] = {
"rtDW.gprmqx2cbw" , "rtDW.a5n05qvuz0" , "rtDW.mxboqf3skh" , "rtDW.a5yx3v2fjf"
, "rtDW.khbtd0f5vb" , "rtDW.moc2zlrmo5" , "rtDW.oug1x01dyp" ,
"rtDW.c5nse2xfsg" , "rtDW.dcrnppafnr" , } ; mxArray * rtdwData =
mxCreateStructMatrix ( 1 , 1 , 9 , rtdwDataFieldNames ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 0 , ( const void * ) & ( rtDW
. gprmqx2cbw ) , sizeof ( rtDW . gprmqx2cbw ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) & ( rtDW
. a5n05qvuz0 ) , sizeof ( rtDW . a5n05qvuz0 ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) & ( rtDW
. mxboqf3skh ) , sizeof ( rtDW . mxboqf3skh ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) & ( rtDW
. a5yx3v2fjf ) , sizeof ( rtDW . a5yx3v2fjf ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) & ( rtDW
. khbtd0f5vb ) , sizeof ( rtDW . khbtd0f5vb ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) & ( rtDW
. moc2zlrmo5 ) , sizeof ( rtDW . moc2zlrmo5 ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) & ( rtDW
. oug1x01dyp ) , sizeof ( rtDW . oug1x01dyp ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) & ( rtDW
. c5nse2xfsg ) , sizeof ( rtDW . c5nse2xfsg ) ) ;
mr_pmsm_foc_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) & ( rtDW
. dcrnppafnr ) , sizeof ( rtDW . dcrnppafnr ) ) ; mxSetFieldByNumber ( ssDW ,
0 , 1 , rtdwData ) ; } return ssDW ; } void mr_pmsm_foc_SetDWork ( const
mxArray * ssDW ) { ( void ) ssDW ; mr_pmsm_foc_restoreDataFromMxArray ( (
void * ) & ( rtB ) , ssDW , 0 , 0 , sizeof ( rtB ) ) ; { const mxArray *
rtdwData = mxGetFieldByNumber ( ssDW , 0 , 1 ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . gprmqx2cbw ) ,
rtdwData , 0 , 0 , sizeof ( rtDW . gprmqx2cbw ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . a5n05qvuz0 ) ,
rtdwData , 0 , 1 , sizeof ( rtDW . a5n05qvuz0 ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . mxboqf3skh ) ,
rtdwData , 0 , 2 , sizeof ( rtDW . mxboqf3skh ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . a5yx3v2fjf ) ,
rtdwData , 0 , 3 , sizeof ( rtDW . a5yx3v2fjf ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . khbtd0f5vb ) ,
rtdwData , 0 , 4 , sizeof ( rtDW . khbtd0f5vb ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . moc2zlrmo5 ) ,
rtdwData , 0 , 5 , sizeof ( rtDW . moc2zlrmo5 ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . oug1x01dyp ) ,
rtdwData , 0 , 6 , sizeof ( rtDW . oug1x01dyp ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . c5nse2xfsg ) ,
rtdwData , 0 , 7 , sizeof ( rtDW . c5nse2xfsg ) ) ;
mr_pmsm_foc_restoreDataFromMxArray ( ( void * ) & ( rtDW . dcrnppafnr ) ,
rtdwData , 0 , 8 , sizeof ( rtDW . dcrnppafnr ) ) ; } } mxArray *
mr_pmsm_foc_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 10 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char * blockType [ 10 ] = { "S-Function" , "Scope" , "Scope" , "Scope" ,
"Scope" , "Scope" , "Scope" , "Scope" , "Scope" , "Scope" , } ; static const
char * blockPath [ 10 ] = { "pmsm_foc/powergui/EquivalentModel1/State-Space"
, "pmsm_foc/Scope2" , "pmsm_foc/Scope6" , "pmsm_foc/Scope8" ,
"pmsm_foc/Scope" , "pmsm_foc/Scope1" , "pmsm_foc/Scope3" , "pmsm_foc/Scope4"
, "pmsm_foc/Scope5" , "pmsm_foc/Scope7" , } ; static const int reason [ 10 ]
= { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , } ; for ( subs [ 0 ] = 0 ; subs [
0 ] < 10 ; ++ ( subs [ 0 ] ) ) { subs [ 1 ] = 0 ; offset =
mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data , offset ,
mxCreateString ( blockType [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 1 ; offset =
mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data , offset ,
mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 2 ; offset =
mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data , offset ,
mxCreateDoubleScalar ( ( double ) reason [ subs [ 0 ] ] ) ) ; } } return data
; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 0 ) ;
ssSetNumY ( rtS , 0 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS
, 0 ) ; ssSetNumSampleTimes ( rtS , 3 ) ; ssSetNumBlocks ( rtS , 89 ) ;
ssSetNumBlockIO ( rtS , 28 ) ; ssSetNumBlockParams ( rtS , 109 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.0 ) ; ssSetSampleTime ( rtS , 2 , 1.0E-6 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ;
ssSetOffsetTime ( rtS , 2 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 3708514171U ) ; ssSetChecksumVal ( rtS , 1 ,
3344188691U ) ; ssSetChecksumVal ( rtS , 2 , 2449843500U ) ; ssSetChecksumVal
( rtS , 3 , 992344854U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; ( void ) memset ( ( char * ) rtS , 0 ,
sizeof ( SimStruct ) ) ; ( void ) memset ( ( char * ) & mdlInfo , 0 , sizeof
( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr ( rtS , & mdlInfo ) ;
ssSetExecutionInfo ( rtS , executionInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { void * dwork = ( void * ) & rtDW ; ssSetRootDWork ( rtS , dwork
) ; ( void ) memset ( dwork , 0 , sizeof ( DW ) ) ; } { static
DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T * ) & dtInfo , 0 ,
sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo ) ; dtInfo .
numDataTypes = 14 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ] ; dtInfo
. dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . BTransTable = &
rtBTransTable ; dtInfo . PTransTable = & rtPTransTable ; dtInfo .
dataTypeInfoTable = rtDataTypeInfoTable ; } pmsm_foc_InitializeDataMapInfo (
) ; ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS )
; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"pmsm_foc" ) ; ssSetPath ( rtS , "pmsm_foc" ) ; ssSetTStart ( rtS , 0.0 ) ;
ssSetTFinal ( rtS , 1.0 ) ; { static RTWLogInfo rt_DataLoggingInfo ;
rt_DataLoggingInfo . loggingInterval = ( NULL ) ; ssSetRTWLogInfo ( rtS , &
rt_DataLoggingInfo ) ; } { { static int_T rt_LoggedStateWidths [ ] = { 1 , 1
, 1 , 1 } ; static int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 }
; static int_T rt_LoggedStateDimensions [ ] = { 1 , 1 , 1 , 1 } ; static
boolean_T rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 } ; static
BuiltInDTypeId rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE } ; static int_T rt_LoggedStateComplexSignals [ ] = { 0
, 0 , 0 , 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) } ; static const char_T * rt_LoggedStateLabels [ ] = { "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = {
 "pmsm_foc/Permanent Magnet\nSynchronous Machine/Mechanical model/Discrete-Time\nIntegrator1"
,
 "pmsm_foc/Permanent Magnet\nSynchronous Machine/Electrical model/iq,id/iq/Discrete-Time\nIntegrator"
,
 "pmsm_foc/Permanent Magnet\nSynchronous Machine/Electrical model/iq,id/id/Discrete-Time\nIntegrator"
,
 "pmsm_foc/Permanent Magnet\nSynchronous Machine/Mechanical model/Discrete-Time\nIntegrator"
} ; static const char_T * rt_LoggedStateNames [ ] = { "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" } ; static boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0
, 0 , 0 , 0 } ; static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = {
{ 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } } ; static int_T rt_LoggedStateIdxList [ ] = { 0 , 1 , 2 , 3 } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 4 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 4 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtDW . gprmqx2cbw ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtDW . a5n05qvuz0 ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtDW . mxboqf3skh ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtDW . a5yx3v2fjf ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
ssSolverInfo slvrInfo ; ssSetStepSize ( rtS , 1.0E-6 ) ; ssSetMinStepSize (
rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError (
rtS , 0 ) ; ssSetMaxStepSize ( rtS , 1.0E-6 ) ; ssSetSolverMaxOrder ( rtS , -
1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL )
) ; ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 0 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
0 ) ; ssSetNonContDerivSigInfos ( rtS , ( NULL ) ) ; ssSetSolverInfo ( rtS ,
& slvrInfo ) ; ssSetSolverName ( rtS , "VariableStepDiscrete" ) ;
ssSetVariableStepSolver ( rtS , 1 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetSolverStateProjection ( rtS ,
0 ) ; ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetTNextTid ( rtS , INT_MIN ) ;
ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; } ssSetChecksumVal ( rtS , 0 ,
3708514171U ) ; ssSetChecksumVal ( rtS , 1 , 3344188691U ) ; ssSetChecksumVal
( rtS , 2 , 2449843500U ) ; ssSetChecksumVal ( rtS , 3 , 992344854U ) ; {
static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static
RTWExtModeInfo rt_ExtModeInfo ; static const sysRanDType * systemRan [ 9 ] ;
gblRTWExtModeInfo = & rt_ExtModeInfo ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = &
rtAlwaysEnabled ; systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = &
rtAlwaysEnabled ; systemRan [ 4 ] = & rtAlwaysEnabled ; systemRan [ 5 ] = &
rtAlwaysEnabled ; systemRan [ 6 ] = & rtAlwaysEnabled ; systemRan [ 7 ] = &
rtAlwaysEnabled ; systemRan [ 8 ] = & rtAlwaysEnabled ;
rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_pmsm_foc_GetSimStateDisallowedBlocks ) ; slsaGetWorkFcnForSimTargetOP (
rtS , mr_pmsm_foc_GetDWork ) ; slsaSetWorkFcnForSimTargetOP ( rtS ,
mr_pmsm_foc_SetDWork ) ; rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if (
ssGetErrorStatus ( rtS ) ) { return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 3 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID3 ( tid ) ; }
