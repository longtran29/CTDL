#pragma once

#include "Datetime.h"
#include "Ticket.h"

int TotalFlightPage = 0;// so trang cua danh sach chuyen bay
int CurFlightPage;

string ContentFlight[]= { "Ma Chuyen Bay","San Bay Den"	,"So Hieu May Bay","Thoi Gian Di","Tong So Ve","Trang Thai"};
string InsertContentFL[]= { "Ma Chuyen Bay","San Bay Den","So Hieu May Bay","Thoi Gian Di"};

struct flight {

	char flightCode[10];
	char arrivalPlace[20];
	datetime departTime;
	char serialPlane[15];
	int status; // 1: huy chuyen 2:con ve 3:het ve 4:hoan tat
	Ticket *TicketList= new Ticket[100]; // danh sách ve dã bán 
	
	int totalTicket; // so luong ve cho chuyen bay
	int saleTotal; // tong so ve da ban duoc
	

};

typedef struct flight Flight;

// node trong list
struct FlightNode {
	
	Flight flight;
	FlightNode *pNext = NULL; // con tro -> con tro
};

typedef  FlightNode* PTR_FL;

struct flightList {

	PTR_FL pHead;
	PTR_FL pTail;
	int SoLuongChuyenBay = 0; // truong phu
	
};


struct findedFlight {
	char flightCode[10];
	datetime departTime;
	int vacant_slot;
};

typedef struct flightList FlightList;

FlightList FL; 

void initFlightList(FlightList &FL) {

	FL.pHead = NULL;
	FL.pTail = NULL;
}


PTR_FL createFlightNode(Flight data) {

	PTR_FL nodeTemp = new FlightNode;
	if(nodeTemp == NULL) {
		
		return NULL;	
	}

	nodeTemp->flight = data;
	nodeTemp->pNext = NULL;
	
	return nodeTemp;
}

// them dau ds

void addBeginningList(FlightList &FL, Flight data) {

	PTR_FL nodeTemp = createFlightNode(data);
	
	if(FL.pHead = NULL) {
		FL.pHead = FL.pTail = nodeTemp;
	}
	
	else {
		nodeTemp->pNext = FL.pHead;
		FL.pHead = nodeTemp;
	}
	FL.SoLuongChuyenBay++;

}

void addEndList(FlightList &FL, Flight data) {
		PTR_FL nodeTemp = createFlightNode(data);
		if(FL.pTail == NULL) {
			FL.pHead = FL.pTail = nodeTemp;
		}
	
		else {
			
			FL.pTail->pNext = nodeTemp;
			FL.pTail = nodeTemp;
			
		}
		FL.SoLuongChuyenBay++;
	
}
void removeTail(FlightList &FL) {
	PTR_FL temp = FL.pTail;
	FL.pHead = FL.pHead->pNext;
	delete temp;
	FL.SoLuongChuyenBay--;
}

bool removeHead(FlightList &FL) {
	
	PTR_FL temp = FL.pHead;
	FL.pHead = FL.pHead->pNext;
	delete temp;
	FL.SoLuongChuyenBay--;
	return true;
}

bool removeAfter(FlightList &FL,PTR_FL temp) {
	PTR_FL rmtemp = temp->pNext;
	temp->pNext = rmtemp->pNext; // null neu la phan tu cuoi cung
	
	if(rmtemp == FL.pTail) { // TH la con tro cuoi -> update PTail
		delete rmtemp;
		FL.pTail = temp;
		
	}
	else {
		delete rmtemp;
	}
	FL.SoLuongChuyenBay--;
//	WriteFlightToFile(FL);
	return true;	
}






void SaveTicketListOfOneFlight(Flight &F) { // save flight 's ticket to file

	
	ofstream file;
	char filenameve[50] = "DSV\\";
	strcat(filenameve, F.flightCode);
	strcat(filenameve, ".TXT");
	file.open(filenameve,ios_base::out);
	if( file.is_open() )
	{
		file << F.saleTotal << endl;
		for( int i = 0; i < F.saleTotal ;i++)
		{
			file << F.TicketList[i].CMND << endl;
			file << F.TicketList[i].Status << endl;
		}
	}
	file.close();
	
}

