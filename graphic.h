

#include <Windows.h>
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
  gotoxy (10,27);
  cout <<s;
  Sleep(2000);
  gotoxy(10,27);
  clreol();
  gotoxy(x,y);
  getch();
}


int repeate(char* title, char* content) {

	 if (MessageBoxA(NULL,content, title, MB_YESNO) == IDYES)
    {
//        MessageBoxA(NULL,"YES pressed","",MB_OK);
		return 1;
    }
    else
    {
//        MessageBoxA(NULL,"NO pressed","",MB_OK);
		return 0;
    }
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
///////////////THEM O DAY /////////////////////
class khungIn{
	public:
	int CD;
	int CR;
	int soTruong;
	short xK;
	short yK;
	khungIn(int CD, int CR, int soTruong, int xK, int yK ){
		this->CD=CD;
		this->CR=CR;
		this->soTruong=soTruong;
		this->xK=xK;
		this->yK=yK;		
	}
	void veHCN(int b,int a){
		int x=wherex(),y=wherey();
		for (int i=0;i<a;i++)
			for (int j=0;j<b;j++){
				if(i==0||i==a-1) cout<<"+";
				else if((j==0)||(j==b-1)) cout<<"+";
				else cout<<" ";
				if (j==b-1) gotoxy(x,++y);
			}
	}
	void ve(){
		gotoxy(xK,yK);
		veHCN(CD,CR);
		gotoxy(xK,yK+2);
		veHCN(CD,1);
		for (int i=1; i<soTruong;i++)
			for(int j=0;j<CR;j++){
				gotoxy(xK+i*(CD/soTruong),yK+j);
				cout<<"+";
			}
		
	}
	void ve1(){
		gotoxy(xK,yK);
		veHCN(CD,CR);
		for (int i=0; i<CR;i++)
		{
			gotoxy(xK,yK+1);
			for (int j=0;i<CD;j++) cout<<"+";
		}
	}
	void gop(int a, int b){
		for (int i=a; i<b;i++)
			for(int j=1;j<CR-1;j++){
				if (j==2) continue;
				gotoxy(xK+i*(CD/soTruong),yK+j);
				cout<<" ";
			}
	}
	void chuyen(int x, int y){
		gotoxy(xK+x*(CD/soTruong)+1,yK+y+1);
	}
	void themHang(){
		//dang fix
		this->CR++;
		gotoxy(xK+1,yK+CR-2);
//		cout<<xK+1<<" "<<yK+CR-1;
		for(int i=0;i<CD-2;i++) cout<<" ";
		gotoxy(xK,yK+CR-1);
		for(int i=0;i<CD;i++) cout<<"+";
		for (int i=1; i<soTruong;i++){
			gotoxy(xK+i*(CD/soTruong),yK+CR-2);
			cout<<"+";
			}
		gotoxy(200,50);
	}
};

