#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>		//include mmap 



/*
 *实现功能：操作/dev/mem描述符，读取/写入内存地址
 */

/*
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
*/

extern int errno;
	   
enum {
	ERROR = -1,
	SUCCESS = 0
};

enum {
	READ_FLAG  = 0,
	WRITE_FLAG = 1
};


#define MEM_DES_PATH  "/dev/mem"	//mem描述符路径
#define DEFUALT_OPT_MEM_SIZE 1		//默认操作内存大小

static const char *short_opts = "rwd:s:g:v:o:h?";
static const struct option longOpts[] = {
	{ "read", no_argument, NULL, 'r' },
	{ "write", no_argument, NULL, 'w' },
	{ "addr", required_argument, NULL, 'd' },
	{ "off", required_argument, NULL, 'o' },
	{ "size", required_argument, NULL, 's' },
	{ "value", required_argument, NULL, 'v' },
	{ "debug", required_argument, NULL, 'g' },
	{ "help", no_argument, NULL, 'h' },
	{ NULL, no_argument, NULL, 0 }
};


int open_des(char *path_p, int flag)
{
	int fd = ERROR;
	fd = open(path_p, flag);
	if(fd < 0){
		printf("[%s]-[%d]:%s\r\n", __func__, __LINE__ ,strerror(errno));
	}
	
	return fd;
}

void close_des(int fd)
{
	if(fd > 0){
		close(fd);
	}
}

/*
int mmap_addr()
{
	
}
*/


void print_usage(char *file)
{
	printf("Usage:\n");
	printf("%s -r -d [addr] -s [memsize] \n", file);
	printf("%w -r -d [addr] -s [memsize] -v [value]\n", file);	
	printf("\n");
	printf("eg: %s -r -d 0xe000a000 -s 1\n", file);	
	printf("eg: %s -w -d 0xe000a000 -s 1 -v 0xff\n", file);	
}


int main(int argc, char **argv)
{
	int opt = ERROR;
	int mem_fd = ERROR;
	int read_write_flag = ERROR;	//read = 0; write = 1;
	unsigned long addr = ERROR;	
	unsigned long value = ERROR;
	unsigned long mem_size = DEFUALT_OPT_MEM_SIZE;
	unsigned long *mem_addr = NULL;	
	char *p_End;
	printf("test3\r\n");
	
	if (argc < 3){
		print_usage(argv[0]);
		return -1;
	}
	
	if ( (mem_fd = open_des(MEM_DES_PATH, O_RDWR | O_SYNC)) < 0){
		return ERROR;
	}
	
	while( ( opt = getopt_long( argc, argv, short_opts, longOpts, NULL ) )!= -1 ) {
		switch( opt ) {
			case 'r':
					read_write_flag = READ_FLAG;					
				break;
			case 'w':
					read_write_flag = WRITE_FLAG;
				break;		
			case 's':
					if(optarg[0] == '0' && (optarg[1] == 'x' || optarg[1] == 'X') ){
						mem_size = strtoll(optarg+2, &p_End, 16);
					}else{
						mem_size = strtoll(optarg, &p_End, 10);
					}
					printf("mem_size:%lx\r\n",mem_size);
				break;	
			case 'd':
					if(optarg[0] == '0' && (optarg[1] == 'x' || optarg[1] == 'X') ){
						addr = strtoll(optarg+2, &p_End, 16);
					}else{
						addr = strtoll(optarg, &p_End, 10);
					}					
					printf("addr:%lx\r\n",addr);
				break;	
			case 'v':
					if(optarg[0] == '0' && (optarg[1] == 'x' || optarg[1] == 'X') ){
						value = strtoll(optarg+2, &p_End, 16);
					}else{
						value = strtoll(optarg, &p_End, 10);
					}
					printf("value:%lx\r\n",value);
				break;					
			case 'h':
					print_usage(argv[0]);
				break;	
			default:
				/* You won't actually get here. */
				break;
		}
	}

	printf("opt:%s addr:0x%lx size:0x%lx value:0x%lx\r\n",  read_write_flag?"write":"read", addr, mem_size, value);

    mem_addr = mmap(
                    NULL,                   //Any adddress in our space will do
                    mem_size,      		    //Map length
                    PROT_READ|PROT_WRITE,   // Enable reading & writting to mapped memory
                    MAP_SHARED,             //Shared with other processes
                    mem_fd,                 //File to map
                    addr	 		 		//Offset to GPIO peripheral
                  );	
	if(mem_addr == MAP_FAILED){
		printf("[%s]-[%d]:mmap %s\r\n", __func__, __LINE__ ,strerror(errno));
		close_des(mem_fd);
		return ERROR;
	}else{
		printf("mem_addr:[0x%x]\r\n", (int)mem_addr);
	}

	if(read_write_flag == READ_FLAG){
		value = *mem_addr;
		printf("read:[0x%x]\r\n",  value);
	}else{
		*mem_addr = value;
		printf("write:[0x%x]\r\n",  value);
	}		
	
	munmap(mem_addr,mem_size);
	
	close_des(mem_fd);	
	return 0;
}

