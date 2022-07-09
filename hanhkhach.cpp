#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include "F:\mylib.h"
#include<iomanip>
#include<fstream>
#include "DefineConst.h"
#include "graphic.h"
#include "Airplane.h"
#include "Interfaces.h"


struct Customer {
	char ID_Card[10];
	char Surname[10];
	char Name[30];
	bool Gender; //true:nam-false:nu
};
typedef struct Customer KH;

struct nodeKH {
	KH data;
	struct nodeKH* left = NULL;
	struct nodeKH* right = NULL;
};
typedef nodeKH* TREE;

int main() {



	MenuCenter();



	return 0;
}