void SaveFlight( Flight &F,ofstream &fileout)
{
	fileout << F.flightCode << endl;
	fileout << F.arrivalPlace << endl;
	fileout << F.serialPlane << endl;
	fileout << F.departTime.gio << endl;
	fileout << F.departTime.phut << endl;
	fileout << F.departTime.ngay << endl;
	fileout << F.departTime.thang<< endl;
	fileout << F.departTime.nam << endl;
	fileout << F.totalTicket << endl;

	fileout << F.status << endl;
	SaveTicketListOfOneFlight(F);
	
}
PTR_FL FindBefore(FlightList &FL,char *flightCode[10]){
	//NEU head=null thi ham goi tu tim node dau 
	if(FL.pHead==NULL||FL.pHead->pNext==NULL){
		return NULL;
	}

//	PTR_FL *k=findFlight(FL,flightCode)
	PTR_FL f;
	for(f=FL.pHead;f!=NULL||strcmp((f->pNext->flight.flightCode),*flightCode)==0;f=f->pNext){
//		if(f->flight == k->flight){
//			PTR_FL *g= createFlightNode(k->flight)
//			g->pNext=f;
//			p->pNext=g;
//			
//		}
//		p=f
		
	}
	return f;


}
bool EditFlight(FlightList &FL,char *flightCode[10], PTR_FL flightNode){
	PTR_FL search = FindBefore(FL,flightCode);
	if(search==NULL){
		if(strcmp((FL.pHead->flight.flightCode),*flightCode)==0){
//			&(flightNode->flight.flightCode)=*flightCode;
			FL.pHead=flightNode;
		}
	}
//thay doi node nhung chua xu li ticket
	else{
		PTR_FL tmp=search->pNext->pNext;
		search->pNext=flightNode;
		search->pNext->pNext=tmp;
		

	}
		
}



void WriteFlightToFile(FlightList &FL)
{
	ofstream fileout;
	fileout.open("DSCB.TXT",ios_base::out);

	
	if( fileout.is_open() )
	{
		fileout << FL.SoLuongChuyenBay << endl; // in sl
		for(  PTR_FL search = FL.pHead ; search != NULL ; search = search->pNext)
		{
			SaveFlight(search->flight,fileout);
		}
	}
	else
	{
		gotoxy(X_Notification,Y_Notification+1);
		cout << " Ket noi file de ghi vao that bai";
	}
	fileout.close();
}

void ReadTicketListOfOneFlight(Flight &F) {
	
	ifstream file;
	char filenameve[50] = "DSV\\";
	strcat(filenameve, F.flightCode);
	strcat(filenameve, ".TXT");

	file.open(filenameve, ios_base::in);
	if (file.is_open()) 
	{
		file >> F.saleTotal;
		F.TicketList = new Ticket[F.saleTotal];

		for (int i = 0; i < F.saleTotal; i++)
		{
			file >> F.TicketList[i].CMND;
			file >> F.TicketList[i].Status;
		}
	}
	file.close();
}

void ReadFlightFromFile(FlightList &FL) {
	
	ifstream filein;
	filein.open("DSCB.TXT", ios_base::in);
	
	Flight F;
	if(filein.is_open()) {
		int sizeFlight;
		filein>>sizeFlight;
		
		string temp;
		getline(filein, temp);
		
		for(int i=0; i< sizeFlight; i++) {
			if (strcmp(F.flightCode,"") == 0) break;
			filein.getline(F.flightCode,15,'\n');
			filein.getline(F.arrivalPlace,20,'\n');
			filein.getline(F.serialPlane,15,'\n');
			
			filein >> F.departTime.gio;
			filein >> F.departTime.phut;
			filein >> F.departTime.ngay;
			filein >> F.departTime.thang;
			filein >> F.departTime.nam;
			filein >> F.totalTicket;
			filein >> F.status;
			
			if(filein == NULL) break;
			
			getline(filein,temp);
			ReadTicketListOfOneFlight(F);
			addEndList(FL,F);
		}

	}
	filein.close();
}




