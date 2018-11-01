#pragma once

enum class Direction {
	kSouth, kEast, kNorth, kWest
};

class CarData {
public:
	Direction dir;
	int id;
	CarData(Direction dir, int id);
};