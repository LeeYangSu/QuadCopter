//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                                        2012.07.18 Lee Yang Su                                          ///
///                                   ref : spec.6175G.ATARM.22-Nov-06                                     ///
///                                                                                                        ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef	__ARM_H__
#define	__ARM_H__

#include "switch.h"
#include "adc.h"
#include "pwm.h"
#include "gyro.h"
#include "accelero.h"
#include "timer.h"
#include "ars.h"
#include "dbgu.h"
#include "pid.h"
#include "kalman.h"
#include <math.h>
#include <stdlib.h>
#include <float.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         Parallel Input Output Controller                                               ///
///                                                                                                 page.88///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		PIO_PER			*((volatile unsigned int *) 0xFFFFF400) //PIO Enable Register
#define		PIO_PDR			*((volatile unsigned int *) 0xFFFFF404)	//PIO Disable Register
#define		PIO_PSR			*((volatile unsigned int *) 0xFFFFF408)	//PIO Status Register

#define		PIO_OER			*((volatile unsigned int *) 0xFFFFF410)	//Output Enable Register
#define		PIO_ODR			*((volatile unsigned int *) 0xFFFFF414)	//Output Disable Register
#define		PIO_OSR			*((volatile unsigned int *) 0xFFFFF418)	//Output Status Register

#define		PIO_IFER		*((volatile unsigned int *) 0xFFFFF420)	//Glitch Input Filter Enable Register
#define		PIO_IFDR		*((volatile unsigned int *) 0xFFFFF424)	//Glitch Input Filter Disable Register
#define		PIO_IFSR		*((volatile unsigned int *) 0xFFFFF428)	//Glitch Input Filter Status Register

#define		PIO_SODR		*((volatile unsigned int *) 0xFFFFF430)	//Set Output Data Register
#define		PIO_CODR		*((volatile unsigned int *) 0xFFFFF434) //Clear Output Data Register                                                 
#define		PIO_ODSR		*((volatile unsigned int *) 0xFFFFF438)	//Output Data Status Register
#define		PIO_PDSR		*((volatile unsigned int *) 0xFFFFF43C)	//Pin Data Status Register
#define		PIO_IER			*((volatile unsigned int *) 0xFFFFF440)	//Interrupt Enable Register
#define		PIO_IDR			*((volatile unsigned int *) 0xFFFFF444)	//Interrupt Disable Register
#define		PIO_IMR			*((volatile unsigned int *) 0xFFFFF448)	//Interrupt Mask Register
#define		PIO_ISR			*((volatile unsigned int *) 0xFFFFF44C)	//Interrupt Status Register
#define		PIO_MDER		*((volatile unsigned int *) 0xFFFFF450)	//Multi-driver Enable Register
#define		PIO_MDDR		*((volatile unsigned int *) 0xFFFFF454)	//Multi-driver Disable Register
#define		PIO_MDSR		*((volatile unsigned int *) 0xFFFFF458)	//Multi-driver Status Register

#define		PIO_PUDR		*((volatile unsigned int *) 0xFFFFF460)	//Pull-up Disable Register
#define		PIO_PUER		*((volatile unsigned int *) 0xFFFFF464)	//Pull-up Enable Register
#define		PIO_PUSR		*((volatile unsigned int *) 0xFFFFF468)	//Pad Pull-up Status Register

#define		PIO_ASR			*((volatile unsigned int *) 0xFFFFF470)	//Peripheral A Select Register
#define		PIO_BSR			*((volatile unsigned int *) 0xFFFFF474)	//Peripheral B Select Register
#define		PIO_ABSR		*((volatile unsigned int *) 0xFFFFF478)	//AB Status Register

#define		PIO_OWER		*((volatile unsigned int *) 0xFFFFF4A0)	//Output Write Enable
#define		PIO_OWDR		*((volatile unsigned int *) 0xFFFFF4A4)	//Output Write Disable
#define		PIO_OWSR		*((volatile unsigned int *) 0xFFFFF4A8)	//Output Write Status Register

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         Pulse Width Modulation Controller                                              ///
///                                                                                                page.433///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		PWM_MR			*((volatile unsigned int *) 0xFFFCC000) // PWM Mode Register
#define		PWM_ENA			*((volatile unsigned int *) 0xFFFCC004) // PWM Enable Register
#define		PWM_DIS			*((volatile unsigned int *) 0xFFFCC008) // PWM Disable Register
#define		PWM_SR			*((volatile unsigned int *) 0xFFFCC00C) // PWM Status Register
#define		PWM_IER			*((volatile unsigned int *) 0xFFFCC010) // PWM Interrupt Enable Register
#define		PWM_IDR			*((volatile unsigned int *) 0xFFFCC014) // PWM Interrupt Disable Register
#define		PWM_IMR			*((volatile unsigned int *) 0xFFFCC018) // PWM Interrupt Mask Register
#define		PWM_ISR			*((volatile unsigned int *) 0xFFFCC01C) // PWM Interrupt Status Register

