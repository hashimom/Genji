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
#ifndef LIB_INCLUDE_AOI_H_
#define LIB_INCLUDE_AOI_H_

#include <stdint.h>

#define AOI_MAX_WORD_LEN (16)
#define AOI_MAX_RMJI_LEN (4)

/* 0x FF 00 00 00 : keycode */
/* 0x 00 FF FF 00 : parentnode */
/* 0x 00 00 00 FF : child node count */
#define AOI_MASK_KEYCODE    (0xFF000000)
#define AOI_MASK_PARENTID   (0x00FFFF00)
#define AOI_MASK_CHILDCOUNT (0x000000FF)
#define AOI_MASK_SEARCHCODE (0xFFFFFF00)
#define AOI_GET_SEARCHKEY(keycde, prnt) ((keycde << 24) | (prnt << 8))
#define AOI_GET_PARENTID(keycde)        ((keycde & AOI_MASK_PARENTID) >> 8)


typedef struct {
	uint32_t code;
	uint8_t word[AOI_MAX_WORD_LEN];
} AOI_NODE;

typedef struct {
	AOI_NODE *node;
	int nodecnt;
} AOI_DIC;

typedef struct {
	AOI_DIC *dic;
	uint8_t *workstr;
	int curpos;
	int nodepos;
} AOI_STR;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern AOI_STR *aoi_new();
extern void aoi_input(AOI_STR *aoistr, char inkey);
extern void aoi_clear(AOI_STR *aoistr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIB_INCLUDE_AOI_H_ */
