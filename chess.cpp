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

    cout << "***************BOARD****************" << endl;
	head.output();

    int initF, initR;
    cout << "Piece to move:" << endl;
    cout << "File = "; cin >> initF; 
    cout << "Rank = "; cin >>  initR;
    while(head.board[initF][initR] != 'k' && head.board[initF][initR] != 'q' && head.board[initF][initR] != 'r' && head.board[initF][initR] != 'h' && head.board[initF][initR] != 'b' && head.board[initF][initR] != 'p')
    {
    	cout << "You chose a block that does not contain one of your pieces. \nPlease try again.\n" << endl;
    	cout << "File = "; cin >> initF; 
        cout << "Rank = "; cin >>  initR;
    }

    int resF, resR;
    cout << "Move where?" << endl;
    cout << "File = "; cin >> resF; 
    cout << "Rank = "; cin >>  resR;

    // func(state s, startF, startR, endF, endR)
    // function to check if the move is a valid move or not. if so then perform the move. if not then ask for the end position again.
    while(!data::validMove(head, initF, initR, resF, resR))
    {
    	cout << "You chose an invalid move. \nPlease try again by entering the indices of the block you want to move to by File and then Rank.\n" << endl;
    	cout << "File = "; cin >> resF; 
        cout << "Rank = "; cin >>  resR;
    }

    head.board[resF][resR] = head.board[initF][initR];
    head.board[initF][initR] = 'E';
    head.setPlayer(false);

    cout << endl << "**************YOUR MOVE*************" << endl;
    head.output();

    Tree tree = Tree(head);
    tree.create();
    tree.recurse();

    while(1)
    {
        head = tree.getMove();
        if(head.finished())
        {
            cout << "The computer has killed your king. The game is over." << endl;
            return 0;
        }
        head.setLevel(0);

        cout << endl << "***********COMPUTER MOVED***********" << endl;
        head.output();

        cout << "Piece to move:" << endl;
        cout << "File = "; cin >> initF; 
        cout << "Rank = "; cin >>  initR;
        while(head.board[initF][initR] != 'k' && head.board[initF][initR] != 'q' && head.board[initF][initR] != 'r' && head.board[initF][initR] != 'h' && head.board[initF][initR] != 'b' && head.board[initF][initR] != 'p')
        {
            cout << "You chose a block that does not contain one of your pieces. \nPlease try again.\n" << endl;
            cout << "File = "; cin >> initF; 
            cout << "Rank = "; cin >>  initR;
        }

        cout << "Move where?" << endl;
        cout << "File = "; cin >> resF; 
        cout << "Rank = "; cin >>  resR;

        while(!data::validMove(head, initF, initR, resF, resR))
        {
            // func(state s, startF, startR, endF, endR)
            // function to check if the move is a valid move or not. if so then perform the move. if not then ask for the end position again.
            cout << "You chose an invalid move. \nPlease try again by entering the indices of the block you want to move to by File and then Rank." << endl;
            cout << "File = "; cin >> resF; 
            cout << "Rank = "; cin >>  resR;
        }        

        head.board[resF][resR] = head.board[initF][initR];
        head.board[initF][initR] = 'E';
        head.setPlayer(false);
        if(head.finished())
        {
            cout << "You have killed the computers king. You win. Congrats." << endl;
            return 0;
        }
        cout << endl << "**************YOUR MOVE*************" << endl;
        head.output();  

        try {
            tree = Tree(head);
            cout << endl << "The Computer is thinking...." << endl;
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
