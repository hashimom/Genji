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

using namespace Kasuga;

namespace Genji {

Fujitsubo::Fujitsubo()
{
	corpus.Open(KASUGA_DBNAME, KASUGA_CPS_CSVNAME);
}

Fujitsubo::~Fujitsubo()
{
	corpus.Close();
}

int Fujitsubo::Regist(std::string text)
{
	return(corpus.Regist(text));
}

int Fujitsubo::Build()
{
	int cnt = 0;
	std::string token;
	KSG_DIC tmpDicVal;
	std::vector<KSG_DIC> ksgDic;

	corpus.Get(KASUGA_DIC_CSVNAME);

	std::ifstream ifs(KASUGA_DIC_CSVNAME);
	if (!ifs) {
		std::cout << "Error:Input data file not found" << std::endl;
		return(-1);
	}

	/* Dic read from Kasuga CSV file */
	while (std::getline(ifs, token)) {
		readKsgDic(token.c_str(), tmpDicVal);
		ksgDic.push_back(tmpDicVal);
	}

	/* Build wordTrie */
	cnt = buildTrie(ksgDic);

	return(cnt);
}

void Fujitsubo::readKsgDic(const char *instr, KSG_DIC &out)
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
	size_t len;
	GNJ_MAPVAL tmpMapVal;
	std::vector<std::string> wordList;
	std::map<std::string, GNJ_MAPVAL> yomiList;
	ux::Map<GNJ_MAPVAL> gnjYomiMap;
	std::ofstream gnjYomiDicOfs(GENJI_YOMIDIC_NAME);
	std::ofstream gnjWordDicOfs(GENJI_WORDDIC_NAME);

	// build Word Trie
	for (i = 0; i < ksgDic.size(); i++) {
		wordList.push_back(ksgDic[i].word);
	}
	ux::Trie gnjWordTrie(wordList);
	gnjWordTrie.save(gnjWordDicOfs);


	// build Yomi Map
	for (i = 0; i < ksgDic.size(); i++) {
		tmpMapVal.id = gnjWordTrie.prefixSearch(ksgDic[i].word.c_str(), ksgDic[i].word.length(), len);
		tmpMapVal.len = ksgDic[i].yomi.length();
		tmpMapVal.prob = ksgDic[i].prob;
		yomiList[ksgDic[i].yomi] = tmpMapVal;
//		std::cout << ksgDic[i].yomi << "/"
//				<< ksgDic[i].word << ", "
//				<<  ksgDic[i].prob << std::endl;
	}
	gnjYomiMap.build(yomiList);
	gnjYomiMap.save(gnjYomiDicOfs);

	return(i);
}

} // namespace Genji

