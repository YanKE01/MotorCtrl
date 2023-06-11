#ifndef __MULT_H_
#define __MULT_H__
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/******************** MULT Register Struct Definition *****************/
typedef unsigned           int uint32_t;
typedef struct
{
    __IO uint32_t MCTRL        ;	// 0x00 * 4
    __IO uint32_t SHIFT_NUM    ;	// 0x01 * 4
    __IO uint32_t MULTA	       ;	// 0x02 * 4
    __IO uint32_t MULTB	       ;	// 0x03 * 4
    __IO uint32_t MULTA_ADD    ;	// 0x04 * 4
    __IO uint32_t MULTB_ADD    ;	// 0x05 * 4
    __IO uint32_t MULTA_SUB    ;	// 0X06 * 4
    __IO uint32_t MULTB_SUB    ;	// 0X07 * 4
    __IO uint32_t MULT_RESULLO ;	// 0X08 * 4
    __IO uint32_t MULT_RESULHI ;	// 0X09 * 4 
} COPROC_TypeDef;

typedef struct
{
    __IO uint32_t DIV_CTRL;
    __IO uint32_t DIV_ALO;
    __IO uint32_t DIV_AHI;
    __IO uint32_t DIV_B;
    __IO uint32_t DIV_QUOTLO;
    __IO uint32_t DIV_QUOTHI;
    __IO uint32_t DIV_REM;
} DIV_TypeDef;


typedef struct
{
    __IO uint32_t CRC_CTRL;
    __IO uint32_t CRC_DATA;
    __IO uint32_t CRC_RESULT;
}CRC_TypeDef;


typedef struct
{
    __IO uint32_t CORDIC_CTRL;
    __IO uint32_t CORDIC_CONFIG;
    __IO uint32_t CORDIC_STATUS;
    __IO uint32_t CORDIC_XI;
    __IO uint32_t CORDIC_YI;
    __IO uint32_t CORDIC_ZI;
    __IO uint32_t CORDIC_XO;
    __IO uint32_t CORDIC_YO;
    __IO uint32_t CORDIC_ZO;
}CORDIC_TypeDef;

/***************** Bit Definition for MULT_CTRL Register **************/
#define     MULT_CTRL_SIGNED_Pos				31
#define     MULT_CTRL_SIGNED_Msk				(0x1UL << MULT_CTRL_SIGNED_Pos) 
#define     MULT_USIGNED                        (0x0UL << MULT_CTRL_SIGNED_Pos) 
#define     MULT_SIGNED                         (0x1UL << MULT_CTRL_SIGNED_Pos) 

#define     MULT_CTRL_MULT_Only_Pos 			19
#define     MULT_CTRL_MULT_Only_Msk 			(0x1UL << MULT_CTRL_MULT_Only_Pos)
#define     MULT_CTRL_MULT   			        (0x0UL << MULT_CTRL_MULT_Only_Pos)
#define     MULT_CTRL_MULT_ONLY   			    (0x1UL << MULT_CTRL_MULT_Only_Pos)

#define     MULT_CTRL_SHIFT_SEL_Pos 			18
#define     MULT_CTRL_SHIFT_SEL_Msk 			(0x1UL << MULT_CTRL_SHIFT_SEL_Pos)
#define     MULT_CTRL_SHIFT_AB 			        (0x0UL << MULT_CTRL_SHIFT_SEL_Pos)
#define     MULT_CTRL_SHIFT_RESULT 			    (0x1UL << MULT_CTRL_SHIFT_SEL_Pos)

#define     MULT_CTRL_SHIFT_EN_Pos 				17
#define     MULT_CTRL_SHIFT_EN_Msk	 			(0x1UL << MULT_CTRL_SHIFT_EN_Pos)
#define     MULT_CTRL_SHIFT_OFF	 			    (0x0UL << MULT_CTRL_SHIFT_EN_Pos)
#define     MULT_CTRL_SHIFT_ON	 			    (0x1UL << MULT_CTRL_SHIFT_EN_Pos)

