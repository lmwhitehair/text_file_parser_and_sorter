#include "hw2_wvpp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <io.h>
#include <string.h>
#include <ctype.h>

#define _CRT_SECURE_NO_WARNINGS

/**
 * @author: Logan Whitehair
 * @file: whitehair_logan_hw2_wvpp.c
 * @brief: this program recieves a formatted text document with data, sorts the data within a linked list, and saves the sorted data to a csv file 
 * 
 * Visual Studio 2022
*/


/**
 * @brief: node structure for storing data 
*/
typedef struct node {

	char* county_name;
	char* fips_code;							
	char* seat;
	int population;
	int area;

	struct node* nextPtr;

}node;

/**
 * @brief: function declarations
*/
list* create_list(void);
node* get_head_node(list* listPtr);
void add_sorted_county(list* listPtr, const char* county_name, const char* fips_code, const char* seat, int population, int area);
int delete_by_county_name(list* listPtr, const char* county_name);
const char* get_county_name(struct node* nodePtr);
const char* get_fips_code(struct node* nodePtr);
const char* get_seat(struct node* nodePtr);
int get_population(struct node* nodePtr);
int get_area(struct node* nodePtr);
double get_population_density(struct node* nodePtr);
struct node* get_next_node(struct node* nodePtr);
void load_counties(list* listPtr, const char* filename);
void save_counties(list* listPtr, const char* filename);
const char* rtrim(const char* string);
const char* substring(const char* string, int start, int end);
const char* get_programmer_name(void);

/**
 * @brief: instantiates a new list 
 * @return: new list
*/
list* create_list(void) {

	// allocating memory for new list struct
	list* new_list = malloc(sizeof(list)); 
	if (new_list == NULL) {

		puts("Could not allocate memory for new list.");
		exit(1);

	}

	// initialize head
	new_list->headPtr = NULL;


	return new_list;

}

/**
 * @brief: gets the head node of a list 
 * @param: listPtr: list to get head node for 
 * @return: head node 
*/
node* get_head_node(list* listPtr) {

	// return head pointer of given list
	return listPtr->headPtr;

}

/**
 * @brief: adds a county with its data to the correct position within a list 
 * @param listPtr: list pointer	
 * @param county_name: county name of the node that's being added
 * @param fips_code: fips code of the node that's being added 
 * @param seat: seat value of the node that's being added
 * @param population: population value of the node that's being added
 * @param area: area value of the node that's being added
*/
void add_sorted_county(list* listPtr, const char* county_name, const char* fips_code, const char* seat, int population, int area) {

	
	// allocate memory for new node 
	node* new_node = malloc(sizeof(node));
	new_node->county_name = malloc(sizeof(char[20]));
	new_node->fips_code = malloc(sizeof(char[20]));
	new_node->seat = malloc(sizeof(char[20]));

	if (new_node == NULL) {

		puts("Could not allocate memory for new node.");
		exit(1);

	}
	
	// initializing all values for new node 
	new_node->area = area;
	strncpy(new_node->county_name, county_name, 20);
	new_node->county_name[19] = '\0';
	strncpy(new_node->fips_code, fips_code, 20);
	new_node->fips_code[19] = '\0';
	strncpy(new_node->seat, seat, 20);
	new_node->seat[19] = '\0';
	new_node->population = population;
	new_node->nextPtr = NULL;
	
	// set curPtr equal to headPtr
	node* curPtr = listPtr->headPtr;

	// if list is empty
	if(listPtr->headPtr == NULL) {

		listPtr->headPtr = new_node;
		return;

	}
	else {

		// if new node should be head node 
		if(get_population_density(new_node) > get_population_density(curPtr)){

			// swap current head node with new node 
			listPtr->headPtr = new_node;
			new_node->nextPtr = curPtr;
			return;

		}
		// if list only has one node 
		else if (curPtr->nextPtr == NULL) {

			// new node belongs after head node 
			listPtr->headPtr->nextPtr = new_node;
			return;

		}

		// if there are two or more nodes within list 
		while (curPtr->nextPtr != NULL) {

			// find the proper position for new node 
			if (get_population_density(new_node) > get_population_density(curPtr->nextPtr)) {

				// swap
				new_node->nextPtr = curPtr->nextPtr;
				curPtr->nextPtr = new_node;
				return;

			}
			else {

				// iterate
				curPtr = curPtr->nextPtr;

			}

		}

		curPtr->nextPtr = new_node;
		return;
		
	}

}

/**
 * @brief: deletes the node with the corresponding county name 
 * @param listPtr: list structure that the node should be in 
 * @param county_name: county name of the desired node to delete
 * @return: 1 if unsuccessful, 0 if successful 
*/
int delete_by_county_name(list* listPtr, const char* county_name) {

	node* curPtr = listPtr->headPtr;

	// if county name is the headPtr 
	if (!strcmp(listPtr->headPtr->county_name, county_name)) {

		// 'remove' headPtr
		listPtr->headPtr = listPtr->headPtr->nextPtr;
		return 0;

	}
	else {

		// headPtr is not desired node 
		while (curPtr->nextPtr != NULL) {

			// find desired headPtr 
			if (!strcmp(curPtr->nextPtr->county_name, county_name)) {

				// 'remove' desired node 
				curPtr->nextPtr = curPtr->nextPtr->nextPtr;
				return 0;

			}

			// iterate 
			curPtr = curPtr->nextPtr;

		}

	}
	
	// unsuccessful 
	return 1;

}

/**
 * @brief: gets the county name of a specified node
 * @param nodePtr: specified node 
 * @return: return the value of the county name 
*/
const char* get_county_name(node* nodePtr) {

	return nodePtr->county_name;

}

