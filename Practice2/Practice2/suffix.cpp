#include"suffix.h"
#include<iostream>
#include"stack.h"
using namespace std;


// 返回由后缀式suffix表达式的运算结果
int suffix::evaluation(char suffix[]) {
	stack *s = new stack();
	char a, b;
	char ch = *suffix++;
	while (ch != '#') {
		if (!OpMember(ch))      
			s->push( ch);               // 非运算符入操作数栈
		else {
			b = s->pop();
			a = s->pop();               // 退出栈顶两个操作数
			s->push( Operate(a, ch, b));     // 作相应运算，并将运算结果入栈
		}
		ch = *suffix++;                     // 继续取下一字符
	}
	char result = s->pop();
	return result-'0';
}

//由中缀表达式求后缀表达式
char* suffix::transform(char str_arr[]) {
	
	char *suffix = new char ;
	stack *s = new stack();
	char c;
	char *p = str_arr; 
	char ch = *p;  
	int k = 0;
	s->push('#');                          // 预设运算符栈的栈底元素为'#'
	while (!s->isEmpty()) {
		if (!OpMember(ch))   
			suffix[k++] = ch;           // 操作数直接发送给后缀式
		else {
			switch (ch) {
			case '(': 
				s->push(ch); break;            // 左括弧一律入栈
			case ')': {
				c = s->pop();
				while (c != '(')            // 自栈顶至左括弧之前的运算符发送给后缀式
				{
					suffix[k++] = c;  
					c = s->pop();
				}
				break;
			}
			default: {
				while (precede(s->getTop(), ch)) {
					suffix[k++] = s->getTop();
					c = s->pop();
					if (c == '#') {
						break;
					}
				}  // 将栈中所有优先数不小于当前运算符优先数的运算符发送给后缀式
				if (ch != '#') {
					s->push(ch);           // 优先数大于栈顶的运算符入栈
				}
				break;
			} 
			}
		}
		if (ch != '#') 
			ch = *++p;
	}
	suffix[k] = '\0';                             // 添加字符串的结束符
	return suffix;
}

//用于判断ch是否是操作符
int suffix:: OpMember(char ch) {
	int result;
	switch (ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '#':
		result = 1; break;
	default:
		result = 0; break;
	}
	return result;
}

char suffix::Operate(char a, char ch, char b) {
	double result;
	double aa, bb;
	aa = a - '0';
	bb = b - '0';
	switch (ch)
	{
	case '+':
		result = aa + bb; break;
	case '-':
		result = aa - bb; break;
	case '*':
		result = aa*bb; break;
	case '/':
		result = aa / bb; break;
	default:
		break;
	}
	return result + '0';
}

int suffix::precede(char a, char b) {
	return getPrioraty(a) >= getPrioraty(b);
}

int suffix::getPrioraty(char e) {
     switch (e) {
	 case '+':
	 case '-':
		 return 1;
	 case '*':
	 case '/':
		 return 2;
	 case '(':
	 case ')':
		 return 0;
	 default:
		 return -1;
	}
}