#define     MULT_CTRL_SHIFT_IMM_Pos 			16
#define     MULT_CTRL_SHIFT_IMM_Msk 			(0x1UL << MULT_CTRL_SHIFT_IMM_Pos)
#define     MULT_SHIFT_IMM_OFF                  (0x0UL << MULT_CTRL_SHIFT_IMM_Pos)
#define     MULT_SHIFT_IMM                      (0x1UL << MULT_CTRL_SHIFT_IMM_Pos)

#define     MULT_CTRL_CR_INTR_EN_Pos   			13
#define     MULT_CTRL_CR_INTR_EN_Msk    		(0x1UL << MULT_CTRL_CR_INTR_EN_Pos)
#define     MULT_CTRL_CR_INTR_OFF    		    (0x0UL << MULT_CTRL_CR_INTR_EN_Pos)
#define     MULT_CTRL_CR_INTR_ON    		    (0x1UL << MULT_CTRL_CR_INTR_EN_Pos)

#define     MULT_CTRL_OV_INTR_EN_Pos    		12
#define     MULT_CTRL_OV_INTR_EN_Msk    		(0x1UL << MULT_CTRL_OV_INTR_EN_Pos)
#define     MULT_CTRL_OV_INTR_OFF    		    (0x0UL << MULT_CTRL_OV_INTR_EN_Pos)
#define     MULT_CTRL_OV_INTR_ON    		    (0x1UL << MULT_CTRL_OV_INTR_EN_Pos)

#define     MULT_CTRL_CARRY_Pos     			9
#define     MULT_CTRL_CARRT_Msk     			(0x1UL << MULT_CTRL_CARRY_Pos)
#define     MULT_CTRL_OVER_FLOW_Pos   			8
#define     MULT_CTRL_OVER_FLOW_Msk   			(0x1UL << MULT_CTRL_OVER_FLOW_Pos)


#define     MULT_CTRL_CRC_VALID_Pos			    2
#define     MULT_CTRL_CRC_VALID_Msk			    (0x1UL <<MULT_CTRL_CRC_VALID_Pos)
#define     MULT_CTRL_CRC_VALID_OFF			    (0x0UL <<MULT_CTRL_CRC_VALID_Pos)
#define     MULT_CTRL_CRC_VALID_ON			    (0x1UL <<MULT_CTRL_CRC_VALID_Pos)

#define     MULT_CTRL_RESET_RESULT_Pos			1
#define     MULT_CTRL_RESET_RESULT_Msk			(0x1UL <<MULT_CTRL_RESET_RESULT_Pos)
#define     MULT_CTRL_RESET_RESULT_OFF			(0x0UL <<MULT_CTRL_RESET_RESULT_Pos)
#define     MULT_CTRL_RESET_RESULT_ON			(0x1UL <<MULT_CTRL_RESET_RESULT_Pos)

#define     MULT_CTRL_RESET_MULT_Pos			0
#define     MULT_CTRL_RESET_MULT_Msk			(0x1UL <<MULT_CTRL_RESET_MULT_Pos)
#define     MULT_CTRL_RESET_MULT_OFF			(0x0UL <<MULT_CTRL_RESET_MULT_Pos)
#define     MULT_CTRL_RESET_MULT_ON			    (0x1UL <<MULT_CTRL_RESET_MULT_Pos)

/************* Bit Definition for MULT_SHIFT_NUM Register **********/
#define     SHIFT_MUN_Shift_num_Pos				0
#define     SHIFT_MUN_Shift_num_Msk				(0x3fUL << SHIFT_MUN_Shift_num_Pos 0)

