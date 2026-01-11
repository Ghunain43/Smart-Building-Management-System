#include <iostream>
#include<windows.h>
#include<fstream>
#include <string>
#include<atomic>
#include <thread>

using namespace std;
class dashboard {
public:
	virtual void dashboarddisplay() = 0;
};
class Lighting : public dashboard {
private:
	bool lightsOn;	
	int brightness;
	string lightMood;

public:
	Lighting() : lightsOn(false), brightness(0), lightMood("NORMAL") {}

	void toggleLights(bool on) {
		lightsOn = on;
		if (on && brightness == 0) {
			brightness = 2;
		}
		cout << "Lights turned " << (on ? "ON" : "OFF") << "." << endl;
	}

	void setBrightness(int level) {
		if (!lightsOn) {
			cout << "ERROR: Turn lights ON first!" << endl;
			return;
		}
		if (level < 1 || level > 3) {
			cout << "ERROR: Brightness must be between 1 and 3" << endl;
			return;
		}
		brightness = level;
		cout << "Brightness set to ";
		if (level == 1) cout << "LOW";
		else if (level == 2) cout << "MEDIUM";
		else cout << "HIGH";
		cout << "." << endl;
	}

	void setMood(int mood) {
		if (!lightsOn) {
			cout << "LIGHTS WERE NOT TURNED ON!!!!" << endl<<"LIGHTS TURNED ON AUTOMATICALLY!!"<<endl;
			lightsOn = true;
			
		}
		if (mood < 1 || mood > 4) {
			cout << "ERROR: Invalid mood selection" << endl;
			return;
		}

		if (mood == 1) {
			lightMood = "NORMAL";
			brightness = 2;
		}
		else if (mood == 2) {
			lightMood = "RELAX";
			brightness = 1;
		}
		else if (mood == 3) {
			lightMood = "FOCUS";
			brightness = 3;
		}
		else if (mood == 4) {
			lightMood = "PARTY";
			brightness = 3;
		}
		cout << "Light mood set to " << lightMood << "." << endl;

	}

	void dashboarddisplay() override {
		cout << "========== LIGHTING DASHBOARD ==========" << endl;
		cout << "STATUS: " << (lightsOn ? "ON" : "OFF") << endl;
		if (lightsOn) {
			cout << "BRIGHTNESS: ";
			if (brightness == 1) cout << "LOW";
			else if (brightness == 2) cout << "MEDIUM";
			else if (brightness == 3) cout << "HIGH";
			else cout << "CUSTOM";
			cout << endl;
			cout << "MOOD: " << lightMood << endl;
		}
		else {
			cout << "BRIGHTNESS: OFF" << endl;
			cout << "MOOD: NOT APPLICABLE" << endl;
		}
		cout << "=======================================" << endl;
	}
};
class HVAC : public dashboard {
private:
	bool hvacOn;
	int currentTemperature;
	bool autemp;
	bool cool;
	bool heat;
	bool fanOn;
	int fanSpeed;
	bool fanspeed;
public:
	HVAC() : hvacOn(false), currentTemperature(22), autemp(false), cool(false), heat(false), fanOn(false), fanSpeed(false) {}

