#ifndef SUFFIX_H
#define SUFFIX_H

#include<iostream>

class suffix {


public:
	int evaluation(char suffix[]);
	char* transform(char str_arr[]);
	int OpMember(char ch);
	char Operate(char a, char ch, char b);
	int precede(char a, char b);
	int getPrioraty(char e);
};


#endif