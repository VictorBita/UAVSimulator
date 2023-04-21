#pragma once
class Altimeter {
private:
	double height;

public:
	Altimeter() : height(50.0) {}

	inline double getHeight() { return height; }
	inline void setHeight(double newHeight) { this->height = newHeight; }
};