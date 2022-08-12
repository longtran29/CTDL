#pragma once
#include <ctime>


int dayInMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

typedef struct DateTime {
	
	int ngay;
	int thang;
	int nam;
	int gio;
	int phut;
	
} datetime;


datetime initTime() {
	datetime now;
	time_t baygio = time(0);
	tm* ltm = localtime(&baygio);
	
	now.ngay = ltm->tm_mday;
	now.thang = 1+ ltm->tm_mon;
	now.nam = 1900 + ltm->tm_year;
	now.gio = ltm->tm_hour;
	now.phut = ltm->tm_min;
	
	return now;	
	
}

void InitDataTime(datetime &dt) {

	time_t baygio = time(0);
	tm* ltm = localtime(&baygio);
	
	dt.ngay = ltm->tm_mday;
	dt.thang = 1+ ltm->tm_mon;
	dt.nam = 1900 + ltm->tm_year;
	dt.gio = ltm->tm_hour;
	dt.phut = ltm->tm_min;
	
}


bool DateTimeFormart(datetime &dt) {
	dayInMonth[2] =28;
	if((dt.nam % 400 == 0) || (dt.nam % 4 ==0 && dt.nam %100 !=0)) dayInMonth[2] =29;
	if(dt.ngay > dayInMonth[dt.thang]) return false;
	return true;	
}


bool checkValidDT(datetime dt) {
	
	if(!DateTimeFormart(dt)) return false;
	
	datetime now = initTime();
	
	if(dt.nam < now.nam) return false;
	if((dt.nam == now.nam) && (dt.thang< now.thang)) return false;
	if(dt.nam == now.nam && dt.thang == now.thang && dt.ngay< now.ngay) return false;
	if(dt.nam == now.nam && dt.thang == now.thang && dt.ngay ==  now.ngay && dt.gio< now.gio) return false;
	if(dt.nam == now.nam && dt.thang == now.thang && dt.ngay== now.ngay && dt.gio ==  now.gio && dt.phut < now.phut) return false;
	
	return true;	
}


void OutputDateTime(datetime dt)
{
	cout << dt.gio << ":" << dt.phut << " " << dt.ngay << "/" << dt.thang << "/" << dt.nam;
}



bool checkDateTime(DateTime dt1, DateTime dt2) {
	
	if(dt1.gio == dt2.gio && dt1.nam==dt2.nam && dt1.ngay== dt2.ngay && dt1.phut == dt2.phut && dt1.thang == dt2.thang)
		return true;
	return false;
}




