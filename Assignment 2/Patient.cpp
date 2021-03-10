#include "Patient.h"

Patient::Patient()
	: Person(), m_Appointment(0,0), m_DoctorID("")
{}

Patient::Patient(const string& name, const string& ID, const int& age, 
	const int& hours, const int& mins, const string& DoctorID)
	: Person(name, ID, age), m_Appointment(hours, mins), m_DoctorID(DoctorID)
{}

Patient::Patient(const Patient& patient) 
	: Person(patient), m_Appointment(patient.m_Appointment),
	m_DoctorID(patient.m_DoctorID), m_DoctorName(patient.m_DoctorName)
{}

Patient::~Patient()
{}

bool Patient::operator < (const Patient& patient) {
	if (m_Appointment.hours == patient.m_Appointment.hours)
		return (m_Appointment.mins < patient.m_Appointment.mins);
	else
		return (m_Appointment.hours < patient.m_Appointment.hours);
}

bool Patient::operator > (const Patient& patient) {
	if (m_Appointment.hours == patient.m_Appointment.hours)
		return (m_Appointment.mins > patient.m_Appointment.mins);
	else
		return (m_Appointment.hours > patient.m_Appointment.hours);
}

bool Patient::operator == (const Patient& patient) {
	return ((m_Appointment.hours == patient.m_Appointment.hours)
		 && (m_Appointment.mins == patient.m_Appointment.mins));
}

void Patient::setAppointment(const appointment& appointment) {
	m_Appointment = appointment; // using the struct's default copy constructor
}

void Patient::setDocID(const string& DocID) {
	m_DoctorID = DocID;
}

void Patient::setDoctorName(const string& DocName) {
	m_DoctorName = DocName;
}

appointment Patient::getAppointment() const {
	return m_Appointment;
}

string Patient::getDocID() const {
	return m_DoctorID;
}

void Patient::print() {
	Person::print();
	cout << "The appointment the patient booked is at ";
	cout << m_Appointment.hours << ":";
	if (m_Appointment.mins < 10)
		cout << "0" << m_Appointment.mins;
	else
		cout << m_Appointment.mins;
	cout << " with Dr. " << m_DoctorName << " (ID = " << m_DoctorID << ")" << endl << endl;
}