/************* Bit Definition for DIV Register **********/
#define     DIV_CTRL_BY_0_Pos                   24
#define     DIV_BY_0_OFF                        ( 0x0UL << DIV_CTRL_BY_0_Pos)
#define     DIV_BY_0_ON                         ( 0x1UL << DIV_CTRL_BY_0_Pos)
#define     DIV_CTRL_DIV_32bit_Pos              8
#define     DIV_64BIT                           ( 0x0UL << DIV_CTRL_DIV_32bit_Pos)
#define     DIV_32BIT                           ( 0x1UL << DIV_CTRL_DIV_32bit_Pos)
#define     DIV_CTRL_DIV_RST_Pos                0
#define     DIV_DIV_RST_OFF                     ( 0x0UL << DIV_CTRL_DIV_RST_Pos)
#define     DIV_DIV_RST_ON                      ( 0x1UL << DIV_CTRL_DIV_RST_Pos)


/************* Bit Definition for CRC Register **********/
#define     CRC_CTRL_GPS_Pos            24
#define     CRC_GPS_CRC8                ( 0x0UL << CRC_CTRL_GPS_Pos )
#define     CRC_GPS_CRC16a              ( 0x1UL << CRC_CTRL_GPS_Pos )
#define     CRC_GPS_CRC16b              ( 0x2UL << CRC_CTRL_GPS_Pos )
#define     CRC_GPS_CRC32               ( 0x3UL << CRC_CTRL_GPS_Pos )

#define     CRC_CTRL_SWAP_Pos           17
#define     CRC_SWAP_00                 ( 0x0UL << CRC_CTRL_SWAP_Pos)
#define     CRC_SWAP_01                 ( 0x1UL << CRC_CTRL_SWAP_Pos)
#define     CRC_SWAP_10                 ( 0x2UL << CRC_CTRL_SWAP_Pos)
#define     CRC_SWAP_11                 ( 0x3UL << CRC_CTRL_SWAP_Pos)

#define     CRC_CTRL_LM_Pos             16
#define     CRC_LM_LSB                  ( 0x0UL << CRC_CTRL_LM_Pos)
#define     CRC_LM_MSB                  ( 0x1UL << CRC_CTRL_LM_Pos)

#define     CRC_CTRL_INVEN_Pos          15
#define     CRC_INVEN_0                 ( 0x0UL << CRC_CTRL_INVEN_Pos)
#define     CRC_INVEN_1                 ( 0x1UL << CRC_CTRL_INVEN_Pos)

#define     CRC_CTRL_BYTE_Pos           8
#define     CRC_BYTE_1                  ( 0x0UL << CRC_CTRL_BYTE_Pos )
#define     CRC_BYTE_2                  ( 0x1UL << CRC_CTRL_BYTE_Pos )
#define     CRC_BYTE_3                  ( 0x2UL << CRC_CTRL_BYTE_Pos )
#define     CRC_BYTE_4                  ( 0x3UL << CRC_CTRL_BYTE_Pos )

#define     CRC_CTRL_OVERFLOW_Pos       5
#define     CRC_CTRL_OVERFLOW_OFF       ( 0x0UL << CRC_CTRL_OVERFLOW_Pos )
#define     CRC_CTRL_OVERFLOW_EN        ( 0x1UL << CRC_CTRL_OVERFLOW_Pos )

#define     CRC_CTRL_CORDIC_Pos         4
#define     CRC_CTRL_CORDIC_OFF         ( 0x0UL << CRC_CTRL_CORDIC_Pos)
#define     CRC_CRTL_CORDIC_EN          ( 0x1UL << CRC_CTRL_CORDIC_Pos)

#define     CRC_RESET_CRC_Pos           1
#define     CRC_RESET_CRC_OFF           ( 0x0UL << CRC_RESET_CRC_Pos)
#define     CRC_RESET_CRC_EN            ( 0x1UL << CRC_RESET_CRC_Pos)

#define     CRC_RESET_Pos               0
#define     CRC_RESET_OFF               ( 0x0UL << CRC_RESET_Pos )
#define     CRC_RESET_ON                ( 0x1UL << CRC_RESET_Pos )


