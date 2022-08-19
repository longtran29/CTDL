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
	struct passengernode* pLeft = NULL;
	struct passengernode* pRight = NULL;
	int bf;
};
typedef passengernode PassengerNode;
typedef passengernode* AVLTree;

AVLTree root;

string ContentPassenger[5] = {"STT", "CMND", "Ho", "Ten", "GioiTinh"};


void CreateAVLTree(AVLTree &root) {
	root = NULL;
}

int CurPosTicket = 1;
int CurPosPreTicket = 1;

int nPassenger= 0; // bien dem sl hanh khach


AVLTree CreateTree(Passenger data) {
	
	AVLTree newPsg = new PassengerNode;
	newPsg->data = data;
	newPsg->pLeft = NULL;
	newPsg->pRight = NULL;
	return newPsg;
}


int height(AVLTree r) {
	
	if(r == NULL) return -1;
	
	else {
		
		int lheight = height(r->pLeft);
		int rheight = height(r->pRight);
		
		if(lheight> rheight) return lheight+1;
		else return rheight+1;
	}
}


int getBalanceFactor(AVLTree n) {
	if(n == NULL) return -1;
	return height(n->pLeft) - height(n->pRight);
}

AVLTree rightRotate(AVLTree y) {
	
	AVLTree x = y->pLeft;
	AVLTree T2 = x->pRight;
	
	// perfrom r
	x->pRight = y;
	y->pLeft  = T2;
	return x;
	
	
}


AVLTree leftRotate(AVLTree x) {
	
	AVLTree y = x->pRight;
	AVLTree T2 = y->pLeft;
	
	// perform rotate
	y->pLeft = x;
	x->pRight = T2;
	
	return y;
}

AVLTree AddPassenger(AVLTree &root, AVLTree new_Psg) {
	
	if(root == NULL) {
		root = new_Psg;
		
		return root;
	}
	
	else if(new_Psg->data.CMND < root->data.CMND) root->pLeft =  AddPassenger(root->pLeft, new_Psg);
	else if(new_Psg->data.CMND > root->data.CMND) root->pRight  = AddPassenger(root->pRight, new_Psg);
	
	else return root;
	
	int bf = getBalanceFactor(root);
	
	
	// left left case
	if(bf> 1  && new_Psg->data.CMND < root->pLeft->data.CMND) return rightRotate(root);
	
	// right right case
	if(bf <-1 && new_Psg->data.CMND > root->pRight->data.CMND) return leftRotate(root);
	//left right case
	if(bf>1 && new_Psg->data.CMND > root->pLeft->data.CMND) {
		root->pLeft = leftRotate(root->pLeft);
		return rightRotate(root);
	}
	
	// right left case
	if(bf<-1 && new_Psg->data.CMND < root->pRight->data.CMND) {
		root->pRight = rightRotate(root->pRight);
		return leftRotate(root);
	}
	
	// giu nguyen nut goc 
	return root;
	
	
	
}


PassengerNode* findPassenger(AVLTree root, int CMND) {
	
	if(root == NULL) return NULL;
	 else if(root->data.CMND == CMND) return root;
	
	else if(root->data.CMND > CMND) return findPassenger(root->pLeft, CMND);
	else return findPassenger(root->pRight, CMND);
	
}

// save passenger

void SaveOnePassenger(AVLTree root ,ofstream &fileout) {
	
	Passenger psg = root->data;
	
	fileout <<psg.CMND << endl;
	fileout << psg.Surname << endl;
	fileout << psg.Name << endl;
	fileout << psg.Gender << endl;


}

void SavePassengerToList(AVLTree root, ofstream &fileout) {

	if(root != NULL) {
		
		SaveOnePassenger(root,fileout);
		SavePassengerToList(root->pLeft,fileout);
		SavePassengerToList(root->pRight,fileout);
		
	}



}
void SavePassengerToFile(AVLTree root) { // luu hanh khach vao file

	ofstream fileout;	
	fileout.open("DSHK.TXT", ios_base::out);
	
	if(fileout.is_open()) {
		fileout<< nPassenger <<endl;
		SavePassengerToList(root, fileout);	
	}
	
	fileout.close();

}

