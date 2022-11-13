/**
 * @file main_hw2_wvpp.c
 * @brief File with main function for CS 350 Homework #2: West Virginia Population Problem
 * @author Brian Powell
 * 
 * Place this file in the same directory as your own source code and add it to your project.
 * 
 * DO NOT MODIFY THE CONTENTS OF THIS FILE OTHER THAN AS INDICATED BELOW.
 */

// Include header files
#include "hw2_wvpp.h"
#include <stdio.h>

/**
* @brief Program entry point
*/
int main(void) {
	// Define filename to read from
	// You may change the contents of the input_file variable if convenient while writing your program
	const char* input_file = "counties.txt";

	// Define filename to save to
	// You may change the contents of the output_file variable if convenient while writing your program
	const char* output_file = "output.csv";

	// Create list
	list* listPtr = create_list();

	// Load data into list
	load_counties(listPtr, input_file);


	// Delete specified counties
	delete_by_county_name(listPtr, "Brooke");
	delete_by_county_name(listPtr, "Ohio");

	// Print CSV file with results
	save_counties(listPtr, output_file);

	// Print name of programmer
	printf("Code written by %s\n", get_programmer_name());

	return 0;
}
