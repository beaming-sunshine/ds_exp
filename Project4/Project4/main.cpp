#include <iostream>
#include "MGraph.h"
#include<stack>
#include<queue>
using namespace std;

int main() {

	MGraph G;
	Graph graph;       //�ڽӾ���
	stack<int> s;

	G.CreateGraph(graph);
	G.PrintGraph(graph);
	G.TopoSort(graph,s);
	G.CriticalPath(graph, s);

	system("pause");
	return 0;
}