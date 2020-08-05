#include<iostream>
#define MAX_MA 1000
#define MAX_ZF 100
using namespace std;


//Huffman���Ĵ洢��ʾ
typedef struct
{
	int weight;                                     //Ȩֵ
	int parent, lchild, rchild;              //˫�ף����ӣ��Һ��ӵ��±�
}HTNode, *HuffmanTree;                //��̬��������洢Huffman��

//Huffman����Ĵ洢��ʾ
typedef char **HuffmanCode;         //��̬��������洢Huffman�����




// ѡȡȨֵ��С���������
void Select(HuffmanTree a, int n, int &s1, int &s2){
	int temp;
	for (int i = 0; i < n; i++) {
		if (a[i].parent == 0) {                   // ѡ���һ��parentΪ0�Ľڵ�
			s1 = i;
			break;
		}
	}
	for (int i = 0; i < n; i++) {                 // �����ҵ�Ȩֵ��С����Ϊs1
		if (a[i].parent == 0 && a[s1].weight > a[i].weight)
			s1 = i;
	}
	for (int j = 0; j < n; j++) {
		if (a[j].parent == 0 && j != s1) {       // ѡ���һ��parentΪ0�Ҳ���s1�Ľڵ�
			s2 = j;
			break;
		}
	}
	for (int j = 0; j < n; j++) {                   // �����ҵ�Ȩֵ��С�Ҳ���s1����Ϊs2
		if (a[j].parent == 0 && a[s2].weight > a[j].weight&&j != s1)
			s2 = j;
	}
	if (s1 > s2) {
		temp = s1;
		s1 = s2;
		s2 = temp;
	}
}


//�����������
void CreateHuffmanTree(HuffmanTree &huftree, int n)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	huftree = new HTNode[m + 1];
	int i;

	for (i = 1; i <= n; i++) {          // ��ʼ��n��Ҷ�ӽڵ�
		cin >> huftree[i].weight;
		huftree[i].parent = 0;
		huftree[i].lchild = 0;
		huftree[i].rchild = 0;
	}
	for (; i <= 2 * n - 1; i++) {       // ��ʼ��m-n����Ҷ�ӽڵ�
		huftree[i].weight = 0;
		huftree[i].parent = 0;
		huftree[i].lchild = 0;
		huftree[i].rchild = 0;
	}

	for (int k = n+1; k <= 2 * n - 1; k++) {
		int s1, s2;
		Select(huftree, k, s1, s2);                    // ����Ȩֵ��С���������ڵ㲢�ϲ�
		huftree[s1].parent = k;
		huftree[s2].parent = k;
		huftree[k].lchild = s1;
		huftree[k].rchild = s2;
		huftree[k].weight = huftree[s1].weight + huftree[s2].weight;
	}
}


//����������
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	HC = new char*[n + 1];               //����n���ַ������ͷָ������
	char *cd = new char[n];                //�������������ݿռ�
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++){
		int start = n - 1;                 //start ��ʼָ����������λ��
		int c = i;
		int f = HT[c].parent;         //fָ����c��˫��
		while (f != 0) {                    //������ж�
			--start;                              //��ǰ���ݣ�start��ǰָ��һ��λ��
			if (HT[f].lchild == c) 
				cd[start] = '0';             
			else 
				cd[start] = '1';
			c = f;
			f = HT[f].parent;               //�������ϻ���
		}
		HC[i] = new char[n - start];           //Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);               //����ñ�����׵�ַ��cd[start]���Ƶ�HC�ĵ�ǰ����
	}
	delete cd;
}


//����������
void TranCode(HuffmanTree HT, char a[], char zf[], char b[], int n){
	int q = 2 * n - 1;
	int k = 0;                   //��¼b������±�
	int i = 0;
	for (i = 0; a[i] != '\0'; i++){
		if (a[i] == '0'){
			q = HT[q].lchild;
		}else if (a[i] == '1'){
			q = HT[q].rchild;
		}
		if (HT[q].lchild == 0 && HT[q].rchild == 0){           //��Ҷ�ӽڵ�
			b[k++] = zf[q];
			q = 2 * n - 1;
		}
	}
	b[k] = '\0';
}


//�˵�����
void menu(){
	cout << endl;
	cout << "       ************************************************************" << endl;
	cout << "       |      ������������������������������        |" << endl;
	cout << "       |                   1.  ������������                       |" << endl;
	cout << "       |                   2.  ���й���������                     |" << endl;
	cout << "       |                   3.  ���й���������                     |" << endl;
	cout << "       |                   4.  �˳�����                           |" << endl;
	cout << "       ************************************************************" << endl;
	cout << endl;
}


void main(){
	int char_num;                                                    //��¼Ҫ������ַ�����
	char a[MAX_MA];                                             //��������Ķ������ַ�����
	char b[MAX_ZF];                                              //�洢������ַ�
	char zf[MAX_ZF];                                  //����Ҫ������ַ�
	HuffmanTree HT = NULL;                   //��ʼ����Ϊ����
	HuffmanCode HC = NULL;                  //��ʼ�������Ϊ�ձ�

	menu();
	while (true)
	{
		int num;
		cout << "��ѡ����(1-���� 2-���� 3-���� 4-�˳�): ";
		cin >> num;
		switch (num)
		{
		case 1:
			cout << "�������ַ�����:";
			cin >> char_num;
			cout << "����������" << char_num << "���ַ�: ";
			for (int i = 1; i <= char_num; i++)
				cin >> zf[i];
			cout << "����������" << char_num << "���ַ���Ȩֵ: ";
			CreateHuffmanTree(HT, char_num);//���ô������������ĺ���
			cout << "����Huffman���Ĳ��������" << endl;
			cout << "nodei" << "\t" << "char" << "\t" << "weight" << "\t" << "parent" << "\t" << "lchild" << "\t" << "rchild" << endl;
			for (int i = 1; i <= char_num * 2 - 1; i++){
				cout << i << "\t" << zf[i] << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
			}
			cout << endl;
			break;
		case 2:
			CreatHuffmanCode(HT, HC, char_num);      //���ô�������ĺ���
			cout << endl;
			cout << "���ɹ����������������" << endl;
			cout << "���i" << "\t" << "�ַ�" << "\t" << "Ȩֵ" << "\t" << "����" << endl;
			for (int i = 1; i <= char_num; i++){
				cout << i << "\t" << zf[i] << "\t" << HT[i].weight << "\t" << HC[i] << endl;
			}
			cout << endl;
			break;
		case 3:
			cout << "��������Ҫ�����һ�������Ʊ��룺";
			cin >> a;
			TranCode(HT, a, zf, b, char_num);            //��������ĺ���
			cout << endl;
			cout << "����ɹ���������Ϊ��" << b << endl;
			cout << endl;
			break;
		case 4:
			cout << endl;
			cout << "�˳��ɹ���" << endl;
			exit(0);
		default:
			break;
		}
	}
	system("pause");
}
