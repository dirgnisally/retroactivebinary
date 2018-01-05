#include<iostream>
#include <ctime>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#define INSERT 1
#define DEL_MIN -1

using namespace std;
struct nodoq
{
    int type;
    int val;
    float time;
    nodoq *izquierda;
    nodoq *derecha;
};
struct nodo
{
    int val;
    nodo *lt,*rt;
    nodoq *link;
}*bst;
class cola
{
    nodoq *front,*back;
    float t;
    public:
        void insertar_insertar(int);
        void insertar_insertar(int,float);
        void insert_del();
        void insert_del(float);
        void del(float);
        void show_op();
        void simple_del(nodoq *);
        cola()
        {
            t=0;
            front=NULL;
            back=NULL;
        };
}q;

int buscar_min(nodo *);
void cola::simple_del(nodoq *tp)
{
    if(tp==NULL)return;
    if(tp->izquierda!=NULL)
    {
        tp->izquierda->derecha=tp->derecha;
    }
    if(tp->derecha!=NULL)
    {
        tp->derecha->izquierda=tp->izquierda;
    }
    delete(tp);
}

void insert_tree(nodo **root,int v,nodoq *ptr)
{
    nodo *p=new nodo;
    nodo *temp;
    ptr->type=0;
    p->val=v;
    p->lt=NULL;
    p->rt=NULL;
    p->link=ptr;
    if(*root == NULL)
    {
        *root = p;
        return;
    }
    temp=*root;
    while(temp)
    {
        if(temp->val>=v)
        {
            if(temp->lt!=NULL)
                temp=temp->lt;
            else
            {
                temp->lt=p;
                break;
            }
        }
        else
        {
            if(temp->rt!=NULL)
                temp=temp->rt;
            else
            {
                temp->rt=p;
                break;
            }
        }
    }
}
void del_tree(nodo **root,int v)
{
    int found;
    nodo *q,*par,*x,*xsucc;
    if(*root==NULL)return;
    par=x=NULL;
    q=*root;
    found=0;
    while(q!=NULL)
    {
        if(q->val==v)
        {
            found=1;
            x=q;
            break;
        }
        par=q;
        if(q->val>v)
            q=q->lt;
        else
            q=q->rt;
    }

    if(found==0)return;
    x->link->type=1;
    if(x->lt!=NULL && x->rt!=NULL)
    {
        par=x;
        xsucc=x->rt;
        while(xsucc->lt!=NULL)
        {
            par=xsucc;
            xsucc=xsucc->lt;
        }
        x->val=xsucc->val;
        x=xsucc;
    }
    if(par==NULL)
    {
        if(x->lt==NULL && x->rt==NULL)
        {
            *root=NULL;
        }
        else if(x->lt==NULL && x->rt!=NULL)
            {
                *root=x->rt;
                free(x);
            }
            else if(x->lt!=NULL && x->rt==NULL)
            {
                *root=x->lt;
                free(x);
            }
         return;
    }
    if(x->lt==NULL && x->rt==NULL)
    {
        if(par->rt==x)
            par->rt=NULL;
        else
            par->lt=NULL;
        free(x);
        return;
    }
    if(x->lt==NULL && x->rt!=NULL)
    {
        if(par->lt==x)
            par->lt=x->rt;
        else
            par->rt=x->rt;
        free(x);
        return;
    }
    if(x->lt!=NULL && x->rt==NULL)
    {
        if(par->lt==x)
            par->lt=x->lt;
        else
            par->rt=x->lt;
        free(x);
        return;
    }
}

void maxk(nodoq *start,nodoq *cu)
{
    nodoq *temp,*st;
    int sum=0,max;
    st=start;
    if(st==NULL)return;
    temp=NULL;

    while(st!=cu && st!=NULL)
    {
        sum+=st->type;
        if(sum==0)temp=st;
        st=st->derecha;
    }
   if(temp==NULL)
    {
        temp=start;

   }
    else temp=temp->derecha;
    {

        if(cu->type!=-1)
            max=cu->val;
        else
            max=-32000;

        while(temp)
        {
            if(temp->type==1 && temp->val>max)
            {
                cu=temp;
                max=temp->val;
            }
            temp=temp->derecha;
        }
        cu->type=0;
        insert_tree(&bst,cu->val,cu);
    }
}

void mink(nodoq *st,nodoq *cu)
{
    nodoq *temp,*temp2;
    int flag=0;
    int sum=0,min=32000;
    if(st==NULL)return;
    temp=NULL;
    temp2=NULL;

    while(st!=NULL)
    {

        if(st==cu)flag=1;
        else sum+=st->type;
        if(sum==0 && flag==1)
        {
            temp=st;
            break;
        }
        st=st->derecha;
    }
   if(temp==NULL)
    {
        temp=cu;
        while(temp->derecha!=NULL)temp=temp->derecha;
        cout<<"temp==NULL";
    }

        while(temp)
        {
            if(temp->type==0 && temp->val<min)
            {
                temp2=temp;
                min=temp->val;
            }
            temp=temp->izquierda;
        }
        if(temp2 != NULL)
        {
            temp2->type=1;
            del_tree(&bst,temp2->val);
        }
        else
        {
            q.simple_del(cu);
        }

}

void show_cola(nodo *root)
{
    if(root)
    {
        show_cola(root->lt);
        printf("%d -> ",root->val);
        show_cola(root->rt);
    }
}
int buscar_min(nodo *p)
{
    if(p==NULL)
    {
        //cout<<"No element in cola\n";
        return -1;
    }
    while(p->lt!=NULL)p=p->lt;
    return (p->val);
}

