/*
* gps_ublox.h
* 
* created on March 28 2013
*
* Author: N.Dousse
*
*/


#ifndef GPS_UBLOX_H__ND
#define GPS_UBLOX_H__ND

//#include "gps_maveric.h"
#include "stdint.h"
#include "stdbool.h"

/*
 *  try to put a UBlox into binary mode. This is in two parts. First we
 *  send a PUBX asking the UBlox to receive NMEA and UBX, and send UBX,
 *  with a baudrate of 38400. Then we send a UBX message setting rate 1
 *  for the NAV_SOL message. The setup of NAV_SOL is to cope with
 *  configurations where all UBX binary message types are disabled.
 * 0001: UBX
 * 0002: NMEA
 * 0003: NMEA + UBX
 */
//#define UBLOX_SET_BINARY "$PUBX,41,1,0003,0001,38400,0*26\n\265\142\006\001\003\000\001\006\001\022\117"

// changed by ndousse
#define UBLOX_SET_BINARY "$PUBX,41,1,0003,0001,38400,0*25\r\n"//\265\142\006\001\003\000\001\006\001\022\117"

/*
Structure of an UBlox binary message

PREAMBLE1		PREAMBLE2		CLASS		MSG_ID		LENGTH1			LENGTH2			MESSAGE			CHECKSUMA		CHECKSUMB
1 byte			1 byte			1 byte		1 byte		Lowest byte		Highest byte	LENGTH size		1 byte			1 byte

The information is received in the Little endian format (least significant byte first).
*/

#define UBX_PREAMBLE1 0xb5
#define UBX_PREAMBLE2 0x62

/*
Name Class Description
NAV 0x01 Navigation Results: Position, Speed, Time, Acc, Heading, DOP, SVs used
RXM 0x02 Receiver Manager Messages: Satellite Status, RTC Status
INF 0x04 Information Messages: Printf-Style Messages, with IDs such as Error, Warning, Notice
ACK 0x05 Ack/Nack Messages: as replies to CFG Input Messages
CFG 0x06 Configuration Input Messages: Set Dynamic Model, Set DOP Mask, Set Baud Rate, etc.
MON 0x0A Monitoring Messages: Comunication Status, CPU Load, Stack Usage, Task Status
AID 0x0B AssistNow Aiding Messages: Ephemeris, Almanac, other A-GPS data input
TIM 0x0D Timing Messages: Timepulse Output, Timemark Results
*/
#define UBX_CLASS_NAV 0x01
#define UBX_CLASS_RXM 0x02
#define UBX_CLASS_INF 0x04
#define UBX_CLASS_ACK 0x05
#define UBX_CLASS_CFG 0x06
#define UBX_CLASS_MON 0x0A
#define UBX_CLASS_AID 0x0B
#define UBX_CLASS_TIM 0x0D
#define UBX_CLASS_ESF 0x10

// Type of Messages that can be received in each class
#define MSG_ACK_NACK 0x00
#define MSG_ACK_ACK 0x01

#define MSG_INF_ERROR 0x00
#define MSG_INF_WARNING 0x01
#define MSG_INF_NOTICE 0x02
#define MSG_INF_TEST 0x03
#define MSG_INF_DEBUG 0x04

#define MSG_NAV_POSLLH 0x02
#define MSG_NAV_STATUS 0x03
#define MSG_NAV_AOPSTATUS 0x60
#define MSG_NAV_CLOCK 0x22
#define MSG_NAV_SOL 0x06
#define MSG_NAV_VELNED 0x12
#define MSG_NAV_VELCEF 0x11
#define MSG_NAV_TIMEGPS 0x20
#define MSG_NAV_TIMEUTC 0x21
#define MSG_NAV_SVINFO 0x30

#define MSG_CFG_PRT 0x00
#define MSG_CFG_RATE 0x08
#define MSG_CFG_SET_RATE 0x01
#define MSG_CFG_NAV_SETTINGS 0x24
#define MSG_CFG_NMEA 0x17

#define MSG_MON_RXR 0x21

#define MSG_TIM_TP 0x01
#define MSG_TIM_VRFY 0x06

