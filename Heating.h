#pragma once
#include "Device.h"
class Heating :
    public Device
{
public:
	Heating(string& name);
	void QuickView() override;
	void OneClickAction() override;
	bool ShowMenu() override;
	void SetTemperature(float temp);
	float GetTemperature();
	void Save(ofstream& file) override;
	void Load(ifstream& file) override;
private:
    bool power;
    string schedule;
	float temp;
    bool heatingBoost;
};

