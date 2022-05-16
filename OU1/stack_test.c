/*
 * Datastrukturer och algoritmer (c).
 * Spring 21
 * OU1
 * Version:		 3.0
 * File:         stack_test.c
 * Description:  A simple test program for the implementation of a stack. 
 * Author:       Jaffar El-Tai
 * CS username:  hed20jel
 * Date:         21-02-
 * Input:        N/A
 * Output:       Prints out each test and if it was successful or not.
 * Limitations:  The test program may only use operations on the interface.
 * 
 *				 The test program must not use knowledge of how the data type 
 * 				 is implemented.	
 * 
 *	 			 The tests in the program should be divided into functions that
 *				 each test a new thing. 

 * 				 The test must not generate stacks deeper than 10 elements.	
 * 				
 * 				 The program must not go into an infinite loop. 
 * 
 * 				 The test program must be able to run without input from the 
 * 				 user.
 * 
 * 				 The test program should not make any prints that make it 
 * 				 difficult for the user to see which tests have succeeded or 
 * 				 failed.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* Declaration of functions */
void axiom_1(void);
void axiom_2(void);
void axiom_3(void);
void axiom_4(void);
void axiom_5(void);
void additional_test(void);

/* Description: The sequence of tests that will test a stack.
 * Input:       N/A.
 * Output:      Prints out each test and if it was successful or not.
 */
int main(void)
{
    axiom_1();
	axiom_2();
    axiom_3();
	axiom_4();
    axiom_5();
	additional_test();

	fprintf(stdout, "SUCCESS: Implementation passed all tests. Normal exit.\n");

	return 0;
}

/* Description:	Tests the first axiom. "A newly made stack is empty" 
 * Input:		N/A.        
 * Output:      Prints out if the test was successful or not. 
 */
void axiom_1(void)
{
	fprintf(stdout, "TEST: Axiom 1\n");
	stack *s = stack_empty(NULL); 		//create an empty stack. 
	//checks if the stack is empty or not.
    if (stack_is_empty(s) == true)
	{
		fprintf(stdout, "SUCCESS: Stack is empty\n");
		fprintf(stdout, "Axiom 1 test successful\n\n");
	}
	else
	{
		fprintf(stderr, "FAIL: Expected stack to be empty.\n");
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
		stack_kill(s);
		exit(EXIT_FAILURE);
	}
	//clear all allocations.    
	stack_kill(s);
}

/* Description:	Tests the second axiom. "A stack on which an element has
				been placed is not empty." 
 * Input:		N/A.        
 * Output:      Prints out if the test was successful or not. 
 */
void axiom_2(void)
{   
	fprintf(stdout, "TEST: Axiom 2\n");
    stack *s = stack_empty(NULL); 		//create an empty stack. 
	int *temp = malloc(sizeof(*temp));	//allocated memory to varieble.
	*temp = 3;

	s = stack_push(s, temp);			//pushes value to stack.
	//tests if stack is empty or not.
	if (stack_is_empty(s) == true)
	{
		fprintf(stderr, "FAIL: Expected stack to not be empty.\n");
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
		free(temp);
		stack_kill(s);
		exit(EXIT_FAILURE);
	}
	else
	{	
		fprintf(stdout, "SUCCESS: Stack is not empty\n");
		fprintf(stdout, "Axiom 2 test successful\n\n");
	}
	//clear all allocations.
	free(temp);
	stack_kill(s);
}

/* Description:	Tests the third axiom. "If you put a value on the stack
 				and delete that value, the stack looks like before." 
 * Input:		N/A.        
 * Output:      Prints out if the test was successful or not. 
 */
void axiom_3(void)
{	
	fprintf(stdout, "TEST: Axiom 3\n");
	stack *s = stack_empty(NULL); 		//create an empty stack. 
	int *temp = malloc(sizeof(*temp));	//allocate memory for value.
	int *temp2 = malloc(sizeof(*temp2));	//allocate memory for value.
	*temp = 3;
	*temp2 = 4;

	s = stack_push(s, temp);			//pushes value to stack.
	s = stack_push(s, temp2);			//pushes value to stack.

	if (*(int*)stack_top(s) == *temp2)
	{
		s = stack_pop(s);				//pops value from stack.
	}
	else
	{
		fprintf(stderr, "FAIL: Expected stack to be empty.\n");
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
		free(temp);
		free(temp2);
		stack_kill(s);
		exit(EXIT_FAILURE);
	}
	
	if (*(int*)stack_top(s) == *temp)
	{
		s = stack_pop(s);

		if (stack_is_empty(s) == true)
		{
			fprintf(stdout, "SUCCESS: Stack looks the same\n");
			fprintf(stdout, "Axiom 3 test successful\n\n");
		}
		else
		{
			fprintf(stderr, "FAIL: Expected stack to be empty.\n");
			fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
			free(temp);
			free(temp2);
			stack_kill(s);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "FAIL: Expected stack to be empty.\n");
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
		free(temp);
		free(temp2);
		stack_kill(s);
		exit(EXIT_FAILURE);
	}
	//clear all allocations.	
	free(temp2);
	free(temp);
	stack_kill(s);
}

/* Description:	Tests the fourth axiom. " If we put a value in the stack,
 				they are at the top of the stack." 
 * Input:		N/A.        
 * Output:      Prints out if the test was successful or not. 
 */
