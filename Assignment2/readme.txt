1) make                     (To make the Kernel object File)

2) sudo insmod main.ko      (Insert the Object File into Kernel)

3)dmesg  (Check log)

4)sudo fdisk -l /dev/dof    (Partition Details that we have created)

5)sudo chmod 777 /dev/dof1  (Permission to access the file and its operations)

6)cat > /dev/dof1           (Used to enter the input)

                            After Enterting the input press Enter then press ctrl+z

7)xxd /dev/dof1 | less      (To display the input where it is stored in the partition we created)

8)sudo rmmod main.ko        (Remove from kernel)