#define UBX_PLATFORM_PORTABLE 0x00
#define UBX_PLATFORM_STATIONARY 0x02
#define UBX_PLATFORM_PEDESTRIAN 0x03
#define UBX_PLATFORM_AUTO   0x04
#define UBX_PLATFORM_SEA    0x05
#define UBX_PLATFORM_1GAIR  0x06
#define UBX_PLATFORM_2GAIR  0x07
#define UBX_PLATFORM_4GAIR  0x08

#define GPS_FIX_TYPE_NOFIX 0x00
#define GPS_FIX_TYPE_DEADRECK 0x01
#define GPS_FIX_TYPE_2DFIX 0x02
#define GPS_FIX_TYPE_3DFIX 0x03
#define GPS_FIX_TYPE_GPSDEADRECK 0x04
#define GPS_FIX_TYPE_TIMEONLY 0x05

// For binary message
#define UBX_CFG_MSG 0xF1
#define UBX_CFG_MSG_ID 0x41

// Sizes
#define UBX_SIZE_NAV_POSLLH 28
#define UBX_SIZE_NAV_STATUS 16
#define UBX_SIZE_NAV_SOL 52
#define UBX_SIZE_NAV_VELNED 36
#define UBX_SIZE_NAV_SVINFO 30 //8 + 12*numChannel
#define UBX_SIZE_NAV_SETTINGS 36

#define UBX_SIZE_CFG_RATE 6
#define UBX_SIZE_CFG_GETSET_RATE 3

#define UBX_SIZE_MON_RXR 1

#define UBX_SIZE_TIM_TP 16
#define UBX_SIZE_TIM_VRFY 20

#define NAV_STATUS_FIX_NVALID 0
#define NAV_STATUS_FIX_VALID 1

//epoch
#define TIME_OF_DAY 0 //<
#define TIME_OF_WEEK 1 //< Ublox
#define TIME_OF_YEAR 2 //< MTK, NMEA
#define UNIX_EPOCH 3

#define PI 3.141592
#define DEG2RAD PI/180

// The UART bytes are sent in a little endian format from the GPS, if the processor is big endian, define BIG_ENDIAN
// Otherwise comment the following line
#define BIG_ENDIAN

