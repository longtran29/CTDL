#pragma once

#include "Datetime.h"
#include "Ticket.h"

int TotalFlightPage = 0;// so trang cua danh sach chuyen bay
int CurFlightPage;

string ContentFlight[]= { "Ma Chuyen Bay","San Bay Den"	,"So Hieu May Bay","Thoi Gian Di","Tong So Ve","Trang Thai"};
string InsertContentFL[]= { "Ma Chuyen Bay","San Bay Den"	,"So Hieu May Bay","Trang Thai","Thoi Gian Di"};

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
// cap nhat trang thai chuyen bay
void UpdateFlightStatus(FlightList &FL)
{
	for( FlightNode *search = FL.pHead; search != NULL ; search = search->pNext)
	{
		if( checkValidDT( search->flight.departTime) == false )
			// xet trang thai ve hoan tat
			search->flight.status = 4;
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
				
			
				if(Del) {
					
					// xoa chuyen bay theo ID
					if(!DeleteFlightById(FL, ID.c_str())) {
						BaoLoi("Delete fail !");
					}
					else 					
						{
							BaoLoi("Delete successful !");
						}
					
					return;
				
				}	
						
				
				if(search != NULL && Edit == false) { // them chuyen bay moi
							
					BaoLoi("ID da ton tai, vui long nhap ID khac");break;
				
				
				}
				else if(search == NULL && Edit == true) {
					BaoLoi("ID can sua khong ton tai");break;
				}
				
				
				if(Edit) {
					
					destination =  search->flight.arrivalPlace;
					serialPlane = search->flight.serialPlane;
					ID =  search->flight.flightCode;
					gotoxy(x_add + 16, 0 * 3 + y_add);cout << ID;
					
					gotoxy(x_add + 16, 1 * 3 + y_add);cout << destination;
					gotoxy(x_add + 18, 2 * 3 + y_add);cout << serialPlane;
					
					gotoxy(x_add + 16, 5 * 3 + y_add);cout << search->flight.status;

					gotoxy(x_add + 16, 3 * 3 + y_add);OutputDateTime(search->flight.departTime);

					
					gotoxy(x_add + 16, 4 * 3 + y_add);cout << search->flight.totalTicket;
					
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
//				gotoxy(x_add+12,3*3+y_add);cout<<"Con ve";
				order++;
				break;
				
			case 4:
			
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
			
			
				
		
			case 5:
				{
					Flight addflight;
					strcpy(addflight.flightCode, ID.c_str());
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
			
			if(signal == ESC) {
				int n;
				cout<<"\n Ban co muon luu du lieu ? \n (0 de luu, 1 de thoat)";
				cin>>n;
				if(n==0){
					WriteFlightToFile(FL);
				}
				return;
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
					CreateForm(InsertContentFL,0,5,27);
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
// giai phong vung nho
bool CleanUpFlightList(FlightList &FL)
{
	if( FL.pHead == NULL)
		return false;
	PTR_FL clean;
	while(FL.pHead != NULL)
	{
		clean = FL.pHead;
		FL.pHead = FL.pHead->pNext;
		delete clean;
	}
	return true;
}
