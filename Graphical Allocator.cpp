#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define ll long long
struct point{
	int x1,y1;
	int x2,y2;
};

typedef struct v
{
	int  CPU, MEM;		//mem in mb atleast 100mb  clock is in mega Hz and atleast 100 mHz
}VM;

typedef struct s
{
	int ThreshCPU, ThreshMEM;
	int  serverID;
	double peakPower;
}Server;

typedef struct solution{
	int vm_allot[20];
}Sol;

int no_of_pm , no_of_vm ;
VM v_machines[20];
Server server[20];

struct point p_machines[20];
Sol sol[5];
void print_machinnes();
void initialize_v_machines();
void initialize_p_machines();
void print_V_machines(int );
void initialize_server();
void initialize_allot();

int main()
{
   	//int gd = DETECT, gm, no_of_sol;
	//initgraph(&gd, &gm, "C:\\TC\\BGI");
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	int i,j,no_of_sol;
	//clrscr();
	//fflush(stdin);
	FILE *fp;
	fp = fopen("DataFile.txt","r");

	fscanf(fp," %d",&no_of_vm);
	//printf("%d\n",no_of_vm);

	for(i=0;i<no_of_vm;i++)
	{
		int c,m;
		fscanf(fp," %d %d",&c,&m);
		//printf("%d %d \n",c,m);
	   	v_machines[i].CPU=c;
		v_machines[i].MEM=m;
		//printf("%d %d\n",v_machines[i].CPU,v_machines[i].MEM);
		v_machines[i].CPU=(v_machines[i].CPU*1000)/4;
		v_machines[i].MEM=(v_machines[i].MEM*1000)/2;
	}

	fscanf(fp," %d",&no_of_pm);
	//printf("%d\n",no_of_pm);
	for(i=0;i<no_of_pm;i++)
	{         
		int tc,tm;
		fscanf(fp," %d %d",&tc,&tm);
		//printf("%d %d \n",tc,tm);
		server[i].ThreshCPU=tc;
		server[i].ThreshMEM=tm;
		//printf("%d %d \n",server[i].ThreshCPU,server[i].ThreshMEM);
		server[i].ThreshCPU/=4;
		server[i].ThreshMEM/=2;
	}

	initialize_p_machines();
    int k;
	fscanf(fp," %d",&no_of_sol);
	//printf("%d\n",no_of_sol);
	
	for(i=0;i<no_of_sol;i++)
	{
		//initialize_allot();
	    for(k=0;k<no_of_vm;k++)
		{
			fscanf(fp," %d",&j);
			fscanf(fp," %d",&sol[i].vm_allot[j]);
			//printf("%d %d %d\n",i,j,sol[i].vm_allot[j]);
			//printf("%d, %d\n",j,vm_allot[j]);
		}
		//print_machinnes();
	    //print_V_machines();
	    //cleardevice();
	}
	
	
	for(i=0;i<no_of_sol;i++)
	{
		cleardevice();
		//initialize_allot();
		print_machinnes();
	    print_V_machines(i);
		getch();	    
	}
	fclose(fp);
	getch();
	closegraph();
	return 0;
}

void print_V_machines(int s)
{
	int i,j;
	for(i=0;i<no_of_pm;i++)
	{
		int a,b;
		a = p_machines[i].x1;
		b = p_machines[i].y2;
		for(j=0;j<no_of_vm;j++)
		{
			if( sol[s].vm_allot[j] == i )
			{
				int cpu , mem ,xtemp , ytemp;
				cpu = (v_machines[j].CPU*3)/100;
				mem = (v_machines[j].MEM*4)/100;
				xtemp = a + (p_machines[i].x2 - p_machines[i].x1 -cpu)/2 + cpu;
				ytemp = b;
				a = a+(p_machines[i].x2 - p_machines[i].x1-cpu)/2;
				b = b - mem;
				//printf("a=%d b=%d xtemp=%d ytemp=%d\n",a,b,xtemp,ytemp);
				rectangle(a,b,xtemp,ytemp);
				a = a - (p_machines[i].x2 - p_machines[i].x1-cpu)/2;
				char text[5];
				sprintf(text,"%02d",j+1);
				outtextxy(a,b+mem-10,text);
			}
		}
	}
}

void print_machinnes()
{
	int i;
	for(i=0;i<no_of_pm;i++)
	{
		//printf("x1=%d y1=%d x2=%d y2=%d\n",p_machines[i].x1,p_machines[i].y1,p_machines[i].x2,p_machines[i].y2);
		rectangle(p_machines[i].x1,p_machines[i].y1,p_machines[i].x2,p_machines[i].y2);
		char text[5];
		sprintf(text,"PM %d",i+1);
		outtextxy(p_machines[i].x1+5,p_machines[i].y2+20,text);
	}
}

void initialize_p_machines()
{
	int i,j;
	for(i=0,j=0;i<no_of_pm;i++,j+=100)
	{
		p_machines[i].x1=j+10;
		p_machines[i].y2=340;
		p_machines[i].y1=p_machines[i].y2 - server[i].ThreshMEM*40;
		p_machines[i].x2=p_machines[i].x1+30*server[i].ThreshCPU;
		//printf("%d %d %d %d\n",p_machines[i].x1,p_machines[i].y1,p_machines[i].x2,p_machines[i].y2);
	}
}

/*
void initialize_v_machines()
{
	for(i=0;i<no_of_vm;i++)
	{
		fscanf(fp," %d %d",&v_machines[i].CPU,&v_machines[i].MEM);
		printf("%d %d \n",v_machines[i].CPU,v_machines[i].MEM);
		v_machines[i].CPU*=100;
		v_machines[i].MEM*=100;
	}
}

void initialize_server()
{
	for(i=0;i<no_of_pm;i++)
	{
		fscanf(fp," %d %d",&server[i].ThreshCPU,&server[i].ThreshMEM);
		printf("%d %d \n",server[i].ThreshCPU,server[i].ThreshMEM);
		server[i].ThreshCPU*=2;
		server[i].ThreshMEM*=2;
	}
}

void initialize_allot()
{
	
	for(i=0;i<no_of_vm;i++)
	{
		fscanf(fp," %d",&j);
		fscanf(fp," %d",&vm_allot[j]);
		printf("%d, %d\n",j,vm_allot[j]);
	}
}*/