void ShowPassenger(Passenger psg, int position) { // show 1 passenger
	
	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position*3);printf("%-5d",position+1);
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position*3);printf("%-12d",psg.CMND);
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position*3);printf("%-20s",psg.Surname);
	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position*3);printf("%-10s",psg.Name);
	gotoxy(xKeyDisplay[4] + 3, Y_Display + 3 + position*3);
	if(psg.Gender == 0) cout<<"Nam"; else cout<<"Nu";
	
	int signal;
	
	while(true) {
		signal = _getch();
		if(signal == ESC) return;
	}
	
}


void WatchPassengerFlight(AVLTree root, Flight F) { // menu  case 5 :  show hanh khach cua 1 chuyen bay
	ShowCur(false);
	Display(ContentPassenger,5);
	
	for(int i=0; i< F.saleTotal; i++) {
		PassengerNode* searchNode = findPassenger(root, F.TicketList[i].CMND);
		
		if(searchNode == NULL) continue;
		ShowPassenger(searchNode->data, i);
	}
	
	
	
}



// load passenger
//void LoadPassengerFromFile(AVLTree &root) {
//	ifstream filein;string temp= " ";char lot[50];
//	
//	filein.open("DSHK.TXT", ios_base::in);
//	if(filein.is_open()) {
//		
//		filein>>nPassenger;
//		for(int i=0; i<nPassenger; i++) {
//			Passenger psg;
//		
//			getline(filein,temp);
//			filein>>psg.CMND;
//			
//			filein>>psg.Surname;
//			filein >> lot;
//
//			strcat(psg.Surname, " ");
//			strcat(psg.Surname, lot);
//			cout<<psg.Surname;
//			
//			filein>>psg.Name;
//			filein>>psg.Gender;
//			
//			AVLTree new_Psg = CreateTree(psg);
//			
//			root = AddPassenger(root,new_Psg);
//		}
//	}
//	
//}



void LoadPassengerFromFile(AVLTree &root) {
	ifstream filein;
	
	filein.open("DSHK.TXT", ios_base::in);
	if(filein.is_open()) {
		
		filein>>nPassenger;
		for(int i=0; i<nPassenger; i++) {
			Passenger psg;char lot[50];
		
			filein>>psg.CMND;
			
//			string line; string value;
//	        while (getline(filein, line))
//	        {
//	            istringstream iss(line);
//	            string City, Country, Population;
//
//	         
//	
//	            if (getline(iss, City, ' ') && getline(iss, Country, ' ') && iss >> Population)
//	               
//					  value = City + Country + Population;
//				psg.Surname = value;
//	        }
			
//			filein >> lot;
			filein>>psg.Surname;
			filein>>lot;
			strcat(psg.Surname, " ");
			strcat(psg.Surname, lot);
			filein>>psg.Name;
			filein>>psg.Gender;
			
			AVLTree new_Psg = CreateTree(psg);
			
			root = AddPassenger(root,new_Psg);
		}
	}
	
}

/*Di chuyen thanh sang */
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

/* trang thai cho ngoi  */
int CheckStatus(Flight F, int x) {
	
	for(int i=0;i< F.saleTotal; i++) {
		if(x== F.TicketList[i].Status) return 1;
	}
	
	return 0;
}

/* hien thi 1 cho ngoi  */
void TicketSlot(int x, int y, int pos, int status) {
	
	SetColor(243);
	SetBGColor(0);

	gotoxy(x,y-1);
	cout << char(176) << setw(3) << setfill(char(176)) << char(176) << char(176);
	gotoxy(x, y);
	cout << char(176) << setw(3) << setfill('0')<<pos<<char(176);
	/*ve duong ke ben duoi cua cai ve*/
	gotoxy(x,y+1);
	if (status == 1) {
		SetBGColor(248);
	}
	cout << char(176) << setw(3) << setfill(char(176)) << char(176) << char(176);

}

