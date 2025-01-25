#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define inf 999999
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
        int adjvex;              //顶点位置编号
     struct ArcNode  *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode{                //头结点及其数组类型定义
        VertexType data;           //顶点信息
     ArcNode *firstarc;           //指向第一条弧
    } VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;          //头结点数组
    int vexnum,arcnum;         //顶点数、弧数
    GraphKind  kind;        //图的类型
   } ALGraph;
ALGraph G;
typedef struct{  //二叉树的管理表定义
     struct { char name[30];
         ALGraph G;
      } elem[10];
    int length;//多链表的长度
    int listsize;
 }GRAPHS;
GRAPHS Graphs;
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
//VR存放弧，V存放顶点
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    if(V[0].key==-1)
        return ERROR;
    G.kind={UDG};
    int judge[100];
    int judge2[30][30];
    int i,j,k,flag;
    for(i=0;i<100;i++)
        judge[i]=0;
    for(i=0;i<30;i++)
        for(j=0;j<30;j++)
            judge2[i][j]=0;
    G.vexnum=0;
    for(i=0;V[i].key!=-1;i++){
        if(i>=20)
            return ERROR;
        G.vexnum++;
        if(judge[V[i].key]==0)
            judge[V[i].key]++;
        else
            return ERROR;
        G.vertices[i].data=V[i];
        G.vertices[i].firstarc=NULL;
    }//存顶点
    G.arcnum=0;
    for(i=0;VR[i][0]!=-1;i++){
        G.arcnum++;
        if(judge2[VR[i][0]][VR[i][1]]==0||judge2[VR[i][1]][VR[i][0]]==0){
            judge2[VR[i][0]][VR[i][1]]++;
            judge2[VR[i][1]][VR[i][0]]++;
        }
        else
            continue;
        if(VR[i][1]==VR[i][0])
            continue;
        flag=0;
        for(j=0;j<G.vexnum;j++){//找到第一个顶点
            if(G.vertices[j].data.key==VR[i][0]){
                flag++;
                for(k=0;k<G.vexnum;k++){//找到第二个顶点
                    if(G.vertices[k].data.key==VR[i][1]){
                        ArcNode *p;
                        p=(ArcNode *)malloc(sizeof(ArcNode));
                        p->adjvex=k;
                        ArcNode *t;
                        t=G.vertices[j].firstarc;
                        G.vertices[j].firstarc=p;
                        p->nextarc=t;
                        break;
                    }
                }
            }
            if(G.vertices[j].data.key==VR[i][1]){
                flag++;
                for(k=0;k<G.vexnum;k++){
                    if(G.vertices[k].data.key==VR[i][0]){
                        ArcNode *p;
                        p=(ArcNode *)malloc(sizeof(ArcNode));
                        p->adjvex=k;
                        ArcNode *t;
                        t=G.vertices[j].firstarc;
                        G.vertices[j].firstarc=p;
                        p->nextarc=t;
                        break;
                    }
                }
            }
        }
        if(flag!=2){
            return ERROR;
        }
    }
    return OK;
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    int i;
    if(G.vertices[0].firstarc==NULL)
        return ERROR;
    ArcNode *p,*p1;
    for(i=0;i<G.vexnum;i++){
        p=G.vertices[i].firstarc;
        while(p!=NULL){
            p1=p->nextarc;
            free(p);
            p=p1;
        }
        G.vertices[i].firstarc=NULL;
    }
    G.arcnum=0;
    G.vexnum=0;
    return OK;
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    int i;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u){
            return  i;
        }
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    int i;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key == u){
            continue;
        }
        if(G.vertices[i].data.key==value.key){
            return ERROR;
        }
    }
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u){
            G.vertices[i].data=value;
            return  OK;
        }
    }
    return ERROR;
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int i;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u){
            if(G.vertices[i].firstarc)
                return G.vertices[i].firstarc->adjvex;
        }
    }
    return -1;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    int i;
    int j;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==w)
            j=i;
    }
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v){
            ArcNode *p=G.vertices[i].firstarc;
            while(p){
                if(p->adjvex==j){
                    if(p->nextarc==NULL)
                        return -1;
                    else
                        return p->nextarc->adjvex;
                }
                else
                    p=p->nextarc;
            }
            return -1;
        }
    }
    return -1;
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    int i;
    for(i=0;i<G.vexnum;i++)
        if(G.vertices[i].data.key==v.key)
            return ERROR;
    if(i>=20)
        return ERROR;
    G.vertices[G.vexnum].data=v;
    G.vertices[G.vexnum].firstarc=NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    int i,j=-1;
    if(G.vexnum==1&&G.vertices[0].data.key==v)
        return ERROR;
    ArcNode *p,*last,*p1;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v){
            j=i;
            break;
        }
    }
    if(j==-1)
        return ERROR;
    p=G.vertices[i].firstarc;
    while(p){
        p1=p->nextarc;
        G.arcnum--;
        free(p);
        p=p1;
    }
    for(;i<G.vexnum;i++){
        G.vertices[i]=G.vertices[i+1];
    }
    G.vexnum--;
    for(i=0;i<G.vexnum;i++){
    p=G.vertices[i].firstarc;
    if(p==NULL)
        continue;
    if(p->adjvex==j){
        G.vertices[i].firstarc=p->nextarc;
        free(p);
        }
    else{
        last=p;
        p=p->nextarc;
    while(p){
        if(p->adjvex==j){
            last->nextarc=p->nextarc;
            free(p);
            p=last->nextarc;
        }
        else{
            last=p;
            p=p->nextarc;
        }
    }
    }
    }
    for(i=0;i<G.vexnum;i++){
        p=G.vertices[i].firstarc;
        while(p){
            if(p->adjvex>j)
                p->adjvex--;
            p=p->nextarc;
        }
    }
    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    int i,j1,j2,flag=0;
    ArcNode *p1,*p2;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v){
            j1=i;
            flag=1;
            break;
        }
    }
    if(flag==0)
        return ERROR;
    flag=0;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==w){
            j2=i;
            flag=1;
            break;
        }
    }
    if(flag==0)
        return ERROR;
    G.arcnum++;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v){
            p2=G.vertices[i].firstarc;
            while(p2){
                if(p2->adjvex==j2)
                    return ERROR;
                p2=p2->nextarc;
            }
            ArcNode *p;
            p=(ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex=j2;
            p1=G.vertices[i].firstarc;
            G.vertices[i].firstarc=p;
            p->nextarc=p1;
        }
    }
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==w){
            p2=G.vertices[i].firstarc;
            while(p2){
                if(p2->adjvex==j1)
                    return ERROR;
                p2=p2->nextarc;
            }
            ArcNode *p;
            p=(ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex=j1;
            p1=G.vertices[i].firstarc;
            G.vertices[i].firstarc=p;
            p->nextarc=p1;
        }
    }
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    int i,j1,j2,flag=0;
    ArcNode *p1,*p;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==v){
            j1=i;
            flag=1;
            break;
        }
    }
    if(flag==0)
        return ERROR;
    flag=0;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==w){
            j2=i;
            flag=1;
            break;
        }
    }
    if(flag==0)
        return ERROR;
    G.arcnum--;
    for(i=0;i<G.vexnum;i++){
        flag=0;
        if(G.vertices[i].data.key==v){
            if(G.vertices[i].firstarc->adjvex==j2){
                p=G.vertices[i].firstarc;
                G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
                flag=1;
                free(p);
                break;}
            p1=G.vertices[i].firstarc;
            p=p1->nextarc;
            while(p){
                if(p->adjvex==j2){
                    p1->nextarc=p->nextarc;
                    free(p);
                    flag=1;
                    break;
                }
                else{
                    p1=p;
                    p=p->nextarc;
                }
            }
            if(flag==0)
                return ERROR;
        }
    }
    for(i=0;i<G.vexnum;i++){
        flag=0;
        if(G.vertices[i].data.key==w){
            if(G.vertices[i].firstarc->adjvex==j1){
                flag=1;
                p=G.vertices[i].firstarc;
                G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
                free(p);
                break;}
            p1=G.vertices[i].firstarc;
            p=p1->nextarc;
            while(p){
                if(p->adjvex==j1){
                    p1->nextarc=p->nextarc;
                    free(p);
                    flag=1;
                    break;
                }
                else{
                    p1=p;
                    p=p->nextarc;
                }
            }
            if(flag==0)
                return ERROR;
        }
    }
    return OK;
}

