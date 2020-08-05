#include"suffix.h"
#include<iostream>
#include"stack.h"
using namespace std;


// �����ɺ�׺ʽsuffix���ʽ��������
int suffix::evaluation(char suffix[]) {
	stack *s = new stack();
	char a, b;
	char ch = *suffix++;
	while (ch != '#') {
		if (!OpMember(ch))      
			s->push( ch);               // ��������������ջ
		else {
			b = s->pop();
			a = s->pop();               // �˳�ջ������������
			s->push( Operate(a, ch, b));     // ����Ӧ���㣬������������ջ
		}
		ch = *suffix++;                     // ����ȡ��һ�ַ�
	}
	char result = s->pop();
	return result-'0';
}

//����׺���ʽ���׺���ʽ
char* suffix::transform(char str_arr[]) {
	
	char *suffix = new char ;
	stack *s = new stack();
	char c;
	char *p = str_arr; 
	char ch = *p;  
	int k = 0;
	s->push('#');                          // Ԥ�������ջ��ջ��Ԫ��Ϊ'#'
	while (!s->isEmpty()) {
		if (!OpMember(ch))   
			suffix[k++] = ch;           // ������ֱ�ӷ��͸���׺ʽ
		else {
			switch (ch) {
			case '(': 
				s->push(ch); break;            // ������һ����ջ
			case ')': {
				c = s->pop();
				while (c != '(')            // ��ջ����������֮ǰ����������͸���׺ʽ
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
				}  // ��ջ��������������С�ڵ�ǰ���������������������͸���׺ʽ
				if (ch != '#') {
					s->push(ch);           // ����������ջ�����������ջ
				}
				break;
			} 
			}
		}
		if (ch != '#') 
			ch = *++p;
	}
	suffix[k] = '\0';                             // ����ַ����Ľ�����
	return suffix;
}

//�����ж�ch�Ƿ��ǲ�����
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