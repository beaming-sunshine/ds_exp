#include <iostream>
#include"suffix.h"
using namespace std;

int main() {

	suffix* suf = new suffix();
	char str[30],*suffixs;
	// char *str = "6-4/2-(3-1)*3+2#";    //���Ե���׺���ʽ
	cout << "��������׺���ʽ����#��������";
	cin >> str;
	suffixs  = suf->transform( str);
	cout <<endl<< "ת���ĺ�׺���ʽ��"<<suffixs << endl<<endl;

	//suffixs = "642/-31-3*-2+#";        //���Ե���׺���ʽ�ĺ�׺���ʽ
	int result = suf->evaluation(suffixs);
	cout<<"�ñ��ʽ�Ľ����"<<result << endl<<endl<<endl;

	system("pause");
	return 0;
}