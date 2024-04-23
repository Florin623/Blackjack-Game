# Blackjack Game
Console-based Blackjack game in C++, allowing users to check cards, shuffle cards and play games.

"check_cards" command is used to see if the card deck is fake (there are cards that represent numbers outside of 2 - 14 interval or they belong to suits that don't exist) or OK (it is a standard 52-card French-suited deck) or ready for Blackjack (there aren't 52 cards and there are also cards that repeat themselves).

"shuffle_cards" command is used to shuffle the cards by using the LCG (Linear Congruential Generator) algorithm.

"play_game" command is used to play games with n players where n is between 1 and 20. The stake is 10 euros for each player.
newline 
Examples of tests:

Input:

check_cards

4,romb

3,rosu

12,trefla

17,negru

7,rosu

9,telefon

7,negru

Output:

Pachet masluit


Input:

check_cards

4,romb

3,rosu

12,trefla

10,negru

7,rosu

9,romb

7,negru

3,rosu

Output:

Pregatit pentru Blackjack



Input:

shuffle_cards

1 5 4

2 2 3

4,romb

3,rosu

12,trefla

10,negru

7,rosu

9,romb

7,negru

3,rosu


Output:


7,negru

10,negru

7,rosu

9,romb

12,trefla

3,rosu

3,rosu

4,romb


Input:


play_game

4

Mihai 100

Maria 50

Matei 176

Andrei 100

10 26 33 34 37 45

2 4 30 32 38 48

3 24 27 34 45 48


Output:


Mihai: 70

Maria: 20

Matei: 146

Andrei: 80
