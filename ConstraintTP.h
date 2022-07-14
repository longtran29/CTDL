#pragma once

void ConstraintLetterAndNumber(string &chuoi, int order, int width) {
	int lenght = (int)chuoi.length();
//	gotoxy(x_add + width,order * 3 + y_add);
	gotoxy(x_add+width,order*3+y_add);
	cout << chuoi;
	int count = lenght;
	int signal;
	while(true)
	{
			signal = getch();
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
							return ;
							
						
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


void ConstraintLetter(string &chuoi, int order, int width) {
	int lenght = (int)chuoi.length();
//	gotoxy(x_add + width,order * 3 + y_add);
	gotoxy(x_add+width,order*3+y_add);
	cout << chuoi;
	int count = lenght;

	while(true)
	{
			int signal = _getch();
			if(signal != 224 && signal != BACKSPACE && signal !=0) {
			
						if( ( 65 <= signal && signal <= 90 ) || ( 97 <= signal && signal <= 122 ) )
						{
							
							if( count < 15 )
							{
								count++; 
								cout << (char)signal;// hien thi
								chuoi += (char)signal;// cap nhat 
							}
						}
						
						else if(signal == ESC){
							return ;
							
						
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


void ConstraintNumber(int &num, int order, int width, int limitseats) {
	gotoxy(x_add+width,order*3+y_add);
	cout<<num;
	
	while(true)
	{
			int signal = _getch();
			if(signal != 224 && signal != BACKSPACE && signal !=0) {
			
						if(  48 <= signal && signal <= 57 )
						{
							
							int result = signal - 48;
							if(signal == 48) {
								continue;	
							}
							else if((num*10+ result) < limitseats ) {
								
								num = num * 10 +result;
								cout<<result;
							
							}
						}
						
						else if(signal == ESC){
							return ;
							
						
							}
						else if(signal == ENTER) {
							return;
						}
					
			}
			else if(signal == BACKSPACE  ) {
				cout << (char)BACKSPACE<<" "<<(char)BACKSPACE;
				num /=10;
			}
					
	
}
	
}

void ConstraintsForLetterAndSpace(string &destination,int order,int width) {
	gotoxy(x_add+width,order*3+y_add);
	int signal;
	int lens = (int) destination.length();
	while(true) {
		
		while(kbhit()) {
			
			while(true) {
				signal = getch();
				if(signal != 224 && signal != BACKSPACE && signal !=0 ) {
					if( ( 65 <= signal && signal <= 90 ) || ( 97 <= signal && signal <= 122 ) || signal == SPACE)
						{
							if(lens <= 20 )
							{
								lens++; 
								cout << (char)signal;
								destination += (char)signal;
							}
						}
					else if(signal == ESC) {
						return;
					}
					else if(signal == ENTER){
						return;
					}
			
				}
				else if(signal == BACKSPACE && lens >0)	 {
					
					cout << "\b" << " " << "\b";
						destination.erase(destination.length() - 1, 1);
						lens--;
				}
			
			
			}
			
		}
	}
	
}	

void ConstraintForOnlyNumber(int &num,int order,int width ,int maxTicket) {
	
	gotoxy(x_add+width,order*3+y_add);
	
	while(true)
	{
			int signal = _getch();
			if(signal != 224 && signal != BACKSPACE && signal !=0) {
			
						if(  48 <= signal && signal <= 57 )
						{
							
							int result = signal - 48;
							if(signal == 48) {
								continue;	
							}
							else if((num*10+ result) <= maxTicket ) {
								
								num = num * 10 +result;
								cout<<result;
							
							}
						}
						
						else if(signal == ESC){
							return ;
							
						
							}
						else if(signal == ENTER) {
							
							return;
						}
					
			}
			else if(signal == BACKSPACE  ) {
				cout << (char)BACKSPACE<<" "<<(char)BACKSPACE;
				num /=10;
			}
					
	
}
	
}


void ConstraintForDateAndTime(int &result,int &dtOrder,int space , int limit) {
	gotoxy(x_add + space + dtOrder * 3 +1 ,  9 + y_add);
	if( result != 0 )
		cout << result;
	int num = result;
	int count = 0;
	
	while(num > 0) {
		count++;
		num/=10;
		
	}
	
	int signal;
	while(true) {
		signal = getch();
		
		if(signal != 224 && signal != BACKSPACE && signal !=0) {
			
						if(  48 <= signal && signal <= 57 )
						{
							
							int minus = signal - 48;
							if(result > limit) {
								continue;
							}
							else if((result*10+ minus) < limit ) {
								
								count++;
								result = result *10 + minus;
								cout<<minus;
							
							}
						}
					
						else if(signal == ENTER) {
							if (result > limit || result ==0 ) continue;
							return;
						}
			}
						else if(signal == BACKSPACE && count >0  ) {
										cout << (char)BACKSPACE<<" "<<(char)BACKSPACE;
										count--;
										result /=10;
						}
	}
	
}

