
#include "ASSIGN.h"  // including the header library for various tasks that we created for our device

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>              
#include <unistd.h>             
#include <sys/ioctl.h>          /* ioctl */

u_int16_t value;


// total 10 different functions from sensors which are calling ioctl function in driver module code.
int x_gyro(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, gyro_x, message);  // calling the ioctl function which is located in driver used for specific task from the device
                                                             //name file is the file we opened and gyro_x is the request code for device which we assigned in header function
    if (ret_val == 0) {
        printf("ioctl_ failed:%d\n", ret_val);   // if nothing is returned from the ioctl function in kernel driver then ioctl call is failed.
        exit(-1);                                //same for all the below functions
    }
    return 0;
}

int y_gyro(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, gyro_y, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int z_gyro(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, gyro_z, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int x_accelero(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, accelero_x, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int y_accelero(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, accelero_y, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int z_accelero(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, accelero_z, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int x_compass(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, compass_x, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int y_compass(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, compass_y, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int z_compass(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, compass_z, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}


int barom(int namefile, char *message)
{
    int ret_val;
    ret_val = ioctl(namefile, baro , message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}
int main()
{
    int reading;
    int choose;
    int namefile;
    char *msg = "Message passed by ioctl\n";

    namefile = open(DEVICE_FILE_NAME, 0);   //opening the device file
    if (namefile < 0) {                                                // if open function doesnt respond with some return value then we cant open the file.
        printf("Unable to open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }
    printf("1.Gyros Pitch \n 2.Gyro Yaw \n 3.Gyro Roll \n 4.Accelerometer acceleration\n  5. Accelerometer left right acc \n 6.Up and Down acc \n 7.Compass X \n 8.Compass Y \n 9.Compass Z \n 10.baro pressure \n");
    printf("Select one\n");
     scanf("%d",&choose);    
     switch(choose)
     {
          case 1: x_gyro(namefile,"10");break;
          case 2: y_gyro(namefile,"11");break;
          case 3: z_gyro(namefile,"12");break;
          case 4: x_accelero(namefile,"19");break;
          case 5: y_accelero(namefile,"23");break;
          case 6: z_accelero(namefile,"45");break;
          case 7: x_compass(namefile,"41");break;
          case 8: y_compass(namefile,"65");break;
          case 9: z_compass(namefile,"21");break;
          case 10: barom(namefile,"16");break;
          default: printf("Select the appropriate option\n");break;
     }  
   
    reading = read(namefile, &value, sizeof(value));  //reading the value from sensor using driver function read.
    printf("The reading given as\n");
    printf("%d\n", reading);                             // printing the required sensor value
    close(namefile);                                     //closing the file
    return 0;
}
