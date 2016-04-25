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
#include <sstream>

using namespace std;

#define LAT 0
#define LON 1
/**
 * Classe relativa a uma paragem
 */
class Stop {

	string name;
	float coords[2];
	string node, zone;
	int wait_time;

public:
	/**
	 * Construtor, inicializa uma paragem vazia.
	 */
	Stop();
	/**
	 * Construtor, incializa uma paragem.
	 *
	 * @param n nome
	 * @param lat latitude
	 * @param lon longitude
	 * @param time frequencia de passagem do transporte
	 * @param nod codigo da paragem
	 * @param zon zona a que a paragem pertence
	 */
	Stop(string n, float lat, float lon, int time, string nod, string zon);
	/**
	 * Construtor, inicializa uma paragem vazia com nome n.
	 *
	 * @param n nome da paragem
	 */
	Stop(string n);

	//Getters
	/**
	 * Devolve o nome da paragem
	 *
	 * @return string nome
	 */
	string getName() const;
	/**
	 * Devolve a latitude da paragem
	 *
	 * @return float latitude
	 */
	float getLatitude() const;
	/**
	 * Devolve a longitude da paragem
	 *
	 * @return float longitude
	 */
	float getLongitude() const;
	/**
	 * Devolve o codigo da paragem
	 *
	 * @return string codigo
	 */
	string getNode() const;
	/**
	 * Devolve a zona da paragem
	 *
	 * @return string zona
	 */
	string getZone() const;
	/**
	 * Devolve o tempo de espera na paragem
	 *
	 * @return string codigo
	 */
	int getWaitTime() const;
	/**
	 * Devolve a linha da paragem
	 *
	 * @return string linha
	 */
	string getLine() const;

	//Setters
	/**
	 * Muda o nome da paragem.
	 *
	 * @param n novo nome.
	 */
	void setName(string n);
	/**
	 * Muda as coordenadas geograficas da paragem.
	 *
	 * @param lat nova latitude
	 * @param lon nova longitude
	 */
	void setCoords(float lat, float lon);
	/**
	 * Muda a latitude da paragem
	 *
	 * @param lat nova latitude
	 */
	void setLatitude(float lat);
	/**
	 * Muda a longitude da paragem
	 *
	 * @param lon nova longitude
	 */
	void setLongitude(float lon);
	/**
	 * Muda o codigo da paragem.
	 *
	 * @param p novo codigo
	 */
	void setNode(string p);
	/**
	 * Muda a zona da paragem.
	 *
	 * @param zon nova zona
	 */
	void setZone(string zon);
	/**
	 * Muda o tempo de espera da paragem.
	 *
	 * @param waitTime novo tempo de espera
	 */
	void setWaitTime(int waitTime);

	//Methods
	/**
	 * Calcula a distancia da paragem atual a uma outra paragem.
	 *
	 * @param s paragem a qual se quer saber a distancia.
	 * @return float distancia entre as duas paragens.
	 */
	float calcDistance(Stop s) const;
	/**
	 * Calcula a distancia da paragem atual até um ponto geografico
	 *
	 * @param lat latitude do ponto
	 * @param lon longitudo do ponto
	 * @return float distancia entre a paragem e o ponto
	 */
	float calcDistance(float lat, float lon);
	/**
	 * Calcula o tempo que o veiculo demora a chegar da paragem atual a uma outra paragem
	 *
	 * @param s paragem a qual se quer saber o tempo que se demora chegar
	 * @param velocity velocidade do veiculo
	 * @return float tempo que o veiculo demora a ir da paragem atual a paragem destino.
	 */
	float calcTimeBetween(const Stop& s, int velocity) const;
	/**
	 * Calcula o tempo que o veiculo demora a chegar da paragem atual a um ponto geografico
	 *
	 * @param lat latitude do ponto
	 * @param lon longitude do pont
	 * @param velocity velocidade do veiculo
	 * @return float tempo que o veiculo demora a ir da paragem atual ao ponto.
	 */
	float calcTimeBetween(float lat, float lon, int velocity);

	//Operator Overloading
	/**
	 * Overloading do operador==
	 *
	 * @return true se o nome de s1 é igual ao de s2, false caso contrario.
	 */
	friend bool operator==(const Stop& s1, const Stop &s2);
	/**
	 * Overloading do operador==
	 *
	 * @return true se o nome de s1 não é igual ao de s2, false caso contrario.
	 */
	friend bool operator!= (const Stop& s1, const Stop &s2);
	/**
	 * Overloading do operador << para que se possa imprimir um elemento do tipo Stop
	 */
	void operator<< (ostream &o);

};

#endif /* SRC_STOP_H_ */