	void setTemperature(int temperature) {
		if (temperature < 16 || temperature > 30) {
			cout << "Invalid temperature! Must be between 16 and 30 degrees Celsius." << endl;
			return;
		}
		currentTemperature = temperature;
		cout << "Temperature set to " << temperature << " degrees Celsius." << endl;
	}
	void suggestTemperature(int people) {
		int suggestedTemp;
		if (people >= 1 && people < 5) {
			suggestedTemp = 22;
		}
		else if (people >= 5 && people < 10) {
			suggestedTemp = 18;
		}
		else if (people >= 10 && people <= 20) {
			suggestedTemp = 16;
		}
		else {
			cout << "Room capacity exceeded! Cannot suggest a temperature." << endl;
			return;
		}
		cout << "Suggested temperature: " << suggestedTemp << " degrees Celsius." << endl;
		setTemperature(suggestedTemp);
	}
	void toggleFan(bool on, int speed = 0) {
		fanOn = on;
		if (on) {
			cout << "Fan turned ON." << endl;
			if (speed >= 1 && speed <= 3) {
				fanSpeed = speed;
				cout << "Fan speed set to " << (speed == 1 ? "LOW" : speed == 2 ? "MEDIUM" : "HIGH") << "." << endl;
			}
			else {
				cout << "Invalid fan speed! Defaulting to LOW." << endl;
				fanSpeed = 1;
			}
		}
		else {
			cout << "Fan turned OFF." << endl;
		}
	}
	void toggleHVAC(bool on) {
		hvacOn = on;
		cout << "HVAC system turned " << (on ? "ON" : "OFF") << "." << endl;
	}
	void toggleAutoControl(bool on) {
		autemp = on;
		if (on) {
			cout << "Automatic temperature control enabled." << endl;
			if (currentTemperature <= 20) {
				cool = true;
				heat = false;
				cout << "Cooling system activated." << endl;
			}
			else if (currentTemperature > 25) {
				heat = true;
				cool = false;
				cout << "Heating system activated." << endl;
			}
			else {
				cool = false;
				heat = false;
				cout << "Cooling and heating systems on standby." << endl;
			}
		}
		else {
			cout << "Automatic temperature control disabled." << endl;
		}
	}
	void dashboarddisplay() override {
		cout << "========== HVAC DASHBOARD ==========" << endl;
		cout << "HVAC Status: " << (hvacOn ? "ON" : "OFF") << endl;
		if (hvacOn) {
			cout << "Current Temperature: " << currentTemperature << " C" << endl;
		}
		else {
			cout << "HVAC is OFF" << endl;
		}
		cout << "FAN STATUS: " << (fanOn ? "ON" : "OFF") << endl;
		if (fanOn == true) {
			cout << "FAN SPEED: " << (fanspeed ? "HIGH" : "LOW") << endl;
		}
		else {
			cout << "FAN SPEED: OFF" << endl;
		}
		cout << "AUTOMATIC COOLING/HEATING CONTROL: " << (autemp ? "ON" : "OFF") << endl;
		if (autemp) {
			if (currentTemperature <= 20) {
				cool = true;
				cout << "COOLING SYSTEM: " << (cool ? "ON" : "OFF") << endl;
			}
			else if (currentTemperature <= 25) {
				cout << "COOLING SYSTEM AND HEATING SYSTEM ON STANDBY" << endl;
			}
			else {
				heat = true;
				cout << "HEATING SYSTEM: " << (heat ? "ON" : "OFF") << endl;
			}
		}
		cout << "===================================" << endl;
	}
};
class Security : public dashboard {
private:
	bool alarmActivated;
	bool doorsLocked;
	bool camerasOn;
	int buildingStatus;
	bool powerOnMain;
	bool panicMode;
	int securityCode;
	atomic<bool> alarmBeeping;
	int pinAttempt;

public:
	Security() : alarmActivated(false), doorsLocked(true), camerasOn(false), buildingStatus(1), panicMode(false), alarmBeeping(false), securityCode(4321) {}
	void activateAlarm() {
		alarmActivated = true;
		alarmBeeping = true;
		thread(&Security::alarmBeep, this).detach();
		cout << "ALARM ACTIVATED! CALLING POLICE AND RESCUE." << endl;
	}
	void deactivateAlarm() {
		alarmActivated = false;
		alarmBeeping = false;
		cout << "ALARM DEACTIVATED." << endl;
	}
	void lockDoors() {
		doorsLocked = true;
		cout << "ALL DOORS LOCKED." << endl;
	}

	void unlockDoors() {
		doorsLocked = false;
		cout << "ALL DOORS UNLOCKED." << endl;
	}

	void toggleCameras(bool on) {
		camerasOn = on;
		cout << "Cameras turned " << (on ? "ON" : "OFF") << "." << endl;
	}
	void setBuildingStatus(int status) {
		if (status < 0 || status > 4) {
			cout << "INVALID BUILDING STATUS!" << endl;
			return;
		}
		buildingStatus = status;
		cout << "BUILDING STATUS UPDATED TO: " << getBuildingStatusString() << endl;
	}
	void activatePanicMode() {
		panicMode = true;
		activateAlarm();
		unlockDoors();

		while (true) {
			cout << "PANIC MODE ACTIVATED! CALLING EMERGENCY SERVICES." << endl;
			cout << "GIVE THE SECURITY CODE TO DEACTIVATE PANIC MODE: " << endl;
			int code;
			cin >> code;
			if (code == securityCode) {
				panicMode = false;
				deactivateAlarm();
				lockDoors();
				cout << "PANIC MODE DEACTIVATED." << endl;
			}
			else {
				cout << "INVALID SECURITY CODE! PANIC MODE REMAINS ACTIVATED." << endl;
			}
			if (code == securityCode) break;
		}
	}

