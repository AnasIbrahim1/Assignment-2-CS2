#include <fstream>
#include "Doctor.h"
#include "Patient.h"
#include "my_queue.h"
using namespace std;

appointment convertAppointment(const string&); 
// this function is responsible for converting an appointment from a string
// of hours and minutes separated by a colon (e.g. 01:00), into hours and minutes
// of the appointment
void DoctorsFileFormat(); // explain the format of the Doctors' file
void PatientsFileFormat(); // explain the format of the Patients' file

void ReadDoctorsFromFile(Doctor*&, int&); // we input an alias to the pointer to be able to allocate
/* i.e. as "int y; int& x = y;" makes x an alias to y, "Doctor* Doctors; Doctor*& doctors = Doctors" makes
 doctors an alias to Doctors, then we can allocate "doctors = new Doctor[number];" and by so we 
have allocated Doctors too */
void DoctorsUserInput(Doctor*&, int&); 
void ReadPatientsFromFile(Patient*&, int&);
void PatientsUserInput(Patient*&, int&);
void clearScreen();

string temporaryString; // temporaryString string for input
int temporaryInteger; // temporaryString integer for input

int main() {
	// In this program, we're going to assume all inputs are valid.
	Doctor* Doctors;
	Patient* Patients;
	int numDoctors, numPatients;
	cout << "Choose from the following options of input for the doctors' data" << endl;
	cout << "1. Read from a file" << endl;
	cout << "2. Input the data manually here" << endl;
	cout << "Please enter 1 or 2: ";
	char c; // a character for 1 or 2 (chosen "char" because it's less in size)
	cin >> c;
	cout << endl;
	if (c == '1') {
		DoctorsFileFormat();
		ReadDoctorsFromFile(Doctors, numDoctors);
	}
	else  // c == '2' 
		DoctorsUserInput(Doctors, numDoctors);
	clearScreen(); // clear the screen after the input 
	cout << "Choose from the following options of input for the patients' data" << endl;
	cout << "1. Read from a file" << endl;
	cout << "2. Input the data manually here" << endl;
	cout << "Please enter 1 or 2: ";
	cin >> c;
	cout << endl;
	if (c == '1') {
		PatientsFileFormat();
		ReadPatientsFromFile(Patients, numPatients);
	}
	else // c == '2'
		PatientsUserInput(Patients, numPatients);
	clearScreen(); // clear the screen after the input 
	int j = 0; // counter inside the for loop, to get the index of the available doctor
	for (int i = 0; i < numPatients; i++) { // iterate through the patients and assign them to doctors
		while (!Doctors[j].checkAvailability(Patients[i].getAppointment()))
		{
			j++; // we linearly search for available doctors by getting the index
			j = j % numDoctors; // if the index is more than the number of doctors,
			// get back to how many elements after the end
		}
		Doctors[j].addAppointment(Patients[i].getAppointment()); // add the appointment to the doctor
		Patients[i].setDocID(Doctors[j].getID()); // set the doctor's ID to the patient
		Patients[i].setDoctorName(Doctors[j].getName()); // set the doctor's name to the patient
		j++; j = j % numDoctors;
	}
	cout << endl;
	// now it's time to sort the patients according to their appointments (using selection sort algorithm)
	for (int i = 0; i < numPatients - 1; i++) { 
		for (j = i + 1; j < numPatients; j++) {
			if (Patients[i] > Patients[j])
				swap(Patients[i], Patients[j]);
		}
	}
	// then insert them into a queue
	my_queue<Patient> sortedPatients;
	for (int i = 0; i < numPatients; i++) 
		sortedPatients.push(Patients[i]);
	// now output the patients' data to the user
	for (int i = 0; i < numPatients; i++) {
		sortedPatients.front().print();
		sortedPatients.pop();
	}
	delete[] Doctors;
	delete[] Patients;
}

appointment convertAppointment(const string& app) {
	appointment answer;
	if (app.length() > 4) { // validates if the input is H:MM (e.g. 2:00) or HH:MM
		// in this condition, it's HH:MM
		/* we're going to use a function called substr, which takes a substring of the 
		string from the first index, and counts how many characters you're going to take
		(e.g. string1 = "abcdef", string1.substr(1,2) == "bc" is true)
		*/
		string hrs = app.substr(0, 2); // takes a string of the first two characters
		string mins = app.substr(3, 2); // takes a string of the last two characters
		answer.hours = stoi(hrs); 
		// stoi(string) is a function that converts a string to an integer
		// in this case, we're converting the string "HH" into an integer equal to HH
		// similarly,
		answer.mins = stoi(mins);
	}
	else {
		// in this condition, it's H:MM, so the first character is the hour
		answer.hours = app[0] - '0'; // app[0] is a character from '0' to '9'
		// so, when we subtract the character '0' (or its ascii code), we get
		// an integer from 0 to 9, which is what we require
		string mins2 = app.substr(2, 2);
		answer.mins = stoi(mins2);
	}
	return answer;
}

void DoctorsFileFormat() {
	cout << "The file shall have the following format: -" << endl << endl;
	cout << "1. It shall begin with the number of doctors" << endl;
	cout << "2. For each doctor, there shall be: the name, age,"
		<< " and ID, separated by spaces/lines" << endl;
	cout << "3. In a new line (for each doctor), there shall be the "
		<< "number of appointments the Dr. already has." << endl;
	cout << "4. The appointments separated by spaces/lines, in the format"
		<< " HH:MM" << endl << endl;
	cout << "Sample shape of file: -" << endl << endl;
	cout << "2" << endl << "Mai\t40\t1" << endl << "3" << endl;
	cout << "1:00\t5:30\t3:15" << endl;
	cout << "Magdy\t35\t23" << endl << "2" << endl;
	cout << "2:00\t12:00\t16:00" << endl << endl;
}

