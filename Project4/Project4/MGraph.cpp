#include<iostream>
#include<stack>
#include<queue>
#include "MGraph.h"
using namespace std;

//创建邻接矩阵
void MGraph::CreateGraph(Graph &G) {
	cout << "请输入顶点个数与弧个数:";
	cin >> G.vexnum >> G.arcs;
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++)
			G.matrix[i][j] = INFINITY;
	}
	cout << "请分别输入顶点入度与出度的下标与弧的权值:"<<endl;
	for (int k = 0; k< G.arcs; k++) {
		int i, j,w;
		cin >> i >> j >> w;
		G.matrix[i-1][j-1] = w;
	}
}

//打印邻接矩阵
void MGraph::PrintGraph (Graph G){
	cout << "图的邻接矩阵表示："<<endl;
	for (int i = 0; i < G.vexnum; i++){
		for (int j = 0; j < G.vexnum; j++){
			if (G.matrix[i][j] == INFINITY){
				cout << "*" << '\t';
			}else{
				cout << G.matrix[i][j] << '\t';
			}
		}
		cout << endl;
	}
	cout << endl;
}

//拓扑排序
void MGraph::TopoSort(Graph G , stack<int> &T) {
	int indegree[MAX_VERTEX_NUM] = {0};
	int count = 0;

	//求入度（列和）
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			if (G.matrix[j][i] != INFINITY)
				indegree[i]++;
		}
	}
	for (int i = 0; i < G.vexnum; i++) {
		if (!indegree[i]) {
			s.push(i);
		}
	}
	cout << "拓扑排序为:";
	while (s.size()) {
		int i = s.top();
		s.pop();
		cout << "v" << i + 1 << "\t";
		T.push(i);
		count++;
		for (int j = 0; j < G.vexnum; j++) {
			if (G.matrix[i][j] != INFINITY) {
				if (!(--indegree[j]))
					s.push(j);
				if (ve[i] + G.matrix[i][j] > ve[j]){
					ve[j] = ve[i] + G.matrix[i][j];
				}
			}
		}
	}
	cout << endl;
	if (count < G.vexnum) {
		cout << "该图有回路！" << endl;
	}
	s.~stack();
}

//关键路径
void MGraph::CriticalPath(Graph G, stack<int>T) {
	
	for (int i = 0; i < G.vexnum; i++){
		vl[i] = INFINITY;
	}
	vl[G.vexnum - 1] = ve[G.vexnum - 1];
	while (!T.empty()){
		int i = T.top();
		T.pop();
		for (int j = 0; j < G.vexnum; j++){
			if (G.matrix[j][i] != INFINITY){
				if (vl[i] - G.matrix[j][i] < vl[j]){
					vl[j] = vl[i] - G.matrix[j][i];
				}
			}
		}
	}
	for (int i = 0; i < G.vexnum; i++){
		for (int j = 0; j < G.vexnum; j++){
			if (G.matrix[i][j] != INFINITY){
				if (ve[i] == vl[j] - G.matrix[i][j]){
					cout<<"v"<<i+1 << "-v" << j+1 << "  " << G.matrix[i][j] << endl;
				}
			}
		}
	}
	cout << "关键路径需要" << vl[G.vexnum - 1] << "天" << endl;

}