#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Cell
{
	protected:
		vector <vector <char> > vtemp; 
	public:
		Cell(); //default constructor
		Cell(const Cell& pt_vcopy); //copy 
		~Cell();

		virtual void change_temp(vector <vector <char> > v2); // checks on the actual board and the changes are made on the temporary board
		virtual vector <vector <char> > get_tempboard() {return vtemp;}; // function to get the temporary board
};

Cell::Cell()
{
	vector <char> vd;
	vd.push_back(' ');
	vtemp.push_back(vd);
}

Cell::Cell(const Cell& pt_vcopy)
{
	cout<<"Cell:: copy constructor"<<endl;
	vtemp = pt_vcopy.vtemp;
}

Cell::~Cell()
{
	//destructor
}

void Cell::change_temp(vector <vector <char> > v2)
{
	vtemp=v2;
	int i;
	int j;
	int n, m;
	int count;
	for (i=1; i<=20; ++i)
    {
		for (j=1; j<=75; ++j)
		{
			if (v2[i][j]=='O')//Overpopulation and loneliness
			{
				count=-1;
				n=0;
				m=0;
				for(n=(i-1); n<=(i+1); ++n)
				{
					for(m=(j-1); m<=(j+1); ++m)
					{
						if (v2[n][m]=='O')
						{
							count = count+1;
						}
					}
				}
				if((count>=4)||(count<=1))
				{
					vtemp[i][j]= ' ';
				}
			}
				
			if(v2[i][j]==' ') //Birth
			{
				count=0;
				n=0;
				m=0;
				for(n=(i-1); n<=(i+1); ++n)
				{
					for(m=(j-1); m<=(j+1); ++m)
					{
						if (v2[n][m]=='O')
						{
							
							count = count+1;
						}
					}
				}
				if(count==3)
				{
					vtemp[i][j]= 'O';
				}
			}
		}
	}
}

class Cancer : public Cell
{
	public:
		Cancer();
		Cancer(const Cancer& pt_vcopy);
		~Cancer();
		
		void change_temp(vector <vector <char> > v2); //same functions as in cell
		vector <vector <char> > get_tempboard() {return vtemp;};
};

Cancer::Cancer()
{
	vector <char> vd;
	vd.push_back(' ');
	vtemp.push_back(vd);
}

Cancer::Cancer(const Cancer& pt_vcopy)
{
	cout<<"Cancer:: copy constructor"<<endl;
	vtemp = pt_vcopy.vtemp;
}

Cancer::~Cancer()
{
	//destructor
}

void Cancer::change_temp(vector <vector <char> > v2)
{
	vtemp=v2;
	int i;
	int j;
	int n;
	int m;
	int count;
	for (i=1; i<=20; ++i)
    {
		for (j=1; j<=75; ++j)
		{
			if (v2[i][j]=='X')//Overpopulation and loneliness
			{
				count=-1;
				n=0;
				m=0;
				for(n=(i-1); n<=(i+1); ++n)
				{
					for(m=(j-1); m<=(j+1); ++m)
					{
						if (v2[n][m]=='X')
						{
							count = count+1;
						}
					}
				}
				if((count>=5)||(count<=1))
				{
					vtemp[i][j]= ' ';
				}
			}
				
			if(v2[i][j]==' ') //Birth
			{
				count=0;
				n=0;
				m=0;
				for(n=(i-1); n<=(i+1); ++n)
				{
					for(m=(j-1); m<=(j+1); ++m)
					{
						if (v2[n][m]=='X')
						{
							
							count = count+1;
						}
					}
				}
				
				if(count==3)
				{
					vtemp[i][j]= 'X';
				}
			}
		}
	}
}

class Board
{
	private:
		int menu;
		vector <vector <char> > varray;
		vector <char>v2;
		int time;
		int row;
		int column;
		int r;
		int n;
	public:
		Board();//default constructor
		Board(int x, int y); //initialises a board of row size x and column size y to ' ' (blank board)
		~Board();
		int get_time() {return time;}; 
		int get_num_cells();
		
		void seed_cells(int s, double c);//Sets the board: time 0
		void display(); //display board
		void next_state(); //Function to get the board at the next state
		void set_newboard(vector <vector <char> > v5); //Function to set the board to the next state
};

Board::Board()
{
	v2.push_back(0);
	varray.push_back(v2);
}

Board::~Board()
{
	//destructor
}
Board::Board(int x, int y)
{
	int i=0;
	int j=0;
	for (i=0; i<x; ++i)
    {
		for (j=0; j<y; ++j)
		{
			v2.push_back(' ');
		} 
		varray.push_back(v2);
	}	
}

void Board::seed_cells (int s, double c)
{
	menu = s;
	time = 0;
	srand(1);
	n = (c/100)*1500;
	for (r=0; r<n; ++r)
	{
		row = (rand() %20) +1;
		column = (rand() %75)+1 ;
		if(varray[row][column] == ' ')
		{	
			if (s==1)
			{
				varray[row][column] = 'O'; 
			}
			else if(s==2)
			{
				varray[row][column] = 'X'; 
			}
		}
		else
		{
			r = r-1;
		}
	}
}

void Board::display()
{
	int i=0;
	int  j=0;
	for (i=1; i<21; ++i)
	{
		for (j=1; j<76; ++j)
		{
			cout<<varray[i][j];
		} 
		cout<<endl;
	}	
}

void Board::set_newboard(vector <vector <char> > v5)
{
	varray=v5;
}

void Board::next_state()
{
	if (menu==1)
	{
		Cell test;
		test.change_temp(varray); //goes into cell to set the temporary board to the next state
		set_newboard(test.get_tempboard()); //set the actual board to the next set (equal to the temporary board)
	}
	else if(menu==2)
	{
		Cancer test2;
		test2.change_temp(varray);
		set_newboard(test2.get_tempboard());
	}
	time=time+1;
}

int Board::get_num_cells()
{
	int i=0;
	int j=0;
	int y = 0;
	char t;
	for (i=1; i<21; i++)
	{
		for (j=1; j<76; j++)
		{
		  if(varray[i][j] != ' ')
		  {
			  y = y +1;
		  }
		}
	}		
	return y;
}

int main()
{
	int selection;
	double confluence;
	int x =0;
	int c;
	Board board(22,77);
	string trash;
	
	cout<<"\nWelcome to the cell simulator"<<endl;
	cout<<"Select your cell type: 1) normal cells"<<endl;
	cout<<"                       2) cancer cells"<<endl<<">";
	cin>>selection;
	while (x == 0)
	{
		switch(selection)
		{
		case 1:
		x=1;
		break;
		case 2:
		x=1;
		break;
		default:
		cout<<"The value entered is invalid, type again: "<<endl;
		cin.clear();
		cin.ignore(100,'\n');
		cin>>selection;
		break;
		}	
	}
	
	cout<<"Select the confluence percentage (%)"<<endl<<">";
	cin>> confluence;
	x=0;
	while (x == 0)
	{
		if ((confluence >= 0) && (confluence <= 100))
		{
			x=1;
		}
		else
		{
			cout<<"The value entered is invalid, type again: "<<endl;
			cin.clear();
			cin.ignore(100,'\n');
			cin>>confluence;
		}
	}
	getline(cin,trash);
	board.seed_cells(selection, confluence);
	system("cls");
	while(c!='q')
	{
		system("cls");
		cout<<"time:            "<<board.get_time()<<endl;
		cout<<"number of cells: "<<board.get_num_cells()<<endl;
		board.display();
		c = cin.get();
		board.next_state();
	}
	return 0;
}