
#include "xc.h"

//===============================================
//Application OVER PNC : 
//=================================================
#define REGULAR_SYSTEM           0 //
#define WHITELINE_ESCORTS        1
#define ACE_NX360                2
#define PALFINGER_KNUCKLE_BOOM   3
#define ACE_MANBASKET_HXP        4
#define FORK_LIFT                5 
#define TMC_MANBASKET            6          //Century with Slave display
#define TIL_PIXEF_TELE_PNC       7
#define PNC_FORK                 8
#define TMC_MANBASKET2           9          //Jindal
#define TELESCOPIC_RT40          10
//=================================================
#define ESCORTS_WELCOME_HINDI_MP3               1
#define DEPLOY_OTG_FOR_HIGH_BM_HIGHT_HINDI_MP3  2
#define FIRST_OR_REV_GEAR_ONLY_HINDI_MP3        3
#define DONT_DRIVE_CRANE_WITH_OTG_HINDI_MP3     4

#define ESCORTS_WELCOME_ENG_MP3                 5
#define DEPLOY_OTG_FOR_HIGH_BM_HIGHT_ENG_MP3    6
#define FIRST_OR_REV_GEAR_ONLY_ENG_MP3          7
#define DONT_DRIVE_CRANE_WITH_OTG_ENG_MP3       8

//==================================================

#define NUMBER_OF_ADC_SAMPLES   128
#define NUMBER_OF_FIFO          5

#define MRESET_PASSWORD         8051

#define LEN_DRUM_MAX            6

//====================CAN Ids================================
#define CAN_LENGTH_ANGLE_A2B    226
#define CAN_P1_P2_SLEW          227
#define CAN_P1P2P3P4_TILT       175
#define CAN_KOPs_SLAVE          180
#define CAN_LOADCELL_ANG_LEN    352
#define CAN_MAIN_LOADCELL       201
#define CAN_MAIN_ANGLE          361
#define CAN_MAIN_TILT_ANGLE     357
#define CAN_AUX_TILT_ANGLE      358


#define KEY_SW1            8    //LATEbits.LATE8
#define KEY_SW2            4    //LATDbits.LATD4
#define KEY_SW3            3    //LATDbits.LATD3
#define KEY_SW4            2    //LATDbits.LATD2
#define KEY_SW5            1    //LATDbits.LATD1
#define KEY_SW6            7    //LATAbits.LATA7

#define U4_PIC25K80_RX_B12      12  //RB12(RPI44)
#define U4_PIC25K80_TX_G13      13  //RG13(RP125)


//#define KEY6_DUTY    1
//#define KEY1_FUNC    2
//#define KEY2_INC     3
//#define KEY3_DEC     4
//#define KEY4_ENTR    5
//#define KEY5_BYPASS  6

#define NO_DECIMAL_POINT            0
#define ONE_DECIMAL_POINT           1


//Load status
#define LOAD_SAFE               0
#define LOAD_APPROACH           1
#define LOAD_OVRLOAD_WITH_BP    2
#define LOAD_OVRLOAD_CUTOFF     3
#define LOAD_LOW_NLZ            4
#define LOAD_HIGH_NLZ           5
#define LOAD_A2B_CUTOFF         6
#define LOAD_RADIUS_CUTOFF      7
#define LOAD_LOANG_CUTOFF       8
#define LOAD_HIANG_CUTOFF       9

//System Errors
#define SYS_NO_ERROR                    0x0000
#define SYS_LEN_LOERR_COUNTS            0x0001
#define SYS_LEN_HIERR_COUNTS            0x0002
#define SYS_ANG_LOERR_COUNTS            0x0004
#define SYS_ANG_HIERR_COUNTS            0x0008
#define SYS_P1_LOERR_COUNTS             0x0010
#define SYS_P1_HIERR_COUNTS             0x0020
#define SYS_P2_LOERR_COUNTS             0x0040
#define SYS_P2_HIERR_COUNTS             0x0080
//#define SYS_LEN_LOERR_COUNTS            256
//#define SYS_LEN_HIERR_COUNTS            512



#define FACT1        127
#define FACT2        129
#define FACT3        124
#define FACT4        120
#define FACT5        115

