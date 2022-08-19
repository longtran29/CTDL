#pragma once

char thucdon [so_item][50] = {  "1.Quan Li Cac May Bay",
					   "2.Quan Li Cac Chuyen Bay",
					   "3.Dang Ky Ve May Bay",
					   "4.Huy Bo Ve May Bay",
					   "5.Xem Danh Sach Hanh Khach Chi Tiet",
					   "6.Xem Chi Tiet So Lan Thuc Hien Chuyen Bay",
					   "7.Xem So Do Cho Ngoi & Danh Sach Ve Con Trong",
					   "8.Xem Cac Chuyen Bay Di Toi Cac Dia Danh",
					   "0. Thoat chuong trinh"};
			          



void MenuCenter(){
	
	ReadAirplaneFile(planeList);
	int chon = 0;
	initFlightList(FL);
	
	ReadFlightFromFile(FL);
	CreateAVLTree(root);
	LoadPassengerFromFile(root);
	bool Exit =false;
	
	
	
	while (!Exit) {
		chon = MenuDong (thucdon);

		clrscr();
		switch(chon) {
				
			case 1:
				MenuManageAirplane(planeList);
				break;
				
			case 2 :
				ManageFlightPlane(FL);
				break;
			case 3:
				BookTicket(root);
				break;
			case 4:
				CancelFlightTicket(root);
				break;
			case 5:
				WatchPassengerList(root);
				break;
			case 6:
				system("color 0E");
				WatchStatics();
				break;
			case so_item:
				
				WriteFlightToFile(FL);
				WriteAirplaneToFile(planeList);
				SavePassengerToFile(root);
				Exit = true;
				break;
				
		}
		
	}

	}
