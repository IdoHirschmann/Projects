#pragma once
#include "Status.h"
#include "StatusVid.h"
#include "StatusImage.h"
class StatusFactory
{
public:

	 Status * CreateStatus(string data, string type, string additionalStr)
	{
		if (data.empty())
			throw(emptyData());
		if (type == "Reg")
		{
			return new Status(data);
		}
		else if (type == "Video")
		{
			if (additionalStr.empty())
				throw(invalidFileNameData());
			return new StatusVid(data, additionalStr);
		}
		else if(type == "Image")
		{
			if (additionalStr.empty())
				throw(invalidFileNameData());
			return new StatusImage(data, additionalStr);
		}
		else
		{
			throw(invalidStatusType());
		}
	}

	class invalidStatusType : public exception
	{
		string exp;
	public:
		invalidStatusType()
		{
			exp = "Type is not valid status type. \n";
		}
		char const* what() const noexcept
		{
			return exp.c_str();
		}

	};

	class emptyData : public exception
	{
		string exp;
	public:
		emptyData()
		{
			exp = "Invalid data. Empty statuses are not allowed. \n";
		}
		char const* what() const noexcept
		{
			return exp.c_str();
		}

	};

	class invalidFileNameData : public exception
	{
		string exp;
	public:
		invalidFileNameData()
		{
			exp = "Invalid file name. Empty file names are invalid. \n";
		}
		char const* what() const noexcept
		{
			return exp.c_str();
		}

	};

};

