#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <mylib.h>
#include<iomanip>
#include "DefineConst.h"
#include "graphic.h"
#include "Airplane.h"
#include "Interfaces.h"





struct Passenger {
	char indentity[12];
	char familyName[6];
	char firstName[8];
	char Gender[4];
};



struct Flight {

	char serialNumber[4];
	char departTime[15];
	char arrivalPlace[20];
	boolean status;

};




int main() {
	

			
	MenuCenter();

	
	
	return 0;
}
