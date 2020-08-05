#include<iostream>
#include "stack.h"
using namespace std;

const int Stack_init_size = 100;
const int Stack_increment = 10;


//构造函数
stack::stack() {
	str_arr = new char[Stack_init_size];
	if (!str_arr){
		cout << "arr malloc error!" << endl;
	}
}

//析构函数
stack::~stack() {
	if (str_arr){
		delete[] str_arr;
		str_arr = NULL;
	}
}


//向栈中添加一个e元素
void stack::push(char e) {
	str_arr[stacksize++] = e;
}

//向栈中取出一个元素
char stack::getTop() {
	return str_arr[stacksize - 1];
}

//在栈中删除一个元素
char stack::pop() {
	char top = str_arr[stacksize-1];
	stacksize--;
	return top;
}

//求栈的长度
int stack::stack_size() {
	return stacksize;
}


//检验栈是否为空（1为空）
int stack::isEmpty() {
	return stack_size() == 0;
}