int judge[20],flag=0;
void dfs(ALGraph  G,ArcNode *p,void (*visit)(VertexType)){
    if(p==NULL)
        return ;
    do{
    if(judge[p->adjvex]==0){
        judge[p->adjvex]++;
        visit(G.vertices[p->adjvex].data);
        dfs(G,G.vertices[p->adjvex].firstarc,visit);
        }
        p=p->nextarc;
    }while(p);
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int i,count=0;
    for(i=0;i<20;i++)
        judge[i]=0;
    for(i=0;i<G.vexnum;i++){
        if(judge[i]==0){
            count++;
            visit(G.vertices[i].data);
            judge[i]=1;
            dfs(G,G.vertices[i].firstarc,visit);
        }
    }
    return count;
}

int judge1[20];
struct{
    int pos[100];
    int head,tail;
}q;
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int i;
    q.head=q.tail=0;
    for(i=0;i<100;i++)
        q.pos[i]=0;
    for(i=0;i<G.vexnum;i++){
        if(judge1[i]==0){
    visit(G.vertices[i].data);
    judge1[i]++;
    q.pos[q.tail++]=0;//顶点的位置序号
    while(q.head<q.tail){
        ArcNode *p;
        p=G.vertices[q.head].firstarc;
        if(p&&judge1[p->adjvex]==0){
            judge1[p->adjvex]++;
            visit(G.vertices[p->adjvex].data);
            q.pos[q.tail++]=p->adjvex;
            while(p){
                if(judge1[p->adjvex]==0){
                    visit(G.vertices[p->adjvex].data);
                    q.pos[q.tail++]=p->adjvex;
                    judge1[p->adjvex]++;
                }
                p=p->nextarc;
            }
        }
        q.head++;
    }
    }
    }
    return 0;
}

