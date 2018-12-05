#ifndef TYPE_B_H
#define TYPE_B_H 1
extern unsigned char PUPI[4];
extern unsigned char TypeB_Request(unsigned int *rece_len,unsigned char *buff,unsigned char *card_sn);
extern unsigned char TypeB_Select(unsigned char *card_sn,unsigned int *rece_len,unsigned char *buff);
extern unsigned char TypeB_GetUID(unsigned int *rece_len,unsigned char *buff);
extern unsigned char TypeB_Halt(unsigned char *card_sn);
extern unsigned char TypeB_WUP(unsigned int *rece_len,unsigned char *buff,unsigned char *card_sn);
#endif
