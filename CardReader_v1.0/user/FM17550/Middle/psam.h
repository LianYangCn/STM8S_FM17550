#ifndef PSAM_H 
#define PSAM_H 1
extern unsigned char sam_byte_read(unsigned char *sam_data);
extern unsigned char sam_byte_write(unsigned char sam_data);
extern unsigned char sam_write(unsigned char data_len,unsigned char *sam_data);
extern unsigned char sam_read(unsigned char *rece_len,unsigned char *rece_buff);
extern unsigned char sam_command(unsigned char data_len,unsigned char *data_buff,unsigned char *rece_len,unsigned char *rece_buff);
extern unsigned char sam_get_response(unsigned char response_length,unsigned char *rece_len,unsigned char *buff);
extern unsigned char sam_get_challenge(unsigned char *rece_len,unsigned char *buff);
//extern unsigned char sam_ex_authentication(unsigned char *key_buff,unsigned char *rece_len,unsigned char *buff);
extern unsigned char sam_reset(unsigned char *rece_len,unsigned char *buff);
#endif