#define ONE_METER           10
#define TWO_METER           20
#define THREE_METER         30
#define FOUR_METER          40
#define SIX_METER           60
#define EIGHT_METER         80
#define TEN_METER           100
#define TWELVE_METER        120
#define SIXTEEN_METER       160
#define TWENTY_METER        200
#define TWFOUR_METER        240
#define THIRTY_METER        320

//======================SPI Flash Memory=================
#define SYSTEM_DEFAULT_SECTOR    0
#define FLASH_TEST_SECTOR        500

#define ONE_SECTOR_SIZE          4096
#define SYSTEM_DIRECTORY_SIZE    256
#define FLSH_MEMORY_OFFSET       ONE_SECTOR_SIZE+SYSTEM_DIRECTORY_SIZE
//======================SPI Flash Memory end=============

#define CAN_ID_OWN      352
#define CAN_ID1         351 //226
#define CAN_ID2         227

#define OTG_PRESS_HYSTERESIS    25

#define TILT_MIN_ANGLE          0
#define TILT_MAX_ANGLE          10


//#define DEBUG_MSG   1

#define ART_TABLE_START         62

#define DIGITAL_A2B_STATUS          0
#define DIGITAL_ART_STATUS          1

#define DETECTED_INPUT          1
#define RELEASED_INPUT          0
#define OPEN_INPUT_ERR          2
#define BLINKING_ERR            2

#define HI_NIBBLE               6

//=======================LED stats=======================
#define OVER_LOAD_LED            0x00
#define ERROR_LED                0x08
#define A2B_STATUS_LED           0x04
#define NLZ_STATUS_LED           0x01
#define OVER_ARTICULATION_LED    0x02


#define GREENLEDS	10
#define YELLOWLEDS	2
#define REDLEDS		4


//=======================LED stats end===================

//====================Digital Input bits=================
#define A2B_INPUT_BITS                               6
#define OVER_ARTICULATION_INPUT_BITS                 4
#define OTL_FRONT_INPUT_BITS                         2
#define OTR_FRONT_INPUT_BITS                         0

#define OTL_REAR_INPUT_BITS                          6
#define OTR_REAR_INPUT_BITS                          4
#define SPEED_GOVERNER_INPUT_BITS                    2
#define PROXIMITY_INPUT_BITS                         0

#define SAFE_BM_UP_INPUT_BITS                        6
#define SAFE_TELE_IN_INPUT_BITS                      4
#define SAFE_HOIST_DN_INPUT_BITS                     2
#define SAFE_NLZ_BM_DN_INPUT_BITS                    0

#define GEAR1_SWITCH_INPUT_BITS                      6
#define GEAR2_SWITCH_INPUT_BITS                      4
#define GEAR3_SWITCH_INPUT_BITS                      2
#define GEAR4_SWITCH_INPUT_BITS                      0

#define REVERSE_GEAR_SWITCH_INPUT_BITS               6
#define OVER_LOWERING_SWITCH_INPUT_BITS              4
#define SEAT_BELT_SWITCH_INPUT_BITS                  2
#define OPERATOR_DETECT_SWITCH_INPUT_BITS            0

#define BYPASS_KEY_INPUT_BITS                        6
#define SPARE1_INPUT_BITS                            4
#define SPARE2_INPUT_BITS                            2
//====================Digital Input bits end===============

#define INPUT_DETECTED              0x01
#define INPUT_WIRE_OPEN             0x02
#define INPUT_NOT_DETECTED          0x00

#define FIRST_FRAME                 0
#define SECOND_FRAME                1
#define THIRD_FRAME                 2
#define FOURTH_FRAME                3
#define FIFTH_FRAME                 4
#define SIXTH_FRAME                 5
#define SEVENTH_FRAME               6
#define EIGHTH_FRAME                7

//=========================Whiteline=====================
#define DELAY3_SENSE_DEBAUNCE            4000
#define DELAY1_BETWEEN_TWO_TRACKS        10000
#define DELAY2_BETWEEN_TWO_TRACKS        300000

#define CONSECUITIVE 2

