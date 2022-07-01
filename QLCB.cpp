#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <mylib.h>
#include "DefineConst.h"
#include "graphic.h"
#include "Airplane.h"


struct DetailInfo {
	
	char serialPlane[4];
	char typePlane[4];
	int seats;
};


struct Plane {
	
	int n;
	DetailInfo *planes[MAXLIST];
}  ;

typedef struct Plane listPlane;




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




string titleDisplay[] ={"So hieu", "Loai MB", "So cho ngoi"};




int Check_Trung(listPlane &list, char *serialNum) {
	
	for(int i=0; i< list.n; i++) {
	
		int response = strcmp(((list.planes[i])->serialPlane), serialNum);
		if(response == 0) return 1;
	
	}
	return 0;	
	
}
					  

int Nhap_Thong_Tin_MB(listPlane &list, DetailInfo &plane) {
	
	

	while(1) {
		
	
		cout<<"Nhap so hieu may bay ( 0 la ket thuc ) :";
//		getline(cin, plane.serialPlane);
		cin>>plane.serialPlane;
		

		

		if( Check_Trung(list, plane.serialPlane) ==1) {
			BaoLoi("May bay da trong danh sach");
			continue;
		}
	
		

		cout<<"Nhap loai may bay :";
		cin>> plane.typePlane;
		
		
		cout<<"Nhap cho ngoi may bay :";
		cin>> plane.seats;	
		
		if(plane.seats==0) return 0;
		
		return 1;
	
		
	}

	
}

DetailInfo *addPlane(DetailInfo &plane) {
	
	DetailInfo *t = new DetailInfo;
	*t = plane;
	return t;
	
}


void Nhap_DS_MB(listPlane &list ) {
	DetailInfo plane;

	while(list.n < MAXLIST) {
	
		if(Nhap_Thong_Tin_MB(list,plane) == 0) return;
		list.planes[list.n] = addPlane(plane);
		*list.planes[list.n] = plane;
		list.n++;
		
	}
		
}


void show_one_plane(DetailInfo *plane, int position) {
	
	// plane la con tro ->
	
//	cout<<"Gia tri";
//	cout<<(*(plane)).serialPlane;
	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position*3);printf("%-15s",plane->serialPlane);
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position*3);printf("%-15s",plane->typePlane);
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position*3);printf("%-15d",plane->seats);
	
	
	
}


void Xuat_DS_MB(listPlane list) {
	

	
	gotoxy(40,1);
	cout<<"Danh sach may bay";
	gotoxy(1,2);
	cout << " So luong may bay : " <<list.n;
	Display(titleDisplay,3);
	
	for(int i=0; i< list.n && i< NumberPerPage; i++) {
		
		show_one_plane(list.planes[i],i);
		
	}


	getch();

}


void Chinh_Sua_MB(listPlane &list) {
	
	
	
	Xuat_DS_MB(list);
	
	
	
}



char thucdon [so_item][50] = {"1. Nhap danh sach hoc vien",
			                  "2. Liet ke danh sach      ",
			                  "3. Sua danh sach may bay  ",
			                  "4. Ghi mot hoc vien       ",
			                  "5. Ghi danh sach          ",
			                  "6. Mo  danh sach          ",
			                  "7. Them sv co thu tu      ",
			                  "8. Ket thuc chuong trinh  "};
			          
					  



int main() {
	
			

	
	listPlane planeList;
	int chon = 0;
	int vitri;
	
	
	do {
		
		chon = MenuDong (thucdon);
		system ("cls");
		switch(chon) {
				
			case 1:
			Nhap_DS_MB(planeList);
			break;
				
			case 2 :
				Xuat_DS_MB(planeList);
				break;
			case 3:
//				Chinh_Sua_MB(planeList);
				break;
			case 4:
//				SaveFile(planeList, filename);
				break;
			case 5:
				break;
			
			
			
		}
		
		
	}
	while(1);
	
	
	
	
	
	return 0;
}
