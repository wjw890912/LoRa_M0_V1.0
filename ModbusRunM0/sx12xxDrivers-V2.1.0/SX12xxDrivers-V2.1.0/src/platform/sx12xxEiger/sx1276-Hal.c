/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       sx1276-Hal.c
 * \brief      SX1276 Hardware Abstraction Layer
 *
 * \version    2.0.B2 
 * \date       Nov 21 2012
 * \author     Miguel Luis
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#include <stdint.h>
#include <stdbool.h> 

#include "platform.h"

#if defined( USE_SX1276_RADIO )

#include "ioe.h"
#include "spi.h"
#include "../../radio/sx1276-Hal.h"
#include "M051Series.h"




#define  SX1278_SDO                          P23  
#define  RF_REST_L			  	  		     0
#define  RF_REST_H			 			     0 
#define  RF_CE_L           				     P40 =0 
#define  RF_CE_H           				     P40 =1 
#define  RF_CKL_L           			     P22 =0 
#define  RF_CKL_H          					 P22 =1 
#define  RF_SDI_L          					 P24 =0 
#define  RF_SDI_H        					 P24 =1 


uint8_t SpiInOut( uint8_t outData )
{
	 //重写

	 	unsigned char i,data=0;
	

	for (i = 0; i < 8; i++) 
	{
		if (outData & 0x80)
			RF_SDI_H;
		else
			RF_SDI_L;
		outData <<= 1;
		data <<= 1;
		RF_CKL_H;
		if (SX1278_SDO)
			data |= 0x01;
		else
			data &= 0xfe;
		 
		RF_CKL_L;
	}
	return data;
    /* Send SPIy data */
    //SPI_I2S_SendData( SPI_INTERFACE, outData );
    //while( SPI_I2S_GetFlagStatus( SPI_INTERFACE, SPI_I2S_FLAG_RXNE ) == RESET );
    //return SPI_I2S_ReceiveData( SPI_INTERFACE );
}


void SX1276InitIo( void )
{

	 GPIO_SetMode(P4, BIT0, GPIO_PMD_QUASI);//
	 GPIO_SetMode(P2, BIT2|BIT4, GPIO_PMD_QUASI);//
	 GPIO_SetMode(P2, BIT3, GPIO_PMD_QUASI);//
   	//把SPI的几个IO口写上
}

void SX1276SetReset( uint8_t state )
{
    //复位操作，根据state的值决定是高电平还是低电平，先不做了
}

void SX1276Write( uint8_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

void SX1276Read( uint8_t addr, uint8_t *data )
{
    SX1276ReadBuffer( addr, data, 1 );
}

void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;
		 
		RF_CE_L;
		RF_CKL_L;
		
    SpiInOut( addr | 0x80 );
    for( i = 0; i < size; i++ )
    {
        SpiInOut( buffer[i] );
    }

		RF_CE_H;
		RF_CKL_H;
	//重写这个方法
	/*
    //NSS = 0;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_RESET );

    SpiInOut( addr | 0x80 );
    for( i = 0; i < size; i++ )
    {
        SpiInOut( buffer[i] );
    }

    //NSS = 1;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );

	*/
}

void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;



	  RF_CE_L;
		RF_CKL_L;


	    SpiInOut( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( 0 );
    }



			RF_CE_H;
		RF_CKL_H;


	//重写这个方法
   /*
    //NSS = 0;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_RESET );

    SpiInOut( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( 0 );
    }

    //NSS = 1;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );
	*/
}

void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
    SX1276WriteBuffer( 0, buffer, size );
}

void SX1276ReadFifo( uint8_t *buffer, uint8_t size )
{
    SX1276ReadBuffer( 0, buffer, size );
}

inline uint8_t SX1276ReadDio0( void )
{
   // return GPIO_ReadInputDataBit( DIO0_IOPORT, DIO0_PIN );
}

inline uint8_t SX1276ReadDio1( void )
{
    //return GPIO_ReadInputDataBit( DIO1_IOPORT, DIO1_PIN );
}

inline uint8_t SX1276ReadDio2( void )
{
   // return GPIO_ReadInputDataBit( DIO2_IOPORT, DIO2_PIN );
}

inline uint8_t SX1276ReadDio3( void )
{
    //return IoePinGet( RF_DIO3_PIN );
}

inline uint8_t SX1276ReadDio4( void )
{
   // return IoePinGet( RF_DIO4_PIN );
}

inline uint8_t SX1276ReadDio5( void )
{
    //return IoePinGet( RF_DIO5_PIN );
}

inline void SX1276WriteRxTx( uint8_t txEnable )
{
    if( txEnable != 0 )
    {
       // IoePinOn( FEM_CTX_PIN );
       // IoePinOff( FEM_CPS_PIN );
    }
    else
    {
        //IoePinOff( FEM_CTX_PIN );
       // IoePinOn( FEM_CPS_PIN );
    }
}

#endif // USE_SX1276_RADIO
