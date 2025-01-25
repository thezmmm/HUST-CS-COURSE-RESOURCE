#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef int status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    char others[20];
} TElemType; //������������Ͷ���
typedef struct BiTNode
{ //����������Ķ���
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef struct
{
    int pos;
    TElemType data;
} DEF;
typedef struct
{ //�������Ĺ������
    struct
    {
        char name[30];
        BiTree T;
    } elem[10];
    int length; //������ĳ���
    int listsize;
} TREES;
struct
{
    BiTree a[30];
    int top;
} q;
struct
{
    BiTree a[20];
    int head = 0, tail = 0;
} q2;
struct
{
    BiTree a[100];
    int head = 0, tail = 0;
    int cur[100];
} q3;
int MAX(int a, int b, int c)
{
    if (a > b)
    {
        if (a > c)
            return a;
        else
        {
            if (b > c)
                return b;
            else
                return c;
        }
    }
    else
    {
        if (b > c)
            return b;
        else
        {
            if (c > a)
                return c;
            else
                return a;
        }
    }
}

TREES Trees;
int judge[21];
int top = 0;
int flag = 0;
DEF definition[100];
BiTree T;
BiTree zhan[21];
BiTree parent = NULL;
BiTree parent1 = NULL;
BiTree p = NULL;
int maxsum = 0;

void visit(BiTree T);

status CreateBiTree(BiTree &T, DEF definition[]);
status DestroyBiTree(BiTree &T);
status ClearBiTree(BiTree &T);
status TreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode *LocateNode(BiTree T, KeyType e);
BiTNode *LocateNode2(BiTree T, KeyType e);
BiTNode *LocateNode3(BiTree &T, KeyType e);
status Treejudge(BiTree T);
status Assign(BiTree &T, KeyType e, TElemType value);
BiTNode *GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree &T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse2(BiTree T);
status upsum(BiTree T);
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);

status MaxPathSum(BiTree T);
status LowestCommonAncestor(BiTree T, int e1, int e2);
BiTree InvertTree(BiTree &T);
status AddTree(BiTree T, char ListName[]);
status RemoveTree(TREES &Lists, char ListName[]);
int LocateTree(TREES Trees, char ListName[]);

