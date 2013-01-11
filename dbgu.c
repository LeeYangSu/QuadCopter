#include "arm.h"

extern float motor_pwm3_speed;
extern float motor_pwm2_speed;

extern float TARGET_ANGLE;

extern float ui_duty2;
extern float ui_duty3;

extern int cnt_;

extern float kp;
extern float ki;
extern float kd;

extern unsigned int P_cnt;
extern unsigned int I_cnt;
extern unsigned int D_cnt;

extern float kp_temp;

void UART0_RET(void)
{
	unsigned char ch = 0;

	ch = UART0_GetChar();

	switch(ch)
	{
		case 'Q':
		case 'q':
			PWM2_dutyset(0);
			PWM3_dutyset(0);
			PIO_SODR = (1<<switch_pin);
			break;
			
		case 'W':
		case 'w':
			cnt_ = 100;
			PIO_CODR = (1<<switch_pin);
			PWM2_dutyset(ui_duty2 + 130);
			PWM3_dutyset(ui_duty3 + 130);
			break;
			
		case 'K' :
		case 'k' :
			TARGET_ANGLE = TARGET_ANGLE  + 20;
			if(TARGET_ANGLE > 20)
			{
				TARGET_ANGLE = 20;
			}	
			break;

		case 'L' :
		case 'l' :
			TARGET_ANGLE =  TARGET_ANGLE - 20;
			if(TARGET_ANGLE < -20)
			{
				TARGET_ANGLE = -20;
			}
			break;

		case 'H' :
		case 'h' :
			TARGET_ANGLE = TARGET_ANGLE  + 10;
			if(TARGET_ANGLE > 10)
			{
				TARGET_ANGLE = 10;
			}	
			break;

		case 'G' :
		case 'g' :
			TARGET_ANGLE =  TARGET_ANGLE - 10;
			if(TARGET_ANGLE < -10)
			{
				TARGET_ANGLE = -10;
			}
			break;

		case 'J' :
		case 'j' :
			TARGET_ANGLE = 0;
			break;

		case 'P' :
			kp = kp + 0.01;
			++P_cnt;
			break;

		case 'p' :
			kp = kp - 0.01;
			--P_cnt;
			break;
			
		case 'I' :
			ki = ki + 0.0001;
			++I_cnt;
			break;

		case 'i' :
			ki = ki - 0.0001;
			--I_cnt;
			break;

		case 'D' :
			kd = kd + 0.001;
			++D_cnt;
			break;

		case 'd' :
			kd = kd - 0.001;
			--D_cnt;
			break;

		case 'm' :
			cnt_ = 100;
			kp = kp_temp;
			P_cnt = P_cnt + 1;
			kp_temp = kp_temp + 0.01;
			break;

		case 'n' :
			kp = 0;
			motor_pwm2_speed = 200;
			motor_pwm3_speed = 200;
			PWM2_dutyset(motor_pwm2_speed);
			PWM3_dutyset(motor_pwm3_speed);
			cnt_ = 110;
			break;
			
		default:	
			PWM2_dutyset(ui_duty2);
			PWM3_dutyset(ui_duty3);
			break;
	}

}

void Init_DBGU()
{
	DBGU_CR  = ( 1 << DBGU_RSTRX ) | ( 1 << DBGU_RSTTX );       /* Receiver and Trnasmitter is Reset */
	DBGU_IDR = ( 1 << DBGU_RXRDY ) | ( 1 << DBGU_TXRDY ) | ( 1 << DBGU_ENDRX ) | ( 1 << DBGU_ENDTX  ) |
		       ( 1 << DBGU_OVRE )  | ( 1 << DBGU_FRAME ) | ( 1 << DBGU_PARE  ) | ( 1 << DBGU_TXEMPTY) |
		       ( 1 << DBGU_TXBUFE) | ( 1 << DBGU_RXBUFF) | ( 1 << DBGU_COMMTX) | ( 1 << DBGU_COMMRX );   /* all Interrupt Disable */

	PIO_ASR = (1<<DRXD) | (1<<DTXD);            // Peripheral A Select
	PIO_PDR = (1<<DRXD) | (1<<DTXD);            // I/O Disable 

	DBGU_BRGR = 26;                             // 115200bit  / 8  / 1024  = 14kbyte speed
	DBGU_MR   = 0x00000000;                     // Mode Register : Normal Mode, Even Parity

	PERIPH_PTCR = (1<<RXTDIS) | (1<<TXTDIS);    // DMA Off

	DBGU_CR = (1<<DBGU_RXEN) | (1<<DBGU_TXEN);  // Receiver and Transmitter On

	return ;
}