void PatientsFileFormat() {
	cout << "The file shall have the following format: -" << endl << endl;
	cout << "1. It shall begin with the number of patients" << endl;
	cout << "2. For each patient, there shall be: the name, age,"
		<< " and ID, separated by spaces/lines" << endl;
	cout << "3. In a new line, there shall be the appointment " 
		<< "in the format HH:MM" << endl << endl;
	cout << "Sample shape of file: -" << endl << endl;
	cout << "2" << endl << "Ahmed\t15\t44" << endl;
	cout << "1:00" << endl;
	cout << "Sara\t36\t45" << endl << "2" << endl;
	cout << "4:00" << endl << endl;
}

void ReadDoctorsFromFile(Doctor*& doctors, int& numDoctors) {
	cout << "Please enter the file name (with the extension *.txt): ";
	string fileName;
	cin >> fileName;
	ifstream doctorsFile;
	doctorsFile.open(fileName + ".txt");
	doctorsFile >> numDoctors;
	doctors = new Doctor[numDoctors];
	for (int i = 0; i < numDoctors; i++) {
		doctorsFile >> temporaryString; // Name
		(*(doctors + i)).setName(temporaryString);
		doctorsFile >> temporaryInteger; // Age
		(*(doctors + i)).setAge(temporaryInteger);
		doctorsFile >> temporaryString; // ID
		(*(doctors + i)).setID(temporaryString);
		doctorsFile >> temporaryInteger; // Number of appointments
		for (int j = 0; j < temporaryInteger; j++) {
			doctorsFile >> temporaryString; // an appointment
			(*(doctors + i)).addAppointment(convertAppointment(temporaryString));
		}
	}
}
void DoctorsUserInput(Doctor*& doctors, int& numDoctors) {
	cout << "Please enter how many doctors are in the clinic: ";
	cin >> numDoctors;
	doctors = new Doctor[numDoctors];
	cout << endl << "You are now going to enter the data for each doctor." << endl;
	cout << endl;
	for (int i = 0; i < numDoctors; i++) {
		cout << i + 1 << ". Please enter the doctor's name: ";
		cin >> temporaryString;
		(*(doctors + i)).setName(temporaryString);
		cout << i + 1 << ". Please enter the doctor's ID: ";
		cin >> temporaryString;
		(*(doctors + i)).setID(temporaryString);
		cout << i + 1 << ". Please enter the doctor's age: ";
		cin >> temporaryInteger;
		(*(doctors + i)).setAge(temporaryInteger);
		cout << i + 1 << ". Please enter the number of appointments the doctor already has: ";
		cin >> temporaryInteger;
		cout << endl;
		for (int j = 0; j < temporaryInteger; j++) {
			cout << "Please enter the appointment (HH:MM): ";
			/* this is going to take an appointment as a string of hours and minutes
			separated by a colon, and then convert it to an appointment using
			the function convertAppointment */
			cin >> temporaryString;
			(*(doctors + i)).addAppointment(convertAppointment(temporaryString));
			// convertAppointment returns an appointment that we add to the doctor
		}
		cout << endl;
	}
}
void ReadPatientsFromFile(Patient*& patients, int& numPatients) {
	cout << "Please enter the file name (with the extension *.txt): ";
	string fileName;
	cin >> fileName;
	ifstream PatientsFile;
	PatientsFile.open(fileName + ".txt");
	PatientsFile >> numPatients;
	patients = new Patient[numPatients];
	for (int i = 0; i < numPatients; i++) {
		PatientsFile >> temporaryString; // name
		(*(patients + i)).setName(temporaryString);
		PatientsFile >> temporaryInteger; // age
		(*(patients + i)).setAge(temporaryInteger);
		PatientsFile >> temporaryString; // ID
		(*(patients + i)).setID(temporaryString);
		PatientsFile >> temporaryString; // appointment
		(*(patients + i)).setAppointment(convertAppointment(temporaryString));
	}
}
void PatientsUserInput(Patient*& patients, int& numPatients) {
	cout << "Please enter how many patients are going to make reservations at the clinic: ";
	cin >> numPatients;
	cout << endl;
	patients = new Patient[numPatients];
	for (int i = 0; i < numPatients; i++) {
		cout << i + 1 << ". Please enter the patient's name: ";
		cin >> temporaryString;
		(*(patients + i)).setName(temporaryString);
		cout << i + 1 << ". Please enter the patient's ID: ";
		cin >> temporaryString;
		(*(patients + i)).setID(temporaryString);
		cout << i + 1 << ". Please enter the patient's age: ";
		cin >> temporaryInteger;
		(*(patients + i)).setAge(temporaryInteger);
		cout << i + 1 << ". Please enter the patient's appointment (HH:MM): ";
		cin >> temporaryString;
		(*(patients + i)).setAppointment(convertAppointment(temporaryString));
		// convertAppointment returns an appointment that we pass to the setter
		cout << endl;
	}
}

void clearScreen() {
	cout << endl;
	cout << "Please enter any word to continue: ";
	cin >> temporaryString;
	system("cls"); // clearing the screen after finishing the input of the doctors
}