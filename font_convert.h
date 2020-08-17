#ifndef _FONT_CONVERT_H_
#define _FONT_CONVERT_H_

#include<iconv.h>

#define WORD_NUM	20
#define UTF_BUF_LEN		WORD_NUM*3
#define GBK_BUF_LEN		WORD_NUM*2
#define MATRIX_BUF_LEN	WORD_NUM*32

int to_matrix(uint8_t *insert_data, uint8_t *output_data,size_t *olen);


#endif