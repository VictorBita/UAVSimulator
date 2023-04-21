#pragma once
#include <vector>

#include "Constants.h"

#include "Altimeter.h"
#include "PressureSensor.h"

class UAV{
private:
	std::vector<double> maxDepths = { MAX_DIGITAL_DEPTH, MAX_ANALOG_DEPTH };

	std::vector<unsigned short int> maxValues = { MAX_DIGITAL_VALUE, MAX_ANALOG_VALUE };

	Altimeter alti;
	PressureSensor sensor;

	unsigned int sensor_type;

public:
	UAV() = delete;
	//always initalise with activated pressure sensor type
	UAV(unsigned int type);

	void Dive(double targetDepth);
	void Ascend(double targetDepth);
	void MaintainDepth(unsigned int seconds);

private:
	void printStatus(const std::string& operation, const double targetDepth);
	double calculateDepthFromSensorValue();

	void setDepth(double newDepth);

	bool almostEqual(const double a, const double b);
};

