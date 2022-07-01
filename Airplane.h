#pragma once

string titleDisplay[] ={"So hieu", "Loai MB", "So cho ngoi"};


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
