#ifndef __DBGU_H__
#define __DBGU_H__

void Init_DBGU();
void DBGU_string(unsigned char *uc_string);
unsigned char DBGU_GetChar(void );
void DBGU_PutChar(unsigned char );
void INIT_UART0(void);
void UART0_RET(void);

void UART0_PutChar(unsigned char c);
unsigned char UART0_GetChar(void);

#endif	//__DBGU_H__
