// Problem link: https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/monk-and-iq/submissions/
// Solution:
// 1. Keep a priority queue of Courses sorted based on given criteria
// 2. For each of monks friends, pop top Course, add student and lastIQ and push back to Priority Queue

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

enum PriorityQueueType { MIN, MAX };

template<typename T> class PriorityQueue {
private:
	vector<T*> queue;
    int size;
    PriorityQueueType type;
    less<T> L;
    greater<T> G;

public:
	PriorityQueue(PriorityQueueType queueType) {
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
		cout << "size: " << size << "\n";
		for(int k=1; k<=size; k++) {
			cout << queue[k]->ToString() << "\n";
		}
	}

	int GetSize() {
		return size;
	}
};

struct Course {
	int id;
	int numStudents;
	int lastIQ;
	int score;

	Course(int _id) {
		id = _id;
		numStudents = 0;
		lastIQ = 0;
		score = 0;
	}

	string ToString() {
		char buffer [50];
		sprintf(buffer, "id: %d, count: %d, iq: %d, score: %d", id, numStudents, lastIQ, score);
		return buffer;
		// return "";
	}

	void Add(int newIQ) {
		numStudents++;
		score = numStudents * (lastIQ + newIQ);
		lastIQ = newIQ;
	}

	bool operator > (const Course &c) const {
		if(score != c.score)
			return score > c.score;
		else
			return id > c.id;
	}

	bool operator < (const Course &c) const {
		if(score != c.score)
			return score < c.score;
		else
			return id < c.id;
	}
};

int main() {
	int C, P, N, iq;
	while(cin >> C >> P >> N) {
		PriorityQueue<Course> courses(MIN);
		for(int k=1; k<=N; k++) {
			cin >> iq;
			// cout << "k: " << k << " iq: " << iq << endl;
			Course *c = new Course(k);
			c->Add(iq);
			courses.Add(c);
			// courses.Print();
		}
		for(int k=N+1; k<=C; k++)
			courses.Add(new Course(k));
		// courses.Print();
		for(int k=1; k<=P; k++) {
			iq = 0;
			cin >> iq;
			Course *c = courses.Pop();
			c->Add(iq);
			courses.Add(c);
			cout << c->id << " ";
			// courses.Print();
		}
	}
	return 0;
}