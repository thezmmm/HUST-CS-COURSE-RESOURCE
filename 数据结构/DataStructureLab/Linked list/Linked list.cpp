#include "stdio.h"
#include "stdlib.h"
#include"string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //线性表的管理表定义
     struct { char name[30];
               LinkList L;
      } elem[10];
    int length;//多链表的长度
    int listsize;
 }LISTS;
LinkList L;
LISTS Lists;
status InitList(LinkList &L);
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
status DestroyList(LinkList &L);
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
status ClearList(LinkList &L);
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
status ListEmpty(LinkList L);
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
int ListLength(LinkList L);
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
status GetElem(LinkList L,int i,ElemType &e);
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status LocateElem(LinkList L,ElemType e);
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
status PriorElem(LinkList L,ElemType e,ElemType &pre);
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status NextElem(LinkList L,ElemType e,ElemType &next);
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListInsert(LinkList &L,int i,ElemType e);
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListDelete(LinkList &L,int i,ElemType &e);
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListTraverse(LinkList L);
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
status SaveList(LinkList L,char FileName[]);
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
status LoadList(LinkList &L,char FileName[]);
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
status reverseList(LinkList &L);
//初始条件是线性表L已存在；操作结果是将L翻转；
status RemoveNthFromEnd(LinkList &L,int n);
//初始条件是线性表L已存在且非空, 操作结果是删除该链表中倒数第n个节点；
status sortList(LinkList &L);
//初始条件是线性表L已存在；操作结果是将L由小到大排序；
status AddList(LISTS &Lists,char ListName[]);
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
status RemoveList(LISTS &Lists,char ListName[]);
// Lists中删除一个名称为ListName的线性表
int LocateList(LISTS Lists,char ListName[]);
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L!=NULL)
            return INFEASIBLE;
        else{
            L=(LinkList)malloc(sizeof(LNode));
            L->next=NULL;
            return OK;
        }
}
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    else{
        LinkList p;
        while(L){
            p=L->next;
            free(L);
            L=p;
        }
        return OK;
    }
}
status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    else{
        LinkList p1,p2;
        p1=L->next;
        while(p1){
            p2=p1->next;
            free(p1);
            p1=p2;
        }
        L->next=NULL;
        return OK;
    }
}
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    if(L->next==NULL)
        return TRUE;
    else
        return FALSE;
}
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    else{
        int num=0;
        LinkList p;
        p=L->next;
        while(p){
            num++;
            p=p->next;
            
        }
        return num;
    }
}
status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    if(i<1)
        return ERROR;
    LinkList p;
    p=L->next;
    for(int j=1;j<=i;j++){
        if(p==NULL){
            return ERROR;
        }
        e=p->data;
        p=p->next;
    }
    return OK;
}
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next;
    int num=1;
    while(p){
        if(p->data==e)
            return num;
        else{
            num++;
            p=p->next;
        }
    }
    return ERROR;
}
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    if(e==L->next->data)
        return -5;
    LinkList p=L->next;
    LinkList last=L;
    for(;p!=NULL;p=p->next,last=last->next){
        if(p->data==e){
            if(p==L->next)
                return ERROR;
            else{
                pre=last->data;
                return OK;
            }
        }
    }
    return ERROR;
}
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p,after;
    if(L->next==NULL)
        return ERROR;
    for(p=L->next,after=p->next;after!=NULL;p=p->next,after=after->next){
        if(p->data==e){
            next=after->data;
            return OK;
        }
    }
    if(p->data==e)
        return -5;
    return ERROR;
}
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList pre,p;
    int num=1;
    if(L->next==NULL){
        LinkList p1;
        p1=(LinkList)malloc(sizeof(LNode));
        p1->data=e;
        L->next=p1;
        p1->next=NULL;
        return OK;
    }
    for(p=L->next,pre=L;p!=NULL;p=p->next,pre=pre->next,num++){
        if(num==i){
            LinkList p1;
            p1=(LinkList)malloc(sizeof(LNode));
            p1->data=e;
            pre->next=p1;
            p1->next=p;
            return OK;
        }
    }
    if(num==i){
        LinkList p1;
            p1=(LinkList)malloc(sizeof(LNode));
            p1->data=e;
            pre->next=p1;
            p1->next=NULL;
            return OK;
    }
    return ERROR;
}
status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList pre,p;
    pre=L;
    p=L->next;
    int num=1;
    if(i<1)
        return ERROR;
    while(num!=i&&p->next!=NULL){
        pre=pre->next;
        p=p->next;
        num++;
    }
    if(num==i){
        e=p->data;
        pre->next=p->next;
        free(p);
        p=NULL;
        return OK;
    }
    else
        return ERROR;
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList p=L->next;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL){
        return INFEASIBLE;}
    FILE *fp;
    fp=fopen(FileName,"w");
    LinkList p;
    p=L->next;
    while(p){
        fprintf(fp,"%d ",p->data);
        p=p->next;
    }
    fclose(fp);
    return OK;
}
status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList cur=L;
    int e;
    FILE *fp;
    fp=fopen(FileName,"r");
    while(fscanf(fp,"%d",&e)!=EOF){
        LinkList p;
        p=(LinkList)malloc(sizeof(LNode));
        p->data=e;
        cur->next=p;
        cur=p;
    }
    cur->next=NULL;
    fclose(fp);
    return OK;
}
status reverseList(LinkList &L)
//初始条件是线性表L已存在；操作结果是将L翻转；
{
    if(L==NULL)
        return INFEASIBLE;
    LinkList head,tail=NULL,p=L->next,p1;
    while(p){
        head=(LinkList)malloc(sizeof(LNode));
        head->data=p->data;
        head->next=tail;
        tail=head;
        p1=p;
        p=p->next;
        free(p1);
    }
    L->next=head;
    return OK;
}
status RemoveNthFromEnd(LinkList &L,int n)
//初始条件是线性表L已存在且非空, 操作结果是该链表中倒数第n个节点；
{
    if(L==NULL)
        return INFEASIBLE;
    int l=ListLength(L);
    if(n>l||n<=0)
        return ERROR;
    LinkList last=L,p=L->next;
    for(int i=1;i<l-n+1;i++){
        last=last->next;
        p=p->next;
    }
    last->next=p->next;
    free(p);
    return OK;
}
status sortList(LinkList &L){//由小到大排列
    int t;
    LinkList p,tail,head=L->next;
    for(tail=NULL;head!=tail;tail=p){
        for(p=L->next;p->next!=tail;p=p->next){
            if(p->data>p->next->data){
                t=p->data;
                p->data=p->next->data;
                p->next->data=t;
            }
        }
    }
    return OK;
}
status AddList(LinkList &L,char ListName[]){
    Lists.elem[Lists.length].L=L;
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.length++;
    return OK;
}
status RemoveList(LISTS &Lists,char ListName[]){
    int i;
    for(i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){
            //printf("1");
            LinkList L=Lists.elem[i].L;
            DestroyList(L);
            for(int j=i;j<Lists.length;j++)
                Lists.elem[j]=Lists.elem[j+1];
            Lists.length--;
            return OK;
            }
        }
        return ERROR;
}
int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int i;
        for(i=0;i<Lists.length;i++){
            if(strcmp(Lists.elem[i].name,ListName)==0){
                return i+1;
            }
        }
        return ERROR;
}
int main(){
    int op=1;
    Lists.listsize=10;
   while(op){
       system("cls");    printf("\n\n");
       printf("      Menu for Link List On Sequence Structure \n");
       printf("-------------------------------------------------\n");
       printf("           0. exit                11. ListDelete\n");
       printf("           1. InitList            12. ListTraverse \n");
       printf("           2. DestroyList         13. saveList\n");
       printf("           3. ClearList           14. loadList\n");
       printf("           4. ListEmpty           15. reverseList\n");
       printf("           5. ListLength          16. RemoveNthFromEnd\n");
       printf("           6. GetElem             17. sortList\n");
       printf("           7. LocateElem          18. AddList\n");
       printf("           8. PriorElem           19. RemoveList\n");
       printf("           9. NextElem            20. LocateList\n");
       printf("           10. ListInsert         21. switchList\n");
       printf("          \n");
       printf("-------------------------------------------------\n");
       printf("    请选择你的操作[0~21]:");
       scanf("%d",&op);
       switch(op){
            case 0:
               break;
           case 1:{
                if(InitList(L)==OK) printf("单链表创建成功！\n");
                else printf("单链表创建失败！\n");
                getchar();getchar();
               break;}
           case 2:{
                if(DestroyList(L)==OK) printf("单链表删除成功！\n");
                else printf("单链表删除失败! \n");
                getchar();getchar();
               break;}
           case 3:{
                if(ClearList(L)==OK) printf("单链表清空成功！\n");
                else printf("单链表清空失败! \n");
                getchar();getchar();
               break;}
           case 4:{
               int j=ListEmpty(L);
                if(j==TRUE) printf("单链表为空！\n");
                else if(j==FALSE) printf("单链表非空！\n");
                else printf("单链表不存在！\n");
                getchar();getchar();
               break;}
           case 5:{
               int changdu=ListLength(L);
               if(changdu>=0) printf("单链表的长度为:%d \n",changdu);
               else printf("单链表不存在！\n");
               getchar();getchar();
               break;}
           case 6:{
                int i,e,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
                printf("请输入要获取单链表的第几个元素: \n");
                scanf("%d",&i);
                j=GetElem(L,i,e);
                if(j==OK) printf("单链表的第%d个元素为：%d \n",i,e);
                else if(j==ERROR) printf("单链表中不存在第%d个元素 \n",i);
                else if(j==INFEASIBLE) printf("单链表不存在! \n");
                getchar();getchar();
               break;}
           case 7:{
               int e,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               printf("请输入要查找的元素：\n");
               scanf("%d",&e);
               j=LocateElem(L,e);
               if(j==INFEASIBLE) printf("单链表不存在! \n");
               else if(j==ERROR) printf("元素%d不在单链表中! \n",e);
               else printf("元素%d在单链表中的位置为%d \n",e,j);
               getchar();getchar();
               break;}
           case 8:{
               int pre,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               printf("请输入要获取其前驱元素的元素的值: \n");
               int e;
               scanf("%d",&e);
               j=PriorElem(L,e,pre);
               if(j==INFEASIBLE) printf("单链表不存在！ \n");
               else if(j==-5) printf("%d为单链表首元素，其前驱元素不存在! \n",e);
               else if(j==ERROR) printf("%d不在单链表中！\n",e);
               else printf("%d在单链表中的前驱元素为:%d \n",e,pre);
               getchar();getchar();
               break;}
           case 9:{
               int next,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               printf("请输入要获取其后继元素的元素的值: \n");
               int e;
               scanf("%d",&e);
               j=NextElem(L,e,next);
               if(j==INFEASIBLE) printf("单链表不存在！ \n");
               else if(j==-5) printf("%d为单链表尾元素，其后继元素不存在! \n",e);
               else if(j==ERROR) printf("%d不在单链表中！\n",e);
               else printf("%d在单链表中的后继元素为:%d \n",e,next);
               getchar();getchar();
               break;}
            case 10:
               int j;//将元素e插入到线性表L的第i个元素之前
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               printf("请输入要插入的元素: \n");
               int e;
               scanf("%d",&e);
               printf("请输入要将元素插在哪一个元素之前: \n");
               int i;
               scanf("%d",&i);
               j=ListInsert(L,i,e);
               if(j==INFEASIBLE) printf("单链表不存在！\n");
               if(j==ERROR) printf("第%d个元素不在线性表中! \n",i);
               if(j==OK) printf("插入元素成功！ \n");
               getchar();getchar();
               break;
           case 11:{
               int j,i,e;//删除线性表L的第i个元素，并保存在e中，返回OK
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               printf("请输入要删除的元素在单链表中的位置: \n");
               scanf("%d",&i);
               j=ListDelete(L,i,e);
               if(j==INFEASIBLE) printf("单链表不存在! \n");
               if(j==ERROR) printf("第%d个元素不在单链表中! \n",i);
               if(j==OK) printf("删除成功\t被删除元素为%d \n",e);
               getchar();getchar();
               break;}
           case 12:{
               if(ListTraverse(L)==INFEASIBLE) printf("单链表不存在！\n");
               getchar();getchar();
               break;}
           case 13:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               printf("请输入要读入的文件名：\n");
               char FileName[30];
               scanf("%s",FileName);
               j=SaveList(L,FileName);
               if(j==INFEASIBLE) printf("单链表不存在! \n");
               if(j==ERROR) printf("打开文件失败！\n");
               if(j==OK) printf("读入成功！ \n");
                getchar();getchar();
                break;
           }
           case 14:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE){
                   printf("单链表不存在！\n");
                   getchar();getchar();
                   break;
               }
               printf("请输入要打开的文件名：\n");
               char FileName[30];
               scanf("%s",FileName);
               j=LoadList(L,FileName);
               if(j==INFEASIBLE) printf("单链表已存在! \n");
               if(j==ERROR) printf("打开文件失败！\n");
               if(j==OK) printf("读出成功！ \n");
               getchar();getchar();
               break;
           }
           case 15:{
               int j=reverseList(L);
               if(j==INFEASIBLE)
                   printf("单链表不存在! \n");
               else if(j==OK)
                   printf("单链表翻转成功！\n");
               getchar();getchar();
               break;
           }
           case 16:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               printf("请输出要删除倒数第几个数据: ");
               int n;
               scanf("%d",&n);
               j=RemoveNthFromEnd(L,n);
               if(j==ERROR)
                   printf("第%d个数据不在单链表中！\n",n);
               else if(j==OK)
                   printf("删除成功！\n");
               getchar();getchar();
               break;
           }
           case 17:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("单链表不存在! \n");
                   getchar();getchar();
                   break;
               }
               j=sortList(L);
               if(j==OK) printf("单链表从小到大排序成功！\n");
               getchar();getchar();
               break;
           }
           case 18:{
               char name[30];
            //    int j;
            //    j=ListEmpty(L);
            //    if(j==INFEASIBLE){
            //        printf("单链表不存在! \n");
            //        getchar();getchar();
            //        break;
            //    }
               printf("请输入要添加的单链表的名称：\n");
               scanf("%s",name);
               LinkList temp;
               temp =(LinkList)malloc(sizeof(LNode));
               temp->next=NULL;
               j=AddList(temp,name);
               if(j==OK){
                   printf("添加成功!\n");
                   getchar();getchar();
                   break;
               }
           }
           case 19:{
               printf("请输入要删除的单链表的名称：\n");
               char name[30];
               scanf("%s",name);
               int j;
               j=RemoveList(Lists,name);
               if(j==OK){
                   printf("删除成功！\n");
                   getchar();getchar();
                   break;
               }
               if(j==ERROR){
                   printf("名称为%s的单链表不存在！\n",name);
                   getchar();getchar();
                   break;
               }
           }
           case 20:{
               int j;
               printf("请输入要查找的单链表的名称：\n");
               char name[30];
               scanf("%s",name);
               j=LocateList(Lists,name);
               if(j==ERROR){
                   printf("名称为%s的单链表不存在！\n",name);
                   getchar();getchar();
                   break;
               }
               if(j){
                   printf("名称为%s的单链表的位置为%d",name,j);
                   getchar();getchar();
                   break;
               }
           }
           case 21:{
               printf("请输出要切换的单链表的名称: \n");
               char name[30];
               scanf("%s",name);
               int j;
               j=LocateList(Lists,name);
               printf("%d",j);
               if(j==ERROR){
                   printf("名称为%s的单链表不存在！\n",name);
                   getchar();getchar();
                   break;
               }
               if(j){
                   int m;
                   L=Lists.elem[j-1].L;
                   printf("单链表切换成功！\n");
                   getchar();getchar();
                   break;
               }
           }
       }//end of switch
     }//end of while
   printf("欢迎下次再使用本系统！\n");
   }//end of main()









