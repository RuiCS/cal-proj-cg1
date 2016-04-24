#include "Stop.h"
#include <iostream>
#include <math.h>
using namespace std;

// Constructors -----------------------------------------------------------------

Stop::Stop() : name(""), coords({0.0, 0.0}), node(""), zone(""), wait_time(0) {}

Stop::Stop(string n, float lat, float lon, int time, string nod, string zon) : name(n), coords({lat, lon}), wait_time(time), node(nod), zone(zon) {}

Stop::Stop(string n) : name(""), coords({0.0, 0.0}), node(n), zone(""), wait_time(0)  {}
// Getters ----------------------------------------------------------------------

string Stop::getName() const {
	return name;
}

float Stop::getLatitude() const{
	return coords[LAT];
}

float Stop::getLongitude() const{
	return coords[LON];
}

string Stop::getNode() const {
	return node;
}

string Stop::getZone() const {
	return zone;
}

int Stop::getWaitTime() const{
	return wait_time;
}

// Setters ----------------------------------------------------------------------

void Stop::setName(string n) {
	name = n;
}

void Stop::setLatitude(float lat) {
	coords[LAT] = lat;
}

void Stop::setLongitude(float lon) {
	coords[LON] = lon;
}

void Stop::setCoords(float lat, float lon){
	coords[LAT] = lat;
	coords[LON] = lon;
}

void Stop::setNode(string p){
	node = p;
}

void Stop::setZone(string zon){
	zone = zon;
}

void Stop::setWaitTime(int waitTime){
	wait_time = waitTime;
}

// Distance between Coordinates (in meters) ------------------------------------------------------

float distance(float lat1, float lon1, float lat2, float lon2) {
	float distance;

	// Calculated using the Haversine Formula
	float a, c, deltaLat, deltaLon;
	float to_radians = M_PI / 180;
	deltaLat = (lat2 - lat1) * to_radians;
	deltaLon = (lon2 - lon1) * to_radians;

	// a = sin^2 (deltaLat /2) + cos(lat1)*cos(lat2)*sin^2(deltaLon/2)
	a = (sin(deltaLat/2)*sin(deltaLat/2)) + cos(lat1 * to_radians)*cos(lat2 * to_radians)*(sin(deltaLon/2)*sin(deltaLon/2));
	// c = 2 * atan2 ( sqrt(a), sqrt(1-a))
	c = 2 * atan2( sqrt(a), sqrt(1-a));
	// d = R * c, where R is the radius of the Earth
	int R = 6371000;
	distance = R * c;

	return distance;
}

// Calculate Time between Coordinates (with velocity in km/h) (time in seconds) ------------------------------------------------

float timeBetween(float lat1, float lon1, float lat2, float lon2, int velocity){

	// velocity in m/s
	float velocity_ms = velocity * 1000 / 3600;
	float d = distance(lat1, lon1, lat2, lon2);

	if ( d == 0 ){
		return 0.0;
	}
	else return d / velocity_ms;

}

// Methods ---------------------------------------------------------------------------

float Stop::calcDistance(Stop s){
	return distance(coords[LAT], coords[LON], s.getLatitude(), s.getLongitude());
}

float Stop::calcDistance(float lat, float lon){
	return distance(coords[LAT], coords[LON], lat, lon);
}

float Stop::calcTimeBetween(Stop s, int velocity){
	return timeBetween(coords[LAT], coords[LON], s.getLatitude(), s.getLongitude(), velocity);
}

float Stop::calcTimeBetween(float lat ,float lon, int velocity){
	return timeBetween(coords[LAT], coords[LON], lat, lon, velocity);
}

// Operator Overloading ---------------------------------------------------------------------------

bool operator==(const Stop& s1, const Stop& s2) {
	return s1.name == s2.name;
}

void Stop::operator<< (ostream &o){
	o << name;
}

bool operator!= (const Stop& s1, const Stop &s2) {
	return s1.name != s2.name;
}
