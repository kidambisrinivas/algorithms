
# Hackerearth - Monk And IQ Solution

* [Problem link](https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/monk-and-iq/)
* More datasets: After you submit, you'll have access to more inputs and expected outputs

## Solution

* Keep a priority queue of Courses sorted based on given criteria
* For each of monks friends
	* Pop top Course with min score and min id [O(logC)]
	* Add student and lastIQ
	* Push back to Priority Queue

**Space Complexity:** 4 integers for storing a Course ~ O(4C)
**Query Complexity:** O(PlogC) [P - Monk and his friends, C - Number of courses]


