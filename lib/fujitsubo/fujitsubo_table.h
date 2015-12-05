/*
 * kasugadic_table.h
 *
 *  Created on: 2015/09/20
 *      Author: hashimom
 */

#ifndef INCLUDE_KASUGADIC_TABLE_H_
#define INCLUDE_KASUGADIC_TABLE_H_

/* 将来的にはenumではなくフラグ等用いて厳密に定義する */
enum {
	MEISHI = 0,
	DOUSHI,
	JOSHI,
};

/* for Dic regist */
typedef struct {
	const char *word;
	const char *yomi;
	int hinshi;
	int cost;
} KsgDic_reg_t;

static KsgDic_reg_t testdic[] = {
	{"です", "です", DOUSHI, 0},
	{"名", "な", MEISHI, 0},
	{"名前", "なまえ", MEISHI, 0},
	{"中根", "なかね", MEISHI, 0},
	{"中野", "なかの", MEISHI, 0},
	{"綿", "わた", MEISHI, 0},
	{"私", "わたし", MEISHI, 0},
	{"の", "の", JOSHI, 0},
	{"は", "は", JOSHI, 0},
};
#define DICSTR (sizeof(testdic) / sizeof(KsgDic_reg_t))


#endif /* INCLUDE_KASUGADIC_TABLE_H_ */
