#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

enum HeapType { MIN, MAX };

template<typename T> class Heap {
private:
	vector<T*> queue;
    int size;
    HeapType type;
    less<T> L;
    greater<T> G;

public:
	Heap(HeapType queueType) {
		size = 0;
		type = queueType;
		L = less<T>();
		G = greater<T>();
		queue.push_back(0); // 1-based array
	}

	void Swap(int x, int y) {
		T* temp = queue[x];
		queue[x] = queue[y];
		queue[y] = temp;
	}

	bool Compare(int x, int y) {
		if(type == MAX)
			return L(*queue[x], *queue[y]);
		else
			return G(*queue[x], *queue[y]);
	}

	int Parent(int k) { return k >> 1; }
	int Left(int k) { return k << 1; }
	int Right(int k) { return (k << 1) + 1; }

	void Swim(int k) {
		int parentk = Parent(k);
		while(k > 1 && Compare(parentk, k)) {
			Swap(parentk, k);
			k = parentk;
			parentk = Parent(k);
		}
	}

	void Sink(int k) {
		int leftk = Left(k);
		int rightk = Right(k);
		while(leftk <= size) {
			int child = leftk;
			if(rightk <= size) child = Compare(leftk, rightk) ? rightk : leftk;
			if(Compare(child, k)) break;
			Swap(k, child);
			k = child;
			leftk = Left(child);
			rightk = Right(child);
		}
	}

	void Add(T* x) {
		queue.push_back(x);
		size++;
		if(size > 1)
			Swim(size);
	}

	T* Pop() {
		T* top = queue[1];
		queue[1] = queue[size];
		queue.pop_back();
		size--;
		Sink(1);
		return top;
	}

	T* Peek() {
		return queue[1];
	}

	void Print() {
		cout << "Heap\nHeapSize: " << size << "\n";
		for(int k=1; k<=size; k++) {
			cout << queue[k]->ToString() << "\n";
		}
	}

	void PrintA() {
		cout << "Heap\nHeapSize: " << size << "\n";
		for(int k=1; k<=size; k++) {
			cout << queue[k] << "\n";
		}
	}

	int GetSize() {
		return size;
	}
};

struct Query {
	int qnum;
	int period;
	int nexttime;

	Query(int _qnum, int _period) {
		qnum = _qnum;
		period = _period;
		nexttime = period;
	}

	void SetNextTime(int nt) {
		nexttime = nt;
	}

	string ToString() {
		char buffer [50];
		sprintf(buffer, "qnum: %d, period: %d, nexttime: %d ", qnum, period, nexttime);
		return buffer;
	}

	int NextTick() const {
		return nexttime;
	}

	bool operator > (const Query &q) const {
		int myNext = NextTick();
		int qNext = q.NextTick();
		if(myNext != qNext)
			return myNext > qNext;
		else
			return qnum > q.qnum;
	}

	bool operator < (const Query &q) const {
		int myNext = NextTick();
		int qNext = q.NextTick();
		if(myNext != qNext)
			return myNext < qNext;
		else
			return qnum < q.qnum;
	}
};

int main() {
	bool registrationComplete = false;
	string cmd;
	int qnum, period, K, timeelapsed = 0, newTimeElapsed = 0;
	Heap<Query> h(MIN);
	while(!registrationComplete) {
		cin >> cmd;
		if(cmd == "Register") {
			cin >> qnum >> period;
			Query *q = new Query(qnum, period);
			h.Add(q);
		} else if(cmd == "#") {
			registrationComplete = true;
		}
	}
	cin >> K;
	for(int i=0; i<K; ) {
		vector<Query*> queries;
		Query *q = h.Pop();
		queries.push_back(q);
		timeelapsed = q->nexttime;
		bool moreQueriesToExecute = true;
		while(moreQueriesToExecute && h.GetSize() > 0) {
			Query *p = h.Peek();
			if(timeelapsed % p->period == 0) {
				p = h.Pop();
				queries.push_back(p);
			} else {
				moreQueriesToExecute = false;
			}
		}
		for(int j=0; j<queries.size() && i<K; j++) {
			cout << queries[j]->qnum << endl;
			queries[j]->SetNextTime(timeelapsed + queries[j]->period);
			h.Add(queries[j]);
			i++;
		}
	}
	return 0;
}