int main()
{
    int op = 1;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Binary tree On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("           0. �˳�ϵͳ               12. ������� \n");
        printf("           1. ����������              13. ������� \n");
        printf("           2. ���ٶ�����              14. �������\n");
        printf("           3. ��ն�����              15. ���·����\n");
        printf("           4. �ж��ն�����            16. �����������\n");
        printf("           5. ����������            17. ��ת������\n");
        printf("           6. ���ҽ��               18. save\n");
        printf("           7. ��㸳ֵ               19. load\n");
        printf("           8. ����ֵܽ��            20. ���������������һ���¶�����\n");
        printf("           9. ������               21. ������������Ƴ�һ��������\n");
        printf("           10. ɾ�����              22. ��������������Ҷ�����\n");
        printf("           11. ǰ�����              23. �������л�\n");
        printf("          \n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~23]:");
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            break;
        case 1:
        {
            int ans, i = 0;
            printf("�밴��ǰ�����˳������������Ľ�����Լ����ƣ�\n");
            do
            {
                scanf("%d%d%s", &definition[i].pos, &definition[i].data.key, definition[i].data.others);
            } while (definition[i++].pos);
            ans = CreateBiTree(T, definition);
            if (ans == OK)
            {
                printf("�����������ɹ�");
            }
            else
                printf("�ؼ��ֲ�Ψһ");
            getchar();
            getchar();
            break;
        }
        case 2:
        {
            int ans;
            ans = DestroyBiTree(T);
            if (ans == OK)
                printf("���������ٳɹ�\n");
            else
                printf("����������ʧ��! \n");
            getchar();
            getchar();
            break;
        }
        case 3:
        {
            int ans;
            ans = ClearBiTree(T);
            if (ans == INFEASIBLE)
                printf("�����������ڣ�\n");
            if (ans == OK)
                printf("��������ճɹ���\n");
            else
                printf("���������ʧ��! \n");
            getchar();
            getchar();
            break;
        }
        case 4:
        {
            int ans = TreeEmpty(T);
            if (ans == TRUE)
                printf("������Ϊ�գ�\n");
            else if (ans == FALSE)
                printf("�������ǿգ�\n");
            else
                printf("�����������ڣ�\n");
            getchar();
            getchar();
            break;
        }
        case 5:
        {
            int shendu = BiTreeDepth(T);
            if (shendu >= 0)
                printf("�����������Ϊ:%d \n", shendu);
            else
                printf("�����������ڣ�\n");
            getchar();
            getchar();
            break;
        }
        case 6:
        {
            int e, j;
            j = TreeEmpty(T);
            if (j == INFEASIBLE)
            {
                printf("������������! \n");
                getchar();
                getchar();
                break;
            }
            printf("������Ҫ���ҵĽ��Ĺؼ���: \n");
            scanf("%d", &e);
            flag = 0;
            BiTNode *p = LocateNode(T, e);
            if (p && flag == 1)
                printf("%d,%s", p->data.key, p->data.others);
            else if (flag == 0)
                printf("�ؼ���Ϊ%d�Ľ�㲻�ڶ�������!\n", e);
            getchar();
            getchar();
            break;
        }
        case 7:
        {
            int ans, key;
            TElemType e;
            for (int i = 0; i < 21; i++)
                judge[i] = 0;
            Treejudge(T);
            printf("������Ҫ��ֵ���Ĺؼ����Լ��µĹؼ��ֺ��µ����ƣ�\n");
            scanf("%d%d%s", &key, &e.key, e.others);
            p = NULL;
            ans = Assign(T, key, e);
            if (ans == OK)
                printf("��ֵ�ɹ���\n");
            else
                printf("��ֵʧ�ܣ�\n");
            getchar();
            getchar();
            break;
        }
        case 8:
        {
            int e;
            printf("������Ҫ��ȡ�ֵܽ����Ĺؼ���: \n");
            p = NULL;
            scanf("%d", &e);
            BiTNode *p = GetSibling(T, e);
            if (p)
                printf("%d,%s", p->data.key, p->data.others);
            else
                printf("���ֵܽ��");
            getchar();
            getchar();
            break;
        }
        case 9:
        {
            TElemType c;
            p = NULL;
            int ans, i = 0, e, LR;
            for (i = 0; i < 21; i++)
                judge[i] = 0;
            printf("������Ҫ�����Ŀ�Ľ��Ĺؼ��֡����뷽ʽ�Լ�Ҫ���������Ϣ:\n");
            scanf("%d%d%d%s", &e, &LR, &c.key, c.others);
            Treejudge(T);
            ans = InsertNode(T, e, LR, c);
            if (ans == OK)
                printf("����ɹ���\n");
            else
                printf("�������ʧ�ܣ�\n");
            getchar();
            getchar();
            break;
        }
        case 10:
        {
            int ans, e;
            printf("������Ҫɾ���Ľ��Ĺؼ���: \n");
            scanf("%d", &e);
            p = NULL;
            parent = NULL;
            ans = DeleteNode(T, e);
            if (ans == OK)
                printf("ɾ�����ɹ���\n");
            else
                printf("ɾ�����ʧ�ܣ�\n");
            getchar();
            getchar();
            break;
        }
        case 11:
        {
            PreOrderTraverse(T, visit);
            getchar();
            getchar();
            break;
        }
        case 12:
        {
            InOrderTraverse(T, visit);
            getchar();
            getchar();
            break;
        }
        case 13:
        {
            PostOrderTraverse(T, visit);
            getchar();
            getchar();
            break;
        }
        case 14:
        {
            LevelOrderTraverse(T, visit);
            getchar();
            getchar();
            break;
        }
        case 15:
        {
            MaxPathSum(T);
            printf("�������·����Ϊ��%d\n", maxsum);
            getchar();
            getchar();
            break;
        }
        case 16:
        {
            printf("������Ҫ��������������ȵĽ��Ĺؼ��֣�\n");
            int e1, e2;
            scanf("%d %d", &e1, &e2);
            int zuxian;
            zuxian = LowestCommonAncestor(T, e1, e2);
            printf("%d��%d�������������Ϊ����������ΪΪ%d�Ľ��\n", e1, e2, zuxian);
            getchar();
            getchar();
            break;
        }
        case 17:
        {
            T = InvertTree(T);
            printf("��������ת�ɹ���\n");
            getchar();
            getchar();
            break;
        }
        case 18:
        {
            printf("������Ҫ������ļ�������: \n");
            char FileName[20];
            scanf("%s", FileName);
            SaveBiTree(T, FileName);
            printf("����ɹ���\n");
            getchar();
            getchar();
            break;
        }
        case 19:
        {
            printf("������Ҫ�������ļ������ƣ�\n");
            for (int i = 0; i < 20; i++)
                judge[i] = 0;
            char FileName[20];
            scanf("%s", FileName);
            LoadBiTree(T, FileName);
            printf("���سɹ���\n");
            getchar();
            getchar();
            break;
        }
        case 20:
        {
            int j;
            char name[30];
            printf("������Ҫ��ӵĶ����������ƣ�\n");
            scanf("%s", name);
            BiTree temp;
            temp =(BiTree)malloc(sizeof(BiTNode));
            TElemType x;
            x.key = -1;
            temp->data = x;
            temp->lchild=NULL;
            temp->rchild=NULL;
            j = AddTree(temp, name);
            if (j == OK)
            {
                printf("��ӳɹ�!\n");
                getchar();
                getchar();
                break;
            }
        }
        case 21:
        {
            printf("�����Ҫ�Ƴ��Ķ�����������: \n");
            char name[30];
            scanf("%s", name);
            int j;
            j = RemoveTree(Trees, name);
            if (j == OK)
            {
                printf("ɾ���ɹ���\n");
                getchar();
                getchar();
                break;
            }
            if (j == ERROR)
            {
                printf("����Ϊ%s�Ķ����������ڣ�\n", name);
                getchar();
                getchar();
                break;
            }
        }
        case 22:
        {
            printf("������Ҫ���ҵĶ����������ƣ�\n");
            char name[20];
            int j;
            scanf("%s", name);
            j = LocateTree(Trees, name);
            if (j == ERROR)
            {
                printf("����Ϊ%s�Ķ����������ڣ�\n", name);
                getchar();
                getchar();
                break;
            }
            if (j)
            {
                printf("����Ϊ%s�Ķ�������λ��Ϊ%d", name, j);
                getchar();
                getchar();
                break;
            }
        }
        case 23:
        {
            printf("�����Ҫ�л��Ķ�����������: \n");
            char name[30];
            scanf("%s", name);
            int j;
            j = LocateTree(Trees, name);
            if (j == ERROR)
            {
                printf("����Ϊ%s�Ķ����������ڣ�\n", name);
                getchar();
                getchar();
                break;
            }
            if (j)
            {
                T = Trees.elem[j - 1].T;
                printf("�������л��ɹ���\n");
                getchar();
                getchar();
                break;
            }
        }
        } // end of switch
    }     // end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
} // end of main()

