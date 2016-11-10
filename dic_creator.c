#include <stdio.h>
#include <string.h>



main()
{
 freopen("word_list.txt","r",stdin);
 freopen("dic_l.h","w",stdout);

 char s[26];
 
 printf("\n\n\nchar *dic[]={\n");
 
 while(!feof(stdin))
 {

 
  gets(s);
 
  if(strlen(s)>2 && !strpbrk(s,"-+_0123456789 .,;:!?"))
  printf("\"%s\",\n",strupr(s));
 
//  getch();
 }
 
 printf("\n}\n\n");
 
}