#ifdef BIG_ENDIAN
	typedef struct {
		uint16_t length;
		uint8_t msg_id_header;
		uint8_t msg_class;
		uint8_t preamble2;
		uint8_t preamble1;
	}ubx_header;

	typedef struct {
		uint16_t timeref;
		uint16_t nav_rate;
		uint16_t measure_rate_ms;
	}ubx_cfg_nav_rate;
	
	// We still have to send to message in the correct order to the GPS
	typedef struct {
		uint16_t measure_rate_ms;
		uint16_t nav_rate;
		uint16_t timeref;			// 0:UTC time, 1:GPS time
	}ubx_cfg_nav_rate_send;

	typedef struct {
		uint8_t rate;
		uint8_t msg_id_rate;
		uint8_t msg_class;
	}ubx_cfg_msg_rate;

	// We still have to send to message in the correct order to the GPS
	typedef struct {
		uint8_t msg_class;
		uint8_t msg_id_rate;
		uint8_t rate;
	}ubx_cfg_msg_rate_send;

	typedef struct {
		uint32_t res4;
		uint32_t res3;
		uint32_t res2;
		uint8_t dgpsTimeOut;							// s
		uint8_t staticHoldThresh;						// cm/s
		uint16_t tAcc;									// m
		uint16_t pAcc;									// m
		uint16_t tDop;
		uint16_t pDop;
		uint8_t drLimit;								// s
		int8_t minElev;									// deg
		uint32_t fixedAltVar;							// m^2
		int32_t fixedAlt;								// m
		uint8_t fixMode;
		uint8_t dynModel;								// UBX_PLATFORM_... type
		uint16_t mask;
	}ubx_cfg_nav_settings;

	typedef struct {
		uint32_t vertical_accuracy;						// mm
		uint32_t horizontal_accuracy;					// mm
		int32_t altitude_msl;							// mm
		int32_t altitude_ellipsoid;						// mm
		int32_t latitude;								// deg 1e-7
		int32_t longitude;								// deg 1e-7
		uint32_t itow;                                  // GPS msToW
	}ubx_nav_posllh;

	typedef struct {
		uint32_t uptime;                                // milliseconds
		uint32_t time_to_first_fix;						// milliseconds
		uint8_t res;
		uint8_t differential_status;
		uint8_t fix_status;
		uint8_t fix_type;
		uint32_t itow;                                  // GPS msToW
	}ubx_nav_status;

	typedef struct {
		uint32_t res2;
		uint8_t satellites;
		uint8_t res;
		uint16_t position_DOP;							// scaling 0.01
		uint32_t speed_accuracy;						// cm/s
		int32_t ecef_z_velocity;						// cm/s
		int32_t ecef_y_velocity;						// cm/s
		int32_t ecef_x_velocity;						// cm/s
		uint32_t position_accuracy_3d;					// cm
		int32_t ecef_z;									// cm
		int32_t ecef_y;									// cm
		int32_t ecef_x;									// cm
		uint8_t fix_status;
		uint8_t fix_type;
		int16_t week;
		int32_t time_nsec;								// nanoseconds
		uint32_t itow;									// milliseconds
	}ubx_nav_solution;

	typedef struct {
		uint32_t heading_accuracy;						// deg
		uint32_t speed_accuracy;						// cm/s
		int32_t heading_2d;								// deg
		uint32_t groundSpeed_2d;						// cm/s
		uint32_t speed_3d;								// cm/s
		int32_t ned_down;								// cm/s
		int32_t ned_east;								// cm/s
		int32_t ned_north;								// cm/s
		uint32_t itow;                                  // milliseconds GPS msToW
	}ubx_nav_velned;

	typedef struct
	{
		struct
		{
			int32_t prRes;
			int16_t azim;
			int8_t elev;
			uint8_t cno;
			uint8_t quality;
			uint8_t flags;
			uint8_t svid;
			uint8_t chn;
		} channelData[16];
		
		uint16_t reserved;
		uint8_t globalFlags;
		uint8_t numCh;
		uint32_t itow;
	}ubx_nav_SVInfo;
	
 	typedef struct{
 		uint8_t awake_flag;
 	}ubx_mon_rxr_struct;
	 
	typedef struct{
		uint8_t res;
		uint8_t flags;
		uint16_t week;
		int32_t qErr;
		uint32_t towSubMS;				// ms scaling: 2^-32
		uint32_t towMS;					// ms
	}ubx_tim_tp;

	typedef struct
	{
		uint8_t res;
		uint8_t flags;
		uint16_t wno;					// week number
		int32_t deltaNs;				// ns
		int32_t deltaMs;				// ms
		int32_t frac;					// ns
		int32_t itow;					// ms
	}ubx_tim_vrfy;

