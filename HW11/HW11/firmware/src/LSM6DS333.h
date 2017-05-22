#ifndef LSM6DS333_H__
#define LSM6DS333_H__

#define IMU_ADDR 0b1101010

void LSM6DS333_init(void);
void I2C_read_multiple(unsigned char, unsigned char, unsigned char *, int);
float getTemp(unsigned char * );
float getxG(unsigned char * );
float getyG(unsigned char * );
float getzG(unsigned char * );
float getxXL(unsigned char * );
float getyXL(unsigned char * );
float getzXL(unsigned char * );

#endif