#include "RadiatorValve.h"
#include "TempSensor.h"

RadiatorValve::RadiatorValve(string& name) : Device("Radiator valve", name), schedule("Off"), power(false), temp(20.0)
{}

void RadiatorValve::QuickView()
{
	cout << GetName() << " Radiator valve:";
	if (power)
	{
		cout << " is on " << '\n';
	}
	else
	{
		cout << " is off " << '\n';
	}
	cout << "temp: " << temp;
	cout << " schedule: " << schedule << '\n';
}
void RadiatorValve::OneClickAction()
{
	power = !power;
	if (power)
	{
		temp = 22;
		cout << GetName() << " radiator valve is now on." << '\n';
	}
	else
	{
		temp = 20;
		cout << GetName() << " radiator valve is now off." << '\n';
	}
}
bool RadiatorValve::ShowMenu()
{
	string choice;
	do
	{
		system("cls");
		QuickView();
		if (power)
		{
			cout << "1: Turn off" << '\n';
		}
		else
		{
			cout << "1: Turn on" << '\n';
		}
		cout << "2: Set temperature" << '\n';
		cout << "3: Set schedule" << '\n';
		cout << "4: Delete device" << '\n';
		cout << "5: Change device name" << '\n';
		cout << "9: Back to main menu" << '\n';
		cout << "Enter your choice: ";
		getline(cin, choice);
		if (choice == "1")
		{
			system("cls");
			OneClickAction();
			Continue();
		}
		else if (choice == "2")
		{
			system("cls");
			cout << "Enter new temperature: ";
			cin >> temp;
			if (temp < 6)
			{
				temp = 6;
			}
			else if (temp > 28)
			{
				temp = 28;
			}
			system("cls");
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please press enter to continue\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else if (choice == "3")
		{
			system("cls");
			cout << "Enter new schedule: ";
			cin >> schedule;
			system("cls");
			cout << "Schedule set to: " << schedule << '\n';
			Continue();
		}
		else if (choice == "4")
		{
			system("cls");
			cout << GetName() << GetType() << " deleted." << '\n';
			Continue();
			return true;
		}
		else if (choice == "5")
		{
			SetName();
		}
		else if (choice == "9")
		{
			system("cls");
		}
	} while (choice != "9");
	return false;
}
void RadiatorValve::Save(ofstream& file)
{
	file << "Radiator valve" << '\n';
	file << GetName() << '\n';
	file << power << '\n';
	file << temp << '\n';
	file << schedule << '\n';
}
void RadiatorValve::Load(ifstream& file)
{
	file >> power;
	file >> temp;
	file >> schedule;
	file.ignore();
}