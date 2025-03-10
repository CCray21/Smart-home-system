#include "Light.h"

Light::Light(string &name) : Device("Light", name), power(false), intensity(0), timer(0)
{}

void Light::QuickView()
{
	if (power)
	{
		cout << GetName() << " light is on at: " << intensity << "%. ";
		DisplayTimer(timer);
	}
	else
	{
		cout << GetName() << " light is off." << '\n';
	}
}

void Light::OneClickAction()
{
	power = !power;
	if (power)
	{
		cout << GetName() << " light is now on." << '\n';
		intensity = 100;
	}
	else
	{
		intensity = 0;
		timer = 0;
		cout << GetName() << " light is now off." << '\n';
	}
}

bool Light::ShowMenu()
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
		cout << "2: Set intensity" << '\n';
		cout << "3: Set a sleep timer" << '\n';
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
			do
			{
				system("cls");
				cout << "Enter intensity (0-100): ";
				cin >> intensity;
				system("cls");
				if (cin.fail())
				{
					ValidateInput(intensity);
				}
				else
				{
					if (intensity < 0)
					{
						intensity = 0;
					}
					else if (intensity > 100)
					{
						intensity = 100;
					}
					if (intensity == 0)
					{
						power = false;
						cout << GetName() << " light has been turned off." << '\n';
					}
					else
					{
						power = true;
						cout << GetName() << " intensity set to: " << intensity << '\n';
					}
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					Continue();
				}
			} while (intensity < 0 || intensity > 100);
		}
		else if (choice == "3")
		{
			do
			{
				system("cls");
				cout << "Enter a sleep timer in minutes: ";
				cin >> timer;
				system("cls");
				if (cin.fail())
				{
					ValidateInput(timer);
				}
				else
				{
					DisplayTimer(timer);
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					Continue();
				}
			} while (timer < 0);
		}
		else if (choice == "4")
		{
			system("cls");
			cout << GetName() << " removed!" << '\n';
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
	} while (choice != "9" && choice != "4");
	return false;
}
void Light::Save(ofstream& file)
{
	file << "Light" << '\n';
	file << GetName() << '\n';
	file << power << '\n';
	file << intensity << '\n';
	file << timer << '\n';
}
void Light::Load(ifstream& file)
{
	file >> power;
	file >> intensity;
	file >> timer;
	file.ignore();
}
