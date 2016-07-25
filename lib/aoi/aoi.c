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

#include <stdio.h>
#include <string.h>
#include "aoi.h"
#include "aoidic.h"
#include "aoistr.h"
#include "aoiconv.h"

#define AOI_MAX_TEXT_BUF (1024)
static AOI_DIC *aoidic = NULL;

AOI_STR *aoi_new()
{
	AOI_STR *ret_p = NULL;

	aoidic = aoi_dic_new_keymap();
	if (aoidic != NULL) {
		ret_p = aoi_str_new(aoidic, AOI_MAX_TEXT_BUF);
		if (ret_p == NULL) {
			aoi_dic_delete(aoidic);
		}
	}
	return(ret_p);
}

void aoi_input(AOI_STR *aoistr, const char inkey)
{
	aoi_conv_input(aoistr, (uint8_t)inkey);
}

void aoi_convert(AOI_STR *aoistr, const char *instr)
{
	int i;
	int len = strlen(instr);
	aoi_clear(aoistr);
	for (i = 0; i < len; i++) {
		aoi_conv_input(aoistr, (uint8_t)instr[i]);
	}
}

void aoi_clear(AOI_STR *aoistr)
{
	if ((aoistr != NULL) && (aoidic != NULL)) {
		aoi_str_delete(aoistr);
		aoistr = aoi_str_new(aoidic, AOI_MAX_TEXT_BUF);
	}
}