//======================GUI stats========================
#define DEFAULT_PAGE                                     0
#define SYSTEM_SETUP_PAGE                                1
#define SELECT_MENU_PAGE                                 2
#define PASSWORD_PAGE                                    3
#define OPERATOR_MENU_PAGE                               4
#define OPERATOR_VIEW_PAGE                               5
#define OPERATOR_SET_CODE_PAGE                           6
#define OPERATOR_SET_PAGE                                7
#define SUPERVISOR_SET_CODE_PAGE                         8
#define SUPERVISOR_SET_PAGE                              9
#define SITE_SET_CODE_PAGE                               10
#define SITE_SET_PAGE                                    11
#define FACTORY_SET_CODE_PAGE                            12
#define FACTORY_SET_PAGE                                 13
#define SET_DT_CALIB_LEN_PAGE                            14
#define DUTY_TYPE_INDEX_PAGE                             15
#define LEN_CALIB_POINTS_PAGE                            16
#define HOOK_LOAD_CALIB_PAGE1                            17
#define HOOK_LOAD_CALIB_PAGE2                            18
#define HOOK_LOAD_CALIB_PAGE3                            19
#define HOOK_LOAD_CALIB_PAGE4                            20
#define HOOK_LOAD_CALIB_PAGE5                            21
#define HOOK_LOAD_CALIB_PAGE6                            22
#define HOOK_LOAD_CALIB_PAGE7                            23
#define HOOK_LOAD_CALIB_PAGE8                            24
#define SELECT_LEN_COUNT_PAGE                            25
#define EDIT_LEN_COUNTS_PAGE                             26
#define SET_CRANE_DETAILS_PAGE                           27
#define SELECT_CRANE_MODEL_PAGE                          28
#define SET_PERC_STATUS_PAGE                             29
#define SET_PERC_FACTOR_PAGE                             30
#define VIEW_PC_PAGE1                                    31
#define VIEW_PC_PAGE2                                    32
#define VIEW_PC_PAGE3                                    33
#define START_COPY_DUTY_PAGE                             34
#define END_COPY_DUTY_PAGE                               35
#define SELECT_LENGTH_FACTOR_PAGE                        36
#define EDIT_LEN_FACTOR_PAGE                             37
#define OPER_DUMMY_LOAD_CALIB_PAGE                       38
#define OPER_DUMMY_LOAD_CALIB_PAGE1                      39
#define OPER_DUMMY_LOAD_CALIB_PAGE2                      40
#define VIEW_LIFTED_PC_PAGE1                             41
#define VIEW_LIFTED_PC_PAGE2                             42
#define WRITE_TO_MEMORY_PAGE1                            43
#define WRITE_TO_MEMORY_PAGE2                            44
#define WRITE_TO_MEMORY_PAGE3                            45
#define WRITE_TO_MEMORY_PAGE4                            46
#define SET_PRESSURE_FACTOR_PAGE                         47
#define SET_DIGITS_MENU_PAGE                             48
#define FORK_PRESS_MINMAX_PAGE1                          49
#define FORK_PRESS_MINMAX_PAGE2                          50
#define VIEW_PRESS_CALIB_POINT_PAGE1                     51
#define VIEW_PRESS_CALIB_POINT_PAGE2                     52
#define TMC_PRESS_MINMAX_PAGE                            53
#define VIEW_DUTY_TABLE_PAGE1                            54
#define VIEW_DUTY_TABLE_PAGE2                            55
#define PRESSURE_CURVE_SEND_PAGE                         56
#define SET_ART_DRATE_PERCENTAGE1                        57
#define SET_ART_DRATE_PERCENTAGE2                        58
#define SELECT_MIN_MAX_PCURVE_PAGE                       59
#define SET_MIN_ANGLE_PCURVE_PAGE                        60
#define SET_MAX_ANGLE_PCURVE_PAGE                        61
#define BRING_BOOM_DN_PCURVE_PAGE                        62
#define ENTRKEY_BOOM_UP_PCURVE_PAGE                      63
#define ENTRKEY_BOOM_DN_PCURVE_PAGE                      64
#define TAKE_P1P2_PCURVE_UP_PAGE                         65
#define TAKE_P1P2_PCURVE_DN_PAGE                         66
#define SET_KNOWN_LOAD_PCURVE_PAGE                       67
#define VIEW_PCURVE_PAGE                                 68
#define SET_LIVE_LEN_ANGLE_PCURVE_PAGE                   69
#define LEN_MPOINT_CALIBRATION_PAGE1                     70
#define LEN_MPOINT_CALIBRATION_PAGE2                     71
#define FREEZE_LD_ABOVE_ANGLE_PAGE1                      72
#define FREEZE_LD_ABOVE_ANGLE_PAGE2                      73
//============================================================
#define OPERATOR_VIEW_MENU       1
#define OPERATOR_SET_MENU        2
#define SUPERVISOR_SET_MENU      3
#define SITE_SET_MENU            4
#define FACTORY_SET_MENU         5
//====================GUI stats end====================

