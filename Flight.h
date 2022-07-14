#pragma once

struct flight{
	char idFlight[15];
	char destiny[50];
	DateTime timeLeave;
	char idAirplane[15];
	int status;
	// 0: huy chuyen, 1: con ve, 2: het ve, 3: hoan tat

};

typedef struct flight Flight;

struct flightnode{
	Flight data;
	struct flightnode *pNext;
};

typedef struct flightnode FlightNode;

struct flightlist{
	FlightNode *pHead;
	FlightNode *pTail;
	int flightNumber;
};

typedef struct flightlist FlightList;
