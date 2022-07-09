#pragma once


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
