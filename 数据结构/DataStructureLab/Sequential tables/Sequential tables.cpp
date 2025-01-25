/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{ //顺序表（顺序结构）的定义
    ElemType *elem;
    int length;
    int listsize;
} SqList;
typedef struct LISTS
{ //线性表的管理表定义
    struct
    {
        char name[30];
        SqList L;
    } elem[10];
    int length;
} LISTS;


FILE *fp;

status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType &e);
int LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType e, ElemType &pre);
status NextElem(SqList L, ElemType e, ElemType &next);
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(SqList L);
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
int maxSubArray(int* nums, int numsSize);
void sortList(SqList &L);
int subarraySum(SqList &L, int k);

/*--------------------------------------------*/
int main(void)
{
    LISTS lists;
    lists.length = 0;
    char filename[40];
    int op = 1;
    int i;
    int i_num = 1;
    SqList L;
    L.elem = NULL;
    L.listsize = 0;
    L.length = 0;
    ElemType e, cur_e, pre_e, next_e;
    while (op)
    {
        /**
         *  菜单
         */
        system("cls"); //用于清屏
        printf("\n\n");
        printf("      \t\t\tMenu for Linear Table On Sequence Structure \n");
        printf("  ------------------------------------------------------------------------------\n");
        printf("**\t\t\t1. InitList\t\t7.  LocateElem\t\t\t**\n");
        printf("**\t\t\t2. DestroyList\t\t8.  PriorElem\t\t\t**\n");
        printf("**\t\t\t3. ClearList\t\t9.  NextElem \t\t\t**\n");
        printf("**\t\t\t4. ListEmpty\t\t10. ListInsert\t\t\t**\n");
        printf("**\t\t\t5. ListLength\t\t11. ListDelete\t\t\t**\n");
        printf("**\t\t\t6. GetElem\t\t12. ListTraverse\t\t**\n");
        printf("**\t\t\t13.SaveList\t\t14. LoadList\t\t\t**\n");
        printf("      \t\t\tMutiple Linears administration\n");
        printf("  ------------------------------------------------------------------------------\n");
        printf("**\t\t\t\t\t多线性表管理\t\t\t\t**\n\n");
        printf("**\t\t\t15.AddList\t\t16. RemoveList\t\t\t**\n");
        printf("**\t\t\t17.LocateList\t\t\t\t\t\t**\n");
        printf("  ------------------------------------------------------------------------------\n");
        printf("**\t\t\t\t\t附加功能\t\t\t\t**\n\n");
        printf("**\t\t\t18.MaxSubArray\t\t19. SubArrayNum\t\t\t**\n");
        printf("**\t\t\t20.sortList\t\t0. Exit\t\t\t\t**\n");
        printf("**\t\t\t本实验已有文件input，可通过函数14进行加载\n");
        printf("  -------------------------------------马耀辉-----------------------------------\n");
        printf("请选择你的操作[0--20]:\n");
        scanf("%d", &op); //选择op的值,用于switch
        switch (op)
        {
        case 1:
            //第一种情况是初始化线性表
            if (InitList(L) == OK)
            {
                printf("线性表创建成功\n");
            }else
                printf("线性表创建失败！\n");
            getchar();
            getchar();
            break;

        case 2:
            //第二种情况是用来销毁线性表
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            if (DestroyList(L) == OK)
            {
                printf("销毁线性表成功!\n");
            }
            else
                printf("销毁线性表失败！\n");
            getchar();
            getchar();
            break;

        case 3:
            //用于重置线性表
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            if (ClearList(L) == OK)
            {
                printf("线性表重置成功！\n");
            }
            else
                printf("线性表重置失败！\n");
            getchar();
            getchar();
            break;

        case 4:
            //判断是否为空
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            if (ListEmpty(L) == TRUE)
            {
                printf("文件为空！\n");
            }
            else
                printf("线性表不是空表！\n");
            getchar();
            getchar();
            break;

        case 5:
            //得到线性表长度
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("线性表表长为%d\n", ListLength(L));
            getchar();
            getchar();
            break;

        case 6:
            //得到某个元素
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入要取结点的位置：\n");
            scanf("%d", &i);
            if (GetElem(L, i, e) == OK)
                printf("第%d个结点的元素是：%d\n", i, e);
            else
                printf("输入位置错误！\n");
            getchar();
            getchar();
            break;

        case 7:
            //确定元素位置，容易出错
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入数据元素值：\n");
            scanf("%d", &e);
            if (i = LocateElem(L, e))
                printf("%d元素位于第%d个位置！\n", e, i);
            else
                printf("该元素不存在!\n");
            getchar();
            getchar();
            break;

        case 8:
            //求出前驱结点
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入数据元素：\n");
            scanf("%d", &cur_e);
            PriorElem(L, cur_e, pre_e);
            if (PriorElem(L, cur_e, pre_e) == OK)
                printf("其前驱元素为：%d\n", pre_e);
            else 
                printf("其不存在前驱元素！\n");
            
            getchar();
            getchar();
            break;

        case 9:
            //求出后置节点
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入数据元素：\n");
            scanf("%d", &cur_e);
            if (NextElem(L, cur_e, next_e) == OK)
                printf("其后继元素为：%d\n", next_e);
            else if (NextElem(L, cur_e, pre_e) == FALSE)
                printf("其不存在后继元素！\n");
            else
            {
                printf("顺序表中没有该元素！\n");
            }
            getchar();
            getchar();
            break;

        case 10:
            //插入元素
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入您要插入的数据元素：\n");
            scanf("%d", &e);
            printf("请输入您要插入的数据元素的位置：\n");
            scanf("%d", &i);
            if (ListInsert(L, i, e) == OK)
                printf("插入数据元素成功！\n");
            else
                printf("插入数据元素失败！\n");
            getchar();
            getchar();
            break;

        case 11:
            //删除元素
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入您要删除的数据元素的位置：\n");
            scanf("%d", &i);
            if (ListDelete(L, i, e) == OK)
                printf("删除数据元素成功！\n");
            else
                printf("删除数据元素失败！\n");
            getchar();
            getchar();
            break;

        case 12:
            //遍历线性表中的元素
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            if (!ListTraverse(L))
                printf("线性表是空表！\n");
            getchar();
            getchar();
            break;

        case 13:
            //保存文件
            if (L.elem == NULL)
            {
                printf("线性表不存在!\n");
                getchar();
                getchar();
                break;
            }
            printf("请输入要写入的文件名:\n ");
            scanf("%s", filename);
            if (SaveList(L, filename) == OK)
                printf("文件保存成功\n文件名为%s\n", filename);
            break;

        case 14:
            //加载文件，需要输入需要加载的名称
            printf("请输入要加载的文件名:\n ");
            scanf("%s", filename);
            if (LoadList(L, filename) == OK)
            {
                printf("文件加载成功\n");
            }
            break;

        case 15:
            //多表管理：增加一个线性表
            printf("请输入添加的表名:\n ");
            scanf("%s", filename);
            if (AddList(lists, filename) == OK)
            {
                printf("成功添加表:%s\n",filename);
            }
            getchar();
            getchar();
            break;

        case 16:
            //多表管理：移除一个线性表
            printf("请输入要移除的表名:\n ");
            scanf("%s", filename);
            if (RemoveList(lists, filename) == OK)
            {
                printf("成功移除表:%s\n",filename);
            }else{
                printf("移除失败");
            }
            getchar();
            getchar();
            break;

        case 17:
            //查找线性表并操作它
            printf("请输入要加载的表名:\n ");
            scanf("%s", filename);
            if (LocateList(lists, filename) == OK)
            {
                DestroyList(L);
                L = lists.elem[LocateList(lists, filename)].L;
                printf("当前操作的表为:%s\n",filename);
            }else{
                printf("加载失败");
            }
            getchar();
            getchar();
            break;
        case 18:
            //计算连续最大子数组和
            printf("最大连续子数组和为：%d",maxSubArray(L.elem,L.length));
            getchar();
            getchar();
            break;
        case 19:
            //和为k的连续子数组个数
            int k;
            printf("请输入k的值:\n");
            scanf("%d",&k);
            printf("和为k的连续子数组个数为:%d",subarraySum(L,k));
            getchar();
            getchar();
            break;
        case 20:
            //数组排序
            sortList(L);
            printf("排序成功");
            getchar();
            getchar();
            break;
        case 0:
            //退出菜单，退出整个程序
            break;
        } // end of switch
    }     // end of while
} // end of main()


