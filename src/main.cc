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

#include <iostream>
#include <string>
#include "aoi.h"
#include "fujitsubo.hh"

int main()
{
	int mode = 0;
	int i;
	std::string str;
	AOI_STR *aoistr;

	Fujitsubo fjtb;
	fjtb.build();


#if 0
	aoistr = aoi_new();

	while (1) {
		if (mode == 0)
			std::cout << "源氏: かな漢字変換モード)" << std::endl;
		else
			std::cout << "源氏: 形態素解析モード)" << std::endl; /* 未サポート */

		std::cin >> str;

		/* 終了 */
		if (str == "!q") {
			break;
		}
		/* クリア */
		if (str == "!c") {
			aoi_clear(aoistr);
			std::cout << "【文字列クリア】" << std::endl;
		}
		/* 変換 */
		else {
			for (i = 0; i < str.length(); i++) {
				aoi_input(aoistr, str.at(i));
			}
			std::cout << aoistr->workstr << std::endl;
		}
	}
#endif

	std::cout << "お疲れ様でした！" << std::endl;
	return(0);
}
