
/**
 * @file main.c
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
static void printMenu()//why static???
	{
	printf("+===============================================+\n"
		   "|            Manipulation functions             |\n"
		   "+===============================================+\n"
		   "| 1: Initialization of FIFO                     |\n"
		   "| 2: Check FIFO usage                           |\n"
		   "| 3: Print FIFO                                 |\n"
		   "| 4: Insert new element in FIFO                 |\n"
		   "| 5: Peak tail (newest) element of the FIFO     |\n"
		   "| 6: Remove head (oldest) element from FIFO     |\n"
		   "| 0: Quit                                       |\n"
		   "+===============================================+\n\n");
	}
/**********************************************************/

int main()
	{
	int c, value;
	int menuOption = -1;
	//assert(menuOption == -1);

	printMenu();
	while(true)
		{
		//printMenu();

		//read the input of the menu option
		do
			{
			printf("Option: ");
			scanf("%d", &menuOption);

			while(((c = getchar()) != '\n') && (c != EOF))//flushes the stdin
				{
				}

			if((menuOption < 0) || (menuOption > 6))
				{
				printf("  Invalid value!\n");
				}
			}
		while((menuOption < 0) || (menuOption > 6));
		//printf("Value: %d\n", menuOption);

		switch(menuOption)
			{
			/******************************************************************/
			case(0)://Exit
				printf("  Exit!!!\n");
				return(0);
			/******************************************************************/
			case(1)://FIFO initialization
				printf("  ->FIFO initialization\n");
				FIFO fifo;//declaration of the FIFO

				if(!FIFO_checkStatus(&fifo))//check the FIFO's status
					{
					printf("  Error: FIFO pointer is NULL!!!\n");
					return(0);
					}

				if(FIFO_checkInit(&fifo))//check the FIFO's initialization
					{
					printf("  FIFO already initialized!!!\n");
					break;
					}

				//read the input of the FIFO's size
				do
					{
					printf("  FIFO size (>0): ");
					scanf("%d", &value);

					while(((c = getchar()) != '\n') && (c != EOF))//flushes the stdin
						{
						}

					if(value <= 0)
						{
						printf("  Invalid value!\n");
						}
					}
				while(value <= 0);

				FIFO_init(&fifo, value);//initialization of the FIFO
				printf("  Done!\n");
				printf("  Empty: %d\n", FIFO_isEmpty(&fifo));//verification

				if(!FIFO_checkInit(&fifo))//check the FIFO's initialization
					{
					printf("  Error: FIFO yet to be initialized!!!\n");
					}

				break;
			/******************************************************************/
			case(2)://print the FIFO's usage
				printf("  ->FIFO usage\n");
				FIFO_usage(&fifo);
				break;
			/******************************************************************/
			case(3)://print the FIFO's array
				printf("  ->FIFO print\n");
				FIFO_print(&fifo);
				break;
			/******************************************************************/
			case(4)://FIFO insert
				printf("  ->FIFO insert\n");

				if(!FIFO_checkStatus(&fifo))//check the FIFO's status
					{
					printf("  Error: FIFO pointer is NULL!!!\n");
					return(0);
					}

				if(!FIFO_checkInit(&fifo))//check the FIFO's initialization
					{
					printf("  Error: FIFO yet to be initialized!!!\n");
					break;
					}

				if(FIFO_isFull(&fifo))//check if the FIFO is full
					{
					printf("  Error: FIFO full!!!\n");
					break;
					}

				//read the input of the FIFO's size
				printf("  element: ");
				scanf("%d", &value);//error -> allowing letters and chars

				while(((c = getchar()) != '\n') && (c != EOF))//flushes the stdin
					{
					}

				FIFO_insert(&fifo, value);
				break;
			/******************************************************************/
			case(5)://FIFO peak
				printf("  ->FIFO peak\n");
				FIFO_peak(&fifo);
				break;
			/******************************************************************/
			case(6)://FIFO remove head
				printf("  ->FIFO remove\n");
				FIFO_removeHead(&fifo);
				break;
			/******************************************************************/
			default:
				break;
			/******************************************************************/
			}
		menuOption = -1;//resets the menuOption
		//printf("\n");
		}

	return(0);
	}
