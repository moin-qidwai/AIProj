#include "state.h"

std::vector<state> expand(state s)
{
	std::vector<state> c;
	if(s.getPlayer() == false)
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				char piecea = s.board[i][j];
				switch(piecea)
				{
					case 'K':
						for(int dir = 1; dir <= 4; dir++)
						{
							int row, col;
							switch(dir)
							{
								case 1:
									row = 1; col = 0;
									break;
								case 2:
									row = 1; col = 1;
									break;
								case 3:
									row = 0; col = 1;
									break;
								case 4:
									row = -1; col = 1;
									break;
								default:
									row = 1; col = 0;
									break;
							}
							for(int k = -1; k < 2; k+=2)
							{
								row = row*k; col = col*k;
								char piece = s.board[i+row][j+col];
								if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
								{
									state t = state::createChild(s);
									t.board[i+row][j+col] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
							}	
						}
						break;
					case 'R':
						for(int dir = 0; dir < 4; dir++)
						{
							int row = (dir-1)%3, col = dir <= 1 ? dir : (dir%3)-2;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}	
						}
						break;
					case 'B':
						for(int dir = 0;dir < 4; dir++)
						{
							int row = dir%4 == 3 || dir%4 == 0 ? 1 : -1, col = dir <= 1 ? 1 : -1;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}
						}
						break;
					case 'H':
						for(int dir = 1;dir <= 8 ; dir++)
						{
							int row, col;
							switch(dir)
							{
								case 1:
									row = 2; col = 1;
									break;
								case 2:
									row = -1; col = 2;
									break;
								case 3:
									row = 1; col = 2;
									break;
								case 4:
									row = -2; col = 1;
									break;
								case 5:
									row = -2; col = -1;
									break;
								case 6:
									row = -1; col = -2;
									break;
								case 7:
									row = 1; col = -2;
									break;
								case 8:
									row = 2; col = -1;
									break;
								default:
									row = 1; col = 2;
									break;
							}
							char piece = s.board[row+i][col+j];
							if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
							{
								state t = state::createChild(s);
								t.board[row+i][col+j] = t.board[i][j];
								t.board[i][j] = 'E';
								t.calcValue();
								c.push_back(t);
							}
						}
						break;
					case 'Q':
						for(int dir = 0; dir < 4; dir++)
						{
							int row = (dir-1)%3, col = dir <= 1 ? dir : (dir%3)-2;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}	
						}
						for(int dir = 0;dir < 4; dir++)
						{
							int row = dir%4 == 3 || dir%4 == 0 ? 1 : -1, col = dir <= 1 ? 1 : -1;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}
						}
						break;
					case 'P':
						if(i < 8)
						{
							if(j < 7)
							{
								char piece = s.board[i+1][j+1];
								if(piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
								{
									state t = state::createChild(s);
									t.board[i+1][j+1] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
							}
							if(j > 0)
							{
								char piece = s.board[i+1][j-1];
								if(piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
								{
									state t = state::createChild(s);
									t.board[i+1][j-1] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
							}
							char piece = s.board[i+1][j];
							if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
							{
								state t = state::createChild(s);
								t.board[i+1][j] = t.board[i][j];
								t.board[i][j] = 'E';
								t.calcValue();
								c.push_back(t);
							}
						}
						break;
				}
			}
		}
	}
	else
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				char piecea = s.board[i][j];
				switch(piecea)
				{
					case 'K':
						for(int dir = 1; dir <= 4; dir++)
						{
							int row, col;
							switch(dir)
							{
								case 1:
									row = 1; col = 0;
									break;
								case 2:
									row = 1; col = 1;
									break;
								case 3:
									row = 0; col = 1;
									break;
								case 4:
									row = -1; col = 1;
									break;
								default:
									row = 1; col = 0;
									break;
							}
							for(int k = -1; k < 2; k+=2)
							{
								row = row*k; col = col*k;
								char piece = s.board[i+row][j+col];
								if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[i+row][j+col] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
							}	
						}
						break;
					case 'R':
						for(int dir = 0; dir < 4; dir++)
						{
							int row = (dir-1)%3, col = dir <= 1 ? dir : (dir%3)-2;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}	
						}
						break;
					case 'B':
						for(int dir = 0;dir < 4; dir++)
						{
							int row = dir%4 == 3 || dir%4 == 0 ? 1 : -1, col = dir <= 1 ? 1 : -1;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}
						}
						break;
					case 'H':
						for(int dir = 1;dir <= 8 ; dir++)
						{
							int row, col;
							switch(dir)
							{
								case 1:
									row = 2; col = 1;
									break;
								case 2:
									row = -1; col = 2;
									break;
								case 3:
									row = 1; col = 2;
									break;
								case 4:
									row = -2; col = 1;
									break;
								case 5:
									row = -2; col = -1;
									break;
								case 6:
									row = -1; col = -2;
									break;
								case 7:
									row = 1; col = -2;
									break;
								case 8:
									row = 2; col = -1;
									break;
								default:
									row = 1; col = 2;
									break;
							}
							char piece = s.board[row+i][col+j];
							if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
							{
								state t = state::createChild(s);
								t.board[row+i][col+j] = t.board[i][j];
								t.board[i][j] = 'E';
								t.calcValue();
								c.push_back(t);
							}
						}
						break;
					case 'Q':
						for(int dir = 0; dir < 4; dir++)
						{
							int row = (dir-1)%3, col = dir <= 1 ? dir : (dir%3)-2;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}	
						}
						for(int dir = 0;dir < 4; dir++)
						{
							int row = dir%4 == 3 || dir%4 == 0 ? 1 : -1, col = dir <= 1 ? 1 : -1;
							for(int k = i, l = j;k<8 && k >= 0 && l < 8 && l >= 0;k+=row,l+=col)
							{
								char piece = s.board[k][l];
								if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[k][l] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
								else
								{
									break;
								}
							}
						}
						break;
					case 'P':
						if(i < 8)
						{
							if(j < 7)
							{
								char piece = s.board[i-1][j+1];
								if(piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[i+1][j+1] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
							}
							if(j > 0)
							{
								char piece = s.board[i-1][j-1];
								if(piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[i+1][j-1] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
							}
							char piece = s.board[i-1][j];
							if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
							{
								state t = state::createChild(s);
								t.board[i+1][j] = t.board[i][j];
								t.board[i][j] = 'E';
								t.calcValue();
								c.push_back(t);
							}
						}
						break;
				}
			}
		}
	}
	return c;
}

class Tree {
    state head;
    
    public:
    
    Tree(){
    	head = state();
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
        head.setPlayer(false);
        head.setLevel(0);
        head.calcValue();

    }

    void create()
    {
    	int n = 0;
    	std::vector<state> stack;
    	stack.push_back(head);
    	while(stack.size() > 0)
    	{
    		state current = stack.back();
    		stack.pop_back();
    		std::vector<state> newchilds = expand(current);
    		for (int i = 0; i < newchilds.size(); ++i)
			{
				current.children.push_back(&(newchilds[i]));
				newchilds[i].output();
				std::cout << std::endl << n++ << std::endl << std::endl << std::endl << std::endl << std::endl;
				stack.push_back(newchilds[i]);
			}
			
    	}
    }

};
