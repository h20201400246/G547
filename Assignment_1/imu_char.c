#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/random.h>
#include <linux/sched.h>
#include <linux/uaccess.h>        
#include <linux/time.h>
#include <linux/ioctl.h>
#include <linux/slab.h>


#include "ASSIGN.h"                  // declaring the header file for various requests from the device
#define x 100                  //any number other than zero to say that we accesed the file in the user space to user.
#define DEVICE_NAME "imu_char"


uint16_t i1;
static uint16_t *message_ptr;
static char alignment;

static dev_t first;          //variable for device number
static struct cdev c_dev;    //variable for the character device structure
static struct class *cls;    //varible for the device class

static int my_open(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Mychar : open()\n");
   return 0;
}

static int my_close(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Mychar : close()\n");
   return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
   printk(KERN_INFO "Mychar : read()\n");
    char *b;
    int bytes_read = 0;
    int temp;
#ifdef DEBUG
    printk(KERN_INFO "device_read(%p,%p,%d)\n", file, buf, length);
#endif
    uint16_t random,i;
    get_random_bytes(&i1, sizeof(i1));                                 // Since 10 bit highest value is 1023 so %1023 is taken and this value is returned to user space
    i1 = i1%1023;
    printk(KERN_INFO "random number : %d\n", i1);
    return i1;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
   printk(KERN_INFO "Mychar : write()\n");
   return len;
}

static struct file_operations fops =         //all file operations
{
   .owner     = THIS_MODULE,
   .open      = my_open,
   .release   = my_close,
   .read      = my_read,
   .write     = my_write
};




static long ioctl(struct file *file,        
                  unsigned int ioctl_num,        
                  unsigned long ioctl_param)
{
    int i;
    char *temp;
    switch (ioctl_num) {                      // ioctl function will be called according to the call function from user code. So as we defined different requests in header so for
                                                    //                     every ioctl request a 32 bit request number is created 
    case gyro_x:    
          temp = (char *)ioctl_param;
          copy_to_user(temp, &i1, sizeof(i1));      // same as mentioned above for all the below functions
          break;
         
    case gyro_y:  
          
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1));       //this function calls the read function which returns random value to the user
         break;
                           
    case gyro_z:  
          
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1));  
         break;
         
    case accelero_x:    
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1));   
         break;
         
    case accelero_y:    
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1));  
         break;
                           
    case accelero_z:    
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1)); 
         break; 
         
    case compass_x:    
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1));   
         break;
         
    case compass_y:    
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1)); 
         break;
                           
    case compass_z:    
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1));   
         break;  
         
    case baro:
         temp = (char *)ioctl_param;
         copy_to_user(temp, &i1, sizeof(i1)); 
         break;
    default :  break;

    }

    return x;  // returning this value means the user accessed the ioctl function from kernel.
}




static int __init mychar_init(void)
{
  printk(KERN_INFO  "IMU CHAR driver registered ");
  
  //reserve <major,minor>
  if(alloc_chrdev_region(&first,0,1,"BITS-PILANI")<0)   // giving major number and minor number to the device
  {
        return -1;
  }
  
 
  if((cls=class_create(THIS_MODULE,"chardev"))==NULL)    //Creating class for the device
  {
      unregister_chrdev_region(first,1);
	  return -1;
  }
  

  if((device_create(cls,NULL,first,NULL,"imu_char"))==NULL)  //Creating node for the device
  {
      class_destroy(cls);
      unregister_chrdev_region(first,1);
	  return -1;
  }
  
  
  
  cdev_init(&c_dev,&fops);
  if(cdev_add(&c_dev,first,1)== -1)                       // Linking the node of the device to the Kernel Driver.
  {
      device_destroy(cls,first);
      class_destroy(cls);
      unregister_chrdev_region(first,1);
	  return -1;
  }
  return 0;  
}

static void __exit mychar_exit(void)
{                                                      // to deregister the device first we need to delete the link to the node,then the node, then the class, then destroy device.
   cdev_del(&c_dev);
   device_destroy(cls,first);
   class_destroy(cls);
   unregister_chrdev_region(first,1);
   printk(KERN_INFO "Bye:mychar driver unregistered\n\n");
   
}

module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAINADH");
MODULE_DESCRIPTION("Assignment-1");
