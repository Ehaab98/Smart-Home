


void __vector_13(void)          __attribute__((signal));
void __vector_14(void)          __attribute__((signal));
void __vector_15(void)          __attribute__((signal));



#define UDR        *((u8*)0x2C)
#define UCSRA      *((u8*)0x2B)
#define UCSRB      *((u8*)0x2A)
#define UCSRC      *((u8*)0x40)
#define UBRRH      *((u8*)0x40)
#define UBRRL      *((u8*)0x29)

#define RXC          7
#define UDRE         5
#define U2X          1

#define RXCIE           7
#define TXCIE           6
#define UDRIE           5
#define RXEN            4
#define TXEN            3
#define UCSZ2           2
#define RXB8            1
#define TXB8            0

#define URSEL           7
#define UMSEL           6
#define UPM1            5
#define UPM0            4
#define USBS            3
#define UCSZ1           2
#define UCSZ0           1
#define UCSZ2           2
#define UCPOL			0

#define Enable			1
#define Disable			0

#define Async			0
#define Sync			1

#define Odd_Parity		1
#define Even_Parity		2

#define Stop1			1
#define Stop2			2

#define Bit_5			5
#define Bit_6			6
#define Bit_7			7
#define Bit_8			8
#define Bit_9			9

#define Rising			0
#define Falling			1