void ShowFlight(Flight FL, int position) {
	
	int xKeyDisplay[7] = {1,20,45,63,80,95, 107};
	

	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position*3);printf("%-15s",FL.flightCode);
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position*3);printf("%-18s",FL.arrivalPlace);
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position*3);printf("%-15s",FL.serialPlane);
	gotoxy(xKeyDisplay[3] + 2, Y_Display + 3 + position*3);OutputDateTime(FL.departTime);
	gotoxy(xKeyDisplay[4] + 6, Y_Display + 3 + position*3);printf("%-3d",FL.totalTicket);
	gotoxy(xKeyDisplay[5] + 3, Y_Display + 3 + position*3);	
	
	switch(FL.status)
	{
	case 1: cout << "Huy     ";
		break;
	case 2: cout << "Con ve  ";
		break;
	case 3: cout << "Het ve  ";
		break;
	case 4: cout << "Hoan tat";
		break;
	default:
		break;
	}
}

void showFlightList(FlightList FL) {
	
	if( FL.pHead == NULL && FL.pTail == NULL) return;
	
	int count = 0;
	
	for(PTR_FL result = FL.pHead; result != NULL; result = result->pNext) {
		
		count++;
		ShowFlight(result->flight,count);
	}
}




void ShowFlightListPerPage(FlightList FL,int index) {
	
	system("cls");
	Display(ContentFlight,6);
	gotoxy(1,2);
	cout << " So luong chuyen bay : " << FL.SoLuongChuyenBay;
	int count = -1;
	
	if(FL.pHead == NULL || FL.pTail == NULL) return;
	int i=0;
	
	for(PTR_FL search= FL.pHead; search != NULL; search = search->pNext ) {
		
		count++; // thay doi con tro chay trong list
		if(count == index) {
			
			int i = 0;
			while(search != NULL && i< NumberPerPage) {
				ShowFlight(search->flight,i++);
				search = search->pNext;
			
			}
			break;
		}
		
	}

}

void ChangePageFlightPage(FlightList &FL) {
	
	system("cls");

	gotoxy(1,2);
	cout << " So luong chuyen bay : " << FL.SoLuongChuyenBay;
	gotoxy(X_Title,Y_Title);
	cout << " Quan ly chuyen bay ";
	
	ShowFlightListPerPage(FL,(CurFlightPage-1)*NumberPerPage);
	
	gotoxy(X_Page, Y_Page);
	cout <<"Trang "<< CurFlightPage << "/" << TotalFlightPage;

}


PTR_FL findFlight(FlightList FL, const char *ID) {
	
	if(FL.pHead == NULL) return NULL;
	for(PTR_FL search = FL.pHead; search != NULL; search = search->pNext) {
		
		if(strcmp(search->flight.flightCode, ID) == 0 ) return search;
	}
	return NULL;
	
}
bool DeleteFlightById(FlightList &FL, const char * ID) {
	
	PTR_FL delFlight = findFlight(FL, ID);
	
	if(delFlight == NULL) return false;
	else if (delFlight == FL.pHead) return removeHead(FL);
//	else if (delFlight == FL.pTail) removeTail(FL);
	else {
		PTR_FL temp = FL.pHead;
		while(true) {
			if(temp->pNext == delFlight) { // # null
				break;
				
			}
			temp = temp->pNext;
		}
		return removeAfter(FL,temp);
		
	}
	
}

void Swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void bubbleSortPlane(listPlane planeList, int A[]) {

	for(int i=0; i< planeList.n-1; i++) {
		for(int j = i+1; j<planeList.n; j++) {

			if(planeList.planes[i]->flights_num < planeList.planes[j]->flights_num )
				Swap(A[i],A[j]);
		}

	}
}


void ShowHowManyTimesAirplaneTookOff(DetailInfo *A,int position) {

	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3); cout<<position;
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3); printf("%-20s", A->serialPlane );
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3); printf("%-5d",  A->flights_num );


}

/*Thong ke so chuyen bay cua 1 hang may bay*/
void WatchStatics() {

	system("cls");
	gotoxy(X_Title, Y_Title);
	cout << " SO CHUYEN BAY DA THUC HIEN CUA CAC MAY BAY";	
	string StaticsTable[3] = { "Number","ID Plane" ,"Fly Times"};

	gotoxy(xKeyDisplay[0] + 3, Y_Display + 0 * 3); cout<<StaticsTable[0];
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 0 * 3); cout<<StaticsTable[1];
	gotoxy(xKeyDisplay[2] + 3,Y_Display + 0 * 3);  cout<<StaticsTable[2];

	int slmb = planeList.n; // slmb
	int A[slmb];
	for(int i=0; i< slmb; i++) A[i] = i;

	bubbleSortPlane(planeList, A);

	for(int i =0; i< slmb; i++) {
		ShowHowManyTimesAirplaneTookOff(planeList.planes[A[i]],i); // in ra mb tai vi tri thu A[i]

	}


	int signal;
	while (true)
	{
		signal = _getch();
		if (signal == ESC)
		{
			return;
		}
	}


}