//===============Operator view set codes====================
#define PRESS1_COUNT            1
#define PRESS2_COUNT            2
#define BMLEN_COUNT             3
#define BMANGL_COUNT            4
#define BM_MANGL_COUNT          5
#define SET_POINTS              6
#define VIEW_BM_OFFSET          7
#define VIEW_HD_OFFSET          8
#define VIEW_ALL_PRESS_CNTS     9
#define VIEW_DT_TM              10
#define VIEW_LOADCELL_CNTS      11
#define VIEW_GPS_TIME           12
#define VIEW_ZLD_PCURVE         13

//===============Operator set codes====================
#define SET_DUTY                 1
#define SET_FALLS                2
#define SET_UOM                  3
//===============Operator set codes end================

//===============Supervisor set codes==================
#define EN_BYPASS_SWITCH         1
#define SET_SP1_VALUE            2
#define SET_SP2_VALUE            3
#define SET_SP3_VALUE            4
#define SET_SP4_VALUE            5
#define SET_BOOM_OFFSET          6
#define SET_BM_HEAD_OFFSET       7
#define SET_BM_TIP_OFFSET        8
#define SET_MAIN_SAMPLE_CNT      9
#define SET_HOOK_LOAD            10
#define CALIB_LENGTH_MIN         11
#define CALIB_LENGTH_MAX         12
#define CALIB_ANGLE_MIN          13
#define CALIB_ANGLE_MAX          14
#define CALIB_MANGLE_MIN         15
#define CALIB_MANGLE_MAX         16
#define NUMOF_CALIB_POINTS       17
#define SET_DUTY_TYPE            18         //For fork lift use this page for calib pressr min
#define CALIB_HOOK_LOAD          19         //For fork lift use this page for calib pressr max
#define EN_PASSWORD              20
#define EN_BM_DWN_RLY            21
#define EN_BM_UP_RLY             22
#define EN_HOOTER_RLY            23
#define EN_A2B                   24
#define EN_HK_HEIGHT             25
#define RIG_LOAD_LIMIT           26
#define RIG_BM_ANGLE_LIMIT       27
#define RIG_BM_LENGTH_LIMIT      28
#define RIG_DEFAULT_DUTY         29
#define EDIT_ENGINE_NUMBER       30
#define ARTICULATION_DERATE_PERC 31               //All duty art. derate percentage
#define VIEW_DATA_LOGGED         32
#define SEND_DATA_TO_PC          33
#define LOW_CUTOFF_ANGLE         34
#define HIGH_CUTOFF_ANGLE        35
#define EN_DUTY_SELECT           36
#define EN_SNATCH_BLOCK          37
#define SNATCH_BLOCK_VALUE       38
#define BYPASS_METHOD            39
#define FRONT_TILT_ANGLE_CALIB   40
#define REAR_TILT_ANGLE_CALIB    41
#define FRONT_TILT_CUTOFF        42
#define REAR_TILT_CUTOFF         43
#define VOICE_LANGUAGE           44
#define SET_ZERO_LOAD_MASKING    45
#define LOAD_ANNOUNCE_TIMER      46
#define SET_MAX_BOOM_LENGTH      47
#define SET_MAX_BOOM_ANGLE       48
#define SET_HEIGHT_OFFSET        49
#define SET_LOADCEL_ADC_OFFST    50
#define CALIB_MANBAS_MIN         51
#define CALIB_MANBAS_MAX         52
#define EN_ART_DRATE_PERC        53
#define ART_DRATE_PERC_VALUE     54
#define SET_SLEW_OFFSET          55
#define EN_ONBOARD_SING_TILT     56
#define EN_SLAVE_DISPLAY         57
#define EN_MPOINT_LEN_CALIB         58
#define NUMOF_MPOINT_LEN_CALIB      59
#define MPOINT_LCALIBRATION_MENU    60

