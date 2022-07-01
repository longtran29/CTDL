int xKeyDisplay[7] = { 1,20,45,63,83,95, 107 };

const int so_item = 8;
const int dong =1;
const int cot = 1 ;
const int Up = 72; 
const int Down = 80;

void Normal (int val1, int val2) {
	SetColor(val1);
	SetBGColor(val2);
}


void HighLight () {
	SetColor(15);
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
  system("cls");   int chon =0;
  int i; 
  for ( i=0; i< so_item ; i++)
  { gotoxy(cot, dong +i);
    cout << td[i];
  }
  HighLight();
  gotoxy(cot,dong+chon);
  cout << td[chon];
  char kytu;
do {
  kytu = getch();
  if (kytu==0) kytu = getch();
  switch (kytu) {
    case Up :if (chon+1 >1)
  			  {
  		        Normal(15,0);
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon --;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal(15,0);
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon ++;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case 13 : return chon+1;
  }  // end switch
  } while (1);
}


void Display(string content[], int numContent) {
	
	// mau vang

	system("color 0E");
	Normal(14,0);
	for(int i=0; i< numContent; i++) {
		gotoxy(xKeyDisplay[i] + 3, 4);
		cout<<content[i];
	}
	
	

}