void INIT_UART0(void)
{
	/* uart0 clock enable */
	PMC_PCER = ( 1 << US0 );

	/* peripheral A select */
	PIO_ASR = ( 1 << RXD0 ) | ( 1 << TXD0 );		 	

	PIO_PDR = ( 1 << RXD0 ) |        /* Enable RxD0 Pin */
		      ( 1 << TXD0 );         /* Enalbe TxD0 Pin */

	US0_CR  = ( 1 << US_RSTRX ) |    /* Reset Receiver      */
		      ( 1 << US_RSTTX ) |    /* Reset Transmitter   */
		      ( 1 << US_RXDIS ) |    /* Receiver Disable    */
		      ( 1 << US_TXDIS );     /* Transmitter Disable */

	US0_IDR = ( 1 << US_RXRDY ) |    /* Reciever Ready interrupt Disable */
		      ( 1 << US_TXRDY );     /* Transmitter Ready interrupt Disable */

	US0_MR  = ( 0 << USART_MODE ) |  /* Normal Mode */
		      ( 0 << USCLKS ) |      /* Clock = MCK */
		      ( 3 << CHRL ) |        /* 8-bit Data  */
		      ( 0 << SYNC ) |
		      ( 4 << PAR ) |         /* No Parity   */
		      ( 0 << NBSTOP );       /* 1 Stop Bit  */

	US0_BRGR = 313;                  /* 9600 Baud Rate  */

	PERIPH_PTCR = (1 << RXTDIS) | (1 << TXTDIS);	
	US0_CR = ( 1 << US_RXEN ) |      /* Receiver Enable     */
		     ( 1 << US_TXEN );       /* Transmitter Enable  */

	/* RX interrupt enable */
	US0_IER = ( 1 << US_RXRDY );	

	/* us0 interrupt disable */
	AIC_IDCR = ( 1 << US0 );

	/* calling function */
	AIC_SVR[US0] = (unsigned int)UART0_RET;	

	/* priority LOWEST */
	AIC_SMR[US0] = ( AIC_SRCTYPE_INT_HIGH_LEVEL << AIC_SRCTYPE ) | /* internal : Positive edge triggered */
                                                                   /* external : Negative edge triggered */
				   ( AIC_PRIOR_HIGHEST << AIC_PRIOR );        

	/* Interrupt Clear Command Register */
	AIC_ICCR = ( 1 << US0 );	

	/* US0 Interrupt Set */
	AIC_ISCR = ( 1 << US0 );	

	/* US0 Interrupt On */
	AIC_IECR = ( 1 << US0 );

	return ;
}

void DBGU_string(unsigned char *uc_string)
{	

	if(0 == uc_string)
	{
		return ;
	}
	while(0 != *uc_string)
	{
		while(0 == (DBGU_SR & (1<<DBGU_TXRDY)));
		DBGU_THR = *uc_string;
		++uc_string;
	}
	return ;
}

unsigned char DBGU_GetChar(void)
{
	while(0 == (DBGU_SR & (1<<DBGU_RXRDY)));

	return (DBGU_RHR);
}

void DBGU_PutChar(unsigned char c)
{
	/* Wait for the transmitter to be ready */
	while(0 == (DBGU_SR & (1<<DBGU_TXRDY)));

	/* Send character */
	DBGU_THR = c;
}

unsigned char UART0_GetChar(void)
{
	while(0 == (US0_CSR & (1<<US_RXRDY)));

	return (US0_RHR);
}

void UART0_PutChar(unsigned char c)
{
	/* Wait for the transmitter to be ready */
	while (0 == (US0_CSR & ( 1 <<US_TXRDY)));

	/* Send character */
	US0_THR  = c;
}


/*
		case 'A':
		case 'a':		
			ui_duty3 = ui_duty3 + 100;

			if(ui_duty3 > 40000)
			{
				ui_duty3 = 39000;
			}
			ch = 0;

			PWM3_dutyset(ui_duty3);
			break;
		case 'S':
		case 's':			
			ui_duty3 = ui_duty3 - 100;

			if(ui_duty3 < 100)
			{
				ui_duty3 = 1;
			}
			ch = 0;
			PWM3_dutyset(ui_duty3);
			break;
		case 'K':
		case 'k':		
			ui_duty2 = ui_duty2 + 100;

			if(ui_duty2 > 40000)
			{
				ui_duty2 = 39000;
			}
			ch = 0;

			PWM2_dutyset(ui_duty2);
			break;
		case 'L':
		case 'l':			
			ui_duty2 = ui_duty2 - 100;

			if(ui_duty2 < 100)
			{
				ui_duty2 = 1;
			}
			ch = 0;
			PWM2_dutyset(ui_duty2);
			break;
		case '1':	
			ui_duty2 = ui_duty2 + 100;
			ui_duty3 = ui_duty3 + 100;
			
			if(ui_duty2 > 40000)
			{
				ui_duty2 = 39000;
			}
			if(ui_duty3 > 40000)
			{
				ui_duty3 = 39000;
			}
			ch = 0;

			PWM2_dutyset(ui_duty2);
			PWM3_dutyset(ui_duty3);
			break;
		case '2':
			ui_duty2 = ui_duty2 - 100;
			ui_duty3 = ui_duty3 - 100;

			if(ui_duty2 < 100)
			{
				ui_duty2 = 1;
			}
			if(ui_duty3 < 100)
			{
				ui_duty3 = 1;
			}

			ch = 0;

			PWM2_dutyset(ui_duty2);
			PWM3_dutyset(ui_duty3);
			break;
		case 'Q':
		case 'q':
			PIO_CODR = (1<<switch_pin);
			break;
		case 'W':
		case 'w':	
			PIO_SODR = (1<<switch_pin);
			break;
		default:	
			break;
	}

	switch(ch)
	{
		case 'Q':
		case 'q':
			PIO_CODR = (1<<switch_pin);
			break;
			
		case 'W':
		case 'w':	
			PIO_SODR = (1<<switch_pin);
			break;
	*/
		/*case 'K':	
		case 'k':	
			ui_duty2 = ui_duty2 + 100;
			ui_duty3 = ui_duty3 + 100;
			
			if(ui_duty2 > 40000)
			{
				ui_duty2 = 39000;
			}
			if(ui_duty3 > 40000)
			{
				ui_duty3 = 39000;
			}
			ch = 0;
			PWM2_dutyset(ui_duty2);
			PWM3_dutyset(ui_duty3);
			cnt_ = 100;
			
			break;
		*/

