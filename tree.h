#include "state.h"
#include "data.h"

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
							if(row+i >= 0 && row+i <= 7 && col+j >= 0 && col+j <= 7)
							{
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
					case 'k':
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
					case 'r':
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
					case 'b':
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
					case 'h':
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
							if(row+i >= 0 && row+i <= 7 && col+j >= 0 && col+j <= 7)
							{
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
						}
						break;
					case 'q':
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
					case 'p':
						if(i > 0)
						{
							if(j < 7)
							{
								char piece = s.board[i-1][j+1];
								if(piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
								{
									state t = state::createChild(s);
									t.board[i-1][j+1] = t.board[i][j];
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
									t.board[i-1][j-1] = t.board[i][j];
									t.board[i][j] = 'E';
									t.calcValue();
									c.push_back(t);
								}
							}
							char piece = s.board[i-1][j];
							if(piece == 'E' || piece == 'K' || piece == 'H' || piece == 'R' || piece == 'B' || piece == 'Q' || piece == 'P' )
							{
								state t = state::createChild(s);
								t.board[i-1][j] = t.board[i][j];
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
    std::vector<state*> stack;
    state * newchilds = new state[7000];
    
    public:
    
    Tree(){
    }

    Tree(state s){
    	head = state();
    	for (int i = 0; i < 8; ++i)
    	{
    		for (int j = 0; j < 8; ++j)
    		{
    			head.board[i][j] = s.board[i][j];
    		}
    	}
        head.setPlayer(s.getPlayer());
        head.setLevel(s.getLevel());
        head.calcValue();
    }

    void create()
    {
    	int ind = 0;
    	stack.push_back(&head);
    	while(stack.size() > 0)
    	{
    		state * current = stack.back();
    		stack.pop_back();
    		if(current->getValue() != 10000)
    		{
    			std::vector<state> temp = expand(*current);
    			if(temp.size() > 1)
    			{
    				if(temp.at(0).getLevel() > 3)
    				{
    					continue;
    				}
    			}
    			for (int i = 0; i < temp.size(); ++i)
    			{
    				
    				newchilds[ind] = temp.at(i);
    				current->children.push_back(&(newchilds[ind]));
    				stack.push_back(&(newchilds[ind]));
    				ind++;
    			}
    		}
    	}
    }

    void static minmax(state & s)
    {
    	if(s.children.size() == 0)
    	{
    		s.setMinMax(s.getValue());
    		return;
    	}
    	for (int i = 0; i < s.children.size(); ++i)
    	{
    		if(s.children.at(i) != NULL)
    		{
    			Tree::minmax( *(s.children.at(i)) );
    		}
    	}
    	if(s.getPlayer())
    	{
    		int min = 100000;
    		for (int i = 0; i < s.children.size(); ++i)
    		{
    			if(s.children.at(i) != NULL)
    			{
    				min = s.children.at(i)->getValue();
    				break;
    			}		
    		}
    		if(min != 100000)
    		{
    			for (int i = 1; i < s.children.size(); ++i)
	    		{
	    			if(s.children.at(i) != NULL && s.children.at(i)->getValue() < min)
	    				min = s.children.at(i)->getValue();	
	    		}
	    		s.setMinMax(min);
    		}
    		else
    		{
    			s.setMinMax(s.getValue());
    		}
    	}
    	else
    	{
    		int max = -100000;
    		for (int i = 0; i < s.children.size(); ++i)
    		{
    			if(s.children.at(i) != NULL)
    			{
    				max = s.children.at(i)->getValue();
    				break;
    			}		
    		}
    		if(max != -100000)
    		{
    			for (int i = 1; i < s.children.size(); ++i)
	    		{
	    			if(s.children.at(i) != NULL && s.children.at(i)->getValue() > max)
	    				max = s.children.at(i)->getValue();	
	    		}
	    		s.setMinMax(max);
    		}
    		else
    		{
    			s.setMinMax(s.getValue());
    		}
    	}
    }


    void recurse()
    {
    	Tree::minmax(head);
    }

    state getMove()
    {
    	for (int i = 0; i < head.children.size(); ++i)
    	{
    		if(head.children.at(i) != NULL)
    		{
    			if(head.getMinMax() == head.children.at(i)->getValue())
    			{
    				return *(head.children.at(i));
    			}
    		}
    	}
    	return head;
    }

    void destroy()
    {
    	delete newchilds;
    }

    void traverse()
    {
    	head.output();
    	// for (int i = head.children.size()-1; i >= 0; --i)
    	// {
    	// 	if(head.children[i] != NULL)
    	// 		head.children[i]->output();
    	// 	else
    	// 		break;
    	// }
    }

};
