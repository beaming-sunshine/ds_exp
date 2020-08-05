#ifndef  STACK_H
#define STACK_H

#include<iostream>

class stack{

public:
	char *str_arr;
	int stacksize=0;

public:
	stack();             
	~stack();
	void push(char e);
	char getTop();
	char pop();
	int stack_size();
	int isEmpty();
};


#endif
