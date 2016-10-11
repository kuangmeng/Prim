
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#define N 100000
#define MAX 100
#define INF 65535
using namespace std;
int n, m;
struct node
{
	int v, w;
	bool operator<(const node &dd)const {
		return w>dd.w;
	} 
};
vector<node>q[N];
bool visited[N];
typedef char Elem;
typedef struct{
	int n, e;
	Elem vertex[MAX];
	int edge[MAX][MAX];
} MTGraph;
typedef struct {
	int begin, end, weight;
} Edge;
ifstream input("input.txt");
ofstream output("output.txt", ios::app);
int Locate(Elem vertex, MTGraph *G) {
	for (int i = 0; i<G->n; i++){
		if (G->vertex[i] == vertex) return i;
	}
	return -1;
}
void CreateMTGraph(MTGraph *G) {
	input >> G->n >> G->e;
	n = G->n; m = G->e;
	for (int i = 0; i <= n; i++)
		q[i].clear();
	node cur;
	output << "无向图的顶点、边个数：" << setw(5) << G->n << setw(5) << G->e << endl;
	output << "顶点信息：";
	for (int i = 0; i<G->n; i++) {
		input >> G->vertex[i];
		output << setw(5) << G->vertex[i];
	}
	output << endl;
	for (int i = 0; i<G->n; i++) {
		for (int j = 0; j<G->n; j++) {
			G->edge[i][j] = INF;
		}
	}
	Elem head, tail;
	int weight;
	for (int i = 0; i<G->e; i++) {
		input >> head >> tail >> weight;
		output << "第" << i + 1 << "条边：" << setw(5) << head << "<-->" << tail << ":" << weight << endl;
		while (Locate(head, G) == -1 || Locate(tail, G) == -1) {
			output << "边信息有误！" << endl;
			input >> head >> tail >> weight;
			output << "第" << i + 1 << "条边：" << setw(5) << head << "<-->" << tail << ":" << weight << endl;
		}
		int k = Locate(head, G), l = Locate(tail, G);
		G->edge[k][l] = G->edge[l][k] = weight;
		cur.v = l; cur.w = weight;
		q[k].push_back(cur);
		cur.v = k;
		q[l].push_back(cur); 
	}
	output << "*****无向图邻接矩阵已建成！*****" << endl;
}
int k = 0;
int  queue_prim(MTGraph *G){
	priority_queue<node> queue;
	while (!queue.empty())
		queue.pop(); 
	int ans = 0;
	memset(visited, false, sizeof(visited));
	for (int i = 0; i<q[0].size(); i++){
		queue.push(q[0][i]);
	}
	visited[0] = true;
	k++;
	int edge = n - 1;
	node cur;
	while (edge--){
		cur = queue.top();
		queue.pop();
		if (visited[cur.v] == true){
			while (visited[cur.v]){
				cur = queue.top(); 
				queue.pop();
			}
		}
		ans = ans + cur.w; 
		k++;
		visited[cur.v] = true; 
		for (int i = 0; i<q[cur.v].size(); i++){
			if (visited[q[cur.v][i].v] == false)
				queue.push(q[cur.v][i]);
		}
	}
	if (k < G->n){
		output << "图不连通！无法输出最小生成树！"<<endl;
		return 0;
	}
	else {
		output << "最小生成树的长度：";
		return ans;
	}
}
int main(){
	MTGraph *G=new MTGraph;
	char choose;
	while (1) {
		cout << "是否继续：";
		cin >> choose;
		if (choose != 'y' && choose != 'Y') break;
		CreateMTGraph(G);
		int ans = queue_prim(G);
		output  << ans << endl;
	}
	return 0;
}