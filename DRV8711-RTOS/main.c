/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== empty.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
 #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>
#include "registers.h"
struct CTRL_Register	G_CTRL_REG;
struct TORQUE_Register 	G_TORQUE_REG;
struct OFF_Register 	G_OFF_REG;
struct BLANK_Register	G_BLANK_REG;
struct DECAY_Register 	G_DECAY_REG;
struct STALL_Register 	G_STALL_REG;
struct DRIVE_Register 	G_DRIVE_REG;
struct STATUS_Register 	G_STATUS_REG;
/* Board Header file */
#include "Board.h"

#define TASKSTACKSIZE   512
#define SPI_MSG_LENGTH    1

#define REGWRITE    0x00
#define REGREAD     0x80





Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

/*
 *  ======== heartBeatFxn ========
 *  Toggle the Board_LED0. The Task_sleep is determined by arg0 which
 *  is configured for the heartBeat Task instance.
 */
Void MotorFxn(UArg arg0, UArg arg1)
{
		while(1){
		unsigned char dataHi = 0x00;
	    unsigned char dataLo = 0x00;

	    // Write CTRL Register
	    dataHi = REGWRITE | (G_CTRL_REG.Address << 4) | (G_CTRL_REG.DTIME << 2) | (G_CTRL_REG.ISGAIN);
	    dataLo = (G_CTRL_REG.EXSTALL << 7) | (G_CTRL_REG.MODE << 3) | (G_CTRL_REG.RSTEP << 2) | (G_CTRL_REG.RDIR << 1) | (G_CTRL_REG.ENBL);
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    // Write TORQUE Register
	    dataHi = REGWRITE | (G_TORQUE_REG.Address << 4) | (G_TORQUE_REG.SIMPLTH);
	    dataLo = G_TORQUE_REG.TORQUE;
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    // Write OFF Register
	    dataHi = REGWRITE | (G_OFF_REG.Address << 4) | (G_OFF_REG.PWMMODE);
	    dataLo = G_OFF_REG.TOFF;
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    // Write BLANK Register
	    dataHi = REGWRITE | (G_BLANK_REG.Address << 4) | (G_BLANK_REG.ABT);
	    dataLo = G_BLANK_REG.TBLANK;
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    // Write DECAY Register
	    dataHi = REGWRITE | (G_DECAY_REG.Address << 4) | (G_DECAY_REG.DECMOD);
	    dataLo = G_DECAY_REG.TDECAY;
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    // Write STALL Register
	    dataHi = REGWRITE | (G_STALL_REG.Address << 4) | (G_STALL_REG.VDIV << 2) | (G_STALL_REG.SDCNT);
	    dataLo = G_STALL_REG.SDTHR;
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    // Write DRIVE Register
	    dataHi = REGWRITE | (G_DRIVE_REG.Address << 4) | (G_DRIVE_REG.IDRIVEP << 2) | (G_DRIVE_REG.IDRIVEN);
	    dataLo = (G_DRIVE_REG.TDRIVEP << 6) | (G_DRIVE_REG.TDRIVEN << 4) | (G_DRIVE_REG.OCPDEG << 2) | (G_DRIVE_REG.OCPTH);
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    // Write STATUS Register
	    dataHi = REGWRITE | (G_STATUS_REG.Address << 4);
	    dataLo = (G_STATUS_REG.STDLAT << 7) | (G_STATUS_REG.STD << 6) | (G_STATUS_REG.UVLO << 5) | (G_STATUS_REG.BPDF << 4) | (G_STATUS_REG.APDF << 3) | (G_STATUS_REG.BOCP << 2) | (G_STATUS_REG.AOCP << 1) | (G_STATUS_REG.OTS);
	    SPI_DRV8711_ReadWrite(dataHi, dataLo);

	    G_CTRL_REG.RSTEP = 0x01;


		}
}

