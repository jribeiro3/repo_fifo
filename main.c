
/**
 * @file main.c
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
*/

#include <stdio.h>//to use printf, scanf
#include <stdlib.h>//to use malloc
#include <errno.h>//to use system error numbers (EPERM, EINVAL, ESRCH, ENOSPC, (...))
#include <assert.h>//to use asserts

#include "fifo.h"

int menuOption, c;//local variables declaration

/**********************************************************/
static void printMenu()
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

/**********************************************************/
static void readMenuOption()
	{
	menuOption = -1;
	do
		{
		printf("Option: ");
		scanf("%d", &menuOption);

		//flushes the stdin
		while(((c = getchar()) != '\n') && (c != EOF));

		if((menuOption < 0) || (menuOption > 6)) printf("  Invalid value!\n");
		}
	while((menuOption < 0) || (menuOption > 6));
	//printf("Selected: %d\n", menuOption);
	}
/**********************************************************/

int main()
	{
	printMenu();
	while(true)
		{
		//printMenu();
		readMenuOption();//read the input of the menu option

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
				FIFO_init(&fifo);//initialization of the FIFO
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
				FIFO_insert(&fifo);
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
		}
	return(0);
	}
