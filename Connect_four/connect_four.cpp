#include <iostream>
#include <string>

using namespace std;

void Player1();
void Player2();
void Grid(); 
void initialiseGrid();
char array[8][9]; //array of [8][9] instead of [6][7] to ensure that the next column is 'blank' (otherwise problems when checking the diagonals)
int e=5, f=5, g=5, h=5, m=5, n=5, p=5;
int a=0, k=0, l=0;

int main()
{
	initialiseGrid();
	Grid();
	
	while (a==0)
	{
		Player1();//Function for player O's move
		
		for (k=0; k<6; k++)
		{	
			for (l=0; l<7; l++)
			{
				if(((array[k][l]=='O')&&(array[k][l]==array[k+1][l])&&(array[k+1][l]==array[k+2][l])&&(array[k+2][l]==array[k+3][l]))|| //check vertical
				((array[k][l]=='O')&&(array[k][l]==array[k][l+1])&&(array[k][l+1]==array[k][l+2])&&(array[k][l+2]==array[k][l+3]))|| //check horizontal
				((array[k][l]=='O')&&(array[k][l]==array[k+1][l+1])&&(array[k+1][l+1]==array[k+2][l+2])&&(array[k+2][l+2]==array[k+3][l+3]))||//check diagonal down
				((array[k][l]=='O')&&(array[k][l]==array[k-1][l+1])&&(array[k-1][l+1]==array[k-2][l+2])&&(array[k-2][l+2]==array[k-3][l+3]))) //check diagonal up
				//Verify every combination possible
				
				{
					a=1;
				}
			}
		}
		Grid();
		
		if (a==0)//check if O hasn't won before letting player X play
		{
			
		Player2();//Function for player X's move
		
			for (k=0; k<6; k++)
				{
				for (l=0; l<7; l++)
					{
						if(((array[k][l]=='X')&&(array[k][l]==array[k+1][l])&&(array[k+1][l]==array[k+2][l])&&(array[k+2][l]==array[k+3][l]))||
						((array[k][l]=='X')&&(array[k][l]==array[k][l+1])&&(array[k][l+1]==array[k][l+2])&&(array[k][l+2]==array[k][l+3]))||
						((array[k][l]=='X')&&(array[k][l]==array[k+1][l+1])&&(array[k+1][l+1]==array[k+2][l+2])&&(array[k+2][l+2]==array[k+3][l+3]))||
						((array[k][l]=='X')&&(array[k][l]==array[k-1][l+1])&&(array[k-1][l+1]==array[k-2][l+2])&&(array[k-2][l+2]==array[k-3][l+3])))//Verify if X wins
							   {
								   a=2;
							   }
					}
				}
		Grid();
		}
		if (a==0)//check if there is not a tie
		{
			if((array[0][0]!=' ')&&(array[0][1]!=' ')&&(array[0][2]!=' ')&&(array[0][3]!=' ')&&(array[0][4]!=' ')&&
			(array[0][5]!=' ')&&(array[0][6]!=' '))
			{
			   a=3;
			}
		}
	}

	switch(a)
	{
		case 1:
		cout<<"\nThe winner is player O!"<<endl;
		break;
		case 2:
		cout<<"\nThe winner is player X!"<<endl;
		break;
		case 3:
		cout<<"\nIt's a tie!"<<endl;
		break;
	}
}

