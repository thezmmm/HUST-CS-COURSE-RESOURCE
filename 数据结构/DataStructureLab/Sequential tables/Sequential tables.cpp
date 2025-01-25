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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{ //˳���˳��ṹ���Ķ���
    ElemType *elem;
    int length;
    int listsize;
} SqList;
typedef struct LISTS
{ //���Ա�Ĺ������
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
         *  �˵�
         */
        system("cls"); //��������
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
        printf("**\t\t\t\t\t�����Ա����\t\t\t\t**\n\n");
        printf("**\t\t\t15.AddList\t\t16. RemoveList\t\t\t**\n");
        printf("**\t\t\t17.LocateList\t\t\t\t\t\t**\n");
        printf("  ------------------------------------------------------------------------------\n");
        printf("**\t\t\t\t\t���ӹ���\t\t\t\t**\n\n");
        printf("**\t\t\t18.MaxSubArray\t\t19. SubArrayNum\t\t\t**\n");
        printf("**\t\t\t20.sortList\t\t0. Exit\t\t\t\t**\n");
        printf("**\t\t\t��ʵ�������ļ�input����ͨ������14���м���\n");
        printf("  -------------------------------------��ҫ��-----------------------------------\n");
        printf("��ѡ����Ĳ���[0--20]:\n");
        scanf("%d", &op); //ѡ��op��ֵ,����switch
        switch (op)
        {
        case 1:
            //��һ������ǳ�ʼ�����Ա�
            if (InitList(L) == OK)
            {
                printf("���Ա����ɹ�\n");
            }else
                printf("���Ա���ʧ�ܣ�\n");
            getchar();
            getchar();
            break;

        case 2:
            //�ڶ�������������������Ա�
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            if (DestroyList(L) == OK)
            {
                printf("�������Ա�ɹ�!\n");
            }
            else
                printf("�������Ա�ʧ�ܣ�\n");
            getchar();
            getchar();
            break;

        case 3:
            //�����������Ա�
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            if (ClearList(L) == OK)
            {
                printf("���Ա����óɹ���\n");
            }
            else
                printf("���Ա�����ʧ�ܣ�\n");
            getchar();
            getchar();
            break;

        case 4:
            //�ж��Ƿ�Ϊ��
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            if (ListEmpty(L) == TRUE)
            {
                printf("�ļ�Ϊ�գ�\n");
            }
            else
                printf("���Ա��ǿձ�\n");
            getchar();
            getchar();
            break;

        case 5:
            //�õ����Ա���
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("���Ա��Ϊ%d\n", ListLength(L));
            getchar();
            getchar();
            break;

        case 6:
            //�õ�ĳ��Ԫ��
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("������Ҫȡ����λ�ã�\n");
            scanf("%d", &i);
            if (GetElem(L, i, e) == OK)
                printf("��%d������Ԫ���ǣ�%d\n", i, e);
            else
                printf("����λ�ô���\n");
            getchar();
            getchar();
            break;

        case 7:
            //ȷ��Ԫ��λ�ã����׳���
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("����������Ԫ��ֵ��\n");
            scanf("%d", &e);
            if (i = LocateElem(L, e))
                printf("%dԪ��λ�ڵ�%d��λ�ã�\n", e, i);
            else
                printf("��Ԫ�ز�����!\n");
            getchar();
            getchar();
            break;

        case 8:
            //���ǰ�����
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("����������Ԫ�أ�\n");
            scanf("%d", &cur_e);
            PriorElem(L, cur_e, pre_e);
            if (PriorElem(L, cur_e, pre_e) == OK)
                printf("��ǰ��Ԫ��Ϊ��%d\n", pre_e);
            else 
                printf("�䲻����ǰ��Ԫ�أ�\n");
            
            getchar();
            getchar();
            break;

        case 9:
            //������ýڵ�
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("����������Ԫ�أ�\n");
            scanf("%d", &cur_e);
            if (NextElem(L, cur_e, next_e) == OK)
                printf("����Ԫ��Ϊ��%d\n", next_e);
            else if (NextElem(L, cur_e, pre_e) == FALSE)
                printf("�䲻���ں��Ԫ�أ�\n");
            else
            {
                printf("˳�����û�и�Ԫ�أ�\n");
            }
            getchar();
            getchar();
            break;

        case 10:
            //����Ԫ��
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("��������Ҫ���������Ԫ�أ�\n");
            scanf("%d", &e);
            printf("��������Ҫ���������Ԫ�ص�λ�ã�\n");
            scanf("%d", &i);
            if (ListInsert(L, i, e) == OK)
                printf("��������Ԫ�سɹ���\n");
            else
                printf("��������Ԫ��ʧ�ܣ�\n");
            getchar();
            getchar();
            break;

        case 11:
            //ɾ��Ԫ��
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("��������Ҫɾ��������Ԫ�ص�λ�ã�\n");
            scanf("%d", &i);
            if (ListDelete(L, i, e) == OK)
                printf("ɾ������Ԫ�سɹ���\n");
            else
                printf("ɾ������Ԫ��ʧ�ܣ�\n");
            getchar();
            getchar();
            break;

        case 12:
            //�������Ա��е�Ԫ��
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            if (!ListTraverse(L))
                printf("���Ա��ǿձ�\n");
            getchar();
            getchar();
            break;

        case 13:
            //�����ļ�
            if (L.elem == NULL)
            {
                printf("���Ա�����!\n");
                getchar();
                getchar();
                break;
            }
            printf("������Ҫд����ļ���:\n ");
            scanf("%s", filename);
            if (SaveList(L, filename) == OK)
                printf("�ļ�����ɹ�\n�ļ���Ϊ%s\n", filename);
            break;

        case 14:
            //�����ļ�����Ҫ������Ҫ���ص�����
            printf("������Ҫ���ص��ļ���:\n ");
            scanf("%s", filename);
            if (LoadList(L, filename) == OK)
            {
                printf("�ļ����سɹ�\n");
            }
            break;

        case 15:
            //����������һ�����Ա�
            printf("��������ӵı���:\n ");
            scanf("%s", filename);
            if (AddList(lists, filename) == OK)
            {
                printf("�ɹ���ӱ�:%s\n",filename);
            }
            getchar();
            getchar();
            break;

        case 16:
            //�������Ƴ�һ�����Ա�
            printf("������Ҫ�Ƴ��ı���:\n ");
            scanf("%s", filename);
            if (RemoveList(lists, filename) == OK)
            {
                printf("�ɹ��Ƴ���:%s\n",filename);
            }else{
                printf("�Ƴ�ʧ��");
            }
            getchar();
            getchar();
            break;

        case 17:
            //�������Ա�������
            printf("������Ҫ���صı���:\n ");
            scanf("%s", filename);
            if (LocateList(lists, filename) == OK)
            {
                DestroyList(L);
                L = lists.elem[LocateList(lists, filename)].L;
                printf("��ǰ�����ı�Ϊ:%s\n",filename);
            }else{
                printf("����ʧ��");
            }
            getchar();
            getchar();
            break;
        case 18:
            //������������������
            printf("��������������Ϊ��%d",maxSubArray(L.elem,L.length));
            getchar();
            getchar();
            break;
        case 19:
            //��Ϊk���������������
            int k;
            printf("������k��ֵ:\n");
            scanf("%d",&k);
            printf("��Ϊk���������������Ϊ:%d",subarraySum(L,k));
            getchar();
            getchar();
            break;
        case 20:
            //��������
            sortList(L);
            printf("����ɹ�");
            getchar();
            getchar();
            break;
        case 0:
            //�˳��˵����˳���������
            break;
        } // end of switch
    }     // end of while
} // end of main()


status InitList(SqList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    return L.length;
}

status GetElem(SqList L, int i, ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length)
        return ERROR; //ɾ����λ������ȷ
    int j;
    e = L.elem[i - 1];
    for (j = i - 1; j < L.length; j++)
        L.elem[j] = L.elem[j + 1];
    L.length--;
    return OK;
}

status ListTraverse(SqList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
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
// Lists��ɾ��һ������ΪListName�����Ա�
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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