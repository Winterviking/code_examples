
 





 
 
 
 
 
 



typedef void * va_list;
 




 


void init_printf(void* putp,void (*putf) (void*,char));

void tfp_printf(char *fmt, ...);
void tfp_sprintf(char* s,char *fmt, ...);

void tfp_format(void* putp,void (*putf) (void*,char),char *fmt, va_list va);










typedef void (*putcf) (void*,char);
static putcf stdout_putf;
static void* stdout_putp;




static void ui2a(unsigned int num, unsigned int base, int uc,char * bf)
 {
 int n=0;
 unsigned int d=1;
 while (num/d >= base)
 d*=base;
 while (d!=0) {
 int dgt = num / d;
 num%= d;
 d/=base;
 if (n || dgt>0 || d==0) {
 *bf++ = dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10);
 ++n;
 }
 }
 *bf=0;
 }

static void i2a (int num, char * bf)
 {
 if (num<0) {
 num=-num;
 *bf++ = '-';
 }
 ui2a(num,10,0,bf);
 }

static int a2d(char ch)
 {
 if (ch>='0' && ch<='9')
 return ch-'0';
 else if (ch>='a' && ch<='f')
 return ch-'a'+10;
 else if (ch>='A' && ch<='F')
 return ch-'A'+10;
 else return -1;
 }

static char a2i(char ch, char** src,int base,int* nump)
 {
 char* p= *src;
 int num=0;
 int digit;
 while ((digit=a2d(ch))>=0) {
 if (digit>base) break;
 num=num*base+digit;
 ch=*p++;
 }
 *src=p;
 *nump=num;
 return ch;
 }

static void putchw(void* putp,putcf putf,int n, char z, char* bf)
 {
 char fc=z? '0' : ' ';
 char ch;
 char* p=bf;
 while (*p++ && n > 0)
 n--;
 while (n-- > 0)
 putf(putp,fc);
 while ((ch= *bf++))
 putf(putp,ch);
 }

void tfp_format(void* putp,putcf putf,char *fmt, va_list va)
 {
 char bf[12];

 char ch;


 while ((ch=*(fmt++))) {
 if (ch!='%')
 putf(putp,ch);
 else {
 char lz=0;

 int w=0;
 ch=*(fmt++);
 if (ch=='0') {
 ch=*(fmt++);
 lz=1;
 }
 if (ch>='0' && ch<='9') {
 ch=a2i(ch,&fmt,10,&w);
 }

 switch (ch) {
 case 0:
 goto abort;
 case 'u' : {

 ui2a((*(unsigned int *)(((*(char **)&(va))+=((sizeof(unsigned int)+1) & 0xFFFE))-(((sizeof(unsigned int)+1) & 0xFFFE)))),10,0,bf);
 putchw(putp,putf,w,lz,bf);
 break;
 }
 case 'd' : {

 i2a((*(int *)(((*(char **)&(va))+=((sizeof(int)+1) & 0xFFFE))-(((sizeof(int)+1) & 0xFFFE)))),bf);
 putchw(putp,putf,w,lz,bf);
 break;
 }
 case 'x': case 'X' :

 ui2a((*(unsigned int *)(((*(char **)&(va))+=((sizeof(unsigned int)+1) & 0xFFFE))-(((sizeof(unsigned int)+1) & 0xFFFE)))),16,(ch=='X'),bf);
 putchw(putp,putf,w,lz,bf);
 break;
 case 'c' :
 putf(putp,(char)((*(int *)(((*(char **)&(va))+=((sizeof(int)+1) & 0xFFFE))-(((sizeof(int)+1) & 0xFFFE))))));
 break;
 case 's' :
 putchw(putp,putf,w,0,(*(char* *)(((*(char **)&(va))+=((sizeof(char*)+1) & 0xFFFE))-(((sizeof(char*)+1) & 0xFFFE)))));
 break;
 case '%' :
 putf(putp,ch);
 default:
 break;
 }
 }
 }
 abort:;
 }


void init_printf(void* putp,void (*putf) (void*,char))
 {
 stdout_putf=putf;
 stdout_putp=putp;
 }

void tfp_printf(char *fmt, ...)
 {
 va_list va;
 (((va) = (va_list)((char *)(&fmt)+ ((sizeof(fmt)+1) & 0xFFFE))));
 tfp_format(stdout_putp,stdout_putf,fmt,va);
;
 }

static void putcp(void* p,char c)
 {
 *(*((char**)p))++ = c;
 }



void tfp_sprintf(char* s,char *fmt, ...)
 {
 va_list va;
 (((va) = (va_list)((char *)(&fmt)+ ((sizeof(fmt)+1) & 0xFFFE))));
 tfp_format(&s,putcp,fmt,va);
 putcp(&s,0);
;
 }





