void Player1() 
{
	int time=0;
	int x;
	cout<<"\n";
	cout<<"Choose a column Player O: ";
	cin>>x;
	while (time==0)//Plays until the value is valid
	{
		switch(x)
		{
			case 1:
			if (array[0][0]==' ')//check that the column isn't already full
			{
				array[e][0]='O';
				e=e-1;//The next time column one is selected, the value will be placed on the column above
				time=1;
			}
			else
			{
				cout<<"Column 1 is already full, select another one"<<endl;
				cin>>x;
			}
			break;
			case 2:
			if (array[0][1]==' ')
			{
				array[f][1]='O';
				f=f-1;
				time=1;
			}
			else
			{
				cout<<"Column 2 is already full, select another one"<<endl;
				cin>>x;
			}
			break;
			case 3:
			if(array[0][2]==' ')
			{
				array[g][2]='O';
				g=g-1;
				time=1;
			}
			else
			{
				cout<<"Column 3 is already full, select another one"<<endl;
				cin>>x;
			}
			break;
			case 4:
			if(array[0][3]==' ')
			{
				array[h][3]='O';
				h=h-1;
				time=1;
			}
			else
			{
				cout<<"Column 4 is already full, select another one"<<endl;
				cin>>x;
			}
			break;
			case 5:
			if(array[0][4]==' ')
			{
				array[m][4]='O';
				m=m-1;
				time=1;
			}
			else
			{
				cout<<"Column 5 is already full, select another one"<<endl;
				cin>>x;
			}
			break;
			case 6:
			if(array[0][5]==' ')
			{
				array[n][5]='O';
				n=n-1;
				time=1;
			}
			else
			{
				cout<<"Column 6 is already full, select another one"<<endl;
				cin>>x;
			}
			break;
			case 7:
			if(array[0][6]==' ')
			{
				array[p][6]='O';
				p=p-1;
				time=1;
			}
			else
			{
				cout<<"Column 7 is already full, select another one"<<endl;
				cin>>x;
			}
			break;
			default:
			cout<<"The value entered is invalid, type again: "<<endl;
			cin.clear();
			cin.ignore(100,'\n');
			cin>>x;
			break;
		}
	}
}
	

void Player2()//Same function as Player1 only instead of O's, it's X's
{
	int time2=0;
	int x;
	cout<<"\n";
	cout<<"Choose a column Player X: ";
	cin>>x;
	while(time2==0)
	{
		switch(x)
		{
			case 1:
			if(array[0][0]==' ')
			{
				array[e][0]='X';
				e=e-1;
				time2=1;
			}
			else 
			{
				cout<<"Column 1 is already full, select another value"<<endl;
				cin>>x;
			}
			break;
			case 2:
			if (array[0][1]==' ')
			{
				array[f][1]='X';
				f=f-1;
				time2=1;
			}
			else 
			{
				cout<<"Column 2 is already full, select another value"<<endl;
				cin>>x;
			}
			break;
			case 3:
			if (array[0][2]==' ')
			{
				array[g][2]='X';
				g=g-1;
				time2=1;
			}
			else 
			{
				cout<<"Column 3 is already full, select another value"<<endl;
				cin>>x;
			}
			break;
			case 4:
			if (array[0][3]==' ')
			{
				array[h][3]='X';
				h=h-1;
				time2=1;
			}
			else 
			{
				cout<<"Column 4 is already full, select another value"<<endl;
				cin>>x;
			}
			break;
			case 5:
			if (array[0][4]==' ')
			{
				array[m][4]='X';
				m=m-1;
				time2=1;
			}
			else 
			{
				cout<<"Column 5 is already full, select another value"<<endl;
				cin>>x;
			}
			break;
			case 6:
			if (array[0][5]==' ')
			{
				array[n][5]='X';
				n=n-1;
				time2=1;
			}
			else 
			{
				cout<<"Column 6 is already full, select another value"<<endl;
				cin>>x;
			}
			break;
			case 7:
			if (array[0][6]==' ')
			{
				array[p][6]='X';
				p=p-1;
				time2=1;
			}
			else 
			{
				cout<<"Column 7 is already full, select another value"<<endl;
				cin>>x;
			}
			break;
			default:
			cout<<"The value entered is invalid, type again"<<endl;
			cin.clear();
			cin.ignore(100,'\n');
			cin>>x;
			break;
		}	
	}
}

void Grid ()//prints the grid with the array inside
{
	int r=0;
	int c=0;
	cout<<" 1 2 3 4 5 6 7"<<endl;
	for (r=0; r<6; ++r)
	{
		for (c=0; c<7; ++c)
		{
			{
				cout<<"|"<<array[r][c];
			}
		}
		cout<<"|"<<endl<<"---------------";
		cout<<"\n";
	}
}
void initialiseGrid()//initialises the array to ' ', for it to start blank.
{
	int i=0;
	int j=0;
	cout<<"Connect four game"<<endl;
	for (i=0; i<8; ++i)
    {
		for (j=0; j<9; ++j)
		{
		  array[i][j]= ' ';
		}
	}	
}	