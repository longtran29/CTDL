#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <mylib.h>
#define MAXLIST 300

using namespace std;

const int so_item = 8;
const int dong =1;
const int cot = 1 ;
const int Up = 72; // Extended code 
const int Down = 80;

struct DetailInfo {
	
	char serialPlane[4];
	char typePlane[4];
	int seats;
};


typedef struct Plane {
	
	int n = 0;
	DetailInfo *planes[MAXLIST];
} listPlane ;



struct Passenger {
	char indentity[12];
	char familyName[6];
	char firstName[8];
	char Gender[4];
};



struct Flight {

	char serialNumber[4];
	char departTime[15];
	char arrivalPlace[20];
	boolean status;

};



char thucdon [so_item][50] = {"1. Nhap danh sach hoc vien",
			                  "2. Liet ke danh sach      ",
			                  "3. Tim kiem hoc vien      ",
			                  "4. Xoa mot hoc vien       ",
			                  "5. Ghi danh sach          ",
			                  "6. Mo  danh sach          ",
			                  "7. Them sv co thu tu      ",
			                  "8. Ket thuc chuong trinh  "};
			          
					  


void Normal () {
	SetColor(15);
	SetBGColor(0);
}


void HighLight () {
	SetColor(15);
	SetBGColor(1);
}



int MenuDong(char td [so_item][50]){
  Normal();
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
  		        Normal();
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
  		        Normal();
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

int Check_Trung(listPlane &list, char *serialNum) {
	
	for(int i=0; i<= list.n; i++) {
	
		int response = strcmp(((list.planes[i])->serialPlane), serialNum);
		if(response == 0)
		{
			cout<"Trung roi";
			return 1;
		}
	}
	return 0;	
	
}
					  

int Nhap_Thong_Tin_MB(listPlane &list, DetailInfo &plane) {
	


	while(1) {
		
	
		
			
		cout<<"Nhap so hieu may bay ( 0 la ket thuc ) :";
		cin>> plane.serialPlane;
		
//		if(strcmp(plane.serialPlane, "") ==0) return 0;
		
		
//		if( Check_Trung(list, plane.serialPlane) ==1) {
//			cout<< "Nhan hieu bi trung \n";
//			continue;
//		}
//		
		

		cout<<"Nhap loai may bay :";
		cin>> plane.typePlane;
		
		
		cout<<"Nhap cho ngoi may bay :";
		cin>> plane.seats;	
		
		if(plane.seats == 0) return 0;
	
	
		
	}

	
}


void Nhap_DS_MB(listPlane &planeList, boolean flag ) {
	DetailInfo plane;
	

	
	
	while(planeList.n < MAXLIST) {
	
		if(Nhap_Thong_Tin_MB(planeList,plane) == 1) return;
		planeList.planes[planeList.n] = new DetailInfo;
		*planeList.planes[planeList.n] = plane;
		planeList.n++;
		
	}
	
	
	
}


void Xuat_DS_MB(listPlane planList) {
	 system("cls") ;
 printf ("                     DANH SACH SINH VIEN \n");
	for(int i=0; i< planList.n; i++) {
		
		cout<< "Gia tri cua serial number la :";
		cout<< (planList.planes[i])->serialPlane;
	}
	getch();
}




int main() {
	
	listPlane planeList;
	int chon = 0;
	
	boolean flag = true;
	
	do {
		
		chon = MenuDong (thucdon);
		system ("cls");
		switch(chon) {
				
			case 1:
			Nhap_DS_MB(planeList, flag);
			break;
				
			case 2 :
				Xuat_DS_MB(planeList);
				break;
			case 3:
				break;
			
			
			
		}
		
		
	}
	while(1);
	
	
	
	Nhap_DS_MB(planeList, flag);
	
	
	
	return 0;
}
