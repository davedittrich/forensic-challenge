#include <stdio.h>
#include <string.h>
#include "salt.h"

#define PS_CR_EN 0
#define PS_CR_DE 1

unsigned char base[]="'`0123456789abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@$=&*-";
int baselen=67;

unsigned char xres[3];

unsigned char *hashdot(unsigned int r)
{
    unsigned int cnt;
    unsigned int hh=0;
    unsigned int hl=0;
    cnt=r;
    for(;cnt>0;cnt--)
    {
	hl++;
	if (hl==baselen) {hl=0;hh++;}
    }
    xres[0]=base[hh];
    xres[1]=base[hl];
    xres[2]=0;
    return xres;
}

unsigned int unhashdot(unsigned char *hash)
{
    unsigned int lf=baselen;
//    unsigned char *pt;
    unsigned int erg=0;
    unsigned long ln=0;
    while (ln!=baselen && base[ln] != hash[0]) {
	ln++;
    }
    if (ln!=baselen) {
	erg=ln * lf;
    }
    ln=0;
    while (ln!=baselen && base[ln] != hash[1]) {
	ln++;
    }
    if (ln!=baselen) {
	erg=erg+ln;
    }
    return erg;
}

char crybu[2000];

char *psycrypt(char *st,int de,int line)
{
    char *pte;
    char *ptt;
    char *pts1,*pts2;
    char *pt;
    char *hpt;
    int intrln;
    char hbuf[3];
    int res;
    int slen=0;
//    unsigned int zn;
    unsigned int tslt1 = CODE1;
    unsigned int tslt2 = CODE2;
    int p1,p2,p3,p4,p5;
    int erg;
    memset(crybu,0x0,sizeof(crybu));
    intrln=line;
    pt = crybu;
    pte = pt;
    ptt = st;
    pts1 = slt1 +SA1;
    pts2 = slt2 +SA2;
    while (intrln>0)
    {
	pts1++;
	if (*pts1==0) pts1=slt1;
	pts2++;
	if (*pts2==0) pts2=slt2;
	intrln--;
    }
    while(*ptt!=0)
    {
	if (slen>1990) break;
        if (tslt1>255 || tslt1 <0) tslt1=CODE1;
        if (tslt2>255 || tslt2 <0) tslt2=CODE2;
	if (*pts1==0) pts1=slt1;
	if (*pts2==0) pts2=slt2;
	res=0;
	if (de) {
	   hbuf[0]=*ptt++;
	   hbuf[1]=*ptt;
	   hbuf[2]=0;
	   p1=unhashdot(hbuf);              
	   p2=*pts1;p3=tslt1;p4=*pts2;p5=tslt2;
	   erg=p1-p2-p3+p4-p5;    
	   *pte=erg;
	   res=erg;
	} else {
	   p1=*ptt;p2=*pts1;p3=tslt1;p4=*pts2;p5=tslt2;
	   res=p1;
	   erg=p1+p2+p3-p4+p5;    
	   hpt=hashdot(erg);
	   *pte++=hpt[0];slen++;
	   *pte=hpt[1];
	}
	tslt1--;
	res=res/10;
	tslt2=tslt2+res;
	pte++;ptt++;pts1++;pts2++;slen=slen+1;
    } 
    *pte=0;
    return pt;
}

char *decryptline(char *todecipher, int line)
{
    return psycrypt(todecipher,PS_CR_DE,line);
}

int dcryptit(char *infile, char *outfile)
{
//  int letter;
  int alphabet;
  FILE *f, *fi;
  char *epr;
  char *pt;
  int line=0;
  char buf[1200];
//  int i;
  makesalt();
  if ( (f=fopen(infile,"r")) == NULL)
     return(-1);
  if ( (fi=fopen(outfile, "w")) == NULL)
     return(-1);
  alphabet = 24;
  while (fgets(buf, 1199, f)) {
	pt=strchr(buf,'\r');if (pt!=NULL) *pt=0;
	pt=strchr(buf,'\n');if (pt!=NULL) *pt=0;
	epr=decryptline(buf,line);
	pt=strchr(epr,'\r');if (pt!=NULL) *pt=0;
	pt=strchr(epr,'\n');if (pt!=NULL) *pt=0;
	strcat(epr,"\n");
	fputs(epr,fi);
	line++;
  }
  fclose(f);
  fclose(fi);
  return(-2);
}

int main(int argc, char *argv[])
{
   if (argc != 3) {
      printf("Usage: %s [infile] [outfile]\n", argv[0]);
      _exit(0);
   }
   dcryptit(argv[1], argv[2]);
   _exit(0);
   return(1);
}

