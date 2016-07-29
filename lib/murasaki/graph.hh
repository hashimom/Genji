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

#ifndef LIB_MURASAKI_GRAPH_HH_
#define LIB_MURASAKI_GRAPH_HH_

#include "murasaki.hh"

namespace Genji {

typedef struct {
	std::vector<GNJ_MAPVAL> node;
	int strIdx;
	int strLen;
	std::string maxWord;
	double maxProb;
} MRSK_NODES;

class Graph {
public:
	int Initialize(ux::Map<GNJ_MAPVAL> *gnjYomiMap, const char *instr);
	void Construct(ux::Trie *gnjWordTrie, std::string &outStr);

private:
	std::vector<MRSK_NODES> pos;
};

} // namespace Genji

#endif /* LIB_MURASAKI_GRAPH_HH_ */
