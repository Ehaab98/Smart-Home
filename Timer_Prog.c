#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Timer_Private.h"
#include "Timer_Cfg.h"





static void (*Timer_PFun) (void);

f32 over_count;
u32 preload;
u32 over_dec;


/*Call Back Setter Timer*/
void Timer_setCallBack(void (*timerptr)( void), u32 Copy_U32DesTime)
{
	f32 floating;
	Timer_PFun = timerptr;

	f32 Tov;
	Tov = (f32) 256 *1000* ((f32)Prescalar_Type/(f32)frequency);
	over_count = (f32)Copy_U32DesTime/(Tov);
	over_dec = over_count;
	floating = over_count-over_dec;
	preload = 256 - (floating*256);
}

void Timer_VidInit(void)
{
    /*Enable Intrupt*/
    SET_BIT(TIMSK, TOIE0);


    /*Select Normal Mode*/
    CLR_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);

    /*Select Pre-scalar*/

    /*PreScalar: 8*/
    #if Prescalar_Type == Prescaler_8
    TCCR0 &= 0b11111000;
    TCCR0 |= 2;

    /*PreScalar: 64*/
    #elif Prescalar_Type == Prescaler_64
    TCCR0 &= 0b11111000;
    TCCR0 |= 3;

    /*PreScalar: 256*/
    #elif Prescalar_Type == Prescaler_256
    TCCR0 &= 0b11111000;
    TCCR0 |= 4;

    /*PreScalar: 1024*/
    #elif Prescalar_Type == Prescaler_1024
    TCCR0 &= 0b11111000;
    TCCR0 |= 5;

    #elif Prescalar_Type == External_Falling
    TCCR0 &= 0b11111000;
    TCCR0 |= 6;

    #elif Prescalar_Type == External_Rising
    TCCR0 &= 0b11111000;
    TCCR0 |= 7;
    

    #endif
    /*Set Timer Count*/
    TCNT0 = preload;
}





/*ISR for INT0*/
void __vector_11(void)
{
    static u8 flag_count = 0;
    flag_count++;
    if(flag_count == (over_dec+1) )
    {
        TCNT0 = preload;
        Timer_PFun();
        flag_count = 0;
        
    }
}
