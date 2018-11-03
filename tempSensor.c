#include <stdio.h>
#include <stdlib.h>
#include "ifttt.h"
#include <unistd.h>
#include <curl/curl.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
 int fd;
 int n;
 char buf[101]; /* reads the file value from cat w1_slave */
 char config[1] = {0xF3};
 char data[5]=  {0};
 char cMinTemp[5];
 char cMaxTemp[5];
 char cCurrent[5];
 float initialTemp;	
 float cTemp;
 float minTemp = 300.0F;
 float maxTemp = 0.0F;
 int i,j;
 int counter = 0;
  while(1){
     fd = open("/sys/bus/w1/devices/28-01131bd38d54/w1_slave",O_RDONLY);	
      if(fd == -1)
        {
	perror("open of w1_slave failed");
	(void) exit(1);
  }
  counter++;
  while(1){
      n = read(fd,buf,256);
      if(n==0)
       {
	   break;
       }
      if(n==-1){
      perror("read fails");
       close(fd);
	exit(1);	
       }
  }
 
  for(i=0;i<=sizeof(buf);i++){
	if(buf[i] == 't'){
		for(j=0;j<sizeof(buf);j++){
		    data[j] = buf[i+2+j];
		 }	
	}
	
  }
 
 cTemp = (float) atoi(data)/1000;
 printf("%d ",counter);
 if(cTemp < minTemp){
        minTemp = cTemp;
        for(i=0;i<5;i++){
                cMinTemp[i] = data[i];
        }
 }
 if(cTemp > maxTemp){   
        maxTemp = cTemp;
             for(i=0;i<5;i++){
                        cMaxTemp[i] = data[i];
                }
 }

 if(counter == 1){
	initialTemp = cTemp;
        
         sprintf(cCurrent,"%f", cTemp);
         sprintf(cMinTemp,"%f", minTemp);
         sprintf(cMaxTemp,"%f", maxTemp);

	ifttt("https://maker.ifttt.com/trigger/temp_change/with/key/nAtR0mlz6FSWp52xT1BGw",cMaxTemp,cMinTemp,cCurrent);
 }

 if((cTemp - initialTemp) >=1){
		printf("changed");
                
                sprintf(cCurrent," %f", cTemp);
                sprintf(cMinTemp," %f", minTemp);
                sprintf(cMaxTemp," %f", maxTemp);

		ifttt("https://maker.ifttt.com/trigger/temp_change/with/key/nAtR0mlz6FSWp52xT1BGw",cMaxTemp,cMinTemp,cCurrent);
 }
 /*
 if(cTemp < minTemp){
	minTemp = cTemp;
	for(i=0;i<5;i++){
		cMinTemp[i] = data[i];
	}
 }
 if(cTemp > maxTemp){
	maxTemp = cTemp;
	     for(i=0;i<5;i++){
			cMaxTemp[i] = data[i];
		}
 }
 */
 printf("Current: %.3f\n", cTemp);
 printf("Min: %.3f\n", minTemp);
 printf("Max: %.3f\n", maxTemp);
  close(fd); 
 }
}
