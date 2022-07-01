#pragma once


char thucdon [so_item][50] = {"1. Nhap danh sach hoc vien",
			                  "2. Liet ke danh sach      ",
			                  "3. Sua danh sach may bay  ",
			                  "4. Ghi mot hoc vien       ",
			                  "5. Ghi danh sach          ",
			                  "6. Mo  danh sach          ",
			                  "7. Them sv co thu tu      ",
			                  "8. Ket thuc chuong trinh  "};
			          
					  



void MenuCenter() {
	

	listPlane planeList;
	int chon = 0;
	int vitri;
	
	
	do {
		
		chon = MenuDong (thucdon);
		system ("cls");
		switch(chon) {
				
			case 1:
			Nhap_DS_MB(planeList);
			break;
				
			case 2 :
				Xuat_DS_MB(planeList);
				break;
			case 3:
//				Chinh_Sua_MB(planeList);
				break;
			case 4:
//				SaveFile(planeList, filename);
				break;
			case 5:
				break;
			
			
			
		}
		
		
	}
	while(1);
	
	
	
	}
