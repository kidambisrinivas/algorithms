#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MaxSize = 10002;
int p[MaxSize], r[MaxSize], owe[MaxSize];

int Find(int a) {
	return (p[a] == a) ? a : p[a] = Find(p[a]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if(r[pa] > r[pb])
		p[pb] = pa;
	else {
		p[pa] = pb;
		if(r[pa] == r[pb])
			r[pb]++;
	}
}

int main()
{
	int N, n, m, o, a, b;
	cin >> N;
	for(int t=0; t<N; t++) {
		cin >> n >> m;
		for(int k=0; k<n; k++) {
			cin >> o;
			owe[k] = o;
		}
        for ( int i = 0; i < n; i++ ) {
        	p[i] = i;
        	r[i] = 0;
        }
        for ( int i = 0; i < m; i++ ) {
        	cin >> a >> b;
        	Union(a, b);
        }

        for(int k=0; k<n; k++)
        	Find(k);

        int success = 1;
        for(int i=0; i<n; i++) {
        	int pi = Find(i);
        	int sum = owe[i];
        	if(r[pi] == -1)
        		continue;
        	for(int j=0; j<n; j++) {
        		if(j == i) continue;
        		int pj = Find(j);
        		if(pi == pj)
        			sum = sum + owe[j];
        	}
        	if(sum != 0) {
        		success = 0;
        		break;
        	}
        	r[pi] = -1;
        }
        if(success == 1)
        	cout << "HOUDU" << endl;
        else
        	cout << "ILLA" << endl;
	}
	return 0;
}