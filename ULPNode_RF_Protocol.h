// **********************************************************************************
// ULPNode RF protocol paylaods used for transmission
// **********************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend this library but please abide with the CC-BY-SA license:
// http://creativecommons.org/licenses/by-sa/4.0/
//
// For any explanation of ULPNode see 
// https://hallard.me/category/ulpnode/
//
// Written by Charles-Henri Hallard (http://hallard.me)
//
// History : V1.00 2014-07-14 - First release
//
// All text above must be included in any redistribution.
//
// **********************************************************************************
#ifndef ULPN_RF_PROTOCOL_H
#define ULPN_RF_PROTOCOL_H

#ifdef SPARK
#include <application.h>        // Spark Code main include file
#endif

// Payload command code
#define RF_PL_SYSTEM_START  0x00 // first value for system payload type
#define RF_PL_ALIVE      		0x01
#define RF_PL_PING       		0x02
#define RF_PL_PINGBACK   		0x03
#define RF_PL_OTA_CONFIG 		0x04 // OTA Node Configuration
#define RF_PL_OTA_UPDATE 		0x05 // OTA Node Firmware update
#define RF_PL_DHCP_REQUEST	0x06 // Node Auto ID request
#define RF_PL_DHCP_OFFER    0x07 // Node Auto ID assignment
#define RF_PL_SYSTEM_END 		0x07 // Lasted value for system payload

// Payload data code
#define RF_PL_DATA_START    0x10 // first value for system payload type
#define RF_PL_SENSOR_DATA   0x11 // Sensor(s) data(s)
#define RF_PL_DATA_END      0x12 // Lasted value for system payload

// each sensor data type can sent 4 differents values
#define RF_DAT_SENSOR_MASK  0xFC// isolate sensor type

#define RF_DAT_SENSOR_START	0x20// first value for sensor payload type
#define RF_DAT_BAT          0x20 // 20 to 23 = Battery Voltage
#define RF_DAT_TEMP      		0x24 // 24 to 27 = Temperature data
#define RF_DAT_HUM   		    0x28 // 28 to 2B = Humididy data
#define RF_DAT_LUX      		0x2C // 2C to 2F = Luminosity data
#define RF_DAT_CO2      		0x30 // 30 to 33 = CO2 data
#define RF_DAT_RSSI         0x34 // 34 to 37 = RSSI data
#define RF_DAT_VOLT         0x38 // 38 to 3B = Voltage data
#define RF_DAT_COUNTER      0x3C // 3C to 3F = Counter data
#define RF_DAT_LOW_BAT      0x40 // 40 to 43 = Low Battery flag
#define RF_DAT_DUMMY        0x44 // 44 to 4F = Free, for future use
#define RF_DAT_IO_DIGITAL   0x50 // 50 to 5F = Digital I/O
#define RF_DAT_IO_ANALOG    0x60 // 60 to 67 = Analog I/O
#define RF_DAT_SENSOR_END		0x67 // last value for sensor payload type

// Macro to determine valid payload of command or data
#define isPayloadCommand(c)	(c>RF_PL_SYSTEM_START && c<RF_PL_SYSTEM_END) 
#define isPayloadData(c)	  (c>RF_PL_DATA_START   && c<RF_PL_DATA_END) 
#define isPayloadValid(c)	  (isPayloadCommand(c) || isPayloadData(c)) 

// Macro to determine valid sensor data type
#define isSensorData(c)    (c>RF_DAT_SENSOR_START   && c<RF_DAT_SENSOR_END) 
#define isDataBat(c)       ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_BAT ) 
#define isDataTemp(c)      ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_TEMP) 
#define isDataHum(c)       ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_HUM )  
#define isDataLux(c)       ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_LUX )  
#define isDataCO2(c)       ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_CO2 )  
#define isDataRSSI(c)      ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_RSSI)  
#define isDataVolt(c)      ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_VOLT)  
#define isDataCounter(c)   ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_COUNTER)  
#define isDataLowBat(c)    ( (c & RF_DAT_SENSOR_MASK) == RF_DAT_LOW_BAT)  
#define isDataDigitalIO(c) ( c >= RF_DAT_IO_DIGITAL && c <= RF_DAT_IO_DIGITAL+16)  
#define isDataAnalogIO(c)  ( c >= RF_DAT_IO_ANALOG && c <= RF_DAT_IO_ANALOG+7)  

// Application Parameters header flags of Radio Frame
#define RF_PAYLOAD_REQ_ACK   0x01  // Request ACK FLAGS
#define RF_PAYLOAD_RESPONSE  0x02  // Request Response FLAGS

#define RF_ANSWER_TIMEOUT     200  // number of ms to receive ACK/Response
#define RF_RETRIES            3    // number of retries
#define RF_ANSWER_ERROR       9999 // no ack/answer received return value

#define RF_DEFAULT_NODE_ID    248
#define RF_DEFAULT_GW_ID      1

// Different node internal status flags
#define RF_NODE_STATE_RADIO   0x0001 /* Radio Module OK    */
#define RF_NODE_STATE_RFM69   0x0002 /* RFM69 seen and OK   */
#define RF_NODE_STATE_NRF24   0x0004 /* NRF24 seen and OK   */
#define RF_NODE_STATE_TSL2561 0x0008 /* TSL2561 seen and OK */
#define RF_NODE_STATE_SI7021  0x0010 /* SI7021 seen and OK  */
#define RF_NODE_STATE_OLED    0x0020 /* OLED seen and OK    */
#define RF_NODE_STATE_BOOST   0x4000 /* DC bosster always on*/
#define RF_NODE_STATE_LOWBAT  0x8000 /* LOW Bat detected    */

