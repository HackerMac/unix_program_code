#include "apue.h"
#include <fcntl.h>

int main (int argc, char *argv[]) {
	int val;

	if (argc != 2) err_quit("usage: a.out <descriptor#>");

	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) 
			err_sys("fcntl error for fd %d", atoi(argv[1]));

	switch(val & O_ACCMODE) {
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			err_dump("unknoen access mode");

	}
	// 当然可通过或运算开启对应标志位
	// 通过与对应位进行与判断是否该标志位存在
	if (val & O_APPEND) printf(", append");
	if (val & O_NONBLOCK) printf(", nonblcoking");
	if (val & O_SYNC) printf(", synchronous wirtes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC)
		printf(", syncchonous writes");
	
#endif

	putchar('\n');
	exit(0);

}
