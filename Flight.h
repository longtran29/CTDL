#pragma once

#include "Datetime.h"
#include "Ticket.h"

string ContentFlight[]= { "Ma Chuyen Bay","San Bay Den"	,"So Hieu May Bay","Thoi Gian Di","Tong So Ve","Trang Thai"};

struct Flight {

	char flightCode[10];
//	char departTime[15];
	char arrivalPlace[20];
	int status;
	char serialPlane[15];
	int totalTicket;
	int saleTotal;
//	Ticket *TicketList;

};

// node trong list
struct flightNode {
	
	Flight flight;
	flightNode *pNext = NULL;
};

typedef  flightNode* PTR;




void addToListPlane(PTR &first, Flight cb ) {
	
	PTR p;
   	p = new flightNode;


	if(first == NULL) {
		p->flight = cb;
		p->pNext = first;
		first= p;
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

void Nhap_Chuyen_Bay(PTR &p) {

	string ID;
	string destination;
	string serialPlane;
	int nTicket = 0 ;
	int status = 0 ;
	int order = 0;
	datetime DT;
	while(true) {
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
				if(serialPlane == "") {
					
					BaoLoi(" Vui Long Khong Bo Trong ");
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
				if(nTicket<20) {
					BaoLoi(" Khong hop le ");
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
					flight.totalTicket = nTicket;
					flight.status = status;
					flight.saleTotal = 0;
					addToListPlane(p, flight);
				
				}
				break;
			
		}
		
		
	}



}

void ManageFlightPlane(PTR &p) {
	
	system("cls");
	
	gotoxy(40,1);

	cout << " Quan ly chuyen bay ";
	
	Display(ContentFlight,6);
	int signal;
	

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
					Nhap_Chuyen_Bay(p);
										
										
				}
				
				
			}
			else if(signal == DEL) {
					return ;
				}
			
	}
	
}


