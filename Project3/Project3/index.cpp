#include<iostream>
#define MAX_MA 1000
#define MAX_ZF 100
using namespace std;


//Huffman树的存储表示
typedef struct
{
	int weight;                                     //权值
	int parent, lchild, rchild;              //双亲，左孩子，右孩子的下标
}HTNode, *HuffmanTree;                //动态分配数组存储Huffman树

//Huffman编码的存储表示
typedef char **HuffmanCode;         //动态分配数组存储Huffman编码表




// 选取权值最小的两个结点
void Select(HuffmanTree a, int n, int &s1, int &s2){
	int temp;
	for (int i = 0; i < n; i++) {
		if (a[i].parent == 0) {                   // 选择第一个parent为0的节点
			s1 = i;
			break;
		}
	}
	for (int i = 0; i < n; i++) {                 // 遍历找到权值最小的作为s1
		if (a[i].parent == 0 && a[s1].weight > a[i].weight)
			s1 = i;
	}
	for (int j = 0; j < n; j++) {
		if (a[j].parent == 0 && j != s1) {       // 选择第一个parent为0且不是s1的节点
			s2 = j;
			break;
		}
	}
	for (int j = 0; j < n; j++) {                   // 遍历找到权值最小且不是s1的作为s2
		if (a[j].parent == 0 && a[s2].weight > a[j].weight&&j != s1)
			s2 = j;
	}
	if (s1 > s2) {
		temp = s1;
		s1 = s2;
		s2 = temp;
	}
}


//构造哈夫曼树
void CreateHuffmanTree(HuffmanTree &huftree, int n)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	huftree = new HTNode[m + 1];
	int i;

	for (i = 1; i <= n; i++) {          // 初始化n个叶子节点
		cin >> huftree[i].weight;
		huftree[i].parent = 0;
		huftree[i].lchild = 0;
		huftree[i].rchild = 0;
	}
	for (; i <= 2 * n - 1; i++) {       // 初始化m-n个非叶子节点
		huftree[i].weight = 0;
		huftree[i].parent = 0;
		huftree[i].lchild = 0;
		huftree[i].rchild = 0;
	}

	for (int k = n+1; k <= 2 * n - 1; k++) {
		int s1, s2;
		Select(huftree, k, s1, s2);                    // 查找权值最小的两个根节点并合并
		huftree[s1].parent = k;
		huftree[s2].parent = k;
		huftree[k].lchild = s1;
		huftree[k].rchild = s2;
		huftree[k].weight = huftree[s1].weight + huftree[s2].weight;
	}
}


//哈夫曼编码
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	HC = new char*[n + 1];               //分配n个字符编码的头指针向量
	char *cd = new char[n];                //分配求编码的数据空间
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++){
		int start = n - 1;                 //start 开始指向编码结束符位置
		int c = i;
		int f = HT[c].parent;         //f指向结点c的双亲
		while (f != 0) {                    //根结点判断
			--start;                              //向前回溯，start向前指向一个位置
			if (HT[f].lchild == c) 
				cd[start] = '0';             
			else 
				cd[start] = '1';
			c = f;
			f = HT[f].parent;               //继续向上回溯
		}
		HC[i] = new char[n - start];           //为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);               //把求得编码的首地址从cd[start]复制到HC的当前行中
	}
	delete cd;
}


//哈夫曼译码
void TranCode(HuffmanTree HT, char a[], char zf[], char b[], int n){
	int q = 2 * n - 1;
	int k = 0;                   //记录b数组的下标
	int i = 0;
	for (i = 0; a[i] != '\0'; i++){
		if (a[i] == '0'){
			q = HT[q].lchild;
		}else if (a[i] == '1'){
			q = HT[q].rchild;
		}
		if (HT[q].lchild == 0 && HT[q].rchild == 0){           //是叶子节点
			b[k++] = zf[q];
			q = 2 * n - 1;
		}
	}
	b[k] = '\0';
}


//菜单函数
void menu(){
	cout << endl;
	cout << "       ************************************************************" << endl;
	cout << "       |      ★★★★★★★哈夫曼编码与译码★★★★★★★        |" << endl;
	cout << "       |                   1.  创建哈夫曼树                       |" << endl;
	cout << "       |                   2.  进行哈夫曼编码                     |" << endl;
	cout << "       |                   3.  进行哈夫曼译码                     |" << endl;
	cout << "       |                   4.  退出程序                           |" << endl;
	cout << "       ************************************************************" << endl;
	cout << endl;
}


void main(){
	int char_num;                                                    //记录要编码的字符个数
	char a[MAX_MA];                                             //储存输入的二进制字符编码
	char b[MAX_ZF];                                              //存储译出的字符
	char zf[MAX_ZF];                                  //储存要编码的字符
	HuffmanTree HT = NULL;                   //初始化树为空数
	HuffmanCode HC = NULL;                  //初始化编码表为空表

	menu();
	while (true)
	{
		int num;
		cout << "请选择功能(1-创建 2-编码 3-译码 4-退出): ";
		cin >> num;
		switch (num)
		{
		case 1:
			cout << "请输入字符个数:";
			cin >> char_num;
			cout << "请依次输入" << char_num << "个字符: ";
			for (int i = 1; i <= char_num; i++)
				cin >> zf[i];
			cout << "请依次输入" << char_num << "个字符的权值: ";
			CreateHuffmanTree(HT, char_num);//调用创建哈夫曼树的函数
			cout << "创建Huffman树的参数输出：" << endl;
			cout << "nodei" << "\t" << "char" << "\t" << "weight" << "\t" << "parent" << "\t" << "lchild" << "\t" << "rchild" << endl;
			for (int i = 1; i <= char_num * 2 - 1; i++){
				cout << i << "\t" << zf[i] << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
			}
			cout << endl;
			break;
		case 2:
			CreatHuffmanCode(HT, HC, char_num);      //调用创建编码的函数
			cout << endl;
			cout << "生成哈夫曼编码表的输出：" << endl;
			cout << "结点i" << "\t" << "字符" << "\t" << "权值" << "\t" << "编码" << endl;
			for (int i = 1; i <= char_num; i++){
				cout << i << "\t" << zf[i] << "\t" << HT[i].weight << "\t" << HC[i] << endl;
			}
			cout << endl;
			break;
		case 3:
			cout << "请输入想要翻译的一串二进制编码：";
			cin >> a;
			TranCode(HT, a, zf, b, char_num);            //调用译码的函数
			cout << endl;
			cout << "译码成功！翻译结果为：" << b << endl;
			cout << endl;
			break;
		case 4:
			cout << endl;
			cout << "退出成功！" << endl;
			exit(0);
		default:
			break;
		}
	}
	system("pause");
}
