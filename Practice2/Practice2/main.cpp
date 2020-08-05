#include <iostream>
#include"suffix.h"
using namespace std;

int main() {

	suffix* suf = new suffix();
	char str[30],*suffixs;
	// char *str = "6-4/2-(3-1)*3+2#";    //测试的中缀表达式
	cout << "请输入中缀表达式（以#结束）：";
	cin >> str;
	suffixs  = suf->transform( str);
	cout <<endl<< "转化的后缀表达式："<<suffixs << endl<<endl;

	//suffixs = "642/-31-3*-2+#";        //测试的中缀表达式的后缀表达式
	int result = suf->evaluation(suffixs);
	cout<<"该表达式的结果："<<result << endl<<endl<<endl;

	system("pause");
	return 0;
}