	void dashboarddisplay() override {
		cout << "============== SECURITY DASHBOARD ==============" << endl;
		cout << "Alarm Status: " << (alarmActivated ? "ACTIVATED" : "DEACTIVATED") << endl;
		cout << "Door Status: " << (doorsLocked ? "LOCKED" : "UNLOCKED") << endl;
		cout << "Camera Status: " << (camerasOn ? "ON" : "OFF") << endl;
		cout << "Building Status: " << getBuildingStatusString() << endl;
		cout << "Panic Mode: " << (panicMode ? "ACTIVATED" : "DEACTIVATED") << endl;
		cout << "================================================" << endl;
	}

	void alarmBeep() {
		while (alarmBeeping) {
			Beep(750, 300);
			this_thread::sleep_for(chrono::milliseconds(300));
		}
	}
private:
	string getBuildingStatusString() {
		switch (buildingStatus) {
		case 0: return "CLOSED";
		case 1: return "OPEN";
		case 2: return "UNDER MAINTENANCE";
		case 3: return "SYSTEM ON MAIN POWER";
		case 4: return "SYSTEM ON BACKUP POWER";
		default: return "UNKNOWN";
		}
	}
};
const int space = 10;
class userManagement {
private:

	string users[space];
	int password[space];

public:
	userManagement() {
		for (int i = 0; i < space; i++) {
			users[i] = "";
			password[i] = 0;
		}
	}
	void addUser() {
		string username;
		int pass;
		cout << "ENTER THE USERNAME TO BE ADDED: " << endl;
		cin >> username;
		cout << "ENTER THE PASSWORD TO BE ADDED: " << endl;
		cin >> pass;
		ifstream userfile("users.txt");
		if (userfile.is_open()) {
			string line;
			while (getline(userfile, line)) {
				size_t pos = line.find("->");
				if (pos != string::npos) {
					string existingUsername = line.substr(0, pos);
					if (existingUsername == username) {
						cout << "CONTRARY TO LAWS OF DISCRETE STRUCTURES ONE USER CAN ONLY HAVE ONE PASSWORD IT IS A ONE TO ONE RELATIONSHIP" << endl;
						userfile.close();
						return;
					}
				}
			}
			userfile.close();
		}


		for (int i = 0; i < space; i++) {
			if (users[i] == username) {
				cout << "CONTRARY TO LAWS OF DISCRETE STRUCTURES ONE USER CAN ONLY HAVE ONE PASSWORD IT IS A ONE TO ONE RELATIONSHIP" << endl;
				return;
			}
		}


		for (int i = 0; i < space; i++) {
			if (users[i] == "") {
				users[i] = username;
				password[i] = pass;
				cout << "USER ADDED SUCCESSFULLY!" << endl;

				ofstream userfile("users.txt", ios::app);
				if (userfile.is_open()) {
					userfile << username << "->" << pass << endl;
					userfile.close();
					cout << "USER INFORMATION SAVED TO FILE." << endl;
				}
				else {
					cout << "ERROR OPENING USER FILE!" << endl;
				}
				return;
			}
		}

		cout << "USER LIST FULL! CANNOT ADD MORE USERS." << endl;
	}

