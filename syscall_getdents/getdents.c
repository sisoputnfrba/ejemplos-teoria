#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#define BUF_SIZE 1024*1024*5

#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct linux_dirent {
   long           d_ino;
   off_t          d_off;
   unsigned short d_reclen;
   char           d_name[];
};

int main(int argc, char *argv[]) {
   int fd, nread;
   char buf[BUF_SIZE];
   struct linux_dirent *d;
   int bpos;
   char d_type;

   fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
   if (fd == -1)
       handle_error("open");

   for ( ; ; ) {
       nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);

       if (nread == -1)
           handle_error("getdents");

       if (nread == 0)
           break;

       for (bpos = 0; bpos < nread;) {
           d = (struct linux_dirent *) (buf + bpos);
           bpos += d->d_reclen;
    	   if(d != NULL && d->d_ino) printf("%s\n", (char *) d->d_name);
       }
   }

   exit(EXIT_SUCCESS);
}