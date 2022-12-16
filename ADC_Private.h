




#define ADMUX       *((u8*)0x27)
#define ADCSRA      *((u8*)0x26)

#define ADC_Data        *((u16*)0x24)


#define REFS0       6
#define REFS1       7
#define ADLAR       5
#define MUX0        0
#define MUX1        1
#define MUX2        2
#define MUX3        3
#define MUX4        4


#define ADPS0       0
#define ADPS1       1
#define ADPS2       2
#define ADIE        3
#define ADIF        4
#define ADATE       5
#define ADEN        7
#define ADSC        6


#define AREF			0
#define VCC				1
#define INTERNAL_REF	3

#define Left		0
#define Right		1


#define Factor_2     00000000
#define Factor_4     00000010
#define Factor_8     00000011
#define Factor_16    00000100
#define Factor_32    00000101
#define Factor_64    00000110
#define Factor_128   00000111
