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

typedef struct flightList FlightList;

FlightList FL; 

void initFlightList(FlightList &FL) {

	FL.pHead = NULL;
	FL.pTail = NULL;
}



