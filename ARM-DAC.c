#include<lpc213x.h>
int i,j,value,count=0;
void delay_ms(int j)
{
   int x,i;
   for(i=0;i<j;i++)
   {
    for(x=0;x<6000;x++);
   }
}
void delay()
{
   for(j=0;j<1000;j++);
}
int main()
{
   int sin_wave[42] = { 512,591,665,742,808,873,926,968,998,1017,1023,1017,998,968,926,873,808,742,665,591,512,436,359,282,216,211,151,97,55,25,6,0,6,25,55,97,151,211,216,282,359,436 };
   PINSEL1 = 1<<19;
   IODIR0 = 0xFFFFFFFF;
   IODIR1 = 0xFFFEFFFF;
   while(1)
   {
      if((IOPIN1&1<<16)==0)
      {
         count = count + 1;
	     while((IOPIN1&1<<16)==0);
      }
       if(count == 3)  //FOR SAWTOOTH WAVE
       {
           for(i=0;i<1024;i++)
           {
              DACR = i<<6|1<<16;
	          delay();
           }
       }
       if(count == 2)//FOR TRIANGULAR WAVE
       {
          for(i=0;i<1024;i++)
          {
             DACR = i<<6|1<<16;
	         delay();
          }
	      for(i=1023;i>0;i--)
          {
             DACR = i<<6|1<<16;
	         delay();
          }
       }
       if(count ==0)//FOR SQUARE WAVE
       {
      
         DACR = 1023<<6|1<<16;
	     delay();
         DACR = 0<<6|1<<16;
	     delay();
       }
      if(count == 1)//FOR SINE WAVE 
      {
      
         while(i!=42)
	     {
	       value = sin_wave[i];
		   DACR = ((1<<16) | (value<<6));
		   delay_ms(1);
		   i++;
	     }
	     i = 0;
      }

      
   }
   
}