#include "StatusVid.h"

//prints statusVid obj 
void StatusVid::printStatus()
{
	printColor();
	Status::printStatus();
	cout << "Video name: " << this->vidStr<< endl;
	string s = "start " + vidStr;
	system(s.c_str());
}
//prints "the color" of the stratus
void StatusVid::printColor()
{
    cout << "This status is printed colorful" << endl;
}

 bool StatusVid:: operator ==(const Status& s)
{
	 bool res;

	 res = Status:: operator==(s);

	 if (!res)
	 {
		 return res;
	 }
	 return this->vidStr == ((StatusVid &)s).vidStr;
}