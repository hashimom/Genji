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
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "aoi.h"
#include "fujitsubo.hh"
#include "murasaki.hh"

using namespace Genji;

void kanakan()
{
	int i;
	std::string str, outstr;
	AOI_STR *aoistr;

	Murasaki mrsk;
	mrsk.Open();

	aoistr = aoi_new();

	while (1) {
		std::cout << "源氏: かな漢字変換モード(quit: !q))" << std::endl;
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
				mrsk.Convert((const char*)aoistr->workstr, outstr);
			}
			std::cout << aoistr->workstr << std::endl;
			std::cout << outstr << std::endl;
		}
	}
}

void regist()
{
	std::string text;
	Fujitsubo fjtb;

	while(getline(std::cin, text)) {
		fjtb.Regist(text);
	}

	fjtb.Build();
}

#if 0
void registSkkDic(char *skkdic)
{
	int cnt = 0;
	std::string low;
	std::string token;
	std::string entry;
	std::string yomi;
	std::ifstream ifs(skkdic);
	std::istringstream iss(low);
	Fujitsubo fjtb;

	while (std::getline(ifs, low)) {
		// 「;」を見つけたら次の行
		if (low.find(";;") == 0)
			continue;

		iss.str(low);
		while (std::getline(iss, token, '/')) {
			switch (cnt) {
			case 0:
				entry = token;
				break;
			case 1:
				yomi = token;
				break;
			}
			cnt++;
		}
		std::cout << entry << ": " << yomi << std::endl;
		fjtb.RegistWord(entry, yomi);
		iss.clear();
		cnt = 0;
	}
}
#endif

int main(int argc,char *argv[])
{
	int mode = 0;
	int opt;
	std::string str, outstr;
	AOI_STR *aoistr;

	while((opt = getopt(argc, argv, "cr")) != -1){
		switch(opt){
		// 辞書登録モード
		case 'r':
			regist();
			break;

		// SKK辞書登録モード
//		case 's':
//			registSkkDic(optarg); // いろいろ問題があるのでとりあえずコメントアウト
//			break;

		// かな漢字変換モード
		case 'c':
		default:
			std::cout << "Usage / c:かな漢字変換 r:辞書登録" << std::endl;
			kanakan();
			break;
		}
	}

	std::cout << "お疲れ様でした！" << std::endl;
	return(0);
}
