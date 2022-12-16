#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Private.h"




void DIO_VidSetPinDirection(u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Direction)
{
    if (1  == Copy_U8Direction)
    {
        switch (Copy_U8Port)
        {
        case 0: SET_BIT(DDRA_REG, Copy_U8Pin); break;
        case 1: SET_BIT(DDRB_REG, Copy_U8Pin); break;
        case 2: SET_BIT(DDRC_REG, Copy_U8Pin); break;
        case 3: SET_BIT(DDRD_REG, Copy_U8Pin); break;
   
        }
    }
    else if(0  == Copy_U8Direction)
    {
        switch (Copy_U8Port)
        {
        case 0: CLR_BIT(DDRA_REG, Copy_U8Pin); break;
        case 1: CLR_BIT(DDRB_REG, Copy_U8Pin); break;
        case 2: CLR_BIT(DDRC_REG, Copy_U8Pin); break;
        case 3: CLR_BIT(DDRD_REG, Copy_U8Pin); break;
        }
    }
    

}

void DIO_VidSetPinValue(u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Value)
{
     if (1  == Copy_U8Value)
    {
        switch (Copy_U8Port)
        {
        case 0: SET_BIT(PORTA_REG, Copy_U8Pin); break;
        case 1: SET_BIT(PORTB_REG, Copy_U8Pin); break;
        case 2: SET_BIT(PORTC_REG, Copy_U8Pin); break;
        case 3: SET_BIT(PORTD_REG, Copy_U8Pin); break;
   
        }
    }
    else if(0  == Copy_U8Value)
    {
        switch (Copy_U8Port)
        {
        case 0: CLR_BIT(PORTA_REG, Copy_U8Pin); break;
        case 1: CLR_BIT(PORTB_REG, Copy_U8Pin); break;
        case 2: CLR_BIT(PORTC_REG, Copy_U8Pin); break;
        case 3: CLR_BIT(PORTD_REG, Copy_U8Pin); break;
        }
    }

}

u8 DIO_U8GetPinValue(u8 Copy_U8Port, u8 Copy_U8Pin)
{
	u8 x;
    switch (Copy_U8Port)
        {

    	case 0: x =  GET_BIT(PINA_REG, Copy_U8Pin); break;
        case 1: x =  GET_BIT(PINB_REG, Copy_U8Pin); break;
        case 2: x =  GET_BIT(PINC_REG, Copy_U8Pin); break;
        case 3: x =  GET_BIT(PIND_REG, Copy_U8Pin); break;
        }
    	return x;
}

void DIO_VidTooglePinValue(u8 Copy_U8Port, u8 Copy_U8Pin)
{
    switch (Copy_U8Port)
        {
        case 0: TOGGLE_BIT(PORTA_REG, Copy_U8Pin); break;
        case 1: TOGGLE_BIT(PORTB_REG, Copy_U8Pin); break;
        case 2: TOGGLE_BIT(PORTC_REG, Copy_U8Pin); break;
        case 3: TOGGLE_BIT(PORTD_REG, Copy_U8Pin); break;
        }

}

void DIO_VidSetPortValue(u8 Copy_U8Port,  u8 Copy_U8Value)
{
    switch (Copy_U8Port)
        {
        case 0: PORTA_REG = Copy_U8Value; break;
        case 1: PORTB_REG = Copy_U8Value; break;
        case 2: PORTC_REG = Copy_U8Value; break;
        case 3: PORTD_REG = Copy_U8Value; break;
        }

}

void DIO_VidSetPortDirection(u8 Copy_U8Port, u8 Copy_U8Direction)
{
      switch (Copy_U8Port)
        {
        case 0: DDRA_REG = Copy_U8Direction; break;
        case 1: DDRB_REG = Copy_U8Direction; break;
        case 2: DDRC_REG = Copy_U8Direction; break;
        case 3: DDRD_REG = Copy_U8Direction; break;
        }

}
