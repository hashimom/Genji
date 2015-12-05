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

#include <string.h>
#include "aoi.h"

static void aoi_conv_fixword(AOI_STR *strp, int fixedid)
{
	int parentid = fixedid;
	int delidx = strlen(strp->workstr) - 1;

	while(parentid) {
		parentid = AOI_GET_PARENTID(strp->dic->node[parentid].code);
		strp->workstr[delidx] = 0;
		strp->curpos--;
		delidx--;
	}
	strncat(strp->workstr, strp->dic->node[fixedid].word, AOI_MAX_WORD_LEN);
	strp->curpos += aoi_strlen(strp->dic->node[fixedid].word);
	strp->nodepos = 0;
}


static int aoi_conv_search(AOI_STR *strp, uint8_t inkey)
{
	int i;
	int ret = -1;
	int outlen = 0;
	uint32_t searchkey;

	for (i = 0; i < strp->dic->nodecnt; i++) {
		searchkey = AOI_GET_SEARCHKEY(inkey, strp->nodepos);

		/* hit node */
		if (searchkey == (strp->dic->node[i].code & AOI_MASK_SEARCHCODE)) {
			strncat(strp->workstr, &inkey, 1);
			strp->curpos++;
			strp->nodepos = i;
			ret = 0;

			outlen = strlen(strp->dic->node[i].word);
			if (outlen != 0) {
				/* output word, if child node is nothing */
				if ((strp->dic->node[i].code & AOI_MASK_CHILDCOUNT) == 0) {
					aoi_conv_fixword(strp, i);
					ret = 1;
					break;
				}
			}
			break;
		}
	}
	return(ret);
}

void aoi_conv_input(AOI_STR *strp, uint8_t inkey)
{
	int hitret;
	uint32_t searchkey;

	if (strp == NULL)
		return;

	hitret = aoi_conv_search(strp, inkey);

	/* not hit */
	if (hitret < 0) {
		/* exist word in current node position */
		if (strlen(strp->dic->node[strp->nodepos].word) > 0) {
			aoi_conv_fixword(strp, strp->nodepos);
			/* re-search */
			hitret = aoi_conv_search(strp, inkey);
		}
		else {
			strncat(strp->workstr, &inkey, 1);
			strp->curpos++;
			strp->nodepos = 0;
		}
	}
	/* メモ: 「かmnじゃ」のように２連続ヒットせずの場合の２番目の「n」は「ん」に変換できてないぽい。後で直す。 */
}
