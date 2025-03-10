#include "Device.h"
#include "Light.h"
#include "Heating.h"
#include "Speaker.h"
#include "TempSensor.h"
#include "Plugs.h"
#include "RadiatorValve.h" 

void Continue()
{
	cout << "Press enter to continue\n";
	cin.get();
	system("cls");
}

bool CaseInsensitiveCompare(string str1, string str2)
{
	transform(str1.begin(), str1.end(), str1.begin(),[](unsigned char c) {return tolower(c); });
	transform(str2.begin(), str2.end(), str2.begin(), [](unsigned char c) {return tolower(c); });
	return str1 == str2;
}

void AddDevice(Device* device, vector<Device*>& devices)
{
	for (const auto& d : devices)
	{
		if (CaseInsensitiveCompare(d->GetName(), device->GetName()))
		{
			cout << "Device with this name already exists (case insensitive) " << '\n';
			return;
		}
	}
	devices.push_back(device);
	cout << device->GetName() << " " << device->GetType() << " added!" << '\n';
	Continue();
}

void ListDevices(vector<Device*>& devices)
{
	if (devices.empty())
	{
		return;
	}
	else
	{
		cout << "device list: " << '\n';
		cout << "----------------" << '\n';
		for (const auto& d : devices)
		{
			d->QuickView();
			cout << '\n';
		}
	}
	cout << "----------------" << '\n';
}

void SortDevices(vector<Device*>& devices)
{
	if (devices.empty())
	{
		cout << "No devices found" << '\n';
		Continue();
	}
	else
	{
		sort(devices.begin(), devices.end(), [](Device* d1, Device* d2)
		{return d1->GetName() < d2->GetName(); });
		cout << "Devices sorted by name" << '\n';
	}
}

void SortByTypeAndName(vector<Device*>& devices)
{
	if (devices.empty())
	{
		cout << "No devices found" << '\n';
		Continue();
	}
	else
	{
	sort(devices.begin(), devices.end(), [](Device* d1, Device* d2)
		{
			if (d1->GetType() == d2->GetType())
			{
				return d1->GetName() < d2->GetName();
			}
			return d1->GetType() < d2->GetType();
		});
		cout << "Devices sorted by type and name" << '\n';
	}
}

Device* FindDevice(string& name, vector<Device*>& devices)
{
	for (auto& d : devices)
	{
		if (CaseInsensitiveCompare(d->GetName(), name))
		{
			return d;
		}
	}
	cout << "Device not found" << '\n';
	Continue();
	return nullptr;
}

void RemoveDevice(Device* device, vector<Device*>& devices)
{
	devices.erase(std::remove(devices.begin(), devices.end(), device), devices.end());
	delete device;
}

void SaveDevices(vector<Device*>& devices, string fileName)
{
	ofstream file(fileName);
	if (!file.is_open())
	{
		cerr << "Error: could not open file for saving." << '\n';
		return;
	}
	else
	{
		file << devices.size() << '\n';
		for (const auto& d : devices)
		{
			d->Save(file);
		}
	}
	file.close();
	cout << "Devices saved successfuly";
}

void LoadDevices(vector<Device*>& devices, string fileName)
{
	ifstream file(fileName);
	if(!file.is_open())
	{
		cerr << "Error: could not open file for loading.";
		return;
	}
	else{
		if (file.peek() == ifstream::traits_type::eof())
		{
			return;
		}
		int numberOfDevices;
		file >> numberOfDevices;
		if (numberOfDevices == 0)
		{
			return;
		}
		file.ignore();
		for (int i = 0; i < numberOfDevices; i++)
		{
			string type;
			getline(file, type);
			string name;
			getline(file, name);
			Device* device = nullptr;
			if (type == "Light")
			{
				device = new Light(name);
			}
			else if (type == "Temperature and humidity sensor")
			{
				device = new TempSensor(name);
			}
			else if (type == "Radiator valve")
			{
				device = new RadiatorValve(name);
			}
			else if (type == "Speaker")
			{
				device = new Speaker(name);
			}
			else if (type == "Plugs")
			{
				device = new Plugs(name);
			}
			else if (type == "Heating thermostat")
			{
				device = new Heating(name);
			}
			if (device)
			{
				device->Load(file);
				devices.push_back(device);
			}
		}
	}
}
void AdjustTempSensor(vector<Device*>& devices)
{
	for (auto& d : devices)
	{
		if (d->GetType() == "Temperature and humidity sensor")
		{
			TempSensor* tempSensor = dynamic_cast<TempSensor*>(d);
			if (tempSensor)
			{
				tempSensor->SetHumidity(tempSensor->GetHumidity());
			}
			for (auto& d : devices)
			{
				if (d->GetType() == "Heating thermostat")
				{
					Heating* heating = dynamic_cast<Heating*>(d);
					tempSensor->SetTemperature(heating);
				}
			}
		}
	}
}

