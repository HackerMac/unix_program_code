#include <unistd.h>

// 返回值：读到的字节数，若已到文件尾，返回0；若出错，返回-1
ssize_t pread(inf fd, void *buf, size_t, nbytes, off_t offset);

// 返回值：若成功，返回已写的字节数，若出错，返回-1
ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);

/*	调用pread相当于当用lseek后调用read,但是pread又与这种顺序调用有下列重要区别
 *	调用pread时，无法中断器定位于读操作
 *	不更新当前文件偏移量
 *	调用pwrite相当于调用lseek后调用write
 *	/
 

int dup(int fd);
int dup2(int fd, int fd2);

/*	dup(fd) -> fcntl(fd, F_DUPFD, 0)
 *
 *	dup2(fd, fd2) -> close(fd2)
 *					 fcntl(fd, F_DUPFD, fd2)
 *
 */


int fsync(int fd);

int fdatasync(int fd);
					/*若成功 返回值为0， 若出错， 返回-1*/
void sync(void);
		
/* sync 只是将所有修改过的块缓冲区排入写队列，然后返回，并不等待实际写磁盘操作结束
 * update(系统守护进程)周期性调用（一般隔30s）sync函数， 这就保证了定期冲洗(flush) 内核的块缓冲区 sync(1) 调用 sync函数
 * fsync函数只对有文件描述父fd指定的一个文件起作用，并且等待写磁盘操作结束才返回
 * fsync可用于对数据库，因为需要对修改过的块立即写到磁盘上
 * fdatasync函数类似于fsync, 但他只影响文件的数据部分。除数据外，fsync还会同步更新文件属性
 * /



#include <fcntl.h>

int fcntl(int fd, int cmd, .... /*int arg*/);
						/* 返回值：若成功->依赖于cmd 若出错-> 返回-1 */

/*fcntl 有如下5个功能：
 复制一个已有的描述符号
 获取/设置文件描述符标志
 获取/设置文件状态标志
 获取/设置异步I/O所有权
 获取/记录记录锁
*/

#include <ioctl.h>

int ioctl(int fd, int request, ...);
				/* 返回值，若出错，返回-1，若成功， 返回其他值*/
/*
 * 磁带操作使我们可以在磁带上写一个文件结束标志，倒带，越过指定个数的文件或记录等
 * 用（read、write、lseek）都难于表示这些操作，此时对这些设备进行操作最容易的方法就是ioctl
 * ioctl获取和设置中断窗口大小
 * /
 


相关Linux命令
time (./可执行文件 ...(包含相关操作)) 统计程序运行事件
