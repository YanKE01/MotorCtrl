#include "HY_Display2.h"
#include "HY_Variable.h"
#include "lcm32f037_gpio.h"

static uint8_t s_7number[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00};
static uint8_t digital_tube_addr[4] = {0xC0, 0xC2, 0xC4, 0xC6};
static uint8_t digital_led_addr[8] = {0xC1, 0xC3, 0xC5, 0xC7, 0xC9, 0xCB, 0xCD, 0xCF};
/**
 * @brief TM1638:修改SDA输出
 *
 */
void HY_TM1650_SDA_Ouput()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化
}

/**
 * @brief TM1638:修改SDA为输入
 *
 */
void HY_TM1650_SDA_Input()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化
}

/**
 * @brief TM1638 write value
 *
 * @param value
 */
void HY_TM1638_Write(uint8_t value)
{
    int i = 0;
    HY_TM1650_SDA_Ouput();
    for (i = 0; i < 8; i++)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        if (value & 0x01)
        {
            GPIO_SetBits(GPIOA, GPIO_Pin_0);
        }
        else
        {
            GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        }
        value >>= 1;
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
}

/**
 * @brief TM1638: 读
 *
 * @return uint8_t
 */
uint8_t HY_TM1638_Read()
{
    uint8_t i;
    uint8_t temp = 0;
    HY_TM1650_SDA_Input();

    for (i = 0; i < 8; i++)
    {
        temp >>= 1;
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
        {
            temp |= 0x80;
        }
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
    return temp;
}

/**
 * @brief TM1638写命令，只有STB拉低才有效
 *
 * @param value
 */
void HY_TM1638_SendCmd(uint8_t value)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    HY_TM1638_Write(value);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

uint8_t HY_TM1638_ScanKey()
{
    uint8_t data[4], i;
    uint8_t key = 0;
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    HY_TM1638_Write(0x42);
    for (i = 0; i < 4; i++)
    {
        data[i] = HY_TM1638_Read();
    }
    GPIO_SetBits(GPIOB, GPIO_Pin_0);

    for (i = 0; i < 4; i++) // 取出4个BYTE中的键值
    {
        if (((data[i] >> 0) & 0x01) == 0x01) // 第0位，B0,对应按键为1、3、5、7，计算公式是i*2+1
        {
            key = (i * 2 + 1);
            break;
        }
        else
        {
            if (((data[i] >> 4) & 0x01) == 0x01) // 第4位，B4,对应按键为2、4、6、8，计算公式是i*2+2
            {
                key = (i * 2 + 2);
                break;
            }
        }
    }
    return key;
}

/**
 * @brief TM1638复位初始化
 *
 */
void HY_TM1638_Reset()
{
    uint8_t i = 0;
    HY_TM1638_SendCmd(0x40); // 自动增加
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);

    HY_TM1638_Write(0xc0); // 设置起始地址
    for (i = 0; i < 16; i++)
    {
        HY_TM1638_Write(0x00); // 传输16位数据
    }
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

/**
 * @brief TM1638设置亮度，0到7级
 *
 * @param brightness
 */
void HY_TM1638_SetBrightness(uint8_t brightness)
{
    if (brightness < 0 || brightness > 7)
    {
        return;
    }
    HY_TM1638_SendCmd(0x88 | brightness);
}

/**
 * @brief TM1638：对应地址设置数字
 *
 * @param index
 * @param num
 */
void HY_TM1638_SetIndexNum(uint8_t index, uint8_t num)
{
    if (index < 0 || index > 4 || num < 0 || num > 9)
    {
        return;
    }

    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    HY_TM1638_Write(digital_tube_addr[index]);
    HY_TM1638_Write(s_7number[num]);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

/**
 * @brief TM1638自动设置数字
 *
 * @param num
 */
void HY_TM1638_SetNumAuto(uint16_t num)
{
    uint8_t index = 3;
    if (num > 9999)
    {
        return;
    }

    while (num)
    {
        HY_TM1638_SetIndexNum(index, num % 10);
        index--;
        num /= 10;
    }
}

void HY_TM1638_Clear()
{
    uint8_t j = 0;
    for (j = 0; j < 4; j++)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        HY_TM1638_Write(digital_tube_addr[j]);
        HY_TM1638_Write(s_7number[10]);
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
    }
}

/**
 * @brief TM1638单独设置LED状态
 *
 * @param index
 * @param status
 */
void HY_TM1638_SetLedState(uint8_t index, uint8_t status)
{
    if (index < 0 || index > 8)
    {
        return;
    }

    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    HY_TM1638_Write(digital_led_addr[index]);
    HY_TM1638_Write(status);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

/**
 * @brief TM1638显示故障
 *
 * @param fault
 */
void HY_TM1638_SetFault(UGT_S_SYSTEMSTATE_STRU fault)
{

    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    HY_TM1638_Write(digital_tube_addr[0]);
    HY_TM1638_Write(0x73);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
    if (fault.uSystemError.Bits.OverVoltage)
    {
        HY_TM1638_SetNumAuto(0);
    }
    else if (fault.uSystemError.Bits.LosePhase)
    {
        HY_TM1638_SetNumAuto(43);
    }
    else if (fault.uSystemError.Bits.StartupFail)
    {
        HY_TM1638_SetNumAuto(44);
    }
    else if (fault.uSystemError.Bits.OverCurrent)
    {
        HY_TM1638_SetNumAuto(49);
    }
    else if (fault.uSystemError.Bits.UnderVoltage)
    {
        HY_TM1638_SetNumAuto(50);
    }
    else if (fault.uSystemError.Bits.OverVoltage)
    {
        HY_TM1638_SetNumAuto(51);
    }
    else if (fault.uSystemError.Bits.NoWater)
    {
        HY_TM1638_SetNumAuto(48);
    }
}

/**
 * @brief TM1638初始化
 *
 */
void HY_TM1638_Init()
{
    HY_TM1638_SetBrightness(3);
    HY_TM1638_Reset();
    HY_TM1638_SetLedState(POWER, 1); // 电源灯
}