/*========================= Register definition for PWM3 peripheral ========================================*/
#define		PWM_CMR3		*((volatile unsigned int *) 0xFFFCC260) // Channel 3 Mode Register
#define		PWM_CDTY3		*((volatile unsigned int *) 0xFFFCC264) // Channel 3 Duty Cycle Register
#define		PWM_CPRD3		*((volatile unsigned int *) 0xFFFCC268) // Channel 3 Period Register
#define		PWM_CCNT3		*((volatile unsigned int *) 0xFFFCC26C) // Channel 3 Counter Register
#define		PWM_CUPD3		*((volatile unsigned int *) 0xFFFCC270) // Channel 3 Update Register
/*========================= Register definition for PWM2 peripheral ========================================*/
#define		PWM_CMR2		*((volatile unsigned int *) 0xFFFCC240) // Channel 2 Mode Register
#define		PWM_CDTY2		*((volatile unsigned int *) 0xFFFCC244) // Channel 2 Duty Cycle Register
#define		PWM_CPRD2		*((volatile unsigned int *) 0xFFFCC248) // Channel 2 Period Register
#define		PWM_CCNT2		*((volatile unsigned int *) 0xFFFCC24C) // Channel 2 Counter Register
#define		PWM_CUPD2		*((volatile unsigned int *) 0xFFFCC250) // Channel 2 Update Register
/*========================= Register definition for PWM1 peripheral ========================================*/
#define		PWM_CMR1		*((volatile unsigned int *) 0xFFFCC220) // Channel 1 Mode Register
#define		PWM_CDTY1		*((volatile unsigned int *) 0xFFFCC224) // Channel 1 Duty Cycle Register
#define		PWM_CPRD1		*((volatile unsigned int *) 0xFFFCC228) // Channel 1 Period Register
#define		PWM_CCNT1		*((volatile unsigned int *) 0xFFFCC22C) // Channel 1 Counter Register
#define		PWM_CUPD1		*((volatile unsigned int *) 0xFFFCC230) // Channel 1 Update Register
/*========================= Register definition for PWM0 peripheral ========================================*/
#define		PWM_CMR0		*((volatile unsigned int *) 0xFFFCC200) // Channel 0 Mode Register
#define		PWM_CDTY0		*((volatile unsigned int *) 0xFFFCC204) // Channel 0 Duty Cycle Register
#define		PWM_CPRD0		*((volatile unsigned int *) 0xFFFCC208) // Channel 0 Period Register
#define		PWM_CCNT0		*((volatile unsigned int *) 0xFFFCC20C) // Channel 0 Counter Register
#define		PWM_CUPD0		*((volatile unsigned int *) 0xFFFCC210) // Channel 0 Update Register

#define		PWM_DIVA		0
#define		PWM_PREA		8
#define		PWM_DIVB		16
#define		PWM_PREB		24

#define		PWM_CPRE		0
#define		PWM_CALG		8
#define		PWM_CPOL		9	 
#define		PWM_CPD			10

#define		PWM_CPRD		0
#define		PWM_CDTY		0

/*========================= PWM Channel Number =============================================================*/
#define		CHID0			0
#define		CHID1			1
#define		CHID2			2
#define		CHID3			3

