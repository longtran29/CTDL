#pragma once
#include<math.h>
#include "ConstraintTP.h"


string titleDisplay[] ={"So hieu", "Loai MB", "So cho ngoi"};
int TotalPage = 0;
int CurrentPage = 0; 

struct DetailInfo {
	
	char serialPlane[15];
	char typePlane[40];
	int seats;
};


struct Plane {
	
	int n=0;
	DetailInfo *planes[MAXLIST];
}  ;

typedef struct Plane listPlane;


void WriteAirplaneToFile(listPlane &list)
{
	ofstream fileout;
	fileout.open("DSMB.TXT",ios_base::out);// ios_base::out la de ghi vao file
	if( fileout.is_open() )
	{
		for( int i = 0 ; i < list.n ; i++)
		{
			fileout << list.planes[i]->serialPlane <<" "<<list.planes[i]->typePlane<<" "<<list.planes[i]->seats<<endl;
		}
	}
	else
	{
		gotoxy(X_Notification,Y_Notification+1);
		cout << " Ket noi file de ghi vao that bai";
	}
	fileout.close();
}


void ReadAirplaneFile(listPlane &list)
{
	ifstream filein;
	filein.open("DSMB.TXT", ios_base::in);// ios_base::in la de doc

	
	string temp;
	int i = 0;
	if( filein.is_open() )
	{
		while(!filein.eof())
		{
			DetailInfo *plane = new DetailInfo;
			
			filein>> plane->serialPlane;
		
			filein>> plane->typePlane;
			filein>>plane->seats;
			
			
			list.planes[i++] = plane;
			list.n++;
			filein.ignore();
			if (filein.eof()) break;
			
		}
	}
	filein.close();
}


//void ReadAirplaneFile(listPlane &list) {
//	 char *filename = "DSMB.TXT";
// FILE * f; DetailInfo plane;
// if ((f=fopen(filename,"rb"))==NULL)
// {  BaoLoi ("Loi mo file de doc"); return ;
// }
//  
// while  (fread (&plane, sizeof (DetailInfo), 1, f)!=0) {
// 	list.planes[list.n]=new DetailInfo;
// 	*list.planes[list.n]=plane;
// 	list.n ++;
// }
//    
// fclose(f);
// BaoLoi ("Da load xong danh sach vao bo nho");
//
//}



int Check_Trung(listPlane &list, const char *serialNum) {
	
	for(int i=0; i< list.n; i++) {
	
		int response = strcmp(((list.planes[i])->serialPlane), serialNum);
		if(response == 0) return i;
	
	}
	return -1 ;	
	
}


void Display(string content[], int numContent) {
	
	// mau vang

	system("color 0E");
	Normal(14,0);
	for(int i=0; i< numContent; i++) {
		gotoxy(xKeyDisplay[i] + 3, 4);
		cout<<content[i];
	}
	
	gotoxy(x_hd,y_hd);
	cout << " Huong dan " ;
	gotoxy(x_hd-1,y_hd + 2);
	cout << "  Up:Len || Down:Xuong ";
	gotoxy(x_hd,y_hd + 3);
	cout << " Insert:Them || Del:Xoa ";
	gotoxy(x_hd,y_hd + 4);
	cout << " Home:Chinh Sua || ESC : thoat" ;

}



//DetailInfo *addPlane(DetailInfo &plane) {
//	
//	DetailInfo *t = new DetailInfo;
//	*t = plane;
//	return t;
//	
//}


 

void show_one_plane(DetailInfo *plane, int position) {
	
	// plane la con tro ->
	
//	cout<<"Gia tri";
//	cout<<(*(plane)).serialPlane;
	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position*3);printf("%-15s",plane->serialPlane);
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position*3);printf("%-15s",plane->typePlane);
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position*3);printf("%-15d",plane->seats);
	
	
}

void Xuat_DS_MB(listPlane list, int startIndex) {
	
	gotoxy(40,1);
	cout<<"Danh sach may bay";
	gotoxy(1,2);
	cout << " So luong may bay : " <<list.n;
	Display(titleDisplay,3);
	
	for(int i=0; i +startIndex < list.n && i< NumberPerPage; i++) {
		
		show_one_plane(list.planes[i],i);
		
	}
	

}

