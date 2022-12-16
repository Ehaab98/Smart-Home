#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Timer1_Private.h"
#include "Timer1_Cfg.h"






void Timer1_VidInit(void)
{

    CLR_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);

    SET_BIT(TCCR1A, COM1A1);
    CLR_BIT(TCCR1A, COM1A0);

    TCCR1B &= 0b11111000;
    TCCR1B |= 2;

    ICR1H = (u8)(20000>>8);
    ICR1L = (u8)20000;

}
void Timer1_VidOCRVal(u16 Copy_U16OCRVAl)
{
	OCR1AH = (u8)(Copy_U16OCRVAl>>8);
	OCR1AL = (u8)(Copy_U16OCRVAl);
}





