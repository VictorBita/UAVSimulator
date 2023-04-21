#include <stdexcept>

#include "PressureSensor.h"

void PressureSensor::setDepth(double depth) {
	if (depth > maxDepth) {
		throw std::runtime_error("invalid depth");
	}

	if (depth < 0.0) {
		depth = 0.0;
	}

	value = (unsigned short int)((double)depth * ((double)maxValue / maxDepth));
}