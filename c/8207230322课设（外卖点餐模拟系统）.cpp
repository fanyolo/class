#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<windows.h>
#include<time.h>
#include<conio.h>
//�û��Ľṹ��  
typedef struct user     //����ڵ����� typedef������Ϊ�������ʹ���һ���µ�����user=struct user�����ں�������������
{
	char name[50];
	char delivery[50];
	char password[20];
	char number[15];
	int score;           //���
	struct user *next;    //ָ���� ��������
}user,*link_user;
//�˻��ṹ��
typedef struct money
{
	char person[50];
	char card[25];
	char mima[20];
	struct money *next;
}money,*link_money;
//�����Ľṹ�� 
typedef struct food
{
	char name[50];
	int type;              //������
	int amount;            //����
	int price;             //����
	int total;
	char shop[40];
	char yonghu[40];
	char leibie[40];       //���
	struct food *next; 
}food,*link_food;
//�̼ҵĽṹ��   
typedef struct shop   //����ڵ�����
{
	char name[40];
	char phone[20]; 
	char address[50];
	char password[50];
    char pingjia[100];
	struct shop *next;       //ָ����
}shop,*link_shop;  //shop��ʾ�������ͣ�link_shop��ʾָ��shop������͵�ָ������
//��������
void foodwrite(link_food LF);         //��Ӳ�Ʒ
void shopwrite1(link_shop LS);      //���̼������Ϣwrite 
void dingdanwrite(link_food LF);     //�Զ�������write
void user_(link_user LM);
//���溯�� ���������
void welcome()
{   system("color 90");
	int i=0;
	char a[52]="��ӭ�������Աϵͳ";
	printf("\n\n\n\n\t\t");
	while(a[i])
	{
		printf("%c",a[i]);
		Sleep(50);   //��ʱ ���ֻ���ʽ������� windows.h
		i++;
	}
	printf("\n\n\n\n\t\t");
}
void Exit()  //�˳�
{
	int i=0;
	system("cls");
	char a[52]="���˳��������ģ��ϵͳ����ӭ�����´ι���";
	system("color 90");
	printf("\n\n\n\t\t\t");
	while(a[i])
	{
		printf("%c",a[i]);
		Sleep(100);   //��ʱ ���ֻ���ʽ�������
		i++;
	}
}
//��¼ע��˵�
void jiemian_zhuce()
{
	system("color 90");
	printf("\n\n\n\t\t                 \n\n\t��ӭ�����������ģ��ϵͳ����ѡ��������Ĳ�������");
	printf("\n\n\t\t\t1.ע��");
	printf("\t\t\t2.��½\t\t\t0.�˳�\n"); 
}
//���˵� ��¼����	
void jiemian_deng()
{
	printf("\n\n\t\t\t\t\t     �� �� �� �� �� ¼ ϵ ͳ     \n\n");
	printf("\t\t\t\t\t          1.����Ա��½          \n");
	printf("\t\t\t\t\t          2.�û���¼            \n");
	printf("\t\t\t\t\t          3.��ҵ�½            \n");
	printf("\t\t\t\t\t          0.����ע��         \n");
	printf("\t\t\t\t\t--------------------------------\n");
}
//����Ա����
void jiemian_guan()
{
	system("color 90");
	printf("                                                                                      ��ʾ����5����\n");
	printf("\n\n\n\t\t\t\t\t _______��ӭ�������Աϵͳ _____\n\n");
	printf("\n\n\t\t\t\t\t1.�鿴������Ϣ��\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t2.������Ϣ�޸Ĩ�\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t3.����������̨�\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t4.�鿴������Ϣ��\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t0.���ص�¼ϵͳ��\n");
}
//�û�����
void jiemian_yong()
{
	system("color 90");
	printf("\n\n\n\t\t\t\t\t _______��ӭ�����û�ϵͳ _____\n\n");
	printf("\n\n\t\t\t\t 1.�û���� ��\t\t\t 5.�����Ʒ ��\n"); 
	printf("\t\t\t\t---------------\t\t\t---------------\n");
	printf("\t\t\t\t 2.�鿴���� ��\t\t\t 6.�������� ��\n");
	printf("\t\t\t\t---------------\t\t\t---------------\n");
	printf("\t\t\t\t 3.�鿴��Ʒ ��\t\t\t 7.�̼����� ��\n");
	printf("\t\t\t\t---------------\t\t\t---------------\n");
	printf("\t\t\t\t 4.�޸Ķ��� ��\t\t\t 0.���ص�¼ ��\n");
}
//�̼ҽ���
void jiemian_shang()
{
	system("color 90");
	printf("\n\n\n\t\t\t _______��ӭ�����̼�ϵͳ _____\n\n");
	printf("\t\t\t\t1.��Ӳ�Ʒ\n");
	printf("\t\t\t\t2.�޸Ĳ�Ʒ\n");
	printf("\t\t\t\t3.ɾ����Ʒ\n");
	printf("\t\t\t\t4.�鿴��Ʒ\n");
	printf("\t\t\t\t5.�鿴ҵ��\n");
	printf("\t\t\t\t6.�鿴����\n");
	printf("\t\t\t\t7.����״̬\n");
	printf("\t\t\t\t0.���ص�¼\n");
	printf("\t\t\t------------------------------\n");
}char yh[20];char dp[20];
//�������ڵ�����LF ���ú���foodwrite
void *creatf()
{
	int i=0,n;
	link_food LF;          //link_food��ʾָ��food������͵�ָ������
	food *s,*r;             //s �� r ���� food* ���͵�ָ�룬����������Ʒ����ڵ�
	char a[10];
	LF=(food *)malloc(sizeof(food));  //ʹ�� malloc �������ڴ�ռ䣬��СΪ food �ṹ��Ĵ�С���������ص�ָ��ǿ������ת��Ϊ food* ����
	LF->next=NULL;    //�����ͷ�ڵ㣬���ҵ�ǰ����Ϊ��
	r=LF;             //r Ҳָ���������ͷ�ڵ㣬������������ı���
	while(1)
	{
		printf("������˵����ƣ�");
		scanf("%s",a);
		if(strcmp(a,"0")!=0) //�Ƚ��ַ�����С
		{
			s=(food *)malloc(sizeof(food));
			printf("������˵ĵ��ۣ�");
			scanf("%d",&s->price);
			printf("������˵����");
			scanf("%s",s->leibie); 
			strcpy(s->name,a);
			printf("����0ȷ���Ƿ񱣴�\n");
			s->total=(s->amount)*(s->price);
			r->next=s;           //��ǰ����β���ڵ�r��nextָ��ָ���´����Ľڵ�s ��s���뵽�����У���Ϊ����������һ���ڵ�
			s->next=NULL;        //�ڽ�s���뵽����ĩβ�� ��s��nextָ����ΪNULL s�������е����һ���ڵ�
			r=s;                 //���½ڵ�s��ӵ�����β�� ����rָ���µ�����β�ڵ�
		} 
		else
			break;
	}
	foodwrite(LF);  //��Ӳ�Ʒ �������õĲ�Ʒ���� LF ���浽�ļ�
} 
shop *creats()    //����̼�
{
	char a[30],b[20],c[15],d[20];
	link_shop LS;
	shop *s,*r;
	LS=r=(shop *)malloc(sizeof(shop));
	LS->next=NULL;
	r=LS;
	while(1)
	{
		printf("�����������Ϣ:\n");
		printf("\t\t��    �������ƣ�");
		scanf("%s",a);
		printf("\n\t\t��    ���̵绰��");
		scanf("%s",b);
		if(strcmp(b,"0")!=0)
		{
			printf("\n\t\t��    ���̵�ַ��");  
			scanf("%s",c);
			printf("\n\t\t��    �������룺");  
			scanf("%s",d);
			s=(shop *)malloc(sizeof(shop));
			strcpy(s->name,a);
			strcpy(s->phone,b);
			strcpy(s->address,c);
			strcpy(s->password,d);
			r->next=s;
			s->next=NULL;
			r=s;
		}
		else
			break;
	}
	return LS; 
}
void Outputshop(link_shop Ls) //����̼ң�����Ա�鿴�̼�
{
	int n=0;
	shop *p,*u;
	p=Ls->next;
	system("cls");
	printf("��פ���̼����£�\n");
	printf("\t\t\t\t-------------------------------------------\n");
	printf("\t\t\t\t��������\t���̵绰\t���̵�ַ\n");
	printf("\t\t\t\t-------------------------------------------\n");
	while(p)
	{
		printf("\t\t\t\t%8s\t%8s\t%7s\n",p->name,p->phone,p->address);
		printf("\t\t\t\t-------------------------------------------\n");
		p=p->next;
	}
	for(u =Ls->next; u != NULL;u = u->next)  
        n++;                                                         //�����̼�����
    printf("\t\t\t\t�ϼ�\t\t\t\t%d��\n",n);
    printf("\t\t\t\t-------------------------------------------\n");
}
void Outputfood(link_food LF)  //�������       
{
	food *s;
	s=LF->next;
	int sum=0;
	printf("�������£�\n");
	printf("\t----------------------------------------------------------------------------------------------------\n");
	printf("\t����\t\t����/��\t\t����/Ԫ\t\t�ܼ�/Ԫ\t\t�̼�\t\t������\t\t�û���\n"); 
	printf("\t----------------------------------------------------------------------------------------------------\n");
	for(s=LF->next;s!=NULL;s=s->next)
	{
		if(strcmp(s->yonghu,yh)==0)
		{
			printf("\t%-8s\t%-8d\t%-8d\t%-8d\t%-10s\t%-10d\t%s\n",s->name,s->amount,s->price,s->total,s->shop,s->type,s->yonghu);
			printf("\t----------------------------------------------------------------------------------------------------\n");
			sum=sum+s->total;
		}
	}
	printf("\t�ۼ����/Ԫ\t\t\t\t\t\t\t%d\n",sum);
	printf("\t----------------------------------------------------------------------------------------------------\n");
	if(sum==0)
	{  
		printf("����δ�����κβ�Ʒ����û�в�����������ȥ�˵�ѡ���� ");
		Sleep(1000);
		system("cls");
		jiemian_yong();
		return;
	}
}
void outputfood(link_food LF)   //����˵�
{
	food *p;
	p=LF->next;
	printf("\n\t\t\t                 ��       ��                        "); 
	printf("\n\t\t\t==================================================\n");
	printf("\t\t\t����        �˼�         �̼�           ��ϵ\n"); 
	printf("\t\t\t---------------------------------------------------\n");
	while(p)
	{
		printf("\t\t\t%-13s%-12d%-14s%s\n",p->name,p->price,p->shop,p->leibie);   //��������
		printf("\t\t\t===================================================\n");
		p=p->next;
	}
}
user* addmoney(user *u)//��ֵ        ����һ��user*���͵�ָ��u��Ϊ���� ����һ��user*���͵�ָ��
{
	int n;
	char y;
	char a[20];
	FILE *fp;   //FILE *fp;������һ��ָ�� FILE ���ͽṹ���ָ����� fp�����ڲ����ļ�
	link_money LY;
	money *p,*r;
	printf("���˻�������Ϊ��%d",u->score);
	printf("��ѡ���Ƿ��ֵ��Y/else");
	fflush(stdin);//������� 
	y=getchar();
	if(y=='Y')
	{
		fp=fopen("�˻�.txt","rt");
		LY=r=(money *)malloc(sizeof(money));//������һ�� money �ṹ����ڴ棬�����丳ֵ�� LY �� r
		LY->next=NULL;
		while(!feof(fp))
		{
			p=(money *)malloc(sizeof(money));
			fscanf(fp,"%s %s %s\n",p->person,p->card,p->mima);//���ļ��ж�ȡ�˻���Ϣ���������˻���Ϣ��������һ��������
			p->next=NULL;
			r->next=p;
			r=p; 
		}		
		fclose(fp);
		p=LY->next;
		while(1)
		{
			if(strcmp(yh,p->person)==0)
			{
				break;
			}
			else
				p=p->next; 
		}
		printf("��ֵ��Ǯ����");
		scanf("%d",&n);
		printf("������֧�����룺");
		scanf("%s",a);
		if(strcmp(p->mima,a)==0)
		{
			u->score=(u->score+n); 
			printf("�ѳ�ֵ");
		} 
		else
			printf("\t\t��   ������󣬳�ֵʧ��");
	}
	else
		printf("�ѷ�����ֵ");
	return u; //������Ϣ
}					
void dingdan_name_sort(link_food LF)  //��������1 ������ʳ���������� 
{  
    int i,j,n;  
    n = 0;  //��¼����������
    food *u,*q,*p;
    for(u =LF->next; u != NULL;u = u->next)  
        n++;  
//����ð�ݷ��Ը����ڵ㰴��������
    for(i=1;i<=n;i++)  
    {  
        u =LF;  
        for(j=0;j<n-i;j++)  
        {  
            p = u->next;  
            q = p->next;  
            if(strcmp(p->name,q->name) > 0 || strcmp(p->name,q->name) == 0)  
            {  
                u->next = q;  
                p->next = q->next;  
                q->next = p;  
            }  
            u = u->next;  
        }  
    } 
	Outputfood(LF);
	return;
}
void dingdan_total_sort(link_food LF)  //��������2 �������ܼ����� 
{  
    int i,j,n;  
    n = 0;  //��¼����������
    food *u,*q,*p;
    for(u =LF->next; u != NULL;u = u->next)  
        n++;  
//����ð�ݷ��Ը����ڵ㰴��������
    for(i=1;i<=n;i++)  
    {  
        u =LF;  
        for(j=0;j<n-i;j++)  
        {  
            p = u->next;  
            q = p->next;  
            if(p->total>q->total)  
            {  
                u->next = q;  
                p->next = q->next;  
                q->next = p;  
            }  
            u = u->next;  
        }  
    } 
	Outputfood(LF);
	return;
}
food *dingdanread()    //���ļ��ж�ȡ������Ϣ
{
	FILE *fp;
	link_food LF,r,s;
	fp=fopen("����.txt","rt");
	if(fp==NULL)
	{ 
		printf("�鿴����ʧ��");
		return 0;
	}
	LF=r=(food *)malloc(sizeof(food));
	r->next=NULL;
	while(!feof(fp))
	{
		s=(food *)malloc(sizeof(food));	
		fscanf(fp,"%s %d %d %d %s %d %s\n",s->name,&s->amount,&s->price,&s->total,s->shop,&s->type,s->yonghu);
		r->next=s;
		s->next=NULL;
		r=s;
	}
	return LF;
}
void scorefind(link_food LF)    //�̼Ҳ鿴����
{
	int sum=0;
	food *p;
	p=LF->next;
	system("cls"); 
	printf("\n\n\n\t\t\t�����Ķ�������:\n");
	printf("      ----------------------------------------------------------------------------------------------------\n");
	printf("      ��Ʒ���� \t��Ʒ����\t��Ʒ����\t��Ʒ�ܼ�\t�̼�����\t������ \t\t�û���\n");
	printf("      ----------------------------------------------------------------------------------------------------\n");
	while(p)
	{
		if(strcmp(p->shop,dp)==0)
		{
		printf("    %7s%14d%15d%16d%16s%15d%18s\n",p->name,p->amount,p->price,p->total,p->shop,p->type,p->yonghu);
		printf("      ----------------------------------------------------------------------------------------------------\n");
		sum=sum+p->total;
		}
		p=p->next;
	}
	printf("      �ϼ�/Ԫ��\t\t\t\t\t\t\t�ۼ�����%d\n",sum);
	printf("      ----------------------------------------------------------------------------------------------------\n");
	if(sum==0)
		printf("\t\t   ������Ĳ�Ŀǰ��û���˹���û�в�������\n");
}
food * foodread()   //�˵����ļ��ж�ȡ 
{
	link_food LF;
	food *s,*r;
	LF=r=(food *)malloc(sizeof(food));
	LF->next=NULL;
	FILE *fp;
	fp=fopen("�˵�.txt","rt");
	if(fp==NULL)
	{
		printf("���ܴ򿪴��ļ�");
		exit(1); 
	}
	while(!feof(fp))//C���Ա�׼�⺯������ԭ����stdio.h�У��书���Ǽ�����ϵ��ļ�������������ļ��������򷵻ط�0ֵ�����򷵻�0
	{
		s=(food *)malloc(sizeof(food));	
		fscanf(fp,"%s %d %s %s\n",s->name,&s->price,s->shop,s->leibie);
		r->next=s;
		s->next=NULL;
		r=s;
	}
	fclose(fp);
	return LF;	
 }
