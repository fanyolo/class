#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<windows.h>
#include<time.h>
#include<conio.h>
//用户的结构体  
typedef struct user     //定义节点类型 typedef是用来为现有类型创建一个新的名称user=struct user（便于后续建立单链表）
{
	char name[50];
	char delivery[50];
	char password[20];
	char number[15];
	int score;           //余额
	struct user *next;    //指针域 建立链表
}user,*link_user;
//账户结构体
typedef struct money
{
	char person[50];
	char card[25];
	char mima[20];
	struct money *next;
}money,*link_money;
//订单的结构体 
typedef struct food
{
	char name[50];
	int type;              //订单号
	int amount;            //数量
	int price;             //单价
	int total;
	char shop[40];
	char yonghu[40];
	char leibie[40];       //类别
	struct food *next; 
}food,*link_food;
//商家的结构体   
typedef struct shop   //定义节点类型
{
	char name[40];
	char phone[20]; 
	char address[50];
	char password[50];
    char pingjia[100];
	struct shop *next;       //指针域
}shop,*link_shop;  //shop表示结点的类型，link_shop表示指向shop结点类型的指针类型
//函数声明
void foodwrite(link_food LF);         //添加菜品
void shopwrite1(link_shop LS);      //对商家相关信息write 
void dingdanwrite(link_food LF);     //对订单进行write
void user_(link_user LM);
//界面函数 输出更美观
void welcome()
{   system("color 90");
	int i=0;
	char a[52]="欢迎进入管理员系统";
	printf("\n\n\n\n\t\t");
	while(a[i])
	{
		printf("%c",a[i]);
		Sleep(50);   //延时 打字机形式输出文字 windows.h
		i++;
	}
	printf("\n\n\n\n\t\t");
}
void Exit()  //退出
{
	int i=0;
	system("cls");
	char a[52]="已退出外卖点餐模拟系统，欢迎您的下次光临";
	system("color 90");
	printf("\n\n\n\t\t\t");
	while(a[i])
	{
		printf("%c",a[i]);
		Sleep(100);   //延时 打字机形式输出文字
		i++;
	}
}
//登录注册菜单
void jiemian_zhuce()
{
	system("color 90");
	printf("\n\n\n\t\t                 \n\n\t欢迎进入外卖点餐模拟系统，请选择接下来的操作：▼");
	printf("\n\n\t\t\t1.注册");
	printf("\t\t\t2.登陆\t\t\t0.退出\n"); 
}
//主菜单 登录界面	
void jiemian_deng()
{
	printf("\n\n\t\t\t\t\t     外 卖 点 餐 登 录 系 统     \n\n");
	printf("\t\t\t\t\t          1.管理员登陆          \n");
	printf("\t\t\t\t\t          2.用户登录            \n");
	printf("\t\t\t\t\t          3.店家登陆            \n");
	printf("\t\t\t\t\t          0.返回注册         \n");
	printf("\t\t\t\t\t--------------------------------\n");
}
//管理员界面
void jiemian_guan()
{
	system("color 90");
	printf("                                                                                      提示：按5清屏\n");
	printf("\n\n\n\t\t\t\t\t _______欢迎进入管理员系统 _____\n\n");
	printf("\n\n\t\t\t\t\t1.查看店铺信息▼\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t2.店铺信息修改▼\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t3.处理申请店铺▼\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t4.查看本人信息▼\n");
	printf("\t\t\t\t\t--------------\n");
	printf("\t\t\t\t\t0.返回登录系统▲\n");
}
//用户界面
void jiemian_yong()
{
	system("color 90");
	printf("\n\n\n\t\t\t\t\t _______欢迎进入用户系统 _____\n\n");
	printf("\n\n\t\t\t\t 1.用户相关 ▲\t\t\t 5.购买菜品 ▼\n"); 
	printf("\t\t\t\t---------------\t\t\t---------------\n");
	printf("\t\t\t\t 2.查看订单 ▲\t\t\t 6.订单排序 ▼\n");
	printf("\t\t\t\t---------------\t\t\t---------------\n");
	printf("\t\t\t\t 3.查看菜品 ▲\t\t\t 7.商家评价 ▼\n");
	printf("\t\t\t\t---------------\t\t\t---------------\n");
	printf("\t\t\t\t 4.修改订单 ▲\t\t\t 0.返回登录 ▼\n");
}
//商家界面
void jiemian_shang()
{
	system("color 90");
	printf("\n\n\n\t\t\t _______欢迎进入商家系统 _____\n\n");
	printf("\t\t\t\t1.添加菜品\n");
	printf("\t\t\t\t2.修改菜品\n");
	printf("\t\t\t\t3.删除菜品\n");
	printf("\t\t\t\t4.查看菜品\n");
	printf("\t\t\t\t5.查看业绩\n");
	printf("\t\t\t\t6.查看评价\n");
	printf("\t\t\t\t7.订单状态\n");
	printf("\t\t\t\t0.返回登录\n");
	printf("\t\t\t------------------------------\n");
}char yh[20];char dp[20];
//建立关于单链表LF 调用函数foodwrite
void *creatf()
{
	int i=0,n;
	link_food LF;          //link_food表示指向food结点类型的指针类型
	food *s,*r;             //s 和 r 都是 food* 类型的指针，用来操作菜品链表节点
	char a[10];
	LF=(food *)malloc(sizeof(food));  //使用 malloc 分配了内存空间，大小为 food 结构体的大小，并将返回的指针强制类型转换为 food* 类型
	LF->next=NULL;    //链表的头节点，并且当前链表为空
	r=LF;             //r 也指向了链表的头节点，用来管理链表的遍历
	while(1)
	{
		printf("请输入菜的名称：");
		scanf("%s",a);
		if(strcmp(a,"0")!=0) //比较字符串大小
		{
			s=(food *)malloc(sizeof(food));
			printf("请输入菜的单价：");
			scanf("%d",&s->price);
			printf("请输入菜的类别：");
			scanf("%s",s->leibie); 
			strcpy(s->name,a);
			printf("输入0确定是否保存\n");
			s->total=(s->amount)*(s->price);
			r->next=s;           //当前链表尾部节点r的next指针指向新创建的节点s 把s加入到链表中，成为了链表的最后一个节点
			s->next=NULL;        //在将s插入到链表末尾后 将s的next指针设为NULL s是链表中的最后一个节点
			r=s;                 //将新节点s添加到链表尾部 更新r指向新的链表尾节点
		} 
		else
			break;
	}
	foodwrite(LF);  //添加菜品 将创建好的菜品链表 LF 保存到文件
} 
shop *creats()    //添加商家
{
	char a[30],b[20],c[15],d[20];
	link_shop LS;
	shop *s,*r;
	LS=r=(shop *)malloc(sizeof(shop));
	LS->next=NULL;
	r=LS;
	while(1)
	{
		printf("请输入店铺信息:\n");
		printf("\t\t●    店铺名称：");
		scanf("%s",a);
		printf("\n\t\t●    店铺电话：");
		scanf("%s",b);
		if(strcmp(b,"0")!=0)
		{
			printf("\n\t\t●    店铺地址：");  
			scanf("%s",c);
			printf("\n\t\t●    店铺密码：");  
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
void Outputshop(link_shop Ls) //输出商家，管理员查看商家
{
	int n=0;
	shop *p,*u;
	p=Ls->next;
	system("cls");
	printf("入驻的商家如下：\n");
	printf("\t\t\t\t-------------------------------------------\n");
	printf("\t\t\t\t店铺名称\t店铺电话\t店铺地址\n");
	printf("\t\t\t\t-------------------------------------------\n");
	while(p)
	{
		printf("\t\t\t\t%8s\t%8s\t%7s\n",p->name,p->phone,p->address);
		printf("\t\t\t\t-------------------------------------------\n");
		p=p->next;
	}
	for(u =Ls->next; u != NULL;u = u->next)  
        n++;                                                         //计算商家总数
    printf("\t\t\t\t合计\t\t\t\t%d个\n",n);
    printf("\t\t\t\t-------------------------------------------\n");
}
void Outputfood(link_food LF)  //输出订单       
{
	food *s;
	s=LF->next;
	int sum=0;
	printf("订单如下：\n");
	printf("\t----------------------------------------------------------------------------------------------------\n");
	printf("\t菜名\t\t数量/份\t\t单价/元\t\t总价/元\t\t商家\t\t订单号\t\t用户名\n"); 
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
	printf("\t累计输出/元\t\t\t\t\t\t\t%d\n",sum);
	printf("\t----------------------------------------------------------------------------------------------------\n");
	if(sum==0)
	{  
		printf("您还未购买任何菜品，还没有产生订单，快去菜单选购吧 ");
		Sleep(1000);
		system("cls");
		jiemian_yong();
		return;
	}
}
void outputfood(link_food LF)   //输出菜单
{
	food *p;
	p=LF->next;
	printf("\n\t\t\t                 菜       单                        "); 
	printf("\n\t\t\t==================================================\n");
	printf("\t\t\t菜名        菜价         商家           菜系\n"); 
	printf("\t\t\t---------------------------------------------------\n");
	while(p)
	{
		printf("\t\t\t%-13s%-12d%-14s%s\n",p->name,p->price,p->shop,p->leibie);   //输出左对齐
		printf("\t\t\t===================================================\n");
		p=p->next;
	}
}
user* addmoney(user *u)//充值        接受一个user*类型的指针u作为参数 返回一个user*类型的指针
{
	int n;
	char y;
	char a[20];
	FILE *fp;   //FILE *fp;声明了一个指向 FILE 类型结构体的指针变量 fp。用于操作文件
	link_money LY;
	money *p,*r;
	printf("您账户里的余额为：%d",u->score);
	printf("请选择是否充值？Y/else");
	fflush(stdin);//清除缓存 
	y=getchar();
	if(y=='Y')
	{
		fp=fopen("账户.txt","rt");
		LY=r=(money *)malloc(sizeof(money));//分配了一个 money 结构体的内存，并将其赋值给 LY 和 r
		LY->next=NULL;
		while(!feof(fp))
		{
			p=(money *)malloc(sizeof(money));
			fscanf(fp,"%s %s %s\n",p->person,p->card,p->mima);//从文件中读取账户信息，将所有账户信息都读入了一个链表中
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
		printf("充值的钱数？");
		scanf("%d",&n);
		printf("请输入支付密码：");
		scanf("%s",a);
		if(strcmp(p->mima,a)==0)
		{
			u->score=(u->score+n); 
			printf("已充值");
		} 
		else
			printf("\t\t×   密码错误，充值失败");
	}
	else
		printf("已放弃充值");
	return u; //更新信息
}					
void dingdan_name_sort(link_food LF)  //订单排序1 按订单食物名称排序 
{  
    int i,j,n;  
    n = 0;  //记录店铺总数；
    food *u,*q,*p;
    for(u =LF->next; u != NULL;u = u->next)  
        n++;  
//采用冒泡法对各个节点按姓名升序
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
void dingdan_total_sort(link_food LF)  //订单排序2 按订单总价排序 
{  
    int i,j,n;  
    n = 0;  //记录店铺总数；
    food *u,*q,*p;
    for(u =LF->next; u != NULL;u = u->next)  
        n++;  
//采用冒泡法对各个节点按姓名升序
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
food *dingdanread()    //从文件中读取订单信息
{
	FILE *fp;
	link_food LF,r,s;
	fp=fopen("订单.txt","rt");
	if(fp==NULL)
	{ 
		printf("查看订单失败");
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
void scorefind(link_food LF)    //商家查看订单
{
	int sum=0;
	food *p;
	p=LF->next;
	system("cls"); 
	printf("\n\n\n\t\t\t产生的订单如下:\n");
	printf("      ----------------------------------------------------------------------------------------------------\n");
	printf("      菜品名称 \t菜品数量\t菜品单价\t菜品总价\t商家名称\t订单号 \t\t用户名\n");
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
	printf("      合计/元：\t\t\t\t\t\t\t累计收入%d\n",sum);
	printf("      ----------------------------------------------------------------------------------------------------\n");
	if(sum==0)
		printf("\t\t   您店里的菜目前还没有人购买，没有产生订单\n");
}
food * foodread()   //菜单从文件中读取 
{
	link_food LF;
	food *s,*r;
	LF=r=(food *)malloc(sizeof(food));
	LF->next=NULL;
	FILE *fp;
	fp=fopen("菜单.txt","rt");
	if(fp==NULL)
	{
		printf("不能打开此文件");
		exit(1); 
	}
	while(!feof(fp))//C语言标准库函数，其原型在stdio.h中，其功能是检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0
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
money * moneyread()   //文件中读取账户
{
	link_money LM;
	money *s,*r;
	LM=r=(money *)malloc(sizeof(money));
	LM->next=NULL;
	FILE *fp;
	fp=fopen("账户.txt","rt");
	if(fp==NULL)
	{
		printf("不能打开此文件");
		exit(1); 
	}
	while(!feof(fp))//判断文件指针是否处于文件结束位置
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
shop * shopread()     //从文件中读取商家信息
{
	link_shop LS;
	shop *s,*r;
	LS=r=(shop *)malloc(sizeof(shop));
	r->next=NULL;
	FILE *fp;
	fp=fopen("商家.txt","rt");
	if(fp==NULL)
	{
		printf("不能打开此文件");
		exit(1); 
	}
	while(!feof(fp))//C语言标准库函数，其原型在stdio.h中，其功能是检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0
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
shop * pingjiaread()    //从文件中读取评价//打开订单评价功能会复制上一次的评价
{
	link_shop LS;
	shop *s,*r;
	LS=r=(shop *)malloc(sizeof(shop));
	r->next=NULL;
	FILE *fp;
	fp=fopen("订单评价.txt","rt");
	if(fp==NULL)
	{
		printf("不能打开此文件");
		exit(1); 
	}
	while(!feof(fp))//C语言标准库函数，其原型在stdio.h中，其功能是检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0
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
user * userread()   //文件中读取用户信息
{
	link_user LU;
	user *s,*r;
	LU=r=(user *)malloc(sizeof(user));
	r->next=NULL;
	FILE *fp;
	fp=fopen("用户.txt","rt");
	if(fp==NULL)
	{
		printf("不能打开此文件");
		exit(1); 
	}
	while(!feof(fp))//C语言标准库函数，其原型在stdio.h中，其功能是检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0
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
void deleteshop(link_shop LS)  //管理员删除商家
{
	int i=0;
	shop *p,*q;
	p=LS;
	q=p->next;
	char m[20];
	char a;
	printf("请输入你所想删除的店铺名称或者电话：");
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
		printf("没有此店铺，无法删除\n");
		return;
	}
}
void yonghudeletedingdan(link_food Lf)    //用户删除订单
{
	food *p,*n;
	p=Lf;
	n=p->next;
	int m,i=0;
	char a;
	printf("请输入你所想删除的订单号：");
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
				printf("不好意思，您没有权限删除\n");
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
		printf("\t没有此订单，无法删除\n");
		return;
	}
}
void user_moneywrite(link_user LM)   //更新购买后余额
 {
 	FILE *fp;
	user *p;
	char a;

		fp=fopen("用户.txt","wt");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LM->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s %d\n",p->name,p->delivery,p->password,p->number,p->score);
		fclose(fp);
 }time_t start,end;//订单下单时间，用于查看订单状态
void purchase()    //购买菜品函数
{
	link_food Lf;
	money *LM,*mo;
	user *lu,*us;
	FILE *fp;
	char a[20],b[20],mi[20];
	char y;
	int i=0;
	printf("\t\t◇请输入您想要购买的菜名");
	scanf("%s",a);
	Lf=foodread();
	food *p;
	p=Lf->next;
	srand((unsigned)time(NULL));//订单号的种子，随机生成订单号
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
		printf("\t\t\t×不好意思，还没您输入的菜\n");
		system("pause");
		system("cls");
		jiemian_yong();
		return; 
	}
	else   //输出有这个菜的店名，供用户选择
	{
		p=Lf->next;
		printf("\n\t\t\t--------------------------------------------------\n");
		printf("\t\t\t菜名        菜价         店铺           菜系\n"); 
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
	printf("\t\t◇请输入要购买的店铺：");
	scanf("%s",b);
	lu=userread();
	us=lu->next;
	while(us)
	{
		if(strcmp(yh,us->name)==0)
			break;
		else
			us=us->next;
	}//找出要购买的用户信息 
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
	}//找出用户的银行卡信息 
	if(i==0)
	{
		printf("\t\t×   您还没有绑定银行卡哦，不能购买的");
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
				printf("\t\t◇请输入要购买的数量");
				scanf("%d",&p->amount);
				if(p->amount!=0)
				{
					i++;
					p->total=(p->amount)*(p->price);
					p->type=rand()%900+100;   //生成随机订单号
					if((us->score)<p->total)//比较余额
					{
						printf("\t\t×   您的账号余额不足，请先充值\n");
						system("pause");
						system("cls");
						jiemian_yong();
						return;
					}
					printf("\t\t●确认购买？Y/else");
					fflush(stdin);
					y=getchar();
					if(y=='Y')
					{
						printf("请输入支付密码:");
						scanf("%s",mi);
						if(strcmp(mi,mo->mima)==0)
						{
							fp=fopen("订单.txt","at");
							if(fp==NULL)
								printf("\t\t\t\t×购买失败\n");//因文件无法打开而失败
							else
							{
								fprintf(fp,"%s %d %d %d %s %d %s\n",p->name,p->amount,p->price,p->total,p->shop,p->type,yh);
								fclose(fp);
								us->score=(us->score)-(p->total);
								user_moneywrite(lu);
								printf("\t\t\t\t√购买成功，请耐心等待配送\n");
								start = time(NULL);   //开始计时 
								system("pause");
								system("cls");
								jiemian_yong();
								return;
							}		
						}
						else
						{
							printf("\t\t×   密码错误，购买失败");
							system("pause");
							system("cls");
							jiemian_yong();
							return;  
						}		 
					} 
					else
					{
						printf("\t\t\t×已放弃购买");
						system("pause");
						system("cls");
						jiemian_yong();
						return; 
					}
				}
				else
				{
					printf("\t\t\t×请输入正确的数量");
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
		printf("\t\t×请输入表中的店铺名称，您输入的商家还没有入驻该外卖模拟系统\n");
		system("pause");
		system("cls");
		jiemian_yong(); 
	}
}
//保存信息到文件或从文件中读取信息
void foodwrite(link_food LF)//添加菜品并保存在文件中 
 {
 	FILE *fp;
	food *p;
	char a;
	printf("确认保存？(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("菜单.txt","at");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LF->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %d %s %s\n",p->name,p->price,dp,p->leibie);
		printf("修改成功\n");
		fclose(fp);
		return;
	}
	else
		printf("已放弃修改");
 }
 void foodwrite1(link_food LF)//修改菜品
 {
 	FILE *fp;
	food *p;
	char a;
	printf("确认保存？(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("菜单.txt","wt");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LF->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %d %s %s\n",p->name,p->price,p->shop,p->leibie);
		printf("修改成功\n");
		fclose(fp);
		return;
	}
	else
		printf("已放弃修改");
 }
 void dingdanwrite(link_food LF)
 {
 	FILE *fp;
	food *p;
	char a;
	printf("确认保存？(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("订单.txt","wt");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LF->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %d %d %d %s %d %s\n",p->name,p->amount,p->price,p->total,p->shop,p->type,p->yonghu);
		printf("修改成功\n");
		fclose(fp);
		return;
	}
	else
		printf("已放弃修改"); 
 }
void shopwrite1(link_shop LS)   //商家信息保存
 {
 	FILE *fp;
	shop *p;
	char a;
	printf("确认保存？(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("商家.txt","wt");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LS->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s\n",p->name,p->phone,p->address,p->password);
		printf("保存成功\n");
		fclose(fp);
		return;
	}
	else
		printf("已放弃");
 }
 void shopwrite2(link_shop LS)   //修改商家信息
 {
 	FILE *fp;
	shop *p;
	char a;
	printf("是否将信息保存至文件里？(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("商家.txt","at");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LS->next;p!=NULL;p=p->next)
		fprintf(fp,"%s %s %s\n",p->name,p->phone,p->address);
		printf("修改成功\n");
		fclose(fp);
		return;
	}
	else
		printf("已放弃修改");
	 
 }
  void shopwrite3(link_shop LS)   //对商家的评价的保存
 {
 	FILE *fp;
	shop *p;
	char a;
	printf("是否将评价保存？(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("订单评价.txt","at");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LS->next;p!=NULL;p=p->next)
		fprintf(fp,"%s %s\n",p->name,p->pingjia);
		printf("保存成功\n");
		fclose(fp);
		return;
	}
	else
		printf("已放弃保存\n");
	 
 }
 void userwrite(link_user LU)   
 {
 	FILE *fp;
	user *p;
	char a;
		fp=fopen("用户.txt","wt");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LU->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s %d\n",p->name,p->delivery,p->password,p->number,p->score);
		printf("操作成功\n");
		fclose(fp);
		return;
 }
void deletefood(link_food Lf)    //商家删除菜品
{
	int i=0;
	food *p,*n;
	p=Lf;
	n=p->next;
	char m[20];
	char a;
	printf("请输入你所想删除的菜名：");
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
			
				printf("不好意思，您没有权限删除\n");
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
		printf("没有此菜，无法删除\n");
		return;
	}
}
 void userwrite2(link_user LU)   //用户注册保存与文件，数据备份
 {
 	FILE *fp;
	user *p;
	char a;
	printf("是否将信息保存至对应的文件里？(Y/else)");
	scanf("%*c%c",&a);
	if(a=='Y')
	{
		fp=fopen("用户.txt","at");
		if(fp==NULL)
			printf("错误！无法打开");
		for(p=LU->next;p!=NULL;p=p->next)
			fprintf(fp,"%s %s %s %s %d\n",p->name,p->delivery,p->password,p->number,p->score);
		printf("注册成功\n");
		fclose(fp);
		return;
	}
	else
		printf("已放弃注册");
 }
void increaseshop(link_shop LS)     //添加商家函数
{
	char a[30],b[20],c[15],d[20];
	shop *s;
	printf("请输入你所想入驻的商家信息：\n");
	printf("\t\t●    店铺名称：");
	scanf("%s",a);
	printf("\n\t\t●    店铺电话：");
	scanf("%s",b);
	printf("\n\t\t●    店铺地址：");  
	scanf("%s",c);
	printf("\n\t\t●    店铺密码：");  
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
 void pingjiawrite(link_shop LS)     //用户对商家进行评价
{
	char a[30],b[100];
	shop *s;
	printf("请输入你想评价商家名称：\n（请核对正确哦，输入错误商家无法看到评价反馈）\n");
	scanf("%s",a);
	printf("\n请输入对该商家的评价：\n");
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
void shopfind(link_shop LS)   //查询商家函数
{ 
	shop *p;
	char E[20];
	p=LS->next;
	printf("请输入店铺的名称：");
	scanf("%s",E); 
	while(strcmp(p->name,E)!=0&&(p->next)!=NULL)
	{
		p=p->next;
	}
	if((p->next)==NULL)
	{
		printf("没有此店铺\n");
		return;
	}	 
	printf("您所查询的店铺信息为：\n名称\t电话\t地址\n");
	printf("%s %s %s\n",p->name,p->phone,p->address);
} 
void registerdeal()  //管理员处理申请函数
{
	int q;
	FILE *fp;
	char y;
	link_shop head;
	shop *r,*p;
	head=r=(shop *)malloc(sizeof(shop));
	r->next=NULL;
	fp=fopen("申请.txt","rt");
	if(fp==NULL)
	{
		printf("发生错误，无法打开文件");
		return; 
	}
	if((y=fgetc(fp))==EOF)
	{
		printf("目前没有申请的商家，请耐心等待\n");
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
		printf("是否同意注册？Y/else");
		scanf("%*c%c",&y); 
		if(y=='Y')
		{
			fp=fopen("商家.txt","at");
			if(fp==NULL)
				printf("文件不存在，打开错误\n"); 
			for(p=head->next;p!=NULL;p=p->next)
				fprintf(fp,"% s %s %s %s \n",p->name,p->phone,p->address,p->password);
			fclose(fp);
		} 
			
	} 
	printf("处理成功"); 
	fp=fopen("申请.txt","wt");
	fclose(fp);
}
//界面选择 供用户访问不同的功能
void jiemian_guan_choose()//管理员界面
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
		printf("请选择你想所想进行的选项:\n"); 
		scanf("%d",&n);
		if(n==1)
		{
			Outputshop(LS);
			printf("按任意键返回管理员系统\n"); 
			system("pause"); 
			system("cls");
			jiemian_guan();
				
		}
		if(n==2)
		{
			system("cls");
			printf("\n\n\n\t\t\t【1】删除店铺\n");
			printf("\t\t\t【2】增加店铺\n");
			printf("\t\t\t【3】查询商家\n");
			printf("\t\t\t【0】返回管理员系统\n");
			printf("\n\t\t请选择将要进行的操作：\n"); //二级 
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
			registerdeal();//注册处理函数 
		if(n==4)
		{
			system("cls");
			printf("\n\t请选择所想进行的选项：\n\n");
			printf("\n");
			printf("\t●1.查看个人信息\n");
			printf("\t●2.修改密码（可找回密码）\n");
			printf("\t●0.返回管理员系统\n");//二级 
			printf("\n");
			while(1)
			{
				scanf("%d",&m);
				if(m==1)
				{
					char d[20];
					fa=fopen("管理员.txt","rt");
					fscanf(fa,"%s %s %s %s",a,b,c,d);
					fclose(fa);
					printf("\n\t\t地区\t姓名\t电话号码\n");
					printf("\t\t%s\t%s\t%s\n",a,b,d);
				}
				if(m==2)
				{
					system("cls");
					printf("\n\t\t●按0返回查看个人信息\n"); 
					printf("\n\t\t\n");
					printf("\t\t●按1修改密码\n");//三级 
					printf("\t\t\n");
					scanf("%d",&q); 
					if(q==1)//修改密码，含找回密码 
					{
						int j=0,h; 
						char f[20],e[20];
						fa=fopen("管理员.txt","rt");
						fscanf(fa,"%s %s %s %s",a,b,c,d);
						printf("您需要输入旧的密码：\n");
						scanf("%s",f);
						while(strcmp(f,c)!=0)
						{
							j++; 
							printf("\t\t×您的密码有误,请重新输入：");
							scanf("%s",f);
							if(j==2)
							{
								printf("\t\t×您已经连续输错三次，按1找回密码，其他数字键返回主菜单登陆界面:");
								scanf("%d",&j);
								if(j==1)
								{
									printf("请输入您的电话号码:");
									scanf("%s",e);
									if(strcmp(e,d)==0)
									{
										srand((unsigned)time(NULL));
										j=rand()%900+100;    //随机产生验证码，在验证码txt文档中查看
										fp=fopen("验证码.txt","wt");
										fprintf(fp,"%d\n",j);
										fclose(fp);
										printf("我们已经发送验证码到您的手机（验证码txt），请输入:");
										scanf("%d",&h);
										if(h==j)
										{
											printf("\t\t√请重新设置您的密码:");
											scanf("%s",c);
											printf("是否保存？Y/else");
						fflush(stdin);
						y=getchar();
						if(y=='Y')
						{
							fa=fopen("管理员.txt","wt");
							fprintf(fa,"%s %s %s %s",a,b,c,d);
							fclose(fa);
							printf("\t\t√保存成功"); 
						}
						else
							printf("\t\t×已放弃修改");
						system("pause");
						system("cls");
						printf("\n\t请选择所想进行的选项：\n\n");
						printf("\t\n");
						printf("\t●1.查看个人信息    \n");
						printf("\t●2.修改个人信息  \n");
						printf("\t●0.返回管理员系统      \n");//二级 
						printf("\t\n");
											break; 
										}
										else
										{
											printf("\t\t×验证码错误\n");
											system("pause");
						system("cls");
						printf("\n\t请选择所想进行的选项：\n\n");
						printf("\t\n");
						printf("\t●1.查看个人信息    \n");
						printf("\t●2.修改个人信息  \n");
						printf("\t●0.返回管理员系统      \n");//二级 
						printf("\t\n");
											break; 
										}
									}
									else
									{
										printf("\t\t×找回密码失败\n");
										system("pause");
						system("cls");
						printf("\n\t请选择所想进行的选项：\n\n");
						printf("\t\n");
						printf("\t●1.查看个人信息    \n");
						printf("\t●2.修改个人信息  \n");
						printf("\t●0.返回管理员系统      \n");//二级 
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
							printf("请输入新的密码：\n");
							scanf("%s",c);
							printf("是否保存？Y/else");
						fflush(stdin);
						y=getchar();
						if(y=='Y')
						{
							fa=fopen("管理员.txt","wt");
							fprintf(fa,"%s %s %s %s",a,b,c,d);
							fclose(fa);
							printf("\t\t√保存成功"); 
						}
						else
							printf("\t\t×已放弃修改");
						system("pause");
						system("cls");
						printf("\n\t请选择所想进行的选项：\n\n");
						printf("\t\n");
						printf("\t●1.查看个人信息    \n");
						printf("\t●2.修改个人信息  \n");
						printf("\t●0.返回管理员系统      \n");//二级 
						printf("\t\n");
						}
					}
					if(q==0)
					{
						system("cls");
						printf("\n\t请选择所想进行的选项：\n\n");
						printf("\t\n");
						printf("\t●1.查看个人信息    \n");
						printf("\t●2.修改个人信息  \n");
						printf("\t●0.返回管理员系统      \n");//二级 
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
			printf("输入的数字有误，请输入提示数字\n"); 
		}	
	}
}
void jiemian_yong_choose()//用户界面
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
//	用户
	while(1)
	{
		scanf("%d",&n);
		switch(n)
		{
			case 1:
					system("cls");
					printf("\n\n\t\t\t请选择需要进行的选项:\n\n");
					printf("\t\t\t--------------------\n");
					printf("\t\t\t    用 户 相 关\n");
					printf("\t\t\t--------------------\n");
					printf("\t\t\t●   1.修改用户名\n"); 
					printf("\t\t\t●   2.修改密码\n"); 
					printf("\t\t\t●   3.修改收货地址\n");
					printf("\t\t\t●   4.修改电话号\n");
					printf("\t\t\t●   5.查看个人信息\n");
					printf("\t\t\t●   6.充值钱包\n");
					printf("\t\t\t●   0.返回用户界面\n");
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
							printf("请输入新的用户名：\n");
							scanf("%s",u->name);
						}
						if(m==2)
						{
							printf("您需要输入旧的密码：\n");
							scanf("%s",b);
							if(strcmp(u->password,b)!=0)
							printf("密码错误，请重新操作\n");
							if(strcmp(u->password,b)==0){
							printf("请输入新的密码：");
							scanf("%s",u->password); 
							userwrite(LU);
							}
							
						}
						if(m==3)
						{
							printf("请输入新的收货地址：");
							scanf("%s",u->delivery); 
						}
						if(m==4)
						{ 
							printf("请输入新的电话号码");
							scanf("%s",u->number);
						}
						if(m==1||m==3||m==4)
							userwrite(LU);
						if(m==5)
						{
							printf("您的信息为：\n");
							printf("姓名\t收获地址\t联系方式\n"); 
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
				Outputfood(LF);	//输出订单信息
				p=LF->next;
				i=0;		 
				printf("请输入所想查询状态的订单号：");  //查询订单状态
				scanf("%d",&n);
				while(p)
				{
					if(n==p->type)
					{
						if(strcmp(p->yonghu,yh)==0)
						{
							i=1; 
								end = time(NULL);
								if((difftime(end,start))<600)       //判断下单时间
								{
									printf("还没有超过10分钟，商家正在备餐，您还可以修改订单哦\n"); 
									system("pause");
									system("cls");
									jiemian_yong(); 
									break;
								}
								else
								{
									printf("时间超过10分钟，正在配送中，请耐心等待\n");
									printf("如有其他需要，请重新下单，商家将尽快备餐配送\n");
									system("pause");
									system("cls");
									jiemian_yong(); 
									break;
								}	
							
						}
						if(strcmp(p->yonghu,yh)!=0)
						{
							printf("\t\t×   不好意思，未查询到该订单\n");
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
					printf("\t\t×   不好意思，未查询到该订单\n");
					system("pause");
					system("cls");
					jiemian_yong();
					continue;
				}	
				break;
			case 3://查看菜品
				LF=foodread();
				system("cls");
				outputfood(LF);
				p=LF->next; 
				printf("\t●   按1购买，其他数字返回\t");
				scanf("%d",&q);
				if(q==1)
				{
					purchase();  //购买菜品
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
				printf("请输入所想修改的订单号：");
				scanf("%d",&n);
				while(p)
				{
					if(n==p->type)
					{
						if(strcmp(p->yonghu,yh)==0)
						{
							i=1; 
							system("cls");
							printf("\n订单信息如下：\n"); 
							printf("\t菜名\t单价\t数量\t总价\t店铺\t用户名\t\n");
							printf("\t%s\t%d\t%d\t%d\t%s\t%s\n\n",p->name,p->price,p->amount,p->total,p->shop,p->yonghu); 
							printf("\t\t○   1.修改数量\n");
							printf("\t\t○   2.删除订单\n");
							printf("\t\t○   其他数字键返回\n"); 
							scanf("%d",&n);
							if(n==1)
							{
								end = time(NULL);
								if((difftime(end,start))<600)       //判断下单时间
								{
									printf("还没有超过10分钟，请尽快修改哦\n"); 
									printf("您只能修改菜的数量，如果需要其他菜品，请再选购菜品下单\n");
									printf("请修改菜的数量:");
									scanf("%d",&m);
									p->amount=m;
									p->total=(p->amount)*(p->price);
									dingdanwrite(LF);
									printf("\t\t√已成功修改");
								}
								else
								{
									printf("时间超过10分钟，已配送，无法修改\n");
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
							printf("\t\t×   不好意思，该订单您没有权限修改\n");
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
					printf("\t\t×没有改订单\n");
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
				printf("\t\t\t  订 单 排 序\n");
				printf("\t\t\t---------------\n"); 
				printf("\t\t\t△ 1.按菜名排序：\n");
				printf("\t\t\t△ 2.按总价排序：\n");
				printf("\t\t\t△ 0.返回用户系统\n");
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
					printf("\n\n\t\t\t您可以对订单进行评价:\n\n");
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
void jiemian_shang_choose()//商家界面
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
		printf("请选择：");
		scanf("%d",&x);
		if(x==1)
		{
			creatf();
		}
		if(x==2)
		{
			int i=0;
			printf("请输入要修改的菜的名称：");
			scanf("%s",a);

			p=LF->next;
			while(p!=NULL)
			{
				if(strcmp(a,p->name)==0)
				{
					i++;
					if(strcmp(dp,p->shop)==0)
					{
						printf("请重新输入菜的信息:\n");
						printf("\t\t\t△新菜名：");
						scanf("%s",p->name);
						printf("\t\t\t△新菜价：");
						scanf("%d",&p->price);
						foodwrite1(LF); 
					}
					else
						printf("不好意思，您没有权限修改\n");
					break; 
				}
				p=p->next;
			}
			if(i==0)
				printf("\t\t×   没有此菜的信息\n"); 
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
			printf("\n\n\t\t您家的食物如下：");
			printf("\n\t\t----------------------------------------\n");
			printf("\t\t菜名\t     菜价\t店铺\t    菜系\n");
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
			printf("\t\t合计/个：\t\t\t%d个菜\n",sum);
			printf("\t\t----------------------------------------\n");
			if(sum==0)
				printf("\t\t\t● 您还没有添加菜品，快去添加菜品吧\n");
			system("pause");
			system("cls");
			jiemian_shang();
		}
		if(x==5)
		{
			LF=dingdanread();
			scorefind(LF);//查看业绩函数
			system("pause");
			system("cls");
			jiemian_shang();
		}	
		if(x==6)
		{
			printf("\n\t\t\t\t用户评价\n\n");
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
            printf("按任意键返回商家界面\n");
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
			printf("您可以查看订单下单时间：\n");
			printf("请输入所想查询状态的订单号：");  //查询订单状态
			scanf("%d",&n);
			p=LF->next;
			while(p){
					if(n==p->type)
					{          i=1;
								end = time(NULL);
								if((difftime(end,start))<600)       //判断下单时间
								{
									printf("还没有超过10分钟，请尽快备餐\n"); 
									printf("按任意键返回商家界面\n");
									system("pause");
									system("cls");
									jiemian_shang();
									break;
								}
								else
								{
									printf("时间超过10分钟，请尽快联系骑手配送\n");
									printf("按任意键返回商家界面\n");
									system("pause");
									system("cls");
									jiemian_shang();
									break;
								}		
					
					}
					else p=p->next;}
			if(i==0)
					{printf("\t\t×   不好意思，未查询到该订单\n");
					printf("按任意键返回商家界面\n");
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
//登陆
void login()
{
	int n,i=0,j=0;
	char a[10],c[10];
	char b[15],d[15],f[10],e[20];
	FILE *fp;
	char ch;
	system("cls"); 
	jiemian_deng();
	printf("请选择：");
	while(1)
	{
		scanf("%d",&n);
		//管理员登陆 
		if(n==1)
		{
			printf("请输入用户名:"); 
			scanf("%s",a);
			printf("请输入密码:");
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
			fp=fopen("管理员.txt","rt");
				if(fp==NULL)printf("没有此文件，无法打开");
			fscanf(fp,"%s %s %s %s",f,c,d,e);
			fclose(fp);
			while(strcmp(a,c)!=0||strcmp(b,d)!=0)
			{
				printf("\n账号或密码错误，请重新输入：\n");
				printf("请输入用户名：");
				scanf("%s",a);
				printf("请输入密码：");
				i=0;
				while((ch=getch())!=13){  //循环条件是不断读取用户输入的字符，直到按下回车键（ASCII码为13）为止
				if(ch==8){                     //检查用户输入的字符是否是退格键（ASCII码为8）
					printf("\b \b");
					i--;
					continue;
				}
				b[i++]=ch;     //将当前输入的字符ch存储在b数组中，并将i增加一
				putchar('*');
				}
				b[i]='\0';
				j++;
				if(j==2)
				{
					printf("\n密码错误已达三次,将自动退回登录界面\n");
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
	//用户登录 
		if(n==2)
		{
			link_user LU;
			user *p;
			LU=userread();
			p=LU->next;
			printf("请输入账号或名称：");
			scanf("%s",yh);
			printf("请输入密码：");
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
				printf("密码或者账号错误\n");
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
			printf("请输入店铺名称或者账号：");
			scanf("%s",dp);
			printf("请输入密码：");
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
				printf("\t\t\n×   密码或者账号错误\n");
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
//用户注册
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
	printf("请输入姓名：");
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
				printf("\t\t×此用户已经有人注册过,请重新输入:");
				scanf("%s",a);
				break;
			}
			else
				p=p->next;
		}
		if(i==0)
			break;
	}
	printf("请输入收货地址：");
	scanf("%s",b); 
	printf("请输入密码：");
	scanf("%s",c);
	printf("请输入电话号码：");
	scanf("%s",d); 
	x=strlen(c);
	while(x<8)
	{
		printf("\t\t●温馨提示：您的密码小于8位，安全指数较低\n");
		printf("按1修改,其他键放弃修改:");
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
		printf("为了方便充值钱包购买菜品，请绑定您的银行卡：");
		scanf("%s",ca);
		h=strlen(ca);
		while(h<19)
		{
			printf("\t\t●   您的银行卡不足19位，请重新输入：");
			scanf("%s",ca);
			h=strlen(ca); 
		}
		i=0; 
		printf("请设置您的支付密码");
		scanf("%s",mi1);
		printf("请确认密码");
		scanf("%s",mi2);
		if(strcmp(mi1,mi2)!=0)
		{
			printf("\t\t×注册失败,两次密码不同");
			return 0;
		}
		if(strcmp(mi1,mi2)==0){
		fp=fopen("账户.txt","at");
		fprintf(fp,"%s %s %s\n",a,ca,mi1);
		fclose(fp);
		}
	}
	else
	{
		printf("\t\t×注册失败，请输入正确信息：");
		return 0;
	}
	return LU; 	 
}
void Register()//商家申请
{
	int y;
	char a;
	FILE *fp;
	shop sq;//申请 
	system("cls");
	printf("\n\n\n\t\t\t\t1.注册用户\n\t\t\t\t2.申请店铺\n");
	printf("\t\t\t\t0.返回模拟系统");
	while(1)
	{
		printf("\n\t\t▲  请选择要进行的选项：\n"); 
		scanf("%d",&y);
		if(y==1)//用户注册 
		{
			link_user LU;
			LU=creatu();    //调用用户注册函数
			userwrite2(LU); //保存数据
		}
		if(y==2)
		{
			printf("请输入店铺名称：");
			scanf("%s",sq.name);
			printf("请输入店铺电话：");
			scanf("%s",sq.phone);
			printf("请输入店铺地址：");
			scanf("%s",sq.address); 
			printf("请输入店铺密码：");
			scanf("%s",sq.password);
			fp=fopen("申请.txt","at");
			if(fp==NULL)
			{
				printf("发生错误，无法打开文件");
				return; 
			}
			printf("是否保存？Y/else");
			scanf("%*c%c",&a);
			if(a=='Y')
			{	
				fprintf(fp," %s %s %s %s \n",sq.name,sq.phone,sq.address,sq.password);
				fclose(fp);
				printf("\t\t√   申请成功，等待管理员审核"); 
			}
			else
			{
				printf("\t\t×   已放弃申请");
				fclose(fp); 
			}
		}
		if(y==0)
		{
			system("cls");
			printf("\t\t\n欢迎回到外卖点餐模拟系统，请选择接下来的操作：");
			printf("\n\n\t\t\t\t1.注册");
			printf("\t\t\t\t2.登陆\n"); 
			break;		
		}
	}
}
int main()
{int x;
	jiemian_zhuce();//主菜单
	while(1)
	{
		scanf("%d",&x);
		if(x==1)
			Register();//注册
		if(x==2)
			login();//登录
		if(x==0)
		{
			Exit();//退出
		}
	}
}