/*========================= PWM Pin Number =================================================================*/
#define		PWM2			13
#define		PWM3			14

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         Power Management Controller                                                    ///
///                                                                                                page.222///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		PMC_PCER		*((volatile unsigned int *) 0xFFFFFC10)	//Peripheral Clock Enable Register

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         Advanced Interrupt Controller                                                  ///
///                                                                                                page.198///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		AIC_SMR			((volatile unsigned int *) 0xFFFFF000)
#define		AIC_SMR0		*((volatile unsigned int *) 0xFFFFF000)   //Source Mode Register 0
#define		AIC_SMR1		*((volatile unsigned int *) 0xFFFFF004)
#define		AIC_SMR2		*((volatile unsigned int *) 0xFFFFF008)
#define		AIC_SMR3		*((volatile unsigned int *) 0xFFFFF00C)
#define		AIC_SMR4		*((volatile unsigned int *) 0xFFFFF010)
#define		AIC_SMR5		*((volatile unsigned int *) 0xFFFFF014)
#define		AIC_SMR6		*((volatile unsigned int *) 0xFFFFF018)
#define		AIC_SMR7		*((volatile unsigned int *) 0xFFFFF01C)
#define		AIC_SMR8		*((volatile unsigned int *) 0xFFFFF020)
#define		AIC_SMR9		*((volatile unsigned int *) 0xFFFFF024)
#define		AIC_SMR10		*((volatile unsigned int *) 0xFFFFF028)
#define		AIC_SMR11		*((volatile unsigned int *) 0xFFFFF02C)
#define		AIC_SMR12		*((volatile unsigned int *) 0xFFFFF030)
#define		AIC_SMR13		*((volatile unsigned int *) 0xFFFFF034)
#define		AIC_SMR14		*((volatile unsigned int *) 0xFFFFF038)
#define		AIC_SMR15		*((volatile unsigned int *) 0xFFFFF03C)
#define		AIC_SMR16		*((volatile unsigned int *) 0xFFFFF040)
#define		AIC_SMR17		*((volatile unsigned int *) 0xFFFFF044)
#define		AIC_SMR18		*((volatile unsigned int *) 0xFFFFF048)
#define		AIC_SMR19		*((volatile unsigned int *) 0xFFFFF04C)
#define		AIC_SMR20		*((volatile unsigned int *) 0xFFFFF050)
#define		AIC_SMR21		*((volatile unsigned int *) 0xFFFFF054)
#define		AIC_SMR22		*((volatile unsigned int *) 0xFFFFF058)
#define		AIC_SMR23		*((volatile unsigned int *) 0xFFFFF05C)
#define		AIC_SMR24		*((volatile unsigned int *) 0xFFFFF060)
#define		AIC_SMR25		*((volatile unsigned int *) 0xFFFFF064)
#define		AIC_SMR26		*((volatile unsigned int *) 0xFFFFF068)
#define		AIC_SMR27		*((volatile unsigned int *) 0xFFFFF06C)
#define		AIC_SMR28		*((volatile unsigned int *) 0xFFFFF070)
#define		AIC_SMR29		*((volatile unsigned int *) 0xFFFFF074)
#define		AIC_SMR30		*((volatile unsigned int *) 0xFFFFF078)
#define		AIC_SMR31		*((volatile unsigned int *) 0xFFFFF07C)   //Source Mode Register 31

