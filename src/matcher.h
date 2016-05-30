/*
 * matcher.h
 *
 *  Created on: 28/05/2016
 *      Author: Rui
 */

#ifndef MATCHER_H_
#define MATCHER_H_

#include <iostream>
#include <string>

using namespace std;

/*
 * Inicializar funcao prefixo
 * @param patter padrao a pesquisar
 * @param prefix vetor a modificar
 */
void pre_kmp(string pattern, vector<int> & prefix);

/*
 * Algoritmo KMP para strings
 * @param text texto total onde encontrar padrao
 * @param pattern padrao a pesquisar
 * @return vezes encontradas
 */
int kmp(string text, string pattern);

/**
 * Numero de vezes encontrado o padrao num ficheiro de texto
 * @param filename ficheiro a abrir/ler
 * @param toSearch padrao a pesquisar
 * @return numero de vezes encontradas
 */
int numStringMatching(string filename,string toSearch);

/**
 * Distancia entre duas palavras com algoritmo de pesquisa aproximada
 * @param pattern padrao a pesquisar
 * @param text texto a ler
 * @return distancia
 */
int editDistance(string pattern, string text);

/*
 * Distancia media de todas as palavras ao padrao
 * @param filename ficheiro a ler
 * @param toSearch padrao
 * @return distancia media obtida
 */
float numApproximateStringMatching(string filename,string toSearch);



#endif /* MATCHER_H_ */
