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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //���Ա�Ĺ������
     struct { char name[30];
               LinkList L;
      } elem[10];
    int length;//������ĳ���
    int listsize;
 }LISTS;
LinkList L;
LISTS Lists;
status InitList(LinkList &L);
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
status DestroyList(LinkList &L);
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
status ClearList(LinkList &L);
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
status ListEmpty(LinkList L);
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
int ListLength(LinkList L);
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
status GetElem(LinkList L,int i,ElemType &e);
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
status LocateElem(LinkList L,ElemType e);
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
status PriorElem(LinkList L,ElemType e,ElemType &pre);
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
status NextElem(LinkList L,ElemType e,ElemType &next);
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
status ListInsert(LinkList &L,int i,ElemType e);
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
status ListDelete(LinkList &L,int i,ElemType &e);
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
status ListTraverse(LinkList L);
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
status SaveList(LinkList L,char FileName[]);
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
status LoadList(LinkList &L,char FileName[]);
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
status reverseList(LinkList &L);
//��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L��ת��
status RemoveNthFromEnd(LinkList &L,int n);
//��ʼ���������Ա�L�Ѵ����ҷǿ�, ���������ɾ���������е�����n���ڵ㣻
status sortList(LinkList &L);
//��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L��С��������
status AddList(LISTS &Lists,char ListName[]);
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
status RemoveList(LISTS &Lists,char ListName[]);
// Lists��ɾ��һ������ΪListName�����Ա�
int LocateList(LISTS Lists,char ListName[]);
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L==NULL)
        return INFEASIBLE;
    if(L->next==NULL)
        return TRUE;
    else
        return FALSE;
}
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
//��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L��ת��
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
//��ʼ���������Ա�L�Ѵ����ҷǿ�, ��������Ǹ������е�����n���ڵ㣻
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
status sortList(LinkList &L){//��С��������
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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
       printf("    ��ѡ����Ĳ���[0~21]:");
       scanf("%d",&op);
       switch(op){
            case 0:
               break;
           case 1:{
                if(InitList(L)==OK) printf("���������ɹ���\n");
                else printf("��������ʧ�ܣ�\n");
                getchar();getchar();
               break;}
           case 2:{
                if(DestroyList(L)==OK) printf("������ɾ���ɹ���\n");
                else printf("������ɾ��ʧ��! \n");
                getchar();getchar();
               break;}
           case 3:{
                if(ClearList(L)==OK) printf("��������ճɹ���\n");
                else printf("���������ʧ��! \n");
                getchar();getchar();
               break;}
           case 4:{
               int j=ListEmpty(L);
                if(j==TRUE) printf("������Ϊ�գ�\n");
                else if(j==FALSE) printf("������ǿգ�\n");
                else printf("���������ڣ�\n");
                getchar();getchar();
               break;}
           case 5:{
               int changdu=ListLength(L);
               if(changdu>=0) printf("������ĳ���Ϊ:%d \n",changdu);
               else printf("���������ڣ�\n");
               getchar();getchar();
               break;}
           case 6:{
                int i,e,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
                printf("������Ҫ��ȡ������ĵڼ���Ԫ��: \n");
                scanf("%d",&i);
                j=GetElem(L,i,e);
                if(j==OK) printf("������ĵ�%d��Ԫ��Ϊ��%d \n",i,e);
                else if(j==ERROR) printf("�������в����ڵ�%d��Ԫ�� \n",i);
                else if(j==INFEASIBLE) printf("����������! \n");
                getchar();getchar();
               break;}
           case 7:{
               int e,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               printf("������Ҫ���ҵ�Ԫ�أ�\n");
               scanf("%d",&e);
               j=LocateElem(L,e);
               if(j==INFEASIBLE) printf("����������! \n");
               else if(j==ERROR) printf("Ԫ��%d���ڵ�������! \n",e);
               else printf("Ԫ��%d�ڵ������е�λ��Ϊ%d \n",e,j);
               getchar();getchar();
               break;}
           case 8:{
               int pre,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               printf("������Ҫ��ȡ��ǰ��Ԫ�ص�Ԫ�ص�ֵ: \n");
               int e;
               scanf("%d",&e);
               j=PriorElem(L,e,pre);
               if(j==INFEASIBLE) printf("���������ڣ� \n");
               else if(j==-5) printf("%dΪ��������Ԫ�أ���ǰ��Ԫ�ز�����! \n",e);
               else if(j==ERROR) printf("%d���ڵ������У�\n",e);
               else printf("%d�ڵ������е�ǰ��Ԫ��Ϊ:%d \n",e,pre);
               getchar();getchar();
               break;}
           case 9:{
               int next,j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               printf("������Ҫ��ȡ����Ԫ�ص�Ԫ�ص�ֵ: \n");
               int e;
               scanf("%d",&e);
               j=NextElem(L,e,next);
               if(j==INFEASIBLE) printf("���������ڣ� \n");
               else if(j==-5) printf("%dΪ������βԪ�أ�����Ԫ�ز�����! \n",e);
               else if(j==ERROR) printf("%d���ڵ������У�\n",e);
               else printf("%d�ڵ������еĺ��Ԫ��Ϊ:%d \n",e,next);
               getchar();getchar();
               break;}
            case 10:
               int j;//��Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               printf("������Ҫ�����Ԫ��: \n");
               int e;
               scanf("%d",&e);
               printf("������Ҫ��Ԫ�ز�����һ��Ԫ��֮ǰ: \n");
               int i;
               scanf("%d",&i);
               j=ListInsert(L,i,e);
               if(j==INFEASIBLE) printf("���������ڣ�\n");
               if(j==ERROR) printf("��%d��Ԫ�ز������Ա���! \n",i);
               if(j==OK) printf("����Ԫ�سɹ��� \n");
               getchar();getchar();
               break;
           case 11:{
               int j,i,e;//ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               printf("������Ҫɾ����Ԫ���ڵ������е�λ��: \n");
               scanf("%d",&i);
               j=ListDelete(L,i,e);
               if(j==INFEASIBLE) printf("����������! \n");
               if(j==ERROR) printf("��%d��Ԫ�ز��ڵ�������! \n",i);
               if(j==OK) printf("ɾ���ɹ�\t��ɾ��Ԫ��Ϊ%d \n",e);
               getchar();getchar();
               break;}
           case 12:{
               if(ListTraverse(L)==INFEASIBLE) printf("���������ڣ�\n");
               getchar();getchar();
               break;}
           case 13:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               printf("������Ҫ������ļ�����\n");
               char FileName[30];
               scanf("%s",FileName);
               j=SaveList(L,FileName);
               if(j==INFEASIBLE) printf("����������! \n");
               if(j==ERROR) printf("���ļ�ʧ�ܣ�\n");
               if(j==OK) printf("����ɹ��� \n");
                getchar();getchar();
                break;
           }
           case 14:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE){
                   printf("���������ڣ�\n");
                   getchar();getchar();
                   break;
               }
               printf("������Ҫ�򿪵��ļ�����\n");
               char FileName[30];
               scanf("%s",FileName);
               j=LoadList(L,FileName);
               if(j==INFEASIBLE) printf("�������Ѵ���! \n");
               if(j==ERROR) printf("���ļ�ʧ�ܣ�\n");
               if(j==OK) printf("�����ɹ��� \n");
               getchar();getchar();
               break;
           }
           case 15:{
               int j=reverseList(L);
               if(j==INFEASIBLE)
                   printf("����������! \n");
               else if(j==OK)
                   printf("������ת�ɹ���\n");
               getchar();getchar();
               break;
           }
           case 16:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               printf("�����Ҫɾ�������ڼ�������: ");
               int n;
               scanf("%d",&n);
               j=RemoveNthFromEnd(L,n);
               if(j==ERROR)
                   printf("��%d�����ݲ��ڵ������У�\n",n);
               else if(j==OK)
                   printf("ɾ���ɹ���\n");
               getchar();getchar();
               break;
           }
           case 17:{
               int j;
               j=ListEmpty(L);
               if(j==INFEASIBLE) {
                   printf("����������! \n");
                   getchar();getchar();
                   break;
               }
               j=sortList(L);
               if(j==OK) printf("�������С��������ɹ���\n");
               getchar();getchar();
               break;
           }
           case 18:{
               char name[30];
            //    int j;
            //    j=ListEmpty(L);
            //    if(j==INFEASIBLE){
            //        printf("����������! \n");
            //        getchar();getchar();
            //        break;
            //    }
               printf("������Ҫ��ӵĵ���������ƣ�\n");
               scanf("%s",name);
               LinkList temp;
               temp =(LinkList)malloc(sizeof(LNode));
               temp->next=NULL;
               j=AddList(temp,name);
               if(j==OK){
                   printf("��ӳɹ�!\n");
                   getchar();getchar();
                   break;
               }
           }
           case 19:{
               printf("������Ҫɾ���ĵ���������ƣ�\n");
               char name[30];
               scanf("%s",name);
               int j;
               j=RemoveList(Lists,name);
               if(j==OK){
                   printf("ɾ���ɹ���\n");
                   getchar();getchar();
                   break;
               }
               if(j==ERROR){
                   printf("����Ϊ%s�ĵ��������ڣ�\n",name);
                   getchar();getchar();
                   break;
               }
           }
           case 20:{
               int j;
               printf("������Ҫ���ҵĵ���������ƣ�\n");
               char name[30];
               scanf("%s",name);
               j=LocateList(Lists,name);
               if(j==ERROR){
                   printf("����Ϊ%s�ĵ��������ڣ�\n",name);
                   getchar();getchar();
                   break;
               }
               if(j){
                   printf("����Ϊ%s�ĵ������λ��Ϊ%d",name,j);
                   getchar();getchar();
                   break;
               }
           }
           case 21:{
               printf("�����Ҫ�л��ĵ����������: \n");
               char name[30];
               scanf("%s",name);
               int j;
               j=LocateList(Lists,name);
               printf("%d",j);
               if(j==ERROR){
                   printf("����Ϊ%s�ĵ��������ڣ�\n",name);
                   getchar();getchar();
                   break;
               }
               if(j){
                   int m;
                   L=Lists.elem[j-1].L;
                   printf("�������л��ɹ���\n");
                   getchar();getchar();
                   break;
               }
           }
       }//end of switch
     }//end of while
   printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
   }//end of main()









