

//const int so_item = 8;
//const int dong =1;
//const int cot = 1 ;
const int Up = 72; 
const int Down = 80;

void Normal (int val1, int val2) {
	SetColor(val1);
	SetBGColor(val2);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void HighLight () {
	SetColor(15); 
//	system("Color F3");// system("Color F3"); F for background color and 3 for text color
	SetBGColor(1);
}


void BaoLoi (char *s){
  int x=wherex() , y=wherey();
  gotoxy (10,24);
  cout <<s;
  Sleep(2000);
  gotoxy(10,24);
  clreol();
  gotoxy(x,y);
}



int MenuDong(char td [so_item][50]){
Normal(15,0);
  clrscr();
  int chon =0;
  
  
  for (int i=0; i< so_item ; i++)
  { gotoxy(horizonMenu, vertiMenu +i);
    cout << td[i];
  }
  
 
  gotoxy(horizonMenu, vertiMenu +chon);
 	HighLight();  
    cout << td[chon];
  
  char kytu;
do {
  kytu = getch();
  if (kytu==0) kytu = getch();
  switch (kytu) {
    case Up :if (chon+1 >1)
  			  {
  		        Normal(15,0); // 15= white : text ; 0= black : bg
              	gotoxy(horizonMenu, vertiMenu +chon);
              	cout << td[chon];
              	chon --;
              	HighLight();
              	gotoxy(horizonMenu, vertiMenu +chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal(15,0);
              	gotoxy(horizonMenu, vertiMenu +chon);
              	cout << td[chon];
              	chon ++;
              	HighLight();
              	gotoxy(horizonMenu, vertiMenu +chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case 13 : return chon+1;
  }  // end switch
  } while (1);
}