#define MASTER_RESET_DEFAULT     70

/*Application Menu Starts here Refer .c files of Specific Application*/
//===============Supervisor set codes end==============

//==================Site set codes=====================
#define MIN_BOOM_LEGTH           1
#define MAX_BOOM_LEGTH           2
#define SET_PRESS_P1_CHANNEL     3
#define SET_PRESS_P2_CHANNEL     4
#define SET_LENGTH_CHANNEL       5
#define SET_ANGLE_CHANNEL        6
#define SET_MANGLE_CHANNEL       7
#define SET_LOW_ERR_COUNT        8
#define SET_HIGH_ERR_COUNT       9
#define SET_CAL_SAMPLE_COUNT     10
#define LOAD_CORR_FACTOR         11
#define LOAD_CORR_LIMIT          12
#define COPY_ZERO_CALIB          13
#define SET_DATE_TIME            14
#define EDIT_LENGTH_COUNT        15
#define BM_LENGTH_CORR_1         16
#define BM_LENGTH_CORR_2         17
#define BM_LENGTH_CORR_3         18
#define BM_LENGTH_CORR_4         19
#define FAIL_SAFE_STATUS_CASE    20
#define LOAD_CORR_1              21
#define LOAD_CORR_2              22
#define LOAD_CORR_3              23
#define LOAD_CORR_4              24
#define LOAD_CORR_5              25
#define LENGTH_FACTORS           26
#define PRESSURE_FACTOR          27
#define COPY_ZLOAD_PCURVE        28
#define EN_PEAKNHOLD_OPTION      29         //Spacially for Terex FR17
#define ENTR_LOAD_THRESHOLD      30
#define VIEW_DUTY_TABLE          31

#define CUSTOMER_CARE_NUM        254
#define USB_MASS_STORAGE         255
//==================Site set codes end===================

//==================Factory set codes====================
#define CALIB_PRESSURE_P1_MIN           1
#define CALIB_PRESSURE_P1_MAX           2
#define CALIB_PRESSURE_P2_MIN           3
#define CALIB_PRESSURE_P2_MAX           4
#define EN_LOAD_AVERAGING_VALUE         5
#define WINDOW_SAMPLES_SIZE             6
#define NUM_OF_CYLINDERS                7
#define WRITE_TO_MEMORY                 8
#define CRANE_DETAILS                   9
#define SET_BM_ANGLE_MIN                10
#define SET_BM_ANGLE_MAX                11
#define SET_BM_LENGTH_MIN               12
#define SET_BM_LENGTH_MAX               13
//#define SET_CALIB_DATE_TIME      14
#define SET_CRANE_MODEL                 14
#define SET_BAUDRATE                    15
#define ERASE_DATA_LOGS                 16
#define SELECT_SENSOR                   17
#define DEFAULT_BL_ADC_COUNT            18
#define WINDOW_SAMPLES_SIZE1            19
#define STICKER_TYPE                    20
#define SET_INSALLATION_DATE            21
#define SET_PERCENTAGE_STATUS           22
#define SET_CORRECTION_LOAD             23
#define EN_NUMBER_OF_CALIB              24
#define SET_SO_NUMBER                   25
#define P1P2_TO_RS232_PC                26
#define SET_RADIUS_CUTOFF               27
#define SET_MANBASKET_DUTY              28
#define SET_MANBASKET_CHANN             29
#define NO_LOAD_PRESSURE_CURVE_UP       30          //Pressure curve observations
#define NO_LOAD_PRESSURE_CURVE_DN       31          //Pressure curve observations
#define WITH_LOAD_PRESSURE_CURVE_UP     32          //Pressure curve observations
#define WITH_LOAD_PRESSURE_CURVE_DN     33          //Pressure curve observations
#define VIEW_NO_LOAD_PRESSURE_CURVE_UP  34          //Pressure curve observations
#define VIEW_NO_LOAD_PRESSURE_CURVE_DN  35          //Pressure curve observations
#define VIEW_WITH_LOAD_PRESSURE_CURVE_UP 36          //Pressure curve observations
#define VIEW_WITH_LOAD_PRESSURE_CURVE_DN 37          //Pressure curve observations
#define SELECT_LENGTH_DRUM              38
#define SELECT_SYSTEM                   39