money * moneyread()   //�ļ��ж�ȡ�˻�
{
	link_money LM;
	money *s,*r;
	LM=r=(money *)malloc(sizeof(money));
	LM->next=NULL;
	FILE *fp;
	fp=fopen("�˻�.txt","rt");
	if(fp==NULL)
	{
		printf("���ܴ򿪴��ļ�");
		exit(1); 
	}
	while(!feof(fp))//�ж��ļ�ָ���Ƿ����ļ�����λ��
	{
		s=(money *)malloc(sizeof(money));	
		fscanf(fp,"%s %s %s\n",s->person,s->card,s->mima);
		r->next=s;
		s->next=NULL;
		r=s;
	}
	fclose(fp);
	return LM;	
 }
shop * shopread()     //���ļ��ж�ȡ�̼���Ϣ
{
	link_shop LS;
	shop *s,*r;
	LS=r=(shop *)malloc(sizeof(shop));
	r->next=NULL;
	FILE *fp;
	fp=fopen("�̼�.txt","rt");
	if(fp==NULL)
	{
		printf("���ܴ򿪴��ļ�");
		exit(1); 
	}
	while(!feof(fp))//C���Ա�׼�⺯������ԭ����stdio.h�У��书���Ǽ�����ϵ��ļ�������������ļ��������򷵻ط�0ֵ�����򷵻�0
	{
		s=(shop *)malloc(sizeof(shop));
		s->next=NULL;
		fscanf(fp,"%s %s %s %s\n",s->name,s->phone,s->address,s->password);
		r->next=s;
		r=s;
	}
	fclose(fp);
	return LS;	
 } 