void cola::show_op()
{
    nodoq *temp;
    temp=back;
    while(temp)
    {
        if(temp->type==-1)
        {
//             printf("insert(del_min() ,t=%.2f), %d\n",temp->time,temp->type);
              printf("insert(del_min() ,t=%.2f)\n",temp->time);
        }
        else
        {
//            printf("insert(insert(%2d),t=%.2f),  %d\n",temp->val,temp->time,temp->type);
            printf("insert(insert(%2d),t=%.2f)\n",temp->val,temp->time);
        }
        temp=temp->derecha;
    }
}
void cola::del(float tm)
{
    nodoq *temp;
    temp=back;
    while(temp)
    {
        if(temp->time==tm)
        {
            if(temp->type==-1)
                maxk(back,temp);
            else if(temp->type==0)
                      del_tree(&bst,temp->val);
                  else
                        mink(back,temp);
            if(temp->izquierda!=NULL)
                temp->izquierda->derecha=temp->derecha;
            if(temp->derecha!=NULL)
                temp->derecha->izquierda=temp->izquierda;
            if(temp->izquierda==NULL && temp->derecha!=NULL)
                back=temp->derecha;
            if(temp->izquierda!=NULL && temp->derecha==NULL)
                front=temp->izquierda;
            if(temp->izquierda==NULL && temp->derecha==NULL)
                back=NULL;
            break;
        }
        temp=temp->derecha;
    }
}
void cola::insertar_insertar(int v)
{
    nodoq *p;
    p = new nodoq;
    p->type = 1;
    p->val = v;
    p->izquierda = front;
    p->derecha = NULL;
    p->time = t;
    t=t+1;
    if(front!=NULL)front->derecha=p;
    front=p;
    insert_tree(&bst,v,p);
    if(back==NULL)back=front;
}
void cola::insertar_insertar(int v, float tm)
{
    nodoq *p = new nodoq;
    nodoq *temp;
    //cout<<t<<endl;
    if(tm > t)
    {
        cout<<"excediendo el tiempo actual, por lo tanto, no hay operación \n";
        return;
    }
    t = tm+1;
    //cout<<"excediendo las marcas "<<t<<endl;
    p->type = 1;
    p->val = v;
    p->time = tm;

    if(back==NULL)
    {
        p->izquierda=front;
        p->derecha=NULL;
        front=p;
        back=p;
    }
    else
    {
        temp=back;
        while(temp->time<tm && temp->derecha!=NULL)
            temp=temp->derecha;
        if(tm>temp->time && temp->derecha==NULL )
        {
            temp->derecha=p;
            p->izquierda=temp;
            p->derecha=NULL;
            front=p;
        }
        else
        {
            if(temp->izquierda==NULL)
                back=p;
            else
                temp->izquierda->derecha=p;
            p->izquierda=temp->izquierda;
            temp->izquierda=p;
            p->derecha=temp;
        }

    }
    maxk(back,p);
}

void cola::insert_del()
{
    nodoq *p;int i;
    if(buscar_min(bst)==-1)return;
    p=new nodoq;
    p->type=-1;
    p->izquierda=front;
    p->derecha=NULL;
    p->time=t;
    t=t+1;
    if(front!=NULL)front->derecha=p;
    front=p;
    del_tree(&bst,buscar_min(bst));
    if(back==NULL)back=front;
}
void cola::insert_del(float tm)
{
    nodoq *p=new nodoq;
    nodoq *temp;
    if(tm>t)
    {
        cout<<"exceeding current time hence no operation \n";
        return;
    }
    p->type=-1;
    p->time=tm;
    if(back==NULL)
    {
        p->izquierda=front;
        p->derecha=NULL;
        front=p;
        back=p;
    }
    else
    {
        temp=back;
        while(temp->time<tm && temp->derecha!=NULL)
            temp=temp->derecha;
        if(temp->derecha==NULL && temp->time<tm)
        {
            temp->derecha=p;
            p->izquierda=temp;
            front=p;
            p->derecha=NULL;
        }
        else
        {
            if(temp->izquierda==NULL)
                back=p;
            else
                temp->izquierda->derecha=p;
            p->izquierda=temp->izquierda;
            temp->izquierda=p;
            p->derecha=temp;
        }
    }
    mink(back,p);
}



int main()
{
    bst = NULL;

    int ch,val;
    float time;


    int i = 0;
    int n = 100000;
    clock_t cl = clock();
	/*while(i++ < n) {
		int r = (rand() % 100) + 1;
		q.insertar_insertar(r-1);
        q.insertar_insertar(r+1);
        //q.insertar_insertar(r+1,2);
        //show_cola(bst);
		//cout <<"hello"<< r << " ";
	}
    cout << "tiempo"<<(clock()-cl)*1000/CLOCKS_PER_SEC << "ms" << endl;
    */
    q.insertar_insertar(1,0);
    q.insertar_insertar(6,0);
    q.insertar_insertar(10,0);
    q.insertar_insertar(15,0);

    q.insertar_insertar(20,1);
    q.insertar_insertar(18,2);
    q.insertar_insertar(50,3);
    cout<<endl<<"Total de  lista de operaciones  :\n";
    q.show_op();
    cout<<endl<<"Los elementos en la cola actual son (en orden creciente):\n";
    show_cola(bst);
    cout<<endl;
    q.del(0);
    cout<<endl<<"Total de  lista de operaciones  :\n";
    q.show_op();
    cout<<endl<<"Los elementos en la cola actual son (en orden creciente):\n";
    show_cola(bst);
    cout << "tiempo"<<(clock()-cl)*1000/CLOCKS_PER_SEC << "ms" << endl;




    cout<<endl<<endl<<endl<<endl;
    //}

}

