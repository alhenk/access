/**
 *@addtogroup access_control_project_c		
 *@{
 */

/**
 *@defgroup requests_15693
 */

#define ISO_15693 1
#define ISO_14443 2

#define UNKNOWN_IN_REPORT_ID -1
#define UID_OK 0
#define EMPTY_REPORT 1   
 
#define REPORT_LENGTH 64
#define REPORT_BUF_LENGTH REPORT_LENGTH+1
#define OUT_REPORT_ID '0x01'
#define FILLER '0xcc'

static char dllEcho[2]                   = {0x55, '\0'};

//ISO 15693
static char dllSelect_iso15693[8]        = {0x02, 0x02, 0x01, 0x0D, 0x00, 0x00, 0x00, '\0'};
static char dllSendReceive_iso15693[8]   = {0x04, 0x03, 0x26, 0x01, 0x00, 0x00, 0x00, '\0'};

//ISO 14443
static char dllSelect_iso14443[8]        = {0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, '\0'};
static char dllSendReceive1_iso14443[9]  = {0x04, 0x03, 0x93, 0x20, 0x08, 0x00, 0x00, 0x00, '\0'};
static char dllSendReceive2_iso14443[11] = {0x04, 0x04, 0x93, 0x70, 0x00, 0x28, 0x00, 0x00, 0x00, '\0'};
static char dllSendReceive3_iso14443[9]  = {0x04, 0x03, 0x30, 0x00, 0x28, 0x00, 0x00, 0x00, '\0'};


int getReportLength(char *array);
void makeOutHidReport(char reportId, char filler, int outReportLength, char *outReport, char *data);
int parseInHidReport(int iso, char *inReport, char *uid);




/**
 *@}
 */ //access_control_project_c
