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
#ifndef INCLUDE_FUJISTUBO_HH_
#define INCLUDE_FUJISTUBO_HH_

#include "kasuga.hh"
#include "ux/ux.hpp"

using namespace Kasuga;

namespace Genji {

typedef struct {
	std::string word;
	std::string yomi;
	double prob;
} KSG_DIC;

typedef struct {
	ux::id_t id;
	size_t len;
	double prob;
} GNJ_MAPVAL;

class Fujitsubo {
public:
	Fujitsubo();
	virtual ~Fujitsubo();
	int Regist(std::string text);
	void RegistWord(std::string entry, std::string yomi);
	void RegistBasicWords();
	int Build();

private:
	void readKsgDic(const char *instr, KSG_DIC &out);
	int buildTrie(std::vector<KSG_DIC> &ksgDic);
	Corpus corpus;
};

} // namespace Genji

#endif /* INCLUDE_FUJISTUBO_HH_ */
