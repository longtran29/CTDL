#pragma once


struct passenger {
	int CMND;
	char Surname[20];
	char Name[10];
	int Gender; // 1 : male, 2 : female
};
typedef struct passenger Passenger;

struct passengernode {
	passenger data;
	struct passenger* pLeft = NULL;
	struct passenger* pRight = NULL;
	int bf;
};
typedef passengernode PassengerNode;
typedef passengernode* AVLTree;

AVLTree root;

void CreateAVLTree(AVLTree &root) {
	root = NULL;
}

int CurPosTicket = 1;
int CurPosPreTicket = 1;

int CheckStatus(Flight F, int x) {
	
	for(int i=0;i< F.saleTotal; i++) {
		if(x== F.TicketList[i].Status) return 1;
	}
	
	return 0;
}

void TicketSlot(int x, int y, int pos, int status) {
	
	SetColor(14);// yellow
	SetBGColor(0);// black

	gotoxy(x,y-1);
	cout << char(176) << setw(3) << setfill(char(176)) << char(176) << char(176);
	gotoxy(x, y);
	cout << char(176) << setw(3) << setfill('0')<<pos<<char(176);
	//printf("%-5d",text);
	/*ve duong ke ben duoi cua cai ve*/
	gotoxy(x,y+1);
	if (status == 1) {
		SetBGColor(5);
	}
	cout << char(176) << setw(3) << setfill(char(176)) << char(176) << char(176);

}

void TicketSlotTable(Flight F) {
	int x = X_Ticket+ 8;
	int y = Y_Ticket + 5;
	
	int Limit = F.totalTicket;
	
	for(int i=1; i<= Limit; i++) {
	
		TicketSlot(x,y,i, CheckStatus(F,i));
		
			x+=8;
			if(i%10 ==0) {
				y+=5;
				x = X_Ticket + 8;		
			}
	
	
	}
	


}

void ChangeTicket(int pos) {
	
	ShowCur(false);
	int Current = pos;
	
	int col = (Current-1 ) %10 ;
	int row = (Current -1)/10 ;
	
	SetBGColor(3);
	gotoxy( X_Ticket + (col+1)*8, Y_Ticket +(row+1)*5);
	cout << char(176) << setw(3) << setfill('0')<<Current<<char(176);
	
	SetBGColor(0);
	col = (CurPosPreTicket-1)%10;
	row = (CurPosPreTicket-1)/10;
	gotoxy( X_Ticket + (col+1)*8, Y_Ticket +(row+1)*5);
	cout << char(176) << setw(3) << setfill('0')<<CurPosPreTicket<<char(176);
	
	CurPosPreTicket = Current;
	
	
}



int ChooseTicket(Flight F) {
	CurPosTicket = 1;
	CurPosPreTicket = 1;
	
	TicketSlotTable(F);
	
	SetBGColor(3);// blue
	gotoxy(X_Ticket+ 8, Y_Ticket + 5);
	cout << char(176) << setw(3) << setfill('0') << 1 << char(176);
	int signal;
	bool quit = false;
	while(!quit) {
		
		signal = _getch();
		
		switch(signal) {
			
			case KEY_DOWN:
				if(CurPosTicket + 10 <=F.totalTicket) {
					CurPosTicket = CurPosTicket + 10;
					ChangeTicket(CurPosTicket);
				}
				break;
				
			case KEY_UP:
				if(CurPosTicket - 10 >=1) {
					CurPosTicket = CurPosTicket-10;
					ChangeTicket(CurPosTicket);
				}
				break;
			case KEY_LEFT:
				if(CurPosTicket>1){
					CurPosTicket--;
					ChangeTicket(CurPosTicket);
				}
				break;
			case KEY_RIGHT:
				if(CurPosTicket< F.totalTicket) {
					CurPosTicket++;
					ChangeTicket(CurPosTicket);
				}
				break;
			case ESC:
				return -1;
				
		}
	}
	
	

	
	

}

void BookTicket(AVLTree root) {
	system("cls");
	system("color 0E");
	gotoxy(X_Title, Y_Title);
	cout << "Vui long nhap ma chuyen bay  --->";
	
	bool flag = false;
	int order = 0;
	bool Save = true;
	string result;
	PTR_FL currentFlight = NULL; 
	
	while(flag == false ) {
		ConstraintLetterAndNumber(result,order,Save, 12);
		if(Save == false) {
			return;
		}
		
		currentFlight = findFlight(FL, result.c_str());
		
		if(currentFlight == NULL) BaoLoi("Chuyen bay khong ton tai");
		
		else {
			if(currentFlight->flight.status == 1 || currentFlight->flight.status ==4 ||currentFlight->flight.status ==3) {
				
				BaoLoi("Chuyen bay da huy or hoan tat, vui long nhap lai ");
//				continue;
			}
			flag = true;
		
	}
	
	
}
		system("cls");
		gotoxy(X_Title, Y_Title);
		cout << " Danh sach hanh khach co ma chuyen bay " << currentFlight->flight.flightCode << " toi " << currentFlight->flight.arrivalPlace<< " luc ";
		OutputDateTime(currentFlight->flight.departTime);
		
		gotoxy(20,5);
		cout << "Warn: VE MAU DO LA DA CO NGUOI DAT ROI !!";
		
		while(1) {
			
			int choosen = ChooseTicket(currentFlight->flight);
		
		
		}	



}
