#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

 struct game
 {
 	string name;
 	int time;
 }user;
 
game list[100];
int currentAmount = 0;
  
 void sort() 
 {
 	for(int i = 0; i < currentAmount; i++){
 		if(list[i].time == 0)
 			list[i].time = 100000000;
	}
 	
 	for(int i = 1; i < currentAmount; i++)
	{
	 	int j;
	 	int key = list[i].time;
	 	for(j = i-1; j >= 0 ; j--)
		{
		 	if(list[j].time > key)
 				list[j+1].time = list[j].time;
 			else
 				break;
	 	}
	 	list[j + 1].time = key;
	}
 }


void loadData()
{
    ifstream file("data.txt");
    if(file.is_open())
    {
        currentAmount = 0;
        game list1;
        while(file >> list1.name && file >> list1.time)
        {
            list[currentAmount] = list1;
            currentAmount++;
        }   
    }
}

void saveData()
{
    ofstream file("data.txt", ios::trunc);

    if(file.is_open())
    {
        for(int i = 0; i < currentAmount; i++)
        {
            file << list[i].name << " " <<  list[i].time << "\n";
        }
    }
}


void reportData()
{
    system("cls");
    cout << endl << "*************** Players **************" << endl << endl;
    cout << "Rank            Name             Time\n" ;
    cout << "--------------------------------------\n" << endl;
    for(int i = 0; i < currentAmount; i++)
    {
        game g = list[i];
        cout << " " << left << setw(15) << i+1;
        cout << setw(17)  << g.name;
        if(g.time == 100000000)
        	cout << "NULL" << endl << endl;
        else
        	cout << g.time << endl << endl;
    }
    char in = getch();   
}

void addData(game list1)
{
    list[currentAmount] = list1;
    currentAmount++;
    saveData();
}



 bool first = true;
 bool gameover = false;
 int baghi;
 int flagg;
 
typedef enum          
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE = 5,
    YELLOW = 6, WHITE = 7, GRAY = 8, 
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12, 
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;
typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
short setTextColor(const ConsoleColors foreground) 
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}

void setcolor(int f, int b)
{
	Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, (b << 4) | f);
}


void gotoxy(short x, short y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x, y};
	SetConsoleCursorPosition(h, pos);
}

void showmap(int show[10][10] , int map[10][10] , int end)
{
    int i , j ;
    system("cls");
            
    setTextColor(LIGHT_WHITE);
    	    
   
    cout << endl;  
		
    for(i = 0; i < 10 ; i++){
    if(i == 0){
    	setTextColor(LIGHT_BLUE);
    	cout << "   -";
		}
		cout << "----" ;
		}
	cout << endl;	
		
    for(i = 0 ; i < 10 ; i++){
        	
    	setTextColor(LIGHT_BLUE);
    	cout << "  " << " |";
    	    	
    	for(j = 0 ; j < 10 ; j++){
        	if(show [i][j] == 1 || end){
        			
        			if( map[i][j] >= 100) {
        			setTextColor(BLACK);
					cout << " "<< '*' ;
					setTextColor(LIGHT_BLUE);
					cout <<" |";
					}
					else {	
					
					cout << " " ;
					
					if(map[i][j] == 0){
					setTextColor(YELLOW);
					cout<< map[i][j] ;}
					
					else if(map[i][j] == 1){
					setTextColor(LIGHT_PURPLE);
					cout<< map[i][j] ;}
					
				 	else if(map[i][j] == 2){
					setTextColor(LIGHT_GREEN);
					cout<< map[i][j] ;}
					
					else if(map[i][j] == 3){
					setTextColor(BLUE);
					cout<< map[i][j] ;}
					
					else if(map[i][j] == 4){
					setTextColor(RED);
					cout<< map[i][j];}
					
					else
					cout << map[i][j];
					
					setTextColor(LIGHT_BLUE);
					cout << " |";
					}
					
				}		
			else{
				setTextColor(LIGHT_BLUE);
				cout << "   |";}	
		}	
		cout << endl;
		
		for(j = 0 ; j < 10 ; j++){
			if(j == 0){
    		setTextColor(LIGHT_BLUE);
    		cout << "   -";
			}
			cout << "----" ;
			}
		cout << endl;	
   }
   
 }
  
void putbomb(int map[10][10], int bomb , int x , int y)
{
 	
 	srand(time(0));
 	
 	while(bomb){
 		int new_x = rand()%10;
 		int new_y = rand()%10;
 		if(map[new_y][new_x] != 100 && ((x - new_x > 1 || x - new_x < -1) && (y - new_y > 1 || y - new_y < -1))){
 			map[new_y][new_x] = 100;
 			bomb--;
		}
	}
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(map[i][j] != 100){
				int r = 0;
				for(int m = -1; m < 2; m++){
					for(int n = -1; n < 2; n++){
						if(i+m < 0 || i + m >= 10 || j + n < 0 || j + n >= 10)
							continue;
						if(map[i+m][j+n] == 100)
							r++;
					}
				}
				map[i][j] = r;
				
			}
		}
	}
 }