shop * pingjiaread()    //���ļ��ж�ȡ����//�򿪶������۹��ܻḴ����һ�ε�����
{
	link_shop LS;
	shop *s,*r;
	LS=r=(shop *)malloc(sizeof(shop));
	r->next=NULL;
	FILE *fp;
	fp=fopen("��������.txt","rt");
	if(fp==NULL)
	{
		printf("���ܴ򿪴��ļ�");
		exit(1); 
	}
	while(!feof(fp))//C���Ա�׼�⺯������ԭ����stdio.h�У��书���Ǽ�����ϵ��ļ�������������ļ��������򷵻ط�0ֵ�����򷵻�0
	{
		s=(shop *)malloc(sizeof(shop));
		s->next=NULL;
		fscanf(fp,"%s %s\n",s->name,s->pingjia);
		r->next=s;
		r=s;
	}
	fclose(fp);
	return LS;	
 }
user * userread()   //�ļ��ж�ȡ�û���Ϣ
{
	link_user LU;
	user *s,*r;
	LU=r=(user *)malloc(sizeof(user));
	r->next=NULL;
	FILE *fp;
	fp=fopen("�û�.txt","rt");
	if(fp==NULL)
	{
		printf("���ܴ򿪴��ļ�");
		exit(1); 
	}
	while(!feof(fp))//C���Ա�׼�⺯������ԭ����stdio.h�У��书���Ǽ�����ϵ��ļ�������������ļ��������򷵻ط�0ֵ�����򷵻�0
	{
		s=(user *)malloc(sizeof(user));
		s->next=NULL;
		fscanf(fp,"%s %s %s %s %d\n",s->name,s->delivery,s->password,s->number,&s->score);
		r->next=s;
		r=s;
	}
	fclose(fp);
	return LU;	
 } 
void deleteshop(link_shop LS)  //����Աɾ���̼�
{
	int i=0;
	shop *p,*q;
	p=LS;
	q=p->next;
	char m[20];
	char a;
	printf("������������ɾ���ĵ������ƻ��ߵ绰��");
	scanf("%s",m);
	while(q)
	{
		if(strcmp(m,q->name)==0||strcmp(m,q->phone)==0)
		{
			i++;
			p->next=q->next;
			shopwrite1(LS);
			return;
		}
		else
		{
			p=p->next;
			q=q->next;
		}
	}
	if(i==0)
	{
		printf("û�д˵��̣��޷�ɾ��\n");
		return;
	}
}
void yonghudeletedingdan(link_food Lf)    //�û�ɾ������
{
	food *p,*n;
	p=Lf;
	n=p->next;
	int m,i=0;
	char a;
	printf("������������ɾ���Ķ����ţ�");
	scanf("%d",&m);
	while(n)
	{
		if(n->type==m)
		{
			if(strcmp(n->yonghu,yh)==0)
			{
				p->next=n->next;
				i++;
				foodwrite(Lf);
			}
			else
				printf("������˼����û��Ȩ��ɾ��\n");
			break;
		}
		else
		{
			p=p->next;
			n=n->next;  
		}
	}
	if(i==0)
	{
		printf("\tû�д˶������޷�ɾ��\n");
		return;
	}
}
void user_moneywrite(link_user LM)   //���¹�������
 {
 	FILE *fp;
	user *p;
	char a;

		fp=fopen("�û�.txt","wt");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LM->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s %d\n",p->name,p->delivery,p->password,p->number,p->score);
		fclose(fp);
 }time_t start,end;//�����µ�ʱ�䣬���ڲ鿴����״̬