#define		AIC_SVR			((volatile unsigned int *) 0xFFFFF080) 
#define		AIC_SVR0		*((volatile unsigned int *) 0xFFFFF080)   //Source Vector Register 0
#define		AIC_SVR1		*((volatile unsigned int *) 0xFFFFF084)
#define		AIC_SVR2		*((volatile unsigned int *) 0xFFFFF088)
#define		AIC_SVR3		*((volatile unsigned int *) 0xFFFFF08C)
#define		AIC_SVR4		*((volatile unsigned int *) 0xFFFFF090)
#define		AIC_SVR5		*((volatile unsigned int *) 0xFFFFF094)
#define		AIC_SVR6		*((volatile unsigned int *) 0xFFFFF098)
#define		AIC_SVR7		*((volatile unsigned int *) 0xFFFFF09C)
#define		AIC_SVR8		*((volatile unsigned int *) 0xFFFFF0A0)
#define		AIC_SVR9		*((volatile unsigned int *) 0xFFFFF0A4)
#define		AIC_SVR10		*((volatile unsigned int *) 0xFFFFF0A8)
#define		AIC_SVR11		*((volatile unsigned int *) 0xFFFFF0AC)
#define		AIC_SVR12		*((volatile unsigned int *) 0xFFFFF0B0)
#define		AIC_SVR13		*((volatile unsigned int *) 0xFFFFF0B4)
#define		AIC_SVR14		*((volatile unsigned int *) 0xFFFFF0B8)
#define		AIC_SVR15		*((volatile unsigned int *) 0xFFFFF0BC)
#define		AIC_SVR16		*((volatile unsigned int *) 0xFFFFF0C0)
#define		AIC_SVR17		*((volatile unsigned int *) 0xFFFFF0C4)
#define		AIC_SVR18		*((volatile unsigned int *) 0xFFFFF0C8)
#define		AIC_SVR19		*((volatile unsigned int *) 0xFFFFF0CC)
#define		AIC_SVR20		*((volatile unsigned int *) 0xFFFFF0D0)
#define		AIC_SVR21		*((volatile unsigned int *) 0xFFFFF0D4)
#define		AIC_SVR22		*((volatile unsigned int *) 0xFFFFF0D8)
#define		AIC_SVR23		*((volatile unsigned int *) 0xFFFFF0DC)
#define		AIC_SVR24		*((volatile unsigned int *) 0xFFFFF0E0)
#define		AIC_SVR25		*((volatile unsigned int *) 0xFFFFF0E4)
#define		AIC_SVR26		*((volatile unsigned int *) 0xFFFFF0E8)
#define		AIC_SVR27		*((volatile unsigned int *) 0xFFFFF0EC)
#define		AIC_SVR28		*((volatile unsigned int *) 0xFFFFF0F0)
#define		AIC_SVR29		*((volatile unsigned int *) 0xFFFFF0F4)
#define		AIC_SVR30		*((volatile unsigned int *) 0xFFFFF0F8)
#define		AIC_SVR31		*((volatile unsigned int *) 0xFFFFF0FC)   //Source Vector Register 31

#define		AIC_IVR			*((volatile unsigned int *) 0xFFFFF100)   //Interrupt Vector Register
#define		AIC_FVR			*((volatile unsigned int *) 0xFFFFF104)   //FIQ Interrupt Vector Register
#define		AIC_ISR			*((volatile unsigned int *) 0xFFFFF108)   //Interrupt Status Register
#define		AIC_IPR			*((volatile unsigned int *) 0xFFFFF10C)   //Interrupt Pending Register
#define		AIC_IMR			*((volatile unsigned int *) 0xFFFFF110)   //Interrupt Mask Register
#define		AIC_CISR		*((volatile unsigned int *) 0xFFFFF114)   //Core Interrupt Status Register

#define		AIC_IECR		*((volatile unsigned int *) 0xFFFFF120)   //Interrupt Enable Command Register
#define		AIC_IDCR		*((volatile unsigned int *) 0xFFFFF124)   //Interrupt Disable Command Register
#define		AIC_ICCR		*((volatile unsigned int *) 0xFFFFF128)   //Interrupt Clear Command Register
#define		AIC_ISCR		*((volatile unsigned int *) 0xFFFFF12C)   //Interrupt Set Command Register
#define		AIC_EOICR		*((volatile unsigned int *) 0xFFFFF130)   //End of Interrupt Command Register
#define		AIC_SPU			*((volatile unsigned int *) 0xFFFFF134)   //Spurious Interrupt Vector Register
#define		AIC_DCR			*((volatile unsigned int *) 0xFFFFF138)   //Debug Control Register

#define		AIC_FFER		*((volatile unsigned int *) 0xFFFFF140)   //Fast Forcing Enable Register
#define		AIC_FFDR		*((volatile unsigned int *) 0xFFFFF144)   //Fast Forcing Disable Register
#define		AIC_FFSR		*((volatile unsigned int *) 0xFFFFF148)   //Fast Forcing Status Register

/*========================= AIC Source Mode Register =======================================================*/
#define		AIC_PRIOR						0
#define		AIC_SRCTYPE						5

#define		AIC_SRCTYPE_INT_POS_LEVEL		1
#define		AIC_SRCTYPE_INT_HIGH_LEVEL		2

