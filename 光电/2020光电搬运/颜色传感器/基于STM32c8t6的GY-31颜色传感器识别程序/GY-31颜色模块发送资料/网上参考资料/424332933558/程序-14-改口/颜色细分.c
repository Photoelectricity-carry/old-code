#include <reg52.h>
unsigned  int  code jdm=(3*256),jdn=(3*256);
extern  unsigned int rgb[];
extern  float rx,gx,bx;
extern  unsigned int x,y,z;
display(unsigned int x);
fews(unsigned int ss)
{
static unsigned int wwwww;
if(wwwww<500)
      display(ss);//((x>>8)|(ss|0x0100));
else if((wwwww<2000)&(wwwww>499))
      display(ss);//((y>>8)|(ss|0x0200));
else if((wwwww<3000)&(wwwww>1999))
      display(ss);//((z>>8)|(ss|0x0300)); 
else wwwww=0;

wwwww++;

}
                                                    
zrgb(unsigned char we)//������
{
fews(0x1000|we);    
}

zrbg(unsigned char we)//������
{
fews(0x2000|we);   
}

zgrb(unsigned char we)//�̺���
{
fews(0x3000|we);
}

zgbr(unsigned char we)//������
{
fews(0x4000|we);   
}

zbrg(unsigned char we)//������
{
fews(0x5000|we);   
}

zbgr(unsigned char we)//���̺�
{
fews(0x6000|we);   
}
rgb_rgb()//������ƽ��
{
fews(0x7000); 
}

rg_rgb(unsigned char we)//����ƽ��
{
 fews(0x8000|we);

}

rb_rgb(unsigned char we)//����ƽ��
{
 fews(0x9000|we);

}

gb_rgb(unsigned char we)//����ƽ��
{
 fews(0xa000|we);

}



unsigned char max(unsigned int x,unsigned int y,unsigned int z)//����
{
 if((x-z)<jdm)//����
      return 'a';
 else if((x-y)<jdm)
       {          return 'b'; }
 else if((y-z)<jdm)
        {         return 'c'; }
 else return 'n';
}
unsigned char may(unsigned int x,unsigned int y,unsigned int z)//��ƽ��
{
 if((x-y)<jdn)
       {
          if((y-z)<jdn)
               return 'a';
          else if((y-z)<(2*jdn))
               return 'b';
          else if((y-z)<(3*jdn))
               return 'c';
          else if((y-z)<(4*jdn)) 
               return 'd'; 
          else if((y-z)<(5*jdn)) 
               return 'e';
          else if((y-z)<(6*jdn))
               return 'f'; 
          else return 'g'; 
       }                    
 else if((x-y)<(2*jdn))
       {
         if((y-z)<jdn)
               return 'h';
          else if((y-z)<(2*jdn))
               return 'i';
          else if((y-z)<(3*jdn))
               return 'j';
          else if((y-z)<(4*jdn)) 
               return 'k'; 
          else if((y-z)<(5*jdn)) 
               return 'l';
          else if((y-z)<(6*jdn))
               return 'm'; 
          else return 'n'; 

       }                  
 else if((x-y)<(3*jdn))
        {
          if((y-z)<jdn)
               return 'o';
          else if((y-z)<(2*jdn))
               return 'p';
          else if((y-z)<(3*jdn))
               return 'q';
          else if((y-z)<(4*jdn)) 
               return 'r'; 
          else if((y-z)<(5*jdn)) 
               return 's';
          else if((y-z)<(6*jdn))
               return 't'; 
          else return 'u'; 

       }
else if((x-y)<(4*jdn))
        {
          if((y-z)<jdn)
               return 'v';
          else if((y-z)<(2*jdn))
               return 'w';
          else if((y-z)<(3*jdn))
               return 'x';
          else if((y-z)<(4*jdn)) 
               return 'y'; 
          else if((y-z)<(5*jdn)) 
               return 'z';
          else if((y-z)<(6*jdn))
               return 'A'; 
          else return 'B'; 

       }
else if((x-y)<(5*jdn))
        {
          if((y-z)<jdn)
               return 'C';
          else if((y-z)<(2*jdn))
               return 'D';
          else if((y-z)<(3*jdn))
               return 'E';
          else if((y-z)<(4*jdn)) 
               return 'F'; 
          else if((y-z)<(5*jdn)) 
               return 'G';
          else if((y-z)<(6*jdn))
               return 'H'; 
          else return 'I'; 

       }


else if((x-y)<(6*jdn))
        {
          if((y-z)<jdn)
               return 'J';
          else if((y-z)<(2*jdn))
               return 'K';
          else if((y-z)<(3*jdn))
               return 'L';
          else if((y-z)<(4*jdn)) 
               return 'M'; 
          else if((y-z)<(5*jdn)) 
               return 'N';
          else if((y-z)<(6*jdn))
               return 'O'; 
          else return 'P'; 

       }

                  
       
 else  {
         if((y-z)<jdn)
               return 'Q';
          else if((y-z)<(2*jdn))
               return 'R';
          else if((y-z)<(3*jdn))
               return 'S';
          else if((y-z)<(4*jdn)) 
               return 'T'; 
          else if((y-z)<(5*jdn)) 
               return 'U';
          else if((y-z)<(6*jdn))
               return 'V'; 
          else return 'W'; 

       }                  





}
unsigned char maz(unsigned int x,unsigned int y)//��ƽ��
{
 if((x-y)<jdn)
    return 'a';
 else if((x-y)<(2*jdn))
     return 'b';
 else if((x-y)<(3*jdn))
     return 'c';
else if((x-y)<(4*jdn))
     return 'd';
 else if((x-y)<(5*jdn))
     return 'e';
else if((x-y)<(6*jdn))
     return 'f';
 else if((x-y)<(7*jdn))
     return 'g';
 else return 'h'; 
 
}



