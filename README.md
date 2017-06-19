# Final-Project
My PIC 10C Final Project is a C++ implementation of the Game 2048. There are four files included in this repository: matrix.h, Game.h, Game.cpp, and main.cpp.

# Introduction of the Game
The Game 2048 has been popular for a long time, and my best friend is a big fan of it. This inspired me to give it a c++ implementation as my final project. 

1. The Rules of the Game
The Interface of the Game is a 4 by 4 matrix. At the beginning of the game, two 2's will appear in two random entries of the matrix. The gamer can move all the numbers in four directions: up/down/left/right. Once the gamer choose one direction, all the nonzero entries will be squeezed to the top of that direction, while all the zero entries will be squeezed to the bottom. In addition, two same entries right next to each other in that direction will be combined, and one space will be released. Finally, a new random entry of a number ranging from 2 to the max value in the interface will be generated. The goal of the gamer is to receive the highest score 2048. 

2. The Difference of my Version
When I played the Game 2048 online, I noticed that only number 2 or 4 will be generated as a new entry. However, in my implementation of the Game, for every new entry, I chose to generate a random number (of course it's some power of 2) ranging from 2 (the minimum value) to the max value in the current interface.

3. How to Play
When the program is started, it will first generated two 2's in two random entries. Then it will ask the gamer which direction to move. The user can choose from up (type 'u'), down (type 'd'), left (type 'l') and right (type 'r'). Notice that all the input should be exact as described. After receiving the input, the program will move and add accrodingly. Then it will ask the gamer again which direction to choose until no move can be done.

# Introduction of the Files
1. matrix.h
Since the interface is a 4 by 4 matrix, I implemented a matrix template which has its own iterators. The basic structure of the matrix class is a 2-D array. Specifically, to access the data, I use one pointer points to an array of pointers. The detailed explanation can be noticed in the comments of the file.

To connect with the content of our PIC 10C class, I tried four major topics in this file. 
a. Define a template.
To make matrix template more generic, I allowed multi-type of Item to be contained in the matrix. Ideally, those Itemtypes should be double or int. The advantage of this is to save memory when we only need integers, like my 2048 case.

b. Implementation of copy constructor, move constructor and move&copy.
To be honest, I experienced a really hard time when completing all these constructors. Since my basic container is a 2-D array, I have to be very careful with memory leak when creating something on the heap. Thus I used try-catch in every constructors. I actually tried many techiniques to move the 2-D array pointers in loops; however, finally I found std::swap is the easiest but the best way to swap 2-D array pointers. In the destructor I delete all the objects on the heap in a for loop.

c. Implementation of iterator
The iterator of a matrix is quite different from the iterator of a linear container. I first overloaded some basic operators including 
*(), ++(), --(), ==() and !=(). The fun part is my operator ++() can be used in versatile ways: with a private parameter byrow in matrix class, it can move the iterator either to the right or to the top. Same to my operator --().

d. Use of Generic Algorithm and Lambda Function
find_if and find.

2. Game.h & Game.cpp
Game class is a container and operator of all the contents in the game 2048. It uses the Matrix class and its iterators to move and change the values of the entries. It generates random entries, checks the failure condition of the gamer, and prints the game matrix to the console.

3. main.cpp
main.cpp is a simple interface with the gamer. It directs and interacts with the gamer. 
 

