#pragma once
class PressureSensor {
private:
	double maxDepth;
	unsigned short int maxValue;
	unsigned short int value;
public:
	//always initalizes at sea level
	PressureSensor(double p_maxDepth, unsigned short int p_maxValue) : maxDepth(p_maxDepth), maxValue(p_maxValue), value(0) {}

	unsigned short int readValue() { return value; };
	void setDepth(double depth);
};