#define		AIC_PRIOR_LOWEST				0
#define		AIC_PRIOR_HIGHEST				7

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         Timer/Counter (TC)                                                             ///
///                                                                                                page.405///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		TC0_CCR			*((volatile unsigned int *) 0xFFFA0000) //Channel Control Register
#define		TC0_CMR			*((volatile unsigned int *) 0xFFFA0004)	//Channel Mode Register
#define		TC0_CV			*((volatile unsigned int *) 0xFFFA0010)	//Counter Value
#define		TC0_RA			*((volatile unsigned int *) 0xFFFA0014)	//Register A
#define		TC0_RB			*((volatile unsigned int *) 0xFFFA0018)	//Register B
#define		TC0_RC			*((volatile unsigned int *) 0xFFFA001C)	//Register C
#define		TC0_SR			*((volatile unsigned int *) 0xFFFA0020)	//Status Register
#define		TC0_IER			*((volatile unsigned int *) 0xFFFA0024)	//Interrupt Enable Register
#define		TC0_IDR			*((volatile unsigned int *) 0xFFFA0028)	//Interrupt Disable Register
#define		TC0_IMR			*((volatile unsigned int *) 0xFFFA002C) //Interrupt Mask Register

#define		TC1_CCR			*((volatile unsigned int *) 0xFFFA0040) //Channel Control Register
#define		TC1_CMR			*((volatile unsigned int *) 0xFFFA0044)	//Channel Mode Register
#define		TC1_CV			*((volatile unsigned int *) 0xFFFA0050)	//Counter Value
#define		TC1_RA			*((volatile unsigned int *) 0xFFFA0054)	//Register A
#define		TC1_RB			*((volatile unsigned int *) 0xFFFA0058)	//Register B
#define		TC1_RC			*((volatile unsigned int *) 0xFFFA005C)	//Register C
#define		TC1_SR			*((volatile unsigned int *) 0xFFFA0060)	//Status Register
#define		TC1_IER			*((volatile unsigned int *) 0xFFFA0064)	//Interrupt Enable Register
#define		TC1_IDR			*((volatile unsigned int *) 0xFFFA0068)	//Interrupt Disable Register
#define		TC1_IMR			*((volatile unsigned int *) 0xFFFA006C) //Interrupt Mask Register

#define		TC2_CCR			*((volatile unsigned int *) 0xFFFA0080) //Channel Control Register
#define		TC2_CMR			*((volatile unsigned int *) 0xFFFA0084)	//Channel Mode Register
#define		TC2_CV			*((volatile unsigned int *) 0xFFFA0090)	//Counter Value
#define		TC2_RA			*((volatile unsigned int *) 0xFFFA0094)	//Register A
#define		TC2_RB			*((volatile unsigned int *) 0xFFFA0098)	//Register B
#define		TC2_RC			*((volatile unsigned int *) 0xFFFA009C)	//Register C
#define		TC2_SR			*((volatile unsigned int *) 0xFFFA00A0)	//Status Register
#define		TC2_IER			*((volatile unsigned int *) 0xFFFA00A4)	//Interrupt Enable Register
#define		TC2_IDR			*((volatile unsigned int *) 0xFFFA00A8)	//Interrupt Disable Register
#define		TC2_IMR			*((volatile unsigned int *) 0xFFFA00AC) //Interrupt Mask Register

#define		TC_BCR			*((volatile unsigned int *) 0xFFFA00C0) //TC Block Control Register
#define		TC_BMR			*((volatile unsigned int *) 0xFFFA00C4) //TC Block Mode Register

/*========================= TC Channel Control Register ====================================================*/
#define		TC_CLKEN		0
#define		TC_CLKDIS		1
#define		TC_SWTRG		2		

/*========================= TC Interrupt Disable Register and Status Register ==============================*/
#define		TC_COVFS		0
#define		TC_LOVRS		1
#define		TC_CPAS			2
#define		TC_CPBS			3
#define		TC_CPCS			4
#define		TC_LDRAS		5
#define		TC_LDRBS		6
#define		TC_ETRGS		7
#define		TC_CLKSTA		16
#define		TC_MTIOA		17
#define		TC_MTIOB		18

/*========================= TC Channel Mode Register : Capture Mode ========================================*/
#define		TC_TCCLKS		0
#define		TC_CLKI			3
#define		TC_BURST		4
#define		TC_LDBSTOP		6
#define		TC_LDBDIS		7
#define		TC_ETRGEDG		8
#define		TC_ABETRG		10
#define		TC_CPCTRG		14
//#define	WAVE = 0		15
#define		TC_LDRA			16
#define		TC_LDRB			18

