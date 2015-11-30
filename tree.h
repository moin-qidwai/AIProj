#include "state.h"
#include "data.h"

class Tree {

	int DYNSIZE = 1000000;

    state head;
    int ind;
    state * newchilds = new state[DYNSIZE];
    
    public:
    
    Tree(){
    	ind = 1;
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
        newchilds[0] = head;
        ind = 1;
    }

    void process(state & h)
    {
    	if(h.getLevel() == 6)
    	{
    		h.calcValue();
    		h.setAlpha(state::MININFINITY);
    		h.setBeta(h.getValue());
    		return;
    	}
    	else if(h.getLevel() > 6)
    	{
    		return;
    	}

    	if(h.getValue() == state::MAXINFINITY)
    	{
    		h.calcValue();
    		if(h.getPlayer())
    		{
    			h.setAlpha(state::MININFINITY);
    			h.setBeta(h.getValue());
    		}
    		else
    		{
    			h.setAlpha(h.getValue());
    			h.setBeta(state::MAXINFINITY);
    		}
    		return;
    	}

    	if(h.getPlayer())
    	{
    		if(h.parent != NULL && h.getLevel() > 0)
    		{
    			if(h.parent->parent != NULL && h.getLevel() > 1)
    			{
    				if(h.parent->parent->getBeta() != state::MAXINFINITY)
    				{
    					h.setBeta(h.parent->parent->getBeta());
    					h.setAlpha(h.parent->getAlpha());
    				}
    			}
    		}
    		for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					char piecea = h.board[i][j];
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
									char piece = h.board[i+row][j+col];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[i+row][j+col] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
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
									char piece = h.board[row+i][col+j];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[i+row][j+col] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
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
									char piece = h.board[i+1][j+1];
									if(piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[i+1][j+1] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
									}
								}
								if(j > 0)
								{
									char piece = h.board[i+1][j-1];
									if(piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[i+1][j-1] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() < h.getBeta())
										{
											h.setBeta(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getBeta());
											}
											if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
											{
												h.setValue(h.getBeta());
												return;
											}
										}
									}
								}
								char piece = h.board[i+1][j];
								if(piece == 'E' )
								{
									newchilds[ind] = state::createChild(h);
									newchilds[ind].board[i+1][j] = newchilds[ind].board[i][j];
									newchilds[ind].board[i][j] = 'E';
									newchilds[ind].parent = &h;
									ind++;
									int childind = ind-1;
									process(newchilds[childind]);
									if(newchilds[childind].getValue() < h.getBeta())
									{
										h.setBeta(newchilds[childind].getValue());
										if(!data::isChecked(newchilds[childind], h.getPlayer()))
										{
											h.children.push_back(&newchilds[childind]);
											h.setValue(h.getBeta());
										}
										if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
										{
											h.setValue(h.getBeta());
											return;
										}
									}
								}
								piece = h.board[i+2][j];
								if(piece == 'E' && h.board[i+1][j] == 'E')
								{
									newchilds[ind] = state::createChild(h);
									newchilds[ind].board[i+2][j] = newchilds[ind].board[i][j];
									newchilds[ind].board[i][j] = 'E';
									newchilds[ind].parent = &h;
									ind++;
									int childind = ind-1;
									process(newchilds[childind]);
									if(newchilds[childind].getValue() < h.getBeta())
									{
										h.setBeta(newchilds[childind].getValue());
										if(!data::isChecked(newchilds[childind], h.getPlayer()))
										{
											h.children.push_back(&newchilds[childind]);
											h.setValue(h.getBeta());
										}
										if(h.parent->getAlpha() != state::MAXINFINITY && h.parent->getAlpha() > h.getBeta())
										{
											h.setValue(h.getBeta());
											return;
										}
									}
								}
							}
							break;
					}
				}
			}
    	}
    	else
    	{
    		if(h.parent != NULL && h.getLevel() > 0)
    		{
    			if(h.parent->parent != NULL && h.getLevel() > 1)
    			{
    				
    				if(h.parent->parent->getAlpha() != state::MININFINITY)
    				{
    					h.setAlpha(h.parent->parent->getAlpha());
    					h.setBeta(h.parent->getBeta());
    				}
    			}
    		}

			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					char piecea = h.board[i][j];
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
									char piece = h.board[i+row][j+col];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[i+row][j+col] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
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
									char piece = h.board[row+i][col+j];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[row+i][j+col] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
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
									char piece = h.board[k][l];
									if(piece == 'E' || piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[k][l] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
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
									char piece = h.board[i+1][j+1];
									if(piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[i+1][j+1] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
									}
								}
								if(j > 0)
								{
									char piece = h.board[i+1][j-1];
									if(piece == 'k' || piece == 'h' || piece == 'r' || piece == 'b' || piece == 'q' || piece == 'p' )
									{
										newchilds[ind] = state::createChild(h);
										newchilds[ind].board[i+1][j-1] = newchilds[ind].board[i][j];
										newchilds[ind].board[i][j] = 'E';
										newchilds[ind].parent = &h;
										ind++;
										int childind = ind-1;
										process(newchilds[childind]);
										if(newchilds[childind].getValue() > h.getAlpha())
										{
											h.setAlpha(newchilds[childind].getValue());
											if(!data::isChecked(newchilds[childind], h.getPlayer()))
											{
												h.children.push_back(&newchilds[childind]);
												h.setValue(h.getAlpha());
											}
											if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
											{
												h.setValue(h.getAlpha());
												return;
											}
										}
									}
								}
								char piece = h.board[i+1][j];
								if(piece == 'E' )
								{
									newchilds[ind] = state::createChild(h);
									newchilds[ind].board[i+1][j] = newchilds[ind].board[i][j];
									newchilds[ind].board[i][j] = 'E';
									newchilds[ind].parent = &h;
									ind++;
									int childind = ind-1;
									process(newchilds[childind]);
									if(newchilds[childind].getValue() > h.getAlpha())
									{
										h.setAlpha(newchilds[childind].getValue());
										if(!data::isChecked(newchilds[childind], h.getPlayer()))
										{
											h.children.push_back(&newchilds[childind]);
											h.setValue(h.getAlpha());
										}
										if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
										{
											h.setValue(h.getAlpha());
											return;
										}
									}
								}
								piece = h.board[i+2][j];
								if(piece == 'E' && h.board[i+1][j] == 'E')
								{
									newchilds[ind] = state::createChild(h);
									newchilds[ind].board[i+2][j] = newchilds[ind].board[i][j];
									newchilds[ind].board[i][j] = 'E';
									newchilds[ind].parent = &h;
									ind++;
									int childind = ind-1;
									process(newchilds[childind]);
									if(newchilds[childind].getValue() > h.getAlpha())
									{
										h.setAlpha(newchilds[childind].getValue());
										if(!data::isChecked(newchilds[childind], h.getPlayer()))
										{
											h.children.push_back(&newchilds[childind]);
											h.setValue(h.getAlpha());
										}
										if(h.parent->getBeta() != state::MAXINFINITY && h.parent->getBeta() < h.getAlpha())
										{
											h.setValue(h.getAlpha());
											return;
										}
									}
								}
							}
							break;
					}
				}
			}
    	}
    }

    void create()
    {
    	process(head);
    }

    state getMove()
    {
    	for (int i = 0; i < head.children.size(); ++i)
    	{
    		if(head.children.at(i) != NULL)
    		{
    			if( head.getValue() == head.children.at(i)->getValue())
    			{
    				return *(head.children.at(i));
    			}
    		}
    	}
    }

    void destroy()
    {
    	// destroyTree(head);
    	delete[] newchilds;
    }

    void destroyTree(state & h)
    {
    	for (int i = 0; i < h.children.size(); ++i)
    	{
    		destroyTree(*(h.children.at(i)));
    	}
    	h.children.clear();
    }

    // function to traverse the tree, in order traversal
    void traverse()
    {
    	head.output();
    	for (int i = head.children.size()-1; i >= 0; --i)
    	{
    		if(head.children[i] != NULL)
    			head.children[i]->output();
    		else
    			break;
    	}
    }

};
