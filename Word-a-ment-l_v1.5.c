#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "dic_l.h"


#define n 4
#define mn 3
#define mx 11

#define v 210

//int x=64,y=166,w=100,h=100;

int x=136,y=239,w=50,h=50;

// x,y = 136,239  & w=50, h=50





go(int mov[][2],int p)
{
// return ;
	register int x1=x+**mov*w ,y1=y+*(*mov+1)*h;
	int k;

// SetCursorPos(x,y);
//   x1+=**mov*w ;  y1+= *(*mov+1)*h;

	SetCursorPos(x1,y1);
	mov++;
	mouse_event( MOUSEEVENTF_LEFTDOWN,0,0,0,0 );

	while(1-p--)
	{
		x1+=**mov*w ;
		y1+= *(*mov+1)*h;
		SetCursorPos(x1,y1);
		for(k=(unsigned)-1/v; k--;);
//  getch();
		mov++;
	}
	mouse_event( MOUSEEVENTF_LEFTUP,0,0,0,0 );

}







char *alr[350];
int a1=0 ;


int lSer(char *key)
{
	register int i;
	for(i=0; i<a1; i++)
		if(!strcmp(alr[i],key))
		{
			/*printf("Already exists: %s\n",key);*/ return 1;
		}
	return 0;
}






char **Ser(char *key)
{
	register char **l,**m,**h;

	l=dic;
	h=dic+d-1;

// printf("\n%lld, %llu\n",d,h-l); getch();

	while(l<=h)
	{
		m=l+(h-l)/2  ;
		if(!strcmp(key,*m))
		{
			return m;
		}
		if(strcmp(key,*m)<0) h=m-1;
		else l=m+1			   ;
	}
	return NULL;
}











form(char *s[],int p,int mov[][2])
{
	register int m,i,l,k;
	char o[n*n]= {0},o1[n*n]= {0},o2[n*n]= {0};
	if(p>mx)
	{
		return 0;
	}



	if(p>1)
	{
		for(i=0; i<p; i++)l=sprintf(o,"%s%s",o,s[i]);



		if(l>=mn && !lSer(o) && Ser(o) )
		{
			printf("found:-%*s\n",mx,o);
			alr[a1++]=strdup(o);
			go(mov,p); /*getch(); */
		}


		/*
		  if(strstr("ERENESLY",o+strlen(o)-2) ||
		     (o[strlen(o)-1]=='S' && !strchr("OAYXVJQ",o[strlen(o)-2])))
		  {

		   sprintf(o1,o);
		   for(k=100000;k--;);
		   o[strlen(o)-1]=0 ;
		    if(!lSer(o1) && Ser(o) )
		   { printf("found:-%*s\n",mx,o1); alr[a1++]=strdup(o1);
		   go(mov,p); /*getch(); }

		   o[strlen(o)-1]=0 ;
		    if(!lSer(o1) && Ser(o) )
		   { printf("found:-%*s\n",mx,o1); alr[a1++]=strdup(o1);
		   go(mov,p); /*getch(); }

		 }

		*/
	}




	for(m=0; m<9; m++)
	{
		s[p]=(s[p-1]+ (4*(n+2)*(mov[p][1]=(m/3-1))) + 4*(mov[p][0]=(m%3-1))) ;

		if(!*s[p])
		{
			/*puts("Can_NULL");*/ continue;
		}
		for(i=0; i<p; i++) if(s[i]==s[p]) break;
		if(s[i]==s[p] && i<p)
		{
			/*puts("Can_Already exists");*/ continue;
		}

// mov[p][0]=(m%3-1);   mov[p][1]=(m/3-1);

		form(s,p+1,mov);
	}
}







main()
{
	int i=0,j,k;
	char *s[(n*n)];
	int mov[n*n][2];

	/* char w1[n][n]={"ABLY","OIAH","NDZT","TEEN"}; */
	char wrd[n+2][n+2][4]= {0};
	/*void *p=wrd;*/

	printf("x,y = %d,%d  & w=%d, h=%d\n",x,y,w,h);


	printf("Enter the characters serially: \n");

	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
		{
			scanf("%3s",wrd[i][j]);
			strupr(wrd[i][j]);
		}



	outMat(wrd,n+2,n+2);

	printf("Press C to calibrate or any other key to cancel.\n");
	if(toupper(getch())=='C')calibrate();




	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
		{
			s[0]=wrd[i][j];
			mov[0][0]=j-1;
			mov[0][1]=i-1;
			form(s,1,mov);
			for(k=0; k<(n*n); k++)s[i]=NULL;

			/*
			   SetCursorPos(768,300);
			  mouse_event( MOUSEEVENTF_LEFTDOWN,0,0,0,0 );
			  mouse_event( MOUSEEVENTF_LEFTUP,0,0,0,0 );
			  getch();*/
		}



	rewind(stdin);

	printf("Found %d words\n",a1);
	while(a1--)
	{
		/* puts(alr[a1]);*/ free(alr[a1]);
	}
	main();

}





calibrate()
{
	char c	;
	POINT lu,rd ;

	printf("Press I,J,K,L to move cursor up,left,down,right and x to finish.\n");

	while((c=toupper(getch())) != 'X')
	{
		switch(c)
		{
			case 'Q':
				GetCursorPos(&lu);
				printf("lu = %d,%d\n",lu.x,lu.y);
				break;

			case 'S':
				GetCursorPos(&rd);
				printf("rd = %d,%d\n",rd.x,rd.y);
				break;

			case 'I':
				mouse_event(1, 0,-1,0,0 );
				break;
			case 'K':
				mouse_event(1, 0, 1,0,0 );
				break;
			case 'J':
				mouse_event(1,-1,0 ,0,0 );
				break;
			case 'L':
				mouse_event(1, 1,0 ,0,0 );
				break;
		}
	}

	w=(rd.x-lu.x)/n ;
	h=(rd.y-lu.y)/n ;
	x=lu.x+(w/2);
	y=lu.y+(h/2) ;
	printf("x,y = %d,%d  & w=%d, h=%d\n",x,y,w,h);
}








outMat(void *A,int x,int y)
{
	int i,j    	;
	printf("\n")	;
	for(i=0; i<x; i++)
	{
		for(j=0; j<y; j++) printf("%-3s|",((char (*)[y][4])A)[i][j]);
		printf("\n")	;
	}
	printf("\n")	;
}


