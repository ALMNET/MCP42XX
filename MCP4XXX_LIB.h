////////////////////////////////////////////////////////////////////////////////
////////////////////////////// MCP LIBRARY HEADER //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

#define   INPUT      1
#define   OUTPUT     0

#define   SPI1_MCP4XXX_CS_D TRISE.RE2
#define   SPI1_MCP4XXX_CS   LATE.RE2

#define   ENABLED     0
#define   DISABLED    1

#define   HIGH        1
#define   LOW         0

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// DEFINES AND I/O's //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// OUTPUT COMMANDS USING INTERNAL RAM (VOLATILE MEMORY)
#define MCP4XXX_VOLATILE_WIPER_OUT_0        0x00
#define MCP4XXX_VOLATILE_WIPER_OUT_1        0x01

// OUTPUT COMMANDS USING INTERNAL EEPROM (NON VOLATILE MEMORY)
#define MCP4XXX_NON_VOLATILE_WIPER_0        0x02
#define MCP4XXX_NON_VOLATILE_WIPER_1        0x03

// VOLATILE TCON
#define MCP4XXX_TCON                  0x04

// MCP4XXX STATUS REGISTER
#define MCP4XXX_STATUS                0x05

// READ AND WRITE COMMAND VALUES ACCORDING TO DS22059B page 45, 
// TABLE 7-1: COMMAND BIT OVERVIEW

// MCP4XXX WRITE VALUE COMMAND (DS22059B page 49, FIGURE 7-2)
#define MCP4XXX_WRITE                 0x00

// MCP4XXX READ VALUE COMMAND (DS22059B page 51, FIGURE 7-4)
#define MCP4XXX_READ                  0x0C

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// CONSTANTS AND VARIABLES ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// MCP4XXX EEPROM REGISTERS ARRAY
//const uint8_t MCP4XXX_EEPROM_ARRAY[10] = {
//  0x06,
//  0x07,
//  0x08,
//  0x09,
//  0x0A,
//  0x0B,
//  0x0C,
//  0x0D,
//  0x0E,
//  0x0F
//};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// PROTOTYPES //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// General Command functions according to DS22059B page 29, Table 4-1
// Where:
// MCP4XXX_COMMAND: Is an 8 bit variable which only 4 MSBs matters. This
//                  variable is for MCP Commands according to DS22059B
//                  page 29, Table 4-1
// MCP4XXX_Data   : Is a 16 bit variable which will be used for data
//                  That data could be the digital pot output value
//                  for volatile or non volatile memory. The value could be
//                  set according to DS22059B page 36, table 5-1

void MCP4XXX_General_Command(uint8_t MCP4XXX_COMMAND, uint16_t MCP4XXX_Data);

// General Read functions, the parameter value is a 16 bit command
// According to DS22059B page 29, Table 4-1: MEMORY MAP
// Where:
// MCP4XXX_COMMAND: Is an 8 bit variable which only 4 MSBs matters. This
//                  variable is for MCP Commands according to DS22059B
//                  page 29, Table 4-1 (Address)
// The function returns a 16 bit data value which is structured according to
// DS22059B page 45, FIGURE 7-1: General SPI Command Formats.
uint16_t MCP4XXX_General_Read(uint8_t MCP4XXX_COMMAND);


