#pragma once

void ConstraintLetterAndNumber(string &chuoi, int order, int width) {
	int lenght = (int)chuoi.length();
//	gotoxy(x_add + width,order * 3 + y_add);
	gotoxy(x_add+width,order*3+y_add);
	cout << chuoi;
	int count = lenght;

	bool quit = false;
	while(!quit)
	{
			int signal = _getch();
			if(signal != 224 && signal != BACKSPACE && signal !=0) {
			
						if( ( 65 <= signal && signal <= 90 ) || ( 97 <= signal && signal <= 122 ) || ( 48 <= signal && signal <= 57 ) )
						{
							
							if( count < 15 )
							{
								count++; 
								cout << (char)signal;// hien thi
								chuoi += (char)signal;// cap nhat 
							}
						}
						
						else if(signal == ESC){
							quit = true;
							
						
							}
						else if(signal == ENTER) {
							return;
						}
					
					}
					
	
			else if(signal == BACKSPACE && count >0) {
				putch('\b');
				putch(' ');
				putch('\b');
				chuoi.erase(chuoi.length()-1, 1);
				count--;
			}
	

}
}
