#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#define max(a,b) ((a)>(b) ? (a):(b))

int main() {
   char buf[1600];
   int f1, f2, l, fm;
   fd_set fds;
   struct ifreq ifr;

   if ((f1 = open("/dev/net/tun", O_RDWR)) == -1) {
       printf("open f1: %s\n", strerror(errno));
       return 1;
   }

   if ((f2 = open("/dev/net/tun", O_RDWR)) == -1) {
       printf("open f2: %s\n", strerror(errno));
       return 1;
   }

   memset(&ifr, 0, sizeof(ifr));
   ifr.ifr_flags = IFF_TUN;
   if (ioctl(f1, TUNSETIFF, (void*)&ifr)) {
       printf("f1 TUNSETIFF: %s\n", strerror(errno));
       return 1;
   }

   memset(&ifr, 0, sizeof(ifr));
   ifr.ifr_flags = IFF_TUN;
   if (ioctl(f2, TUNSETIFF, (void*)&ifr)) {
       printf("f2 TUNSETIFF: %s\n", strerror(errno));
       return 1;
   }

   printf("bridge is ready\n");
   fm = max(f1, f2) + 1;
   while(1){
       FD_ZERO(&fds);
       FD_SET(f1, &fds);
       FD_SET(f2, &fds);
       select(fm, &fds, NULL, NULL, NULL);
       if( FD_ISSET(f1, &fds) ) {
           l = read(f1, buf, sizeof(buf));
           write(f2, buf, l);
       }
       if( FD_ISSET(f2, &fds) ) {
           l = read(f2, buf, sizeof(buf));
           write(f1, buf, l);
       }
   }
   return 0;
}
