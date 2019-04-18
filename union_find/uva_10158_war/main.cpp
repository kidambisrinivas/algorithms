#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 20020;
int p[N], r[N], n;

int Find(int a) {
	return (p[a] == a) ? a : p[a] = Find(p[a]);
}

void Union(int pa, int pb) {
	if(r[pa] > r[pb])
		p[pb] = pa;
	else {
		p[pa] = pb;
		if(r[pa] == r[pb])
			r[pb]++;
	}
}

int SetFriends(int a, int b) {
	int pa, pb, ea, eb;
	pa = Find(a); pb = Find(b);
	ea = Find(a+n); eb = Find(b+n);
	if(pa == eb || pb == ea) {
		return -1;
	}
	Union(pa, pb);
	Union(ea, eb);
	return -2;
}

int SetEnemies(int a, int b) {
	int pa, pb, ea, eb;
	pa = Find(a); pb = Find(b);
	ea = Find(a+n); eb = Find(b+n);
	if(pa == pb) {
		return -1;
	}
	Union(pa, eb);
	Union(pb, ea);
	return -2;
}

int AreFriends(int a, int b) {
	return (Find(a) == Find(b)) ? 1 : 0;
}

int AreEnemies(int a, int b) {
	int pa, pb, ea, eb;
	pa = Find(a); pb = Find(b);
	ea = Find(a+n); eb = Find(b+n);
	return ((pa == eb) || (pb == ea)) ? 1 : 0;
}

int main()
{
	while ( scanf("%d", &n) != EOF ) {
		int c, a, b;
        for ( int i = 0; i <= n*2; ++i ) {
        	p[i] = i;
        	r[i] = 0;
        }
        while ( 1 ) {
        	scanf("%d%d%d", &c, &a, &b);
        	if ( a == 0 && c == 0 && b == 0 ) break;
        	int res = 0;
        	if ( c == 1 ) res = SetFriends( a, b );
            else if ( c == 2 ) res = SetEnemies( a, b );
            else if ( c == 3 ) res = AreFriends( a, b );
            else if ( c == 4 ) res = AreEnemies( a, b );
            if (res != -2)
            	printf("%d\n",res);
        }
	}
	return 0;
}