#pragma once

struct Location {
	double latitude, longitude;
	Location(double latitude, double longitude):
		latitude(latitude), longitude(longitude) {}
};