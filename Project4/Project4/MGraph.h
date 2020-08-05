#ifndef  MGRAPH_H
#define MGRAPH_H

#include<iostream>
#include <iostream>
#include<stack>
#include<queue>
using namespace std;

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20        //最大顶点个数

struct Graph {
	int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];     //邻接矩阵
	int vexnum;    //顶点个数
	int arcs;          //弧的个数
};

class MGraph {
public:
	stack<int> s;
	int ve[MAX_VERTEX_NUM] = { 0 };                    //最早发生时间
	int vl[MAX_VERTEX_NUM] = { INFINITY };       //最迟发生时间

public:

	void CreateGraph(Graph &G);
	void PrintGraph(Graph G);
	void TopoSort(Graph G ,stack<int> &T);
	void CriticalPath(Graph G,stack<int>T);

};


#endif