status InitList(SqList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL)
    {
        return INFEASIBLE;
    }
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    L.elem[0] = 0;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    else
    {
        if (L.elem)
            free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
}

status ClearList(SqList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    if (L.length == 0)
    {
        return TRUE;
    }
    return FALSE;
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    return L.length;
}

status GetElem(SqList L, int i, ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length)
    {
        return ERROR;
    }
    e = L.elem[i - 1];
    return OK;
}

int LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
            return ++i;
    }
    return 0;
}

status PriorElem(SqList L, ElemType e, ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.elem[0] == e)
        {
            return ERROR;
        }
        else if (L.elem[i] == e)
        {
            pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;
}

status NextElem(SqList L, ElemType e, ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    int i;
    for (i = 0; i < (L.length - 1); i++)
    {
        if (L.elem[i] == e)
        {
            next = L.elem[i + 1];
            return OK;
        }
    }
    if (i == L.length - 1 && (L.elem[i] != e))
        return ERROR;
    else
        return FALSE;
}

status ListInsert(SqList &L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    int *p, *q, *newbase;
    if (i < 1 || i > L.length + 1)
    {
        return ERROR;
    }

    if (L.length >= L.listsize)
    {
        newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    q = &(L.elem[i - 1]);
    for (p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p + 1) = *p;
    *q = e;
    ++L.length;
    return OK;
}

status ListDelete(SqList &L, int i, ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length)
        return ERROR; //删除的位数不正确
    int j;
    e = L.elem[i - 1];
    for (j = i - 1; j < L.length; j++)
        L.elem[j] = L.elem[j + 1];
    L.length--;
    return OK;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    int i;
    for (i = 0; i < L.length; i++)
        printf("%d ", L.elem[i]);
    return OK;
}

