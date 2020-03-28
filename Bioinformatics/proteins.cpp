#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Protein
{
	int item_id;
	string gi_id;
	string ref_id;
	string name_of_protein;
	string protein_sequ;
};

void Display_menu(); //function to display the main menu
void Search_hit(); //function to display the sub-menu
void Count_number(ifstream* funct); //function to count the number of proteins in the database
void Display_amino(); //function that displays a table to associate each amino acid to a letter
void Display_protein(Protein name); //function to do the description of the protein
void Protein_sequence(Protein seq); //function to display the protein sequence
void Protein_stat(Protein amino); //function to count the number of each amino acid in one protein
void Record (Protein file); // function to save the protein in a separate file
void Default(); //function to display the proper message when the value entered in menu or sub-menu is invalid

int record = 0;//this is a global variable on purpose so that in the function "Record" it increments properly

int main()
{
	int x;
	vector<Protein> v1;
	
	cout<<"\nWelcome to the Protein Database"<<endl;
	cout<<endl;
	cout<<"Choose option 1) to load the abridged protein file"<<endl;
	cout<<"       option 2) to load the complete protein file"<<endl;
	cout<<"       option 3) Quit the database"<<endl;
	cin>>x;
	
	string pt;
	int a=0;
	while(a==0)//permits to have a string containing the database selected by the user
	{
		if (x==1)
		{
			pt = "protein_a.fa";
			a=1;
		}
		else if (x==2)
		{
			pt = "protein_c.fa";
			a=1;
		}
		else if(x==3)
		{
			return 0;
		}
		 else
		{
		Default();
		cin>>x;
		}
	}
	
	ofstream fout;
	fout.open("selected_proteins.txt", ios::trunc); //this erases the contents of the file "selected_proteins.txt",
	fout.close();									//so that the record of any previous proteins is eliminated.
	Protein selected;
	ifstream fs;
	ifstream file;
	fs.open(pt.c_str()); //opens the database selected
	cout<<"Loading database...";
	int count1 = 1;
	while(!fs.eof()) //load the database in vector v1
	{
		fs.ignore(1000, '|');
		getline(fs, selected.gi_id, '|');
		fs.ignore(1000, '|');
		getline(fs, selected.ref_id, '|');
		fs.ignore(1000, ' ');
		getline(fs, selected.name_of_protein, '\n');
		getline(fs, selected.protein_sequ, '>');
		selected.item_id=count1;
		count1++;
		v1.push_back(selected);
	}
	cout<<"\nDatabase loaded."<<endl;
	int time=0;
	while(time==0)//goes to main menu until the user decides to quit the program
	{
		Display_menu();
		
		int y;
		cin>>y;
	
		if(y==1) //count number of proteins + overview of the database
		{
			file.open(pt.c_str());
			Count_number(&file);
			Display_amino();
		}
		
		else if (y==2) //Search by item ID
		{
			int z;
			Protein pro;
			cout<<"Enter an item ID: ";
			int ut=0;
			while(ut==0)//checks if the item ID is valid
			{
				cin>>z;
				if((z>0)&&(z<=v1.size()))
				{
					pro = v1[z-1];
					ut=1;
				}
				else 
				{
					cout<<"This item ID does not exist, please select another one: ";  
					cin.clear();
					cin.ignore(100,'\n');
				}
			}
			
			int b = 0;
			while(b==0)//goes to sub menu until the user wants to go to the main menu
			{
				Search_hit();
				int x;
				cin>>x;
				switch (x) //for every switch in the main, each case are the same thing
				{
					case 1:
					Display_protein(pro);
					break;
					case 2:
					Protein_sequence(pro);
					break;
					case 3:
					Protein_stat(pro);
					break;
					case 4:
					Record (pro);
					break;
					case 5:
					b=1;
					break;
					default:
					Default();
				}
			}
		}
		
		else if(y==3)//Search by gi id
		{
			string z;
			Protein pro;
			cout<<"Enter a gi id: ";
			cin>>z;
			
			int i;
			Protein print;
			for(i=0; i < v1.size(); i++)
			{
				pro=v1[i];
				if(pro.gi_id == z)
				{
					print = pro;
				
				}
			}
			int c = 0;
			while(c==0)
			{
				Search_hit();
				int x;
				cin>>x;
				switch (x)
				{
					case 1:
					Display_protein(print);
					break;
					case 2:
					Protein_sequence(print);
					break;
					case 3:
					Protein_stat(print);
					break;
					case 4:
					Record (print);
					break;
					case 5:
					c=1;
					break;
					default:
					Default();
				}
			}
		}
		
		else if(y==4)//Search by ref id
		{
			string z;
			Protein pro;
			cout<<"Enter a ref id: ";
			cin>>z;
			
			int i;
			Protein print;
			for(i=0; i < v1.size(); i++)
			{
				pro=v1[i];
				if(pro.ref_id == z)
				{
					print = pro;
				}
			}
			int d = 0;
			while (d == 0)
			{
				Search_hit();
				int x;
				cin>>x;
				switch (x)
				{
					case 1:
					Display_protein(print);
					break;
					case 2:
					Protein_sequence(print);
					break;
					case 3:
					Protein_stat(print);
					break;
					case 4:
					Record (print);
					break;
					case 5:
					d=1;
					break;
					default:
					Default();
				}
			}
		}
		else if(y==5)//Search by keyword
		{
			string z;
			string npos;
			Protein pro;
			Protein chosen;
			int i,j, t,r,u;
			vector<Protein> v2;
			int k=0;
			
			
			cout<<"Enter a keyword: ";
			cin>>z;
			while (k==0)
			{
				t=0;
				j=1;
				for(i=0; i<v1.size(); i++)
				{
					pro=v1[i];
					size_t found = pro.name_of_protein.find(z);
					if (found!=std::string::npos)
					{
						t=t+1;
						pro.item_id = i+1;
						v2.push_back(pro);
					}
				}
				cout<<"\nNumber of matches found: "<<t<<endl;
				for(r=0; r<v2.size(); r++)
				{
					pro=v2[r];
					cout<<r+1<<") item id: "<<pro.item_id<<", gi id: "<<pro.gi_id<<", ref id: "<<pro.ref_id<<endl<<pro.name_of_protein<<endl;
				}
				if(r==0)//In case no matches are found
				{
					cout<<"No matches were found, type 1 to try again or 0 to go to main menu";
					int h;
					cin.clear();
					cin.ignore(100,'\n');
					cin>>h;
					if(h==1)
					{
						
						cout<<"Enter a keyword: ";
						cin.clear();
						cin.ignore(100,'\n');
						cin>>z;
					}
					else if(h==1)
					{
						k=1;
					}
				}
				if(r==1)//In case one match is found
				{
					cout<<"\nOne match was found. Is this the protein you are looking for?"<<endl;
					cout<<"Type 1 if yes, 0 to go to main menu: ";
					int o;
					cin>>o;
					if (o==1)
					{
						Protein chosen;
						chosen = v2[0];
						int e=0;
						while(e==0)
						{
							Search_hit();
							k=1;
							int x;
							cin>>x;
							switch (x)
							{
								case 1:
								Display_protein(chosen);
								break;
								case 2:
								Protein_sequence(chosen);
								break;
								case 3:
								Protein_stat(chosen);
								break;
								case 4:
								Record (pro);
								break;
								case 5:
								e=1;
								break;
								default:
								Default();
							}
						}
					}
				k=1;
				}
				else //The case were multiples matches are found
				{
				cout<<"\nSelect one of the matches. If you are enable to find your protein, type 0 to go to main menu : ";
				cin>>u;
				
					if((u!=0)&&(u <= v2.size() +1))
					{
						chosen = v2[u-1];
						int e=0;
						while(e==0)
						{
							Search_hit();
							k=1;
							int x;
							cin>>x;
							switch (x)
							{
								case 1:
								Display_protein(chosen);
								break;
								case 2:
								Protein_sequence(chosen);
								break;
								case 3:
								Protein_stat(chosen);
								break;
								case 4:
								Record (pro);
								break;
								case 5:
								e=1;
								break;
								default:
								Default();
							}
						}		
					}
				k=1;
				}
			}
		}
		
		else if(y==6) //Quit the program
		{
			time = 1;
		}
		else //If the value entered by the user is invalid
		{
			Default();
			cin>>x;
		}
	}  
	fs.close();
	return 0;
}

