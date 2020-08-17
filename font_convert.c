#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#include "font_convert.h"

static void show_matrix(uint8_t *data, size_t len)
{
	if( len == 32 )
	{
		for(int i = 0 ; i < 16 ;i++)
		{
			for(int n=0;n<8;n++)
			{
				if(data[2*i] & (0x80>>n))
				{
					printf("  ");
				}
				else
				{
					printf("**");
				}
			}
			for(int m=0;m<8;m++)
			{
				if(data[2*i + 1] & (0x80>>m))
				{
					printf("  ");
				}
				else
				{
					printf("**");
				}
			}	
			printf("\n");	
		}
	}
	else
	{
		for(int i = 0 ; i < 16 ;i++)
		{
			for(int n=0;n<8;n++)
			{
				if(data[i] & (0x80>>n))
				{
					printf("  ");
				}
				else
				{
					printf("# ");
				}	
			}
			printf("\n");
		}
	}
}

static size_t font_to_matrix(uint8_t *insert_data, uint8_t *output_data,size_t len)
{
	int *fp_hanzi, *fp_asc;
	
	if( !( fp_hanzi = open("HZK16X",O_RDONLY)))
	{
		printf("open font HZK16 failed\n");
		return -1;
	}
	
	if( !( fp_asc = open("ASC16",O_RDONLY)))
	{
		printf("open font ASC16 failed\n");
		return -1;
	}
	
	int i = 0;
	int offset=0;
	int out_idx = 0;
	while(i<len)
	{	
		//ASCII 
		if( insert_data[i] <= 0xA0)
		{
			offset = insert_data[i]*16;
			lseek(fp_asc,offset,SEEK_SET);
			read(fp_asc,output_data,16 * sizeof(uint8_t));
			out_idx += 16;
			show_matrix(output_data,16);
			i++;
		}
		else//hanzi
		{
			offset = (94*(unsigned int)(insert_data[i]-0xa0-1)+(insert_data[i+1]-0xa0-1))*32;
			lseek(fp_hanzi,offset,SEEK_SET);
			read(fp_hanzi,output_data,32 * sizeof(uint8_t));
			out_idx += 32;
			show_matrix(output_data,32);
			i+=2;
		}
	}
	return out_idx;	
}

int utf_to_gbk(uint8_t *insert_data, uint8_t *output_data,size_t *olen)
{
	int ret = 0;
	iconv_t cd = iconv_open("GBK","UTF-8");
	const char *ins = (char *) insert_data;
	char *outs = (char *) output_data;
	size_t ilen = strlen(insert_data);
	size_t outlen = GBK_BUF_LEN;
	ret = iconv(cd, &ins, &ilen, &outs, &outlen);
	*olen = GBK_BUF_LEN - outlen;
	iconv_close(cd);
	return ret;
}

int to_matrix(uint8_t *insert_data, uint8_t *output_data,size_t *olen)
{
	uint8_t gbk_tmp[GBK_BUF_LEN];
	int ret = 0;
	ret = utf_to_gbk(insert_data, gbk_tmp,olen);
	if(ret)
	{
		printf("utf-8 to gbk failed!\n");
	}
	font_to_matrix(gbk_tmp,output_data,*olen);
	return 0;
}