/* So do cho ngoi  */
void TicketSlotTable(Flight F) { 
	int x = X_Ticket+ 8;
	int y = Y_Ticket + 5;	
	int Limit = F.totalTicket;
	
	for(int i=1; i<= Limit; i++) {
	
			TicketSlot(x,y,i, CheckStatus(F,i));
		
			x += 8;
			if(i%10 ==0) {
				y+=5;
				x = X_Ticket + 8;		
			}
	}
}


/* So do dat ve */
int ChooseTicket(Flight F) { 
	ShowCur(false);
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
			case ENTER:
				if(CheckStatus(F,CurPosTicket) == 1) {
				SetColor(243);
				gotoxy(3, 5);
				cout << "Ve nay da co Hanh khach dat cho";
				Sleep(1000);
				gotoxy(3, 5);
				printf("%-50s", " ");
				break;
				}
				quit = true;
				return CurPosTicket;
				
				
		}
	}
	
	
}



void CreatePassenger(AVLTree &root,bool &Save, bool Edit, bool Del, int ID) { // nhap new in4 passenger
	Save = true;
	
	int order = 1;
	string firstName;
	string lastName;
	int gender = 1; // 0 : female , 1: male
	
	gotoxy(x_add+10,4*3+y_add); cout<<" 0 la nu , 1 la nam";
	
	int ch ;
	bool quit = false;
	
	while(!quit) {
		
		switch(order) {
			
			case 1 : // input ho
				{
					ConstraintsForLetterAndSpace(firstName,Save,order,12);
					if(Save == false)  { RemoveFormComplete(); return;}
					
					if(firstName == "")	{
						BaoLoi("Khong bo trong");continue;
					} 					 
					
				}
					order++;
				
					break;
			case 2: // ten
				{
					ConstraintLetter(lastName,order,Save, 12);
					if(Save == false)  { RemoveFormComplete(); return;}
					
					if(lastName ==  "") {
						BaoLoi("Khong bo trong");continue;
					}
					
					order++;
					break;
				
					
				}
			case 3: // gioi tinh
				{
					ConstraintForOnlyGender(gender,order,Save,12);
			
					if(Save == false ) { RemoveFormComplete(); return;}
					if(gender == -1) {
						BaoLoi("Khong bo trong"); continue;
					}
					
					
				
				}
				order++;
				break;
			case 4:
				{
					Passenger psg;
					psg.CMND = ID;
					stringOptimize(firstName);
					StandardName((char*)firstName.c_str());
					strcpy(psg.Surname,firstName.c_str());
					stringOptimize(lastName);
					StandardName((char*)lastName.c_str());
					strcpy(psg.Name,lastName.c_str());
					psg.Gender = gender;
					
					AVLTree newPsg =  CreateTree(psg);
				
					root =  AddPassenger(root,newPsg);
					
					BaoLoi("Dat ve thanh cong !");		
					return;
					
				}
				quit = true;
				break;
				
			
		}
	
	}
	
}

void DisplayList(string content[], int nContent, int count) { // display content
	
	system("color 0E");
	SetColor(14);
	SetBGColor(0);
	for(int i=0; i< nContent; i++) {
		gotoxy(xKeyDisplay[i], Y_Display);
		cout<<content[i];
	}
	
	
}

