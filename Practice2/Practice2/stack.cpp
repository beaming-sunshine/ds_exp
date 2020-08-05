#include<iostream>
#include "stack.h"
using namespace std;

const int Stack_init_size = 100;
const int Stack_increment = 10;


//���캯��
stack::stack() {
	str_arr = new char[Stack_init_size];
	if (!str_arr){
		cout << "arr malloc error!" << endl;
	}
}

//��������
stack::~stack() {
	if (str_arr){
		delete[] str_arr;
		str_arr = NULL;
	}
}


//��ջ�����һ��eԪ��
void stack::push(char e) {
	str_arr[stacksize++] = e;
}

//��ջ��ȡ��һ��Ԫ��
char stack::getTop() {
	return str_arr[stacksize - 1];
}

//��ջ��ɾ��һ��Ԫ��
char stack::pop() {
	char top = str_arr[stacksize-1];
	stacksize--;
	return top;
}

//��ջ�ĳ���
int stack::stack_size() {
	return stacksize;
}


//����ջ�Ƿ�Ϊ�գ�1Ϊ�գ�
int stack::isEmpty() {
	return stack_size() == 0;
}