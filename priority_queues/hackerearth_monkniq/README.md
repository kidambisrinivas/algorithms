
# Hackerearth - Monk And IQ Solution

* [Problem link](https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/monk-and-iq/)
* More datasets: After you submit, you'll have access to more inputs and expected outputs

## Solution

* Keep a priority queue of Courses sorted based on given criteria
* For each of monks friends
	* Pop top Course with min score and min id [O(logC)]
	* Add student and lastIQ
	* Push back to Priority Queue

## Complexity

* P - Monk and his friends
* C - Number of courses

### Space Complexity

* **Space Complexity:** O(4C)
	* 1 Course requires 4 integers

### Run Complexity

* **Query Complexity:** O(2P * logC)
	- 2 operations per person in Monk and his friends group [1 pop and 1 insert]