void showPassenger(Passenger psg, int pos) { // show 1 hanh khach tu ds ve
	
	int temp_Y = Y_Display+3;
	
	gotoxy(xKeyDisplay[0], temp_Y+ pos*3);printf("%-5d" ,pos+1);
	gotoxy(xKeyDisplay[1], temp_Y+ pos*3);printf("%-12d", psg.CMND);
	gotoxy(xKeyDisplay[2], temp_Y+ pos*3);printf("%-20s", psg.Surname);
	gotoxy(xKeyDisplay[3], temp_Y+ pos*3);printf("%-10s", psg.Name);
	gotoxy(xKeyDisplay[4], temp_Y+ pos*3);
	if(psg.Gender == 1) cout<<"Nam"; else cout<<"Nu";


}

void showPassengerOfFlight(AVLTree root,Flight curFlight) { // ham show ds ve 1 chuyen bay
	
	ShowCur(false);
	DisplayList(ContentPassenger,5,curFlight.saleTotal);
	for(int i=0; i< curFlight.saleTotal; i++) {
	
		PassengerNode *temp = findPassenger(root,curFlight.TicketList[i].CMND);
		if(temp == NULL) continue;
		showPassenger(temp->data,i);
	}
}

void WatchPassengerList(AVLTree root) { // xem danh sach ve cac chuyen bay theo macb
	system("cls");
	system("color 0E");
	gotoxy(X_Title, Y_Title);
	cout << "Vui long nhap ma chuyen bay : ";
	CreateForm(ContentFlight,0,1,10);
	int order = 0;
	bool Save = true;
	string result;
	PTR_FL currentFlight = NULL; 
	bool quit = false;
	while(!quit) {
		ConstraintLetterAndNumber(result,order,Save, 15);
		if(Save == false)  { RemoveFormComplete(); return;}
		
		currentFlight = findFlight(FL, result.c_str());
		if(currentFlight == NULL) {
			 BaoLoi("MaCB khong ton tai");
		}
		else {
			RemoveFormComplete();
			quit = true;
		}
	}
	
		gotoxy(X_Title, Y_Title);
			cout << " Danh sach hanh khach co ma chuyen bay " << currentFlight->flight.flightCode << " toi " << currentFlight->flight.arrivalPlace<< " luc ";
			OutputDateTime(currentFlight->flight.departTime);
			
	showPassengerOfFlight(root, currentFlight->flight);
	
	int signal;
	while(true) {
		while( _kbhit() )
			{
				signal = _getch();
				if( signal == ESC )
				{
					return;
				}
			}
	}
}


void CancelFlightTicket(AVLTree root) { // huy ve mb
	system("cls");
	gotoxy(X_Title, Y_Title);
	cout << "Nhap ma chuyen bay de kiem tra : ";
	string IDFlight;
	CreateForm(ContentFlight, 0,1,0);
	bool quit = false;
	bool Save = true;
	int order = 0;
	FlightNode *currentFL = NULL;
	
	while(!quit) {
		
		system("color 0E");
		ConstraintLetterAndNumber(IDFlight, order, Save, 15);
		if(Save == false) return;
		
		currentFL = findFlight(FL,IDFlight.c_str());
		if(currentFL == NULL) BaoLoi("CB khong ton tai");
		else {
			if(currentFL->flight.status== 1)
			{
				BaoLoi("Chuyen bay da HUY hoac HOAN TAT");
				continue;
			}
			else {
				system("cls");
				quit = true;
			}
		}
	
	}
	
	gotoxy(X_Title, Y_Title);
	cout << "Nhap CMND de kiem tra  ";
	CreateForm(ContentPassenger,1,2,0);
	
	int IDPsg = 0; int target = -1;
	while(true) {
		ConstraintNumber(IDPsg,order,Save,12,99999);
		if(Save == false) return;
		
		for(int i=0; i< currentFL->flight.saleTotal; i++) if(currentFL->flight.TicketList[i].CMND == IDPsg) { // check ds cac ve da dat
			target = i;
			break;
		}
		
		if(target == -1) { BaoLoi("Khong tim thay trong DSV ");
		}
		else break;
	}	
	
	for(int i=target; i< currentFL->flight.saleTotal-1; i++) {  // xoa tai vi tri target
		currentFL->flight.TicketList[i] = currentFL->flight.TicketList[i+1];
	}
	currentFL->flight.saleTotal--;
	BaoLoi("Xoa thanh cong");
	
	
}