void select(int show[10][10] , int map[10][10], int x , int y)
{ 
	
	if(x < 0 || x >= 10 || y < 0 || y >= 10)
		return;
		
	if(show[x][y])
		return;
		
	if(map[x][y] >= 100){
		setcolor(0, 7);
		gameover = true;
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 10; j++){
				if(map[i][j] == 100){
					gotoxy(i*4+5, j*2+2);
					cout << "*";
				}
			}
		}
		gotoxy(x*4+5, y*2+2);
		setcolor(0, 12);
		cout << "*";
		setcolor(0, 7);
		return;
	}	
		
	show[x][y] = 1;
	
	if(map[x][y] == 0){
		gotoxy(x*4+5, y*2+2);
		setcolor(6, 7);
		cout << map[x][y];
		setcolor(0, 7);
		baghi--;
		
		select(show , map , x + 1 , y);
		select(show , map , x - 1 , y);
		select(show , map , x , y + 1);
		select(show , map , x , y - 1);
		select(show , map , x + 1 , y + 1);
		select(show , map , x + 1 , y - 1);
		select(show , map , x - 1 , y - 1);
		select(show , map , x - 1 , y + 1);
	}
	else if(map[x][y] > 0){
		baghi--;
		gotoxy(x*4+5, y*2+2);
		switch(map[x][y]){
			case 1:
				setcolor(13, 7);
				break;
			case 2:
				setcolor(10, 7);
				break;
			case 3:
				setcolor(1, 7);
				break;
			case 4:
				setcolor(4, 7);
				break;
			case 5:
				setcolor(8, 7);
				break;
			case 6:
				setcolor(5, 7);
				break;
			case 7:
				setcolor(11, 7);
				break;
			case 8:
				setcolor(9, 7);
		}
		cout << map[x][y];
		setcolor(0, 7);
	}
}

void flagger(bool flag[10][10], int show[10][10], int x, int y)
{
	setcolor(8, 7);
	if(flag[x][y]){
		gotoxy(x*4+5, y*2+2);
		cout << " ";
		flagg++;
		flag[x][y] = false;
	}else if(flagg > 0 && !show[x][y]){
		gotoxy(x*4+5, y*2+2);
		cout << "#";
		flagg--;
		flag[x][y] = true;
	}
	gotoxy(0, 22);
	cout << "                    Flags: " << flagg << " ";
	setcolor(0, 7);
	
}
 
 void gameprofmance()
 {
    system("cls");
    game list;
    cout << "-- Enter Data --\n";
    cout << "Enter Name:";
    cin >> list.name;
	system("color 79");
	
    int map[10][10] = {0};
    int show[10][10] = {0};
	bool flag[10][10] = {0};

    int i , bomb=16;
    showmap(show , map , 0);
                           
    flagg = bomb;
	gotoxy(0, 22);
	setcolor(8, 7);
	cout << "                    Flags: " << flagg << " ";  
	setcolor(0, 7);        
    int n = 0;
    int x = 5 , y = 2;
    gotoxy(x-1, y);
    cout << "(";
    gotoxy(x+1, y);
    cout << ")";
	gotoxy(x, y);
	baghi = 100;
	clock_t str;
    do{		    	
    	char c = getch();
    	gotoxy(x-1, y);
    	cout << " ";
    	gotoxy(x+1, y);
    	cout << " ";
		gotoxy(x, y);       
    	switch(c){
    		case 'w':
    			if(y > 2){
    				y -= 2;
				}
				break;
    		case 's':
    			if(y < 20){
    				y += 2;
				}
				break;
    		case 'a':
    			if(x > 5){
    				x -= 4;
				}
				break;
    		case 'd':
    			if(x < 40){
    				x += 4;
				}
				break;
    		case 'f':
    			flagger(flag, show,(x-5)/4, (y-2)/2);
				break;
			case '\r':
				if(first){
					str = clock();
					putbomb(map, bomb, (x-5)/4, (y-2)/2);
					first = false;
				}
				select(show , map , (x-5)/4, (y-2)/2);
				
				                                    
    		
		}
		gotoxy(x-1, y);
    	cout << "(";
    	gotoxy(x+1, y);
    	cout << ")";
		gotoxy(x, y);
	}while(!gameover && baghi != bomb);

	
	gotoxy(0, 23);
	if(!gameover){
		list.time = (clock() - str) / CLOCKS_PER_SEC;
		setTextColor(GREEN);
		cout << endl <<  "   GAME OVER." << "YOU WIN!!!\n" << "   Time: " << list.time << "s" << endl;
		}
	else{
		list.time = 0;
		setTextColor(RED);
		cout << endl <<  "   GAME OVER." << "YOU LOSE!!!\n" << endl;
		}
		system("pause");
	
	
    addData(list);
	
}

 int main()
 {
    while(true)
    {
    	currentAmount = 0;
    	loadData();
    	sort();
    	first = true;
    	gameover = false;
        system("cls");
        system("color 70");
        cout << "-------- Menu ------- \n" << endl;
        cout << "1. New Game\n\n2. Leaderboard\n\n3. Exit\n\n";
        
        char in = getch();

        switch (in)
        {
        case '1': 
		gameprofmance();
            break;
        case '2': reportData();
            break;
        case '3': return 0;
        default: 
            break;
        }
    }
 }