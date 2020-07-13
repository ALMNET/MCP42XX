////////////////////////////////////////////////////////////////////////////////
////////////////////////////// STANDARD LIBRARIES  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <MCP4XXX_LIB.h>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEFINES ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define   LED_TEST   LATE.RE0

#define   ON      1
#define   OFF     0

#define   HIGH    1
#define   LOW     0

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// CONSTANTS AND VARIABLES ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Temporary Pot values to be sent through SPI
int P0W_Value, P1W_Value;

// Value for general Stepping delay between pot value changes
const unsigned long Stepping_delay_value = 20;

// Buffer for UART Debugging messages
unsigned char buffer[128];

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// SETUP FUNCTION ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Setup(){
  // All ports as Digital
  ANSELA = ANSELB = ANSELC = ANSELD = ANSELE= 0;

  // PortA as Output
  TRISA = 0b00000000;
  // PortB as Output
  TRISB = 0b00000000;
  // PortC as Output
  TRISC = 0b00000000;
  // PortE as Output
  TRISE = 0b00000000;
  
  // Clears the portB for debug purposes
  LATB = 0;
  
  // SPI1 init
  SPI1_Init();
  
  // I2C init
  //I2C2_Init(100000);
  
  // UART init for debugging
  UART1_Init(9600);
}


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// MAIN FUNCTION ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void main(void){

  setup();          // Configuration function
  PORTB = 0;
  LED_TEST = 1;     // LED Test on
  
  UART1_Write_Text("System Init");
  delay_ms(100);
  UART1_Write_Text(".");
  delay_ms(100);
  UART1_Write_Text(".");
  delay_ms(100);
  UART1_Write_Text(".");
  delay_ms(100);
  UART1_Write_Text(".");
  delay_ms(100);
  UART1_Write_Text(".");
  delay_ms(100);
  UART1_Write_Text(".\n\n");

  //////////////////// SOME RANDOM POT VALUES ////////////////////
  do{
  
    // RAMDON INCREMENT FOR OUTPUT TESTING: WIPER 0, FROM 0 TO 128
    for(P0W_Value = 0; P0W_Value <= 128; P0W_Value++){
      MCP4XXX_General_Command(MCP4XXX_VOLATILE_WIPER_OUT_0, P0W_Value);
      
      // Debug Purposes on UART1
      sprintf(buffer, "POT 0 INCREMENT: WIPER_OUT_0 = %x, WIPER_OUT_1 = %x, \n", MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_0), MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_1));
      UART1_Write_Text(buffer);
      delay_ms(Stepping_delay_value);
    }
    
    UART1_Write_Text("\n\n");

    // RAMDON INCREMENT FOR OUTPUT TESTING: WIPER 1, FROM 0 TO 128
    for(P1W_Value = 0; P1W_Value <= 128; P1W_Value++){
      MCP4XXX_General_Command(MCP4XXX_VOLATILE_WIPER_OUT_1, P1W_Value);
      
      // Debug Purposes on UART1
      sprintf(buffer, "POT 1 INCREMENT: WIPER_OUT_0 = %x, WIPER_OUT_1 = %x, \n", MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_0), MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_1));
      UART1_Write_Text(buffer);
      delay_ms(Stepping_delay_value);
    }

    UART1_Write_Text("\n\n");

    // RAMDON INCREMENT FOR OUTPUT TESTING: WIPER 0, FROM 128 TO 0
    for(P0W_Value = 128; P0W_Value >= 0; P0W_Value--){
      MCP4XXX_General_Command(MCP4XXX_VOLATILE_WIPER_OUT_0, P0W_Value);
      
      // Debug Purposes on UART1
      sprintf(buffer, "POT 0 DECREMENT: WIPER_OUT_0 = %x, WIPER_OUT_1 = %x, \n", MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_0), MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_1));
      UART1_Write_Text(buffer);
      delay_ms(Stepping_delay_value);
    }

    UART1_Write_Text("\n\n");

    // RAMDON INCREMENT FOR OUTPUT TESTING: WIPER 1, FROM 128 TO 0
    for(P1W_Value = 128; P1W_Value >= 0; P1W_Value--){
      MCP4XXX_General_Command(MCP4XXX_VOLATILE_WIPER_OUT_1, P1W_Value);
      
      // Debug Purposes on UART1
      sprintf(buffer, "POT 1 DECREMENT: WIPER_OUT_0 = %x, WIPER_OUT_1 = %x, \n", MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_0), MCP4XXX_General_Read(MCP4XXX_VOLATILE_WIPER_OUT_1));
      UART1_Write_Text(buffer);
      delay_ms(Stepping_delay_value);
    }

    UART1_Write_Text("\n\n");

  }while(true);

}