//================Factory set codes end==================
#define MAX_SEL_SYSTEM           11

#define MOVE_SYSTEM_SETTINGS       1
#define MOVE_PRESSURE_CURVE        2
#define MOVE_WHOLE_CSV             3

#define PI                               3.141592

#define DEG_TO_RAD                       0.017453
#define RAD_TO_DEG                       57.29577
#define PI                               3.141592

#define factor_bar                       0.150319
#define MIN_ADC_Pressure                 640

#define MAXADC_CH                        4

#define OLD                              1        // OLD = OvrLed .....
#define NEW                              2        // New = ART_Led.....

#define MAX_LENGTH_CALIB_PT              5

#define MAX_SENSOR_OPTIONS               3

//System parameters values on SPI flash sector 0
#define FACTORY_DEFAULT_RESET      0
#define SYS_PARA_MEM_BASE_ADDR     1
#define DLC_HIGH                   1
#define DLC_LOW                    2
#define MAIN_SMPL_CNT_HIGH         3
#define MAIN_SMPL_CNT_LOW          4
#define NUMBER_OF_CYLINDERS        5
#define CALIB_SMPL_CNT_HIGH        6
#define CALIB_SMPL_CNT_LOW         7
#define NUMBER_OF_FALLS            8
#define UNIT_OF_MEASUREMEMNT       9
#define SET_POINT_1_HIGH           10

#define SET_POINT_1_LOW            11
#define SET_POINT_2_HIGH           12
#define SET_POINT_2_LOW            13
#define SET_POINT_3_HIGH           14
#define SET_POINT_3_LOW            15
#define SET_POINT_4_HIGH           16
#define SET_POINT_4_LOW            17
#define BOOM_OFFSET_HIGH           18
#define BOOM_OFFSET_LOW            19
#define BM_HEAD_OFFSET_HIGH        20

#define BM_HEAD_OFFSET_LOW         21
#define BM_TIP_OFFSET_HIGH         22
#define BM_TIP_OFFSET_LOW          23
#define BAUDRATE_HIGH              24
#define BAUDRATE_LOW               25
#define ART_DERATE_PERC_HIGH       26
#define ART_DERATE_PERC_LOW        27
#define LOAD_CORR_LMT_HIGH         28
#define LOAD_CORR_LMT_LOW          29
#define SELECT_SENSOR_HIGH         30

#define SELECT_SENSOR_LOW          31
#define CALIB_P1MIN_HIGH           32
#define CALIB_P1MIN_LOW            33
#define CALIB_P1MIN_ADC_CNT_HIGH   34
#define CALIB_P1MIN_ADC_CNT_LOW    35
#define CALIB_P1MAX_HIGH           36
#define CALIB_P1MAX_LOW            37
#define CALIB_P1MAX_ADC_CNT_HIGH   38
#define CALIB_P1MAX_ADC_CNT_LOW    39
#define CALIB_P2MIN_HIGH           40

#define CALIB_P2MIN_LOW            41
#define CALIB_P2MIN_ADC_CNT_HIGH   42
#define CALIB_P2MIN_ADC_CNT_LOW    43
#define CALIB_P2MAX_HIGH           44
#define CALIB_P2MAX_LOW            45
#define CALIB_P2MAX_ADC_CNT_HIGH   46
#define CALIB_P2MAX_ADC_CNT_LOW    47
#define CALIB_BM_ANGLE_MIN_HIGH    48
#define CALIB_BM_ANGLE_MIN_LOW     49
#define CALIB_BA_MIN_CNT_HIGH      50