unsigned int SPI_DRV8711_ReadWrite(unsigned char dataHi, unsigned char dataLo)
{

	unsigned char masterRxBuffer[SPI_MSG_LENGTH];
	unsigned char masterTxBuffer[SPI_MSG_LENGTH]=dataHi;
	/******************************************************/
//	unsigned int readData = 0;
//
//	//P2OUT |= CS;
//	GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
//
//	UCB0TXBUF = dataHi;
//	while (UCB0STAT & UCBUSY);
//	readData |= (UCB0RXBUF << 8);
//
//	UCB0TXBUF = dataLo;
//	while (UCB0STAT & UCBUSY);
//	readData |= UCB0RXBUF;
//
//	//P2OUT &= ~CS;
//	GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
//	return readData;
	/*****************************************************/


	SPI_Handle masterSpi;
	SPI_Transaction masterTransaction;
	bool transferOK;


		    /* Initialize SPI handle as default master */
		    masterSpi = SPI_open(Board_SPI0, NULL);
		    if (masterSpi == NULL) {
		        System_abort("Error initializing SPI\n");
		    }
		    else {
		        System_printf("SPI initialized\n");
		    }

		    /* Initialize master SPI transaction structure */
		        masterTransaction.count = SPI_MSG_LENGTH;
		        masterTransaction.txBuf = (Ptr)masterTxBuffer;
		        masterTransaction.rxBuf = (Ptr)masterRxBuffer;

		    /* Initiate SPI transfer */
		        //transferOK = SPI_transfer(masterSpi, &masterTransaction);

		        masterTransaction.count = SPI_MSG_LENGTH;
		        masterTransaction.txBuf = (Ptr)masterTxBuffer;
		        masterTransaction.rxBuf = (Ptr)masterRxBuffer;

	unsigned int readData = 0;
	masterTransaction.count = SPI_MSG_LENGTH;
	masterTransaction.txBuf = (Ptr)dataHi;
	masterTransaction.rxBuf = (Ptr)masterRxBuffer;

	GPIO_write(CS, 1);

	//masterTxBuffer = dataHi;
	SPI_transfer(masterSpi, &masterTransaction);
	unsigned char temp = masterRxBuffer;
	readData |= (temp << 8);

	masterTransaction.txBuf = (Ptr)dataLo;
	SPI_transfer(masterSpi, &masterTransaction);
	temp = masterRxBuffer;
	readData |= temp;

	GPIO_write(CS, 0);
	return readData;


}

/*
 *  ======== main ========
 */
int main(void)
{
	G_CTRL_REG.Address 	= 0x00;
		    	G_CTRL_REG.DTIME 	= 0x01;
		    	G_CTRL_REG.ISGAIN 	= 0x03;
		    	G_CTRL_REG.EXSTALL 	= 0x00;
		    	G_CTRL_REG.MODE 	= 0x03;
		    	G_CTRL_REG.RSTEP 	= 0x01;
		    	G_CTRL_REG.RDIR 	= 0x01;
		    	G_CTRL_REG.ENBL 	= 0x01;

		    	// TORQUE Register
		    	G_TORQUE_REG.Address = 0x01;
		    	G_TORQUE_REG.SIMPLTH = 0x00;
		    	G_TORQUE_REG.TORQUE  = 0x1F;

		    	// OFF Register
		    	G_OFF_REG.Address 	= 0x02;
		    	G_OFF_REG.PWMMODE 	= 0x00;
		    	G_OFF_REG.TOFF 		= 0x30;

		    	// BLANK Register
		    	G_BLANK_REG.Address = 0x03;
		    	G_BLANK_REG.ABT 	= 0x01;
		    	G_BLANK_REG.TBLANK 	= 0x08;

		    	// DECAY Register.
		    	G_DECAY_REG.Address = 0x04;
		    	G_DECAY_REG.DECMOD  = 0x11;
		    	G_DECAY_REG.TDECAY 	= 0x10;

		    	// STALL Register
		    	G_STALL_REG.Address = 0x05;
		    	G_STALL_REG.VDIV 	= 0x03;
		    	G_STALL_REG.SDCNT 	= 0x03;
		    	G_STALL_REG.SDTHR 	= 0x40;

		    	// DRIVE Register
		    	G_DRIVE_REG.Address = 0x06;
		    	G_DRIVE_REG.IDRIVEP = 0x10;
		    	G_DRIVE_REG.IDRIVEN = 0x10;
		    	G_DRIVE_REG.TDRIVEP = 0x01;
		    	G_DRIVE_REG.TDRIVEN = 0x01;
		    	G_DRIVE_REG.OCPDEG 	= 0x01;
		    	G_DRIVE_REG.OCPTH 	= 0x01;

		    	// STATUS Register
		    	G_STATUS_REG.Address = 0x07;
		    	G_STATUS_REG.STDLAT  = 0x00;
		    	G_STATUS_REG.STD     = 0x00;
		    	G_STATUS_REG.UVLO    = 0x00;
		    	G_STATUS_REG.BPDF    = 0x00;
		    	G_STATUS_REG.APDF    = 0x00;
		    	G_STATUS_REG.BOCP    = 0x00;
		    	G_STATUS_REG.AOCP    = 0x00;
		    	G_STATUS_REG.OTS     = 0x00;

    Task_Params taskParams;

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    // Board_initI2C();
    // Board_initSDSPI();
     Board_initSPI();
    // Board_initUART();
    // Board_initWatchdog();
    // Board_initWiFi();

    /* Construct heartBeat Task  thread */
    Task_Params_init(&taskParams);
    taskParams.arg0 = 1000;
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    Task_construct(&task0Struct, (Task_FuncPtr)MotorFxn, &taskParams, NULL);

    /* Turn on user LED */
    //GPIO_write(Board_LED0, Board_LED_ON);

    //System_printf("Starting the example\nSystem provider is set to SysMin. "
    //              "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
