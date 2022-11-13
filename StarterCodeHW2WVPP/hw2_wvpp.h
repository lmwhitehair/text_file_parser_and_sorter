/**
 * @file hw2_wvpp.h
 * @brief Header file for CS 350 Homework #2: West Virginia Population Problem
 * @author Brian Powell
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

#pragma once

/**
 * @brief Struct for a linked list
*/
typedef struct list {
	/**
	 * @brief Pointer to head node of linked list
	*/
	struct node* headPtr;
} list;

/**
 * @brief Creates a new linked list
 * @return Pointer to new list
*/
list* create_list(void);

/**
 * @brief Get the head node for a linked list
 * @param counties_listPtr Linked list to get head node for
 * @return Head node for linked list, or NULL if list is empty
*/
struct node* get_head_node(list* listPtr);

/**
 * @brief Add new county to list, leaving list sorted in descending order by population density
 * @param listPtr Linked list to add county to
 * @param county_name Name of county
 * @param fips_code FIPS Code
 * @param seat Seat of county
 * @param population Population of county
 * @param area Area of county in square miles
*/
void add_sorted_county(list* listPtr, const char* county_name, const char* fips_code, const char* seat, int population, int area);

/**
 * @brief Delete node from list by its county name
 * @param listPtr Linked lst to delete from
 * @param county_name Name of county for node to be deleted
 * @return 0 if successfully deleted, 1 if node did not exist
*/
int delete_by_county_name(list* listPtr, const char* county_name);

/**
 * @brief Get county name from specified node
 * @param nodePtr Node to get county name from
 * @return Name of county
*/
const char* get_county_name(struct node* nodePtr);

/**
 * @brief Get FIPS Code from specified node
 * @param nodePtr Node to get FIPS Code from
 * @return FIPS Code
*/
const char* get_fips_code(struct node* nodePtr);

/**
 * @brief Get seat from specified node
 * @param nodePtr Node to get seat from
 * @return Seat
*/
const char* get_seat(struct node* nodePtr);

/**
 * @brief Get population from specified node
 * @param nodePtr Node to get population from
 * @return Population
*/
int get_population(struct node* nodePtr);

/**
 * @brief Get area from specified node
 * @param nodePtr Node to get area from
 * @return Area
*/
int get_area(struct node* nodePtr);

/**
 * @brief Get populationd density (population/area) for specified node
 * @param nodePtr Node to get population density for
 * @return Number of people per square mile
*/
double get_population_density(struct node* nodePtr);

/**
 * @brief Get next node for specified node
 * @param nodePtr Node to get next node for
 * @return Next node, or NULL if there are no more nodes in the linked list
*/
struct node* get_next_node(struct node* nodePtr);

/**
 * @brief Load counties from file, storing them each as nodes in linked list
 * @param listPtr Linked list to store counties in as nodes
 * @param filename name of fixed-width column text file to load counties from
*/
void load_counties(list* listPtr, const char* filename);

/**
 * @brief Save counties from linked list to CSV file
 * @param listPtr linked list containing counties to be saved
 * @param filename CSV file to save counties in
*/
void save_counties(list* listPtr, const char* filename);

/**
 * @brief Removes whitespace from the trailing end of a string
 * @param string String to remove whitespace from
 * @return String with trailing whitespace removed
 */
const char* rtrim(const char* string);

/**
 * @brief Returns substring of original string
 * @param string String to take substring from
 * @param start Starting index for substring (included in result)
 * @param end Ending index for substring (excluded from result)
 * @return Substring
 */
const char* substring(const char* string, int start, int end);

/**
 * @brief Get name of programmer
 * @return String with the name of the programmer.
 */
const char* get_programmer_name(void);