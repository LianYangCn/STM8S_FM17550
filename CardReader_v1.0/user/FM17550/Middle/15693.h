#ifndef _15693_H
#define _15693_H
extern unsigned char rfid[8];

extern unsigned char ISO15693_Init(void);
extern unsigned char ISO15693_Stayquite(void);
extern unsigned char ISO15693_Inventory(unsigned char *rece_len,unsigned char *buff,unsigned char *card_uid,unsigned char *slot_num);
extern unsigned char ISO15693_Select(unsigned char *card_uid,unsigned char *rece_len,unsigned char *buff);
extern unsigned char ISO15693_Read(unsigned char block,unsigned char *rece_len,unsigned char *buff);
extern unsigned char ISO15693_Write(unsigned char card_type,unsigned char block, unsigned char *block_data,unsigned char *rece_len,unsigned char *buff);
extern unsigned char ISO15693_Getinfo(unsigned char *rece_len,unsigned char *buff);
extern unsigned char ISO15693_Inventory_16slot(unsigned char *card_num,unsigned char *card_uid);
extern unsigned char ISO15693_Mult_Read(unsigned char block1,unsigned char block2,unsigned char *rece_len,unsigned char *buff);
#endif
