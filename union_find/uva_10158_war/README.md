
# UVA 10158 - War Solution

* [Problem link](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1099)
* [More datasets](https://www.udebug.com/UVa/10158)

## Solution

### Idea 1
* Enemy relation cannot be captured by set [Friend of friend can be in same set, but enemy of enemy cannot be in same set]
* Maintain separate enemies array, but for every `setEnemies(x,y)` always set root of x to be enemy of root of y
* For every setFriends(x,y) or setEnemies(x,y), check enemies array if root of x is enemy of root of y

### Idea 2
* Maintain a single UFDS set (parent, rank tuple) for double the number of citizens
* Every citizen x has an imaginary (or representative) enemy at x + n
* `setFriends(x,y)` : Union (x,y) and Union(x+n,y+n) [Enemy of x is friend of enemy of y]
* `setEnemies(x,y)` : Union (px, ey) and Union (ex, py) [x will become friends with enemies of y, and vice-versa]

In this enemy relationships are also modelled as friendship relationships and we can use a single UFDS set to solve this problem

**Space Complexity:** O(2N)
**Union Time Complexity:** O(1)
**Find Time Complexity for M queries:** O(M * Ackermans(N)) ~ O(M * 4) [Amortized O(1) per find query]


