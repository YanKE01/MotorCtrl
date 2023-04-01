/******************* (C) COPYRIGHT 2020 Fortiortech Shenzhen *******************
* File Name          : FU68xx_2_SMDU.h
* Creat Author       : Any Lin, R&D
* Modify Author      : Any Lin, R&D
* Creat Date         : 2020-08-19
* Modify Date        : 2020-08-21
* Description        :
********************************************************************************
* All Rights Reserved
*******************************************************************************/

#ifndef __FU68XX_2_SMDU_H__
#define __FU68XX_2_SMDU_H__

/******************************************************************************///Including Header Files
#include <FU68xx_2_MCU.h>
/******************************************************************************///Define Macro
/******************************************************************************///Define Type
/**
 * @brief SMDU的模式类型
 *
 * @note 使用@ref SMDU_RunNoBlock时, 其中的mode参数可以直接使用本枚举的内容
 * @note 使用@ref SMDU_RunBlock时, 其中的mode参数可以直接使用本枚举的内容
 */
typedef enum
{
    S1MUL   = 0, /**< 有符号乘法, 计算结果左移1位 */
    SMUL    = 1, /**< 有符号乘法 */
    UMUL    = 2, /**< 无符号乘法 */
    DIV     = 3, /**< 32/16无符号除法 */
    SIN_COS = 4, /**< Sin/Cos */
    ATAN    = 5, /**< ATan */
    LPF     = 6, /**< 低通滤波 */
    PI      = 7  /**< PI */
} ETypeSMDUMode;
/******************************************************************************///External Symbols
/******************************************************************************///External Function
/**
 * @brief 运行SMDU且不等待运行结束
 *
 * @param  stan (0-3) 要启动的计算单元编号
 * @param  mode (0-7) 指定计算单元的模式, 可使用@ref ETypeSMDUMode 作为计算模式的设置\n
 * @ref S1MUL   有符号乘法, 计算结果左移1位 \n
 * @ref SMUL    有符号乘法 \n
 * @ref UMUL    无符号乘法 \n
 * @ref DIV     32/16无符号除法 \n
 * @ref SIN_COS Sin/Cos \n
 * @ref ATAN    ATan \n
 * @ref LPF     低通滤波 \n
 * @ref PI      PI \n
 */
#define SMDU_RunNoBlock(stan, mode)   do                                                  \
                                      {                                                   \
                                          MDU_CR = MDUSTA0 << stan | (unsigned char)mode; \
                                      } while (0)

/**
 * @brief 运行SMDU且等待运行结束
 *
 * @param  stan (0-3) 要启动的计算单元编号
 * @param  mode (0-7) 指定计算单元的模式, 可使用@ref ETypeSMDUMode 作为计算模式的设置\n
 * @ref S1MUL   有符号乘法, 计算结果左移1位 \n
 * @ref SMUL    有符号乘法 \n
 * @ref UMUL    无符号乘法 \n
 * @ref DIV     32/16无符号除法 \n
 * @ref SIN_COS Sin/Cos \n
 * @ref ATAN    ATan \n
 * @ref LPF     低通滤波 \n
 * @ref PI      PI \n
 */
#define SMDU_RunBlock(stan, mode)   do                                       \
                                    {                                        \
                                        SMDU_RunNoBlock(stan, mode);         \
                                        while (MDU_CR & MDUBSY);             \
                                    } while (0);

#endif
