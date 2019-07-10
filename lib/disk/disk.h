#ifndef _DISK_H_
#define _DISK_H_

extern int m_disk_to_file(void);
extern int m_file_to_disk(void);

extern int m_disk_status(void);
extern int m_disk_initialize(void);
extern int m_disk_read(unsigned char *buff, unsigned long sector, unsigned int count);
extern int m_disk_write(unsigned char *buff, unsigned long sector, unsigned int count);
extern int m_disk_get_sector_count(void);
extern int m_disk_get_sector_size(void);

#endif
