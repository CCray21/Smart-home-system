#include "Speaker.h"

Speaker::Speaker(string& name) : Device("Speaker", name), volume(0), status(false)
{}

void Speaker::QuickView()
{
	if (status)
	{
		cout << GetName() << " speaker is playing at voulume " << volume << "\n";
	}
	else
	{
		cout << GetName() << " speaker is paused" << "\n";
	}
}
void Speaker::OneClickAction()
{
	status = !status;
	if (status)
	{
		cout << GetName() << " speaker is now playing at volume " << volume << '\n';
	}
	else
	{
		volume = 0;
		cout << GetName() << " speaker is now stopped." << '\n';
	}
}
bool Speaker::ShowMenu()
{
	string choice;
	do
	{
		system("cls");
		QuickView();
		if (status)
		{
			cout << "1: Pause" << '\n';
		}
		else
		{
			cout << "1: Play" << '\n';
		}
		cout << "2: Set volume" << '\n';
		cout << "3: Delete device" << '\n';
		cout << "4: Change device name" << '\n';
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
			cout << "Enter volume (0-100): ";
			cin >> volume;
			if (cin.fail())
			{
				ValidateInput(volume);
			}
			else
			{
				if (volume < 0)
				{
					volume = 0;
				}
				else if (volume > 100)
				{
					volume = 100;
				}
				if (volume == 0)
				{
					status = false;
					cout << GetName() << " speaker is now stopped." << '\n';
				}
				else
				{
					status = true;
					cout << GetName() << " volume set to " << volume << '\n';
				}
				system("cls");
				Continue();
			}
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
void Speaker::Save(ofstream& file)
{
	file << "Speaker" << '\n';
	file << GetName() << '\n';
	file << volume << '\n';
	file << status << '\n';
}
void Speaker::Load(ifstream& file)
{
	file >> volume;
	file >> status;
	file.ignore();
}