int count=0;
int judge2[20];
struct{
    int pos[100];
    int head,tail;
}q2;
status VerticesSetLessThanK(ALGraph G,int v,int k)
//初始条件是图G存在；操作结果是返回与顶点v距离小于k的顶点集合；
{
    int i;
    for(i=0;i<20;i++)
        judge2[i]=0;
    q2.head=q2.tail=0;
    for(i=0;i<100;i++)
        q2.pos[i]=0;
    for(i=0;i<G.vexnum;i++){
        if(judge2[i]==0){
    visit(G.vertices[i].data);
    judge2[i]++;
    q2.pos[q2.tail++]=0;//顶点的位置序号
    while(q2.head<q2.tail&&count<k){
        ArcNode *p;
        p=G.vertices[q2.head].firstarc;
        if(judge2[p->adjvex]==0){
            judge2[p->adjvex]++;
            visit(G.vertices[p->adjvex].data);
            q2.pos[q2.tail++]=p->adjvex;
            while(p){
                if(judge2[p->adjvex]==0){
                    visit(G.vertices[p->adjvex].data);
                    q2.pos[q.tail++]=p->adjvex;
                    judge2[p->adjvex]++;
                }
                p=p->nextarc;
            }
            count++;
        }
        q2.head++;
    }
            if(count>=k)
                return OK;
    }
    }
    return 0;
}

status ShortestPathLength(ALGraph G,int v,int w){
    int i,j,k;
    int block[30][30];
    for(i=0;i<30;i++)
        for(j=0;j<30;j++)
            block[i][j]=inf;
    int x,y;
    for(i=0;i<G.vexnum;i++)
        if(G.vertices[i].data.key==v)
            x=i;
    for(i=0;i<G.vexnum;i++)
        if(G.vertices[i].data.key==w)
            y=i;
    for(i=0;i<G.vexnum;i++){
        ArcNode *p;
        p=G.vertices[i].firstarc;
        while(p){
            block[i][p->adjvex]=block[p->adjvex][i]=1;
            p=p->nextarc;
        }
    }
    for(k=0;k<G.vexnum;k++){
        for(i=0;i<G.vexnum;i++){
            for(j=0;j<G.vexnum;j++){
                if(block[i][j]>block[i][k]+block[k][j])
                    block[i][j]=block[j][i]=block[i][k]+block[k][j];
            }
        }
    }
    return block[x][y];
}

