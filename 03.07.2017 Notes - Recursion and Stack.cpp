// 03.07.2017 Notes - Recursion and Stacks
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

// Towers of Hanoi Recursive Problem (https://www.youtube.com/watch?v=5_6nsViVM00) 
void towers(char start, char temp, char end, int disks) { // O(2^n) <- repeated doubling of a problem
	if (disks == 1) {
		cout << "Move it." << endl;
	}
	else {
		towers(start, end, temp, disks - 1); // (n - 1)
		towers(start, temp, end, 1);
		towers(temp, start, end, disks - 1); // (n - 1)
	}
}

template<class T>
class Stack {
public:
	void push(T newData);
	T pop();
	T& top();
	T top() const;
	bool isEmpty() const { return data.begin() == data.end(); }
	void clear() { data.clear(); }
private:
	list<T> data;
};

template<class T>
T Stack<T>::top() const {
	return *(data.begin());
}

template<class T>
T Stack<T>::top() {
	return *(data.begin());
}

template <class T>
void Stack<T>::push(T newData) {
	data.push_front(newData);
}

template<class T>
T Stack<T>::pop() {
	T retval = *(data.begin());
	data.pop_front();
	return retval;
}

int main() {
	Stack<int> s;
	for (int i = 0; i < 10; i++) {
		s.push(i);
	}
	while (!(s.isEmpty())) {
		cout << s.pop() << endl;
	}

	int arr[5];
	// func(arr[3)]; <-- ) = unexpected ')'
	/*
	Stack - main - func(arr[3)]
	[
	(
	{
	*/
}

/*
Towers of Hanoi Problem 
Three towers (A, B, C)
Goal is to move all the disks from A to C
Can never place a larger disk on a smaller disk

Stacks:
Last In First Out (LIFO) data structure
Like a stack of plates
Can't access the bottom-most plate. You can only take the top-most plate

Stack functions:
Stack		Vector			STL List
push		O(1) / O(n)		O(1)
pop			O(1)			O(1)
top			O(1)			O(1)
isEmpty		O(1)			O(1)
clear		O(1)			O(n)

Token matching - an open has to be followed by a close
(  )
{  }
[  ]
"  "
'  '

Call Stack
Every function call you make makes a new activation record
Activation records placed on top of call stack
You can see local variables because they're on the top of the stack

5 + 3 * 4 - 2 = 15

Post Fix Notation
4 3 +
534*+2-

Pre Fix Notation
+ 4 3 

C++ Precedence levels:
In CS associativity doesn't work, must be specified (Right to left, or left to right)
(a + b) + c = a + (b + c)
Assignment operator: right to left
x = y = z  is x = (y = z)  NOT  (x = y) = z
epsilon = eps the smallest value that can be stored in a float greater than 0
eps/2 = eps
eps/2 + eps/2 = eps
eps + eps = eps
(1 + eps) + eps =/= 1 + (eps + eps)
1 + 2eps       =/= 1 + eps
++++a = can do
a++++ = cannot do

	Precedence		Associativity
P		1				-
E		2			right to left
MD		3			left to right
AS		4			left to right

A + B + C = (A + B) + C
A ^ B ^ C = (A)^((B)^C)
Assosciativity is the order of operations of adjacent operators at the same precedence level
ASSOSCIATIVITY IS THE ORDER OF OPERATIONS OF ADJACENT OPERATORS OF THE SAME PRECEDENCE LEVEL****** IMPORTANT

Converting from infix to post fix (The stack stores the operators)
1) If the input is an operand, output it.
2) If the input is an open parentheses, put it on the stack
3) If the input is a close parentheses, pop to output all the elements until open parentheses, (throw away the open)
4) If the input is an operator, 
	a) if the precedence of the incoming operator is higher than that of the top of the stack, push the incoming operator
	b) if the precedence of the incoming operator is lower, pop to output, until you can push, then push the incoming operator
	c) If the precedence of the incoming operator is equal,
		I) if assosciativity is left to right, use b) above
		II) if assosciativity is right to left, use a) above

5 + 3 * 4 - 2 

534			Stack : + *
Because - is next, and precedence of - is lower than *, pop the *
534*		Stack : +
Now because incoming operator is -, which is the same precedence as +,
follows left to right, so uses b, pushes out the operator in the stack
534*+		Stack : 
Now does like normal
534*+2		Stack : -
534*+2-

3*(2+3)^2
3		Stack : * (
323		Stack : * ( + )
323+	Stack : *
323+2	Stack : * ^
323+2^	Stack : *
FINAL : 323+2^*

Converting from post fix to value (Stack stores operator)
1) If the input is an operand, push it onto the stack
2) If the input is an operator, pop two items and perform the operation. Remember that the second item popped is the left hand
side of the operation. Push the result
3) When input is finished, the value will be on the top of the stack.

323+2^*
Stack: 3
(2 + 3) = 5
Stack : 3 5
(5)^2 = 25
Stack : 3 25
3 * 25 = 75
Stack : 75
FINAL : 75

(4^(6-4)+25)/2
4			Stack : (
4			Stack : ( ^
464			Stack : ( ^ ( - 
464			Stack : ( ^ ( - )
464-		Stack : ( ^ 
464-		Stack : ( ^ INCOMING +
464-^		Stack : ( + 
464-^25		Stack : ( + )
464-^25+	Stack :
464-^25+2	Stack : /

FINAL : 464-^25+2/

(6 - 4) = 2
4^2 = 16
16 + 25 = 41
41/2 = 20.5
*/