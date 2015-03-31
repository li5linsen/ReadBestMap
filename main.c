//aling function:  align the read short to the genomes like the BWA progress
#include "head.h"

//#define DEBUG
void getParameter(int Num,char *Para[]);
void mainUsage(void);
//public var
//static int Test=0;
//static int VL=1000, N=10, K=8, ref_num=1, P=1;  //Parameter & its initialization
//static double  E=0.05;


int  *base_num=NULL, *KeyofPosiCount=NULL, file_count=0; 
char *title=NULL,    *genBaseBuf=NULL,   IndexPreKey[16]={0};  
int  HashStrlen=8,  IndexPosiCount=0,  BaseCount=0, *IndexPosition=NULL; //Index information
/*
typedef struct IndexDataType
{
	char IndexPreKey[16];
	int  HashStrlen;
	int  IndexPosiCount;  //tatle Indexposition
	int  BaseCount;       //tatle base
	int *IndexP;
	//int *KeyofPosiCount[]; //position count of each keyword 4^10=1048576(1M)  or 4^8=65536(64K)
}InfoType;
InfoType IndexInfo={"CG", 8, 0, 0, NULL };
*/
int main(int argc,char *argv[]) 
{	
	int i,j, next=0, str_len=0,  Readmode=1;
	int	d=0,  f=0; //d, f is parameters for map function
	char genFileDir[256]={0}, readFileDir[256]={0}, outFile[256]={0},INDEXKEY[10]={0}; //index num <= 10;
	char *testargv[3]={"cmp", "srcFile", "readFile" };
	
	//for(j=0; j<10; j++)  //init the INDEXKEY
	//	INDEXKEY[j]=(char *)calloc(256,sizeof(char));
	

#ifdef DEBUG //if debug had defined
	//genomeRead("db.fa", BaseBuffer);
	//ind=getIndex(BaseBuffer, "CG");
	genBaseBuf=genProcess("NC_017634.1.fasta",genBaseBuf,"CG"); //15829254.fasta  NC_000913.3.fasta  NC 001136.10
	// OutputIndex(ind);  //ind is a struct
	map("SRR1063349.fastq", genBaseBuf,"result.txt",testargv); //map read to db, output the result to read.sam  ERR231645.fastq

#else
	//getParameter( argc,argv );
	if(argc<3) { printf("wrong parameter!\n");  mainUsage(); return -1;}
	strcpy(genFileDir,argv[1]);
	strcpy(readFileDir,argv[2]);

	strcpy(outFile,argv[2]);
	strcat(outFile,".map.txt");
	strcpy(INDEXKEY,"CG"); 
	//genomeRead(genFileDir,BaseBuffer);  //genRead and getIndex should in the same time
       if( (genBaseBuf=genProcess(genFileDir,genBaseBuf,INDEXKEY))==NULL)
         return -1;
	map(readFileDir,genBaseBuf,outFile, argv);
	//if(mode>0) // cmd index
	//{
	//	//getIndex(BaseBuffer,INDEXKEY);
	//	genProcess(genFileDir,genBaseBuf,INDEXKEY);
	//	OutputIndex(ind);
	//}
	//else if(mode<0) //cmd map
	//{
	//	ind=indexRead(indFileDir,ind);
	//	map(readFileDir,BaseBuffer,ind);
	//}
	//else //mode==0 one step finish all
	//{
	//	ind=getIndex(BaseBuffer,INDEXKEY);
	//	map(readFileDir,BaseBuffer,ind);
	//}
#endif
	
	
	   
#ifdef DEBUG //if debug had defined-- temp output 

	
//#elif


#endif
	return 0;
}

void mainUsage(void)
{
	/*printf("align Usage:\n");
	printf("  cmd <db.fa> <read1.fq, read2.fq ...>\n");
	printf("  Output read1.sam, read2.sam ...\n");
	printf("  Eg. cmd db.fa read.fq\n");
	printf("  This command can be consisted of two command: index & map\n");

	printf("index Usage:\n");
	printf("  cmd index <db.fa> \n ");
	printf("  Output db.ind file\n");

	printf("map Usage:\n");
	printf("  cmd map <db.fa> <read.fq>\n");
	printf("  db.ind should store in the same directory with the db.fa file.\n");*/
	printf("MapRead Usage:\n");
	printf("  cmd <db.fa> <read.fq>\n");
	printf("\n  get help by 'cmd -h'\n");
	
}