void dfs1(ALGraph  G,ArcNode *p,void (*visit)(VertexType)){
    if(p==NULL)
        return ;
    do{
    if(judge[p->adjvex]==0){
        judge[p->adjvex]++;
        dfs1(G,G.vertices[p->adjvex].firstarc,visit);
        }
        p=p->nextarc;
    }while(p);
}

status DFSTraverse1(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int i,count=0;
    for(i=0;i<20;i++)
        judge[i]=0;
    for(i=0;i<G.vexnum;i++){
        if(judge[i]==0){
            count++;
            judge[i]=1;
            dfs1(G,G.vertices[i].firstarc,visit);
        }
    }
    return count;
}

status ConnectedComponentsNums(ALGraph G){
    int i=0;
    for(i=0;i<20;i++)
        judge[i]=0;
    i=DFSTraverse1(G,visit);
    return i;
}

status AddGraph(ALGraph G,char ListName[]){
    Graphs.elem[Graphs.length].G=G;
    strcpy(Graphs.elem[Graphs.length].name,ListName);
    Graphs.length++;
    return OK;
}

status RemoveGraph(ALGraph &Lists,char ListName[]){
    int i;
    for(i=0;i<Graphs.length;i++){
        if(strcmp(Graphs.elem[i].name,ListName)==0){
            ALGraph G=Graphs.elem[i].G;
            DestroyGraph(G);
            for(int j=i;j<Graphs.length;j++)
                Graphs.elem[j]=Graphs.elem[j+1];
            Graphs.length--;
            return OK;
            }
        }
        return ERROR;
}