void purchase()    //�����Ʒ����
{
	link_food Lf;
	money *LM,*mo;
	user *lu,*us;
	FILE *fp;
	char a[20],b[20],mi[20];
	char y;
	int i=0;
	printf("\t\t������������Ҫ����Ĳ���");
	scanf("%s",a);
	Lf=foodread();
	food *p;
	p=Lf->next;
	srand((unsigned)time(NULL));//�����ŵ����ӣ�������ɶ�����
	while(p!=NULL)
	{
		if(strcmp(p->name,a)==0||strcmp(p->leibie,a)==0)
		{
			i++;
		}	
		p=p->next;	
	}
	if(i==0)
	{
		printf("\t\t\t��������˼����û������Ĳ�\n");
		system("pause");
		system("cls");
		jiemian_yong();
		return; 
	}
	else   //���������˵ĵ��������û�ѡ��
	{
		p=Lf->next;
		printf("\n\t\t\t--------------------------------------------------\n");
		printf("\t\t\t����        �˼�         ����           ��ϵ\n"); 
		printf("\t\t\t---------------------------------------------------\n");
		while(p)
		{
			if(strcmp(p->leibie,a)==0||strcmp(p->name,a)==0)
			{
				printf("\t\t\t%-13s%-12d%-14s%s\n",p->name,p->price,p->shop,p->leibie);
				printf("\t\t\t---------------------------------------------------\n");
			}
			
			p=p->next;
		}
	}
	printf("\t\t��������Ҫ����ĵ��̣�");
	scanf("%s",b);
	lu=userread();
	us=lu->next;
	while(us)
	{
		if(strcmp(yh,us->name)==0)
			break;
		else
			us=us->next;
	}//�ҳ�Ҫ������û���Ϣ 
	LM=moneyread();
	mo=LM->next;
	i=0;
	while(mo)
	{
		if(strcmp(yh,mo->person)==0)
		{
			i++;
			break;
		}
		
		else
			mo=mo->next;
	}//�ҳ��û������п���Ϣ 
	if(i==0)
	{
		printf("\t\t��   ����û�а����п�Ŷ�����ܹ����");
		return; 
	}
	p=Lf->next;
	i=0;
	while(p)
	{
		if(strcmp(p->name,a)==0||strcmp(p->leibie,a)==0)
		{
			if(strcmp(p->shop,b)==0)
			{
				printf("\t\t��������Ҫ���������");
				scanf("%d",&p->amount);
				if(p->amount!=0)
				{
					i++;
					p->total=(p->amount)*(p->price);
					p->type=rand()%900+100;   //�������������
					if((us->score)<p->total)//�Ƚ����
					{
						printf("\t\t��   �����˺����㣬���ȳ�ֵ\n");
						system("pause");
						system("cls");
						jiemian_yong();
						return;
					}
					printf("\t\t��ȷ�Ϲ���Y/else");
					fflush(stdin);
					y=getchar();
					if(y=='Y')
					{
						printf("������֧������:");
						scanf("%s",mi);
						if(strcmp(mi,mo->mima)==0)
						{
							fp=fopen("����.txt","at");
							if(fp==NULL)
								printf("\t\t\t\t������ʧ��\n");//���ļ��޷��򿪶�ʧ��
							else
							{
								fprintf(fp,"%s %d %d %d %s %d %s\n",p->name,p->amount,p->price,p->total,p->shop,p->type,yh);
								fclose(fp);
								us->score=(us->score)-(p->total);
								user_moneywrite(lu);
								printf("\t\t\t\t�̹���ɹ��������ĵȴ�����\n");
								start = time(NULL);   //��ʼ��ʱ 
								system("pause");
								system("cls");
								jiemian_yong();
								return;
							}		
						}
						else
						{
							printf("\t\t��   ������󣬹���ʧ��");
							system("pause");
							system("cls");
							jiemian_yong();
							return;  
						}		 
					} 
					else
					{
						printf("\t\t\t���ѷ�������");
						system("pause");
						system("cls");
						jiemian_yong();
						return; 
					}
				}
				else
				{
					printf("\t\t\t����������ȷ������");
					system("pause");
					system("cls");
					jiemian_yong();
					return; 
				}
			}
		}
		p=p->next;
	}
	if(i==0)
	{
		printf("\t\t����������еĵ������ƣ���������̼һ�û����פ������ģ��ϵͳ\n");
		system("pause");
		system("cls");
		jiemian_yong(); 
	}
}
//������Ϣ���ļ�����ļ��ж�ȡ��Ϣ
void foodwrite(link_food LF)//��Ӳ�Ʒ���������ļ��� 
 {
 	FILE *fp;
	food *p;
	char a;
	printf("ȷ�ϱ��棿(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("�˵�.txt","at");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LF->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %d %s %s\n",p->name,p->price,dp,p->leibie);
		printf("�޸ĳɹ�\n");
		fclose(fp);
		return;
	}
	else
		printf("�ѷ����޸�");
 }
 void foodwrite1(link_food LF)//�޸Ĳ�Ʒ
 {
 	FILE *fp;
	food *p;
	char a;
	printf("ȷ�ϱ��棿(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("�˵�.txt","wt");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LF->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %d %s %s\n",p->name,p->price,p->shop,p->leibie);
		printf("�޸ĳɹ�\n");
		fclose(fp);
		return;
	}
	else
		printf("�ѷ����޸�");
 }
 void dingdanwrite(link_food LF)
 {
 	FILE *fp;
	food *p;
	char a;
	printf("ȷ�ϱ��棿(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("����.txt","wt");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LF->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %d %d %d %s %d %s\n",p->name,p->amount,p->price,p->total,p->shop,p->type,p->yonghu);
		printf("�޸ĳɹ�\n");
		fclose(fp);
		return;
	}
	else
		printf("�ѷ����޸�"); 
 }
void shopwrite1(link_shop LS)   //�̼���Ϣ����
 {
 	FILE *fp;
	shop *p;
	char a;
	printf("ȷ�ϱ��棿(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("�̼�.txt","wt");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LS->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s\n",p->name,p->phone,p->address,p->password);
		printf("����ɹ�\n");
		fclose(fp);
		return;
	}
	else
		printf("�ѷ���");
 }
 void shopwrite2(link_shop LS)   //�޸��̼���Ϣ
 {
 	FILE *fp;
	shop *p;
	char a;
	printf("�Ƿ���Ϣ�������ļ��(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("�̼�.txt","at");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LS->next;p!=NULL;p=p->next)
		fprintf(fp,"%s %s %s\n",p->name,p->phone,p->address);
		printf("�޸ĳɹ�\n");
		fclose(fp);
		return;
	}
	else
		printf("�ѷ����޸�");
	 
 }
  void shopwrite3(link_shop LS)   //���̼ҵ����۵ı���
 {
 	FILE *fp;
	shop *p;
	char a;
	printf("�Ƿ����۱��棿(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("��������.txt","at");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LS->next;p!=NULL;p=p->next)
		fprintf(fp,"%s %s\n",p->name,p->pingjia);
		printf("����ɹ�\n");
		fclose(fp);
		return;
	}
	else
		printf("�ѷ�������\n");
	 
 }
 void userwrite(link_user LU)   
 {
 	FILE *fp;
	user *p;
	char a;
		fp=fopen("�û�.txt","wt");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LU->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s %d\n",p->name,p->delivery,p->password,p->number,p->score);
		printf("�����ɹ�\n");
		fclose(fp);
		return;
 }