status CreateBiTree(BiTree &T, DEF definition[])
{
    int i = 0, j;
    static BiTNode *p[100];
    for (i = 0; i < 21; i++)
        judge[i] = 0;
    i = 0;
    if (definition[0].pos == 0)
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        T->lchild = NULL;
        T->rchild = NULL;
        return OK;
    }
    while (j = definition[i].pos)
    {
        if (judge[definition[i].data.key] != 0)
        {
            return INFEASIBLE;
        }
        p[j] = (BiTNode *)malloc(sizeof(BiTNode));
        judge[definition[i].data.key]++;
        p[j]->data = definition[i].data;
        p[j]->lchild = NULL;
        p[j]->rchild = NULL;
        if (j != 1)
            if (j % 2)
                p[j / 2]->rchild = p[j];
            else
                p[j / 2]->lchild = p[j];
        i++;
    }
    T = p[1];
    return OK;
}

void deletree(BiTree &t)
{
    if (t == NULL)
        return;
    deletree(t->lchild);
    deletree(t->rchild);
    if (t != T)
    {
        free(t);
        t = NULL;
    }
    else
    {
        t->data.key = '\0';
        strcpy(t->data.others, "");
    }
}

status ClearBiTree(BiTree &T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�,���������ͷ��㻹��
{
    if (T == NULL)
        return INFEASIBLE;
    deletree(T);
    return OK;
}

status DestroyBiTree(BiTree &T)
{
    //����������ͷ���ΪNULL
    if (T == NULL)
        return INFEASIBLE;
    ClearBiTree(T);
    T = NULL;
    return OK;
}

status TreeEmpty(BiTree T)
{
    if (T == NULL)
        return INFEASIBLE;
    if (T->lchild == NULL && T->rchild == NULL)
        return OK;
    else
        return FALSE;
}

int BiTreeDepth(BiTree T)
//�������T�����
{
    static int j = 0;
    if (T == NULL)
        return 0;
    j = max(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild)) + 1;
    return j;
}