	void showuser() {
		ifstream userfile("users.txt");
		if (userfile.is_open()) {
			string line;
			cout << "THE USER PASSWORD RELATIONS ARE AS FOLLOWS: " << endl;
			while (getline(userfile, line)) {
				cout << line << endl;
			}
		}
		else {
			cout << "ERROR OPENING USER FILE!" << endl;
		}
	}
	void loadusers() {
		ifstream UserFile("USER.txt");
		string line;
		int idx = 0;
		while (getline(UserFile, line) && idx < space) {
			if (line.find("USERNAME: ") == 0) {
				users[idx] = line.substr(10);
				if (getline(UserFile, line) && line.find("PASSWORD: ") == 0) {
					password[idx] = stoi(line.substr(10));
					idx++;
				}
			}
		}
		UserFile.close();
	}
	void login() {
		int attempts = 0;
		string existingUsername;
		string existingPassword;
		while (true) {
			string username, password;
			cout << "ENTER USERNAME: ";
			cin >> username;
			cout << "ENTER PASSWORD: ";
			cin >> password;
			if (username == "admin" && password == "0000") {
				cout << "ACCESS GRANTED. WELCOME, " << username << "!" << endl;
				return;
			}

			ifstream userfile("users.txt");
			if (userfile.is_open()) {
				string line;
				while (getline(userfile, line)) {
					size_t pos = line.find("->");
					if (pos != string::npos) {
						existingUsername = line.substr(0, pos);
						existingPassword = line.substr(pos + 2);
						if (existingUsername == username && existingPassword == password) {
							cout << "ACCESS GRANTED. WELCOME, " << username << "!" << endl;
						 	userfile.close();
							return;
						}
					}
				}
				userfile.close();
			}
			else {
				cout << "ERROR OPENING USER FILE!" << endl;
				return;
			}

			cout << "ACCESS DENIED. INVALID USERNAME OR PASSWORD." << endl;
			Beep(750, 300);
			attempts++;
			if (attempts >= 3) {
				cout << "TOO MANY FAILED ATTEMPTS. EXITING PROGRAM." << endl;

				for (int i = 0; i < 3; i++) {
					Beep(1000, 500);
				}

				exit(0);
			}

			if (username == existingUsername && password == existingPassword)
				break;
		}

	}
	void removeUser() {
		string username;
		cout << "ENTER THE USERNAME TO BE REMOVED: " << endl;
		cin >> username;

		bool userRemoved = false;


		ifstream userfile("users.txt");
		ofstream tempFile("temp.txt");

		if (!userfile.is_open() || !tempFile.is_open()) {
			cout << "ERROR OPENING USER FILE!" << endl;
			return;
		}

		string line;
		while (getline(userfile, line)) {
			size_t pos = line.find("->");
			if (pos != string::npos) {
				string existingUsername = line.substr(0, pos);
				if (existingUsername == username) {
					userRemoved = true;
					continue;
				}
			}
			tempFile << line << endl;
		}

		userfile.close();
		tempFile.close();


		remove("users.txt");
		rename("temp.txt", "users.txt");

		if (userRemoved) {
			cout << "USER REMOVED SUCCESSFULLY!" << endl;
		}
		else {
			cout << "USER NOT FOUND IN FILE." << endl;
		}
	}
};



