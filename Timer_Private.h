




void __vector_11(void)          __attribute__((signal));


#define TCCR0       *((u8*)0x53)
#define TCNT0       *((u8*)0x52)
#define TIMSK      *((u8*)0x59)
#define TIFR       *((u8*)0x58)

#define WGM00      6
#define WGM01      3
#define CS02       2
#define CS01       1
#define CS00       0

#define TOIE0       0

#define No_Clock                0
#define No_Prescaler            1
#define Prescaler_8             8
#define Prescaler_64            64
#define Prescaler_256           256
#define Prescaler_1024          1024
#define External_Falling        6
#define External_Rising         7

#define frequency 		8000000
     


