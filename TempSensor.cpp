#include "TempSensor.h"

TempSensor::TempSensor(string &name) : Device("Temperature and humidity sensor", name), temp(20), humidity(50)
{}

void TempSensor::QuickView()
{
	cout << GetName() << " Temperature and humidity sensor: " << '\n';
	cout << "Temperature: " << temp << "C" << '\n';
	cout << "Humidity: " << humidity << "%" << '\n';
}
void TempSensor::OneClickAction()
{
	cout << "No one click action available for this device." << '\n';
}
void TempSensor::SetHumidity(float humidity)
{
	srand(time(nullptr));
	humidityHistory.push_back(this->humidity);
	if (rand() % 2 == 0)
	{
		this->humidity = humidity + (rand() % 3) + 1;
	}
	else
	{
		this->humidity = humidity - ((rand() % 3) + 1);
	}
	if (this->humidity < 0)
	{
		this->humidity = 0;
	}
	else if (this->humidity > 100)
	{
		this->humidity = 100;
	}
}
void TempSensor::SetTemperature(Heating* heating)
{
	if (heating)
	{
		tempHistory.push_back(this->temp);
		this->temp = heating->GetTemperature();
	}
}
void TempSensor::ViewHistory()
{
	cout << "Temperature history:" << ' \n';
	for (auto& t : tempHistory)
	{
		cout << t << "C\n";
	}
	cout << "Humidity history:" << '\n';
	for (auto& h : humidityHistory)
	{
		cout << h << "%\n";
	}
}
float TempSensor::GetTemperature()
{
	return temp;
}
float TempSensor::GetHumidity()
{
	return humidity;
}
bool TempSensor::ShowMenu()
{
	string choice;
	do
	{
		system("cls");
		QuickView();
		cout << "1: View live data" << '\n';
		cout << "2: View historic data" << '\n';
		cout << "3: Delete device" << '\n';
		cout << "4: Change device name" << '\n';
		cout << "9: Back to main menu" << '\n';
		cout << "Enter your choice: ";
		getline(cin, choice);
		if (choice == "1")
		{
			system("cls");
			cout << "Current temperature: " << temp << "C\n";
			cout << "Current humidity: " << humidity << "%\n";
			Continue();
		}
		else if (choice == "2")
		{
			system("cls");
			ViewHistory();
			Continue();
		}
		else if (choice == "3")
		{
			system("cls");
			cout << GetName() << " deleted.\n";
			Continue();
			return true;
		}
		else if (choice == "4")
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
void TempSensor::Save(ofstream& file)
{
	file << "Temperature and humidity sensor" << '\n';
	file << GetName() << '\n';
	file << temp << '\n';
	file << humidity << '\n';
	file << tempHistory.size() << '\n';
	for (auto& t : tempHistory)
	{
		file << t << '\n';
	}
	file << humidityHistory.size() << '\n';
	for (auto& h : humidityHistory)
	{
		file << h << '\n';
	}
}
void TempSensor::Load(ifstream& file)
{
	file >> temp;
	file >> humidity;
	size_t tempHistorySize;
	file >> tempHistorySize;
	for (size_t i = 0; i < tempHistorySize; i++)
	{
		float temp;
		file >> temp;
		tempHistory.push_back(temp);
	}
	size_t humidityHistorySize;
	file >> humidityHistorySize;
	for (size_t i = 0; i < humidityHistorySize; i++)
	{
		float humidity;
		file >> humidity;
		humidityHistory.push_back(humidity);
	}
	file.ignore();
}