/* Dat ve may bay*/
void BookTicket(AVLTree &root) { 

	system("cls");
	system("color 0E");
	gotoxy(X_Title, Y_Title);
	cout << "Vui long nhap ma chuyen bay  ";
	CreateForm(ContentFlight, 0, 1,0);
	bool flag = false;
	int order = 0;
	bool Save = true;
	string result;
	PTR_FL currentFlight = NULL; 
	bool quit = false;
	ShowCur(true);
	
	while(flag == false ) {
		ConstraintLetterAndNumber(result,order,Save, 15);
		if(Save == false) {
			return;
		}
		
		currentFlight = findFlight(FL, result.c_str());
		
		if(currentFlight == NULL) BaoLoi("CB khong ton tai ");
		
		else {
			if(currentFlight->flight.status == 1 || currentFlight->flight.status ==4 ||currentFlight->flight.status ==3) {
				
				BaoLoi("Chuyen bay da HUY hoac HOAN TAT hoac HET VE, vui long nhap lai ");
				continue;
			} 
			flag = true;
		
	}
}
		system("cls");
		
		while(true) {
			Save = true;
			int IDHanhKhach=0; int target = -1;
			gotoxy(X_Title, Y_Title);
			cout << " Danh sach hanh khach co ma chuyen bay " << currentFlight->flight.flightCode << " toi " << currentFlight->flight.arrivalPlace<< " luc ";
			OutputDateTime(currentFlight->flight.departTime);
			
			gotoxy(20,8);
			cout<<"Warn: VE MAU DO LA DA CO NGUOI DAT ROI !!";
		
			system("color 0E");
			int choosen = ChooseTicket(currentFlight->flight);
			
			if(choosen == -1) return;
			ShowCur(true);
			system("cls");
			system("color 0E");
			gotoxy(X_Title+15,Y_Title+2);
			cout<<"Nhap CMND -> ";
			
			
			CreateForm(ContentPassenger,1,2,30);			
		
			ConstraintForOnlyNumber(IDHanhKhach, order, Save, 12, 999999);
			
			if(Save == false) {
			
				RemoveFormComplete();
				continue;
			
			};
			
			PTR_FL k = checkDupOnOtherFlight(FL.pHead,currentFlight, IDHanhKhach);
			
			if(k != NULL) { // dat 2 cb, co trung lich ?????
			
				BaoLoi("Khach da dat tren mot chuyen bay khac cung lich");
				continue;
			}
			
			for(int i=0; i< currentFlight->flight.saleTotal; i++) { // da dat tren chuyen hien tai chua ?????
				
				if(currentFlight->flight.TicketList[i].CMND == IDHanhKhach) { // tim trong danh sach ve ? co ton tai hanh khach cmnd ?
					target = i;
					break;
				}
			
			}
			
			if(target > -1) {
				
				BaoLoi("Ban da dat ve roi");
				RemoveFormComplete();
				continue;
			
			}
			
			if(target == -1) { // khong co trong listTicket
				
				PassengerNode* findedPassenger = findPassenger(root,IDHanhKhach);
			
				if(findedPassenger == NULL) {
					CreateForm(ContentPassenger, 1, 5, 27);
					CreatePassenger(root,Save,true,false,IDHanhKhach);
					nPassenger++;
					if(Save == false) continue;
			
				}
				
				
			
				RemoveFormComplete();
			
			
				Ticket newTicket;
				newTicket.CMND = IDHanhKhach;
				newTicket.Status = choosen;
				
				currentFlight->flight.TicketList[currentFlight->flight.saleTotal] = newTicket ;
				currentFlight->flight.saleTotal++;
				
			}
		
		}	

}