#define CALIB_BA_MIN_CNT_LOW       51
#define CALIB_BM_ANGLE_MAX_HIGH    52
#define CALIB_BM_ANGLE_MAX_LOW     53
#define CALIB_BA_MAX_CNT_HIGH      54
#define CALIB_BA_MAX_CNT_LOW       55
#define BM_LENGTH_MIN_HIGH         56
#define BM_LENGTH_MIN_LOW          57
#define BM_LENGTH_MAX_HIGH         58
#define BM_LENGTH_MAX_LOW          59
#define CALIB_BM_LENGTH_MIN_HIGH   60

#define CALIB_BM_LENGTH_MIN_LOW    61
#define CALIB_BM_LENGTH_MAX_HIGH   62
#define CALIB_BM_LENGTH_MAX_LOW    63
#define BM_LENGTH1_ACD_HIGH        64
#define BM_LENGTH1_ACD_LOW         65
#define BM_LENGTH2_ACD_HIGH        66
#define BM_LENGTH2_ACD_LOW         67
#define BM_LENGTH3_ACD_HIGH        68
#define BM_LENGTH3_ACD_LOW         69
#define BM_LENGTH4_ACD_HIGH        70

#define BM_LENGTH4_ACD_LOW         71
#define BM_LENGTH5_ACD_HIGH        72
#define BM_LENGTH5_ACD_LOW         73
#define BM_LENGTH6_ACD_HIGH        74
#define BM_LENGTH6_ACD_LOW         75
#define CALIB_BL_ADC_MAX_CNT_HIGH  76
#define CALIB_BL_ADC_MAX_CNT_LOW   77
#define BYPASS_KEY_EN_DISABLE      78
#define HOOK_HIGHT_STATUS          79
#define LO_ERROR_CNT_HIGH          80

#define LO_ERROR_CNT_LOW           81
#define HI_ERROR_CNT_HIGH          82
#define HI_ERROR_CNT_LOW           83
#define P1_CHAN_NUM_HIGH           84
#define P1_CHAN_NUM_LOW            85
#define P2_CHAN_NUM_HIGH           86
#define P2_CHAN_NUM_LOW            87
#define BM_LEN_CHAN_NUM_HIGH       88
#define BM_LEN_CHAN_NUM_LOW        89
#define BM_ANG_CHAN_NUM_HIGH       90

#define BM_ANG_CHAN_NUM_LOW        91
#define MIN_ANG_HIGH               92
#define MIN_ANG_LOW                93

#define DEFAULT_DUTY_HIGH          94
#define DEFAULT_DUTY_LOW           95
#define RIG_DUTY_FLAG              96
#define LOAD_LIMIT_HIGH            97
#define LOAD_LIMIT_LOW             98
#define BM_LENGHT_LIMIT_HIGH       99
#define BM_LENGHT_LIMIT_LOW        100

#define BM_ANGLE_LIMIT_HIGH        101
#define BM_ANGLE_LIMIT_LOW         102
#define PASSWORD_STATUS            103
#define BM_DN_RELAY_STATUS         104
#define BM_UP_RELAY_STATUS         105
#define HOOTER_RELAY_STATUS        106
#define A2B_SWITCH_STATUS          107

#define LOAD_AVG_VAL_HIGH          108
#define LOAD_AVG_VAL_LOW           109
#define WINDO_SMPL_SIZE_HIGH       110

#define WINDO_SMPL_SIZE_LOW        111
#define WINDO_SMPL_SIZE1_HIGH      112
#define WINDO_SMPL_SIZE1_LOW       113
#define HOOK_LOAD_HIGH             114
#define HOOK_LOAD_LOW              115
#define GROUP_DUTY_S_HIGH          116
#define GROUP_DUTY_S_LOW           117

#define VERTICAL_OFFSET_HIGH       118
#define VERTICAL_OFFSET_LOW        119
#define HORIZONTAL_OFFSET_HIGH     120

#define HORIZONTAL_OFFSET_LOW      121
#define RAMPIVOT_OFFSET_HIGH       122
#define RAMPIVOT_OFFSET_LOW        123
#define BM_CENTR_LINE_OFFSET_HIGH  124
#define BM_CENTR_LINE_OFFSET_LOW   125
#define PISTON_DIAMETER_HIGH       126
#define PISTON_DIAMETER_LOW        127
#define ROD_DIAMETER_HIGH          128
#define ROD_DIAMETER_LOW           129
#define BM_LENGTH_CORR1_HIGH       130

