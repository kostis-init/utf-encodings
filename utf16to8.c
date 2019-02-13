#include <stdio.h>
int main(void)
{
      int c1,c2,code,a1,c3,c4,a2,temp;
      while ((c1=getchar())!=EOF)
      {
	    c2=getchar();
	    c1 <<= 8;
	    code =c1 + c2;
	    if (code>=0xD800 && code<=0xDBFF) //surrogate pairs
	    {
		  a1=code;
		  c3=getchar();
		  c4=getchar();
		  c3 <<= 8;
		  a2=c3 + c4;
		  if (a2 < 0xDC00 || a2 > 0xDFFF)
		  {
			printf("\nWRONG ENCODING OF INPUT CHARACTERS\n");
			return 2;
		  }
		  a1 &= 0x3FF; //10 right bits of a1
		  a2 &= 0x3FF; //10 right bits of a2
		  a1 <<= 10;
		  code = a1 | a2;
		  code += 0x10000;
	    }
	    else if (code >= 0xDC00 && code <= 0xDFFF)
	    {
		  printf("\nWRONG ENCODING OF INPUT CHARACTERS\n");
		  return 2;
	    }
	    
	    //decoding from utf-16 done
	    //encoding to utf-8 starts
	    
	    if (code <=  0x007F)
		  putchar(code);
	    else if (code <= 0x07FF)
	    {
		  temp = code >> 6;
		  c1 = temp | 0xC0; // c1: 110xxxxx
		  temp = code & 0x3F; 
		  c2 = temp | 0x80; // c2: 10xxxxxx
		  putchar(c1);
		  putchar(c2);
	    }
	    else if (code <= 0xFFFF)
	    {
		  temp = code >> 12;
		  c1 = temp | 0xE0; // c1: 1110xxxx
		  temp = code >> 6;
		  temp &= 0x3F;
		  c2 = temp | 0x80; // c2: 10xxxxxx
		  temp = code & 0x3F;
		  c3 = temp | 0x80; // c3: 10xxxxxx
		  putchar(c1);
		  putchar(c2);
		  putchar(c3);
	    }
	    else
	    {
		  temp = code >> 18;
		  c1 = temp | 0xF0; // c1: 11110xxx
		  temp = code >> 12;
		  temp &= 0x3F;
		  c2 = temp | 0x80; // c2: 10xxxxxx
		  temp = code >> 6;
		  temp &= 0x3F;
		  c3 = temp | 0x80; // c3: 10xxxxxx
		  temp = code & 0x3F;
		  c4 = temp | 0x80; // c4: 10xxxxxx
		  putchar(c1);
		  putchar(c2);
		  putchar(c3);
		  putchar(c4);
	    }
      }
      return 0;
}