void Display_menu()
{
	cout<<"\nMAIN MENU: Select from the following options by entering a value between 1 and 6"<<endl;
	cout<<"1. Overview of the database"<<endl;
	cout<<"2. Search by item id"<<endl;
	cout<<"3. Search by gi id"<<endl;
	cout<<"4. Search by ref id"<<endl;
	cout<<"5. Search by keyword"<<endl;
	cout<<"6. Quit database"<<endl;
}

void Search_hit()
{
	cout<<"\nSEARCH HIT MENU: Select from the following options by entering a number between"<<endl;
	cout<<" 1 and 5"<<endl;
	cout<<"1. Description of the protein"<<endl;
	cout<<"2. Protein sequence"<<endl;
	cout<<"3. Protein statistics"<<endl;
	cout<<"4. Record protein to file"<<endl;
	cout<<"5. Return to main menu"<<endl;
}

void Count_number(ifstream* funct)
{
	int count=0;
	char line;
	while((*funct)>>line)
	{
		if(line == '>')
		  {
			count = count + 1;
		  }
	}
	cout<<"\nThe proteins in the database are from GenBank(R)"<<endl;
	cout<<"The total number of proteins in the selected database is: "<<count;
}

void Display_amino()
{
	cout<<"\nAmino acids are represented by the following characters: "<<endl;
	cout<<"A: alanine               P: proline"<<endl;
	cout<<"B: aspartate/aspargine   Q: glutamine"<<endl;
	cout<<"C: cystine               R: arganine"<<endl;
	cout<<"D: aspartate             S: serine"<<endl;
	cout<<"E: glutamate             T: threonine"<<endl;
	cout<<"F: phenylalanine         U: selenocysteine"<<endl;
	cout<<"G: glycine               V: valine"<<endl;
	cout<<"H: histidine             W: tryptophan"<<endl;
	cout<<"I: isoleucine            Y: tyrosine"<<endl;
	cout<<"K: lysine                Z: glutamate/glutamine"<<endl;
	cout<<"L: leucine               X: any"<<endl;
	cout<<"M: methionine            *: translation stop"<<endl;
	cout<<"N: asparagine            -: gap of indeterminate length"<<endl;
}

