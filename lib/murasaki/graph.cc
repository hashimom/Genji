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
#include <cstring>
#include "murasaki.hh"
#include "graph.hh"
#include "ux/ux.hpp"

namespace Genji {

int Graph::Initialize(ux::Map<GNJ_MAPVAL> *gnjYomiMap, const char *instr)
{
	MRSK_NODES tmp;
	int i, j, k, retSize, place, endPlace;
	int inLen = strlen(instr);
	std::vector<GNJ_MAPVAL> mapVal;

	// Create Index
	tmp.strIdx = 0;
	tmp.strLen = 0;
	tmp.maxProb = 0;
	nodes.push_back(tmp);

	// for UTF-8
	while(tmp.strLen < inLen){
		if ((uint8_t)instr[i] < 0x80)
			tmp.strLen += 1;
		else if((uint8_t)instr[i] < 0xE0)
			tmp.strLen += 2;
		else if((uint8_t)instr[i] < 0xF0)
			tmp.strLen += 3;
		else if((uint8_t)instr[i] < 0xF8)
			tmp.strLen += 4;
		else if((uint8_t)instr[i] < 0xFC)
			tmp.strLen += 5;
		else // ( < 0xFE)
			tmp.strLen += 6;
		nodes.push_back(tmp);
		tmp.strIdx = tmp.strLen;
	}

	// create nodes
	for (i = 0; i < nodes.size(); i++) {
		place = nodes[i].strIdx;
		retSize = gnjYomiMap->commonPrefixSearch(&(instr[place]), (inLen - place), mapVal, ux::LIMIT_DEFAULT);
//		std::cout << retSize << " : " << std::endl;
		for (j = 0; j < retSize; j++) {
			endPlace = place + mapVal[j].len;
//			std::cout << mapVal[j].id << ":" << mapVal[j].len << "/" << mapVal[j].prob << std::endl;
			for (k = i; k < nodes.size(); k++) {
				if (endPlace <= nodes[k].strLen)
					break;
			}
			nodes[k].node.push_back(mapVal[j]);
		}
	}

	return(nodes.size());
}

void Graph::Construct(ux::Trie *gnjWordTrie, std::string &outStr)
{
	int i, j, k;
	int tmpLen;
	double tmpProb;
	std::string tmpWord;

	for (i = 0; i < nodes.size(); i++) {
		for (j = 0; j < nodes[i].node.size(); j++) {
			tmpWord = gnjWordTrie->decodeKey(nodes[i].node[j].id);
			tmpProb = nodes[i].node[j].prob;
			tmpLen  = nodes[i].node[j].len;

			if (nodes[i].strLen != nodes[i].node[j].len) {
				for (k = 0; k < i; k++) {
					if (nodes[i].strLen == (nodes[k].strLen + nodes[i].node[j].len)) {
						tmpWord = nodes[k].maxWord + gnjWordTrie->decodeKey(nodes[i].node[j].id);
						tmpProb = nodes[k].maxProb * nodes[i].node[j].prob;
						break;
					}
				}
			}

			if (nodes[i].maxProb < tmpProb) {
				nodes[i].maxWord = tmpWord;
				nodes[i].maxProb = tmpProb;

				outStr = tmpWord;
			}
		}
	}
}


} // namespace Genji
