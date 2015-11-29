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
		    head.parent = NULL;
		    return head;
		}

		static bool isChecked(state s, bool player)
		{
			if(player)
			{
				for (int i = 0; i < 8; ++i)
				{
					for (int j = 0; j < 8; ++j)
					{
						switch(s.board[i][j])
						{
							case 'K':
								for (int l = -1; l <= 1; ++l)
								{
									for (int m = -1; m < 1; ++m)
									{
										if(l == 0 && m == 0)
											continue;
										if(s.board[l][m] == 'k')
											return true;
									}
								}
								break;
							case 'Q':
								for(int m = -1, n = -1; m <= 1 && n <= 1 ; m++, n++)
								{
									if (m == 0 && n == 0)
										continue;
									for(int k = i+m, l = j+n;k<8 && k >= 0 && l < 8 && l >= 0;k+=m,l+=n)
									{
										char piece = s.board[k][l];
										if(piece == 'k')
										{
											return true;
										}
										else if (piece == 'E')
										{
											continue;
										}
										else
										{
											break;
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
										if(piece == 'k')
										{
											return true;
										}
										else if (piece == 'E')
										{
											continue;
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
										if(piece == 'k')
										{
											return true;
										}
										else if (piece == 'E')
										{
											continue;
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
										if(piece == 'k')
										{
											return true;
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
										if(piece == 'k')
										{
											return true;
										}
									}
									if(j > 0)
									{
										char piece = s.board[i+1][j-1];
										if(piece == 'k')
										{
											return true;
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
				for (int i = 0; i < 8; ++i)
				{
					for (int j = 0; j < 8; ++j)
					{
						switch(s.board[i][j])
						{
							case 'k':
								for (int l = -1; l <= 1; ++l)
								{
									for (int m = -1; m < 1; ++m)
									{
										if(l == 0 && m == 0)
											continue;
										if(s.board[l][m] == 'K')
											return true;
									}
								}
								break;
							case 'q':
								for(int m = -1; m <= 1; m++)
								{
									for (int n = -1;  n <= 1 ; n++)
									{
										if (m == 0 && n == 0)
											continue;
										for(int k = i+m, l = j+n;k<8 && k >= 0 && l < 8 && l >= 0;k+=m,l+=n)
										{
											char piece = s.board[k][l];
											if(piece == 'K')
											{
												return true;
											}
											else if (piece == 'E')
											{
												continue;
											}
											else
											{
												break;
											}
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
										if(piece == 'K')
										{
											return true;
										}
										else if (piece == 'E')
										{
											continue;
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
										if(piece == 'K')
										{
											return true;
										}
										else if (piece == 'E')
										{
											continue;
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
										if(piece == 'K')
										{
											return true;
										}
									}
								}
								break;
							case 'p':
								if(i < 8)
								{
									if(j < 7)
									{
										char piece = s.board[i+1][j+1];
										if(piece == 'K')
										{
											return true;
										}
									}
									if(j > 0)
									{
										char piece = s.board[i+1][j-1];
										if(piece == 'K')
										{
											return true;
										}
									}
								}
								break;
						}
					}
				}
			}
				
			return false;
		}

		static bool validMove(state s, int startF, int startR, int endF, int endR)
		{

			state tt = s;
            tt.board[endF][endR] = tt.board[startF][startR];
            tt.board[startF][startR] = 'E';
            if(data::isChecked(tt, true))
            {
            	return false;
            }
           
			// only doing for player at first
			char chosenPiece = s.board[startF][startR];
			if(s.board[endF][endR] == 'k' || s.board[endF][endR] == 'q' || s.board[endF][endR] == 'r' || s.board[endF][endR] == 'b' || s.board[endF][endR] == 'h' || s.board[endF][endR] == 'p')
				return false;
			switch(chosenPiece)
			{
				case 'k':
					return (endF-startF == -1 || endF-startF == 1) && (endR-startR == -1 || endR-startR == 1);
					break;
				case 'q':
					if( std::abs((double)endF-startF) == std::abs((double)endR-startR) )
					{
						int dirF = endF - startF > 0 ? 1 : -1, dirR = endR - startR > 0 ? 1 : -1;
						for (int i = startF+dirF, j = startR+dirR; i != endF && j != endR ; i += dirF, j += dirR)
						{
							if(s.board[i][j] != 'E')
								return false;
						}
						return true;
					}
					else if (endF == startF)
					{
						int dirR = endR - startR > 0 ? 1 : -1;
						for (int i = startR+dirR; i != endR; i += dirR)
						{
							if(s.board[startF][i] != 'E')
								return false;
						}
						return true;
					}
					else if (endR == startR)
					{
						int dirF = endF - startF > 0 ? 1 : -1;
						for (int i = startF+dirF; i != endF; i += dirF)
						{
							if(s.board[i][startR] != 'E')
								return false;
						}
						return true;
					}
					else
					{
						return false;
					}
					break;
				case 'r':
					if (endF == startF)
					{
						int dirR = endR - startR > 0 ? 1 : -1;
						for (int i = startR+dirR; i != endR; i += dirR)
						{
							if(s.board[startF][i] != 'E')
								return false;
						}
						return true;
					}
					else if (endR == startR)
					{
						int dirF = endF - startF > 0 ? 1 : -1;
						for (int i = startF+dirF; i != endF; i += dirF)
						{
							if(s.board[i][startR] != 'E')
								return false;
						}
						return true;
					}
					else
					{
						return false;
					}
					break;
				case 'b':
					if( std::abs((double)endF-startF) == std::abs((double)endR-startR) )
					{
						int dirF = endF - startF > 0 ? 1 : -1, dirR = endR - startR > 0 ? 1 : -1;
						for (int i = startF+dirF, j = startR+dirR; i != endF && j != endR ; i += dirF, j += dirR)
						{
							if(s.board[i][j] != 'E')
								return false;
						}
						return true;
					}
					else
					{
						return false;
					}
					break;
				case 'h':
					return ( (std::abs((double)endF-startF) == 2 && std::abs((double)endR-startR) == 1) || (std::abs((double)endF-startF) == 1 && std::abs((double)endR-startR) == 2) );
					break;
				case 'p':
					switch(endR-startR)
					{
						case -1:
						case 1:
							return (endF-startF == -1) && ( s.board[endF][endR] == 'K' || s.board[endF][endR] == 'Q' || s.board[endF][endR] == 'R' || s.board[endF][endR] == 'H' || s.board[endF][endR] == 'B' || s.board[endF][endR] == 'P');
							break;
						case 0:
							return ((endF-startF == -1 || (endF-startF == -2 && startF == 6 && s.board[endF+1][endR] == 'E')) &&  ( s.board[endF][endR] == 'E'));
							break;
						default:
							return false;
							break;
					}
					break;
				default:
					return false;
					break;
			}
		}

};