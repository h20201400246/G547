#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define gyro_x _IOWR(MAJOR_NUM, 0, char *)   //major number is unique to every device so its better to give major number as majic number for request.

#define gyro_y _IOWR(MAJOR_NUM, 1, char *)
                                             //since only a single device is performing all these functions one major number is enough.
#define gyro_z _IOWR(MAJOR_NUM, 2, char *)

#define accelero_x _IOWR(MAJOR_NUM, 3, char *)

#define accelero_y _IOWR(MAJOR_NUM, 4, char *)

#define accelero_z _IOWR(MAJOR_NUM, 5, char *)

#define compass_x _IOWR(MAJOR_NUM, 6, char *)

#define compass_y _IOWR(MAJOR_NUM, 7, char *)

#define compass_z _IOWR(MAJOR_NUM, 8, char *)

#define baro _IOWR(MAJOR_NUM, 9, char *)

#define DEVICE_FILE_NAME "/dev/imu_char"

#endif
