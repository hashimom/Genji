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
	tmp.minProb = 0;
	pos.push_back(tmp);

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
		pos.push_back(tmp);
		tmp.strIdx = tmp.strLen;
	}

	// create nodes
	for (i = 0; i < pos.size(); i++) {
		place = pos[i].strIdx;
		retSize = gnjYomiMap->commonPrefixSearch(&(instr[place]), (inLen - place), mapVal, ux::LIMIT_DEFAULT);
		for (j = 0; j < retSize; j++) {
			endPlace = place + mapVal[j].len;
			for (k = i; k < pos.size(); k++) {
				if (endPlace <= pos[k].strLen)
					break;
			}
			pos[k].node.push_back(mapVal[j]);
		}
	}

	return(pos.size());
}

void Graph::Construct(ux::Trie *gnjWordTrie, std::string &outStr)
{
	int i, j, k;
	double compProb;
	std::string compWord;

	// １語ずつずらしながら辞書に登録された単語を取り出す
	for (i = 0; i < pos.size(); i++) {
		for (j = 0; j < pos[i].node.size(); j++) {
			compWord = gnjWordTrie->decodeKey(pos[i].node[j].id);
			compProb = pos[i].node[j].prob;
			// 辞書に登録されていた語が空文字だった場合は以降の処理を行わない
			if (compWord.length() == 0)
				continue;

			// 現在の位置までの文字の長さより辞書から取り出した語の方が短ければ、取り出した語の開智地点までの最短距離と結合する
			if (pos[i].strLen != pos[i].node[j].len) {
				for (k = 0; k < i; k++) {
					if (pos[i].strLen == (pos[k].strLen + pos[i].node[j].len)) {
						compWord = pos[k].minWord + gnjWordTrie->decodeKey(pos[i].node[j].id);
						compProb = pos[k].minProb + pos[i].node[j].prob;
						break;
					}
				}
			}

			// これまでの探索結果と比較
			if ((pos[i].minProb == 0) || (compProb < pos[i].minProb)) {
				pos[i].minWord = compWord;
				pos[i].minProb = compProb;
			}
		}
		outStr = pos[i].minWord;
	}
}


} // namespace Genji