/************* Bit Definition for CORDIC Register **********/
#define     CORDIC_CTRL_START_Pos       8
#define     CORDIC_CTRL_START_OFF       ( 0x0UL << CORDIC_CTRL_START_Pos)
#define     CORDIC_CRTL_START_EN        ( 0x1UL << CORDIC_CTRL_START_Pos)

#define     CORDIC_CTRL_OVFINTR_Pos     5
#define     CORDIC_CTRL_OVFINTR_OFF     ( 0x0UL << CORDIC_CTRL_OVFINTR_Pos)
#define     CORDIC_CRTL_OVFINTR_EN      ( 0x1UL << CORDIC_CTRL_OVFINTR_Pos)

#define     CORDIC_CTRL_DONEINTR_Pos    4
#define     CORDIC_CTRL_DONEINTR_OFF    ( 0x0UL << CORDIC_CTRL_DONEINTR_Pos)
#define     CORDIC_CRTL_DONEINTR_EN     ( 0x1UL << CORDIC_CTRL_DONEINTR_Pos)

#define     CORDIC_CTRL_OVF_Pos         1
#define     CORDIC_CTRL_OVF_OFF         ( 0x0UL << CORDIC_CTRL_OVF_Pos)
#define     CORDIC_CRTL_OVF_EN          ( 0x1UL << CORDIC_CTRL_OVF_Pos)

#define     CORDIC_CTRL_DONE_Pos        0
#define     CORDIC_CTRL_DONE_OFF        ( 0x0UL << CORDIC_CTRL_DONE_Pos)
#define     CORDIC_CRTL_DONE_EN         ( 0x1UL << CORDIC_CTRL_DONE_Pos)

#define     CORDIC_CONFIG_CYCLES_Pos    16
#define     CORDIC_CONFIG_CYCLES_Msk    0x1F

#define     CORDIC_CONFIG_FUNCMODE_Pos    12
#define     CORDIC_CONFIG_FUNCMODE_Msk    3
#define     CORDIC_CONFIG_FUNCMODE_LINEAR   ( 0x0UL << CORDIC_CONFIG_FUNCMODE_Pos)
#define     CORDIC_CONFIG_FUNCMODE_CIRCLE ( 0x1UL << CORDIC_CONFIG_FUNCMODE_Pos)
#define     CORDIC_CONFIG_FUNCMODE_ATANTH ( 0x3UL << CORDIC_CONFIG_FUNCMODE_Pos)

#define     CORDIC_CONFIG_MODE_Pos      8
#define     CORDIC_CONFIG_MODE_ROTATE   ( 0x0UL << CORDIC_CONFIG_MODE_Pos)
#define     CORDIC_CONFIG_MODE_VECTOR   ( 0x1UL << CORDIC_CONFIG_MODE_Pos)

#define     CORDIC_CONFIG_BYPASS_POST_Pos    5
#define     CORDIC_CONFIG_BYPASS_POST_OFF    ( 0x0UL << CORDIC_CONFIG_BYPASS_POST_Pos)
#define     CORDIC_CONFIG_BYPASS_POST_EN     ( 0x1UL << CORDIC_CONFIG_BYPASS_POST_Pos)

#define     CORDIC_CONFIG_BYPASS_PRE_Pos    4
#define     CORDIC_CONFIG_BYPASS_PRE_OFF    ( 0x0UL << CORDIC_CONFIG_BYPASS_PRE_Pos)
#define     CORDIC_CONFIG_BYPASS_PRE_EN     ( 0x1UL << CORDIC_CONFIG_BYPASS_PRE_Pos)

#define     CORDIC_CONFIG_KEEPZ_Pos    2
#define     CORDIC_CONFIG_KEEPZ_OFF    ( 0x0UL << CORDIC_CONFIG_KEEPZ_Pos)
#define     CORDIC_CONFIG_KEEPZ_EN     ( 0x1UL << CORDIC_CONFIG_KEEPZ_Pos)