BiTNode *LocateNode(BiTree T, KeyType e) // KeyType int
//���ҽ��
{
    if (T == NULL)
        return p;
    if (e == T->data.key)
    {
        p = T;
        flag = 1;
        return p;
    }
    LocateNode(T->lchild, e);
    LocateNode(T->rchild, e);
    return p;
}
status Treejudge(BiTree T)
{
    if (T == NULL)
        return OK;
    judge[T->data.key]++;
    Treejudge(T->lchild);
    Treejudge(T->rchild);
    return OK;
}
BiTNode *LocateNode2(BiTree T, KeyType e) // KeyType int
//���ҽ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (T == NULL)
        return p;
    if (e == T->data.key)
    {
        p = T;
        judge[T->data.key] = 0;
        return p;
    }
    LocateNode(T->lchild, e);
    LocateNode(T->rchild, e);
    return p;
    /********** End **********/
}
status Assign(BiTree &T, KeyType e, TElemType value)
//ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
{
    BiTree p1;
    p1 = LocateNode2(T, e);
    if(p1 == NULL){
        printf("1");
    }
    if (p1 == NULL || (judge[value.key]))
        return ERROR;
    else
    {
        p1->data = value;
        return OK;
    }
}

BiTNode *GetSibling(BiTree T, KeyType e)
//ʵ�ֻ���ֵܽ��
{
    if (T == NULL)
        return p;
    if (T->data.key == e)
    {
        if (parent == NULL)
            return NULL;
        else
        {
            if (parent->lchild == T)
            {
                p = parent->rchild;
                return p;
            }
            if (parent->rchild == T)
            {
                p = parent->lchild;
                return p;
            }
        }
    }
    parent = T;
    GetSibling(T->lchild, e);
    parent = T;
    GetSibling(T->rchild, e);
    return p;
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//�����㡣��������ͨ������������������ʵ�ֱ�������
{
    BiTree C;
    C = (BiTree)malloc(sizeof(BiTNode));
    C->data = c;
    C->lchild = NULL;
    C->rchild = NULL;
    if (LR == -1)
    {
        C->lchild = NULL;
        C->rchild = T;
        T = C;
        return OK;
    }
    BiTree p, p_left = NULL, p_right = NULL;
    p = LocateNode2(T, e);
    if (judge[C->data.key])
        return ERROR;
    if (p == NULL)
        return ERROR;
    else
    {
        if (LR == 0)
        {
            p_left = p->lchild;
            p_right = p->rchild;
            p->lchild = C;
            C->rchild = p_left;
            return OK;
        }
        else if (LR == 1)
        {
            p_left = p->lchild;
            p_right = p->rchild;
            p->rchild = C;
            C->rchild = p_right;
        }
    }
    return OK;
}

BiTNode *LocateNode3(BiTree &T, KeyType e) // KeyType int//ע��˴��޸���T��ֵ���ڽ��д������ʱ����һ���µĺ���
//���ҽ��
{
    if (T == NULL)
        return p;
    if (e == T->data.key)
    {
        parent1 = parent;
        p = T;
        return p;
    }
    parent = T;
    LocateNode3(T->lchild, e);
    parent = T;
    LocateNode3(T->rchild, e);
    return p;
}
status DeleteNode(BiTree &T, KeyType e)
//ɾ����㡣��������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    BiTree p, head = T;
    p = LocateNode3(T, e);
    if (p == NULL)
        return ERROR;
    BiTree p_left = p->lchild, p_right = p->rchild;
    if (p_left == NULL && p_right == NULL)
    {
        if (p == head)
        {
            free(p);
            p = NULL;
            T = p;
        }
        else
        {
            free(p);
            if (p == parent1->lchild)
                parent1->lchild = NULL;
            if (p == parent1->rchild)
                parent1->rchild = NULL;
        }
    }
    if (p_left && p_right == NULL)
    {
        if (p == head)
        {
            free(p);
            p = p_left;
            T = p;
        }
        else
        {
            free(p);
            if (p == parent1->lchild)
                parent1->lchild = p_left;
            if (p == parent1->rchild)
                parent1->rchild = p_left;
        }
    }
    if (p_left == NULL && p_right)
    {
        if (p == head)
        {
            free(p);
            p = p_right;
            T = p;
        }
        else
        {
            free(p);
            if (p == parent1->lchild)
                parent1->lchild = p_right;
            if (p == parent1->rchild)
                parent1->rchild = p_right;
        }
    }
    if (p_left && p_right)
    {
        if (p == head)
        {
            free(p);
            p = p_left;
            T = p;
            while (p->rchild)
            {
                p = p->rchild;
            }
            p->rchild = p_right;
        }
        else
        {
            if (parent1->lchild == p)
                parent1->lchild = p_left;
            if (parent1->rchild == p)
                parent1->rchild = p_left;
            p = p_left;
            while (p->rchild)
            {
                p = p->rchild;
            }
            p->rchild = p_right;
        }
    }
    return OK;
}

