#include "Heating.h"
#include "TempSensor.h"

Heating::Heating(string& name) : Device("Heating thermostat", name), power(false), schedule("Off"), temp(22), heatingBoost(false)
{}

void Heating::QuickView()
{
	if (power)
	{
		cout << GetName() << " heating thermostat is on." << '\n';
		cout << "Current temperature: " << temp << "C" << '\n';
		cout << "Schedule: " << schedule << '\n';

		if (heatingBoost)
		{
			cout << "Heating boost is on." << '\n';
		}
		else
		{
			cout << "Heating boost is off." << '\n';
		}
	}
	else
	{
		cout << GetName() << " heating thermostat is off." << '\n';
	}
}
void Heating::OneClickAction()
{
	power = !power;
	if (power)
	{
		temp = 25;
		cout << GetName() << " heating thermostat is now on." << '\n';
	}
	else
	{
		schedule = "Off";
		heatingBoost = false;
		temp = 18;
		cout << GetName() << " heating thermostat is now off." << '\n';
	}
}

bool Heating::ShowMenu()
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
		cout << "4: Toggle heating boost" << '\n';
		cout << "5: Delete device" << '\n';
		cout << "6: Change device name" << '\n';
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
			cout << "Enter new temperature (between 12C and 32C): ";
			cin >> temp;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (temp < 12)
			{
				temp = 12;
			}
			else if (temp > 32)
			{
				temp = 32;
			}
			system("cls");
			cout << "Temperature set to " << temp << '\n';
			Continue();
		}
		else if (choice == "3")
		{
			system("cls");
			cout << "Enter new schedule: ";
			cin >> schedule;
			system("cls");
			cout << "Schedule set to " << schedule << '\n';
			Continue();
		}
		else if (choice == "4")
		{
			system("cls");
			heatingBoost = !heatingBoost;
			if (heatingBoost)
			{
				cout << "Heating boost is now on." << '\n';
				temp = temp + 3;
				if (temp > 32)
				{
					temp = 32;
				}
			}
			else
			{
				cout << "Heating boost is now off." << '\n';
				temp = temp - 3;
				if(temp < 12)
				{
					temp = 12;
				}
			}
			Continue();
		}
		else if (choice == "5")
		{
			system("cls");
			cout << GetName() << " deleted." << '\n';
			Continue();
			return true;
		}
		else if (choice == "6")
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
void Heating::SetTemperature(float temp)
{
	this->temp = temp;
}
float Heating::GetTemperature()
{
	return temp;
}

void Heating::Save(ofstream& file)
{
	file << "Heating thermostat" << '\n';
	file << GetName() << '\n';
	file << power << '\n';
	file << schedule << '\n';
	file << temp << '\n';
	file << heatingBoost << '\n';
}
void Heating::Load(ifstream& file)
{
	file >> power;
	file >> schedule;
	file >> temp;
	file >> heatingBoost;
	file.ignore();
}