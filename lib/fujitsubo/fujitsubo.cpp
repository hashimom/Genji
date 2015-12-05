/*
 /* Copyright (c) 2015 Masahiko Hashimoto <hashimom@geeko.jp>
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
#include <fstream>
#include <string>
#include <vector>
#include "kasuga.h"

/* for test */
#include "kasugadic_table.h"

void ksgDic::keyListAppend(const char *word, const char *yomi, int hinshi, int cost)
{
	KasugaDic_info_t wordinfo;

	/* regist yomiKeyList */
	wordKeyList.push_back(word);

	/* regist wordinfoMap */
	wordinfo.hinshi = hinshi;
	wordinfo.cost = cost;
	wordMap[word] = wordinfo;

	/* regist yomiMap */
	yomiMap[word] = yomi;
}

void ksgDic::readHeaderDic()
{
	int i;

	for (i=0; i<DICSTR; i++) {
		keyListAppend(testdic[i].word, testdic[i].yomi, testdic[i].hinshi, testdic[i].cost);
	}
}

int ksgDic::build()
{
	int cnt = 0;
	size_t retLen = 0;
	std::map<std::string, ux::id_t> yomiregMap;
	ux::id_t wordid;
	std::ofstream wordofs("worddic.dat");
	std::ofstream yomiofs("yomidic.dat");

	/* Dic read from Header */
	readHeaderDic();

	/* Build wordTrie */
	wordTrie.build(wordMap);

	/* Build yomiTrie */
	for (cnt=0; cnt < wordMap.size(); cnt++) {
		wordid = wordTrie.prefixSearchKey(
				wordKeyList[cnt].c_str(), wordKeyList[cnt].size(), retLen);

		yomiregMap[(yomiMap[wordKeyList[cnt].c_str()])] = wordid;
	}
	yomiTrie.build(yomiregMap);

	wordTrie.save(wordofs);
	yomiTrie.save(yomiofs);

	return(wordKeyList.size());
}