int main()
{
	#ifdef _DEBUG
	//_CrtSetBreakAlloc(224);
	_onexit(_CrtDumpMemoryLeaks);
	#endif

	string input;
	vector <Device*> devices;
	LoadDevices(devices, "devices.txt");
	cout << "Welcome to the smart home system! Please select an option from the menu below" << '\n';

	do
	{
		AdjustTempSensor(devices);
		ListDevices(devices);
		cout << "[device name]: Perform that devices one click action" << '\n';
		cout << "1. List all devices" << '\n';
		cout << "2. Sort devices by name" << '\n';
		cout << "3. Sort devices by type and name" << '\n';
		cout << "4 [device name]: Select a device to view its menu" << '\n';
		cout << "5. Add a new device" << '\n';
		cout << "6. Remove a device" << '\n';
		cout << "9. Exit" << '\n';
		getline(cin, input);
		if (input == "1")
		{
			system("cls");
			ListDevices(devices);
			if (devices.empty())
			{
				cout << "No devices found" << '\n';
			}
			Continue();
		}
		else if (input == "2")
		{
			system("cls");
			SortDevices(devices);
		}
		else if (input == "3")
		{
			system("cls");
			SortByTypeAndName(devices);
		}
		else if (input.substr(0,2) == "4 ")
		{
			string deviceName = input.substr(2);
			Device* device = FindDevice(deviceName, devices);
			if (device)
			{
				system("cls");
				bool deleted = device->ShowMenu();
				if (deleted)
				{
					RemoveDevice(device, devices);
				}
			}
		}
		else if (input == "5")
		{
			system("cls");
			string type;
			cout << "Enter device type: " << '\n';
			cout << "1. Light" << '\n';
			cout << "2. Heating" << '\n';
			cout << "3. Speaker" << '\n';
			cout << "4. Temperature and humidity sensor" << '\n';
			cout << "5. Plugs" << '\n';
			cout << "6. Radiator valve" << '\n';
			cout << "9. Back to main menu" << '\n';
			getline(cin, type);

			if (type == "1")
			{
				system("cls");
				string name;
				cout << "Enter light name: ";
				getline(cin, name);
				Light* light = new Light(name);
				system("cls");
				AddDevice(light, devices);
			}
			else if (type == "2")
			{
				system("cls");
				string name;
				cout << "Enter heating thermostat name: ";
				getline(cin, name);
				Heating* heating = new Heating(name);
				system("cls");
				AddDevice(heating, devices);
			}
			else if (type == "3")
			{
				system("cls");
				string name;
				cout << "Enter speaker name: ";
				getline(cin, name);
				Speaker* speaker = new Speaker(name);
				system("cls");
				AddDevice(speaker, devices);
			}
			else if (type == "4")
			{
				system("cls");
				string name;
				cout << "Enter temperature and humidity sensor name: ";
				getline(cin, name);
				TempSensor* tempSensor = new TempSensor(name);
				system("cls");
				AddDevice(tempSensor, devices);
			}
			else if (type == "5")
			{
				system("cls");
				string name;
				cout << "Enter plug name: ";
				getline(cin, name);
				Plugs* plugs = new Plugs(name);
				system("cls");
				AddDevice(plugs, devices);
			}
			else if (type == "6")
			{
				system("cls");
				string name;
				cout << "Enter radiator valve name: ";
				getline(cin, name);
				RadiatorValve* radiatorValve = new RadiatorValve(name);
				system("cls");
				AddDevice(radiatorValve, devices);
			}
			else if (type == "9")
			{
				system("cls");
				continue;
			}
			else
			{
				cout << "Invalid input." << '\n';
				Continue();
			}
		}
		else if (input == "6")
		{
			if (devices.empty())
			{
				cout << "No devices found" << '\n';
				Continue();
				continue;
			}
			else
			{
				system("cls");
				ListDevices(devices);
				cout << "Enter the name of the device you want to remove: ";
				string name;
				getline(cin, name);
				Device* device = FindDevice(name, devices);
				if (device)
				{
					RemoveDevice(device, devices);
					cout << "Device removed successfuly" << '\n';
					Continue();
				}
			}
		}
		else if (input == "9")
		{
			system("cls");
			continue;
		}
		else
		{
			Device* device = FindDevice(input, devices);
			if (device)
			{
				device->OneClickAction();
				Continue();
			}
		}
	} while (input != "9");
	SaveDevices(devices, "devices.txt");
	for (auto& d : devices)
	{
		delete d;
	}
	return 0;

}