void deletefood(link_food Lf)    //�̼�ɾ����Ʒ
{
	int i=0;
	food *p,*n;
	p=Lf;
	n=p->next;
	char m[20];
	char a;
	printf("������������ɾ���Ĳ�����");
	scanf("%s",m);
	while(n)
	{
		if(strcmp(m,n->name)==0)
		{
			if(strcmp(n->shop,dp)==0)
			{
				i++;
				p->next=n->next;
				foodwrite1(Lf);
			}
			else
			
				printf("������˼����û��Ȩ��ɾ��\n");
			break;
		}
		else
		{
			p=p->next;
			n=n->next;
		}
	}
	if(i==0)
	{
		printf("û�д˲ˣ��޷�ɾ��\n");
		return;
	}
}
 void userwrite2(link_user LU)   //�û�ע�ᱣ�����ļ������ݱ���
 {
 	FILE *fp;
	user *p;
	char a;
	printf("�Ƿ���Ϣ��������Ӧ���ļ��(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("�û�.txt","at");
		if(fp==NULL)
			printf("�����޷���");
		for(p=LU->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s %d\n",p->name,p->delivery,p->password,p->number,p->score);
		printf("ע��ɹ�\n");
		fclose(fp);
		return;
	}
	else
		printf("�ѷ���ע��");
 }
void increaseshop(link_shop LS)     //����̼Һ���
{
	char a[30],b[20],c[15],d[20];
	shop *s;
	printf("��������������פ���̼���Ϣ��\n");
	printf("\t\t��    �������ƣ�");
	scanf("%s",a);
	printf("\n\t\t��    ���̵绰��");
	scanf("%s",b);
	printf("\n\t\t��    ���̵�ַ��");  
	scanf("%s",c);
	printf("\n\t\t��    �������룺");  
	scanf("%s",d);
	if(strcmp(a,"0")!=0)
	{
		s=(shop *)malloc(sizeof(shop));
		strcpy(s->name,a);
		strcpy(s->phone,b);
		strcpy(s->address,c);
		strcpy(s->password,d);
	}
	s->next=LS->next;
	LS->next=s; 
	shopwrite1(LS);
 }
 void pingjiawrite(link_shop LS)     //�û����̼ҽ�������
{
	char a[30],b[100];
	shop *s;
	printf("���������������̼����ƣ�\n����˶���ȷŶ����������̼��޷��������۷�����\n");
	scanf("%s",a);
	printf("\n������Ը��̼ҵ����ۣ�\n");
	scanf("%s",b);
	if(strcmp(a,"0")!=0)
	{
		s=(shop *)malloc(sizeof(shop));
		strcpy(s->name,a);
		strcpy(s->pingjia,b);
	}
	s->next=LS->next;
	LS->next=s; 
	shopwrite3(LS);
 }
void shopfind(link_shop LS)   //��ѯ�̼Һ���
{ 
	shop *p;
	char E[20];
	p=LS->next;
	printf("��������̵����ƣ�");
	scanf("%s",E); 
	while(strcmp(p->name,E)!=0&&(p->next)!=NULL)
	{
		p=p->next;
	}
	if((p->next)==NULL)
	{
		printf("û�д˵���\n");
		return;
	}	 
	printf("������ѯ�ĵ�����ϢΪ��\n����\t�绰\t��ַ\n");
	printf("%s %s %s\n",p->name,p->phone,p->address);
} 
void registerdeal()  //����Ա�������뺯��
{
	int q;
	FILE *fp;
	char y;
	link_shop head;
	shop *r,*p;
	head=r=(shop *)malloc(sizeof(shop));
	r->next=NULL;
	fp=fopen("����.txt","rt");
	if(fp==NULL)
	{
		printf("���������޷����ļ�");
		return; 
	}
	if((y=fgetc(fp))==EOF)
	{
		printf("Ŀǰû��������̼ң������ĵȴ�\n");
		system("pause");
		system("cls");
		jiemian_guan();
		return;
	}
	else
	{
		while(!feof(fp))
		{
			p=(shop *)malloc(sizeof(shop));
			fscanf(fp," %s %s %s %s \n",p->name,p->phone,p->address,p->password);
			r->next=p;
			p->next=NULL;
			r=p;
		}
		for(p=head->next;p!=NULL;p=p->next)
			printf("%s %s %s\n",p->name,p->phone,p->address); 
		printf("�Ƿ�ͬ��ע�᣿Y/else");
		scanf("%*c%c",&y); 
		if(y=='Y')
		{
			fp=fopen("�̼�.txt","at");
			if(fp==NULL)
				printf("�ļ������ڣ��򿪴���\n"); 
			for(p=head->next;p!=NULL;p=p->next)
				fprintf(fp,"% s %s %s %s \n",p->name,p->phone,p->address,p->password);
			fclose(fp);
		} 
			
	} 
	printf("����ɹ�"); 
	fp=fopen("����.txt","wt");
	fclose(fp);
}
//����ѡ�� ���û����ʲ�ͬ�Ĺ���
void jiemian_guan_choose()//����Ա����
{
	int n,m,q;
	char a[20],b[20],c[20],d[20];
	char y;
	FILE *fp,*fa;
	shop *p;
	shop sq;
	link_shop LS;
	link_user LU;
	LS=shopread();
	while(1)
	{
		printf("��ѡ������������е�ѡ��:\n"); 
		scanf("%d",&n);
		if(n==1)
		{
			Outputshop(LS);
			printf("����������ع���Աϵͳ\n"); 
			system("pause"); 
			system("cls");
			jiemian_guan();
				
		}
		if(n==2)
		{
			system("cls");
			printf("\n\n\n\t\t\t��1��ɾ������\n");
			printf("\t\t\t��2�����ӵ���\n");
			printf("\t\t\t��3����ѯ�̼�\n");
			printf("\t\t\t��0�����ع���Աϵͳ\n");
			printf("\n\t\t��ѡ��Ҫ���еĲ�����\n"); //���� 
			while(1)
			{
				scanf("%d",&m);
				if(m==1)
					deleteshop(LS);
				if(m==2)
					increaseshop(LS);
				if(m==3)
					shopfind(LS);	
				if(m==0)
				{
					system("cls");
					jiemian_guan();
					break;
				} 
			}		
		}
		if(n==3)
			registerdeal();//ע�ᴦ���� 
		if(n==4)
		{
			system("cls");
			printf("\n\t��ѡ��������е�ѡ�\n\n");
			printf("\n");
			printf("\t��1.�鿴������Ϣ\n");
			printf("\t��2.�޸����루���һ����룩\n");
			printf("\t��0.���ع���Աϵͳ\n");//���� 
			printf("\n");
			while(1)
			{
				scanf("%d",&m);
				if(m==1)
				{
					char d[20];
					fa=fopen("����Ա.txt","rt");
					fscanf(fa,"%s %s %s %s",a,b,c,d);
					fclose(fa);
					printf("\n\t\t����\t����\t�绰����\n");
					printf("\t\t%s\t%s\t%s\n",a,b,d);
				}
				if(m==2)
				{
					system("cls");
					printf("\n\t\t��0���ز鿴������Ϣ\n"); 
					printf("\n\t\t\n");
					printf("\t\t��1�޸�����\n");//���� 
					printf("\t\t\n");
					scanf("%d",&q); 
					if(q==1)//�޸����룬���һ����� 
					{
						int j=0,h; 
						char f[20],e[20];
						fa=fopen("����Ա.txt","rt");
						fscanf(fa,"%s %s %s %s",a,b,c,d);
						printf("����Ҫ����ɵ����룺\n");
						scanf("%s",f);
						while(strcmp(f,c)!=0)
						{
							j++; 
							printf("\t\t��������������,���������룺");
							scanf("%s",f);
							if(j==2)
							{
								printf("\t\t�����Ѿ�����������Σ���1�һ����룬�������ּ��������˵���½����:");
								scanf("%d",&j);
								if(j==1)
								{
									printf("���������ĵ绰����:");
									scanf("%s",e);
									if(strcmp(e,d)==0)
									{
										srand((unsigned)time(NULL));
										j=rand()%900+100;    //���������֤�룬����֤��txt�ĵ��в鿴
										fp=fopen("��֤��.txt","wt");
										fprintf(fp,"%d\n",j);
										fclose(fp);
										printf("�����Ѿ�������֤�뵽�����ֻ�����֤��txt����������:");
										scanf("%d",&h);
										if(h==j)
										{
											printf("\t\t��������������������:");
											scanf("%s",c);
											printf("�Ƿ񱣴棿Y/else");
						fflush(stdin);
						y=getchar();
						if(y=='Y')
						{
							fa=fopen("����Ա.txt","wt");
							fprintf(fa,"%s %s %s %s",a,b,c,d);
							fclose(fa);
							printf("\t\t�̱���ɹ�"); 
						}
						else
							printf("\t\t���ѷ����޸�");
						system("pause");
						system("cls");
						printf("\n\t��ѡ��������е�ѡ�\n\n");
						printf("\t\n");
						printf("\t��1.�鿴������Ϣ    \n");
						printf("\t��2.�޸ĸ�����Ϣ  \n");
						printf("\t��0.���ع���Աϵͳ      \n");//���� 
						printf("\t\n");
											break; 
										}
										else
										{
											printf("\t\t����֤�����\n");
											system("pause");
						system("cls");
						printf("\n\t��ѡ��������е�ѡ�\n\n");
						printf("\t\n");
						printf("\t��1.�鿴������Ϣ    \n");
						printf("\t��2.�޸ĸ�����Ϣ  \n");
						printf("\t��0.���ع���Աϵͳ      \n");//���� 
						printf("\t\n");
											break; 
										}
									}
									else
									{
										printf("\t\t���һ�����ʧ��\n");
										system("pause");
						system("cls");
						printf("\n\t��ѡ��������е�ѡ�\n\n");
						printf("\t\n");
						printf("\t��1.�鿴������Ϣ    \n");
						printf("\t��2.�޸ĸ�����Ϣ  \n");
						printf("\t��0.���ع���Աϵͳ      \n");//���� 
						printf("\t\n");
										break; 
									}
								}
								else
								{
									system("cls");
									jiemian_deng();
									return; 
								}
									
							}
						}
						if(strcmp(c,f)==0)
						{
							printf("�������µ����룺\n");
							scanf("%s",c);
							printf("�Ƿ񱣴棿Y/else");
						fflush(stdin);
						y=getchar();
						if(y=='Y')
						{
							fa=fopen("����Ա.txt","wt");
							fprintf(fa,"%s %s %s %s",a,b,c,d);
							fclose(fa);
							printf("\t\t�̱���ɹ�"); 
						}
						else
							printf("\t\t���ѷ����޸�");
						system("pause");
						system("cls");
						printf("\n\t��ѡ��������е�ѡ�\n\n");
						printf("\t\n");
						printf("\t��1.�鿴������Ϣ    \n");
						printf("\t��2.�޸ĸ�����Ϣ  \n");
						printf("\t��0.���ع���Աϵͳ      \n");//���� 
						printf("\t\n");
						}
					}
					if(q==0)
					{
						system("cls");
						printf("\n\t��ѡ��������е�ѡ�\n\n");
						printf("\t\n");
						printf("\t��1.�鿴������Ϣ    \n");
						printf("\t��2.�޸ĸ�����Ϣ  \n");
						printf("\t��0.���ع���Աϵͳ      \n");//���� 
						printf("\t\n");
						continue;
					}
				}
				if(m==0) 
				{
					system("cls");
					jiemian_guan();
					break;
				} 
			} 
		}
		if(n==5)
		{
			system("cls");
			jiemian_guan();
		}
		if(n==0)
		{
			system("cls");
			jiemian_deng();
			break;
		}
		if(n!=1&&n!=2&&n!=3&&n!=4&&n!=5&&n!=0)
		{
			Sleep(400);
			printf("���������������������ʾ����\n"); 
		}	
	}
}
void jiemian_yong_choose()//�û�����
{
	int n,m,q,i=0;
	char a[20],b[20];
	char y;
	FILE *fp,*fa;
	user *u;
	food *p,*s,*r;
	link_food LF,Lf;
	LF=foodread();
	link_user LU;
	link_shop LS;
	LS=pingjiaread();
//	�û�
	while(1)
	{
		scanf("%d",&n);
		switch(n)
		{
			case 1:
					system("cls");
					printf("\n\n\t\t\t��ѡ����Ҫ���е�ѡ��:\n\n");
					printf("\t\t\t--------------------\n");
					printf("\t\t\t    �� �� �� ��\n");
					printf("\t\t\t--------------------\n");
					printf("\t\t\t��   1.�޸��û���\n"); 
					printf("\t\t\t��   2.�޸�����\n"); 
					printf("\t\t\t��   3.�޸��ջ���ַ\n");
					printf("\t\t\t��   4.�޸ĵ绰��\n");
					printf("\t\t\t��   5.�鿴������Ϣ\n");
					printf("\t\t\t��   6.��ֵǮ��\n");
					printf("\t\t\t��   0.�����û�����\n");
					LU=userread();
					u=LU->next;
					while(1)
					{
						if(strcmp(yh,u->name)==0)
							break;
						else
							u=u->next;
					}
					while(1)
					{
						scanf("%d",&m);
						if(m==1)
						{
							printf("�������µ��û�����\n");
							scanf("%s",u->name);
						}
						if(m==2)
						{
							printf("����Ҫ����ɵ����룺\n");
							scanf("%s",b);
							if(strcmp(u->password,b)!=0)
							printf("������������²���\n");
							if(strcmp(u->password,b)==0){
							printf("�������µ����룺");
							scanf("%s",u->password); 
							userwrite(LU);
							}
							
						}
						if(m==3)
						{
							printf("�������µ��ջ���ַ��");
							scanf("%s",u->delivery); 
						}
						if(m==4)
						{ 
							printf("�������µĵ绰����");
							scanf("%s",u->number);
						}
						if(m==1||m==3||m==4)
							userwrite(LU);
						if(m==5)
						{
							printf("������ϢΪ��\n");
							printf("����\t�ջ��ַ\t��ϵ��ʽ\n"); 
							printf("%s\t%s\t%s\n",u->name,u->delivery,u->number);
						}
						if(m==6)
						{
							u=addmoney(u);
							userwrite(LU); 
						}
						if(m==0)
						{
							system("cls");
							jiemian_yong(); 
							break;
						}
						
					} 
					break;
			case 2:
				LF=dingdanread();
				Outputfood(LF);	//���������Ϣ
				p=LF->next;
				i=0;		 
				printf("�����������ѯ״̬�Ķ����ţ�");  //��ѯ����״̬
				scanf("%d",&n);
				while(p)
				{
					if(n==p->type)
					{
						if(strcmp(p->yonghu,yh)==0)
						{
							i=1; 
								end = time(NULL);
								if((difftime(end,start))<600)       //�ж��µ�ʱ��
								{
									printf("��û�г���10���ӣ��̼����ڱ��ͣ����������޸Ķ���Ŷ\n"); 
									system("pause");
									system("cls");
									jiemian_yong(); 
									break;
								}
								else
								{
									printf("ʱ�䳬��10���ӣ����������У������ĵȴ�\n");
									printf("����������Ҫ���������µ����̼ҽ����챸������\n");
									system("pause");
									system("cls");
									jiemian_yong(); 
									break;
								}	
							
						}
						if(strcmp(p->yonghu,yh)!=0)
						{
							printf("\t\t��   ������˼��δ��ѯ���ö���\n");
							i=2;
						    system("pause");  
							system("cls");
							jiemian_yong(); 
							break;
						}
					}
					else
						p=p->next;
				}	
				if(i==0)
				{
					printf("\t\t��   ������˼��δ��ѯ���ö���\n");
					system("pause");
					system("cls");
					jiemian_yong();
					continue;
				}	
				break;
			case 3://�鿴��Ʒ
				LF=foodread();
				system("cls");
				outputfood(LF);
				p=LF->next; 
				printf("\t��   ��1�����������ַ���\t");
				scanf("%d",&q);
				if(q==1)
				{
					purchase();  //�����Ʒ
				}
				else
				{
					system("cls");
					jiemian_yong();
					continue;
				}
				break;
			case 4:
				LF=dingdanread();
				p=LF->next;
				i=0;		 
				printf("�����������޸ĵĶ����ţ�");
				scanf("%d",&n);
				while(p)
				{
					if(n==p->type)
					{
						if(strcmp(p->yonghu,yh)==0)
						{
							i=1; 
							system("cls");
							printf("\n������Ϣ���£�\n"); 
							printf("\t����\t����\t����\t�ܼ�\t����\t�û���\t\n");
							printf("\t%s\t%d\t%d\t%d\t%s\t%s\n\n",p->name,p->price,p->amount,p->total,p->shop,p->yonghu); 
							printf("\t\t��   1.�޸�����\n");
							printf("\t\t��   2.ɾ������\n");
							printf("\t\t��   �������ּ�����\n"); 
							scanf("%d",&n);
							if(n==1)
							{
								end = time(NULL);
								if((difftime(end,start))<600)       //�ж��µ�ʱ��
								{
									printf("��û�г���10���ӣ��뾡���޸�Ŷ\n"); 
									printf("��ֻ���޸Ĳ˵������������Ҫ������Ʒ������ѡ����Ʒ�µ�\n");
									printf("���޸Ĳ˵�����:");
									scanf("%d",&m);
									p->amount=m;
									p->total=(p->amount)*(p->price);
									dingdanwrite(LF);
									printf("\t\t���ѳɹ��޸�");
								}
								else
								{
									printf("ʱ�䳬��10���ӣ������ͣ��޷��޸�\n");
									system("pause");
									system("cls");
									jiemian_yong(); 
									break;
								}
							}
							if(n==2)
							{
								yonghudeletedingdan(LF);
								dingdanwrite(LF); 
							}
							else
							{
								system("pause");
								system("cls");
								jiemian_yong();
								break;
							}
						}
						if(strcmp(p->yonghu,yh)!=0)
						{
							printf("\t\t��   ������˼���ö�����û��Ȩ���޸�\n");
							i=2;
						    system("pause");  
							system("cls");
							jiemian_yong(); 
							break;
						}
					}
					else
						p=p->next;
				}	
				if(i==0)
				{
					printf("\t\t��û�иĶ���\n");
					system("pause");
					system("cls");
					jiemian_yong();
					continue;
				}	
				break; 
			case 5:
				purchase();
				break;
			case 6:
				system("cls");
				printf("\n\n\n\t\t\t---------------\n");
				printf("\t\t\t  �� �� �� ��\n");
				printf("\t\t\t---------------\n"); 
				printf("\t\t\t�� 1.����������\n");
				printf("\t\t\t�� 2.���ܼ�����\n");
				printf("\t\t\t�� 0.�����û�ϵͳ\n");
				scanf("%d",&m);
				{
					LF=dingdanread();
					if(m==1)
						dingdan_name_sort(LF);
					if(m==2)
						dingdan_total_sort(LF);
					if(m==0)
					{
						system("cls");
						jiemian_yong();
						continue;
					}
					system("pause");
					system("cls");
					jiemian_yong();
					continue;
						
				}
				break;
			case 7:
					system("cls");
					printf("\n\n\t\t\t�����ԶԶ�����������:\n\n");
					printf("\t\t\t--------------------\n");
			        pingjiawrite(LS);
					system("pause");
					system("cls");
					jiemian_yong();		
			break;	
			case 0:
				system("cls");
				jiemian_deng();
				return;
				break;
			}
		}
}
void jiemian_shang_choose()//�̼ҽ���
{
	int x,y;
	char a[20];
	link_food LF,Lf;
	LF=foodread();
	food *p;
	shop *qp;
	link_shop L;
	L=pingjiaread();
	while(1)
	{
		printf("��ѡ��");
		scanf("%d",&x);
		if(x==1)
		{
			creatf();
		}
		if(x==2)
		{
			int i=0;
			printf("������Ҫ�޸ĵĲ˵����ƣ�");
			scanf("%s",a);

			p=LF->next;
			while(p!=NULL)
			{
				if(strcmp(a,p->name)==0)
				{
					i++;
					if(strcmp(dp,p->shop)==0)
					{
						printf("����������˵���Ϣ:\n");
						printf("\t\t\t���²�����");
						scanf("%s",p->name);
						printf("\t\t\t���²˼ۣ�");
						scanf("%d",&p->price);
						foodwrite1(LF); 
					}
					else
						printf("������˼����û��Ȩ���޸�\n");
					break; 
				}
				p=p->next;
			}
			if(i==0)
				printf("\t\t��   û�д˲˵���Ϣ\n"); 
		}
		if(x==3)
		{
			deletefood(LF);
		} 
		if(x==4)
		{
			int sum=0;
			Lf=foodread();
			p=Lf->next;
			system("cls");
			printf("\n\n\t\t���ҵ�ʳ�����£�");
			printf("\n\t\t----------------------------------------\n");
			printf("\t\t����\t     �˼�\t����\t    ��ϵ\n");
			printf("\t\t----------------------------------------\n"); 
			while(p)
			{
				if(strcmp(p->shop,dp)==0)
				{
					printf("\t\t%-14s%-10d%-12s%s\n",p->name,p->price,p->shop,p->leibie);
					printf("\t\t----------------------------------------\n");
					sum=sum+1;
				}
				p=p->next;
			}
			printf("\t\t�ϼ�/����\t\t\t%d����\n",sum);
			printf("\t\t----------------------------------------\n");
			if(sum==0)
				printf("\t\t\t�� ����û����Ӳ�Ʒ����ȥ��Ӳ�Ʒ��\n");
			system("pause");
			system("cls");
			jiemian_shang();
		}
		if(x==5)
		{
			LF=dingdanread();
			scorefind(LF);//�鿴ҵ������
			system("pause");
			system("cls");
			jiemian_shang();
		}	
		if(x==6)
		{
			printf("\n\t\t\t\t�û�����\n\n");
			qp=L->next;
			while(qp)
			{
				if(strcmp(qp->name,dp)==0)
				{
					printf("\t\t%-14s %s\n",qp->name,qp->pingjia);
					printf("\t\t----------------------------------------\n");
				}
				qp=qp->next;
			}
            printf("������������̼ҽ���\n");
					system("pause");
					system("cls");
					jiemian_shang();
		}
		if(x==7)
		{   int n,i=0;
			FILE *fp;
			food *p,*s,*r;
            LF=dingdanread();
			scorefind(LF);
			printf("�����Բ鿴�����µ�ʱ�䣺\n");
			printf("�����������ѯ״̬�Ķ����ţ�");  //��ѯ����״̬
			scanf("%d",&n);
			p=LF->next;
			while(p){
					if(n==p->type)
					{          i=1;
								end = time(NULL);
								if((difftime(end,start))<600)       //�ж��µ�ʱ��
								{
									printf("��û�г���10���ӣ��뾡�챸��\n"); 
									printf("������������̼ҽ���\n");
									system("pause");
									system("cls");
									jiemian_shang();
									break;
								}
								else
								{
									printf("ʱ�䳬��10���ӣ��뾡����ϵ��������\n");
									printf("������������̼ҽ���\n");
									system("pause");
									system("cls");
									jiemian_shang();
									break;
								}		
					
					}
					else p=p->next;}
			if(i==0)
					{printf("\t\t��   ������˼��δ��ѯ���ö���\n");
					printf("������������̼ҽ���\n");
					system("pause");
					system("cls");
					jiemian_shang();
					continue;}
					
		}			 	 
		if(x==0) 
		{
			system("cls");
			jiemian_deng();
			break;
		}	
	} 
}
//��½
void login()
{
	int n,i=0,j=0;
	char a[10],c[10];
	char b[15],d[15],f[10],e[20];
	FILE *fp;
	char ch;
	system("cls"); 
	jiemian_deng();
	printf("��ѡ��");
	while(1)
	{
		scanf("%d",&n);
		//����Ա��½ 
		if(n==1)
		{
			printf("�������û���:"); 
			scanf("%s",a);
			printf("����������:");
			while((ch=getch())!=13){
			if(ch==8){
				printf("\b \b");
				i--;
				continue;
			}
			b[i++]=ch;
			putchar('*');
			}
			b[i]='\0';
			fp=fopen("����Ա.txt","rt");
				if(fp==NULL)printf("û�д��ļ����޷���");
			fscanf(fp,"%s %s %s %s",f,c,d,e);
			fclose(fp);
			while(strcmp(a,c)!=0||strcmp(b,d)!=0)
			{
				printf("\n�˺Ż�����������������룺\n");
				printf("�������û�����");
				scanf("%s",a);
				printf("���������룺");
				i=0;
				while((ch=getch())!=13){  //ѭ�������ǲ��϶�ȡ�û�������ַ���ֱ�����»س�����ASCII��Ϊ13��Ϊֹ
				if(ch==8){                     //����û�������ַ��Ƿ����˸����ASCII��Ϊ8��
					printf("\b \b");
					i--;
					continue;
				}
				b[i++]=ch;     //����ǰ������ַ�ch�洢��b�����У�����i����һ
				putchar('*');
				}
				b[i]='\0';
				j++;
				if(j==2)
				{
					printf("\n��������Ѵ�����,���Զ��˻ص�¼����\n");
					system("pause"); 
					system("cls");
					jiemian_deng();
					return;
				}
			}
			system("cls");
			welcome();
			printf("\n");
			system("pause");
			system("cls");
			jiemian_guan();
			jiemian_guan_choose(); 
		}
	//�û���¼ 
		if(n==2)
		{
			link_user LU;
			user *p;
			LU=userread();
			p=LU->next;
			printf("�������˺Ż����ƣ�");
			scanf("%s",yh);
			printf("���������룺");
			i=0;
			while((ch=getch())!=13){
			if(ch==8){
				printf("\b \b");
				i--;
				continue;
			}
			b[i++]=ch;
			putchar('*');
			}
			b[i]='\0';
			int i=0;
			while(p!=NULL)
			{
				if(strcmp(yh,p->name)==0&&strcmp(b,p->password)==0)
				{
					system("cls");
					printf("\n");
					system("pause");
					system("cls");
					i++;
					jiemian_yong();
					jiemian_yong_choose();
					break;
				}
				p=p->next;
			}
			if(i==0)
			{ 
				printf("��������˺Ŵ���\n");
				system("pause");
				system("cls");
				jiemian_zhuce();
				return;
			}
		}
		if(n==3)
		{
			link_shop LS;
			shop *p;
			j=0;
			LS=shopread();
			p=LS->next;
			printf("������������ƻ����˺ţ�");
			scanf("%s",dp);
			printf("���������룺");
			i=0;
			while((ch=getch())!=13)
			{
				if(ch==8)
				{
					printf("\b \b");
					i--;
					continue;
				}		
				putchar('*');
				b[i++]=ch;
			}
			b[i]='\0';
			while(p!=NULL)
			{
				if(strcmp(dp,p->name)==0&&strcmp(b,p->password)==0)
				{
					system("cls");
					j++;
					printf("\n");
					system("pause");
					system("cls");
					jiemian_shang();
					jiemian_shang_choose();
					break;
				}
				else
					p=p->next;
			}
			if(j==0)
			{ 
				printf("\t\t\n��   ��������˺Ŵ���\n");
				system("pause");
				system("cls");
				jiemian_zhuce();
				return;
			}
		}
		if(n==0)
		{
			system("cls");
			jiemian_zhuce();
			break; 
		}	
	}
}
//�û�ע��
user * creatu()  
{
	char a[30],b[20],c[15],d[20];
	char ca[20],mi1[20],mi2[20];
	link_user LU,lu;
	FILE *fp;
	user *s,*r,*p;
	int x,y,i,h; 
	LU=r=(user *)malloc(sizeof(user));
	LU->next=NULL;
	printf("������������");
	scanf("%s",a);
	lu=userread();
	while(1)
	{
		i=0;
		p=lu->next;
		while(p)
		{ 
			if(strcmp(a,p->name)==0)
			{
				i++;
				printf("\t\t�����û��Ѿ�����ע���,����������:");
				scanf("%s",a);
				break;
			}
			else
				p=p->next;
		}
		if(i==0)
			break;
	}
	printf("�������ջ���ַ��");
	scanf("%s",b); 
	printf("���������룺");
	scanf("%s",c);
	printf("������绰���룺");
	scanf("%s",d); 
	x=strlen(c);
	while(x<8)
	{
		printf("\t\t����ܰ��ʾ����������С��8λ����ȫָ���ϵ�\n");
		printf("��1�޸�,�����������޸�:");
		scanf("%d",&y);
		if(y==1)
		{
			scanf("%s",c);
			x=strlen(c);	
		}
		else
			break;	
	}
	if(strcmp(b,"0")!=0)
	{
		s=(user *)malloc(sizeof(user));
		s->score=0;
		strcpy(s->name,a);
		strcpy(s->delivery,b);
		strcpy(s->password,c);
		strcpy(s->number,d);
		r->next=s;
		s->next=NULL;
		r=s;
		printf("Ϊ�˷����ֵǮ�������Ʒ������������п���");
		scanf("%s",ca);
		h=strlen(ca);
		while(h<19)
		{
			printf("\t\t��   �������п�����19λ�����������룺");
			scanf("%s",ca);
			h=strlen(ca); 
		}
		i=0; 
		printf("����������֧������");
		scanf("%s",mi1);
		printf("��ȷ������");
		scanf("%s",mi2);
		if(strcmp(mi1,mi2)!=0)
		{
			printf("\t\t��ע��ʧ��,�������벻ͬ");
			return 0;
		}
		if(strcmp(mi1,mi2)==0){
		fp=fopen("�˻�.txt","at");
		fprintf(fp,"%s %s %s\n",a,ca,mi1);
		fclose(fp);
		}
	}
	else
	{
		printf("\t\t��ע��ʧ�ܣ���������ȷ��Ϣ��");
		return 0;
	}
	return LU; 	 
}
void Register()//�̼�����
{
	int y;
	char a;
	FILE *fp;
	shop sq;//���� 
	system("cls");
	printf("\n\n\n\t\t\t\t1.ע���û�\n\t\t\t\t2.�������\n");
	printf("\t\t\t\t0.����ģ��ϵͳ");
	while(1)
	{
		printf("\n\t\t��  ��ѡ��Ҫ���е�ѡ�\n"); 
		scanf("%d",&y);
		if(y==1)//�û�ע�� 
		{
			link_user LU;
			LU=creatu();    //�����û�ע�ắ��
			userwrite2(LU); //��������
		}
		if(y==2)
		{
			printf("������������ƣ�");
			scanf("%s",sq.name);
			printf("��������̵绰��");
			scanf("%s",sq.phone);
			printf("��������̵�ַ��");
			scanf("%s",sq.address); 
			printf("������������룺");
			scanf("%s",sq.password);
			fp=fopen("����.txt","at");
			if(fp==NULL)
			{
				printf("���������޷����ļ�");
				return; 
			}
			printf("�Ƿ񱣴棿Y/else");
			scanf("%*c%c",&a);
			if(a=='Y')
			{	
				fprintf(fp," %s %s %s %s \n",sq.name,sq.phone,sq.address,sq.password);
				fclose(fp);
				printf("\t\t��   ����ɹ����ȴ�����Ա���"); 
			}
			else
			{
				printf("\t\t��   �ѷ�������");
				fclose(fp); 
			}
		}
		if(y==0)
		{
			system("cls");
			printf("\t\t\n��ӭ�ص��������ģ��ϵͳ����ѡ��������Ĳ�����");
			printf("\n\n\t\t\t\t1.ע��");
			printf("\t\t\t\t2.��½\n"); 
			break;		
		}
	}
}
int main()
{int x;
	jiemian_zhuce();//���˵�
	while(1)
	{
		scanf("%d",&x);
		if(x==1)
			Register();//ע��
		if(x==2)
			login();//��¼
		if(x==0)
		{
			Exit();//�˳�
		}
	}
}
