#pragma once

#include "Ticket.h"

string ContentFlight[]= { "Ma Chuyen Bay","San Bay Den"	,"So Hieu May Bay","Tong So Ve","Trang Thai"};

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
	flightNode *pNext;
};

typedef  flightNode* PTR;




void addToListPlane(PTR &first, Flight &cb ) {
	
	PTR p;
   	p = new flightNode;


	if(first == NULL) {
		p->flight = cb;
		p->pNext = first;
		first= p;
	}
	
	
	
}

void Nhap_Chuyen_Bay(PTR &p) {

	string ID;
	string destination;
	string serialPlane;
	int nTicket = 0 ;
	int status = 0 ;
	int order = 0;
	
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
				ConstraintForOnlyNumber(nTicket,order,17,999);
				if(nTicket<20) {
					BaoLoi(" Khong hop le ");
					break;
				}
				order++;
				break;
			case 4:
				gotoxy(X_Notification,Y_Notification+1);cout <<"1 = Huy     ";
				gotoxy(X_Notification,Y_Notification+2);cout <<"2 = Con ve  ";
				gotoxy(X_Notification,Y_Notification+3);cout <<"3 = Het ve  ";
				gotoxy(X_Notification,Y_Notification+4);cout <<"4 = Hoan tat";
				ConstraintForOnlyNumber(status,order,17, 4);
				order++;
				break;
			case 5:
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
	
	Display(ContentFlight,5);
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
					CreateForm(ContentFlight,5,27);
					gotoxy(115 + 12,0 * 3 + 4);
					Nhap_Chuyen_Bay(p);
										
										
				}
				
				
			}
			else if(signal == DEL) {
					return ;
				}
			
	}
	
}


