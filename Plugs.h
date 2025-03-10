#pragma once
#include "Device.h"
class Plugs :
    public Device
{
public:
	Plugs(string& name);
	void QuickView() override;
	void OneClickAction() override;
	bool ShowMenu() override;
	void Save(ofstream& file) override;
	void Load(ifstream& file) override;
private:
    string schedule;
	bool power;
    int timer;
    int currentUsage;
	vector<int> usageHistory;
};