void DateTimeInput(datetime &dt, int order) {
	
	gotoxy(x_add + 13 + 2 , order * 3 + y_add);
	cout << ":";
	gotoxy(x_add + 13 + 8 , order * 3 + y_add);
	cout << "/";
	gotoxy(x_add + 13 + 11, order * 3 + y_add);
	cout << "/";

	int dtOrder = 0;
	
	while(true) {
		
		switch(dtOrder) {
			case 0:
				ConstraintForDateAndTime(dt.gio,dtOrder,12,23);
				dtOrder++;
				break;
			case 1:
				ConstraintForDateAndTime(dt.phut,dtOrder,12,59);
				dtOrder++;
				break;
			case 2:
				ConstraintForDateAndTime(dt.ngay,dtOrder,12,31);
				dtOrder++;
				break;
			case 3:
				ConstraintForDateAndTime(dt.thang,dtOrder,12,13);
				dtOrder++;
				break;
			case 4:
				ConstraintForDateAndTime(dt.nam,dtOrder,12,2100);
				return;						
		}
	}
	

}

PTR_FL checkDupOnOtherFlight(FlightNode* first, FlightNode* xFlight, int idHK)  { 


	for(PTR_FL k = first; k != NULL; k=k->pNext) {
	
		if(k != xFlight) {
			
			for(int i=0;i< k->flight.saleTotal; i++) // check trên tong sale dc cua 1 flight
			{
				if(k->flight.TicketList[i].CMND == idHK && checkDateTime(k->flight.departTime, xFlight->flight.departTime)) {
					
					return k;
			
				}
			
			}
		
			
		}
	
	}
	return NULL;

}


/* check valid dest and time */
int check_placedate_cb(FlightList FL, datetime dt, string dest) {
	
	PTR_FL temp = new FlightNode;  int count = 0;
	strcpy(temp->flight.arrivalPlace, dest.c_str()); // convert
	
	if(FL.pHead == NULL) return 0 ;
	
	PTR_FL p = FL.pHead; 
		
	for(int i = 0; i< FL.SoLuongChuyenBay ;i++) {
	
		if( strcmp(p->flight.arrivalPlace, temp->flight.arrivalPlace) == 0 && dt.ngay == p->flight.departTime.ngay && dt.thang == p->flight.departTime.thang && dt.nam == p->flight.departTime.nam && p->flight.status == 2) {
		
			count++;
		}
		
		p = p->pNext;
		
	
	}
	return count;



}