#define BM_LENGTH_CORR1_LOW        131
#define BM_LENGTH_CORR2_HIGH       132
#define BM_LENGTH_CORR2_LOW        133
#define BM_LENGTH_CORR3_HIGH       134
#define BM_LENGTH_CORR3_LOW        135
#define BM_LENGTH_CORR4_HIGH       136
#define BM_LENGTH_CORR4_LOW        137
#define FAIL_SAFE_STATUS           138
#define BM_ANGLE_CUTOFF_MAX_HIGH   139
#define BM_ANGLE_CUTOFF_MAX_LOW    140

#define BM_ANGLE_CUTOFF_MIN_HIGH   141
#define BM_ANGLE_CUTOFF_MIN_LOW    142
#define DUTY_SELECT_STATUS         143
#define SNATCH_BLOCK_STATUS        144
#define SNATCH_BLK_THRE_VAL_HIGH   145
#define SNATCH_BLK_THRE_VAL_LOW    146
#define STICKET_TYPE_HIGH          147
#define STICKET_TYPE_LOW           148
#define BPK_METODE_STATUS          149
#define LOAD_CORR1_HIGH            150

#define LOAD_CORR1_LOW             151
#define LOAD_CORR2_HIGH            152
#define LOAD_CORR2_LOW             153
#define LOAD_CORR3_HIGH            154
#define LOAD_CORR3_LOW             155
#define LOAD_CORR4_HIGH            156
#define LOAD_CORR4_LOW             157
#define LOAD_CORR5_HIGH            158
#define LOAD_CORR5_LOW             159
#define FACTOR_HIGH                160

#define FACTOR_LOW                 161
#define PERC_FACT_STATUS           162
#define CORRECTION_LOAD_HIGH       163
#define CORRECTION_LOAD_LOW        164
#define NUM_CAL_HIGH               165
#define NUM_CAL_LOW                166

#define LOAD_AVG_STATUS            167
#define MAX_ANG_HIGH               168
#define MAX_ANG_LOW                169
#define GROUP_DUTY_E_HIGH          170
#define GROUP_DUTY_E_LOW           171
#define CURR_DUTY_HIGH             172
#define CURR_DUTY_LOW              173
#define ENGINE_NUMBER_BYTE1        174
#define ENGINE_NUMBER_BYTE2        175
#define ENGINE_NUMBER_BYTE3        176
#define ENGINE_NUMBER_BYTE4        177
#define SO_NUMBER_BYTE1            178
#define SO_NUMBER_BYTE2            179
#define SO_NUMBER_BYTE3            180
#define SO_NUMBER_BYTE4            181

#define INSTALLATION_DATE          183         //4bytes(dd/mm/yyyy)
#define CSV_INDEX_PAGE_HIGH        187
#define CSV_INDEX_PAGE_LOW         188
#define RADIUS_CUTOFF_LOCATION     189
#define LOAD_CORR_FACT_HIGH        190
#define LOAD_CORR_FACT_LOW         191
#define BM_LENGTH_FACT1_HIGH       192
#define BM_LENGTH_FACT1_LOW        193
#define BM_LENGTH_FACT2_HIGH       194
#define BM_LENGTH_FACT2_LOW        195
#define BM_LENGTH_FACT3_HIGH       196
#define BM_LENGTH_FACT3_LOW        197
#define BM_LENGTH_FACT4_HIGH       198
#define BM_LENGTH_FACT4_LOW        199
#define BM_LENGTH_FACT5_HIGH       200
#define BM_LENGTH_FACT5_LOW        201

#define MOB_NUMBER_BYTE1           202
#define MOB_NUMBER_BYTE2           203
#define MOB_NUMBER_BYTE3           204
#define MOB_NUMBER_BYTE4           205

#define DN_LEN_CALIB_PTS_START     512         //2 pages of 256 bytes for duty no. length calib points.

#define DN_LEN_CALIB_ARRAY_START   1024        //1024 onwards for duty no. length calib values.

#define LOAD_CORR_BM_UP_START      2048

#define TL_GREEN_LAMP           0x01
#define TL_AMBER_LAMP           0x02
#define TL_RED_LAMP             0x04

