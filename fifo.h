
/**
 * @file fifo.h
 * @brief Module that implements a FIFO data structure,
 * used as a circular array, whose elements are integers
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
*/

#ifndef __FIFO_GROUP_
#define __FIFO_GROUP_

/**********************************************************/
/* The information support data structure */

/**
 * @brief The struct representing a FIFO
 */
typedef struct
	{
	int size;//size of the FIFO
	int counter;//number of elements of the FIFO
	int head;//index of the FIFO's head
	int tail;//index of the FIFO's tail
	int priority;
	int* array;//elements stores at the FIFO
	} FIFO;
/**********************************************************/

/**********************************************************/
/**
 * @brief Initializes the FIFO
 *
 * @param fifo Pointer to the FIFO to be initialized
 * @param size Size of the FIFO
*/
void FIFO_init(FIFO* fifo, int size);
/**********************************************************/

/**********************************************************/
/**
 * @brief Returns the number of elements in the FIFO's array
 * 
 * @param fifo Pointer to the FIFO
 * @return Return number of elements in the FIFO's array, 0 otherwise
*/
int FIFO_usage(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Prints the current elements of the FifO
 * 
 * @param fifo Pointer to the FIFO
*/
void FIFO_print(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Inserts a new element into the FIFO
 *
 * @param fifo Pointer to the FIFO
 * @param value Item to be inserted
*/
void FIFO_insert(FIFO* fifo, int value);
/**********************************************************/

/**********************************************************/
/**
 * @brief Returns the head (oldest) element of the FIFO, without removal
 *
 * @param fifo Pointer to the FIFO
 * @return The element returned, 0 otherwise (FIFO is empty)
*/
int FIFO_peak(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Removes an element from the FIFO
 * 
 * @details Removes the head (oldest) element
 * 
 * @param fifo Pointer to the FIFO
 * @return The element removed, 0 otherwise (FIFO is empty)
*/
int FIFO_removeHead(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Checks if the FIFO is full
 * 
 * @param fifo Pointer to the FIFO
 * @return Return 1 if full, -1 if error, 0 otherwise
*/
int FIFO_isFull(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Checks if the FIFO is empty
 * 
 * @param fifo Pointer to the FIFO
 * @return Return 1 if empty, -1 if error, 0 otherwise
*/
int FIFO_isEmpty(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Displays the status of the FIFO
 * 
 * @param fifo Pointer to the FIFO
 * @return Return 1 if OK, 0 otherwise
*/
int FIFO_checkStatus(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Displays the status of the initialization of the FIFO
 * 
 * @param fifo Pointer to the FIFO
 * @return Return 1 if initialized, 0 otherwise
*/
int FIFO_checkInit(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Removes the tail (newest) element of the FIFO
 * 
 * @param fifo Pointer to the FIFO
 * @return The element removed, 0 otherwise (FIFO is empty)
*/
void FIFO_removeTail(FIFO* fifo);
/**********************************************************/

/**********************************************************/
/**
 * @brief Searches for a target element on the FIFO, without removal
 * 
 * @param fifo Pointer to the FIFO
 * @param [in] target The target element of the FIFO to be found
 * @return Return 1 if found, otherwise 0
*/
int FIFO_search(FIFO* fifo, int target);
/**********************************************************/

#endif /* __FIFO_GROUP_ */