int main() {
	cout << "==============BUILDING MANAGEMENT SYSTEM===============" << endl;
	Security ss;
	userManagement um;
	um.loadusers();
	bool hvfac = false;
	um.login();

	HVAC hvac;
	const int numrooms = 5;
	Lighting  lighting[numrooms];

	while (true) {
		cout << "=======WELCOME TO INTEGRATED BUILDING MANAGEMENT CONTROL PANEL=========" << endl;

		cout << "1. HVAC" << endl;
		cout << "2. SECURITY SYSTEM" << endl;
		cout << "3. LIGHTING" << endl;
		cout << "4. ADD NEW USER" << endl;
		cout << "5. REMOVE USER" << endl;
		cout << "6. Building status" << endl;
		cout << "7. PANIC BUTTON" << endl;
		cout << "8. SHOW USER PASSWORD RELATIONS" << endl;
		cout << "9. EXIT" << endl;
		string autempchoice;
		int choice;
		cout << "ENTER YOUR CHOICE" << endl;
		try {
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				throw runtime_error("Invalid input! Please enter a number.");
			}
		}
		catch (const runtime_error& e) {
			cerr << "ERROR: " << e.what() << endl;
			continue;
		}
		
		switch (choice)
		{
		case 1:
		{
			if (!hvfac) {
				cout << "DO YOU WANT TO TURN ON THE HVAC SYSTEM? (Y/N): " << endl;
				cin >> autempchoice;
				if (autempchoice == "Y" || autempchoice == "y")
				{
					hvac.toggleHVAC(true);
					hvfac = true;
				}
				else if (autempchoice == "N" || autempchoice == "n")
				{
					hvac.toggleHVAC(false);
					break;
				}
				else
				{
					cout << "INVALID INPUT! PLEASE ENTER Y OR N." << endl;
					break;
				}
			}
			system("cls");
			int hvacChoice;
			try {
				cout << "============ HVAC CONTROL =============" << endl;
				cout << "WHAT DO YOU WANT TO DO?" << endl;
				cout << "1. SET TEMPERATURE" << endl;
				cout << "2. SUGGEST TEMPERATURE BASED ON ROOM OCCUPANCY" << endl;
				cout << "3. TOGGLE FAN" << endl;
				cout << "4. TOGGLE AUTOMATIC TEMPERATURE CONTROL" << endl;
				cout << "5. DISPLAY DASHBOARD" << endl;

				cin >> hvacChoice;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(10000, '\n');
					throw runtime_error("Invalid input! Please enter a number.");
				}
			}
			catch (const runtime_error& e) {
				cerr << "ERROR: " << e.what() << endl;
				break;
			}
			if (hvacChoice == 1) {
				try {
					cout << "ENTER DESIRED TEMPERATURE (16-30 C): " << endl;
					int temp;
					cin >> temp;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter a number.");
					}
					hvac.setTemperature(temp);
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
			}
			else if (hvacChoice == 2) {
				int people;
				try {
					cout << "ENTER NUMBER OF PEOPLE IN THE ROOM (1-20): " << endl;

					cin >> people;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter a number.");
					}
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
				hvac.suggestTemperature(people);
			}
			else if (hvacChoice == 3) {
				try {
					cout << "DO YOU WANT TO TURN ON THE FAN? (Y/N): " << endl;
					cin >> autempchoice;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter Y or N.");
					}
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
				if (autempchoice == "Y" || autempchoice == "y")
				{

					int speed;
					try {
						cout << "ENTER FAN SPEED (1-LOW, 2-MEDIUM, 3-HIGH): " << endl;
						cin >> speed;
						if (cin.fail() || speed < 1 || speed > 3) {
							cin.clear();
							cin.ignore(10000, '\n');
							throw runtime_error("Invalid input! Please enter a number between 1 and 3.");
						}
					}
					catch (const runtime_error& e) {
						cerr << "ERROR: " << e.what() << endl;
					}
					hvac.toggleFan(true, speed);
				}
				else if (autempchoice == "N" || autempchoice == "n")
				{
					hvac.toggleFan(false);
				}
				else
				{
					cout << "INVALID INPUT! PLEASE ENTER Y OR N." << endl;
					break;
				}

			}
			else if (hvacChoice == 4) {
				try {
					cout << "DO YOU WANT TO ENABLE AUTOMATIC TEMPERATURE CONTROL? (Y/N): " << endl;
					cin >> autempchoice;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter Y or N.");
					}
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
				if (autempchoice == "Y" || autempchoice == "y")
				{
					hvac.toggleAutoControl(true);
				}
				else if (autempchoice == "N" || autempchoice == "n")
				{
					hvac.toggleAutoControl(false);
				}
				else
				{
					cout << "INVALID INPUT! PLEASE ENTER Y OR N." << endl;
					break;
				}
			}
			else if (hvacChoice == 5)
			{
				hvac.dashboarddisplay();
			}
			else
			{
				cout << "INVALID CHOICE!" << endl;
			}
			break;
		}
		case 2:
			int secChoice;
			try {
				cout << "WELCOME TO THE SECURITY SYSTEM CONTROL PANEL" << endl;
				cout << "WHAT DO YOU WANT TO DO?" << endl;
				cout << "1. ACTIVATE ALARM" << endl;
				cout << "2. DEACTIVATE ALARM" << endl;
				cout << "3. LOCK DOORS" << endl;
				cout << "4. UNLOCK DOORS" << endl;
				cout << "5. TOGGLE CAMERAS" << endl;
				cout << "6. SET BUILDING STATUS" << endl;
				cout << "7. DISPLAY DASHBOARD" << endl;
				cin >> secChoice;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					throw runtime_error("Invalid input! Please enter a number.");
				}
			}
			catch (const runtime_error& e) {
				cerr << "ERROR: " << e.what() << endl;
				break;
			}
			if (secChoice == 1) {
				ss.activateAlarm();
			}
			else if (secChoice == 2) {
				ss.deactivateAlarm();
			}
			else if (secChoice == 3) {
				ss.lockDoors();
			}
			else if (secChoice == 4) {
				ss.unlockDoors();
			}
			else if (secChoice == 5) {
				try {
					cout << "DO YOU WANT TO TURN ON THE CAMERAS? (Y/N): " << endl;
					cin >> autempchoice;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter Y or N.");
					}
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
				if (autempchoice == "Y" || autempchoice == "y")
				{
					ss.toggleCameras(true);
				}
				else if (autempchoice == "N" || autempchoice == "n")
				{
					ss.toggleCameras(false);
				}
				else
				{
					cout << "INVALID INPUT! PLEASE ENTER Y OR N." << endl;
				}
			}
			else if (secChoice == 6) {
				try {
					cout << "ENTER BUILDING STATUS (0-CLOSED, 1-OPEN, 2-UNDER MAINTENANCE, 3-SYSTEM ON MAIN POWER, 4-SYSTEM ON BACKUP POWER): " << endl;
					int status;
					cin >> status;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter a number.");
					}
					ss.setBuildingStatus(status);
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
			}
			else if (secChoice == 7) {
				ss.dashboarddisplay();
			}
			else {
				cout << "INVALID CHOICE!" << endl;
			}
			break;
		case 3:
			system("cls");
			int room;
			try {
				cout << "SELECT ROOM NUMBER (1-" << numrooms << "):" << endl;

				cin >> room;
				if (cin.fail() || room < 1 || room > numrooms) {
					cin.clear();
					cin.ignore(10000, '\n');
					throw runtime_error("Invalid room number! Please select a valid room.");
				}
			}
			catch (const runtime_error& e) {
				cerr << "ERROR: " << e.what() << endl;
				break;
			}
			lighting[room - 1].dashboarddisplay();

			int lightChoice;
			try {
				cout << "============ LIGHTING CONTROL =============" << endl;
				cout << "WHAT DO YOU WANT TO DO?" << endl;
				cout << "1. TURN LIGHTS ON/OFF" << endl;
				cout << "2. SET BRIGHTNESS" << endl;
				cout << "3. SET MOOD" << endl;
				cout << "4. DISPLAY DASHBOARD" << endl;

				cin >> lightChoice;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(10000, '\n');
					throw runtime_error("Invalid input! Please enter a number.");
				}
			}
			catch (const runtime_error& e) {
				cerr << "ERROR: " << e.what() << endl;
				break;
			}

			if (lightChoice == 1) {
				try {
					cout << "DO YOU WANT TO TURN ON THE LIGHTS? (Y/N): " << endl;
					cin >> autempchoice;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter Y or N.");
					}
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
				if (autempchoice == "Y" || autempchoice == "y") {
					lighting[room - 1].toggleLights(true);
				}
				else if (autempchoice == "N" || autempchoice == "n") {
					lighting[room - 1].toggleLights(false);
				}
				else {
					cout << "INVALID INPUT! PLEASE ENTER Y OR N." << endl;
				}
			}
			else if (lightChoice == 2) {
				int brightness;
				try {
					cout << "ENTER BRIGHTNESS LEVEL (1-LOW, 2-MEDIUM, 3-HIGH): " << endl;
					cin >> brightness;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter a number.");
					}
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
				lighting[room - 1].setBrightness(brightness);
			}
			else if (lightChoice == 3) {
				int mood;
				try {
					cout << "SELECT LIGHT MOOD:" << endl;
					cout << "1. NORMAL" << endl;
					cout << "2. RELAX" << endl;
					cout << "3. FOCUS" << endl;
					cout << "4. PARTY" << endl;
					cout << "ENTER MOOD (1-4): " << endl;
					cin >> mood;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						throw runtime_error("Invalid input! Please enter a number.");
					}
				}
				catch (const runtime_error& e) {
					cerr << "ERROR: " << e.what() << endl;
				}
				lighting[room - 1].setMood(mood);
			}
			else if (lightChoice == 4) {
				lighting[room - 1].dashboarddisplay();
			}
			else {
				cout << "INVALID CHOICE!" << endl;
			}
			break;
		case 4:
		{
			um.addUser();
			break;
		}
		case 5:
			um.removeUser();
			break;
		case 6:
			int status;
			try {
				cout << "SET BUILDING STATUS:" << endl;
				cout << "0. CLOSED" << endl;
				cout << "1. OPEN" << endl;
				cout << "2. UNDER MAINTENANCE" << endl;
				cout << "3. SYSTEM ON MAIN POWER" << endl;
				cout << "4. SYSTEM ON BACKUP POWER" << endl;
				cout << "ENTER STATUS: ";
				cin >> status;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					throw runtime_error("Invalid input! Please enter a number.");
				}
			}
			catch (const runtime_error& e) {
				cerr << "ERROR: " << e.what() << endl;
				break;
			}
			ss.setBuildingStatus(status);
			break;
		case 7:
			ss.activatePanicMode();
			break;
		case 8:
		{
			um.showuser();
			break;
		}
		case 9:
		{
			cout << "EXITING SYSTEM. GOODBYE!" << endl;
			return 0;
		}
		default:
			cout << "INVALID CHOICE! PLEASE TRY AGAIN." << endl;
		}
		cout << "\nPRESS ENTER TO CONTINUE...";
		cin.ignore();
		cin.get();
		system("cls");
	}
	return 0;
}