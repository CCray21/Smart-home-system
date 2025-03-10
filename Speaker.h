#pragma once
#include "Device.h"
class Speaker :
    public Device
{
public:
	Speaker(string& name);
	void QuickView() override;
	void OneClickAction() override;
	bool ShowMenu() override;
	void Save(ofstream& file) override;
	void Load(ifstream& file) override;
private:
	int volume;
	bool status;
};

