/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */







///////////////////////////////////////////////////////////////
#include "disk.h"

DRESULT RAM_disk_status(void)
{
    return RES_OK;
}

DRESULT RAM_disk_initialize(void)
{
    return RES_OK;
}

DRESULT RAM_disk_read(BYTE *buff, DWORD sector, UINT count)
{
    m_disk_read(buff, sector, count);
    return RES_OK;
}

DRESULT RAM_disk_write(BYTE *buff, DWORD sector, UINT count)
{
    m_disk_write(buff, sector, count);
    return RES_OK;
}


DWORD RAM_disk_get_sector_count(void)
{
    return (DWORD)m_disk_get_sector_count();
}
WORD RAM_disk_get_sector_size(void)
{
    return (WORD)m_disk_get_sector_size();
}

/////////////////////////////////////////////////////////////





/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
		stat = RAM_disk_status();

		// translate the reslut code here

		return stat;

//	case DEV_MMC :
//		result = MMC_disk_status();
//
//		// translate the reslut code here
//
//		return stat;
//
//	case DEV_USB :
//		result = USB_disk_status();
//
//		// translate the reslut code here
//
//		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

//	case DEV_MMC :
//		result = MMC_disk_initialize();
//
//		// translate the reslut code here
//
//		return stat;
//
//	case DEV_USB :
//		result = USB_disk_initialize();
//
//		// translate the reslut code here
//
//		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		res = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

//	case DEV_MMC :
//		// translate the arguments here
//
//		result = MMC_disk_read(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//
//	case DEV_USB :
//		// translate the arguments here
//
//		result = USB_disk_read(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		res = RAM_disk_write((BYTE*)buff, sector, count);

		// translate the reslut code here

		return res;

//	case DEV_MMC :
//		// translate the arguments here
//
//		result = MMC_disk_write(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//
//	case DEV_USB :
//		// translate the arguments here
//
//		result = USB_disk_write(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive
		switch (cmd)
		{
		 case CTRL_SYNC:
			 return RES_OK;

		 /* 扇区数量 1024*1024*1024 =4 (MB) */

		 case GET_SECTOR_COUNT:

			 *(DWORD * )buff =  RAM_disk_get_sector_count();//W25Q32 有1024个大小为4k bytes 的扇区
			 return RES_OK;

		 /* 扇区大小 */

		 case GET_SECTOR_SIZE :

			 *(WORD * )buff =  RAM_disk_get_sector_size();//spi flash的扇区大小是 4K Bytes
			 return RES_OK;

		 /*块大小 */

		 case GET_BLOCK_SIZE :
		 	 *(DWORD * )buff = 1;
			 return RES_OK;

		 default:
		 	 return RES_PARERR;
		 }

		return res;

//	case DEV_MMC :
//
//		// Process of the command for the MMC/SD card
//
//		return res;
//
//	case DEV_USB :
//
//		// Process of the command the USB drive
//
//		return res;
	}

	return RES_PARERR;
}

