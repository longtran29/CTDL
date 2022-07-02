#pragma once
#include<math.h>
string titleDisplay[] ={"So hieu", "Loai MB", "So cho ngoi"};
int TotalPage = 0;
int CurrentPage = 0; 
struct DetailInfo {
	
	char serialPlane[4];
	char typePlane[4];
	int seats;
};


struct Plane {
	
	int n=0;
	DetailInfo *planes[MAXLIST];
}  ;

typedef struct Plane listPlane;


int Check_Trung(listPlane &list, char *serialNum) {
	
	for(int i=0; i< list.n; i++) {
	
		int response = strcmp(((list.planes[i])->serialPlane), serialNum);
		if(response == 0) return 1;
	
	}
	return 0;	
	
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
	
	
	gotoxy(x - 2, y - 1);
	cout << char(176) << setw(length) << setfill(char(176)) << char(176) << char(176);

	gotoxy(x - 2, y);
	cout << char(176) << content << setw(length - content.length() + 1) << setfill(' ') << char(176);

		
	
}


void CreateForm(string content[], int numContent, int length) {
	
	int y = 4;
	
	for(int i=0; i< numContent; i++) {
	
		
		CreateRow(115,y,content[i], length);
		y = y+ 3;
	
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
						Nhap_DS_MB(list);
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


