#include <iostream>
#include <vector>
#pragma comment (linker, "/STACK:33554432")

using namespace std;

int main(){
	//freopen("i.txt", "r", stdin);

	// входные данные
	int n, t, rez=0;
	vector < vector<int> > g;
	const int INF = 1000000000; // значение"бесконечность"
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		vector <int> temp;
		for(int z=0; z<n; z++){
			scanf("%d", &t);
			if(t==0 && i!=z) t=INF;
			temp.push_back(t);
		}
		g.push_back(temp);
	}


	// алгоритм Прима за О(n^2) на матриці сміжності
	vector<bool> used (n);
	vector<int> min_e (n, INF), sel_e (n, -1);
	min_e[0] = 0;
		for (int i=0; i<n; ++i) {
			int v = -1;
			for (int j=0; j<n; ++j){
				if (!used[j] && (v == -1 || min_e[j] < min_e[v])) v = j; }
			if (min_e[v] == INF) { cout << "No MST!"; exit(0); }
			used[v] = true;
			if (sel_e[v] != -1) {
				//cout << v << " " << sel_e[v] << endl;
				rez+=g[v][sel_e[v]];
			}
			for (int to=0; to<n; ++to) if (g[v][to] < min_e[to]) {
																	min_e[to] = g[v][to];
																	sel_e[to] = v;
																}
			}

		printf("%d", rez);
}