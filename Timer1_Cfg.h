
/*
Select Value of Prescaler : 
["0" = "No_Clock","1" = "No_Prescaler", "2" = "Prescaler_8", "3" = "Prescaler_64", "4" = "Prescaler_256", 
"5" = "Prescaler_1024", "6" = "External_Falling", "7" = "External_Rising"]
*/
#define Prescalar_Type Prescaler_256


/*
 * Select Timer Mode:
 * ["0" = "Timer_Normal", "1" = "Timer_PWM", "2" = "Timer_CTC" , "3" = "Timer_Fast_PWM"]
 */
#define Timer_Mode Timer_Fast_PWM


/*
 * Select Timer_PWM_Mode:
 * ["0" = "Timer_PWM_Disconnected", "1" = "Timer_PWM_NonInverting", "2" = "Timer_PWM_Inverting"]
 */
#define Timer_PWM_Mode Timer_PWM_NonInverting


/*Compare Match Value  */
#define TIMER_CTC_OCR0_VALUE   200
