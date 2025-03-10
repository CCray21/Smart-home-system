#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Device
{
public:
	Device(const string &type, string &name);
	virtual ~Device();
	string GetName();
	string GetType();
	void ValidateInput(int& input);
	void Continue();
	void DisplayTimer(int timer);
	virtual void SetName();
	virtual void QuickView() = 0;
	virtual void OneClickAction() = 0;
	virtual bool ShowMenu() = 0;
	virtual void Save(ofstream& file) = 0;
	virtual void Load(ifstream& file) = 0;
private:
	string name;
	string type;
};

