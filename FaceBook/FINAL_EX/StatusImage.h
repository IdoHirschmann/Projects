#pragma once
#include "Status.h"
#include <stdlib.h>
class StatusImage:public Status
{
	string imgStr;
public:
	StatusImage(const string _data, string _imgStr) :Status(_data), imgStr(_imgStr + ".jpg")
	{

	}
	virtual void printStatus() override;
	virtual void printColor() override;
	virtual string getAddData() const override
	{
		return imgStr.substr(0, imgStr.size() - 4);
	}
	virtual bool operator ==(const Status& s) override;
	virtual ~StatusImage() = default;
};

