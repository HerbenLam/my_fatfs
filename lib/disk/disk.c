#include <stdio.h>
#include <string.h>
#include "disk.h"

#define VDISK_SIZE      (64*1024*1024)
#define SECTOR_SIZE     (512)
#define SECTOR_COUNT    (VDISK_SIZE/512)

unsigned char vdisk[VDISK_SIZE] = {0};

int m_disk_to_file(void)
{
    FILE *fp = fopen("lib/disk/disk.bin", "wb+");
    if (fp == NULL) {
        printf("file open err !\n");
        return -1;
    }
    fwrite(vdisk, 1, VDISK_SIZE, fp);
    fclose(fp);
    return 0;
}

int m_file_to_disk(void)
{
    FILE *fp = fopen("lib/disk/disk.bin", "rb");
    if (fp == NULL) {
        printf("file open err !\n");
        return -1;
    }
    fread(vdisk, 1, VDISK_SIZE, fp);
    fclose(fp);
    return 0;
}

int m_disk_status(void)
{
    return 0;
}

int m_disk_initialize(void)
{
    return 0;
}

int m_disk_read(unsigned char *buff, unsigned long sector, unsigned int count)
{
    //printf("#r %x %d %d\n", buff, sector, count);
    memcpy(buff, vdisk+SECTOR_SIZE*sector, count*SECTOR_SIZE);
    //printf("#rend\n");
    return 0;
}

int m_disk_write(unsigned char *buff, unsigned long sector, unsigned int count)
{
    //printf("#w %x %d %d\n", buff, sector, count);
    memcpy(vdisk+SECTOR_SIZE*sector, buff, count*SECTOR_SIZE);
    //printf("#wend\n");
    return 0;
}

int m_disk_get_sector_count(void)
{
    return SECTOR_COUNT;
}

int m_disk_get_sector_size(void)
{
    return SECTOR_SIZE;
}























