# DSA-Big-HW1

This is the first big assignment in the data structures course. In the following, the solutions will be explained.

## Exercise One

### Solution Description

1. We generate a matrix containing the information about the interactions between attendees at the party, with the help of vectors, we read the rows of the matrix from a given text file and save them. Of course, we first read the maximum size of the matrix from the first line of the text file. 

2. We create a stack in which we push the indices corresponding to each person present at the party; from 0 to N-1 (N being the size of  the matrix).

3. We repeatedly check if the people corresponding to the last 2 indices in the stack have talked to each other or not: 
	
- Case A: None of them talked to the other, both are removed from	the stack.  

- Case B: Both talked to each other, both are removed from the stack.

- Case C: Only one of them talked to the other, we remove the one who talked from the stack.


4. Using the characteristics of our VIP “Homer”, we eliminate all the incompatible candidates, leaving only Homer in our stack, or if there’s no one left in the stack, this means that Homer simply wasn’t present at the party.

5. Once we find a candidate, we determine if he hasn’t talked to anyone by checking his row in the matrix and if everyone has talked to him by checking the column corresponding to his index in the matrix.

### How to Use

Create a text file, add on the first line the size of your matrix 		[one integer], on the following lines you write the rows of the matrix,		whose elements are separated by commas. (See the m1.txt file as an		example)
After running the program, you will be asked to insert a path to a text file containing a matrix, then you will simply receive an answer, either that the VIP wasn’t present or the id of the VIP if they attended the party.


## Exercise Two

### Solution Description

1. Our abstract “restaurant” can take orders from text files which are stored using a structure called “order”, having the fields (t) and (d) meaning arrival time and duration. 

2. It can display the expected and actual time of completion for an order, it can also display a message when the chef can take a break and whether any order will be completed after the closing time.

### How to Use

When running the program, you will be asked to insert a path to a text file from which the orders will be read, the text file should respect this format: 

```
Line 1: NUMBER OF ORDERS [INT], CLOSING TIME [INT]
Line 2: TIME_OF_ARRIVAL [INT] , DURATION [INT] 
Line 3: REPEAT FORMAT OF LINE 2 
```

## Exercise Three

