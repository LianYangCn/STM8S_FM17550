
extern unsigned char  picc_atqa[2],picc_uid[15],picc_sak[3];

extern unsigned char TypeA_Request(unsigned char *pTagType);
extern unsigned char TypeA_WakeUp(unsigned char *pTagType);
extern unsigned char TypeA_Anticollision(unsigned char selcode,unsigned char *pSnr);
extern unsigned char TypeA_Select(unsigned char selcode,unsigned char *pSnr,unsigned char *pSak);
extern unsigned char TypeA_Halt(void);
extern unsigned char TypeA_CardActive(unsigned char *pTagType,unsigned char *pSnr,unsigned char *pLng,unsigned char *pSak);