#else

	typedef struct {
		uint8_t preamble1;
		uint8_t preamble2;
		uint8_t msg_class;
		uint8_t msg_id_header;
		uint16_t length;
	}ubx_header;

	typedef struct {
		uint16_t measure_rate_ms;
		uint16_t nav_rate;
		uint16_t timeref;
	}ubx_cfg_nav_rate;

	typedef struct {
		uint8_t msg_class;
		uint8_t msg_id_rate;
		uint8_t rate;
	}ubx_cfg_msg_rate;

	typedef struct {
		uint16_t mask;
		uint8_t dynModel;								// UBX_PLATFORM_... type
		uint8_t fixMode;
		int32_t fixedAlt;								// m
		uint32_t fixedAltVar;							// m^2
		int8_t minElev;									// deg
		uint8_t drLimit;								// s
		uint16_t pDop;
		uint16_t tDop;
		uint16_t pAcc;									// m
		uint16_t tAcc;									// m
		uint8_t staticHoldThresh;						// cm/s
		uint8_t dgpsTimeOut;							// s
		uint32_t res2;
		uint32_t res3;
		uint32_t res4;
	}ubx_cfg_nav_settings;

	typedef struct {
		uint32_t itow;                                  // GPS msToW
		int32_t longitude;								// deg 1E-7
		int32_t latitude;								// deg 1E-7
		int32_t altitude_ellipsoid;						// mm
		int32_t altitude_msl;							// mm
		uint32_t horizontal_accuracy;					// mm
		uint32_t vertical_accuracy;						// mm
	}ubx_nav_posllh;

	typedef struct {
		uint32_t itow;                                  // GPS msToW
		uint8_t fix_type;
		uint8_t fix_status;
		uint8_t differential_status;
		uint8_t res;
		uint32_t time_to_first_fix;						// milliseconds
		uint32_t uptime;                                // milliseconds
	}ubx_nav_status;

	typedef struct {
		uint32_t itow;									// milliseconds
		int32_t time_nsec;								// nanoseconds
		int16_t week;
		uint8_t fix_type;
		uint8_t fix_status;
		int32_t ecef_x;									// cm
		int32_t ecef_y;									// cm
		int32_t ecef_z;									// cm
		uint32_t position_accuracy_3d;					// cm
		int32_t ecef_x_velocity;						// cm/s
		int32_t ecef_y_velocity;						// cm/s
		int32_t ecef_z_velocity;						// cm/s
		uint32_t speed_accuracy;						// cm/s
		uint16_t position_DOP;							// scaling 0.01
		uint8_t res;
		uint8_t satellites;
		uint32_t res2;
	}ubx_nav_solution;

	typedef struct {
		uint32_t itow;                                  // milliseconds GPS msToW
		int32_t ned_north;								// cm/s
		int32_t ned_east;								// cm/s
		int32_t ned_down;								// cm/s
		uint32_t speed_3d;								// cm/s
		uint32_t groundSpeed_2d;						// cm/s
		int32_t heading_2d;								// deg
		uint32_t speed_accuracy;						// cm/s
		uint32_t heading_accuracy;						// deg
	}ubx_nav_velned;

	typedef struct
	{
		uint32_t itow;
		uint8_t numCh;
		uint8_t globalFlags;
		uint16_t reserved;
	
		struct
		{
			uint8_t chn;
			uint8_t svid;
			uint8_t flags;
			uint8_t quality;
			uint8_t cno;
			int8_t elev;
			int16_t azim;
			int32_t prRes;
		} channelData[16];
	}ubx_nav_SVInfo;
	
	typedef struct{
		uint8_t awake_flag;
	}ubx_mon_rxr_struct;

	typedef struct  
	{
		uint32_t towMS;					// ms
		uint32_t towSubMS;				// ms scaling: 2^-32
		int32_t qErr;
		uint16_t week;
		uint8_t flags;
		uint8_t res;
	}ubx_tim_tp;
	
	typedef struct
	{
		int32_t itow;
		int32_t frac;
		int32_t deltaMs;
		int32_t deltaNs;
		uint16_t wno;
		uint8_t flags;
		uint8_t res;
	}ubx_tim_vrfy;

#endif

ubx_cfg_nav_settings nav_settings;

uint8_t cksum_a;
uint8_t cksum_b;

// State machine state
uint8_t         step;
uint8_t         msg_id;
uint16_t        payload_length;
uint16_t        payload_counter;

// 8 bit count of fix messages processed, used for periodic
// processing
uint8_t			fix_count;

uint8_t         ubxclass;

// do we have new position and speed information?
bool new_position;
bool new_speed;

uint8_t         disable_counter;

bool fix;
bool next_fix;
bool have_raw_velocity;
// bool valid_read;
// bool new_data;

uint32_t last_ground_speed_cm;

#define NO_GPS 0
#define NO_FIX 1
#define GPS_OK 2

enum GPS_Engine_Setting{
	GPS_ENGINE_NONE        = -1,
	GPS_ENGINE_PORTABLE    = 0,
	GPS_ENGINE_STATIONARY  = 2,
	GPS_ENGINE_PEDESTRIAN  = 3,
	GPS_ENGINE_AUTOMOTIVE  = 4,
	GPS_ENGINE_SEA         = 5,
	GPS_ENGINE_AIRBORNE_1G = 6,
	GPS_ENGINE_AIRBORNE_2G = 7,
	GPS_ENGINE_AIRBORNE_4G = 8
};

enum GPS_Engine_Setting engine_nav_setting;

//! Number of times ubx_CheckTimeout() must be called without response from GPS before it is considered as timed out
#define UBX_TIMEOUT_CYCLES 2
//! The minimum precision to consider a position as correct (in m)
#define UBX_POSITION_PRECISION 20
//! The minimum precision to consider an altitude as correct (in m)
#define UBX_ALTITUDE_PRECISION 20
//! The minimum precision to consider a speed as correct (in m/s)
#define UBX_SPEED_PRECISION 5
//! The minimum precision to consider a heading as correct (in deg*10^5)
#define UBX_HEADING_PRECISION 5000000//3000000

