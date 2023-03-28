
//******************************************************************************
/**
 * @file fifo.c
 * @brief A simple FIFO, used as a circular array, whose elements are integers
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
*/
//******************************************************************************

#include <stdio.h>//to use printf, scanf, getchar
#include <stdlib.h>//to use malloc
#include <errno.h>//to use system error numbers (EPERM, EINVAL, ESRCH, ENOSPC, (...))
//#include <assert.h>//to use asserts

#include "fifo.h"

//------------------------------------------------------------------------------
void FIFO_init(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return;//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 1)
		{
		printf("  FIFO already initialized!!!\n");
		return;//error
		}

	//read the input of the FIFO's size
	int size, c;
	do
		{
		printf("  FIFO size (>0): ");
		scanf("%d", &size);//read the input number

		//flushes the stdin
		while(((c = getchar()) != '\n') && (c != EOF));

		//invalid input size
		if(size <= 0) printf("	Invalid size!\n");
		}
	while(size <= 0);

	fifo->array = (int*)malloc(size * sizeof(int));//memory allocation of the FIFO array

	//update of the FIFO metadata
	fifo->size = size;//size of the FIFO
	fifo->counter=0;//number of elements in the FIFO
	fifo->head = 0;//points to the 1st element of the FIFO
	fifo->tail = 0;//check
	fifo->priority = 1;//(default) priority of the FIFO
	printf("  Done!\n");

	//check the FIFO's initialization
	if(!FIFO_checkInit(fifo)) printf("	Error: FIFO yet to be initialized!!!\n");
	printf("  Empty: %d\n", FIFO_isEmpty(fifo));//verification
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_usage(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 0)
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(0);//error
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  FIFO empty!!!\n");
		return(0);//error
		}

	//FIFO's usage
	printf("  FIFO's usage: %d/%d\n", fifo->counter, fifo->size);
	return(fifo->counter);//return the number of elements in the FIFO's array
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void FIFO_print(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return;//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 0)
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return;//error
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  FIFO empty!!!\n");
		return;//error
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
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void FIFO_insert(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return;//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 0)
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return;//error
		}

	//if(FIFO_isFull(fifo))//check if the FIFO is full
	if(fifo->counter == fifo->size)//check if the FIFO is full
		{
		printf("  Error: FIFO full!!!\n");
		return;//error
		}

	int value, c;
	//read the input of the FIFO's size
	printf("  element: ");
	scanf("%d", &value);//error -> allowing letters and chars

	//flushes the stdin
	while(((c = getchar()) != '\n') && (c != EOF));

	//insertion of an element
	fifo->array[fifo->tail] = value;//insert a new element into FIFO's array
	fifo->counter++;//update the number of elements stored at the FIFO's array
	fifo->tail = (fifo->tail + 1) % fifo->size;//the FIFO is used as a circular array
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_peak(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 0)
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(0);//error
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  FIFO empty!!!\n");
		return(0);//error
		}

	//FIFO's head (oldest) element
	printf("  Peaked element: %d\n", fifo->array[fifo->head]);
	return(fifo->array[fifo->head]);
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_removeHead(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(0);//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 0)
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(0);//error
		}

	//if(FIFO_isEmpty(fifo))//check if the FIFO is empty
	if(fifo->counter == 0)//check if the FIFO is empty
		{
		printf("  FIFO empty!!!\n");
		return(0);//error
		}

	//removal of the FIFO's head (oldest) element
	int element = fifo->array[fifo->head];//remove the head (oldest) element of the FIFO
	fifo->head = (fifo->head + 1) % fifo->size;//update the head in a circular way
	fifo->counter--;//update the number of elements in the FIFO's array
	printf("  Removed element: %d\n", element);
	return(element);
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_isFull(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(-1);//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 0)
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(-1);//error
		}

	//check if the FIFO is full
	if(fifo->counter == fifo->size) return(1);//full
	return(0);//not full
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_isEmpty(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo))
		{
		printf("  Error: FIFO pointer is NULL!!!\n");
		return(-1);//error
		}

	//check the FIFO's initialization
	if(FIFO_checkInit(fifo) == 0)
		{
		printf("  Error: FIFO yet to be initialized!!!\n");
		return(-1);//error
		}

	//check if the FIFO is empty
	if(fifo->counter == 0) return(1);//empty
	return(0);//not empty
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_checkStatus(FIFO* fifo)
	{
	//check the pointer of the FIFO structure
	if(fifo == NULL) return(0);//error: FIFO pointer is NULL
	return(1);//FIFO pointer exists
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_checkInit(FIFO* fifo)
	{
	//check the FIFO's status
	if(!FIFO_checkStatus(fifo)) return(-1);//error: FIFO pointer is NULL

	//check the FIFO's initialization
	if(fifo->size <= 0) return(0);//error: FIFO not initialized
	return(1);//FIFO already initialized
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void FIFO_removeTail(FIFO* fifo)
	{
	//removes the tail (newest) element
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
int FIFO_search(FIFO* fifo, int target)//searches for an element, without removal
	{
	return(0);
	}
//------------------------------------------------------------------------------
