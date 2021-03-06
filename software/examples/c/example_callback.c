
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_motion_detector.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID


// Callback function for end of detection cycle 
void cb_detection_cycle_ended(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Detection Cycle Ended (next detection possible in ~3 seconds)\n");
}

// Callback function for detected motion
void cb_motion_detected(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Motion Detected\n");
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	MotionDetector md;
	motion_detector_create(&md, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Register detected callback to function cb_motion_detected
	motion_detector_register_callback(&md,
	                                  MOTION_DETECTOR_CALLBACK_MOTION_DETECTED,
	                                  (void *)cb_motion_detected,
	                                  NULL);

	// Register detection cycle ended callback to function cb_detection_cycle_ended
	motion_detector_register_callback(&md,
	                                  MOTION_DETECTOR_CALLBACK_DETECTION_CYCLE_ENDED,
	                                  (void *)cb_detection_cycle_ended,
	                                  NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