#define     CORDIC_CONFIG_KEEPY_Pos    1
#define     CORDIC_CONFIG_KEEPY_OFF    ( 0x0UL << CORDIC_CONFIG_KEEPY_Pos)
#define     CORDIC_CONFIG_KEEPY_EN     ( 0x1UL << CORDIC_CONFIG_KEEPY_Pos)

#define     CORDIC_CONFIG_KEEPX_Pos    0
#define     CORDIC_CONFIG_KEEPX_OFF    ( 0x0UL << CORDIC_CONFIG_KEEPX_Pos)
#define     CORDIC_CONFIG_KEEPX_EN     ( 0x1UL << CORDIC_CONFIG_KEEPX_Pos)


/***************** COPROCx Declaration **************/
#define MULT ((COPROC_TypeDef *) (MULT_ADDR_STR))
#define DIV0 ((DIV_TypeDef *) (DIV_ADDR_STR))
#define CRC0 ((CRC_TypeDef *) (CRC_ADDR_STR))
#define CXC0 ((CXC_TypeDef *) (CXC_ADDR_STR))
#define CORDIC ((CORDIC_TypeDef *) (CORDIC_ADDR_STR))



/***************** COPROC function Declaration **************/

void coproc_mult_initial( COPROC_TypeDef * COPROCx );
void coproc_mult_initial_shift( COPROC_TypeDef * COPROCx );
void coproc_mult_initial_sign( COPROC_TypeDef * COPROCx );

void coproc_wr_mult_a( COPROC_TypeDef * COPROCx, uint32_t wr_mult_a );
void coproc_wr_mult_b( COPROC_TypeDef * COPROCx, uint32_t wr_mult_b );
void coproc_wr_mult_a_add( COPROC_TypeDef * COPROCx, uint32_t wr_mult_a_add );
void coproc_wr_mult_b_add( COPROC_TypeDef * COPROCx, uint32_t wr_mult_b_add );
void coproc_wr_mult_a_sub( COPROC_TypeDef * COPROCx, uint32_t wr_mult_a_sub );
void coproc_wr_mult_b_sub( COPROC_TypeDef * COPROCx, uint32_t wr_mult_b_sub );

uint32_t coproc_read_result_low( COPROC_TypeDef * COPROCx );
uint32_t coproc_read_result_high( COPROC_TypeDef * COPROCx );
void coproc_write_shift_num( COPROC_TypeDef * COPROCx, uint32_t shift_num );
void coproc_rst_result_regist( COPROC_TypeDef * COPROCx );
uint32_t coproc_overflow_signed( COPROC_TypeDef * COPROCx );
uint32_t coproc_read_carry( COPROC_TypeDef * COPROCx );


//-------------------------------------
//DIV
//------------------------------------
void div_crtl_initial( DIV_TypeDef *DIVx);
void div_write_divdend( DIV_TypeDef * DIVx, uint32_t div_high, uint32_t div_low);
void div_write_divsor( DIV_TypeDef * DIVx, uint32_t div_divsor);
uint32_t div_read_result( DIV_TypeDef * DIVx );
uint32_t div_read_remainder( DIV_TypeDef * DIVx );

//-----------------------------------
//CRC
//---------------------------------
void crc_initial_config_8( CRC_TypeDef * CRCx );
void crc_initial_config_16a( CRC_TypeDef * CRCx );
void crc_initial_config_16b( CRC_TypeDef * CRCx );
void crc_initial_config_32( CRC_TypeDef * CRCx );
void crc_write_crc_data( CRC_TypeDef * CRCx, uint32_t crc_data );
uint32_t crc_read_result( CRC_TypeDef * CRCx );
void crc_write_result( CRC_TypeDef * CRCx );

void delay (uint32_t dly);
#endif // __MULT_H__