// Constant of Radio module type we are using
// this permit to know dynamically the
// radio module we have on board
#define RF_MOD_NONE     0
#define RF_MOD_UNKNOWN  1
#define RF_MOD_NRF24    24
#define RF_MOD_RFM69    69

#ifdef SPARK
  // This will force structure to 1 byte alignment
  #pragma pack(push)  // push current alignment to stack
  #pragma pack(1)     // set alignment to 1 byte boundary
  #define sprintf_P(s, f, ...) sprintf((s), (f), __VA_ARGS__)
  #define strstr_P(a, b) strstr((a), (b))
#endif 

// Replace Serial.print primitive with debug one 
// or empty if debug is not enabled, used for 
// external application that does not use ulpnode
// object but just ULPNode RF protocol files
#define ULPN_PROTO_DEBUG

#ifdef ULPN_PROTO_DEBUG
  #define ULPNP_Debug(args...)    Serial.print(args)
  #define ULPNP_Debugln(args...)  Serial.println(args)
  #define ULPNP_DebugF(s)         Serial.print(F(s))
  #define ULPNP_DebuglnF(s)       Serial.println(F(s))
  #define ULPNP_DebugFlush()      Serial.flush()
#else
  #define ULPNP_Debug(args...)      
  #define ULPNP_Debugln(args...)    
  #define ULPNP_DebugF(s)     
  #define ULPNP_DebuglnF(s)   
  #define ULPNP_DebugFlush()  
#endif

// Command payloads type
// =====================
// Ping Payload sent by RF
typedef struct
{
  uint8_t   command;  /* Command code         */
  uint16_t  status;   /* Node internal status flags */
  uint16_t  vbat;     /* Battery voltage (in mV ex 1500 for 1.5V) */
  int8_t    rssi;     /* RSSI */
} RFPingPayload;

// Alive Payload sent by RF
typedef struct
{
  uint8_t  command;  /* Command code     */
  uint16_t status;   /* Node internal status flags */
  uint16_t vbat;     /* Battery voltage (in mV ex 1500 for 1.5V) */
} RFAlivePayload;

// Data payloads format
// ====================
// Temperature format in payload
typedef struct
{
  uint8_t code; // code         
  int16_t temp; // temperature Value 
} s_temp;

// Humidity format in payload
typedef struct
{
  uint8_t code;  // code         
  uint16_t hum;  // humidity Value 
} s_hum;

// Luminosity format in payload
typedef struct
{
  uint8_t code;  // code         
  uint16_t lux;   // Lux Value 
} s_lux;

// CO2 format in payload
typedef struct
{
  uint8_t code;  // code         
  uint16_t co2;  // co2 Value   
} s_co2;

// RSSI format in payload
typedef struct
{
  uint8_t command;  // Command code         
  int8_t  rssi;     // RSSI Value 
} s_rssi;

// Voltage format in payload
typedef struct
{
  uint8_t code;  // code         
  uint16_t volt; // Voltage Value (in mv)
} s_volt;

// Counter format in payload
typedef struct
{
  uint8_t code;     // code         
  uint32_t counter; // counter data
} s_counter;

// lowbat format in payload
typedef struct
{
  uint8_t code;   // code         
  uint8_t lowbat; // lowbat indicator
} s_lowbat;

// IO Digital value
typedef struct
{
  uint8_t code;    // code         
  uint16_t analog; // d0-d16 Value (only D4/D8 could potentially by used on ULPNode)   
} s_io_digital;

// IO Analog Digital value
typedef struct
{
  uint8_t code;    // code         
  uint16_t analog; // a0-a7 Value (only A0,A1 and A3 free on ULPNode)
} s_io_analog;

// dhcp format in payload
typedef struct
{
  uint8_t code;      // code         
  uint8_t networkid; // network ID
  uint8_t nodeid;    // node ID
} s_dhcp;


// Dummy payload, used to be able to handle any possible payload 
// with pointer, and allocating the max payload size, take care to 
// increase this payload size if you add some payload that can contains
// more than 32 bytes on above definition
typedef struct
{
  uint8_t command;   /* Command code is ALWAYS 1st byte */
  uint8_t dummy[31]; 
} RFEmptyPayload;

#ifdef SPARK
  // restore original alignment from stack
  #pragma pack(pop)
  extern const char * rf_frame[];
#else
  extern const char * const rf_frame[];
#endif

extern char json_str[];

char * decode_frame_type(uint8_t);
char * decode_bat(uint16_t, char * index=NULL);
char * decode_volt(uint16_t, char * index=NULL);
char * decode_temp(int16_t, char * index=NULL);
char * decode_hum(uint16_t, char * index=NULL);
char * decode_lux(uint16_t, char * index=NULL);
char * decode_co2(uint16_t, char * index=NULL);
char * decode_rssi(int8_t, char * index=NULL);
char * decode_counter(uint32_t, char * index=NULL);
char * decode_lowbat(uint8_t, char * index=NULL);
char * decode_digital_io(uint8_t, char * index=NULL);
char * decode_analog_io(uint16_t, char * index=NULL);
uint8_t decode_received_data(uint8_t nodeid, int8_t rssi, uint8_t len, uint8_t c, uint8_t * ppayload);

#endif
