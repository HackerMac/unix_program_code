#include <sys/stat.h>
#include "apue.h"

int stat(const char *restrict pathname, struct stat *restrict buf);

int fstat(int fd, struct stat *buf);

int lstat(const char *restrict pathname, struct stat restrict buf);

int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);
									// 4个函数的返回值 若成功：返回0，若出错，返回-1

struct stat {
	mode_t st_mode;	// file_tpye & mode(permission)
	ino_t  st_ino;	// i_node number(serial number)
	dev_t  st_dev;	// device number (file system)
	dev_t  st_rdev;	// device number for special files
	nlink_t st_nlink; // number of links
	uid_t  st_uid;	// user ID of owner
	gid_t  st_gid;	// group ID of owner
	off_t  st_size; // size in bytes, for regular files
	struct timespec	st_atime;	// time of last access
	struct timespec st_mtime; 	// time of last modification
	struct timespec st_ctime; 	// time of last file status change
	blksize_t st_blksize;		// best I/O block size
	blkcnt_t  st_blocks;		// number of disk blocks allocated
};

// 按照秒和纳秒定义了时间戳
struct timespec {
	time_t tv_sec;
	long tv_nsec;
}

文件类型
/*	普通文件 regular file    -> 包含的数据无论是文本还是二进制数据，对于内核而言并无区别
 *	目录文件 directory file  -> 包含其他文件的名字以及指向与这些文件有关信息的指针
 *								-> 对于同一目录而言 需要具有读权限的进程才可以读该目录内容
 *								-> 对于内核而言 可直接写目录文件
 *	块特殊文件 block special -> 提供对设备（如磁盘）带缓冲的访问,每次访问以固定长度为单位进行
 *	字符特殊文件 character specail file
 *							 -> 提供对设备不带缓冲的访问，每次访问长度可变
 *							 -> 系统中的所有设备要么是字符特殊文件要么是块特殊文件
 *	FIFO					 -> 这种类型的文件用于进程间通信 （管道 pipe） char-15
 *	套接字	socket			 -> 这种类型的文件用于进程间的网络通信
 *							 -> 可用于一台宿主机上进程之间的非网络通信	   char-16
 *  符号链接  symbolic link	 -> 文件指向另一个文件 软/硬链接
 /
st_mode 成员
S_ISREG() 普通文件
S_ISDIR() 目录文件
S_ISCHR() 字符特殊文件
S_ISBLK() 块特殊文件
S_ISFIFO() 管道或FIFO
S_ISLINK()	符号链接
S_ISSOCK()	套接字
/*	POSIX.1 实现进程间通信(IPC)对象(如消息队列和信号量)说明为文件
 *	位于#include <sys/stat.h>中
 *	他们的参数并非st_mode 类型，而是指向stat的指针
 *	S_TYPEISMQ() 消息队列
 *	S_TYPEEISSEM() 信号量
 *	S_TYPEISSHM() 共享存储对象
 * /



