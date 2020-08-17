#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<iconv.h>

#include "font_convert.h"

void main(void)
{
	int *fp;
	uint8_t insert_data[UTF_BUF_LEN];//3byte mean a hanzi, so contains 50 words.
	uint8_t output_data_matrix[MATRIX_BUF_LEN];
	size_t length = 0;
	int ret = 0;
	scanf("%s",insert_data);
	ret = to_matrix(insert_data,output_data_matrix,&length);

	return;
}




