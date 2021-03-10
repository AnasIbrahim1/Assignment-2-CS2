#pragma once
#include "Person.h"
#include <stdexcept>
using namespace std;

const int MAXappointments = 24; // the maximum number of appointments a doctor can take

class Doctor : public Person
{
private:
	int m_counter;
	appointment m_appointments[MAXappointments];
public:
	Doctor();
	Doctor(const string&, const string&, const int&);
	Doctor(const Doctor&);
	~Doctor();
	void addAppointment(const appointment&);
	bool checkAvailability(const appointment&);
};