/*========================= TC Channel Mode Register : Waveform Mode ======================================*/
#define		TC_TCCLKS		0
#define		TC_CLKI			3
#define		TC_BURST		4
#define		TC_CPCSTOP		6
#define		TC_CPCDIS		7
#define		TC_EEVTEDG		8
#define		TC_EEVT			10
#define		TC_ENETRG		12
#define		TC_WAVSEL		13
//#define	WAVE = 1		15
#define		TC_ACPA			16
#define		TC_ACPC			18
#define		TC_AEEVT		20
#define		TC_ASWTRG		22
#define		TC_BCPB			24
#define		TC_BCPC			26
#define		TC_BEEVT		28
#define		TC_BSWTRG		30

/*========================= Clock Selection ==============================================================*/
#define		TIMER_CLOCK1	0
#define		TIMER_CLOCK2	1
#define		TIMER_CLOCK3	2
#define		TIMER_CLOCK4	3
#define		TIMER_CLOCK5	4

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         Debug Unit (DBGU)                                                              ///
///                                                                                                page.247///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		DBGU_CR			*((volatile unsigned int *) 0xFFFFF200)	//Control Register
#define		DBGU_MR			*((volatile unsigned int *) 0xFFFFF204)	//Mode Register
#define		DBGU_IER		*((volatile unsigned int *) 0xFFFFF208)	//Interrupt Enable Register
#define		DBGU_IDR		*((volatile unsigned int *) 0xFFFFF20C)	//Interrupt Disable Register
#define		DBGU_IMR		*((volatile unsigned int *) 0xFFFFF210)	//Interrupt Mask Register
#define		DBGU_SR			*((volatile unsigned int *) 0xFFFFF214)	//Status Register
#define		DBGU_RHR		*((volatile unsigned int *) 0xFFFFF218)	//Receive Holding Register
#define		DBGU_THR		*((volatile unsigned int *) 0xFFFFF21C)	//Transmit Holding Register
#define		DBGU_BRGR		*((volatile unsigned int *) 0xFFFFF220)	//Baud Rate Generator Register
#define		DBGU_CIDR		*((volatile unsigned int *) 0xFFFFF240)	//Chip ID Register
#define		DBGU_EXID		*((volatile unsigned int *) 0xFFFFF244)	//Chip ID Extension Register
#define		DBGU_FNR		*((volatile unsigned int *) 0xFFFFF248)	//Force NTRST Register

/*========================= DBGU_CR Register ===============================================================*/

#define		DBGU_RSTRX		2
#define		DBGU_RSTTX		3
#define		DBGU_RXEN		4
#define		DBGU_RXDIS		5
#define		DBGU_TXEN		6
#define		DBGU_TXDIS		7
#define		DBGU_RSTSTA		8

/*========================= DBGU_IER, _IDR, _IMR, _SR Register =============================================*/
#define		DBGU_RXRDY 		0
#define		DBGU_TXRDY 		1
#define		DBGU_ENDRX 		3
#define		DBGU_ENDTX 		4
#define		DBGU_OVRE 		5
#define		DBGU_FRAME 		6
#define		DBGU_PARE 		7
#define		DBGU_TXEMPTY 	9
#define		DBGU_TXBUFE 	11
#define		DBGU_RXBUFF 	12
#define		DBGU_COMMTX 	30
#define		DBGU_COMMRX 	31

#define		DRXD			9
#define		DTXD			10

#define		RXTDIS			1
#define		TXTDIS			9

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         Advanced Interrupt Controller ( ADC )                                          ///
///                                                                                                page.198///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		ADC_CR			*((volatile unsigned int *)0xFFFd8000) // control register
#define		ADC_MR			*((volatile unsigned int *)0xFFFd8004) // mode register
#define		ADC_CHER		*((volatile unsigned int *)0xFFFd8010) // channel enable register
#define		ADC_CHDR		*((volatile unsigned int *)0xFFFd8014) // channel disable register
#define		ADC_CHSR		*((volatile unsigned int *)0xFFFd8018) // chennel status register
#define		ADC_SR			*((volatile unsigned int *)0xFFFd801C) // status register
#define		ADC_LCDR		*((volatile unsigned int *)0xFFFd8020) // last converted data register
#define		ADC_IER			*((volatile unsigned int *)0xFFFd8024) // interrupt enable register
#define		ADC_IDR			*((volatile unsigned int *)0xFFFd8028) // interrupt disable register
#define		ADC_IMR			*((volatile unsigned int *)0xFFFd802C) // interrupt mask register
#define		ADC_CDR0		*((volatile unsigned int *)0xFFFd8030) // channel data register 0
#define		ADC_CDR1		*((volatile unsigned int *)0xFFFd8034) // channel data register 1
#define		ADC_CDR2		*((volatile unsigned int *)0xFFFd8038) // channel data register 2
#define		ADC_CDR3		*((volatile unsigned int *)0xFFFd803C) // channel data register 3
#define		ADC_CDR4		*((volatile unsigned int *)0xFFFd8040) // channel data register 4
#define		ADC_CDR5		*((volatile unsigned int *)0xFFFd8044) // channel data register 5
#define		ADC_CDR6		*((volatile unsigned int *)0xFFFd8048) // channel data register 6
#define		ADC_CDR7		*((volatile unsigned int *)0xFFFd804C) // channel data register 7