status SaveList(SqList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    int i = 0;
    if ((fp = fopen(FileName, "w")) == NULL)
    {
        return INFEASIBLE;
    }
    fprintf(fp, "%d ", L.length);
    fprintf(fp, "%d ", L.listsize);
    while (i < L.length)
        fprintf(fp, "%d ", L.elem[i++]);
    fclose(fp);
    return OK;

    /********** End **********/
}

status LoadList(SqList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    int i = 0;
    if ((fp = fopen(FileName, "r")) == NULL)
    {
        return INFEASIBLE;
    }
    fscanf(fp, "%d", &L.length);
    fscanf(fp, "%d", &L.listsize);
    L.elem = (ElemType *)malloc(L.listsize * sizeof(ElemType));
    if (!L.elem)
        exit(OVERFLOW);
    while (i < L.length)
        fscanf(fp, "%d", &L.elem[i++]);
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    SqList L;
    L.elem = NULL;
    InitList(L);
    Lists.elem[Lists.length].L = L;

    for (int i = 0; ListName[i] != '\0'; i++)
    {
        Lists.elem[Lists.length].name[i] = ListName[i];
    }
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    for (int i = 0; i < Lists.length; i++)
    {
        int flag = 1;
        for (int j = 0; ListName[j] != '\0' && Lists.elem[i].name[j] != '\0'; j++)
        {
            if (ListName[j] != Lists.elem[i].name[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            DestroyList(Lists.elem[i].L);
            while (i < Lists.length)
            {
                Lists.elem[i] = Lists.elem[i + 1];
                i++;
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for (int i = 0; i < Lists.length; i++)
    {
        int flag = 1;
        for (int j = 0; ListName[j] != '\0' && Lists.elem[i].name[j] != '\0'; j++)
        {
            if (ListName[j] != Lists.elem[i].name[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            return i + 1;
        }
    }
    return 0;
}

int maxSubArray(int* nums, int numsSize) {
    int pre = 0, maxAns = nums[0];
    for (int i = 0; i < numsSize; i++) {
        pre = fmax(pre + nums[i], nums[i]);
        maxAns = fmax(maxAns, pre);
    }
    return maxAns;
}

void sortList(SqList &L){
    for(int i = 0;i < L.length-1;i++)
        for(int j = 0;j < L.length-1-i;j++){
            if(L.elem[j] > L.elem[j+1]){
                int temp = L.elem[j];
                L.elem[j] = L.elem[j+1];
                L.elem[j+1] = temp;
            }
        }
}

int subarraySum(SqList &L, int k) {
    int count = 0;
    for (int start = 0; start < L.length; ++start) {
        int sum = 0;
        for (int end = start; end >= 0; --end) {
            sum += L.elem[end];
            if (sum == k) {
                count++;
            }
        }
    }
    return count;
}