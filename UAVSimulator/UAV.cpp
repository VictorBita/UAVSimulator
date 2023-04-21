#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>
#include <cfloat>
#include <cmath>
#include <chrono>

#include <Windows.h>

#include "UAV.h"

UAV::UAV(unsigned int type) : sensor_type(type), sensor(maxDepths[type], maxValues[type]) {
}

void UAV::Dive(double targetDepth) {
	double currentDepth = calculateDepthFromSensorValue();

	if (targetDepth > MAX_UAV_DEPTH || targetDepth < currentDepth) {
		throw std::runtime_error("invalid depth");
	}

	const std::string operation = "Diving";

	do {
		// simulates change of depth
		setDepth(currentDepth);

		printStatus(operation, targetDepth);

		Sleep(100);
		currentDepth += STEP_CHANGE;// simulates dive
	} while (currentDepth <= targetDepth);

	setDepth(currentDepth);

	printStatus(operation, targetDepth);
}

void UAV::Ascend(double targetDepth) {
	double currentDepth = calculateDepthFromSensorValue();
	if (targetDepth > MAX_UAV_DEPTH || targetDepth > currentDepth) {
		throw std::runtime_error("invalid depth");
	}

	const std::string operation = "Ascending";
	do {
		setDepth(currentDepth);
		printStatus(operation, targetDepth);

		Sleep(100);
		currentDepth -= STEP_CHANGE;// simulates ascension
	} while (currentDepth >= targetDepth);

	setDepth(currentDepth);
	printStatus(operation, targetDepth);
}

void UAV::MaintainDepth(unsigned int seconds) {
	const std::string operation = "Maintaining";
	double currentDepth = calculateDepthFromSensorValue();
	for (unsigned int i = 0; i < seconds; ++i) {
		printStatus(operation, currentDepth);
		Sleep(1000);
	}
}

void UAV::printStatus(const std::string& operation, const double targetDepth) {
	std::cout << "[" << operation << "]";
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "[" << targetDepth << "m]";
	std::cout << "[" << calculateDepthFromSensorValue() << "m]";
	std::cout << "[" << alti.getHeight() << "m]";
	std::cout << std::endl;
}

double UAV::calculateDepthFromSensorValue() {
	double sensorValue = (double)sensor.readValue();
	if (1 == sensor_type) {
		sensorValue /= 10.0;
	}
	return sensorValue / (maxValues[sensor_type] / maxDepths[sensor_type]);
}

void UAV::setDepth(double newDepth) {
	alti.setHeight(MAX_UAV_DEPTH - newDepth);

	sensor.setDepth(newDepth * (1 == sensor_type ? 10.0 : 1));
}

bool UAV::almostEqual(const double a, const double b) {
	return fabs(a - b) <= DBL_EPSILON * fabs(a);
}