void ChangePage(listPlane list) {
	
	
	
	Xuat_DS_MB(list, (CurrentPage-1)* NumberPerPage);
}


void CreateRow(int x, int y, string content, int length) {
	gotoxy(x,y);
	cout<<content;
}


void CreateForm(string content[], int numContent, int length) {
	
	int y = y_add;
	
	for(int i=0; i< numContent; i++) {
	
		
		CreateRow(x_add,y,content[i], length);
		y = y+ 3;
	
	}
	

}


//void Nhap_DS_MB(listPlane &list ) {
//	DetailInfo plane;
//
//	while(list.n < MAXLIST) {
//	
//		if(Nhap_Thong_Tin_MB(list,plane) == 0) return;
//		list.planes[list.n] = addPlane(plane);
//		*list.planes[list.n] = plane;
//		list.n++;
//		
//	}
//		
//}


void Nhap_MB(listPlane &list, bool editing= false, bool deleting = false) {
	
		int order = 0;
 		string ID;
 		string typePlane;
 		int nchair = 0;
 	
 	bool quit = false;
 	while(!quit) {
 		
 		switch(order) {
 			case 0 : // nhap cho so hieu mb
 				{
 					
 					ConstraintLetterAndNumber(ID,order,12);
 					if(ID == "") {
						BaoLoi(" Vui Long Khong Bo Trong ");
						break;
					 }
 					if(Check_Trung(list, ID.c_str()) >=0) {
					 
					 	BaoLoi(" So hieu  trung trong ds ");
						break;
					 
					 }
				 }
				 order++;
				 break;
 			case 1: // nhap loai type
 				ConstraintLetter(typePlane,order,12);
 				
 				if(typePlane == "") {
				 	
				 	BaoLoi(" Vui Long Khong Bo Trong ");
					break;
				 
				 }
 				order++;	
 				break;
 			case 2: // nhap cho ngoi
 				ConstraintNumber(nchair,order,12,999);
 				
 				if(nchair <1) {
 					BaoLoi("Khong hop le");
					break;
				 }
				if(nchair< 20) {
					BaoLoi("So ghe >= 20");
					break;
				}
				order++;
 				break;
 			case 3:
 				{
 					list.planes[list.n] = new DetailInfo;
 					strcpy((list.planes[list.n]->serialPlane),ID.c_str());
					strcpy((list.planes[list.n]->typePlane),typePlane.c_str());
					list.planes[list.n]->seats = nchair;
					list.n++;
					gotoxy(X_Notification,Y_Notification+1);
					cout << " Them thanh cong ";
				 }
				 
 				WriteAirplaneToFile(list);
 				quit = true;
 				break;
 				
 				
 				
 				
 			
 			
 			
		 }
 		
 		
 		
	 }
	
	
}
 	
 
 	
 
void MenuManageAirplane(listPlane &list) {
	
	
	
	Xuat_DS_MB(list, 0);
	
	TotalPage = (int)ceil( (double)list.n/NumberPerPage );
	CurrentPage = 1;
	int signal;
	
	while(true) {
		
		while (kbhit()){
			
			signal = getch();
			
			if(signal == ESC) return;
			
			if(signal == 224) {
				
				signal = _getch();
				
				if(signal == PAGE_UP && CurrentPage > 1) {
					
					CurrentPage--;
					Xuat_DS_MB(list,(CurrentPage-1)*CurrentPage);
				}
				else if (signal == PAGE_DOWN && CurrentPage < TotalPage) {
					CurrentPage++;
					
					Xuat_DS_MB(list,(CurrentPage-1)*CurrentPage);	
				}
			
				else if(signal == INSERT) {
				
					if(list.n == MAXLIST) {
						gotoxy(X_Notification,Y_Notification+1);cout <<"Danh sach day,khong the them";
						return;
					}
					else {
						system("cls");
						CreateForm(titleDisplay,3,27);
						gotoxy(115 + 12,0 * 3 + 4);
						Nhap_MB(list);
						system("cls");
						TotalPage = (int) ceil((double)list.n/NumberPerPage);
						Xuat_DS_MB(list, (CurrentPage-1)*NumberPerPage);
						
					}
				
				
				
				} 
				else if(signal == DEL) {
					return ;
				}
				
			
		
			}
			

		}
		

		
	}


}


