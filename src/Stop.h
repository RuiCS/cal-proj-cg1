/*
 * Stop.h
 *
 *  Created on: 19/04/2016
 *      Author: Rui
 */

#ifndef SRC_STOP_H_
#define SRC_STOP_H_

#include <string>
#include <utility>
#include <cmath>
using namespace std;

class Stop {

	string name;
	pair<float, float> coords;
	string pole;

public:
	//Constructors
	Stop();
	Stop(string n, float lat, float lon, string pol);
	Stop(string n, pair<float, float> coord, string pol);

	//Getters
	string getName() const;
	pair<float, float> getCoords() const;
	float getLatitude() const;
	float getLongitude() const;
	string getPole() const;

	//Setters
	void setName(string n);
	void setCoords(pair<float, float> coord);
	void setCoords(float lat, float lon);
	void setLatitude(float lat);
	void setLongitude(float lon);
	void setPole(string p);

	//Methods
	float calcDistance(Stop s);
	float calcDistance(pair<float, float> coord);
	float calcDistance(float lat, float lon);

};

// Constructors -----------------------------------------------------------------

Stop::Stop() : name(""), coords(pair<float, float> (0.0, 0.0)), pole("") {}

Stop::Stop(string n, float lat, float lon, string pol) : name(n), coords(pair<float, float> (lat, lon)), pole(pol) {}

Stop::Stop(string n, pair<float, float> coord, string pol) : name(n), coords(coord), pole(pol) {}

// Getters ----------------------------------------------------------------------

string Stop::getName() const {
	return name;
}

pair<float, float> Stop::getCoords() const{
	return coords;
}

float Stop::getLatitude() const{
	return coords.first;
}

float Stop::getLongitude() const{
	return coords.second;
}

string Stop::getPole() const {
	return pole;
}

// Setters ----------------------------------------------------------------------

void Stop::setName(string n) {
	name = n;
}

void Stop::setLatitude(float lat) {
	coords.first = lat;
}

void Stop::setLongitude(float lon) {
	coords.second = lon;
}

void Stop::setCoords(pair<float, float> coord){
	coords = coord;
}

void Stop::setCoords(float lat, float lon){
	coords.first = lat;
	coords.second = lon;
}

void Stop::setPole(string p){
	pole = p;
}

// Distance between Coordinates ------------------------------------------------------

float distance(pair<float, float> coord1, pair<float, float> coord2) {
	float distance;

	// Calculated using the Haversine Formula
	float a, c, deltaLat, deltaLon;
	deltaLat = abs(abs(coord1.first) - abs(coord2.first));
	deltaLon = abs(abs(coord1.second) - abs(coord2.second));

	// a = sin^2 (deltaLat /2) + cos(lat1)*cos(lat2)*sin^2(deltaLon/2)
	a = (sin(deltaLat/2)*sin(deltaLat/2)) + cos(coord1.first)*cos(coord2.first)*(sin(deltaLon/2)*sin(deltaLon/2));

	// c = 2 * atan2 ( sqrt(a), sqrt(1-a))
	c = 2 * atan2( sqrt(a), sqrt(1-a));

	// d = R * c, where R is the radius of the Earth
	int R = 6371000;
	distance = R * c;

	return distance;
}

float distance(float lat1, float lon1, float lat2, float lon2) {
	return distance(pair<float, float> (lat1, lon1), pair<float, float> (lat2, lon2));
}

// Methods ---------------------------------------------------------------------------

float Stop::calcDistance(Stop s){
	return distance(coords, s.getCoords());
}

float Stop::calcDistance(pair<float, float> coord){
	return distance(coords, coord);
}

float Stop::calcDistance(float lat, float lon){
	return distance(coords, pair<float, float> (lat, lon));
}

#endif /* SRC_STOP_H_ */
