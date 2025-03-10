#pragma once
#include "Device.h"
class Light :
    public Device
{
public:
	Light(string &name);
	void QuickView() override;
	void OneClickAction() override;
	bool ShowMenu() override;
	void Save(ofstream& file) override;
	void Load(ifstream& file) override;
private:
    int intensity;
	int timer;
	bool power;
};