/**
 * @brief: gets the fips code of a specified node
 * @param nodePtr: specified node
 * @return: the value of the fips code 
*/
const char* get_fips_code(node* nodePtr) {

	return nodePtr->fips_code;

}

/**
 * @brief: gets the seat of a specified node
 * @param nodePtr: specified node
 * @return: the value of the seat 
*/
const char* get_seat(node* nodePtr) {

	return nodePtr->seat;

}

/**
 * @brief: gets the population of a specified node
 * @param nodePtr: specified node
 * @return: the population value 
*/
int get_population(node* nodePtr) {

	return nodePtr->population;

}

/**
 * @brief: gets the area of a specified node
 * @param nodePtr: specified node
 * @return: the area value
*/
int get_area(node* nodePtr) {

	return nodePtr->area;

}

/**
 * @brief: gets the population density of a specified node
 * @param nodePtr: specified node
 * @return: the population density ( population / area ) 
*/
double get_population_density(node* nodePtr) {

	return (double)nodePtr->population / nodePtr->area;

}

/**
 * @brief: gets the next node of a specified node
 * @param nodePtr: specified node 
 * @return: next node pointer or NULL if one doesn't exist
*/
node* get_next_node(node* nodePtr) {

	return nodePtr->nextPtr;

}

/**
 * @brief: parses data from a specified filename ( only works with specific format ) - County_name, FIPS_code, Seat, Population, Area
 * @param listPtr: list to store the parsed data 
 * @param filename: specified file name 
*/
void load_counties(list* listPtr, const char* filename) {

	// open file 
	FILE* file = fopen(filename, "r");
	if (file == NULL) {

		puts("Could not read file.");
		exit(1);

	}

	// allocate space for header values 
	char junk[80];
	fgets(junk, 80, file);

	// I couldn't figure out a better way to handle blank rows at the end of the file so I am manually skipping them
	int i = 0;
	// iterate until end of file or all valid counties have been loaded 
	while (!feof(file) && i < 55) {

		// allocate memory for all values 
		char* county_name = malloc(sizeof(char) * 20);
		char* fips_code = malloc(sizeof(char) * 20);
		char* seat = malloc(sizeof(char) * 20);
		char* population = malloc(sizeof(char) * 20);
		char* area = malloc(sizeof(char) * 20);

		// get county name and trim the value 
		fgets(county_name, 17, file);
		strcpy(county_name, rtrim(county_name));

		// get fips_code and trim the value 
		fgets(fips_code, 12, file);
		strcpy(fips_code, rtrim(fips_code));

		// get seat and trim the value 
		fgets(seat, 22, file);
		strcpy(seat, rtrim(seat));

		// get population and trim the value 
		fgets(population, 13, file);
		strcpy(population, rtrim(population));

		// get area and trim the value 
		fgets(area, 10, file);
		strcpy(area, rtrim(area));

		// add each value into a node 
		add_sorted_county(listPtr, county_name, fips_code, seat, atoi(population), atoi(area));
		i++;
	}
	// close file 
	fclose(file);
}

/**
 * @brief: saves list of sorted data into a csv file
 * @param listPtr: list with sorted data
 * @param filename: file to store the data
*/
void save_counties(list* listPtr, const char* filename) {
	
	// open file for writing 
	FILE* write_file = fopen(filename, "w");
	if (write_file == NULL) {

		puts("Could not open file");
		exit(1);

	}

	// putting header values into the file 
	fputs("County Name, FIPS code, Seat, Population, Area, Population Density\n", write_file);

	node* curPtr = listPtr->headPtr;

	
	// loop until there are no more nodes 
	while (curPtr != NULL) {

		int pop = get_population(curPtr);
		int area = get_area(curPtr);
		double pop_den = get_population_density(curPtr);
		
		// write values to file 
		fprintf(write_file, "%s, %s, %s, %d, %d, %.2f\n", get_county_name(curPtr), get_fips_code(curPtr), get_seat(curPtr), get_population(curPtr), get_area(curPtr), get_population_density(curPtr));

		// iterate 
		curPtr = curPtr->nextPtr;
	}
}

/**
 * @brief: trims an array of chars of white space
 * @param string: array of chars
 * @return: trimmed array
*/
const char* rtrim(const char* string) {

	// Create new array large enough to handle string + null terminator
	char* strippedPtr = malloc((strlen(string) + 1) * sizeof(char));
	if (strippedPtr == NULL)
	{
		puts("Could not allocate memory for string.");
		exit(1);
	}

	// Null terminate new array
	memset(strippedPtr, 0, strlen(string) + 1);

	// Copy existing string into new array
	strncpy(strippedPtr, string, strlen(string));

	// Loop over string, start at end, to strip whitespace
	size_t position = strlen(string) - 1;
	while ((position >= 0) && isspace(strippedPtr[position]))
	{
		// Set char to null terminator
		strippedPtr[position] = '\0';

		// Advance one position to left
		position--;
	}

	return strippedPtr;

}

/**
 * @brief: takes a large string and returns a subset of that string
 * @param string: larger string
 * @param start: index of where the substring should begin
 * @param end: index of where the substring should end
 * @return: substring 
*/
const char* substring(const char* string, int start, int end) {

	// Get length of substring
	int strlen = end - start;

	// Allocate enough memory for substring
	char* substringPtr = malloc((strlen + 1) * sizeof(char));
	if (substringPtr == NULL)
	{
		puts("Could not allocate memory for string.");
		exit(1);
	}

	// Initialize new substring to null terminators
	memset(substringPtr, 0, strlen + 1);

	// Copy substring
	strncpy(substringPtr, string + start, strlen);

	return substringPtr;
}

/**
 * @return: programmer's name 
*/
const char* get_programmer_name(void) {

	return "Logan Whitehair";

}
