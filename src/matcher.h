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

void pre_kmp(string pattern, vector<int> & prefix);

int kmp(string text, string pattern);

int numStringMatching(string filename,string toSearch);

int editDistance(string pattern, string text);

float numApproximateStringMatching(string filename,string toSearch);



#endif /* MATCHER_H_ */
