#include<iostream>
#include<stack>
#include<queue>
#include "MGraph.h"
using namespace std;

//�����ڽӾ���
void MGraph::CreateGraph(Graph &G) {
	cout << "�����붥������뻡����:";
	cin >> G.vexnum >> G.arcs;
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++)
			G.matrix[i][j] = INFINITY;
	}
	cout << "��ֱ����붥���������ȵ��±��뻡��Ȩֵ:"<<endl;
	for (int k = 0; k< G.arcs; k++) {
		int i, j,w;
		cin >> i >> j >> w;
		G.matrix[i-1][j-1] = w;
	}
}

//��ӡ�ڽӾ���
void MGraph::PrintGraph (Graph G){
	cout << "ͼ���ڽӾ����ʾ��"<<endl;
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

//��������
void MGraph::TopoSort(Graph G , stack<int> &T) {
	int indegree[MAX_VERTEX_NUM] = {0};
	int count = 0;

	//����ȣ��кͣ�
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
	cout << "��������Ϊ:";
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
		cout << "��ͼ�л�·��" << endl;
	}
	s.~stack();
}

//�ؼ�·��
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
	cout << "�ؼ�·����Ҫ" << vl[G.vexnum - 1] << "��" << endl;

}