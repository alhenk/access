#include "reports.h"
#include <stdio.h>

int getReportLength(char *array){
	int idx = 0;
	while(array[idx] != '\0') idx++;
	return idx;
}

void makeOutHidReport(char reportId, char filler, int outReportLength, char *outReport, char *data){
	int i=0, j=0;
	int reportFillerLength = 0;
	//Set report ID
	outReport[i++] = reportId;
    
	//Set report data
	for(; data[j] != '\0'; j++, i++)
		outReport[i] = data[j];
	 
	//Set report filler
	for(j=0, reportFillerLength = (outReportLength - i); j < reportFillerLength; j++, i++)
		outReport[i] = filler;
	
	//Set 
	outReport[i] = '\0';
}

int parseInHidReport(int iso, char *inReport, char *uid){
	
	switch(iso){
		case ISO_15693:
			switch(inReport[0]){
				case 0x07:
					/*switch(inReport[1]){
					????????????????????????????????????????????????????????????????????????
					}*/
				break;
				default:
					return UNKNOWN_IN_REPORT_ID;
			}
		break;
		
		case ISO_14443:
			switch(inReport[0]){
				case 0x07:
					if((inReport[1] == (char)0x80)){
						uid[0] = inReport[3];
						uid[1] = inReport[4];
						uid[2] = inReport[5];
						uid[3] = inReport[6];
						uid[4] = inReport[7];
						uid[5] = '\0';
						return UID_OK;
					}
					else{
						uid[0] = 'e';
						uid[1] = 'm';
						uid[2] = 'p';
						uid[3] = 't';
						uid[4] = 'y';
						uid[5] = '\0';
						return EMPTY_REPORT;
					}
				default:
					return UNKNOWN_IN_REPORT_ID;
			}
		break;
	}

}





