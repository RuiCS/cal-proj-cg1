#include "Stop.h"

// Constructors -----------------------------------------------------------------

Stop::Stop() : name(""), coords({0.0, 0.0}), node(""), zone("") {}

Stop::Stop(string n, float lat, float lon, string nod, string zon) : name(n), coords({lat, lon}), node(nod), zone(zon) {}

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

// Distance between Coordinates ------------------------------------------------------

float distance(float lat1, float lon1, float lat2, float lon2) {
	float distance;

	// Calculated using the Haversine Formula
	float a, c, deltaLat, deltaLon;
	deltaLat = abs(abs(lat1) - abs(lat2));
	deltaLon = abs(abs(lon1) - abs(lon2));

	// a = sin^2 (deltaLat /2) + cos(lat1)*cos(lat2)*sin^2(deltaLon/2)
	a = (sin(deltaLat/2)*sin(deltaLat/2)) + cos(lat1)*cos(lat2)*(sin(deltaLon/2)*sin(deltaLon/2));

	// c = 2 * atan2 ( sqrt(a), sqrt(1-a))
	c = 2 * atan2( sqrt(a), sqrt(1-a));

	// d = R * c, where R is the radius of the Earth
	int R = 6371000;
	distance = R * c;

	return distance;
}

// Methods ---------------------------------------------------------------------------

float Stop::calcDistance(Stop s){
	return distance(coords[LAT], coords[LON], s.getLatitude(), s.getLongitude());
}

float Stop::calcDistance(float lat, float lon){
	return distance(coords[LAT], coords[LON], lat, lon);
}

// Operator Overloading ---------------------------------------------------------------------------

bool operator==(const Stop& s1, const Stop& s2) {
	return s1.name == s2.name;
}

void Stop::operator<< (ostream &o){
	o << name;
}
