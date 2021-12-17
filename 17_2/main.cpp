#include <iostream>
#include <vector>
#include <limits>

class VelocityRange {
public:
	int vel;
	int minStep;
	int maxStep;

	VelocityRange(int vel, int minStep, int maxStep) : vel(vel), minStep(minStep), maxStep(maxStep) {}
};

int abs(int x)
{
	return x >= 0 ? x : -x;
}

bool RangeOverlap(int aMin, int aMax, int bMin, int bMax)
{
	return abs((aMax + aMin)-(bMax+bMin)) - ((aMax - aMin) + (bMax - bMin)) <= 0;
}

int main() {
	int minX = 96;
	int maxX = 125;
	int minY = -144;
	int maxY = -98;

	std::vector<VelocityRange> xVelocities;
	std::vector<VelocityRange> yVelocities;

	for (int i = 0; i >= minY; --i) {
		int minStep = std::numeric_limits<int>::max();
		int maxStep = std::numeric_limits<int>::min();
		int currentStep = 0;
		int y = 0;
		int velY = i;
		while (y > minY) {
			y += velY--;
			++currentStep;
			if (y >= minY && y <= maxY) {
				minStep = currentStep < minStep ? currentStep : minStep;
				maxStep = currentStep > maxStep ? currentStep : maxStep;
			}
		}

		if (maxStep > 0) {
			yVelocities.push_back(VelocityRange(i, minStep, maxStep));
			if (i < -1)
				yVelocities.push_back(VelocityRange(-i - 1, minStep -(i+1)*2+1, maxStep -(i+1)*2+1));
		}
	}

	for (int i = maxX; i > 0; --i)
	{
		int minStep = std::numeric_limits<int>::max();
		int maxStep = std::numeric_limits<int>::min();
		int currentStep = 0;
		int x = 0;
		int velX = i;
		while (x <= maxX && velX > 0) {
			x += velX > 0 ? velX-- : velX++;
			++currentStep;
			if (x >= minX && x <= maxX) {
				minStep = currentStep < minStep ? currentStep : minStep;
				maxStep = currentStep > maxStep ? currentStep : maxStep;
			}
		}

		if (velX == 0 && x >= minX && x <= maxX)
			maxStep = std::numeric_limits<int>::max();

		if (maxStep > 0)
			xVelocities.push_back(VelocityRange(i, minStep, maxStep));

		if (velX == 0 && x < minX)
			break;
	}

	int sum = 0;
	for (int i = 0; i < xVelocities.size(); ++i)
		for (int j = 0; j < yVelocities.size(); ++j)
			if (RangeOverlap(xVelocities[i].minStep, xVelocities[i].maxStep, yVelocities[j].minStep, yVelocities[j].maxStep)){
				++sum;
				std::cout << xVelocities[i].vel << " " << yVelocities[j].vel << " " << i << " "<< j << " ("<< xVelocities[i].minStep << " "<< xVelocities[i].maxStep << ") ("<< yVelocities[j].minStep << " "<< yVelocities[j].maxStep << ")" << std::endl;
			}

	std::cout << sum << std::endl;

	return 0;
}
