/*
 * Copyright (c) 2007, IRTrans GmbH
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer. 
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution. 
 *     * Neither the name of IRTrans GmbH nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY IRTrans GmbH ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL IRTrans GmbH BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



#ifdef WIN32
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
#endif

#ifdef _HCS12

typedef INT8 int8_t;
typedef UINT8 uint8_t;

typedef UINT16 uint16_t;
typedef INT16 int16_t;

typedef UINT32 uint32_t;

#endif

typedef uint8_t byte;
typedef uint16_t word;

#ifdef _HCS12
#define CODE_LEN	174

#else
#ifndef AVR
#pragma pack(1)
#define CODE_LEN	176							// 2 Byte mehr f�r String-Ende 0
#else
#ifdef REMOTECONTROL
#define CODE_LEN	20
#else
#define CODE_LEN	174
#endif
#endif
#endif


#ifdef AMEX
#define VCC_THRESHOLD	180
#else
#define VCC_THRESHOLD	210
#endif

#define LAN_TIMEOUT_VAL 60

#define TIME_LEN		 8
#define TIME_LEN_18		18
#define TIME_LEN_SINGLE	20
#define RAW_EXTRA	TIME_LEN * 4 + 2
#define CODE_LENRAW	(CODE_LEN + RAW_EXTRA - 2)
#define OLD_LENRAW	(CODE_LEN + (6 * 4 + 2) - 2)
#define MAXLCDLEN 170
#define CODE_LEN_SINGLE (CODE_LEN-10)
#define CODE_LEN_18 (CODE_LEN-40)


typedef struct {
	byte len;							//	0
	byte checksumme;					//	1
	byte command;						//	2

	byte address;						//	3
	word target_mask;					//	4

	byte ir_length;						//	6
	byte transmit_freq;					//	7
	byte mode;							//	8

	int16_t pause_len[TIME_LEN];		//	9
	int16_t pulse_len[TIME_LEN];		// 25
	byte time_cnt;						// 41
	byte ir_repeat;						// 42
	byte repeat_pause;					// 43

	byte data[CODE_LEN];				// 44
} IRDATA;

typedef struct {
	byte len;							//	0
	byte checksumme;					//	1
	byte command;						//	2

	byte address;						//	3
	word target_mask;					//	4

	byte ir_length;						//	6
	byte transmit_freq;					//	7
	byte mode;							//	8

	int16_t pause_len[18];				//	9
	int16_t pulse_len[18];				// 45
	byte time_cnt;						// 81
	byte ir_repeat;						// 82
	byte repeat_pause;					// 83

	byte data[CODE_LEN_18];				// 84
} IRDATA_18;

typedef struct {
	byte len;							//	0
	byte checksumme;					//	1
	byte command;						//	2

	byte address;						//	3
	word target_mask;					//	4

	byte ir_length;						//	6
	byte transmit_freq;					//	7
	byte mode;							//	8

	int16_t multi_len[TIME_LEN_SINGLE];	//	9
	int16_t single_len;					// 49
	byte time_cnt;						// 51
	byte ir_repeat;						// 52
	byte repeat_pause;					// 53

	byte data[CODE_LEN_SINGLE];			// 54
} IRDATA_SINGLE;

typedef struct {
	byte len;							//  0
	byte checksumme;					//  1
	byte command;						//  2

	byte address;						//  3
	word target_mask;					//  4

	byte ir_length;						//  6
	byte transmit_freq;					//  7
	byte mode;							//  8

	byte data[CODE_LENRAW];				//  9
} IRRAW;

typedef union {
	IRDATA		irdata;
	IRRAW		irraw;
	IRDATA_18	irdata18;
} IRDATA_ALL;


#ifndef AVR

typedef struct {
	word crc;
	byte errcnt;
	byte dummy;
	byte cryptstart;
	byte cryptend;
	word magic;
	word pagesize;
	word pagecnt;
	word data[65536];
} FLASH_IR_DATA;


#define IR_MAGIC				0x7a8e

#endif

#define VERSION_MAGIC_1			0x39
#define VERSION_MAGIC_2			0x640b
#define VERSION_MAGIC_3			0xb3
#define VERSION_MAGIC_4			0x8b

#define VERSION_MAGIC_CHECK		0xaa
#define VERSION_MAGIC_CHECKR	0x68

#define FLASH_TYPE_LAN			0xff01
#define FLASH_TYPE_IRDB			0xff02
#define FLASH_TYPE_IRDBAUX		0xff03

#define SENDMASK_LEN  16

#define COMMAND_LAN             200
#define COMMAND_FLASH_START     201
#define COMMAND_FLASH_DATA      202
#define COMMAND_FLASH_END	    203
#define COMMAND_FLASH_ACK       204
#define COMMAND_FLASH_CANCEL    205
#define COMMAND_FLASH_HTML      206
#define COMMAND_SEND_RS232      207
#define COMMAND_FLASH_ACK_1     208
#define COMMAND_FLASH_ACK_2     209
#define COMMAND_FLASH_CRC       210
#define COMMAND_FLASH_IR        211

#define COMMAND_LAN_SENDSTRING	's' 
#define COMMAND_LAN_PING      	'p' 
#define COMMAND_LAN_SENDCCF   	'c' 




#define RESULT_IR_BROADCAST		    230
#define RESULT_GETVERSION	      	231
#define RESULT_DEVSTATUS		    232
#define RESULT_EEPROM			    233
#define RESULT_RESET		      	234
#define RESULT_IRDBSTATUS     		235
#define RESULT_REMOTELIST     		236
#define RESULT_COMMANDLIST		    237
#define RESULT_IR_RECEIVE     		238
#define	RESULT_UDP_FORMAT		    239
#define RESULT_FLASH			    240
#define RESULT_ALIVE			    241
#define RESULT_LEARN			    242
#define RESULT_READ_EEPROM		    243
#define	RESULT_WAKE_ON_LAN		    244
#define	RESULT_PING_OK			    245
#define RESULT_IR_HOSTBROADCAST		246
#define RESULT_IR_BROADCAST_LED		247
#define RESULT_AUX_FORMAT     		248
#define RESULT_ANALOG_INPUT			249


#define ADR_LANPARM		256
#define LEN_LANPARM		(sizeof (LAN_PARAMETER)-3)			// LEN = 21
#define ADR_SYSPARM		(ADR_LANPARM+LEN_LANPARM)
#define LEN_SYSPARM		(sizeof (SYS_PARAMETER)-4)			// LEN = 191 -> capabilities not stored in EEPROM 
#define ADR_WAKEMAC		(ADR_LANPARM+LEN_LANPARM+164)
#define ADR_TIMER		(ADR_SYSPARM+LEN_SYSPARM)
#define LEN_TIMER		sizeof (TIMER_ENTRY_GET)			// LEN = 117

#define MAX_1WIRE_ID	16

typedef struct {
  uint8_t mode;
  uint8_t status;
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t min;
  uint8_t weekday;
  uint32_t next_time;
} TIMER_ENTRY;

typedef struct {
  uint8_t len;
  TIMER_ENTRY tim;
	uint8_t remote[81];
	uint8_t ircommand[21];
	uint8_t ledselect;
	uint16_t  targetmask;
} TIMER_ENTRY_GET;
  
typedef struct {
	uint8_t		len;
	uint8_t      checksumme;
	uint8_t      command;
	uint8_t      mode;
  TIMER_ENTRY tim;
	uint8_t remote[81];
	uint8_t ircommand[21];
	uint8_t ledselect;
	uint16_t  targetmask;
} TIMER_ENTRY_STORE;

typedef struct {
	uint8_t len;
	uint8_t checksumme;
	uint8_t command;

	uint8_t cmd_str[80 + 20 + 10];
} IRCOMMAND_STRING;


typedef struct {
	uint8_t len;
	uint8_t checksumme;
	uint8_t command;

	uint8_t remote[81];
	uint8_t ircommand[121];
	uint16_t mask;
	uint8_t ledselect;
} IRCOMMAND_BUF;

typedef struct {
	uint8_t len;
	uint8_t checksumme;
	uint8_t command;
	uint8_t dummy;

	uint16_t start;
	uint8_t remote[81];
} IRDBLIST_BUF;


typedef struct {
	word adr;
	word len;
	word flash_adr;
	word page;
	word crc;
} FLASH_BLOCK;

typedef struct {
	word crc;
	word type;
	FLASH_BLOCK dir[12];
} FLASH_TABLE;

#define FLASH_TABLE_LEN ((sizeof (FLASH_TABLE) + 1) / 2)

typedef struct {
	uint8_t netcommand;
  word    adr;
  word    len;
  uint8_t data[512];
} IRDATA_LAN_FLASH;

typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	uint32_t sendmask[SENDMASK_LEN];
	IRDATA ir_data;
} IRDATA_LAN;

typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	uint32_t sendmask[SENDMASK_LEN];
	IRDATA ir_data;
	byte buffer[256];
} IRDATA_LAN_LARGE;

typedef struct {
	uint8_t netcommand;
	IRDATA ir_data;
} IRDATA_LAN_SHORT;

typedef struct {
	byte len;
	byte checksumme;
	byte command;
	word adr;
	byte data[200];
} IRDATA_EEPROM;

typedef struct {
	uint8_t		netcommand;
	uint8_t		len;
	uint8_t		ir_version[8];
	uint32_t	ir_capabilities;
	uint32_t	ir_serno;
	uint8_t		lan_version[8];
	uint8_t		mac_adr[6];
} GETVERSION_LAN;

typedef struct {
	uint8_t		netcommand;
	uint8_t		len;
	uint8_t		ir_version[8];
	uint32_t	ir_capabilities;
	uint32_t	ir_serno;
	uint8_t		lan_version[8];
	uint8_t		mac_adr[6];
	uint32_t	ir_capabilities2;
	uint32_t	ir_capabilities3;
	uint32_t	ir_capabilities4;
} GETVERSION_LAN_EX;

typedef struct {
	uint8_t		netcommand;
	uint8_t		len;
	uint8_t		ir_version[8];
	uint32_t	ir_capabilities;
	uint32_t	ir_serno;
	uint8_t		lan_version[8];
	uint8_t		mac_adr[6];
	uint32_t	ir_capabilities2;
	uint32_t	ir_capabilities3;
	uint32_t	ir_capabilities4;
	uint8_t		extended_mode;
	uint8_t		extended_mode2;
	uint8_t		extended_mode_ex[2];
} GETVERSION_LAN_EX2;

typedef struct {
	uint32_t	access_ip[8];		// 0	// Erlaubte Input IPs
	uint32_t	access_mask[8];		// 32	// Netmask dazu
	uint32_t	ir_relay_from[16];	// 64	// IR Relay von diesen Adressen erlaubt
	uint32_t	ir_relay_to[8];  	// 128	// Output wird zus�tzlich zum Broadcast an diese IPs gesendet
	uint32_t	udp_str_adr;		// 160	
	uint8_t		wakeonlan_mac[6];	// 164	// Zielhost f�r WakeOnLAN Pakete (PowerOn)
	int8_t		password[12];		// 170
	uint8_t		broadcast_relay;	// 182
	uint8_t		udp_format_len;		// 183
	uint16_t	udp_port;			// 184
	uint8_t		tz;					// 186
	uint32_t	ntp_ip;				// 187
	uint32_t	ir_relay_led;		// 191
	uint32_t  capabilities;			// 195
} SYS_PARAMETER;

typedef struct {
	uint8_t			len;
	SYS_PARAMETER	sysparm;
} SYS_PARAMETER_GET;

typedef struct {
	uint8_t		len;
	byte      checksumme;
	byte      command;
	byte      mode;
	SYS_PARAMETER	sysparm;
} SYS_PARAMETER_STORE;

typedef struct {
	uint8_t		len;
	byte      checksumme;
	byte      command;
	byte      udplen;
	byte      str[100];
} UDP_FORMAT_STORE;

typedef struct {
	uint8_t		len;
	uint8_t		dhcp_flag;
	uint8_t		fallback_flag;
	uint8_t		mac_adr[6];
	uint32_t	ip_adr;
	uint32_t	ip_netmask;
	uint32_t	ip_gateway;
	uint8_t   eeprom_device_mode;
	uint8_t   eeprom_extended_mode;
	uint8_t   eeprom_extended_mode2;
} LAN_PARAMETER;

typedef struct {
	uint8_t		len;
	byte      checksumme;
	byte      command;
	uint8_t		dhcp_flag;
	uint8_t		fallback_flag;
	uint8_t		mac_adr[6];
	uint32_t	ip_adr;
	uint32_t	ip_netmask;
	uint32_t	ip_gateway;
} LAN_PARAMETER_STORE;

typedef struct {
	byte len;
	byte checksumme;
	byte command;

	byte address;
	word target_mask;

	byte ir_length;
	byte transmit_freq;
	byte mode;

	word pause_len[6];
	word pulse_len[6];
	byte time_cnt;
	byte ir_repeat;
	byte repeat_pause;

	byte data[CODE_LEN];
} IRDATA3;

typedef struct {
	byte len;
	byte checksumme;
	byte command;

	byte address;
	word target_mask;

	byte ir_length;
	byte transmit_freq;
	byte mode;

	byte data[MAXLCDLEN];
} IRRAWLCD;

typedef struct {
	uint8_t len;
	uint8_t count_buffer;
	int16_t offset;
	int16_t count_total;
	int8_t remotes[3][80];
} REMOTEBUFFER_INT;

typedef struct {
	uint8_t len;
	uint8_t count_buffer;
	int16_t offset;
	int16_t count_total;
	int8_t commands[12][20];
} COMMANDBUFFER_INT;

typedef struct {
	uint32_t target_mask;
	uint32_t source_mask;
	int8_t name[80];
} REMOTELINE;

typedef struct {
	uint32_t capabilities;
	uint32_t capabilities2;
	int8_t name[60];
	int8_t version[8];
	uint32_t capabilities3;
	uint32_t capabilities4;
	uint8_t extended_mode;
	uint8_t extended_mode2;
	uint8_t extended_mode_ex[2];
} BUSLINE;

typedef struct {
	int16_t statuslen;
	int16_t statustype;
  int16_t offset;
  int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	int8_t  remotes[3][80];
} REMOTEBUFFER_TCP;

typedef struct {
	int16_t statuslen;
	int16_t statustype;
  int16_t offset;
  int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	REMOTELINE remotes[3];
} REMOTEBUFFER_SHORT;


typedef struct {
	int16_t statuslen;
	int16_t statustype;
  int16_t offset;
  int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	int8_t commands[12][20];
} COMMANDBUFFER_SHORT;

typedef struct {
	int16_t statuslen;
	int16_t statustype;
	uint8_t data[240];
} LEARNBUFFER_TCP;


#define BROADCAST_UDP		1
#define BROADCAST_AUX		2

typedef struct {
	uint8_t		len;
	uint8_t		modeflags;
	uint32_t	ip;
	uint16_t	port;
	uint8_t		data[10];
} UDP_ASCII_RECEIVE;

typedef struct {
	uint8_t	len;
	uint16_t action_adr;
	uint16_t remote_adr;
	uint32_t ip;
	uint16_t port;
	uint8_t	modeflags;
	uint8_t remote[80];
	uint8_t command[20];
	uint8_t ircommand[141];
} IRRECEIVE;

typedef struct {
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint16_t command_num;
	int8_t remote[80];
	int8_t command[20];
	int8_t data[141];
} NETWORKRECV_SHORT;


typedef struct {
	uint8_t	len;
	uint8_t	mode[8];
	uint8_t value[8];
} ANALOG_INPUTS;

typedef struct {
	uint8_t	len;
	uint8_t	mode[MAX_1WIRE_ID];
	uint8_t id[MAX_1WIRE_ID][8];
} ANALOG_INFO;

typedef struct {
	uint8_t	len;
	uint8_t	mode[8];
	uint8_t	dummy;
	int16_t value[8];
} ANALOG_HIRES_INPUTS;


typedef union {
	ANALOG_INPUTS		a_input;
	ANALOG_HIRES_INPUTS a_hires;
	ANALOG_INFO			a_info;
} ANALOG_DATA;

typedef struct {
	uint8_t netcommand;
	ANALOG_DATA ad;
} GET_ANALOG_DATA;


typedef struct {
	uint8_t netcommand;
	ANALOG_INPUTS ai;
} GET_ANALOG_INPUTS;


// Mode Flags
#define DEVMODE_PC			0
#define DEVMODE_SEND		1
#define DEVMODE_IR			2
#define DEVMODE_SBUS		4
#define DEVMODE_IGNORETOG	8
#define DEVMODE_SBUSCODE	16
#define DEVMODE_RAW			32
#define DEVMODE_SBUS_UART	64		// Set: SBUS l�uft �ber UART
#define DEVMODE_REPEAT		128

// Extended Mode Flags
#define INTERNAL_LEDS		1
#define EXTERNAL_LEDS		2
#define STANDARD_RCV		4
#define HI_RCV				8
#define BO_MODE				16
#define SELF_REPEAT			32
#define	INTERNAL_REPEAT		64
#define RCV_NO_SORT			128			

// Extended Mode2 Flags
#define RCV_TOLERANCE_MASK	7			// Bit 0-2
#define RCV_TOLERANCE_64	0
#define RCV_TOLERANCE_96	1
#define RCV_TOLERANCE_140	2
#define RCV_TOLERANCE_200	3
#define INSTANT_REP_COUNT	8			// Bit 3
#define IR_FRAMELENGTH		16			// Bit 4
#define RS232_BAUD_MASK		96			// Bit 5-6	
#define RS232_RTS_CTS		128			// Bit 7		

// EX[0]
#define LOW_RCV_MASK		7
#define HI_RCV_MASK			240

// EX[1]
#define RCV_TIMEOUT_MASK	255			// Bit 0-7

// EX[2]
#define IDLE_TIMEOUT_MASK	7			// Bit 0-2
#define IDLE_TIMEOUT_1		0
#define IDLE_TIMEOUT_2		1
#define IDLE_TIMEOUT_4		2
#define IDLE_TIMEOUT_5		3
#define IDLE_TIMEOUT_6		4
#define IDLE_TIMEOUT_8		5
#define IDLE_TIMEOUT_10		6
#define IDLE_TIMEOUT_15		7

#define SBUS_BAUD_MASK		24			// Bit 3-4
#define SBUS_BAUD_4800		0
#define SBUS_BAUD_9600		8
#define SBUS_BAUD_19200		16
#define SBUS_BAUD_38400		24

#define IR_FILTER_MASK		224			// Bit 5-7
#define IR_FILTER_64		0
#define IR_FILTER_120		32
#define IR_FILTER_160		64
#define IR_FILTER_280		96
#define IR_FILTER_380		128
#define IR_FILTER_480		160
#define IR_FILTER_550		192
#define IR_FILTER_800		224

// EX[3]
#define	CHECK_RCMM			1
#define FORCE_RCMM			2
#define RCMM_TOGGLE			4
#define RSTEP_KEYBOARD		8

// EX[4]
#define TOGGLE_MAP_MASK		63			// Map out Toggle Bits
#define TOGGLE_MAP_LEN		128

#define LRN_TIMEOUT_MASK	7			// Maske beim Lernen 
#define LRN_TIMEOUT_SELECT	8
#define LRN_CALIBRATION		48
#define LRN_RCV_SELECT		960
#define LRN_RCV_56			64
#define LRN_RCV_38			128
#define LRN_RCV_455			256
#define LRN_RCV_455_PLASMA	320
#define LRN_RCV_CARRIER		384
#define LRN_RCV_EXTERNAL	512
#define LRN_RCV_HI			1024
#define LRN_TOLERANCE		14336
#define LRN_BO_MODE			16384
#define LRN_NOSORT			32768

#define LRN_TOGGLE_MAP		1

#define LOCAL_MODE			16
#define	RECEIVE_ALL			17
#define	QUICK_MODE			32
#define RAW_MODE			64
#define REPEAT_MODE			128
#define IR_MODE				256
#define SBUS_MODE			512
#define	INSTANT_MODE		1024
#define IDLE_WAIT			2048
#define TOGGLE_MAP			4096

#define SPECIAL_RCV_MODE	31

#define LONG_LEARN_MODE				16
#define RECEIVER_SELECT_MASK		96
#define RECEIVER_SELECT_LOW			32
#define RECEIVER_SELECT_HI			64
//#define RECEIVER_SELECT_LEARNLOW	192
//#define RECEIVER_SELECT_LEARNHI		224
//#define RECEIVER_LEARN_CARRIER		512

#define LONG_CODE_FLAG		128
#define LONG_CODE_LEN		8
#define USE_LONG_CODES		1
#define LONG_CODE_MODE_CAL	2

// Bereiche der Command Codes durch LEARN blockiert:
//
//  16 -  31
//  48 -  63
//	80 -  95
// 112 - 128
// 144 - 159
// 176 - 191
// 208 - 223
// 240 - 255



// Hier LEARN Command Codes
#define SBUS_LEARN			16
#define HOST_LEARNIR		18
#define SBUS_QUICKPARM		48
#define HOST_LEARNIRQUICK	50
#define SBUS_RAWMODE		80
#define HOST_LEARNIRRAW		82
#define SBUS_REPEATMODE		144
#define HOST_LEARNIRREPEAT	146
#define SBUS_RAWREPEATMODE		208
#define HOST_LEARNIRRAWREPEAT	210


// Hier Standard Command Codes
#define SBUS_REPEAT			1
#define HOST_VERSION		2
#define HOST_NETWORK_STATUS	3
#define SBUS_SEND			4
#define SBUS_RESEND			5
#define HOST_SEND			6
#define HOST_RESEND			7

#define	LAN_REPEAT			32
#define PUT_SERIAL_DATA		33
#define READ_ANALOG_INPUTS	34

#define ASCII_SEND			100 // 'd'

#define SBUS_RESET			192
#define SBUS_PING			193
#define SBUS_PONG			194
#define SBUS_PARAMETER		196
#define HOST_SETMODE		197
#define SET_ID				199
#define SET_TRANSLATE_DATA	200
#define SBUS_TRANSLATE_DATA	201
#define READ_TRANSLATE_DATA	202
#define START_FLASH_MODE	203
#define	TRANSFER_FLASH		204
#define	SBUS_SET_MODE2		206
#define	HOST_SET_MODE2		207

#define	HOST_STORE_LANPARM	224
#define	HOST_READ_LANPARM	225
#define	HOST_STORE_FLASH	226
#define	HOST_READ_FLASH		227
#define SEND_IRDB_STRING	228
#define	SEND_IRDB_BLOCK		229
#define	RESEND_IRDB_BLOCK	230
#define IRDB_REMLIST		231
#define IRDB_COMLIST		232
//#define HOST_STORE_UDPSTR	233
#define PING_IR_CONTROLLER	234
#define SET_POWER_LED		235
#define	TEST_IRDB_BLOCK		236
#define GET_TIMER_PARAMETER 237
#define STORE_TIMER_PARAMETER 238


#define	SEND				SBUS_SEND
#define LEARN				SBUS_LEARN
#define	SETMODE				SBUS_PARAMETER

#define ADRESS_MASK			15
#define ADRESS_LOCAL		16
#define ADRESS_ALL			32
#define ADRESS_LAN			64


#define	START_BIT			1
#define REPEAT_START		2
#define START_MASK			3
#define RC5_DATA			4
#define	RC6_DATA			8
#define IRDA_DATA			12
#define NO_TOGGLE			2
#define NO_TOGGLE_H			64
#define MACRO_DATA			32

#define SPECIAL_IR_FLAG		128
#define SPECIAL_IR_MODE		159
#define	RAW_DATA			16

#define	TIMECOUNT_18		128
#define RCMM				129
// 130 frei
#define PULSE_200			131
#define RECS80				132
#define RECS80_NO_TOGGLE	133
#define RECS80_NO_TOGGLE_H	134

#define OFFSET_TYP_TOGGLE	1

#define LCD_BACKLIGHT		1
#define LCD_TEXT			2


#define LCD_INIT			4
#define LCD_SETTIME			8
#define LCD_DISPLAYTIME		16
#define LCD_DEFINECHAR		12
#define LCD_BRIGHTNESS		20
#define LCD_REFRESHDATE		24

#define	LCD_DATA			32

#define	TEMP_GET			1
#define TEMP_RESET			2
#define TEMP_DATA			64
#define NON_IRMODE			96

#define SWITCH_DATA			96

#define SHORT_PULSE			50
#define IR_CORRECT_455		1				// Entspricht 8 �s Korrektur

#ifndef IR_CORRECT
#define IR_CORRECT			8				// Entspricht 64 �s Korrektur
#define IR_CORRECT_LOW		6				// Entspricht 24 �s Korrektur f�r kurze Pulse
#else
#ifndef IR_CORRECT_LOW
#define IR_CORRECT_LOW		0				// Entspricht 24 �s Korrektur f�r kurze Pulse
#endif
#endif


#define IR_TOLERANCE_BO		50				// Entspricht 280 �s Toleranz
#define IR_TOLERANCE		12				// Entspricht  96 �s Toleranz
#define RCX_TOLERANCE		25				// Entspricht +/- 200 �s Toleranz
#define MAX_IR_REPEAT		5
#define RAW_TOLERANCE		15

#define EXT_LED_SELECT_1	4
#define EXT_LED_SELECT_2	8
#define EXT_LED_SELECT_3	12
#define EXT_LED_SELECT_4	16
#define EXT_LED_SELECT_5	20
#define EXT_LED_SELECT_6	24
#define EXT_LED_SELECT_7	28
#define EXT_LED_SELECT_8	32

#define EXT_LED_SELECT_MASK	60




#define START			1
#define REPEAT			2


typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte mode;
	word target_mask;
	byte hotcode_len;
	byte hotcode[CODE_LENRAW];
} MODE_BUFFER;

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte mode;
	word target_mask;
	byte hotcode_len;
	byte extmode1;
	byte extmode2;
	byte extmode_ex0;
	byte extmode_ex1;
	char remote[81];
	char command[21];
} MODE_BUFFER_LAN;

typedef struct {
	byte device_mode;			//  0
	word send_mask;				//  1
	byte extended_mode;			//  3
	byte extended_mode2;		//  4
	byte extended_mode_ex[8];	//  5
	byte hotcode_len;			// 13
} EEPROM_MEMORY;				// 14

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte device_mode;
	word send_mask;
	byte extended_mode;
	byte extended_mode2;
	byte extended_mode_ex[8];
	byte version[10];
	uint32_t capabilities;
	uint32_t capabilities2;
	uint32_t capabilities3;
	uint32_t capabilities4;
	byte wake_mac[6];
	char remote[81];
	char command[21];
} STATUS_LINE_EX;

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte device_mode;
	word send_mask;
	byte version[10];
	byte extended_mode;
	uint32_t capabilities;
	byte extended_mode2;
	byte extended_mode_ex[2];
	byte wake_mac[6];
	char remote[81];
	char command[21];
} STATUS_LINE_EX_1;

typedef struct {
	byte sbus_len;					//  0
	byte sbus_checksumme;			//  1
	byte sbus_command;				//  2
	byte sbus_address;				//  3
	byte device_mode;				//  4
	word send_mask;					//  5
	byte extended_mode;				//  7
	byte extended_mode2;			//  8
	byte extended_mode_ex[8];		//  9
	byte version[10];				// 17
	uint32_t capabilities;			// 27
	uint32_t capabilities2;			// 31
	uint32_t capabilities3;			// 35
	uint32_t capabilities4;			// 39
	byte wake_mac[6];				// 43
} STATUS_LINE;						// 49

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte device_mode;
	word send_mask;
	byte version[10];
	byte extended_mode;
	uint32_t capabilities;
	byte extended_mode2;
	byte extended_mode_ex[2];
	byte wake_mac[6];
} STATUS_LINE_5;

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte device_mode;
	word send_mask;
	byte version[10];
	byte extended_mode;
	uint32_t capabilities;
	byte extended_mode2;
} STATUS_LINE_4;

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte device_mode;
	word send_mask;
	byte version[10];
	byte extended_mode;
	word capabilities;
} STATUS_LINE_3;

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte device_mode;
	word send_mask;
	byte version[10];
	byte extended_mode;
} STATUS_LINE_2;

typedef struct {
	byte sbus_len;
	byte sbus_checksumme;
	byte sbus_command;
	byte sbus_address;
	byte device_mode;
	word send_mask;
	byte version[10];
} STATUS_LINE_1;

typedef struct {
	byte my_adress;
	STATUS_LINE stat[16];
} STATUS_BUFFER;

typedef struct {
	byte my_adress;
	STATUS_LINE_1 stat[16];
} STATUS_BUFFER_1;

typedef struct {
	byte my_adress;
	STATUS_LINE_2 stat[16];
} STATUS_BUFFER_2;

typedef struct {
	byte my_adress;
	STATUS_LINE_3 stat[16];
} STATUS_BUFFER_3;

typedef struct {
	byte my_adress;
	STATUS_LINE_4 stat[16];
} STATUS_BUFFER_4;

typedef struct {
	byte my_adress;
	STATUS_LINE_5 stat[16];
} STATUS_BUFFER_5;

typedef struct {
	uint8_t netcommand;
	STATUS_LINE_EX stat;
} STATUS_LINE_LAN;

typedef struct {
	uint8_t netcommand;
	STATUS_LINE_EX_1 stat;
} STATUS_LINE_LAN_1;

#define LOGIN_NEEDED      128
#define DYNAMIC_LEN       64
#define EXTERNAL_FILE     32
#define RQ_DATA_CURRENT   16
#define MENU_NEEDED       8

#define CONTENT_MASK      7

#define CONTENT_HTML      1
#define CONTENT_PLAIN     2
#define CONTENT_GIF       3
#define CONTENT_JPEG      4


typedef struct {
  char  name[23];
  byte  filetype;
  word  adr;
  word  len;
  uint32_t timestamp;
} HTTP_DIRENTRY;

typedef struct {
  word  count;
  word  magic;
  HTTP_DIRENTRY dir[1];
} HTTP_DIRECTORY;

#define IRTRANS_PORT	21000

