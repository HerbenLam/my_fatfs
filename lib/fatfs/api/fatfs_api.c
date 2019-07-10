#include <stdio.h>
#include <stdlib.h>
#include "fatfs_api.h"
#include "disk.h"

int m_diskram_export(void)
{
    return m_disk_to_file();
}


int m_diskram_import(void)
{
    return m_file_to_disk();
}

////////////////////////////////////////////////////////////////////

FATFS fsp;           /* Filesystem object */
FRESULT m_f_mount(void)
{
    FRESULT res;  /* API result code */
    DIR dp;
    BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */

    m_diskram_import();

    res = f_mount(&fsp, "C:", 0);
    res = f_opendir(&dp, "C:/");
	if (res) {
        printf("mount fail, try again \n");
        res = f_mkfs("C:", FM_FAT32, 0, work, sizeof work);
        if (res) {
            return -1;
        }
        res = f_mount(&fsp, "C:", 0);
        if (res) {
            return -1;
        }
        m_diskram_export();
	} else {
        res = f_closedir (&dp);
    }

    return 0;
}

FRESULT m_f_unmount(void)
{
    FRESULT res;  /* API result code */
    res = f_mount(0, "C:", 0);
    m_diskram_export();
    return res;
}

/****************************
"r"	    FA_READ
"r+"	FA_READ | FA_WRITE
"w"	    FA_CREATE_ALWAYS | FA_WRITE
"w+"	FA_CREATE_ALWAYS | FA_WRITE | FA_READ
"a"	    FA_OPEN_APPEND | FA_WRITE
"a+"	FA_OPEN_APPEND | FA_WRITE | FA_READ
"wx"	FA_CREATE_NEW | FA_WRITE
"w+x"	FA_CREATE_NEW | FA_WRITE | FA_READ
***************************/

int m_f_open(FIL* fp, const TCHAR* path, const char *arg)
{
    FRESULT res;  /* API result code */
    BYTE mode;

    if (!memcmp(arg, "r+", 2)) {
        mode = FA_READ | FA_WRITE;
    } else if (!memcmp(arg, "r", 1)) {
        mode = FA_READ;
    } else if (!memcmp(arg, "a+", 2)) {
        mode = FA_OPEN_APPEND | FA_WRITE | FA_READ;
    } else if (!memcmp(arg, "a", 1)) {
        mode = FA_OPEN_APPEND | FA_WRITE;
    } else if (!memcmp(arg, "w+x", 3)) {
        mode = FA_CREATE_NEW | FA_WRITE | FA_READ;
    } else if (!memcmp(arg, "w+", 2)) {
        mode = FA_CREATE_ALWAYS | FA_WRITE | FA_READ;
    } else if (!memcmp(arg, "wx", 2)) {
        mode = FA_CREATE_NEW | FA_WRITE;
    } else if (!memcmp(arg, "w", 1)) {
        mode = FA_CREATE_ALWAYS | FA_WRITE;
    } else {
        return -1;
    }

	res = f_open(fp, path, mode);
    if (res) {
        return -1;
    }
    return 0;
}

int m_f_write(FIL *fp, BYTE *buff, UINT btw)
{
    FRESULT res;  /* API result code */
    UINT bw;
    res = f_write(fp, buff, btw, &bw);
    if (res) {
        return -1;
    }
    return bw;
}

int m_f_read(FIL *fp, BYTE *buff, UINT btr)
{
    FRESULT res;  /* API result code */
    UINT br;
	res = f_read(fp, buff, btr, &br);
	if (res) {
        return -1;
	}
    return br;
}

int m_f_close(FIL *fp)
{
    FRESULT res;  /* API result code */
	res = f_close(fp);
	if (res) {
        return res;
	}
    return res;
}

int m_f_size(FIL *fp)
{
    FRESULT res;  /* API result code */
	res = f_size(fp);
    return res;
}

int m_f_lseek(FIL *fp, DWORD ofs)
{
    FRESULT res;  /* API result code */
	res = f_lseek(fp, ofs);
    return res;
}

void m_f_test(void)
{
    FIL fp;
    int ret;
    unsigned char ddd[50] = {0};
    ret = m_f_mount();
    ret = m_f_open(&fp, "C:/1232.bin", "r");
    ret = m_f_size(&fp);
    printf("file size = %d \n", ret);
    ret = m_f_lseek(&fp, 0);
    ret = m_f_read(&fp, ddd, 10);
    printf("====> %s \n", ddd);
    ret = m_f_close(&fp);
    ret = m_f_open(&fp, "C:/1232.bin", "w+");
    ret = m_f_write(&fp, "nihaohwr1!", 10);
    ret = m_f_close(&fp);
    ret = m_f_open(&fp, "C:/1232.bin", "r");
    ret = m_f_size(&fp);
    printf("file size = %d \n", ret);
    ret = m_f_lseek(&fp, 0);
    ret = m_f_read(&fp, ddd, 10);
    printf("====> %s \n", ddd);
    ret = m_f_close(&fp);

    m_f_unmount();
}
///////////////////////////////////////////////////////////




