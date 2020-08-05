#ifndef  MGRAPH_H
#define MGRAPH_H

#include<iostream>
#include <iostream>
#include<stack>
#include<queue>
using namespace std;

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20        //��󶥵����

struct Graph {
	int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];     //�ڽӾ���
	int vexnum;    //�������
	int arcs;          //���ĸ���
};

class MGraph {
public:
	stack<int> s;
	int ve[MAX_VERTEX_NUM] = { 0 };                    //���緢��ʱ��
	int vl[MAX_VERTEX_NUM] = { INFINITY };       //��ٷ���ʱ��

public:

	void CreateGraph(Graph &G);
	void PrintGraph(Graph G);
	void TopoSort(Graph G ,stack<int> &T);
	void CriticalPath(Graph G,stack<int>T);

};


#endif