#pragma once
#include <iostream>
#include <string>
using namespace std;
#ifndef PERSON_H
#define PERSON_H

struct appointment {
	int hours;
	int mins;
	appointment() 
		: hours(0), mins(0)
	{}
	appointment(const int& hrs, const int& m)
		: hours(hrs), mins(m)
	{
	}
};

class Person
{
private:
	string m_Name;
	string m_ID;
	int m_Age;
public:
	Person();
	Person(const string&, const string&, const int&);
	Person(const Person&);
	~Person();

	void setName(const string&);
	void setID(const string&);
	void setAge(const int&);

	string getName() const;
	string getID() const;
	int getAge() const;

	void print();
};
#endif

