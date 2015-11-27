#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include "tree.h"

using namespace std;

int main()
{
	state head = data::startState();

	// head.output();

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
    // function to check if the move is a valid move or not. if so then perform the move. if not then ask for the end position again.
    while(!data::validMove(head, initF, initR, resF, resR))
    {
    	cout << "You chose an invalid move. \nPlease try again by entering the indices of the block you want to move to by File and then Rank.";
    	cin >> resF >> resR;
    }

    head.board[resF][resR] = head.board[initF][initR];
    head.board[initF][initR] = 'E';
    head.setPlayer(false);

    // head.output();

    Tree tree = Tree(head);
    tree.create();
    tree.recurse();

    while(1)
    {
        head = tree.getMove();
        head.output();

        initF, initR;
        cout << "which piece would you like to move? Please input the file then rank seperated by space." << endl;
        cin >> initF >> initR;
        while(head.board[initF][initR] != 'k' && head.board[initF][initR] != 'q' && head.board[initF][initR] != 'r' && head.board[initF][initR] != 'h' && head.board[initF][initR] != 'b' && head.board[initF][initR] != 'p')
        {
            cout << "You chose a block that does not contain one of your pieces. \nPlease try again.";
            cin >> initF >> initR;
        }

        cout << "which block would you like to move? Please input the file then rank seperated by space." << endl;
        resF, resR;
        cin >> resF >> resR;

        // func(state s, startF, startR, endF, endR)
        // function to check if the move is a valid move or not. if so then perform the move. if not then ask for the end position again.
        while(!data::validMove(head, initF, initR, resF, resR))
        {
            cout << "You chose an invalid move. \nPlease try again by entering the indices of the block you want to move to by File and then Rank.";
            cin >> resF >> resR;
        }

        head.board[resF][resR] = head.board[initF][initR];
        head.board[initF][initR] = 'E';
        head.setPlayer(false);

        // head.output();  

        try {
            tree = Tree(head);
            tree.create();
            tree.recurse();
        }
        catch (std::exception& e)
        {
            std::cerr << "Exception catched : " << e.what() << std::endl;
        }      

    }

    	
	return 0;
}
