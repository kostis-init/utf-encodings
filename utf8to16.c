#include <stdio.h>
int main(void)
{
      int code, c1, c2, c3, c4, temp1, temp2, temp3, temp4, b1, b2, a1, a2;
      while ((code=getchar())!=EOF)
      {
	    if (code>=0xC0)
	    {
		  if (code<=0xDF)
		  {
		    c1=code;
		    c2=getchar();
		    temp1=c1 & 0x1F;
		    temp2=c2 & 0x3F;
		    code=(temp1<<6) + temp2;
		  }
		  else if (code<=0xEF)
		  {
		    c1=code;
		    c2=getchar();
		    c3=getchar();
		    temp1=c1 & 0x0F;
		    temp2=c2 & 0x3F;
		    temp3=c3 & 0x3F;
		    code=(temp1<<12) + (temp2<<6) + temp3;
		  }
		  else if (code<=0xF7)
		  {
		    c1=code;
		    c2=getchar();
		    c3=getchar();
		    c4=getchar();
		    temp1=c1 & 0x07;
		    temp2=c2 & 0x3F;
		    temp3=c3 & 0x3F;
		    temp4=c4 & 0x3F;
		    code=(temp1<<18) + (temp2<<12) + (temp3<<6) + temp4;
		  }
	    }
	    else if (code>0x7F)
	    {
		  printf("\nΛΑΘΟΣ ΚΩΔΙΚΟΠΟΙΗΣΗ ΧΑΡΑΚΤΗΡΩΝ ΕΙΣΟΔΟΥ\n");
		  return 2;
	    }
	    
	    //decoding from utf-8 done
	    //encoding to utf-16 starts
	    
	    if (code<=0xFFFF)
	    {
		  c1=code>>8;
		  c2=code & 0xFF;
		  putchar(c1);
		  putchar(c2);
	    }
	    else if (code<=0x10FFFF)
	    {
		  code -= 0x10000;
		  b1=code>>10;
		  b2=code & 0x3FF;
		  a1=b1 + 0xD800;
		  a2=b2 + 0xDC00;
		  c1=a1>>8;
		  c2=a1 & 0xFF;
		  c3=a2>>8;
		  c4=a2 & 0xFF;
		  putchar(c1);
		  putchar(c2);
		  putchar(c3);
		  putchar(c4);
	    }
      }
      return 0;
}