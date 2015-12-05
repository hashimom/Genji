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

AOI_STR *aoi_str_new(AOI_DIC *dic, int bufsize)
{
	AOI_STR *retstr = NULL;

	retstr = calloc(1, sizeof(AOI_STR));
	if (retstr != NULL) {
		retstr->dic = dic;

		/* calloc work buf */
		retstr->workstr = calloc(bufsize, sizeof(char));
		if (retstr->workstr == NULL) {
			free(retstr);
			retstr = NULL;
		}
	}
	return(retstr);
}

void aoi_str_delete(AOI_STR *strp)
{
	if (strp != NULL) {
		if (strp->workstr != NULL)
			free(strp->workstr);
		free(strp);
	}
}

int aoi_strlen(uint8_t *str)
{
	int ret = 0;
	int i = 0;
	int strsize = strlen(str);

	while(i < strsize){
		if (str[i] < 0x80)
			i += 1;
		else if(str[i] < 0xE0)
			i += 2;
		else if(str[i] < 0xF0)
			i += 3;
		else if(str[i] < 0xF8)
			i += 4;
		else if(str[i] < 0xFC)
			i += 5;
		else if(str[i] < 0xFE)
			i += 6;
		else
			i += 0;
		ret++;
	}
	return(ret);
}

int aoi_update_worklen(AOI_STR *strp)
{
	strp->curpos = aoi_strlen(strp->workstr);
	return(strp->curpos);
}

