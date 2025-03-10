#include "Plugs.h"

Plugs::Plugs(string& name) : Device("Plugs", name), schedule("Off"), power(false), timer(0), currentUsage(0)
{}

void Plugs::OneClickAction()
{
	power = !power;
	if (power)
	{
		currentUsage = 10;
		cout << GetName() << " plug is now on" << '\n';
		usageHistory.push_back(currentUsage);
	}
	else
	{
		currentUsage = 0;
		timer = 0;
		schedule = "Off";
		cout << GetName() << "plug is now off" << '\n';
		usageHistory.push_back(currentUsage);
	}
}
void Plugs::QuickView()
{
	if (power)
	{
		cout << GetName() << " plug is on. ";
		cout << "Schedule: " << schedule << '\n';
		DisplayTimer(timer);
	}
	else
	{
		cout << GetName() << " plug is off. " << '\n';
	}
}
bool Plugs::ShowMenu()
{
	string choice;
	do
	{
		system("cls");
		QuickView();
		if (power)
		{
			cout << "1. Turn off" << '\n';
		}
		else
		{
			cout << "1. Turn on" << '\n';
		}
		cout << "2. Set schedule" << '\n';
		cout << "3. Set sleep timer" << '\n';
		cout << "4. View energy usage" << '\n';
		cout << "5. Delete device" << '\n';
		cout << "6. Change device name" << '\n';
		cout << "9. Back to main menu" << '\n';
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
			cout << "Enter schedule: ";
			cin >> schedule;
			system("cls");
			cout << "Schedule set to: " << schedule << '\n';
			Continue();
		}
		else if (choice == "3")
		{
			system("cls");
			cout << "Enter sleep timer in minutes: ";
			cin >> timer;
			system("cls");
			if (cin.fail())
			{
				ValidateInput(timer);
			}
			else
			{
				DisplayTimer(timer);
			}
		}
		else if (choice == "4")
		{
			system("cls");
			cout << "Current energy usage: " << currentUsage << '\n';
			cout << "Historical energy usage: " << '\n';
			for (auto& u : usageHistory)
			{
				cout << u << "kWh" << '\n';
			}
			Continue();
		}
		else if (choice == "5")
		{
			system("cls");
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
void Plugs::Save(ofstream& file)
{
	file << "Plugs" << '\n';
	file << GetName() << '\n';
	file << power << '\n';
	file << timer << '\n';
	file << currentUsage << '\n';
	file << schedule << '\n';
	file << usageHistory.size() << '\n';
	for (auto& u : usageHistory)
	{
		file << u << '\n';
	}
}
void Plugs::Load(ifstream& file)
{
	file >> power;
	file >> timer;
	file >> currentUsage;
	file >> schedule;
	size_t usageHistorySize;
	file >> usageHistorySize;
	for (size_t i = 0; i < usageHistorySize; i++)
	{
		int usage;
		file >> usage;
		usageHistory.push_back(usage);
	}
	file.ignore();
}
