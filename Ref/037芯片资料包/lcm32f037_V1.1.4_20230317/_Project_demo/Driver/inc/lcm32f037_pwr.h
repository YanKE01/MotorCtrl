#ifndef LCM32F037_PWR_H
#define LCM32F037_PWR_H
#include "lcm32f037_rcc.h"
#include "lcm32f037.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "lcm32f037.h"
#include "lcm32f037_conf.h"

#define PWR_STOPEntry_WFI ((uint8_t)0x01)
#define PWR_STOPEntry_WFE ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE))

#define PWR_WakeUpPin2 (2)
#define PWR_WakeUpPin1 (1)
#define PWR_WakeUpPin0 (0)
#define IS_PWR_WAKEUPPIN(expr) ((expr == PWR_WakeUpPin2) || (expr == PWR_WakeUpPin1) || (expr == PWR_WakeUpPin0))

#define PWR_SLEEPEntry_WFI ((uint8_t)0x01)
#define PWR_SLEEPEntry_WFE ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE))

#define PWR_WT_WakeUp (1 << 9)
#define PWR_WT_AlarmWakeUp (1 << 8)
#define PWR_WUF2 (1 << 2)
#define PWR_WUF1 (1 << 1)
#define PWR_WUF0 (1 << 0)
#define PWR_LVD (1 << 24)
#define IS_PWR_FLAG(flag) ((flag == PWR_WT_WakeUp) ||      \
                           (flag == PWR_WT_AlarmWakeUp) || \
                           (flag == PWR_WUF2) ||           \
                           (flag == PWR_WUF1) ||           \
                           (flag == PWR_WUF0) ||           \
                           (flag == PWR_LVD))

#define PWR_VRHLevel_2v5 (0)
#define PWR_VRHLevel_4v (1)
#define IS_VRH_LEVEL(PWR_VRHLevel) ((PWR_VRHLevel == PWR_VRHLevel_2v5) || (PWR_VRHLevel == PWR_VRHLevel_4v))

#define PWR_LVDInternal_2V (0)
#define PWR_LVDInternal_2V2 (1)
#define PWR_LVDInternal_2V4 (2)
#define PWR_LVDInternal_2V7 (3)
#define PWR_LVDInternal_2V9 (4)
#define PWR_LVDInternal_3V1 (5)
#define PWR_LVDInternal_3V6 (6)
#define PWR_LVDInternal_4V5 (7)
#define IS_PWR_LVDLevel(PWR_LVDLevel) (PWR_LVDLevel < 8)

#define PWR_LVDInternal (0)
#define PWR_LVDExternal (1)
#define IS_PWR_LVDIE(IE) ((IE == PWR_LVDInternal) || (IE == PWR_LVDExternal))

#define PWR_LVRLevel_1V6 (0)
#define PWR_LVRLevel_1V8 (1)
#define PWR_LVRLevel_2V0 (2)
#define PWR_LVRLevel_2V5 (3)
#define PWR_LVRLevel_2V8 (4)
#define PWR_LVRLevel_3V0 (5)
#define PWR_LVRLevel_3V5 (6)
#define PWR_LVRLevel_4V0 (7)
#define IS_LVR_Level(PWR_LVRLevel) (PWR_LVRLevel < 8)

#define PWR_VSEL_1V5 (0)
#define PWR_VSEL_1V2 (1)
#define PWR_VSEL_1V1 (2)
#define PWR_VSEL_1V (3)
#define IS_PWR_VESL(expr) ((expr == PWR_VSEL_1V5) || \
                           (expr == PWR_VSEL_1V2) || \
                           (expr == PWR_VSEL_1V1) || \
                           (expr == PWR_VSEL_1V))

#define PWR_LDOInternal (0)
#define PWR_LDOExternal (1)
#define IS_PWR_LDO_IE(expr) ((expr == PWR_LDOInternal) || \
                             (expr == PWR_LDOExternal))

#define PWR_DRV_10uA (0)
#define PWR_DRV_50uA (1)
#define PWR_DRV_150uA (2)
#define PWR_DRV_200uA (3)

  void PWR_DeInit(void);
  void PWR_BankupAccessCmd(FunctionalState NewState);
  void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
  void PWR_PVDCmd(FunctionalState NewState);
  void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);
  void PWR_EnterSleepMode(uint32_t PWR_SLEEPEntry);
  void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint32_t PWR_StopEntry);
  void PWR_EnterSTANDBYMode(void);
  FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
  void PWR_ClearFlag(uint32_t PWR_Flag);
  void PWR_VRHConfig(uint32_t PWR_VRHLevel);
  void PWR_LVDConfig(uint32_t IE, uint32_t PWR_LVDLevel);
  void PWR_LVDCmd(FunctionalState NewState);
  void PWR_LVRConfig(uint32_t PWR_LVRLevel);
  void PWR_LVRCmd(FunctionalState NewState);
  void PWR_LVRClearFlag(void);
  void PWR_POR_PDRClearFlag(void);
  void PWR_LVDRegisterLock(void);
  void PWR_PORCmd(FunctionalState NewState);
  void PWR_PDRCmd(FunctionalState NewState);
  void PWR_LPVRConfig(uint32_t PWR_VSEL);
  void PWR_LDODriverLevel(uint32_t PWR_DRV);
  void PWR_LDOCmd(FunctionalState NewState);
  void PWR_LDOConfig(uint32_t IE);
  void PWR_UltraLowPowerDeepSleep(FunctionalState NewState);
  void PWR_FlashPowerDownDeepSleep(FunctionalState NewState);
  void PWR_LowPowerCmd(FunctionalState NewState);
  void PWR_PowerDownDeepSleep(FunctionalState NewState);
  void PWR_LowPowerDeepSleep(FunctionalState NewState);
  void PWR_EnterUR_STOPMode(uint32_t PWR_Regulator, uint32_t PWR_STOPEntry);
  void PWR_EnterLowPowerSTOPMode(uint32_t PWR_Regulator, uint32_t PWR_STOPEntry);
  void Power_Init(void);
#ifdef __cplusplus
}
#endif

#endif
