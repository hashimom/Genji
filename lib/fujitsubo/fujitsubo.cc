/*
 /* Copyright (c) 2016 Masahiko Hashimoto <hashimom@geeko.jp>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <typeinfo>
#include <iomanip>
#include <fstream>
#include "config.h"
#include "fujitsubo.hh"

int Fujitsubo::build()
{
	int cnt = 0;
	std::string row;
	KSG_DIC tmpDicVal;
	std::vector<KSG_DIC> ksgDic;

	std::ifstream ifs(KASUGA_DIC_CSVNAME);
	if (!ifs) {
		std::cout << "Error:Input data file not found" << std::endl;
		return(-1);
	}

	/* Dic read from Kasuga CSV file */
	while (std::getline(ifs, row)) {
		readKsgDic(row, tmpDicVal);
		ksgDic.push_back(tmpDicVal);
	}

	/* Build wordTrie */
	cnt = buildTrie(ksgDic);

	return(cnt);
}

void Fujitsubo::readKsgDic(std::string instr, KSG_DIC &out)
{
	std::string token;
	std::stringstream ss;
	int cnt = 0;
	std::istringstream iss(instr);

	while (std::getline(iss, token, ',')) {
		switch (cnt) {
		case 0:
			ss << token;
			ss >> out.prob;
			break;
		case 1:
			out.word = token;
			break;
		case 2:
			out.yomi = token;
			break;
		}
		cnt++;
	}
}

int Fujitsubo::buildTrie(std::vector<KSG_DIC> &ksgDic)
{
	int i;
	GNJ_TRIEVAL tmpTrieVal;
	std::map<std::string, GNJ_TRIEVAL> gnjTrieMap;
	ux::Map<GNJ_TRIEVAL> gnjTrie;
	std::ofstream gnjdicofs(GENJI_DIC_NAME);

	for (i = 0; i < ksgDic.size(); i++) {
		tmpTrieVal.word = ksgDic[i].word;
		tmpTrieVal.prob = ksgDic[i].prob;
		gnjTrieMap[ksgDic[i].yomi] = tmpTrieVal;
		std::cout << ksgDic[i].yomi << "/" << ksgDic[i].word << ", " <<  ksgDic[i].prob << std::endl;
	}

	// build and save
	gnjTrie.build(gnjTrieMap);
	gnjTrie.save(gnjdicofs);

	return(i);
}
