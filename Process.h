#pragma once


void WriteAirplaneToFile(listPlane &list)
{
	ofstream fileout;
	fileout.open("DSMB.TXT",ios_base::out);// ios_base::out la de ghi vao file
	if( fileout.is_open() )
	{
		for( int i = 0 ; i < list.n ; i++)
		{
			fileout << list.planes[i]->serialPlane <<" "<<list.planes[i]->typePlane<<" "<<list.planes[i]->seats<<endl;
		}
	}
	else
	{
		gotoxy(X_Notification,Y_Notification+1);
		cout << " Ket noi file de ghi vao that bai";
	}
	fileout.close();
}
