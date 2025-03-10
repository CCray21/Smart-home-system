#pragma once
#include "Device.h"
class RadiatorValve :
    public Device
{
public:
	RadiatorValve(string& name);
	void QuickView() override;
	void OneClickAction() override;
	bool ShowMenu() override;
	void Save(ofstream& file) override;
	void Load(ifstream& file) override;
private:
    bool power;
	float temp;
    string schedule;
};

