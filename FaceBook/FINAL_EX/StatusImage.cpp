#include "StatusImage.h"

void StatusImage::printStatus()
{
	printColor();
	Status::printStatus();
	cout << "Image name: " << this->imgStr<< endl;
	string s = "start " + imgStr;
	system(s.c_str());
}

void StatusImage ::printColor()
{
	cout << "This status is printed colorful" << endl;
}

bool StatusImage:: operator ==(const Status& s)
{
	bool res;

	res = Status:: operator==(s);

	if (!res)
	{
		return res;
	}
	return this->imgStr == ((StatusImage&)s).imgStr;
}