ysxf()//�ⲿ��Ϊ��ɫѡ��
{unsigned char saz; 
 unsigned int xrgb[3];

   x=(rx*rgb[0]); 
   y=(rgb[1]);    
   z=(bx*rgb[2]);
    
        if((x>=y)&(y>=z))//������
          {
            if(max(x,y,z)=='a') rgb_rgb();//��ƽ��
            else if(max(x,y,z)=='n'){zrgb(may(x,y,z));}//��ƽ��  
            else if(max(x,y,z)=='b'){rg_rgb(maz(y,z));}//12ƽ��
            else if(max(x,y,z)=='c'){gb_rgb(maz(x,y));}//23ƽ�� 
         

          } 
        
   else if((x>=z)&(z>=y))//������
          { 
            if(max(x,z,y)=='a') rgb_rgb();//��ƽ��
            else if(max(x,z,y)=='n'){zrbg(may(x,z,y));}//��ƽ��  
            else if(max(x,z,y)=='b'){rb_rgb(maz(z,y));}//12ƽ��
            else if(max(x,z,y)=='c'){gb_rgb(maz(x,z));}//23ƽ�� 
            
           // if(max(x,z,y)==(saz='a')) rgb_rgb();//��ƽ�� 
           // else zrbg(saz); 
          }      
   
   else if((y>=x)&(x>=z))//�̺���
            {
              if(max(y,x,z)=='a') rgb_rgb();//��ƽ��
              else if(max(y,x,z)=='n'){zgrb(may(y,x,z));}//��ƽ��  
              else if(max(y,x,z)=='b'){rg_rgb(maz(x,z));}//12ƽ��
              else if(max(y,x,z)=='c'){rb_rgb(maz(y,x));}//23ƽ�� 


             // if(max(y,x,z)==(saz='a')) rgb_rgb();//��ƽ�� 
             // else zgrb(saz); 
            }      

   else if((y>=z)&(z>=x))//������
            {

              if(max(y,z,x)=='a') rgb_rgb();//��ƽ��
              else if(max(y,z,x)=='n'){zgbr(may(y,z,x));}//��ƽ��  
              else if(max(y,z,x)=='b'){rb_rgb(maz(z,x));}//12ƽ��
              else if(max(y,z,x)=='c'){gb_rgb(maz(y,z));}//23ƽ�� 

             // if(max(y,z,x)==(saz='a')) rgb_rgb();//��ƽ��  
             // else zgbr(saz); 
             }      

   else if((z>=x)&(x>=y))//������
            { 
                if(max(z,x,y)=='a') rgb_rgb();//��ƽ��
                else if(max(z,x,y)=='n'){zbrg(may(z,x,y));}//��ƽ��  
                else if(max(z,x,y)=='b'){rg_rgb(maz(x,y));}//12ƽ��
                else if(max(z,x,y)=='c'){rb_rgb(maz(z,x));}//23ƽ�� 


             // if(max(z,x,y)==(saz='a')) rgb_rgb();//��ƽ�� 
             // else zbrg(saz);
            }       

   else if((z>=y)&(y>=x))//���̺�
            { 
              if(max(x,y,z)=='a') rgb_rgb();//��ƽ��
              else if(max(z,y,x)=='n'){zbgr(may(z,y,x));}//��ƽ��  
              else if(max(z,y,x)=='b'){rg_rgb(maz(y,x));}//12ƽ��
              else if(max(z,y,x)=='c'){gb_rgb(maz(z,y));}//23ƽ�� 



             //if(max(z,y,x)==(saz='a')) rgb_rgb(); //��ƽ�� 
             //else zbgr(saz);
             }

       
   else  rgb_rgb();

}



