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

#include <stdlib.h>
#include <string.h>
#include "aoi.h"
#include "aoimap.h"

static void aoi_dic_wordadd(AOI_DIC *dic, uint8_t *keyary, uint8_t *cana)
{
	int i;
	int keylen = strlen(keyary);
	int prntnode = 0;
	int crntnode = 0;
	uint32_t searchkey;

	for (i = 0; i < keylen; i++) {
		searchkey = AOI_GET_SEARCHKEY(keyary[i], prntnode);

		for (crntnode = 0; crntnode < dic->nodecnt; crntnode++) {
			/* already registered node */
			if (searchkey == (dic->node[crntnode].code & AOI_MASK_SEARCHCODE))
				break;
		}

		/* word setting, if tail of registered word */
		if (i == (keylen -1))
			strncpy(dic->node[crntnode].word, cana, AOI_MAX_WORD_LEN);

		/* regist node, if not registered */
		if (crntnode == dic->nodecnt) {
			dic->node[crntnode].code = searchkey;

			/* child node count increment to parent node */
			dic->node[prntnode].code++;

			dic->nodecnt++;
		}

		/* hitting node or adding node is parent node of next serach */
		prntnode = crntnode;
	}
}

static AOI_DIC *aoi_dic_new(int maxnodecnt)
{
	AOI_DIC *dic = NULL;

	dic = calloc(1, sizeof(AOI_DIC));
	if (dic != NULL) {
		dic->node = calloc(maxnodecnt, sizeof(AOI_NODE));
		dic->nodecnt = 1;

		if (dic->node == NULL) {
			free(dic);
			dic = NULL;
		}
	}
	return(dic);
}

AOI_DIC *aoi_dic_new_keymap()
{
	int i;
	AOI_DIC *dic = NULL;

	dic = aoi_dic_new(AOI_KEYMAP_SIZE * AOI_MAX_RMJI_LEN);

	if (dic != NULL) {
		for (i = 0; i < AOI_KEYMAP_SIZE; i++) {
			aoi_dic_wordadd(dic, aoi_romkan[i].keyary, aoi_romkan[i].word);
		}
	}

	return(dic);
}

void aoi_dic_delete(AOI_DIC *dic)
{
	if (dic != NULL) {
		if (dic->node != NULL)
			free(dic->node);
		free(dic);
	}
}