void getParameter(int Num,char *Para[])
{
	////main Parameter
	//int i,j;
 //   if(argc<2)
	//{	mainUsage(); return -1; }
	//
	//
	//if( stringcmp(argv[1], "comp" )==0 )
	//{
	//	if(argc<4)
	//	{  compUsage(); return -1;  }
	//	else
	//		strcpy(dir,argv[2]);
	//	
	//	for(j=0; j<10; j++)  //init the INDEXKEY
	//		INDEXKEY[j]=(chp)calloc(256,sizeof(char));
	//	strcpy(INDEXKEY[0],"CG");  P=1;
	//	
	//	i=3;
	//	while(*argv[i]=='-')  //option: -L -e -N -k -P -R  -h
	//	{
	//		switch ( *(argv[i]+1) )
	//		{
	//			case 'L':
	//		case 'l': i++; VL=atoi(argv[i]);  if(!VL) { printf("error parameter L!\n"); return -1; }
	//				break;  //display the message
	//			case 'E':
	//			case 'e': i++;  E =atof(argv[i]);  break;
	//			case 'N':
	//			case 'n': i++;  N =atoi(argv[i]);  break;
	//			case 'K':
	//			case 'k': i++;  K =atoi(argv[i]);  break;
	//			case 'P':
	//			case 'T':
	//			case 't':		 Test=1; break;
	//			case 'p': i++;  P =0; next=1;
	//				while( next )
	//				{
	//					next=0;
	//					for(j=0; (ch=*(argv[i]+j))!='\0'; j++)
	//					{
	//						if(ch==','){  ch='\0'; next=1;  }
	//						*(INDEXKEY[P]+j)=Caps(ch);
	//					}
	//					*(INDEXKEY[P]+j)='\0';
	//					
	//					i++;  P++; printf("%s\n",argv[i]);
	//				}   i--;
	//				break;
	//			case 'R':
	//			case 'r': i++; //printf("input R:%s\n",argv[i]); 
	//				Readmode=atoi(argv[i]); 
	//				if(Readmode==2)
	//				{   //init set_ref
	//					i++; ref_num=0;
	//					set_ref=(chp *)malloc(100*sizeof(chp));
	//					if(!set_ref) { printf("err building set_ref\n"); return -1;}
	//					for(j=0; j<100; j++)
	//						*(set_ref+j)=(chp)malloc(256*sizeof(char));
	//					
	//					if(*argv[i]=='@')  //listfile
	//					{
	//						listFile=fopen(argv[i]+1,"r");
	//						if(!listFile) { printf("err open listfile!\n"); return -1; }
	//						while(	fgets( *(set_ref+ref_num), 256, listFile ) !=NULL )
	//						{
	//							for(j=strlen(*(set_ref+ref_num))-1; j>=0; j--)
	//								if( *(*(set_ref+ref_num)+j)<27) 
	//									*(*(set_ref+ref_num)+j)='\0';
	//								else break;
	//							ref_num++;
	//							if(ref_num%100==0)
	//							{
	//								set_ref=(chp*)realloc( set_ref, (ref_num+100)*sizeof(chp) );
	//								for(j=ref_num; j<ref_num+100; j++)
	//									*(set_ref+j)=(chp)malloc(256*sizeof(char));
	//							}
	//						}
	//					}
	//					else  //input file direct
	//					{   next=1;
	//						while(next)
	//						{	//printf("ref %d is: %s\n",ref_num,argv[i]);  //test							
	//							strcpy( *(set_ref+ref_num),argv[i] );
	//							next=0;
	//							str_len=strlen(*(set_ref+ref_num));
	//							if( *(*(set_ref+ref_num)+str_len-1)==',' )
	//							{ 
	//								next=1;
	//								*(*(set_ref+ref_num)+str_len-1)='\0';
	//							}
	//							ref_num++; i++; 
	//							if(ref_num%100==0)
	//							{
	//								set_ref=(chp*)realloc( set_ref, (ref_num+100)*sizeof(chp) );
	//								for(j=ref_num; j<ref_num+100; j++)
	//									*(set_ref+j)=(chp)malloc(256*sizeof(char));
	//							}
	//						}
	//					}
	//					i--;
	//				}
	//				//if there is no INT, Readmode ==0
	//				
	//				break;

	//			case 'H':
	//			case 'h': compUsage(); return -1; break;
	//			
	//			default : compUsage(); return -1;
	//		}
	//		i++;
	//	}
	//	strcpy(chara, argv[i]);
	//	//strcpy(chara, argv[argc-1]);
	//	comp(dir, chara, Readmode);
	//}
	//else if( stringcmp(argv[1], "map" )==0 )
	//{
	//	if(argc<4)
	//	{ mapUsage(); return -1; }
	//	i=2;				
	//	while(*argv[i]=='-')  //option: -d  -f  -h
	//	{
	//		switch ( *(argv[i]+1) )
	//		{
	//			case 'D':
	//			case 'd': d=1;  break;  //display the message
	//			case 'F':
	//			case 'f': f=1;  break;
	//			
	//			case 'H':
	//			case 'h': mapUsage(); return -1;
	//			
	//			default : mapUsage(); return -1;
	//		}
	//		i++;
	//	}
	//	strcpy(aln, argv[i]); i++;
	//	strcpy(chara, argv[i]);
	//	map(aln, chara, d, f);
	//}
	//else {  mainUsage(); return -1; }		
}

