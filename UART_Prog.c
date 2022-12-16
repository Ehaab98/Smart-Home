#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "UART_Private.h"
#include "UART_Cfg.h"

static void (*RX_PFun) (void);
static void (*UDR_PFun) (void);
static void (*TX_PFun) (void);

u8 UCSRC_help = 0b10000000;

void UART_VidInit(void)
{


  /*Receiver Interrupt config*/
#if RX_Int == Enable
	SET_BIT(UCSRB, RXCIE);
#elif RX_Int == Disable
  CLR_BIT(UCSRB, RXCIE);
#endif

  /*Transmit shift interrupt config*/
#if TX_Int == Enable
  SET_BIT(UCSRB, TXCIE);
#elif TX_Int == Disable
  CLR_BIT(UCSRB, TXCIE);
#endif

  /*UDR Interrupt config*/
#if UDR_Int == Enable
  SET_BIT(UCSRB, UDRIE);
#elif UDR_Int == Disable
  CLR_BIT(UCSRB, UDRIE);
#endif

  /*Transmitter pin control*/
#if TX_Control == Enable
  SET_BIT(UCSRB, TXEN);
#elif TX_Control == Disable
  CLR_BIT(UCSRB, TXEN);
#endif

  /*Receiver Pin control*/
#if RX_Control == Enable
  SET_BIT(UCSRB, RXEN);
#elif RX_Control == Disable
  CLR_BIT(UCSRB, RXEN);
#endif

  /*UASRT Mode:*/
#if USART_Mode == Async
  CLR_BIT(UCSRC_help, UMSEL);

  /*Double speed mood Config*/
#if U2X_Mode == Enable
  SET_BIT(UCSRA, U2X);

#elif U2X_Mode == Disable
  CLR_BIT(UCSRA, U2X);
#endif

#elif USART_Mode == Sync
  SET_BIT(UCSRC_help, UMSEL);

  /*Select Clock Polarity*/
#if Clock_Polarity == Falling
  CLR_BIT(UCSRC_help, UCPOL);
#elif Clock_Polarity == Rising
  SET_BIT(UCSRC_help, UCPOL);
#endif

#endif

  /*Parity Mode*/
#if Parity_Mode == Disable
  CLR_BIT(UCSRC_help, UPM0);
  CLR_BIT(UCSRC_help, UPM1);
#elif Parity_Mode == Even_Parity
  CLR_BIT(UCSRC_help, UPM0);
  SET_BIT(UCSRC_help, UPM1);
#elif Parity_Mode == Odd_Parity
  SET_BIT(UCSRC_help, UPM0);
  SET_BIT(UCSRC_help, UPM1);
#endif

  /*Set one stop bit*/
#if StopBit_Num == Stop1
  CLR_BIT(UCSRC_help, USBS);
#elif StopBit_Num == Stop2
  SET_BIT(UCSRC_help, USBS);
#endif

  /*Set data bits*/
#if DataBits_Num == Bit_5
  CLR_BIT(UCSRC_help, UCSZ0);
  CLR_BIT(UCSRC_help, UCSZ1);
  CLR_BIT(UCSRB, UCSZ2);
#elif DataBits_Num == Bit_6
  SET_BIT(UCSRC_help, UCSZ0);
  CLR_BIT(UCSRC_help, UCSZ1);
  CLR_BIT(UCSRB, UCSZ2);
#elif DataBits_Num == Bit_7
  CLR_BIT(UCSRC_help, UCSZ0);
  SET_BIT(UCSRC_help, UCSZ1);
  CLR_BIT(UCSRB, UCSZ2);
#elif DataBits_Num == Bit_8
  SET_BIT(UCSRC_help, UCSZ0);
  SET_BIT(UCSRC_help, UCSZ1);
  CLR_BIT(UCSRB, UCSZ2);
#elif DataBits_Num == Bit_9
  SET_BIT(UCSRC_help, UCSZ0);
  SET_BIT(UCSRC_help, UCSZ1);
  Set_BIT(UCSRB, UCSZ2);
#endif

  /*Set UCSRC Reg*/
  UCSRC = UCSRC_help;

  /*Set Baud rate to 9600*/
  UBRRL = (u8)51;
  UBRRH = (u8)0;

}

u8 UART_U8Read()
{
  u8 RXC_flag = GET_BIT(UCSRA, RXC);
  u8 RXB;
  while (RXC_flag == 0)
  {
	  RXC_flag = GET_BIT(UCSRA, RXC);
    /* Do Nothing */
  }
  RXB = UDR;
  return RXB;
  
}

void UART_VidSend(u8 Copy_U8Data)
{
  u8 UDR_flag = GET_BIT(UCSRA, UDRE);
  while (UDR_flag == 0)
  {
	  UDR_flag = GET_BIT(UCSRA, UDRE);
    /* Do Nothing */
  }
  UDR = Copy_U8Data;
}

/*Call Back Setter RX*/
void RX_setCallBack(void (*rxptr)( void))
{
	RX_PFun = rxptr;
}
/*ISR for RX*/
void __vector_13(void)
{
    RX_PFun();
}

/*Call Back Setter UDR*/
void UDR_setCallBack(void (*udrptr)( void))
{
	UDR_PFun = udrptr;
}
/*ISR for UDR*/
void __vector_14(void)
{
    UDR_PFun();
}

/*Call Back Setter TX*/
void TX_setCallBack(void (*txptr)( void))
{
	TX_PFun = txptr;
}
/*ISR for UDR*/
void __vector_15(void)
{
    TX_PFun();
}
