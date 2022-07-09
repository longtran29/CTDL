#pragma once

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
	Ticket *TicketList;

};

// node trong list
struct flightNode {
	
	Flight flight;
	Flight *pNext;
};

typedef  flightNode * PTR;

PTR First=NULL;

void Nhap_Chuyen_Bay(flightNode list) {

	string ID;
	string destination;
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
				break;
			
			
		}
		
		
	}



}

void ManageFlightPlane(flightNode planeList) {
	
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
					CreateForm(ContentFlight,3,27);
					gotoxy(115 + 12,0 * 3 + 4);
					Nhap_Chuyen_Bay(planeList);
										
										
				}
				
				
			}
			else if(signal == DEL) {
					return ;
				}
			
	}
	
}


