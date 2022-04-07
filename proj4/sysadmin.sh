#!/bin/bash
# sysadmin.sh
# Solomon Himelbloom
# 2022-04-06
# 
# For CS 321 Spring 2022
# File System: Shell Scripting
# 
# Submission: Write down the final list of commands in a .sh file. 
# Write a question as a comment in the file followed by the command 
# sequence or shell-script required to solve it.

echo "
  _   _   _    _____    ____ ____    _________  _ 
 | | | | / \  |  ___|  / ___/ ___|  |___ /___ \/ |
 | | | |/ _ \ | |_    | |   \___ \    |_ \ __) | |
 | |_| / ___ \|  _|   | |___ ___) |  ___) / __/| |
  \___/_/   \_\_|      \____|____/  |____/_____|_|

  "

# 1. Use the command chmod to modify the permissions to files and directories for 
# owner, group and others. Create a shell script and give the current user 
# full permission (read, write, and execution) and everyone else read and execute permission only. 
touch sysadmin.sh
chmod 755 sysadmin.sh

# 2. Create a FAT, NTFS, and EXT3 filesystem in your Linux box. 
# Mount it in three separate subdirectories inside /mnt/ (say, myFat, myNTFS, and myEXT3). 

# 2a. FAT
dd if=/dev/zero of=fat-image.dd bs=1M count=10 # Create a new disk (10 MB) image.
mkfs.fat fat-image.dd # Initialize it with a file system.
mkdir /mnt/myFat # Create a unique mount point.
mount fat-image.dd /mnt/myFat # Mount the image.

# 2b. NTFS
dd if=/dev/zero of=ntfs-image.dd bs=1M count=10
mkfs.ntfs ntfs-image.dd
mkdir /mnt/myNTFS
mount ntfs-image.dd /mnt/myNTFS

# 2c. EXTF
dd if=/dev/zero of=ext3-image.dd bs=1M count=10
mkfs.ext3 ext3-image.dd
mkdir /mnt/myEXT3
mount ext3-image.dd /mnt/myEXT3

# 3. Use 'df' command to test it.
df -h

# 4. Now create three different users called testuser1, testuser2, and testuser3.
adduser testuser1
adduser testuser2
adduser testuser3

# 5. Create a group called myfsuser.
groupadd myfsuser

# 6. Add all those three users to myfsuser group.
usermod -a -G myfsuser testuser1
usermod -a -G myfsuser testuser2
usermod -a -G myfsuser testuser3

# 7. Set the permission of the myFat directory so that 
# only the members of 'myfsuser' group can access it.
chmod -R 070 /mnt/myFat
chgrp -R myfsuser /mnt/myFat

# 8. Now write a program (shell script) that will check if the current
# user has write permission to myFat, myNTFS and myEXT3. 
# In three separate print statements let the user know about it. 
# For example, if the user has write permission to 'myFat' print a message:
# -> "You have permission to write in myFat."
# Otherwise, print a message:
# -> "You do not have permission to write in myFat.

# 8a. myFat
if [ -w /mnt/myFat ]
then
    echo "You have permission to write in myFat."
else
    echo "You do not have permission to write in myFat."
fi

# 8b. myNTFS
if [ -w /mnt/myNTFS ]
then
    echo "You have permission to write in myNTFS."
else
    echo "You do not have permission to write in myNTFS."
fi

# 8c. myEXT3
if [ -w /mnt/myEXT3 ]
then
    echo "You have permission to write in myEXT3."
else
    echo "You do not have permission to write in myEXT3."
fi

# 9. Now modify the ~./bashrc file so that the user will automatically 
# get the message right after login.
if [ -w /mnt/myFat ] || [ -w /mnt/myNTFS ] || [ -w /mnt/myEXT3 ]
then
    echo 'echo "You have permission to write in myFat, myNTFS, or myEXT3."' >> ~/.bashrc
else
    echo 'echo "You do not have permission to write in myFat, myNTFS, or myEXT3."' >> ~/.bashrc
fi
