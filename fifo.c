
/**
 * @file fifo.c
 * @brief A simple FIFO, used as a circular array, whose elements are integers
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
*/

#include <stdio.h>//to use printf, scanf, sizeof
#include <stdlib.h>//to use malloc
#include <stddef.h>//to use sizeof
#include <errno.h>//to use system error numbers (EPERM, EINVAL, ESRCH, ENOSPC, (...))
#include <assert.h>//to use asserts

#include "fifo.h"

/**********************************************************/
void FIFO_init(FIFO* fifo, int size)//initialize the FIFO
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return;
		}

	if(size <= 0)
		{
		printf("  Error: Invalid value! Must be bigger than 0!!!\n");
		return;
		}

	fifo->array = (int*)malloc(size * sizeof(int));//memory allocation of the FIFO array

	//update of the FIFO metadata
	fifo->size = size;//size of the FIFO
	fifo->counter=0;//number of elements in the FIFO
	fifo->head = 0;//points to the 1st element of the FIFO
	fifo->tail = 0;//check
	fifo->priority = 1;//(default) priority of the FIFO
	}
/**********************************************************/

/**********************************************************/
int FIFO_usage(FIFO* fifo)//return the number of elements in the FIFO's array
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);
		}

	if(!FIFO_checkInit(fifo))//check the FIFO's initialization
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(0);
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  Error: FIFO empty!!!\n");
		return(0);
		}

	//FIFO's usage
	printf("  FIFO's usage: %d/%d\n", fifo->counter, fifo->size);
	return(fifo->counter);
	}
/**********************************************************/

/**********************************************************/
void FIFO_print(FIFO* fifo)
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return;
		}

	if(!FIFO_checkInit(fifo))//check the FIFO's initialization
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return;
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  Error: FIFO empty!!!\n");
		return;
		}

	//print the FIFO's array
	int cnt = fifo->counter;
	int idx = fifo->head;
	while(cnt > 0)
		{
		printf("Value %d: %d\n", (fifo->counter - cnt + 1), fifo->array[idx]);
		idx = (idx + 1) % fifo->size;//circular way
		cnt--;
		}
	}
/**********************************************************/

/**********************************************************/
void FIFO_insert(FIFO* fifo, int value)//insert an element
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return;
		}

	if(!FIFO_checkInit(fifo))//check the FIFO's initialization
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return;
		}

	//if(FIFO_isFull(fifo))//check if the FIFO is full
	if(fifo->counter == fifo->size)//check if the FIFO is full
		{
		printf("  Error: FIFO full!!!\n");
		return;
		}

	//insertion of an element
	fifo->array[fifo->tail] = value;//insert a new element into FIFO's array
	fifo->counter++;//update the number of elements stored at the FIFO's array
	fifo->tail = (fifo->tail + 1) % fifo->size;//the FIFO is used as a circular array
	}
/**********************************************************/

/**********************************************************/
int FIFO_peak(FIFO* fifo)//return the head (oldest) element, without removal
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);
		}

	if(!FIFO_checkInit(fifo))//check the FIFO's initialization
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(0);
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  Error: FIFO empty!!!\n");
		return(0);
		}

	//FIFO's head (oldest) element
	printf("  Peaked element: %d\n", fifo->array[fifo->head]);
	return(fifo->array[fifo->head]);
	}
/**********************************************************/

/**********************************************************/
int FIFO_removeHead(FIFO* fifo)//remove the head (oldest) element
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);
		}

	if(!FIFO_checkInit(fifo))//check the FIFO's initialization
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(0);
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  Error: FIFO empty!!!\n");
		return(0);
		}

	//removal of the FIFO's head (oldest) element
	int element = fifo->array[fifo->head];//remove the head (oldest) element of the FIFO
	fifo->head = (fifo->head + 1) % fifo->size;//update the head in a circular way
	fifo->counter--;//update the number of elements in the FIFO's array
	printf("  Removed element: %d\n", element);
	return(element);
	}
/**********************************************************/

/**********************************************************/
int FIFO_isFull(FIFO* fifo)//return 1 if full, -1 if error, 0 otherwise
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(-1);
		}

	if(!FIFO_checkInit(fifo))//check the FIFO's initialization
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(-1);
		}

	if(fifo->counter == fifo->size)//check if the FIFO is full
		{
		return(1);//full
		}
	return(0);//not full
	}
/**********************************************************/

/**********************************************************/
int FIFO_isEmpty(FIFO* fifo)//return 1 if empty, -1 if error, 0 otherwise
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(-1);
		}

	if(!FIFO_checkInit(fifo))//check the FIFO's initialization
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(-1);
		}

	if(fifo->counter == 0)//check if the FIFO is empty
		{
		return(1);//empty
		}
	return(0);//not empty
	}
/**********************************************************/

/**********************************************************/
int FIFO_checkStatus(FIFO* fifo)//check the FIFO's status
	{
	if(fifo == NULL)//check the pointer of the FIFO structure
		{
		//printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);
		}

	//printf("  FIFO pointer exists!!!\n");
	return(1);
	}
/**********************************************************/

/**********************************************************/
int FIFO_checkInit(FIFO* fifo)
	{
	if(!FIFO_checkStatus(fifo))//check the FIFO's status
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);
		}

	if(fifo->size <= 0)//check the FIFO's initialization
		{
		//printf("  Error: FIFO yet to be initialized!!!\n");
		return(0);
		}

	//printf("  FIFO already initialized!!!\n");
	return(1);
	}
/**********************************************************/

/**********************************************************/
void FIFO_removeTail(FIFO* fifo)//removes the tail (newest) element
	{
	}
/**********************************************************/

/**********************************************************/
int FIFO_search(FIFO* fifo, int target)//searches for an element, without removal
	{
	return(0);
	}
/**********************************************************/
