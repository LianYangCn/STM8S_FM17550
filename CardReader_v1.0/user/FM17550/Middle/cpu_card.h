#ifndef CPU_CARD_H
#define CPU_CARD_H 1
//struct apdu_frame
//{
//unsigned char pcb;
//unsigned char cid;
//unsigned char buff[62];
//};

extern unsigned char  PCB,CID;

extern void CPU_PCB(void);
extern unsigned char CPU_BaudRate_Set(unsigned char mode);
extern unsigned char CPU_TPDU(unsigned char send_len,unsigned char *send_buff,unsigned char *rece_len,unsigned char *rece_buff);
extern unsigned char CPU_Rats(unsigned char param1,unsigned char param2,unsigned char *rece_len,unsigned char *buff);
extern unsigned char CPU_PPS(unsigned char pps0,unsigned char pps1,unsigned char *rece_len,unsigned char *buff);
extern unsigned char CPU_Random(unsigned char *rece_len,unsigned char *buff);
extern unsigned char CPU_I_Block(unsigned char send_len,unsigned char *send_buff,unsigned char *rece_len,unsigned char *rece_buff);
extern unsigned char CPU_R_Block(unsigned char *rece_len,unsigned char *rece_buff);
extern unsigned char CPU_S_Block(unsigned char pcb_byte,unsigned char *rece_len,unsigned char *rece_buff);
//extern unsigned char CPU_auth(unsigned char *key_buff,unsigned char *rece_len,unsigned char *buff);
#endif