/* kiem tra cac chuyen bay to dest and time con trong */
void ListFlightInDayAnDest(flightList FL) {
	
	datetime dt; InitDataTime(dt);
	gotoxy(x_add , 3 + y_add);
	cout<<"Nhap thoi gian can loc :";    // dd/mm/yyyy   gotoxy(x_add + space + dtOrder * 3 +1 , 3 *3  + y_add);
	gotoxy(x_add + 13 + 2 , 3 * 3 + y_add);
	cout << "/";
	gotoxy(x_add + 13 + 5 , 3 * 3 + y_add);
	cout << "/";	
	int dtOrder = 0;  bool quit = false;   
	
	while(!quit) {
		
		switch(dtOrder) {
			case 0:
				ConstraintForDateAndTime(dt.ngay,dtOrder,12,31);
				dtOrder++;
				break;
			case 1:
				ConstraintForDateAndTime(dt.thang,dtOrder,12,13);
				dtOrder++;
				break;
			case 2:
				ConstraintForDateAndTime(dt.nam,dtOrder,12,2100);
				quit = true;						
		}
	}
	
	RemoveFormComplete(); quit = false; string dest; bool Save = true; int order = 1;
	gotoxy(x_add - 8 , 3 + y_add); 
	cout<<" Nhap diem den can loc :"; 
	while(!quit) {
	
			ConstraintsForLetterAndSpace(dest,Save,order,16);
			if(!Save) {
				break;
			}	
			if(dest == "") {
				
				BaoLoi(" Vui Long Khong Bo Trong ");
				break;
			}
			stringOptimize(dest);
			StandardName((char*)dest.c_str());
			quit = true;		
	}
	
	system("cls");
	
	int slcb_find = check_placedate_cb(FL, dt, dest);
	if(slcb_find == 0) {BaoLoi("Khong co chuyen bay nao hop le"); return;}
	else {
			gotoxy(X_Title, Y_Title);
			cout << " Danh sach cac chuyen bay toi "<< dest << " luc ";
			OutputDateTime(dt);
		PTR_FL temp = new FlightNode;
		strcpy(temp->flight.arrivalPlace, dest.c_str()); 
		findedFlight listFound[slcb_find]; int count = 0;
		PTR_FL p = FL.pHead; 
		
		for(int i = 0; i< FL.SoLuongChuyenBay ;i++) {
	
				if( strcmp(p->flight.arrivalPlace, temp->flight.arrivalPlace) == 0 && dt.ngay == p->flight.departTime.ngay && dt.thang == p->flight.departTime.thang && dt.nam == p->flight.departTime.nam && p->flight.status == 2) {
				
					strcpy(listFound[count].flightCode, p->flight.flightCode); 
					listFound[count].departTime = p->flight.departTime;
					listFound[count].vacant_slot = p->flight.totalTicket - p->flight.saleTotal;
					count++;
				}
		
				p = p->pNext;
		
	
	}
				gotoxy(xKeyDisplay[0] + 3, Y_Display); cout<<"Ma chuyen bay";
				gotoxy(xKeyDisplay[1] + 3, Y_Display ); cout<<"Khoi hanh luc";
				gotoxy(xKeyDisplay[2] + 3, Y_Display ); cout<<"Cho trong";
	
				for(int i = 0; i< slcb_find; i++) {
					gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + i* 3);printf("%-15s",listFound[i].flightCode);
					gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + i * 3); OutputDateTime(listFound[i].departTime);
					gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + i * 3); printf("%-5d", listFound[i].vacant_slot );
				}	
	}
	
	getch();

}



void Nhap_Chuyen_Bay(FlightList &FL, bool Edit, bool Del) {

	ShowCur(true);
	string ID;
	string destination;
	string serialPlane;
	int nTicket = 0 ;
	int status = 2 ; // luon con ve
	int order = 0;
	datetime DT;
	int target;
	PTR_FL search;
	bool Save = true;
 	bool quit = false;
 	while(!quit) {
		switch(order) {
			case 0:
				ConstraintLetterAndNumber(ID,order,Save,16);
				if(!Save) {
					return;
				}
				if(ID == "") {
					
					BaoLoi(" Vui Long Khong Bo Trong ");
					break;
				}

				
				search = findFlight(FL,ID.c_str());	
				
				if(Edit || Del && search != NULL) {
					
					destination =  search->flight.arrivalPlace;
					serialPlane = search->flight.serialPlane;
					ID =  search->flight.flightCode;
					gotoxy(x_add + 16, 0 * 3 + y_add);cout << ID;
					
					gotoxy(x_add + 16, 1 * 3 + y_add);cout << destination;
					gotoxy(x_add + 17, 2 * 3 + y_add);cout << serialPlane;
					
					gotoxy(x_add + 16, 5 * 3 + y_add);cout << search->flight.status;

					gotoxy(x_add + 15, 3 * 3 + y_add);OutputDateTime(search->flight.departTime);

					
					gotoxy(x_add + 16, 4 * 3 + y_add);cout << search->flight.totalTicket;
					
				}
				
				if(Del && search != NULL) {
					
					int res = repeate("Delete", "Xac nhan xoa?");
					
					if(res == 1) {
						
						if(!DeleteFlightById(FL, ID.c_str())) {
								BaoLoi("Xoa that bai!");
						}
						else 					
						{
							BaoLoi("Xoa thanh cong !");
						}
					
						return;
						
					}
					else return;
				
				}	
				
				if(search != NULL && Edit == false) { // them chuyen bay moi
							
					BaoLoi("ID da ton tai, vui long nhap ID khac");break;
				
				
				}
				else if(search == NULL && Edit == true) {
					BaoLoi("ID can sua khong ton tai");break;
				}
				
				
				
				order++;
				break;
			case 1:
				ConstraintsForLetterAndSpace(destination,Save,order,16);
				if(!Save) {
					return;
				}	
				if(destination == "") {
					
					BaoLoi(" Vui Long Khong Bo Trong ");
					break;
				}
				if(Edit) {order++; break;}
				order++;
				break;	
			case 2:
				ConstraintLetterAndNumber(serialPlane,order,Save,17);
				if(!Save) {
					return;
				}
				if( serialPlane == "") {
					
					BaoLoi(" Vui Long Khong Bo Trong ");
					break;
				}
				target = Check_Trung(planeList,serialPlane.c_str());
				
				if(target<0) {
					BaoLoi(" So hieu may bay khong ton tai");	
					break;			
				}
				order++;	
				break;	
			case 3:
				InitDataTime(DT);
				struct DateTime DT;
				{
					DT = { ngay:0, thang:0, nam:0, gio:0, phut:0};
					DateTimeInput(DT, order);
					if(!checkValidDT(DT)) {BaoLoi("Thoi gian khong hop le");
								 gotoxy(x_add + 13, 4 * 3 + y_add); printf("%-33s", " "); break;}
				
				}
				order++;
				break;
			
		
			case 4:
				{
					Flight addflight;
					strcpy(addflight.flightCode, ID.c_str());
					stringOptimize(destination);
					StandardName((char*)destination.c_str());
					strcpy(addflight.arrivalPlace, destination.c_str());
					strcpy(addflight.serialPlane, serialPlane.c_str());
					addflight.departTime = DT;
					addflight.status = 2;
					addflight.totalTicket = planeList.planes[target]->seats;
					addflight.saleTotal = 0;
					if(!Edit){
						addEndList(FL, addflight);
					}
					else{
//						EditFlight(FL,&ID,addflight);
					
					}
					ID = "";
					destination = "";
					serialPlane = "";
//				InitDataTime(DT);
					order = 0;
				}
				quit = true;
				break;
			
		} //  end switch
		
	}// end while

}

