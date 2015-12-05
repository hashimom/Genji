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
#ifndef LIB_INCLUDE_AOIMAP_H_
#define LIB_INCLUDE_AOIMAP_H_

/* いずれキーマップはconfファイルから読み込むようにするため削除予定 */

typedef struct {
	uint8_t keyary[4];
	uint8_t word[16];
} AOI_KEYMAP;

AOI_KEYMAP aoi_romkan[] = {
		{"a", "あ"}, {"i", "い"}, {"u", "う"}, {"e", "え"}, {"o", "お"},
		{"ka", "か"}, {"ki", "き"}, {"ku", "く"}, {"ke", "け"}, {"ko", "こ"},
		{"sa", "さ"}, {"si", "し"}, {"su", "す"}, {"se", "せ"}, {"so", "そ"},
		{"ta", "た"}, {"ti", "ち"}, {"tu", "つ"}, {"te", "て"}, {"to", "と"},
		{"na", "な"}, {"ni", "に"}, {"nu", "ぬ"}, {"ne", "ね"}, {"no", "の"},
		{"ha", "は"}, {"hi", "ひ"}, {"hu", "ふ"}, {"he", "へ"}, {"ho", "ほ"},
		{"ma", "ま"}, {"mi", "み"}, {"mu", "む"}, {"me", "め"}, {"mo", "も"},
		{"ya", "や"}, {"yi", "いぃ"}, {"yu", "ゆ"}, {"ye", "いぇ"}, {"yo", "よ"},
		{"ra", "ら"}, {"ri", "り"}, {"ru", "る"}, {"re", "れ"}, {"ro", "ろ"},
		{"wa", "わ"}, {"wi", "うぃ"}, {"wu", "う"}, {"we", "うぇ"}, {"wo", "を"},
		{"n", "ん"}, {"nn", "ん" },
		{"ga", "が"}, {"gi", "ぎ"}, {"gu", "ぐ"}, {"ge", "げ"}, {"go", "ご"},
		{"za", "ざ"}, {"zi", "じ"}, {"zu", "ず"}, {"ze", "ぜ"}, {"zo", "ぞ"},
		{"da", "だ"}, {"di", "ぢ"}, {"du", "づ"}, {"de", "で"}, {"do", "ど"},
		{"ba", "ば"}, {"bi", "び"}, {"bu", "ぶ"}, {"be", "べ"}, {"bo", "ぼ"},
		{"pa", "ぱ"}, {"pi", "ぴ"}, {"pu", "ぷ"}, {"pe", "ぺ"}, {"po", "ぽ"},
		{"la", "ぁ"}, {"li", "ぃ"}, {"lu", "ぅ"}, {"le", "ぇ"}, {"lo", "ぉ"},
		{"cha", "ちゃ"}, {"chi", "ちぃ"}, {"chu", "ちゅ"}, {"che", "ちぇ"}, {"cho", "ちょ"},
		{"ja", "じゃ"}, {"ji", "じ"}, {"ju", "じゅ"}, {"je", "じぇ"}, {"jo", "じょ"},
		{"fa", "ふぁ"}, {"fi", "ふぃ"}, {"fu", "ふ"}, {"fe", "ふぇ"}, {"fo", "ふぉ"},
		{"kya", "きゃ"}, {"kyi", "きぃ"}, {"kyu", "きゅ"}, {"kye", "きぇ"}, {"kyo", "きょ"},
		{"sya", "しゃ"}, {"syi", "しぃ"}, {"syu", "しゅ"}, {"sye", "しぇ"}, {"syo", "しょ"},
		{"tya", "ちゃ"}, {"tyi", "ちぃ"}, {"tyu", "ちゅ"}, {"tye", "ちぇ"}, {"tyo", "ちょ"},
		{"nya", "にゃ"}, {"nyi", "にぃ"}, {"nyu", "にゅ"}, {"nye", "にぇ"}, {"nyo", "にょ"},
		{"hya", "ひゃ"}, {"hyi", "ひぃ"}, {"hyu", "ひゅ"}, {"hye", "ひぇ"}, {"hyo", "ひょ"},
		{"mya", "みゃ"}, {"myi", "みぃ"}, {"myu", "みゅ"}, {"mye", "みぇ"}, {"myo", "みょ"},
		{"rya", "りゃ"}, {"ryi", "りぃ"}, {"ryu", "りゅ"}, {"rye", "りぇ"}, {"ryo", "りょ"},
		{"gya", "ぎゃ"}, {"gyi", "ぎぃ"}, {"gyu", "ぎゅ"}, {"gye", "ぎぇ"}, {"gyo", "ぎょ"},
		{"jya", "じゃ"}, {"jyi", "じぃ"}, {"jyu", "じゅ"}, {"jye", "じぇ"}, {"jyo", "じょ"},
		{"zya", "じゃ"}, {"zyi", "じぃ"}, {"zyu", "じゅ"}, {"zye", "じぇ"}, {"zyo", "じょ"},
		{"dya", "ぢゃ"}, {"dyi", "ぢぃ"}, {"dyu", "ぢゅ"}, {"dye", "ぢぇ"}, {"dyo", "ぢょ"},
		{"bya", "びゃ"}, {"byi", "びぃ"}, {"byu", "びゅ"}, {"bye", "びぇ"}, {"byo", "びょ"},
		{"lya", "ゃ"}, {"lyi", "ぃ"}, {"lyu", "ゅ"}, {"lye", "ぇ"}, {"lyo", "ょ"}, {"ltu", "っ"},
		{"xya", "ゃ"}, {"xyi", "ぃ"}, {"xyu", "ゅ"}, {"xye", "ぇ"}, {"xyo", "ょ"}, {"xtu", "っ"},
		{"kka", "っか"}, {"kki", "っき"}, {"kku", "っく"}, {"kke", "っけ"}, {"kko", "っこ"},
		{"ssa", "っさ"}, {"ssi", "っし"}, {"ssu", "っす"}, {"sse", "っせ"}, {"sso", "っそ"},
		{"tta", "った"}, {"tti", "っち"}, {"ttu", "っつ"}, {"tte", "って"}, {"tto", "っと"},
		{"hha", "っは"}, {"hhi", "っひ"}, {"hhu", "っふ"}, {"hhe", "っへ"}, {"hho", "っほ"},
		{"mma", "っま"}, {"mmi", "っみ"}, {"mmu", "っむ"}, {"mme", "っめ"}, {"mmo", "っも"},
		{"rra", "っら"}, {"rri", "っり"}, {"rru", "っる"}, {"rre", "っれ"}, {"rro", "っろ"},
		{"gga", "っが"}, {"ggi", "っぎ"}, {"ggu", "っぐ"}, {"gge", "っげ"}, {"ggo", "っご"},
		{"zza", "っざ"}, {"zzi", "っじ"}, {"zzu", "っず"}, {"zze", "っぜ"}, {"zzo", "っぞ"},
		{"dda", "っだ"}, {"ddi", "っぢ"}, {"ddu", "っづ"}, {"dde", "っで"}, {"ddo", "っど"},
		{"bba", "っば"}, {"bbi", "っび"}, {"bbu", "っぶ"}, {"bbe", "っべ"}, {"bbo", "っぼ"},
		{"ppa", "っぱ"}, {"ppi", "っぴ"}, {"ppu", "っぷ"}, {"ppe", "っぺ"}, {"ppo", "っぽ"},
		{"cca", "っか"}, {"cci", "っし"}, {"ccu", "っく"}, {"cce", "っせ"}, {"cco", "っこ"},
		{"xxa", "っぁ"}, {"xxi", "っぃ"}, {"xxu", "っぅ"}, {"xxe", "っぇ"}, {"xxo", "っぉ"},
		{"yya", "っや"}, {"yyi", "っいぃ"}, {"yyu", "っゆ"}, {"yye", "っいぇ"}, {"yyo", "っよ"},
		{"wwa", "っわ"}, {"wwi", "っうぃ"}, {"wwu", "っう"}, {"wwe", "っうぇ"}, {"wwo", "っを"},
		{"ffa", "っふぁ"}, {"ffi", "っふぃ"}, {"ffu", "っふ"}, {"ffe", "っふぇ"}, {"ffo", "っふぉ"},
		{"jja", "っじゃ"}, {"jji", "っじ"}, {"jju", "っじゅ"}, {"jje", "っじぇ"}, {"jjo", "っじょ"},
		{"vva", "っゔぁ"}, {"vvi", "っゔぃ"}, {"vvu", "っゔ"}, {"vve", "っゔぇ"}, {"vvo", "っゔぉ"},
		{"1", "１"}, {"2", "２"}, {"3", "３"}, {"4", "４"}, {"5", "５"},
		{"6", "６"}, {"7", "７"}, {"8", "８"}, {"9", "９"}, {"0", "０"},
		{",", "、"}, {".", "。"}, {"-", "ー"}, {"+", "＋"}, {"!", "！"}, {"&", "＆"},
		{"(", "（"}, {")", "）"}, {"{", "｛"}, {"}", "｝"},
};

#define AOI_KEYMAP_SIZE (sizeof(aoi_romkan) / sizeof(AOI_KEYMAP))


#endif /* LIB_INCLUDE_AOIMAP_H_ */
