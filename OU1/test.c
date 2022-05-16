#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void axiom_1(void);
void axiom_2(void);
/*
void axiom_3(int *temp);
void axiom_4(int *temp);
void axiom_5(int *temp);
*/
int main(void)
{
	int *temp = malloc(sizeof(*temp));	//allocate memory for value.
    axiom_1();
	axiom_2();
	/*
    axiom_3(temp);
	axiom_4(temp);
    axiom_5(temp);
	*/
	
	return 0;
}

void axiom_1(void)
{
    /* Axiom 1*/
	fprintf(stdout, "TEST: Axiom 1\n");

	stack *s = stack_empty(NULL); 		//create an empty stack. 
	                                    //checks if stack is emptied.
    if (stack_is_empty(s) == true)
	{
		fprintf(stdout, "SUCCESS: Stack is empty\n");
        free(s);
	}
	else
	{
		fprintf(stderr, "FAIL: Expected stack to be empty.\n");
		stack_kill(s);
		fprintf(stderr, "\nFAIL: Implementation did not passed all tests. Force exit.\n");
        free(s);
		exit(0);
	}    


	fprintf(stdout, "Axiom 1 test successful\n\n");


}

void axiom_2(void)
{   
    stack *s = stack_empty(NULL); 		//create an empty stack. 
	int *temp = malloc(sizeof(*temp));
	*temp = 3;

	s = stack_push(s, temp);

	if (stack_is_empty(s) == true)
	{
		
	}
	
	

}
/*
void axiom_3(int *temp)
{

}

void axiom_4(int *temp)
{
	
}

void axiom_5(int *temp)
{
	
}
*/