class data {

	public:

		static state startState()
		{
			state head = state();
			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					head.board[i][j] = 'E';
				}
			}
		    head.board[0][0] = head.board[0][7] = 'R';
		    head.board[0][1] = head.board[0][6] = 'H';
		    head.board[0][2] = head.board[0][5] = 'B';
		    head.board[0][4] = 'Q'; head.board[0][3] = 'K';
		    head.board[1][0] = head.board[1][1] = head.board[1][2] = head.board[1][3] = head.board[1][4] = head.board[1][5] = head.board[1][6] = head.board[1][7] = 'P';
		    head.board[7][0] = head.board[7][7] = 'r';
		    head.board[7][1] = head.board[7][6] = 'h';
		    head.board[7][2] = head.board[7][5] = 'b';
		    head.board[7][4] = 'q'; head.board[7][3] = 'k';
		    head.board[6][0] = head.board[6][1] = head.board[6][2] = head.board[6][3] = head.board[6][4] = head.board[6][5] = head.board[6][6] = head.board[6][7] = 'p';
		    head.setPlayer(true);
		    head.setLevel(0);
		    head.children.push_back(NULL);
		    head.calcValue();
		    return head;
		}
};