#ifndef _FATFS_API_H_
#define _FATFS_API_H_

#include "ff.h"

extern void m_fs_test(void);
extern void m_disk_bin_test(void);

extern FRESULT m_f_mount(void);
extern FRESULT m_f_unmount(void);
extern int m_f_open(FIL* fp, const TCHAR* path, const char *arg);
extern int m_f_write(FIL *fp, BYTE *buff, UINT btw);
extern int m_f_read(FIL *fp, BYTE *buff, UINT btr);
extern int m_f_close(FIL *fp);
extern int m_f_size(FIL *fp);
extern int m_f_lseek(FIL *fp, DWORD ofs);
extern void m_f_test(void);

#endif