void axiom_4(void)
{
	fprintf(stdout, "TEST: Axiom 4\n");
	stack *s = stack_empty(NULL); 			//create an empty stack. 
	int *temp = malloc(sizeof(*temp));		//allocate memory for value.
	int *temp2 = malloc(sizeof(*temp2));	//allocate memory for value.
	*temp = 3;
	*temp2 = 4;

	s = stack_push(s, temp2);				//pushes value to stack.	
	s = stack_push(s, temp);				//pushes value to stack.
	
	//checks the top value and compares.
	if (*(int *)stack_top(s) != *temp)
	{
		fprintf(stderr, "FAIL: Newset element that was pushed was not at the top.\n");
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
		free(temp);
		free(temp2);
		stack_kill(s);
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(stdout, "SUCCESS: Newset element was at the top\n");
		fprintf(stdout, "Axiom 4 test successful\n\n");

	}
	//clear all allocations.
	free(temp);
	free(temp2);
	stack_kill(s);
}

/* Description:	Tests the fifth axiom. " Provided the stack is not empty. 
				If you remove the top element and then put it back, 
				the stack looks like before" 
 * Input:		N/A.        
 * Output:      Prints out if the test was successful or not. 
 */
void axiom_5(void)
{
	fprintf(stdout, "TEST: Axiom 5\n");
	stack *s = stack_empty(NULL); 			//create an empty stack. 
	int *temp = malloc(sizeof(*temp));		//allocate memory for value.
	int *temp2 = malloc(sizeof(*temp2));	//allocate memory for value.
	int *temp3 = malloc(sizeof(*temp3));	//allocate memory for value.
	*temp = 3;
	*temp2 = 4;
	*temp3 = 5;

	s = stack_push(s, temp);				//pushes value to stack.
	s = stack_push(s, temp2);				//pushes value to stack.
	s = stack_push(s, temp3);				//pushes value to stack.
	
	if (stack_is_empty(s) == false)
	{
		if (*(int*)stack_top(s) == *temp3)
		{
			s = stack_pop(s);						//pops value from stack.
			if (*(int*)stack_top(s) == *temp2)
			{
				s = stack_push(s, temp3);				//pushes value to stack.
				//checks top value and compares.
				if (*(int*)stack_top(s) == *temp3)
				{
					fprintf(stdout, "SUCCESS: Same element at the top\n");
					fprintf(stdout, "Axiom 5 test successful\n\n");
				}
				else
				{
					fprintf(stderr, "FAIL: Stack does not look the same.\n");
					fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
					free(temp);
					free(temp2);
					free(temp3);
					stack_kill(s);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
				free(temp);
				free(temp2);
				free(temp3);
				stack_kill(s);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
			free(temp);
			free(temp2);
			free(temp3);
			stack_kill(s);
			exit(EXIT_FAILURE);
		}	
	}
	else
	{
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
		free(temp);
		free(temp2);
		free(temp3);
		stack_kill(s);
		exit(EXIT_FAILURE);
	}
	
	
	
	//clear all allocations.
	free(temp);
	free(temp2);
	free(temp3);
	stack_kill(s);
}

/* Description:	Some additional tests for pop and push. 
 * Input:		N/A.        
 * Output:      Prints out if the test was successful or not. 
 */
void additional_test(void)
{
	fprintf(stdout, "TEST: additional test\n");
	stack *s = stack_empty(NULL); 			//create an empty stack. 
	int *temp = malloc(sizeof(*temp));		//allocate memory for value.
	int *temp2 = malloc(sizeof(*temp));		//allocate memory for value.
	int *temp3 = malloc(sizeof(*temp));		//allocate memory for value.

	*temp = 3;
	*temp2 = 5;
	*temp3 = 6;

	s = stack_push(s, temp);			//pushes value to stack.

	if (*(int*)stack_top(s) == *temp)
	{
		s = stack_pop(s);				//pops value from stack.
		s = stack_push(s, temp2);		//pushes value to stack.
		s = stack_push(s, temp3);		//pushes value to stack.
		
		if (*(int*)stack_top(s) == *temp3)
		{
			s = stack_pop(s);			//pops value from stack.
			if (*(int*)stack_top(s) == *temp2)
			{
				s = stack_pop(s);		//pops value from stack.

				//checks if last pop was succsesfull.
				if (stack_is_empty(s) == true)
				{
					fprintf(stdout,"SUCCESS: Stack is empty!\n");
				}
				else
				{
					fprintf(stderr, "FAIL: Stack is not empty.\n");
					fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
					free(temp);
					free(temp2);
					free(temp3);
					stack_kill(s);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				fprintf(stderr, "FAIL: wrong top value.\n");
				fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
				free(temp);
				free(temp2);
				free(temp3);
				stack_kill(s);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			fprintf(stderr, "FAIL: wrong top value.\n");
			fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
			free(temp);
			free(temp2);
			free(temp3);
			stack_kill(s);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "FAIL: stack expeceted to be empty.\n");
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
		free(temp);
		free(temp2);
		free(temp3);
		stack_kill(s);
		exit(EXIT_FAILURE);
	}
	

	//clear all allocations.
	free(temp);
	free(temp2);
	free(temp3);
	stack_kill(s);
}