void m_fs_test(void)
{
	FATFS fs;           /* Filesystem object */
    FIL fil;            /* File object */
    FRESULT res;  /* API result code */
    UINT bw;            /* Bytes written */
    BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
	BYTE mm[50];
	UINT i;

	printf("文件系统测试开始:\r\n");
	/* 格式化文件系统 */
	res = f_mkfs("C:", FM_FAT32, 0, work, sizeof work);//"0:"是卷标，来自于 #define SPI_FLASH		0
	if (res)
	{
		printf("文件系统格式化失败.\r\n");
		return ;
	}
	else
	{
		printf("文件系统格式化成功.\r\n");
	}
	/* 挂载文件系统 */
	res = f_mount(&fs, "C:", 0);
	if (res)
	{
		printf("文件系统挂载失败.\r\n");
	}
	else
	{
		printf("文件系统挂载成功.\r\n");
	}
	/* Create a file as new */
	res = f_open(&fil, "C:/123.txt", FA_CREATE_NEW|FA_WRITE|FA_READ);
	if (res)
	{
		printf("打开文件失败.\r\n");
	}
	else
	{
		printf("打开文件成功.\r\n");
	}
	/* Write a message */
	res = f_write(&fil, "Hello,World!", 12, &bw);
	printf("res write:%d\r\n",res);
	if (bw == 12)
	{
		printf("写文件成功!\r\n");
	}
	else
	{
		printf("写文件失败!\r\n");
	}
	res = f_size(&fil);
	printf("文件大小:%d Bytes.\r\n",res);
	memset(mm,0x0,50);
	f_lseek(&fil,0);
	res = f_read(&fil,mm,12,&i);
	if (res == FR_OK)
	{
		printf("读文件成功!\r\n");
		printf("读到数据长度:%d Bytes.\r\n",i);
	}
	else
	{
		printf("读文件失败!\r\n");
	}
	printf("读到如下数据: %s \r\n", mm);

	/* Close the file */
	f_close(&fil);
	/*卸载文件系统*/
	f_mount(0, "0:", 0);
	printf("文件系统测试完毕.\r\n");
}



void m_disk_bin_test(void)
{

	FATFS fs;           /* Filesystem object */
    FIL fil;            /* File object */
    FRESULT res;  /* API result code */
    UINT bw;            /* Bytes written */
	BYTE mm[50];
	UINT i;
    m_diskram_import();

	printf("文件系统测试开始:\r\n");

	/* 挂载文件系统 */
	res = f_mount(&fs, "C:", 0);
	if (res) {
		printf("文件系统挂载失败.\r\n");
	} else {
		printf("文件系统挂载成功.\r\n");
	}

	/* Create a file as new */
	res = f_open(&fil, "C:/123.txt", FA_READ);
	if (res) {
		printf("打开文件失败.\r\n");
	} else {
		printf("打开文件成功.\r\n");
	}
	res = f_size(&fil);
	printf("文件大小:%d Bytes.\r\n",res);

	memset(mm,0x0,50);
	f_lseek(&fil,0);
	res = f_read(&fil,mm,12,&i);
	if (res == FR_OK) {
		printf("读文件成功!\r\n");
		printf("读到数据长度:%d Bytes.\r\n",i);
	} else {
		printf("读文件失败!\r\n");
	}
	printf("读到如下数据: %s \r\n", mm);
    /* Close the file */
	f_close(&fil);


    /* Create a file as new */
	res = f_open(&fil, "C:/1231.txt", FA_READ);
	if (res) {
		printf("打开文件失败.\r\n");
	} else {
		printf("打开文件成功.\r\n");
	}
	res = f_size(&fil);
	printf("文件大小:%d Bytes.\r\n",res);

	memset(mm,0x0,50);
	f_lseek(&fil,0);
	res = f_read(&fil,mm,12,&i);
	if (res == FR_OK) {
		printf("读文件成功!\r\n");
		printf("读到数据长度:%d Bytes.\r\n",i);
	} else {
		printf("读文件失败!\r\n");
	}
	printf("读到如下数据: %s \r\n", mm);
    /* Close the file */
	f_close(&fil);


	res = f_open(&fil, "0:/1231.txt", FA_CREATE_ALWAYS|FA_WRITE|FA_READ);
	if (res) {
		printf("打开文件失败.\r\n");
	} else {
		printf("打开文件成功.\r\n");
	}
	/* Write a message */
	res = f_write(&fil, "Hello,herben", 12, &bw);
	printf("res write:%d\r\n",res);
	if (bw == 12) {
		printf("写文件成功!\r\n");
	} else {
		printf("写文件失败!\r\n");
	}
	res = f_size(&fil);
	printf("文件大小:%d Bytes.\r\n",res);
	memset(mm,0x0,50);
	f_lseek(&fil,0);
	res = f_read(&fil,mm,12,&i);
	if (res == FR_OK) {
		printf("读文件成功!\r\n");
		printf("读到数据长度:%d Bytes.\r\n",i);
	} else {
		printf("读文件失败!\r\n");
	}
	printf("读到如下数据: %s \r\n", mm);
    /* Close the file */
	f_close(&fil);



	/*卸载文件系统*/
	f_mount(0, "C:", 0);
	printf("文件系统测试完毕.\r\n");

    m_diskram_export();
}
