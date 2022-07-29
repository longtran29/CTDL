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
					BaoLoi("Ghe nay da co ng dat");
					break;
				}
				quit = true;
				return CurPosTicket;
				
				
		}
	}
	
	
}

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

PassengerNode* findPassenger(AVLTree root, int CMND) {
	
	if(root == NULL) return NULL;
	 else if(root->data.CMND == CMND) return root;
	
	else if(root->data.CMND > CMND) return findPassenger(root->pLeft, CMND);
	else return findPassenger(root->pRight, CMND);
	
}

AVLTree AddPassenger(AVLTree root, AVLTree newPsg) {
	
	if(root == NULL) {
		root = newPsg;
		BaoLoi("Inserted !");
		return root;
	}
	
	else if(newPsg->data.CMND < root->data.CMND) root->pLeft =  AddPassenger(root->pLeft, newPsg);
	else if(newPsg->data.CMND > root->data.CMND) root->pRight  = AddPassenger(root->pRight, newPsg);
	
	else return root;
	
	int bf = getBalanceFactor(root);
	
	
	// left left case
	if(bf> 1  && newPsg->data.CMND < root->pLeft->data.CMND) return rightRotate(root);
	
	// right right case
	if(bf <-1 && newPsg->data.CMND > root->pRight->data.CMND) return leftRotate(root);
	//left right case
	if(bf>1 && newPsg->data.CMND > root->pLeft->data.CMND) {
		root->pLeft = leftRotate(root->pLeft);
		return rightRotate(root);
	}
	
	// right left case
	if(bf<-1 && newPsg->data.CMND < root->pRight->data.CMND) {
		root->pRight = rightRotate(root->pRight);
		return leftRotate(root);
	}
	
	// giu nguyen nut goc 
	return root;
	
	
	
}



void CreatePassenger(AVLTree root, bool Edit, bool Del, int ID) {
	bool Save = true;
	
	int order = 1;
	string firstName;
	string lastName;
	int gender = 1; // 0 : female , 1: male
	
	
	gotoxy(X_Notification, Y_Notification); cout<<" 0 la nu , 1 la nam";
	
	int ch ;
	
	while(true) {
		
		switch(order) {
			
			case 1 : // input ho
				{
					ConstraintsForLetterAndSpace(firstName,Save,order,12);
					if(Save == false) {
						return ;
					}
					
					if(firstName == "")	{
						BaoLoi("Khong bo trong");
					} else order++; 					 
					
				}
				
					break;
			case 2: // ten
				{
					ConstraintLetter(lastName,order,Save, 12);
					if(Save == false) return;
					
					if(lastName ==  "") BaoLoi("Khong bo trong");
					
					order++;
					break;
				
					
				}
			case 3: // gioi tinh
				{
					ConstraintForOnlyGender(gender,order,Save,12);
			
					if(Save == false ) return;
					if(gender == -1) BaoLoi("Khong bo trong");
					
					order++;
				
				}
				break;
			case 4:
				{
					Passenger psg;
					psg.CMND = ID;
					strcpy(psg.Surname,firstName.c_str());
					strcpy(psg.Name,lastName.c_str());
					psg.Gender = gender;
					
					AVLTree newPsg =  CreateTree(psg);
					
					AddPassenger(root,newPsg);
					BaoLoi("Add sucess !");
					RemoveFormComplete();				
					return;
					
				}
				break;
			
		}
		
		
		
		
		
	}
	
	
	
	
	
}



void BookTicket(AVLTree root) {

	system("cls");
	system("color 0E");
	gotoxy(X_Title, Y_Title);
	cout << "Vui long nhap ma chuyen bay : ";
	
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
		
		
		while(1) {
			
			gotoxy(X_Title, Y_Title);
			cout << " Danh sach hanh khach co ma chuyen bay " << currentFlight->flight.flightCode << " toi " << currentFlight->flight.arrivalPlace<< " luc ";
			OutputDateTime(currentFlight->flight.departTime);
			
			gotoxy(20,5);
			cout << "Warn: VE MAU DO LA DA CO NGUOI DAT ROI !!";
			
			system("color 0E");
			int choosen = ChooseTicket(currentFlight->flight);
			
			if(choosen == -1) return;
			ShowCur(true);
			
			gotoxy(X_Title,Y_Title);
			
			system("cls");
			
			
			system("color 0E");
			cout<<"Nhap CMND :";
			int IDHanhKhach = 0; int target = -1;
			
			CreateForm(ContentPassenger,1,5,30);			
		
			ConstraintForOnlyNumber(IDHanhKhach, order, Save, 12, 999999);
			
			if(Save == false) continue;
			
			for(int i=0; i< currentFlight->flight.saleTotal; i++) {
				
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
				
				BaoLoi("Khong tim thay !");
				
				if(findedPassenger == NULL) {
					CreateForm(ContentPassenger, 1, 5, 27);
					CreatePassenger(root,false,false,IDHanhKhach);
			
				}
			
				Ticket newTicket;
				newTicket.CMND = IDHanhKhach;
				newTicket.Status = choosen;
				
				currentFlight->flight.TicketList[currentFlight->flight.saleTotal] = newTicket ;
				currentFlight->flight.saleTotal++;
			}
		
		}	

		


}