// Type definition for GPS data
typedef struct
{
	long latitude; //!< latitude in degree E+7
	long longitude; //!< longitude in degree E+7
	float altitude; //!< altitude in m
	float alt_elips; //!< altitude above ellipsoid in m
	float speed; //!< 3D speed in m/s
	float groundSpeed; //!< 2D ground speed in m/s
	float northSpeed; //!< the speed to the north in m/s
	float eastSpeed; //!< the speed to the east in m/s
	float verticalSpeed; //!< the vertical speed in m/s
	float course; //!< heading in degree
	
	float horizontalAccuracy; //!< horizontal accuracy in m
	float verticalAccuracy; //!< vertical accuracy in m
	
	float speedAccuracy; //!< speed accuracy in m
	float headingAccuracy; //!< heading accuracy in m
	
	uint8_t num_sats;
	uint16_t hdop;
	
	unsigned long timeLastMsg; //!< time reference in ms of microcontroller
	unsigned long timegps; //!< time reference in ms of gps
	
	unsigned char status;
	
	unsigned char horizontalStatus;
	
// 	unsigned char latitudeStatus;
// 	unsigned char longitudeStatus;
 	unsigned char altitudeStatus;
 	unsigned char speedStatus;
// 	unsigned char groundSpeedStatus;
// 	unsigned char northSpeedStatus;
// 	unsigned char eastSpeedStatus;
// 	unsigned char verticalSpeedStatus;
 	unsigned char courseStatus;
	unsigned char accuracyStatus;
} gps_Data_type;

/// Last time that the GPS driver got a good packet from the GPS
uint32_t idleTimer;

/// Time in milliseconds after which we will assume the GPS is no longer
/// sending us updates and attempt a re-init.
///
/// 1200ms allows a small amount of slack over the worst-case 1Hz update
/// rate.
uint32_t idleTimeout;

uint32_t last_fix_time;

float velocity_north;
float velocity_east;
float velocity_down;

//float get_lag() { return 0.5; };
	
void init_gps_ubx(enum GPS_Engine_Setting _engine_nav_setting);

bool ubx_read(void);
bool ubx_process_data(void);

void update_checksum(uint8_t *data, uint8_t len, uint8_t *ck_a, uint8_t *ck_b);
uint8_t endian_lower_bytes_uint16(uint16_t bytes);
uint8_t endian_higher_bytes_uint16(uint16_t bytes);
void ubx_send_header(uint8_t msg_class, uint8_t _msg_id, uint8_t size);
void ubx_send_cksum(uint8_t ck_sum_a, uint8_t ck_sum_b);

void ubx_send_message(uint8_t msg_class, uint8_t msg_id, void *msg, uint8_t size);
void ubx_send_message_CFG_nav_rate(uint8_t msg_class, uint8_t _msg_id, ubx_cfg_nav_rate_send msg, uint8_t size);
void ubx_send_message_nav_settings(uint8_t msg_class, uint8_t _msg_id, enum GPS_Engine_Setting *engine_settings, uint8_t size);
void ubx_configure_message_rate(uint8_t msg_class, uint8_t msg_id, uint8_t rate);

void configure_gps(void);

void gps_update(void);
bool newValidGpsMsg(void);

ubx_nav_posllh * ubx_GetPosllh(void);
ubx_nav_status * ubx_GetStatus(void);
ubx_nav_solution * ubx_GetSolution(void);
ubx_nav_velned * ubx_GetVelned(void);
ubx_nav_SVInfo * ubx_GetSVInfo(void);
ubx_cfg_nav_settings * ubx_GetNavSettings(void);
ubx_cfg_msg_rate * ubx_GetMsgRate(void);
ubx_mon_rxr_struct * ubx_GetMonRXR(void);
ubx_tim_tp * ubx_GetTimTP(void);
ubx_tim_vrfy * ubx_GetTimVRFY(void);

float ToRad(float numdeg);

#endif //GPS_UBLOX_H__