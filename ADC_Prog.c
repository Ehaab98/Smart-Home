#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "ADC_Private.h"
#include "ADC_Cfg.h"
#include <avr/delay.h>




void ADC_VidInit(void)
{
	/*Enable ADC*/
	SET_BIT(ADCSRA, ADEN);

	/*Disable Interupt*/
	CLR_BIT(ADCSRA, ADIE);

	/*Set Ref = External source*/
#if VREF == AREF
    CLR_BIT(ADMUX, REFS0);
    CLR_BIT(ADMUX, REFS1);

    /*Set Ref = 5v*/
#elif VREF == VCC
    SET_BIT(ADMUX, REFS0);
    CLR_BIT(ADMUX, REFS1);

    /*Set Ref = 2.56v*/
#elif VREF == INTERNAL_REF
    SET_BIT(ADMUX, REFS0);
    SET_BIT(ADMUX, REFS1);

#else
	#error "Wrong input reference volt"
#endif

    /*Right Readout*/
	#if ReadOut == Right
    CLR_BIT(ADMUX, ADLAR);

    /*Left Readout*/
	#elif ReadOut == Left
    SET_BIT(ADMUX, ADLAR);

	#endif

    /*Disable Auto Trigger*/
    CLR_BIT(ADCSRA, ADATE);

    /*Division Factor = 2*/
#if Div_factor == 2
    ADCSRA = ADCSRA | Factor_2;

    /*Division Factor = 4*/
#elif Div_factor == 4
    ADCSRA = ADCSRA | Factor_4;

    /*Division Factor = 8*/
#elif Div_factor == 8
    ADCSRA = ADCSRA | Factor_8;

    /*Division Factor = 16*/
#elif Div_factor == 16
    ADCSRA = ADCSRA | Factor_16;

    /*Division Factor = 32*/
#elif Div_factor == 32
    ADCSRA = ADCSRA | Factor_32;

    /*Division Factor = 64*/
#elif Div_factor == 64
    ADCSRA = ADCSRA | Factor_64;

    /*Division Factor = 128*/
#elif Div_factor == 128
    ADCSRA = ADCSRA | Factor_128;

#else
	#error "Wrong input division factor"
#endif

}



u16 ADC_U8ReadOut (u8 Copy_U8Channel)
{

    /*Set Channel*/
    ADMUX = ADMUX & 0b11100000;
    ADMUX = ADMUX | (Copy_U8Channel & 0x0f);

    /*ADC Start Conversion*/
    SET_BIT(ADCSRA, ADSC);

    /*wait for flag*/
    while((GET_BIT(ADCSRA, ADIF)) == 0)
    {
    }
    /*Clear Flag*/
    SET_BIT(ADCSRA, ADIF);

    return ADC_Data;
}