void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{
    q.top = -1;
    while (T || q.top != -1)
    {
        while (T)
        {
            visit(T);
            q.a[++q.top] = T;
            T = T->lchild;
        }
        if (q.top != -1)
        {
            T = q.a[q.top--];
            T = T->rchild;
        }
    }
    return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{
    if (T == NULL)
        return OK;
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{
    if (T == NULL)
        return OK;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{   
    if(T == NULL){
        return OK;
    }
    q2.a[q2.tail++] = T;
    visit(T);
    while (q2.head < q2.tail)
    {
        if (q2.a[q2.head]->lchild)
        {
            visit(q2.a[q2.head]->lchild);
            q2.a[q2.tail++] = q2.a[q2.head]->lchild;
        }
        if (q2.a[q2.head]->rchild)
        {
            visit(q2.a[q2.head]->rchild);
            q2.a[q2.tail++] = q2.a[q2.head]->rchild;
        }
        q2.head++;
    }
    return OK;
}

status upsum(BiTree T)
{
    if (T == NULL)
        return 0;
    int val_left = upsum(T->lchild);
    int val_right = upsum(T->rchild);
    int left_gain = MAX(val_left, 0, 0);
    int right_gain = MAX(val_right, 0, 0);
    int newroot1 = T->data.key + left_gain;
    int newroot2 = T->data.key + right_gain;
    maxsum = MAX(maxsum, newroot1, newroot2);
    return T->data.key + MAX(left_gain, right_gain, 0);
}
status MaxPathSum(BiTree T)
{
    if (T->data.key < 0 && T->lchild == NULL && T->rchild == NULL)
        return T->data.key;
    upsum(T);
    return maxsum;
}

status LevelOrderTraverse2(BiTree T)
//�������������T
{
    q3.cur[0] = 1;
    q3.a[q3.tail++] = T;
    while (q3.head < q3.tail)
    {
        if (q3.a[q3.head]->lchild)
        {
            q3.cur[q3.tail] = q3.cur[q3.head] * 2;
            q3.a[q3.tail++] = q3.a[q3.head]->lchild;
        }
        if (q3.a[q3.head]->rchild)
        {
            q3.cur[q3.tail] = q3.cur[q3.head] * 2 + 1;
            q3.a[q3.tail++] = q3.a[q3.head]->rchild;
        }
        q3.head++;
    }
    return OK;
}
status LowestCommonAncestor(BiTree T, int e1, int e2)
{ //������
    p = NULL;
    LevelOrderTraverse2(T);
    int pos1 = 0, pos2 = 0, i; // e1,e2�ڶ������е�λ��
    for (i = 0; i < 100; i++)
    {
        if (q3.a[i]->data.key == e1)
        {
            pos1 = q3.cur[i];
            break;
        }
    }
    for (i = 0; i < 100; i++)
    {
        if (q3.a[i]->data.key == e2)
        {
            pos2 = q3.cur[i];
            break;
        }
    }
    while (pos1 != pos2)
    {
        if (pos1 > pos2)
            pos1 /= 2;
        else if (pos1 < pos2)
            pos2 /= 2;
    }
    for (i = 0; i < 100; i++)
    {
        if (q3.a[i]->data.key == pos1)
            return q3.cur[i];
    }
    return OK;
}

BiTree InvertTree(BiTree &T)
{
    if (T == NULL)
        return NULL;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
    BiTree t;
    t = T->lchild;
    T->lchild = T->rchild;
    T->rchild = t;
    return T;
}

status SaveBiTree(BiTree T, char FileName[])
//���������Ľ������д�뵽�ļ�FileName��
{
    FILE *fp;
    fp = fopen(FileName, "w");
    LevelOrderTraverse2(T);
    q3.head = 0;
    for (; q3.cur[q3.head] != 0; q3.head++)
    {
        fprintf(fp, "%d %d %s ", q3.cur[q3.head], q3.a[q3.head]->data.key, q3.a[q3.head]->data.others);
    }
    fprintf(fp, "0 0 null ");
    fclose(fp);
    return OK;
}
status LoadBiTree(BiTree &T, char FileName[])
//�����ļ�FileName�Ľ�����ݣ�����������
{
    DEF def[100];
    FILE *fp;
    int i = 0;
    fp = fopen(FileName, "r");
    do
    {
        fscanf(fp, "%d %d %s", &def[i].pos, &def[i].data.key, def[i].data.others);
    } while (def[i++].pos);
    CreateBiTree(T, def);
    fclose(fp);
    return OK;
}

status AddTree(BiTree T, char ListName[])
{
    Trees.elem[Trees.length].T = T;
    strcpy(Trees.elem[Trees.length].name, ListName);
    Trees.length++;
    return OK;
}

status RemoveTree(TREES &Lists, char ListName[])
{
    int i;
    for (i = 0; i < Trees.length; i++)
    {
        if (strcmp(Trees.elem[i].name, ListName) == 0)
        {
            BiTree T = Lists.elem[i].T;
            DestroyBiTree(T);
            for (int j = i; j < Trees.length; j++)
                Lists.elem[j] = Lists.elem[j + 1];
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateTree(TREES Trees, char ListName[])
{
    int i;
    for (i = 0; i < Trees.length; i++)
    {
        if (strcmp(Trees.elem[i].name, ListName) == 0)
        {
            return i + 1;
        }
    }
    return ERROR;
}
