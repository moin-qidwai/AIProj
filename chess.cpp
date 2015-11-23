#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "data.h"

using namespace std;

int main()
{
	state head = data::startState();

    head.output();

    int initF, initR;
    cout << "which piece would you like to move? Please input the file then rank seperated by space." << endl;
    cin >> initF >> initR;
    while(head.board[initF][initR] != 'k' && head.board[initF][initR] != 'q' && head.board[initF][initR] != 'r' && head.board[initF][initR] != 'h' && head.board[initF][initR] != 'b' && head.board[initF][initR] != 'p')
    {
    	cout << "You chose a block that does not contain one of your pieces. \nPlease try again.";
    	cin >> initF >> initR;
    }

    cout << "which block would you like to move? Please input the file then rank seperated by space." << endl;
    int resF, resR;
    cin >> resF >> resR;

    // func(state s, startF, startR, endF, endR)
    // function to check if the move is a valid move or not. if so then perform the move.

	try {
		Tree tree = Tree(head);
		tree.create();
		tree.traverse();
	}
	catch (std::exception& e)
	{
	    std::cerr << "Exception catched : " << e.what() << std::endl;
	}
	return 0;
}