void Display_protein(Protein name)
{
 cout<<"\nDescription of the protein:"<<endl;
 cout<<"The item id is: "<<name.item_id<<endl;
 cout<<"The gi id is: "<<name.gi_id<<endl;
 cout<<"The ref id is: "<<name.ref_id<<endl;
 cout<<"The name of the protein is: "<<endl<<name.name_of_protein<<endl;
}

void Protein_sequence(Protein seq)
{
	cout<<"\nThe protein sequence is: "<<endl<<seq.protein_sequ<<endl;
}

void Protein_stat(Protein amino)
{	
	int it;
	int a = 0, b=0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, k = 0, l = 0, m = 0, n = 0, p = 0;
	int q = 0, r = 0, s = 0, t = 0, u = 0, v = 0, w = 0, x = 0,  y = 0, z = 0;
	int star = 0;
	int gap = 0;
	int count= 0;
	
	string letter;
	char number;
	letter = amino.protein_sequ;
	for (it=0; it<letter.length(); it++)
	{
		number = letter[it];
		switch(number)
		{
			case 'A':
			a++;
			count++;
			break;
			case 'B':
			b++;
			count++;
			break;
			case 'C':
			c++;
			count++;
			break;
			case 'D':
			d++;
			count++;
			break;
			case 'E':
			e++;
			count++;
			break;
			case 'F':
			f++;
			count++;
			break;
			case 'G':
			g++;
			count++;
			break;
			case 'H':
			h++;
			count++;
			break;
			case 'I':
			i++;
			count++;
			break;
			case 'K':
			k++;
			count++;
			break;
			case 'L':
			l++;
			count++;
			break;
			case 'M':
			m++;
			count++;
			break;
			case 'N':
			n++;
			count++;
			break;
			case 'P':
			p++;
			count++;
			break;
			case 'Q':
			q++;
			count++;
			break;
			case 'R':
			r++;
			count++;
			break;
			case 'S':
			s++;
			count++;
			break;
			case 'T':
			t++;
			count++;
			break;
			case 'U':
			u++;
			count++;
			break;
			case 'V':
			v++;
			count++;
			break;
			case 'W':
			w++;
			count++;
			break;
			case 'Y':
			y++;
			count++;
			break;
			case 'Z':
			z++;
			count++;
			break;
			case 'X':
			x++;
			count++;
			break;
			case '*':
			star++;
			count++;
			break;
			case '-':
			gap++;
			count++;
			break;	
		}
	}
	cout<<"\nThe total number of amino acids: "<<count<<endl;
	cout<<"A "<<a<<"	P "<<p<<endl;
	cout<<"B "<<b<<"	Q "<<q<<endl;
	cout<<"C "<<c<<"	R "<<r<<endl;
	cout<<"D "<<d<<"	S "<<s<<endl;
	cout<<"E "<<e<<"	T "<<t<<endl;
	cout<<"F "<<f<<"	U "<<u<<endl;
	cout<<"G "<<g<<"	V "<<v<<endl;
	cout<<"H "<<h<<"	W "<<w<<endl;
	cout<<"I "<<i<<"	Y "<<y<<endl;
	cout<<"K "<<k<<"	Z "<<z<<endl;
	cout<<"L "<<l<<"	X "<<x<<endl;
	cout<<"M "<<m<<"	* "<<star<<endl;
	cout<<"N "<<n<<"	- "<<gap<<endl;
}

void Record (Protein file)
{
	ofstream ft;
	ft.open("selected_proteins.txt", ios::app);
	ft<<record+1<<")"<<"Item id: "<<file.item_id<<endl;
	ft<<"Gi id: "<<file.gi_id<<endl;
	ft<<"Ref id: "<<file.ref_id<<endl;
	ft<<"Name of the protein: "<<file.name_of_protein<<endl;
	ft<<"Protein sequence: "<<file.protein_sequ<<endl;
	record++;
	ft.close();
	cout<<"\nThe protein was written to file"<<endl;
}

void Default()
{
	cout<<"The value entered is invalid, please type again: "<<endl;
	cin.clear();
	cin.ignore(100,'\n');
}