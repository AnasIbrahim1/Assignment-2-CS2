#pragma once
#include "Person.h"

class Patient : public Person
{
private:
	appointment m_Appointment;
	string m_DoctorID;
	string m_DoctorName;
public:
	Patient();
	Patient(const string&, const string&, const int&, const int&, const int&, const string&);
	Patient(const Patient&);
	~Patient();
	bool operator < (const Patient&);
	bool operator > (const Patient&);
	bool operator == (const Patient&);
	
	void setAppointment(const appointment&);
	void setDocID(const string&);
	void setDoctorName(const string&);

	appointment getAppointment() const;
	string getDocID() const;
	void print();
};

