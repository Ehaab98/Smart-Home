/*
 * funs.c
 *
 *  Created on: Nov 1, 2022
 *      Author: moham
 */
#include <avr/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "private.h"
#include "UART_Interface.h"
#include "UART_Cfg.h"
#include "DIO_Interface.h"
#include"LCD_Interface.h"
#include "LCD_Cfg.h"
#include "Timer1_Interface.h"
#include "Timer1_Cfg.h"
#include "ADC_Cfg.h"
#include "ADC_Interface.h"
#include "funs.h"
#include "Timer_Interface.h"

void Funs_VidInit(void)
{
	/*Initialize UART*/
		DIO_VidSetPinDirection(PORTD,PIN0,Low);
		DIO_VidSetPinDirection(PORTD,PIN1,High);
		UART_VidInit();

		/*Initialize Timer1*/
		DIO_VidSetPinDirection(PORTD,PIN5,Low);
		Timer1_VidInit();

		/*Initialize LCD*/
		LCD_VidLCDInit();
		LCD_VidSendCommand(0b00001100);

		/*Initialize ADC*/
		DIO_VidSetPinDirection(0,0,0);
		ADC_VidInit();

		/*Warning Led Setup*/
		DIO_VidSetPinDirection(PORTB,PIN0,High);

		/*Buzzer Setup*/
		DIO_VidSetPinDirection(PORTD,PIN2,High);

		/*Go Led Setup*/
		DIO_VidSetPinDirection(PORTB,PIN2,High);

		/*Initialize Timer 0*/
		Timer_VidInit();

		/*Read Temp Every 200 ms*/
		Timer_setCallBack(Funs_ReadTemp, 200);

}

void Funs_VidLogIn(void)
{
	u8 pass[4];
	u8 right_pass[4] = {'1', '6', '2', '0'};
	u8 flag = 5;
	u8 count = 0;
	while(flag != 0)
	{
		LCD_Clear();
		LCD_VidSendString("Enter password:");
		LCD_VidCursorPosition(1,6);
		for(u8 i = 0; i<4; i++)
		{
			pass[i] = UART_U8Read();
			UART_VidSend(pass[i]);
			LCD_VidSendData(pass[i]);

		}
		for(u8 i = 0; i<4; i++)
		{
			if(pass[i] == right_pass[i])
			{
				count++;
			}
		}
		if(count == 4)
		{
			flag = 0;
			DIO_VidSetPinValue(PORTB, PIN2, High);
			LCD_Clear();
			LCD_VidCursorPosition(0,2);
			LCD_VidSendString("Welcome Ehab");
		}
		else
		{
			if(flag == 1)
			{
				while(1)
				{
					Funs_VidEmergency();
				}
			}
			else
			{
				flag--;
				LCD_Clear();
				DIO_VidSetPinValue(PORTB, PIN0, High);
				DIO_VidSetPinValue(PORTD, PIN2, High);
				LCD_VidCursorPosition(0,1);
				LCD_VidSendString("Wrong Password");
				LCD_VidCursorPosition(1,3);
				LCD_VidSendString("Try Again");
				_delay_ms(1000);
				DIO_VidSetPinValue(PORTD, PIN2, Low);
				DIO_VidSetPinValue(PORTB, PIN0, Low);
				count = 0;
			}
		}

	}
}
void Funs_VidDoorOpen(void)
{
	for(u32 i = 600; i < 2500; i+=50)
			{
				Timer1_VidOCRVal(i);
				_delay_ms(10);
			}
	_delay_ms(2000);
			for(u32 i = 2500; i > 600; i-=50)
			{
				Timer1_VidOCRVal(i);
				_delay_ms(10);
			}
}
void Funs_VidTempControl(void)
{
	LCD_Clear();
	u8 exit =0;
	u8 read;
	u64 Temperature;


	while(exit == 0)
	{

		Temperature = Funs_ReadTemp();
		LCD_VidSendString("Temperature: ");
		LCD_VidSendnum(Temperature);
		LCD_VidCursorPosition(1,0);
		LCD_VidSendString("Exit: 0");
		read = UART_U8Read();
		UART_VidSend(read);
		if(read == '0')
		{
			exit = 1;
		}

	}
}

u64 Funs_ReadTemp(void)
{
	u64 digital_value ;
	u64 Analouge_value;
	u64 Temperature;

	digital_value = ((u64)ADC_U8ReadOut(0));
	Analouge_value = (digital_value*5000)/1024;
	Temperature = Analouge_value/10;

	while(Temperature > 60)
	{
		digital_value = ((u64)ADC_U8ReadOut(0));
		Analouge_value = (digital_value*5000)/1024;
		Temperature = Analouge_value/10;
		Funs_VidEmergency();
	}

	return Temperature;

}


void Funs_VidLedControl(void)
{
	DIO_VidSetPortDirection(PORTB,255);
	u8 exit =0;
	u8 check;
	u8 read;
	LCD_Clear();
	LCD_VidSendString("Toggle One: 0~7");
	LCD_VidCursorPosition(1,0);
	LCD_VidSendString("All: 8   ");
	LCD_VidSendString("Exit: 9");
	while(exit == 0)
	{
		read = UART_U8Read();
		UART_VidSend(read);
		if(read == '9')
		{
			exit = 1;
		}
		else if(read == '8')
		{
			for(u8 i = 0; i<8; i++)
			{
				check = DIO_U8GetPinValue(PORTB,i );
				if(check == 1)
				{
					DIO_VidSetPortValue(PORTB, 0);
					break;
				}
			}
			if(check == 0)
			{
				DIO_VidSetPortValue(PORTB, 255);
			}

		}
		else if(read > 47 && read < 56)
		{
			DIO_VidTooglePinValue(PORTB, read-48);
		}
	}
}
void Funs_VidFanControl(void)
{
	DIO_VidSetPinDirection(PORTA, PIN4, High);
	u8 exit =0;
	u8 read;
	LCD_Clear();
	LCD_VidSendString("On/Off: 1");
	LCD_VidCursorPosition(1,0);
	LCD_VidSendString("Exit: 2");


	while(exit == 0)
	{
		read = UART_U8Read();
		UART_VidSend(read);
		if(read == '2')
		{
			exit = 1;
		}
		else if(read == '1')
		{
			DIO_VidTooglePinValue(PORTA, PIN4);
		}
	}
}

void Funs_VidEmergency(void)
{
		LCD_Clear();
		LCD_VidCursorPosition(0,2);
		LCD_VidSendString("YOUR SYSTEM");
		LCD_VidCursorPosition(1,3);
		LCD_VidSendString("Is LOCKED");
		DIO_VidTooglePinValue(PORTD,PIN2);
		DIO_VidTooglePinValue(PORTB,PIN0);
		_delay_ms(200);
		DIO_VidTooglePinValue(PORTD,PIN2);
		DIO_VidTooglePinValue(PORTB,PIN0);
		LCD_Clear();
		_delay_ms(200);

}



