/*
 * Stop.h
 *
 *  Created on: 19/04/2016
 *      Author: Rui
 */

#ifndef SRC_STOP_H_
#define SRC_STOP_H_

#include <string>
#include <cmath>

using namespace std;

#define LAT 0
#define LON 1

class Stop {

	string name;
	float coords[2];
	string node, zone;
	int wait_time;

public:
	//Constructors
	Stop();
	Stop(string n, float lat, float lon, int time, string nod, string zon);
	Stop(string n);

	//Getters
	string getName() const;
	float getLatitude() const;
	float getLongitude() const;
	string getNode() const;
	string getZone() const;
	int getWaitTime() const;

	//Setters
	void setName(string n);
	void setCoords(float lat, float lon);
	void setLatitude(float lat);
	void setLongitude(float lon);
	void setNode(string p);
	void setZone(string zon);
	void setWaitTime(int waitTime);

	//Methods
	float calcDistance(Stop s);
	float calcDistance(float lat, float lon);
	float calcTimeBetween(const Stop& s, int velocity) const;
	float calcTimeBetween(float lat, float lon, int velocity);

	//Operator Overloading
	friend bool operator==(const Stop& s1, const Stop &s2);
	friend bool operator!= (const Stop& s1, const Stop &s2);
	void operator<< (ostream &o);

};

#endif /* SRC_STOP_H_ */
