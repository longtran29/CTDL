#pragma once

#include "Datetime.h"
#include "Ticket.h"

string ContentFlight[]= { "Ma Chuyen Bay","San Bay Den"	,"So Hieu May Bay","Thoi Gian Di","Tong So Ve","Trang Thai"};

struct flight {

	char flightCode[10];
	char arrivalPlace[20];
	datetime departTime;
	char serialPlane[15];
	int status;
	int totalTicket;
	int saleTotal;
	Ticket *TicketList;

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
	
};

typedef struct flightList FlightList;

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

//void addToListPlane(PTR &first, Flight cb ) {
//	
//	PTR p;
//   	p = new flightNode;
//
//
//	if(first == NULL) {
//		p->flight = cb;
//		p->pNext = first;
//		first= p;
//	}
//
//}

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

void Nhap_Chuyen_Bay(FlightList &FL) {

	ShowCur(true);
	string ID;
	string destination;
	string serialPlane;
	int nTicket = 0 ;
	int status = 0 ; // luon con ve
	int order = 0;
	datetime DT;
	int target;
	bool quit = false;
	while(!quit) {
		switch(order) {
			case 0:
				ConstraintLetterAndNumber(ID,order,15);
				if(ID == "") {
					
					BaoLoi(" Vui Long Khong Bo Trong ");
					break;
				}
				order++;
				break;
			case 1:
				ConstraintsForLetterAndSpace(destination,order,14);	
				if(destination == "") {
					
					BaoLoi(" Vui Long Khong Bo Trong ");
					break;
				}
				order++;
				break;	
			case 2:
				ConstraintLetterAndNumber(serialPlane,order,17);
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
				DateTimeInput(DT, order);
				order++;
				break;
				
			case 4:
				ConstraintForOnlyNumber(nTicket,order,17,999);
				if( nTicket < (planeList.planes[target])->seats   || nTicket<20) {
					BaoLoi("So Ve khong phu hoi voi so cho tren may bay");
					break;
				}
				order++;
				break;
			case 5:
				gotoxy(X_Notification,Y_Notification+1);cout <<"1 = Huy     ";
				gotoxy(X_Notification,Y_Notification+2);cout <<"2 = Con ve  ";
				gotoxy(X_Notification,Y_Notification+3);cout <<"3 = Het ve  ";
				gotoxy(X_Notification,Y_Notification+4);cout <<"4 = Hoan tat";
				ConstraintForOnlyNumber(status,order,17, 4);
				order++;
				break;
			case 6:
				{
					Flight flight;
					strcpy(flight.flightCode, ID.c_str());
					strcpy(flight.arrivalPlace, destination.c_str());
					strcpy(flight.serialPlane, serialPlane.c_str());
					flight.departTime = DT;
					flight.status = status;
					flight.totalTicket = nTicket;
					flight.saleTotal =0;
					addEndList(FL, flight);
				
					ID = "";
					destination = "";
					serialPlane = "";
					nTicket=0;
					status =0;
					order = 0;
				}
				quit = true;
				break;
			
		}
		
		
	}



}

void ManageFlightPlane(FlightList &FL) {
	
	system("cls");
	
	gotoxy(40,1);

	cout << " Quan ly chuyen bay ";
	
	Display(ContentFlight,6);
	int signal;
	int CurFlightPage = 1;

	while(true) {
		
		signal = _getch();
			
			if(signal == ESC) {
				return;
			}
			if (signal == 224) {
				signal = getch();
				
				if(signal == INSERT) {
					system("cls");
					CreateForm(ContentFlight,6,27);
					gotoxy(115 + 12,0 * 3 + 4);
					Nhap_Chuyen_Bay(FL);
//					TotalFlightPage = (int)ceil( (double)FL.SoLuongChuyenBay/NumberPerPage );
//					ShowFlightListPerPage(FL,(CurFlightPage-1)/NumberPerPage);
									
				}
				
				
			}
			else if(signal == DEL) {
					return ;
				}
			
	}
	
}


