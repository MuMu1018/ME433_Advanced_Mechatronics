#ifndef LSM6DS333_H__
#define LSM6DS333_H__

#define IMU_ADDR 0b1101010

void LSM6DS333_init(void);
void I2C_read_multiple(unsigned char, unsigned char, unsigned char *, int);
float getxXL(unsigned char * );
float getyXL(unsigned char * );

#endif