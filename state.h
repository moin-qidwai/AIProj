class state {

    bool player;
    int value, level, minmax;

    int CPawnTable[64] = 
	{
	     0,  0,  0,  0,  0,  0,  0,  0,
	    50, 50, 50, 50, 50, 50, 50, 50,
	    10, 10, 20, 30, 30, 20, 10, 10,
	     5,  5, 10, 27, 27, 10,  5,  5,
	     0,  0,  0, 25, 25,  0,  0,  0,
	     5, -5,-10,  0,  0,-10, -5,  5,
	     5, 10, 10,-25,-25, 10, 10,  5,
	     0,  0,  0,  0,  0,  0,  0,  0
	};

	int PPawnTable[64] = 
	{
	     0,  0,  0,  0,  0,  0,  0,  0,
	     5, 10, 10,-25,-25, 10, 10,  5,
	     5, -5,-10,  0,  0,-10, -5,  5,
	     0,  0,  0, 25, 25,  0,  0,  0,
	     5,  5, 10, 27, 27, 10,  5,  5,
	     10, 10, 20, 30, 30, 20, 10, 10,
	     50, 50, 50, 50, 50, 50, 50, 50,
	     0,  0,  0,  0,  0,  0,  0,  0
	};

	int CKnightTable[64] = 
	{
	    -50,-40,-30,-30,-30,-30,-40,-50,
	    -40,-20,  0,  0,  0,  0,-20,-40,
	    -30,  0, 10, 15, 15, 10,  0,-30,
	    -30,  5, 15, 20, 20, 15,  5,-30,
	    -30,  0, 15, 20, 20, 15,  0,-30,
	    -30,  5, 10, 15, 15, 10,  5,-30,
	    -40,-20,  0,  5,  5,  0,-20,-40,
	    -50,-40,-20,-30,-30,-20,-40,-50
	};

	int PKnightTable[64] = 
	{
	    -50,-40,-20,-30,-30,-20,-40,-50,
	    -40,-20,  0,  5,  5,  0,-20,-40,
	    -30,  5, 10, 15, 15, 10,  5,-30,
	    -30,  0, 15, 20, 20, 15,  0,-30,
	    -30,  5, 15, 20, 20, 15,  5,-30,
	    -30,  0, 10, 15, 15, 10,  0,-30,
	    -40,-20,  0,  0,  0,  0,-20,-40,
	    -50,-40,-30,-30,-30,-30,-40,-50
	};

	int CBishopTable[64] = 
	{
	    -20,-10,-10,-10,-10,-10,-10,-20,
	    -10,  0,  0,  0,  0,  0,  0,-10,
	    -10,  0,  5, 10, 10,  5,  0,-10,
	    -10,  5,  5, 10, 10,  5,  5,-10,
	    -10,  0, 10, 10, 10, 10,  0,-10,
	    -10, 10, 10, 10, 10, 10, 10,-10,
	    -10,  5,  0,  0,  0,  0,  5,-10,
	    -20,-10,-40,-10,-10,-40,-10,-20
	};

	int PBishopTable[64] = 
	{
	    -20,-10,-40,-10,-10,-40,-10,-20,
	    -10,  5,  0,  0,  0,  0,  5,-10,
	    -10, 10, 10, 10, 10, 10, 10,-10,
	    -10,  0, 10, 10, 10, 10,  0,-10,
	    -10,  5,  5, 10, 10,  5,  5,-10,
	    -10,  0,  5, 10, 10,  5,  0,-10,
	    -10,  0,  0,  0,  0,  0,  0,-10,
	    -20,-10,-10,-10,-10,-10,-10,-20
	};

	int CRookTable[64] = 
	{
	     0,  0,  0,  0,  0,  0,  0,  0,
		 5, 10, 10, 10, 10, 10, 10,  5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		 0,  0,  0,  5,  5,  0,  0,  0
	};

	int PRookTable[64] = 
	{
		 0,  0,  0,  5,  5,  0,  0,  0,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		 5, 10, 10, 10, 10, 10, 10,  5,
		 0,  0,  0,  0,  0,  0,  0,  0
		 
	};

	int CQueenTable[64] = 
	{
		-20,-10,-10, -5, -5,-10,-10,-20,
		-10,  0,  0,  0,  0,  0,  0,-10,
		-10,  0,  5,  5,  5,  5,  0,-10,
		 -5,  0,  5,  5,  5,  5,  0, -5,
		  0,  0,  5,  5,  5,  5,  0, -5,
		-10,  5,  5,  5,  5,  5,  0,-10,
		-10,  0,  5,  0,  0,  0,  0,-10,
		-20,-10,-10, -5, -5,-10,-10,-20
	};

	int PQueenTable[64] = 
	{
		-20,-10,-10, -5, -5,-10,-10,-20,
		-10,  0,  5,  0,  0,  0,  0,-10,
		-10,  5,  5,  5,  5,  5,  0,-10,
		  0,  0,  5,  5,  5,  5,  0, -5,
		 -5,  0,  5,  5,  5,  5,  0, -5,
		-10,  0,  5,  5,  5,  5,  0,-10,
		-10,  0,  0,  0,  0,  0,  0,-10,
		-20,-10,-10, -5, -5,-10,-10,-20,
	};

	int CKingTable[64] = 
	{
	  -30, -40, -40, -50, -50, -40, -40, -30,
	  -30, -40, -40, -50, -50, -40, -40, -30,
	  -30, -40, -40, -50, -50, -40, -40, -30,
	  -30, -40, -40, -50, -50, -40, -40, -30,
	  -20, -30, -30, -40, -40, -30, -30, -20,
	  -10, -20, -20, -20, -20, -20, -20, -10, 
	   20,  20,   0,   0,   0,   0,  20,  20,
	   20,  30,  10,   0,   0,  10,  30,  20
	};

	int PKingTable[64] = 
	{
	   20,  30,  10,   0,   0,  10,  30,  20,
	   20,  20,   0,   0,   0,   0,  20,  20,
	  -10, -20, -20, -20, -20, -20, -20, -10, 
	  -20, -30, -30, -40, -40, -30, -30, -20,
	  -30, -40, -40, -50, -50, -40, -40, -30,
	  -30, -40, -40, -50, -50, -40, -40, -30,
	  -30, -40, -40, -50, -50, -40, -40, -30,
	  -30, -40, -40, -50, -50, -40, -40, -30,
	};

    public:

    	static const int MAXINFINITY = 100000;
		static const int MININFINITY = -100000;


    	char board[8][8];
    	state * parent;
    	std::vector<state*> children;

	    state()
	    {
	    	for (int i = 0; i < 8; ++i)
	    	{
	    		for (int j = 0; j < 8; ++j)
	    		{
	    			board[i][j] = 'E';
	    		}
	    	}
	    	player = false;
	    	level = 0;
	    	minmax = 0;
	    	calcValue();
	    	minmax = state::MININFINITY;
	    	children.push_back(NULL);
	    }

	    state(const state &t) //copy constructor
		{
			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					board[i][j] = t.board[i][j];
				}
			}
			player = t.player;
			level = t.level;
			calcValue();
			parent = t.parent;
		}

	    static state createChild(state parent)
	    {
	    	state s;
			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					s.board[i][j] = parent.board[i][j];
				}
			}
			s.player = !(parent.player);
			s.level = parent.level+1;
			s.children.push_back(NULL);
			s.calcValue();
			s.minmax = parent.player ? state::MAXINFINITY : state::MININFINITY;
			return s;
	    }

	    bool finished()
	    {
	    	for (int i = 0; i < 8; ++i)
	    	{
	    		for (int j = 0; j < 8; ++j)
	    		{
	    			if(!player)
	    			{
	    				if(board[i][j] == 'K')
	    					return false;
	    			}
	    			else
	    			{
	    				if(board[i][j] == 'k')
	    					return false;
	    			}
	    		}
	    	}
	    	return true;
	    }

	    void calcValue()
		{
			int score = 0;
			bool victory = true;
			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					victory = board[i][j] == 'k' ? false : victory;
					if (player)
					{
						switch(board[i][j])
						{
							case 'k':
								score+=PKingTable[(i*8)+j];
								break;
							case 'q':
								score+=PQueenTable[(i*8)+j];
								break;
							case 'r':
								score+=PRookTable[(i*8)+j];
								break;
							case 'b':
								score+=PBishopTable[(i*8)+j];
								break;
							case 'h':
								score+=PKnightTable[(i*8)+j];
								break;
							case 'p':
								score+=PPawnTable[(i*8)+j];
								break;
							default:
								break;
						}
					}
					else
					{
						switch(board[i][j])
						{
							case 'K':
								score+=CKingTable[(i*8)+j];
								break;
							case 'Q':
								score+=CQueenTable[(i*8)+j];
								break;
							case 'R':
								score+=CRookTable[(i*8)+j];
								break;
							case 'B':
								score+=CBishopTable[(i*8)+j];
								break;
							case 'H':
								score+=CKnightTable[(i*8)+j];
								break;
							case 'P':
								score+=CPawnTable[(i*8)+j];
								break;
							default:
								break;
						}
					}
					
				}
			}
			score = victory ? state::MAXINFINITY : score;
			value = score;
		}

		bool getPlayer()
		{
			return player;
		}

		void setPlayer(bool p)
		{
			player = p;
		}

		int getValue()
		{
			return value;
		}

		int getLevel()
		{
			return level;
		}

		void setLevel(int l)
		{
			level = l;
		}

		int getMinMax()
		{
			return minmax;
		}

		void setMinMax(int mm)
		{
			minmax = mm;
		}


		void output()
		{
			std::cout << "   | " << 0 << " | " << 1 << " | " << 2 << " | " << 3 << " | " << 4 << " | " << 5 << " | " << 6 << " | " << 7 << " | " << std::endl << "------------------------------------" << std::endl;
			for (int i = 0; i < 8; ++i)
			{
				std::cout << " " << i << " | ";
				for (int j = 0; j < 8; ++j)
				{
					std::cout << board[i][j] << " | ";
				}
				std::cout << std::endl << "------------------------------------" << std::endl;
			}
			// std::cout << player << std::endl;
			// std::cout << value << std::endl;
			// std::cout << level << std::endl;
			// std::cout << minmax << std::endl;
			std::cout << std::endl;
			for (int i = 0; i < children.size(); ++i)
			{
				if(children[i] == NULL)
					break;
				children[i]->output();
			}
		}
};