
/*Using double speed mode in Asynch mode:
 *"0" = "Disable", "1" = "Enable" */
#define U2X_Mode	Disable


/*Receiver interrupt configuration:
 *"0" = "Disable", "1" = "Enable" */
#define RX_Int		Disable


/*Transmitter interrupt configuration:
 *"0" = "Disable", "1" = "Enable" */
#define TX_Int		Disable


/*UDR interrupt configuration:
 *"0" = "Disable", "1" = "Enable" */
#define UDR_Int		Disable

/*Receiver Control:
 *"0" = "Disable", "1" = "Enable" */
#define RX_Control		Enable

/*Transmitter Control:
 *"0" = "Disable", "1" = "Enable" */
#define TX_Control		Enable


/*Select UART Mode:
 * "0" = "Async", "1" = "Sync"
 */
#define USART_Mode	Async

/* Parity Mode:
 * "0" = "Disable", "1" = "Odd_Parity, "2" = "Even_Parity"
 */
#define Parity_Mode	Disable


/*Select number of stop bits
 * "Stop1", "Stop2"
 */
#define StopBit_Num	Stop1


/*Select number of data bits
 * "5" = "Bit_5", "6" = "Bit_6", "7" = "Bit_7", "8" = "Bit_8", "9" = "Bit_9"
  */
#define DataBits_Num	Bit_8


/*Select clock polarity for sync mode
 * "0" = "Rising" , "1" = "Falling"
 */
#define Clock_Polarity	Falling
