#include <bits/stdc++.h>
#include <ncurses.h>
using namespace std;

void print_page(vector<string> v){
	clear();
	for(int i=0;i<v.size();i++)
             printw("%s\n",v[i].c_str());
       		
	refresh();
}
int main(int argc, char **argv){
	string file;
	if(argc<=1){
		cout << "Entre the file name : "<<endl;
		cin >> file;}
	else file = argv[1];

	vector<string> v;
	string line;
	
	ifstream fin(file);
	while(getline(fin,line))
		v.push_back(line);
	
	fin.close();ofstream fout;
	fout.open(file);

	initscr();raw();				
	keypad(stdscr, TRUE);noecho();			
	
	print_page(v);
	int x = 0,y = 0;
	move(y,x);string s;v.push_back(s);
	while(true){
		move(x,y);string c;
		int ascii = getch();
		if(ascii==27){
			for(int i=0;i<v.size();i++){
				line = v[i];fout << line <<endl;
			}
			break;
		}
		c=ascii;
		switch(ascii){

			case KEY_RIGHT :if(y<v[x].size())
					   y++;
				        break;
					
			case KEY_LEFT : if(y>0)
					    y--;
				        break;
					
			case KEY_UP :	if(x>0)
                                           x--;
                                      if(y>v[x].size())
				          y=v[x].size();
				       break;
				      
			case KEY_DOWN : if(x<v.size()-1)
                                              x++;
                                                
						if(y>v[x].size())
                                                        y=v[x].size();
                                              break;
					
			case KEY_DC : if(y<v[x].size())
						v[x].erase(y,1);
						
					else if(y==v[x].size()){
						if(x<v.size()-1){
							string next = v[x+1];v[x].insert(y,next);
								v.erase(v.begin()+x+1);
							}
						}	
						break;
					
			case KEY_BACKSPACE : if(y>0){
						      v[x].erase(y-1,1);
							y--;}
						
						else if(y==0){
							if(x>0){
								string curr = v[x];v.erase(v.begin()+x);
								x--;y=v[x].size();v[x].insert(y,curr);
							}
						}	
						break;
					     
			case '\t' :	v[x].insert(y,"        "); 
					y+=8; break;
				    
			case '\n' :{	
					 if(y<v[x].size()){						   
						   v.insert(v.begin()+x+1,v[x].substr(y,v[x].size()));
						   v[x].erase(y,v[x].size()-y);
					 }
					 else if(y==v[x].size()){
						   string temp;
                                                   v.insert(v.begin()+x+1,temp);
					   }
                        		x++;y=0;
				   }	
					break;
			default: 		
					v[x].insert(y,c);
                        		y++;
					if(c=="(")v[x].insert(y,")");
					if(c=="{")v[x].insert(y,"}");
					if(c=="[")v[x].insert(y,"]");
					if(c=="\"")v[x].insert(y,"\"");
					if(c=="'")v[x].insert(y,"'");
					break;
				 
		}
		print_page(v);
	}
	endwin();
	
	for(int i=0;i<v.size();i++){
		cout << v[i] << endl;
	}
	fout.close();
	return 0;
}

