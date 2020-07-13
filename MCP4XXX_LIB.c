////////////////////////////////////////////////////////////////////////////////
///////////////////////////// DIGITAL POT FUNCTIONS ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <MCP4XXX_LIB.h>



void MCP4XXX_init(){
  //if(SPI1)  SPI1_Init();
  //else      SPI2_Init();
  
  SPI1_Init();
  SPI1_MCP4XXX_CS_D = OUTPUT;

}

/////////////////////////////// MCP4XXX COMMANDS ///////////////////////////////

void MCP4XXX_General_Command(uint8_t MCP4XXX_COMMAND, uint16_t MCP4XXX_Data){

  uint16_t MCP4XXX_SPI_DATA = 0;
  
  // Filters just 10 data bits for MCP4xxx from 16 bits data register
  MCP4XXX_Data &= 0x03FF;
  
  // Combining Command and Data values in a single register, including
  // Write / Read operation indicator (DS22059B page 45, FIGURE 7-1)
  MCP4XXX_SPI_DATA = (MCP4XXX_COMMAND << 12) | (MCP4XXX_WRITE << 8) | MCP4XXX_Data;
  
  // Switch SPI Bus to MCP4XXX
  SPI1_MCP4XXX_CS = ENABLED;

  // Send 8 MSBs data nibble
  SPI1_Write((MCP4XXX_SPI_DATA & 0xFF00) >> 8);

  // Send 8 LSBs data nibble
  SPI1_Write(MCP4XXX_SPI_DATA & 0x00FF);

  // Disables SPI Bus for all SPI devices
  SPI1_MCP4XXX_CS = DISABLED;

}

////////////////////////////////// MCP4XXX READ ////////////////////////////////

uint16_t MCP4XXX_General_Read(uint8_t MCP4XXX_COMMAND){

  // General 16 bit read value to be returned from function
  uint16_t MCP4XXX_READ_VALUE = 0;
  uint16_t MCP4XXX_READ_VALUE1 = 0;
  uint16_t MCP4XXX_READ_VALUE2 = 0;
  
  uint16_t MCP4XXX_SPI_DATA = 0;

  // Dummy data for clock generation on SPI read operation (MikroC)
  short buffer;

  // Combining Command and Write / Read operation indicator
  MCP4XXX_SPI_DATA = (MCP4XXX_COMMAND << 12) | (MCP4XXX_READ << 8);

  // Switch SPI Bus to MCP4XXX
  SPI1_MCP4XXX_CS = ENABLED;

  // Send read command to MCP4XXX
  SPI1_Write((MCP4XXX_SPI_DATA & 0xFF00) >> 8);

  //PORTB = MCP4XXX_COMMAND | MCP4XXX_READ
  // Read SPI
  MCP4XXX_READ_VALUE1 = SPI1_Read(buffer); // 8 MSBs
  MCP4XXX_READ_VALUE2 = SPI1_Read(buffer); // 8 LSBs
  
  // Disables SPI Bus for all SPI devices
  SPI1_MCP4XXX_CS = DISABLED;
  
  //return MCP4XXX_READ_VALUE;
  return ((MCP4XXX_READ_VALUE2 << 8) | MCP4XXX_READ_VALUE1);

}