#define		ADC_SWRST		0
#define		ADC_START		1

#define		ADC_CH0			0
#define		ADC_CH1			1
#define		ADC_CH2			2
#define		ADC_CH3			3
#define		ADC_CH4			4
#define		ADC_CH5			5
#define		ADC_CH6			6
#define		ADC_CH7			7

#define		ADC_TRGEN		0
#define		ADC_TRGSEL		1
#define		ADC_LOWRES		4
#define		ADC_SLEEP		5
#define		ADC_PRESCAL		8
#define		ADC_STARTUP		16
#define		ADC_SHTIM		24

#define		ADC_EOC0		0
#define		ADC_EOC1		1
#define		ADC_EOC2		2
#define		ADC_EOC3		3
#define		ADC_EOC4		4
#define		ADC_EOC5		5
#define		ADC_EOC6		6
#define		ADC_EOC7		7
#define		ADC_DRDY		16

/*========================= Peripheral DMA Controller (PDC) ================================================*/
#define 	PERIPH_PTCR		*((volatile unsigned int *) 0xFFFFF320)
#define		PERIPH_PTSR		*((volatile unsigned int *) 0xFFFFF324)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        ///
///                         UART Bluetooth                                                                 ///
///                                                                                                        ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define		US0_CR			*((volatile unsigned int *)0xFFFC0000)
#define		US0_MR			*((volatile unsigned int *)0xFFFC0004)
#define		US0_BRGR		*((volatile unsigned int *)0xFFFC0020)
#define		US0_CSR			*((volatile unsigned int *)0xFFFC0014)
#define		US0_THR 		*((volatile unsigned int *)0xFFFC001C)
#define		US0_RHR 		*((volatile unsigned int *)0xFFFC0018)
#define		US0_IDR			*((volatile unsigned int *)0xFFFC000C)
#define		US0_IER			*((volatile unsigned int *)0xFFFC0008)
#define		US0_IMR 		*((volatile unsigned int *)0xFFFC0010)

#define		RXD0			5
#define		TXD0			6

#define		USART_MODE		0
#define		USCLKS			4
#define		CHRL			6
#define		SYNC			8
#define		PAR				9
#define		NBSTOP			12

#define		US_RSTRX		2
#define		US_RSTTX		3
#define		US_RXEN			4
#define		US_RXDIS		5
#define		US_TXEN			6
#define		US_TXDIS		7
#define		US_RSTSTA		8

#define		US_RXRDY		0
#define		US_TXRDY		1

#define		MCU				48000000
#define		BAUD_RATE		9600
#define		CD				MCU/(16*BAUD_RATE)

////////////////////////////////////////////////////
//                                                //
//             Peripheral Identifiers             //
//                                         page.34//
////////////////////////////////////////////////////

#define		AIC				0	// Advanced Interrupt Controller
#define		SYSC			1	// System
#define		PIOA			2	// Parallel I/O Controller A

#define		ADC				4	// Analog-to Digital Converter
#define		SPI				5	// Serial Peripheral Interface
#define		US0				6	// USART 0
#define		US1				7	// USART 1
#define		SSC				8	// Synchronous Serial Controller
#define		TWI				9	// Two-wire Interface 
#define		PWMC			10	// PWM Controller
#define		UDP				11	// USB Device Port
#define		TC0				12	// Timer/Counter 0
#define		TC1				13	// Timer/Counter 1
#define		TC2				14	// Timer/Counter 2

#define		AIC_IRQ0		30	// Advanced Interrupt Controller
#define		AIC_IRQ1		31	// Advanced Interrupt Controller

#endif	//__ARM_H__
