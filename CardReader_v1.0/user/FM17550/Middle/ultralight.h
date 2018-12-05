#ifndef ULTRALIGHT_H
#define ULTRALIGHT_H 1


extern unsigned char Ultra_Read(unsigned char block_address,unsigned char *buff);
extern unsigned char Ultra_Write(unsigned char block_address,unsigned char *buff);

#endif
