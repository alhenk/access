#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <jni.h>

#include "../hidapi/hidapi.h"
#include "Cr95hf.h"
#include "reports.h"

// Headers needed for sleeping.
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

JNIEXPORT jstring JNICALL Java_Cr95hf_getUID(JNIEnv *env, jobject obj){

    int res;
    unsigned char buf[256];
    #define MAX_STR 255
    wchar_t wstr[MAX_STR];
    hid_device *handle;
    int i;

    unsigned char fail[]="unable to open device from java\n";
    const char * report;
    

#ifdef WIN32
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#endif

	struct hid_device_info *devs, *cur_dev;
	char outReport[REPORT_BUF_LENGTH];
	//char inReport[REPORT_BUF_LENGTH] = {0x07, 0x80, 0x08, 0xfe, 0xae, 0x69, 0xef, 0xd6};
	char uid[16] = "uid init";

	devs = hid_enumerate(0x0, 0x0);
	cur_dev = devs;	

	while (cur_dev) {
		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		printf("  Product:      %ls\n", cur_dev->product_string);
		printf("  Release:      %hx\n", cur_dev->release_number);
		printf("  Interface:    %d\n",  cur_dev->interface_number);
		printf("\n");
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	// Set up the command buffer.
	memset(buf,0x00,sizeof(buf));
	buf[0] = 0x01;
	buf[1] = 0x81;
	

	// Open the device using the VID, PID,
	// and optionally the Serial number.
	////handle = hid_open(0x4d8, 0x3f, L"12345");
	handle = hid_open(0x0483,0xd0d0, NULL);
	if (!handle) {
		printf("unable to open device from c\n");
                report = (const char *)fail;
 		return (*env)->NewStringUTF(env, report);
	}

	// Read the Manufacturer String
	wstr[0] = 0x0000;
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read manufacturer string\n");
	printf("Manufacturer String: %ls\n", wstr);

	// Read the Product String
	wstr[0] = 0x0000;
	res = hid_get_product_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read product string\n");
	printf("Product String: %ls\n", wstr);

	// Read the Serial Number String
	wstr[0] = 0x0000;
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read serial number string\n");
	printf("Serial Number String: (%d) %ls", wstr[0], wstr);
	printf("\n");

	// Read Indexed String 1
	wstr[0] = 0x0000;
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read indexed string 1\n");
	printf("Indexed String 1: %ls\n", wstr);

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);
	
	// Try to read from the device. There shoud be no
	// data here, but execution should not block.
	res = hid_read(handle, buf, 17);


	memset(buf,0,sizeof(buf));
/********************************************************************/
        for(i=0;i<64;i++) buf[i]=0xcc;
	// Send Echo.The first byte is the report number (0x1).

	buf[0] = 0x01; //report number
	buf[1] = 0x55;//
	res = hid_write(handle, outReport, 64);
	if (res < 0) {
		printf("Unable to write()\n");
		printf("Error: %ls\n", hid_error(handle));
	}

	// Read requested state. hid_read() has been set to be
	// non-blocking by the call to hid_set_nonblocking() above.
	// This loop demonstrates the non-blocking nature of hid_read().

	res = 0;
	while (res == 0) {
		res = hid_read(handle, buf, sizeof(buf));
		if (res == 0)
			printf("waiting...\n");
		if (res < 0)
			printf("Unable to read()\n");
		#ifdef WIN32
		Sleep(500);
		#else
		usleep(500*1000);
		#endif
	}

	printf("Data read:\n   ");
	// Print out the returned buffer.
	for (i = 0; i < res; i++)
		printf("%02hhx ", buf[i]);
	printf("\n");
/********************************************************************/
        for(i=0;i<64;i++) buf[i]=0xcc;
	// Send Select.The first byte is the report number (0x1).

	buf[0] = 0x01; //report number
	buf[1] = 0x02;//
	buf[2] = 0x02;//
	buf[3] = 0x01;//
	buf[4] = 0x0d;//
	buf[5] = 0x00;//
	buf[6] = 0x00;//
	buf[7] = 0x00;//
	res = hid_write(handle, buf, 64);
	if (res < 0) {
		printf("Unable to write()\n");
		printf("Error: %ls\n", hid_error(handle));
	}

	// Read requested state. hid_read() has been set to be
	// non-blocking by the call to hid_set_nonblocking() above.
	// This loop demonstrates the non-blocking nature of hid_read().

	res = 0;
	while (res == 0) {
		res = hid_read(handle, buf, sizeof(buf));
		if (res == 0)
			printf("waiting...\n");
		if (res < 0)
			printf("Unable to read()\n");
		#ifdef WIN32
		Sleep(500);
		#else
		usleep(500*1000);
		#endif
	}

	printf("Data read:\n   ");
	// Print out the returned buffer.
	for (i = 0; i < res; i++)
		printf("%02hhx ", buf[i]);
	printf("\n");
/********************************************************************/
        for(i=0;i<64;i++) buf[i]=0xcc;
	// Send Send/Receive.The first byte is the report number (0x1).

	buf[0] = 0x01; //report number
	buf[1] = 0x04;//
	buf[2] = 0x03;//
	buf[3] = 0x26;//
	buf[4] = 0x01;//
	buf[5] = 0x00;//
	buf[6] = 0x00;//
	buf[7] = 0x00;//
	res = hid_write(handle, buf, 64);
	if (res < 0) {
		printf("Unable to write()\n");
		printf("Error: %ls\n", hid_error(handle));
	}

	// Read requested state. hid_read() has been set to be
	// non-blocking by the call to hid_set_nonblocking() above.
	// This loop demonstrates the non-blocking nature of hid_read().

	res = 0;
	while (res == 0) {
		res = hid_read(handle, buf, sizeof(buf));
		if (res == 0)
			printf("waiting...\n");
		if (res < 0)
			printf("Unable to read()\n");
		#ifdef WIN32
		Sleep(500);
		#else
		usleep(500*1000);
		#endif
	}

	printf("Data read:\n   ");
	// Print out the returned buffer.
	for (i = 0; i < res; i++)
		printf("%02hhx ", buf[i]);
	printf("\n");
/********************************************************************/


	hid_close(handle);

	/* Free static HIDAPI objects. */

#ifdef WIN32
	system("pause");
#endif
	printf("parsing result is %d\n", parseInHidReport(ISO_14443, buf, uid));
        report = (const char *)uid;
	return (*env)->NewStringUTF(env, report);

}
