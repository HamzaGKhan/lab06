#include <stdio.h>
#include <stdlib.h>
#include "ifttt.h"

int main(int argc, char *argv[])
{
 FILE *fd;
 int n;
 char buf[101]; /* reads the file value from cat w1_slave */
 char config[1] = {0xF3};
 write(file, config, 1); 
 sleep(1);
 if((fd = fopen("/sys/bus/w1/devices/28-01131bd38d54/w1_slave", "r")) == (FILE *)NULL) 
  {
  perror("open of /sys/bus/w1/devices/28-01131bd38d54/w1_slave  failed");
  (void) exit(1);
 }

   char data[5]={0}; /*stores the temperature in a 5 bit word */

   n = fread(buf, 1, 100, fd);
   if(n == 0) 
	{
	 perror("read fails!");
 	exit(1);
 	}
  float cTemp = (data[0] * 256 + data[1]);
  cTemp = (((cTemp * 175.72) / 65536) - 46.85);
  float fTemp = cTemp * 1.8 + 32;
 
 printf("Temperature in Celsius    : %.2f\n", cTemp);
 printf("Temperature in Fahrenheit : %.2f\n", fTemp);

}
