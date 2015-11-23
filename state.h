class state {

    bool player;
    int value, level;

    public:

    	char board[8][8];
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
	    	calcValue();
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
			return s;
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
					switch(board[i][j])
					{
						case 'K':
							score+=10;
							break;
						case 'Q':
							score+=7;
							break;
						case 'R':
							score+=3;
							break;
						case 'B':
							score+=3;
							break;
						case 'H':
							score+=4;
							break;
						case 'P':
							score+=1;
							break;
						case 'k':
							score-=10;
							break;
						case 'q':
							score-=7;
							break;
						case 'r':
							score-=3;
							break;
						case 'b':
							score-=3;
							break;
						case 'h':
							score-=4;
							break;
						case 'p':
							score-=1;
							break;
						default:
							break;
					}
				}
			}
			score = victory ? 100 : score;
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

		void output()
		{
			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					std::cout << board[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << player << std::endl;
			std::cout << value << std::endl;
			std::cout << level << std::endl;
			std::cout << std::endl;
			for (int i = 0; i < children.size(); ++i)
			{
				if(children[i] == NULL)
					break;
				children[i]->output();
			}
		}
};