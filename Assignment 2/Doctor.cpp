#include "Doctor.h"

Doctor::Doctor()
	: Person(), m_counter(0)
{
	for (int i = 0; i < MAXappointments; i++) { // initialize all the appointments to 0
		m_appointments[i].hours = 0;
		m_appointments[i].mins = 0;
	}
}

Doctor::Doctor(const string& name, const string& ID, const int& age)
// will not initialize the counter fomr the user
	: Person(name, ID, age), m_counter(0)
{
	for (int i = 0; i < MAXappointments; i++) { // initialize all the appointments to 0
		m_appointments[i].hours = 0;
		m_appointments[i].mins = 0;
	}
}

Doctor::Doctor(const Doctor& doctor) 
	: Person(doctor), m_counter(doctor.m_counter)
{
	for (int i = 0; i < MAXappointments; i++) { // deep copying the array of appointments
		m_appointments[i] = doctor.m_appointments[i];
	}
}

Doctor::~Doctor() 
{}

bool Doctor::checkAvailability(const appointment& app) {
	if (m_counter > 24) // the doctor has reached his maximum number of appointments
		return false;
	for (int i = 0; i < m_counter; i++) { // iterate through the reserved appointments
		// if there's a time conflict 
		if ((app.hours == m_appointments[i].hours)
			&& (app.mins == m_appointments[i].mins)) {
			return false;
		}
	} // else
	return true;
}

void Doctor::addAppointment(const appointment& app) { 
	/* this function will add the appointment instantly because the appointment will have been checked 
	available before so */
	m_appointments[m_counter].hours = app.hours; 
	m_appointments[m_counter].mins = app.mins;
	m_counter++;
}