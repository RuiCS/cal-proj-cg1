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

#endif /* SRC_STOP_H_ */
