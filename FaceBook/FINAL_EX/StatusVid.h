#pragma once
#include "Status.h"
#include <stdlib.h>

class StatusVid:public Status
{
	string vidStr;
public:
	StatusVid(const string _data,string _vidStr):Status(_data),vidStr(_vidStr + ".mov")
	{
		
	}

	virtual	void printStatus() override;

	virtual void printColor() override;

	virtual bool operator ==(const Status& s) override;

	virtual string getAddData() const override
	{
		return vidStr.substr(0, vidStr.size() - 4);
	}

	virtual ~StatusVid() = default;
};