void ManageFlightPlane(FlightList &FL) {
	
	system("cls");
	int signal;
	CurFlightPage = 1;
	TotalFlightPage = (int)ceil( (double)FL.SoLuongChuyenBay/NumberPerPage );
	ShowFlightListPerPage(FL,0);

	while(true) {
		
		signal = _getch();
			
			if(signal == ESC) { return;
			}
			if (signal == 224) {
				signal = _getch();
				
			
				if(signal == PAGE_UP && CurFlightPage >1 ) {
					
						CurFlightPage--;
						ChangePageFlightPage(FL);
				}
				else if(signal == PAGE_DOWN && CurFlightPage< TotalFlightPage) {
					CurFlightPage++;
					ChangePageFlightPage(FL);				
				}
				
				if(signal == INSERT) {
					system("cls");
					CreateForm(InsertContentFL,0,4,27);
					gotoxy(115 + 12,0 * 3 + 4);
					Nhap_Chuyen_Bay(FL, false, false);
					system("cls");
					Display(ContentFlight,6);
					TotalFlightPage = (int)ceil( (double)FL.SoLuongChuyenBay/NumberPerPage );			
					ShowFlightListPerPage(FL,(CurFlightPage-1)/NumberPerPage);
									
				}
				else if(signal == DEL) {
					system("cls");
					CreateForm(ContentFlight,0,6,27);
					gotoxy(115 + 12,0 * 3 + 4);
					Nhap_Chuyen_Bay(FL, false, true);
					TotalFlightPage = (int)ceil( (double)FL.SoLuongChuyenBay/NumberPerPage );
					ShowFlightListPerPage(FL,(CurFlightPage-1)/NumberPerPage);
				}
				
				else if(signal == HOME) {
					system("cls");
					CreateForm(ContentFlight,0,6,27);
					gotoxy(115 + 12,0 * 3 + 4);
					Nhap_Chuyen_Bay(FL,true, false);
					TotalFlightPage = (int)ceil( (double)FL.SoLuongChuyenBay/NumberPerPage );
					ShowFlightListPerPage(FL,(CurFlightPage-1)/NumberPerPage);
					
				}
				
				
			}
			
			
	}
	
}
