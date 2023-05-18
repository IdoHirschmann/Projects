
#ifndef PROJECT1_DATE_H
#define PROJECT1_DATE_H


#include <iostream>
#include <string>
enum month { January = 1, February, March, April, May, June, July, August, September, October, November, December };
using namespace std;
const int DEFAULT_DAY = 1;
const int DEFAULT_MONTH = 1;
const int DEFAULT_YEAR = 2000;
const int MAX_DAY = 31;
const int MAX_MONTH = 12;
const int MAX_YEAR = 2022;
const int MIN_DAY = 1;
const int MIN_MONTH = 1;
const int MIN_YEAR = 1900;

class Date
{
    int day, month, year;

public:
    //Deafualt cto'r
    Date() : day(DEFAULT_DAY), month(DEFAULT_MONTH), year(DEFAULT_YEAR)
    {
    }

    //Full cto'r
    Date(int day, int month, int year)
    {   
        try
        {
            setDay(day);
        }
        catch (dayExp& ex)
        {
            day = DEFAULT_DAY;
            cout << ex.what();
        }
        try
        {
            setMonth(month);
        }
        catch (monthExp& ex)
        {
            month = DEFAULT_MONTH;
            cout << ex.what();
        }
        try
        {
            setYear(year);
        }
        catch (yearExp& ex)
        {
            year = DEFAULT_YEAR;
            cout << ex.what();
        }
     
    }

    class dayExp : public exception
    {
        string exp;
    public:
        dayExp()
        {
            exp = "The input is invalid, the day will have default value and will set as " + to_string(DEFAULT_DAY) + ".\n";
        }
        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class monthExp : public exception
    {
        string exp;
    public:
        monthExp()
        {
            exp = "The input is invalid, the month will have default value and will set as " + to_string(DEFAULT_MONTH) + ".\n";
        }
        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class yearExp : public exception
    {
        string exp;
    public:
        yearExp()
        {
            exp = "The input is invalid, the year will have default value and will set as " + to_string(DEFAULT_YEAR) + ".\n";
        }
        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

private: //set funcs are private because it is there for to check if date enterd is valid, but no user should or will change his or anyone else birth date
    //Getters & Setters
    void setDay(int day)
    {
        if (day >= MIN_DAY && day <= MAX_DAY)
        {
            this->day = day;
        }
        else
        {
            throw(dayExp());
        }
    }
    void setMonth(int month)
    {
        if (month >= MIN_MONTH && month <= MAX_MONTH)
        {
            this->month = month;
        }
        else
        {
            throw(monthExp());
        }
    }
    void setYear(int year)
    {
        if (year >= MIN_YEAR && year <= MAX_YEAR)
        {
            this->year = year;
        }
        else
        {
            throw(yearExp());
        }
    }

public:
    int getDay()
    {
        return day;
    }
    int getMonth()
    {
        return month;
    }
    int getYear()
    {
        return year;
    }
};


#endif //PROJECT1_DATE_H

