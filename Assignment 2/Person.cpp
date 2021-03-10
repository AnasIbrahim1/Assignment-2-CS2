#include "Person.h"

Person::Person()
	: m_Name(""), m_ID(""), m_Age(0)
{}

Person::Person(const string& name, const string& ID, const int& age)
	: m_Name(name), m_ID(ID), m_Age(age)
{}

Person::Person(const Person& person)
	: m_Name(person.m_Name), m_ID(person.m_ID), m_Age(person.m_Age)
{}

Person::~Person()
{}

void Person::setName(const string& name) {
	m_Name = name;
}

void Person::setID(const string& ID) {
	m_ID = ID;
}

void Person::setAge(const int& age) {
	m_Age = age;
}

string Person::getName() const {
	return m_Name;
}

string Person::getID() const {
	return m_ID;
}

int Person::getAge() const {
	return m_Age;
}

void Person::print() {
	cout << "Name is: " << m_Name << endl;
	cout << "ID is: " << m_ID << endl;
	cout << "Age is: " << m_Age << endl;
}