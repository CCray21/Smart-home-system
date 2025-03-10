#pragma once
#include "Device.h"
#include "Heating.h"
class TempSensor :
    public Device
{
public:
    TempSensor(string &name);
	void QuickView() override;
	void OneClickAction() override;
	bool ShowMenu() override;
	float GetTemperature();
	float GetHumidity();
	void SetTemperature(Heating* heating);
	void SetHumidity(float humidity);
	void ViewHistory();
	void Save(ofstream& file) override;
	void Load(ifstream& file) override;
private:
    float temp;
	float humidity;
	vector<float> tempHistory;
	vector<float> humidityHistory;
};