int LocateGraph(GRAPHS Graphs,char ListName[])
{
    int i;
        for(i=0;i<Graphs.length;i++){
            if(strcmp(Graphs.elem[i].name,ListName)==0){
                return i+1;
            }
        }
        return ERROR;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp;
    fp=fopen(FileName,"w");
    int i,j=0;
    for(i=0;i<G.vexnum;i++){
        fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
    }
    fprintf(fp,"-1 nil ");
    for(i=0;i<G.vexnum;i++){
        ArcNode *p;
        p=G.vertices[i].firstarc;
        while(p){
            fprintf(fp,"%d %d ",i,p->adjvex);
            p=p->nextarc;
        }
    }
    fprintf(fp,"-1 -1 ");
    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    FILE *fp;
    G.vexnum=0;
    G.arcnum=0;
    fp=fopen(FileName,"r");
    int a,b;
    int i=0,j;
    int key;
    char str[30];
    do {
        fscanf(fp,"%d %s",&key,str);
        if(key!=-1){
            G.vertices[i].data.key=key;
            strcpy(G.vertices[i].data.others,str);
            G.vertices[i].firstarc=NULL;
            G.vexnum++;
            i++;
        }
    } while(key!=-1);
    i=-1;
    fscanf(fp,"%d %d",&a,&b);
    j=-2;
    ArcNode *last;
    while(a!=-1){
        ArcNode *p;
        if(a==j){
            p=(ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex=b;
            p->nextarc=NULL;
            G.arcnum++;
            last->nextarc=p;
            last=p;
        }
        else{
            i++;
            p=(ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex=b;
            p->nextarc=NULL;
            G.arcnum++;
            G.vertices[i].firstarc=p;
            last=p;
        }
        j=a;
        fscanf(fp,"%d %d",&a,&b);
    }
    G.arcnum/=2;
    return OK;
}





int main(){
    int op=1;
   while(op){
       system("cls");    printf("\n\n");
       printf("      Menu for Adjacency list On Sequence Structure \n");
       printf("-------------------------------------------------\n");
       printf("           0. 退出系统               11. 深度优先搜索遍历 \n");
       printf("           1. 创建图                12. 广度优先搜索遍历 \n");
       printf("           2. 销毁图                13. 距离小于k的顶点集合\n");
       printf("           3. 查找顶点              14. 顶点间最短路径和长度\n");
       printf("           4. 顶点赋值              15. 图的连通分量\n");
       printf("           5. 获得第一邻接点          16. 图读入文件\n");
       printf("           6. 获得下一邻接点          17. 从文件中读出图\n");
       printf("           7. 插入顶点               18. 多图管理：增加一个新图\n");
       printf("           8. 删除顶点               19. 多图管理：移除一个图\n");
       printf("           9. 插入弧                 20. 多图管理：查找图\n");
       printf("           10. 删除弧                21. 图的切换\n");
       printf("          \n");
       printf("-------------------------------------------------\n");
       printf("    请选择你的操作[0~21]:");
       scanf("%d",&op);
       switch(op){
            case 0:
               break;
           case 1:{
               int ans;
               printf("请先输入图的各顶点的关键词以及名称，然后输入顶点之间的关系：\n");
               VertexType V[30];
               KeyType VR[100][2];
               int i=0;
               do {
                   scanf("%d%s",&V[i].key,V[i].others);
               } while(V[i++].key!=-1);
               i=0;
               do {
                   scanf("%d%d",&VR[i][0],&VR[i][1]);
                  } while(VR[i++][0]!=-1);
               ans=CreateCraph(G,V,VR);
               if (ans==OK){
                   printf("图创建成功\n");
               }
               else printf("输入数据错，无法创建\n");
                getchar();getchar();
               break;}
           case 2:{
               int ans;
               ans=DestroyGraph(G);
                if(ans==OK) printf("图销毁成功\n");
                else printf("图销毁失败! \n");
                getchar();getchar();
               break;}
           case 3:{
               int i;
               printf("请输入要查找顶点的关键字：\n");
               int u;
               scanf("%d",&u);
               i=LocateVex(G,u);
               if (i!=-1)
                   printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
               else
                   printf("查找失败");
               getchar();getchar();
               break;}
           case 4:{
               VertexType value;
               int i,u;
               printf("请输入要赋值的顶点的关键字：\n");
               scanf("%d",&u);
               printf("请输入新的关键字以及名称：\n");
               scanf("%d%s",&value.key,value.others);
               i=PutVex(G,u,value);
               if(i==OK)
                   printf("赋值成功！\n");
               else
                   printf("赋值操作失败");
               getchar();getchar();
               break;}
           case 5:{
               int u,i;
               printf("请输入要获得第一邻接点的顶点的关键字：\n");
               scanf("%d",&u);
               i=FirstAdjVex(G,u);
               if (i!=-1)
                   printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
               else
                   printf("查找失败");
               getchar();getchar();
               break;}
           case 6:{
               int i=0,v,w;
               printf("请输入顶点的位序以及与该顶点相连的顶点的关键字以获取其获得下一邻接点: \n");
               scanf("%d%d",&v,&w);
               i=NextAdjVex(G,v,w);
               if (i!=-1)
                   printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
               else
                   printf("无下一邻接顶点");
                   getchar();getchar();
                   break;
                getchar();getchar();
               break;}
           case 7:{
               VertexType v;
               int i;
               printf("请输入要插入新顶点的关键字和名称： \n");
               scanf("%d%s",&v.key,v.others);
               i=InsertVex(G,v);
               if(i==OK)
                   printf("插入顶点成功！\n");
                else
                    printf("插入操作失败");
               getchar();getchar();
               break;}
           case 8:{
               printf("请输入要删除顶点的关键字：\n");
               int v,i;
               scanf("%d",&v);
               i=DeleteVex(G,v);
               if(i==OK)
                   printf("删除顶点成功！\n");
               else
                   printf("删除顶点操作失败");
               getchar();getchar();
               break;}
           case 9:{
               printf("请输入插入的弧的两个顶点的关键字: \n");
               KeyType v,w;
               int i;
               scanf("%d %d",&v,&w);
               i=InsertArc(G,v,w);
               if(i==OK)
                   printf("插入弧成功！");
               else
                   printf("插入弧操作失败");
               getchar();getchar();
               break;}
           case 10:{
               printf("请输入要删除的弧的两个顶点的关键字：\n");
               KeyType v,w;
               int i;
               scanf("%d %d",&v,&w);
               i=DeleteArc(G,v,w);
               if(i==OK)
                   printf("删除弧成功！\n");
               else
                   printf("删除弧操作失败");
               getchar();getchar();
               break;}
           case 11:{
               int i;
               for(i=0;i<20;i++)
                   judge[i]=0;
               DFSTraverse(G,visit);
               getchar();getchar();
               break;}
           case 12:{
               int i;
               for(i=0;i<20;i++)
                   judge1[i]=0;
               BFSTraverse(G,visit);
               getchar();getchar();
               break;}
           case 13:{
               int k;
               count=0;
               printf("请输入顶点的关键字以及距离k\n");
               int v;
               scanf("%d %d",&v,&k);
               VerticesSetLessThanK(G,v,k-1);
                getchar();getchar();
                break;
           }
           case 14:{
               printf("请输入两个顶点的关键字以求其最短路径长度：\n");
               int v,w,i;
               scanf("%d %d",&v,&w);
               i=ShortestPathLength(G,v,w);
               printf("顶点%d与%d之间的最短路径为:%d \n",v,w,i);
                getchar();getchar();
               break;
           }
           case 15:{
               int i;
               i=ConnectedComponentsNums(G);
               printf("图的连通分量的个数为%d\n",i);
               getchar();getchar();
               break;
           }
           case 16:{
               printf("请输入要读出的文件的名称：\n");
               char FileName[20];
               scanf("%s",FileName);
               SaveGraph(G,FileName);
               printf("图读入文件成功！\n");
               getchar();getchar();
               break;
           }
           case 17:{
               printf("请输入要读出的文件的名称：\n");
               if(G.vertices[0].firstarc){
                   printf("图已存在，读出失败！\n");
                   getchar();getchar();
                   break;
               }
               char FileName[30];
               scanf("%s",FileName);
               LoadGraph(G, FileName);
               printf("读出成功！\n");
               getchar();getchar();
               break;
           }
           case 18:{
               printf("请输入要添加的图的名称：\n");
               char Name[30];
               ALGraph G;
               G.vertices[0].firstarc=NULL;
               G.vexnum=0;
               G.arcnum=0;
               scanf("%s",Name);
               AddGraph(G,Name);
               printf("添加成功！\n");
               getchar();getchar();
               break;
           }
           case 19:{
               int j;
               printf("请输入要删除的图的名称: \n");
               char Name[30];
               scanf("%s",Name);
               j=RemoveGraph(G,Name);
               if(j==OK){
                   printf("删除成功！\n");
                   getchar();getchar();
                   break;
               }
               if(j==ERROR){
                   printf("名称为%s的图不存在！\n",Name);
                   getchar();getchar();
                   break;
               }
           }
            case 20:{
                printf("请输入要查找的图的名称：\n");
                char Name[30];
                int i;
                scanf("%s",Name);
                i=LocateGraph(Graphs,Name);
                if(i==ERROR)
                    printf("名称为%s的图不存在",Name);
                else
                    printf("名称为%s的图的位置为：%d",Name,i);
                 getchar();getchar();
                 break;
           }
           case 21:{
               printf("请输入要切换的图的名称：\n");
               int j;
               char Name[30];
               scanf("%s",Name);
               j=LocateGraph(Graphs,Name);
               if(j==ERROR){
                   printf("名称为%s的图不存在！\n",Name);
                   getchar();getchar();
                   break;
               }
               if(j){
                   G=Graphs.elem[j-1].G;
                   printf("图切换成功！\n");
                   getchar();getchar();
                   break;
               }
               getchar();getchar();
               break;
           }
       
       }//end of switch
     }//end of while
   printf("欢迎下次再使用本系统！\n");
   }//end of main()

