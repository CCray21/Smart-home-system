#include "Device.h"

Device::Device(const string& type, string& name) : type(type), name(name)
{}

Device::~Device()
{}

void Device::ValidateInput(int& input)
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input" << '\n';
		Continue();
	}
}
void Device::DisplayTimer(int timer)
{
	if (timer == 0)
	{
		cout << "Sleep timer is not set " << '\n';
	}
	else if (timer > 0 && timer < 60)
	{
		if (timer == 1)
		{
			cout << "Sleep timer is set for " << timer << " minute." << '\n';
		}
		else
		{
			cout << "Sleep timer is set for " << timer << " minutes." << '\n';
		}
	}
	else if (timer % 60 == 0 && timer != 0)
	{
		if (timer / 60 == 1)
		{
			cout << "Sleep timer is set for " << timer / 60 << " hour" << '\n';
		}
		else
		{
			cout << "Sleep timer is set for " << timer / 60 << " hours" << '\n';
		}
	}
	else
	{
		if (timer / 60 == 1)
		{
			cout << "Sleep timer is set for " << timer / 60 << " hour and " << timer % 60 << " mins" << '\n';
		}
		else
		{
			cout << "Sleep timer is set for " << timer / 60 << " hours and " << timer % 60 << " mins" << '\n';
		}
	}
}
void Device::Continue()
{
	cout << "Press enter to continue\n";
	cin.get();
	system("cls");
}
string Device::GetName()
{
	return name;
}
string Device::GetType()
{
	return type;
}
void Device::SetName()
{
	system("cls");
	cout << "Enter new name: ";
	string name;
	getline(cin, name);
	this->name = name;
	system("cls");
	cout << "Name changed to: " << GetName() << '\n';
	Continue();
}