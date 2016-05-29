/*
 *  NetworkMap.h
 */
#ifndef SRC_NETWORKMAP_H_
#define SRC_NETWORKMAP_H_

#include "Graph.h"
#include "Stop.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define SUBWAY_VEL 50
#define SUBWAY_INSTOP 60

#define MIN_LAT 41.14
#define MAX_LAT 41.20
#define MIN_LON -8.56
#define MAX_LON -8.70

#define WIN_WIDTH 3000
#define WIN_HEIGHT 3000
/**
 * Classe que lê e trata de toda a informação relativa as linhas.
 */
class NetworkMap {

	Graph<Stop> map;

public:
	/**
	 * Construtor, inicializa o varial map como um grafo vazio.
	 */
	NetworkMap();

	/**
	 * Retorna o grafo com a informação das linhas.
	 *
	 * @return Graph<Stop> grafo com a respetiva informação.
	 */
	Graph<Stop> getMap() const;

	/**
	 * Iguala o grafo a um novo passado como argumento.
	 *
	 * @param m grafo novo.
	 */
	void setMap(Graph<Stop> m);

	//Methods

	/**
	 * Le o ficheiro passado como argumento e processa a informação para o grafo.
	 *
	 * @param filepath caminho para o ficheiro.
	 * @return bool true se é possível ler, false case não seja.
	 */
	bool loadMap(string filepath);

	/**
	 * Imprime o grafo na consola.
	 */
	void displayMap();

	/**
	 * Calcula o peso total entre duas paragens.
	 *
	 * @param s1 paragem 1.
	 * @param s2 paragem 2.
	 * @return float peso total das arestas entre as duas paragens.
	 */
	float pathWeight(const Stop& s1, const Stop &s2);
	/**
	 * Calcula o caminho entre duas paragens com peso menor.
	 *
	 * @param s1 Codigo da paragem 1.
	 * @param s2 Codigo da paragem 2.
	 * @param weight peso total
	 * @return vector<Stop> vetor com todas as paragens do caminho com menor peso.
	 */
	vector<Stop> findLightestPath(string s1, string s2, float& weight);
	/**
	 * Calcula o caminho mais rápido entre duas paragens.
	 *
	 * @param s1 Codigo da paragem 1.
	 * @param s2 Codigo da paragem 2.
	 */
	void findFastestPath(string s1, string s2);
	/**
	 * Calcula o caminho mais barato entre duas paragens.
	 *
	 * @param s1 Codigo da paragem 1.
	 * @param s2 Codigo da paragem 2.
	 */
	void findCheapestPath(string s1, string s2);
	/**
	 * Calcula o caminho mais curto entre duas paragens.
	 *
	 * @param s1 Codigo da paragem 1.
	 * @param s2 Codigo da paragem 2.
	 */
	void findShortestPath(string s1, string s2);
	/**
	 * Calcula o caminho com menos trocas de veiculo entre duas paragens.
	 *
	 * @param s1 Codigo da paragem 1.
	 * @param s2 Codigo da paragem 2.
	 */
	void findLeastLineSwitchesPath(string s1, string s2);
	/**
	 * Verifica os pontos de articulção do grafo.
	 */
	void getArt();
	/*
	 * Guarda os nomes das paragens numa string
	 *
	 * @return nomes das paragens em formato string
	 */
	string getStopsString();
	/*
	 * Guarda os nomes das linhas numa string
	 *
	 * @return nomes das linhas em formato string
	 */
	string getLinesString();
	/*
	 * Verifica se Paragem existe
	 *
	 * @param stopName nome da paragema pesquisar
	 * @return numero de vezes que aparece
	 */
	int stopExists(string stopName);
	int lineExists(string line);

	vector<Stop> getStops();

	bool stopExistsInLine(string stopName);
	bool searchStopInLine(string line, string stopName);

	vector<vector<string> > stopNameMap();
	string stopNameConverter(string stopName);
};

/**
 * Verifica se o vetor com dado elemento
 *
 * @param v vetor
 * @param s elemento
 * @return bool true caso contenha,false caso nao encontre.
 */
bool exists_in_vector(vector<string> v, string s);
/**
 * Imprime no elemento NetworkMap num interface grafica
 */
void graphView(NetworkMap nm);
/**
 * Procura por um vertice num vetor de vertices
 *
 * @param vertexSet vetor
 * @param to_find vertice a encontrar
 * @return int indice do vertice no vetor, -1 caso nao exista
 */
int findVertexInVector(vector <Vertex<Stop>*> vertexSet, Vertex<Stop>* to_find);
/**
 * Atualiza o peso dos vertices de um NetworkMap com uma função passada como argumento
 *
 * @param weightFunction funçao para calcular o peso dos vertices
 * @param nm NetworkMap a ser atualizado
 */
void resetEdges(float(*weightFunction)(const Stop&, const Stop&), NetworkMap& nm);
/**
 * Calcula o preço de uma viagem com base no numero de zonas em que esta passa.
 *
 * @param numZones numero de zonas
 * @return float preço
 */
float calcPrice(int numZones);

// Methods to calculate edge weight
/**
 * Calcula o peso entre a paragem s1 e s2 com base no tempo a que se demora a chegar de s1 a s2.
 *
 * @param s1 paragem 1
 * @param s2 paragem 2
 * @return float peso da aresta em termos de tempo.
 */
float timeWeight(const Stop& s1, const Stop& s2);
/**
 * Calcula o peso entre a paragem s1 e s2 com base no preço que se paga ao viajar de s1 ate s2.
 *
 * @param s1 paragem 1
 * @param s2 paragem 2
 * @return float peso da aresta em termos de tpreço.
 */
float priceWeight(const Stop& s1, const Stop& s2);
/**
 * Calcula o peso entre a paragem s1 e s2 com base na distancia entre s1 e s2.
 *
 * @param s1 paragem 1
 * @param s2 paragem 2
 * @return float peso da aresta em termos de distancia.
 */
float distanceWeight(const Stop& s1, const Stop& s2);
/**
 * Calcula o peso entre a paragem s1 e s2 com base no numero de trocas a que se efetua para ir de s1 a s2.
 *
 * @param s1 paragem 1
 * @param s2 paragem 2
 * @return float peso da aresta em termos de trocas.
 */
float lineSwitchWeight(const Stop&s1, const Stop& s2);

string getStopNames(string stops);
string getStopLines(string stops);
string getStopsForLine(string line, vector<Stop> stops);
vector<string> getSimilarStops(string stop, string stops, int distance);
vector<string> getLinesForName(string stopName, vector<Stop> stops);



#endif /* SRC_NETWORKMAP_H_ */
