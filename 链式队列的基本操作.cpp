//2025.11.1
//链队的数据结构及基本操作
//若用户无法估计所用队列的长度，则适宜采用链队列 

#include<iostream>
#include<stdlib.h>
using namespace std;

#define MAXQSIZE 100
#define OK 1
#define ERROR 0
typedef int QElemType;

//定义结点类型 
typedef struct QNode{
	QElemType data;
	struct QNode *next; 
}QNode,*QueuePtr; 	//结点类型和指向这个结点的指针类型

//定义链队列类型
typedef struct{
	//这里就是真的指针了，而不是像顺序队列那样用来表示数组下标 
	QueuePtr front;	//队头指针 
	QueuePtr rear;	//队尾指针 
}LinkQueue; 

//操作1：链队列的初始化
int InitQueue(LinkQueue &Q){
	//链队列，初始化时只用分配一个节点的空间 
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) {
		exit(1);
	}
	Q.front->next=NULL;
	return OK;
} 

//操作2：链队列的销毁 
//从队头结点开始，通过循环一个个释放结点（另外一种方法是用尾指针充当p） 
int DestoryQueue(LinkQueue &Q){
	QueuePtr p=new QNode;
	while(Q.front){
		p=Q.front->next;
		free(Q.front) ;
		Q.front=p;
	}
	return OK;
}

//操作3：链队列的入队
int EnQueue(LinkQueue &Q,QElemType e){
	//动态分配一个新节点 
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));	//C写法
	//C++:	QueuePtr p = new QNode; 
	if(!p){
		exit(1);	//退出 
	}
	//先把新节点准备好 
	p->data=e;	//数据域为e 
	p->next=NULL;	//指针域为空
	//再把新节点接在尾部（两步顺序不要错） 
	Q.rear->next=p;
	Q.rear=p;
	
	return OK; 
}

//操作4：链队列的出队（队列被修改）
int DeQueue(LinkQueue &Q,QElemType &e){
	if (Q.front == Q.rear) {    // 队空判断
        return ERROR;
    }
	QueuePtr p=Q.front->next;	//p指向第一个存放数据的有效节点 
	e=p->data;	//取出数据
	Q.front->next=p->next;	//跳过p
	//如果删除的是最后一个节点（队列中有效节点只剩一个的情况） 
	if(Q.rear==p) {
		Q.rear=Q.front;		//rear回到头结点（队列为空的标志）
	}
	delete p;
	return OK;
}

 
//操作5：求链队列的队头元素（同样，因为是把队头元素赋值给e，e要被修改后续才能使用，所以传地址）
int GetHead(LinkQueue &Q,QElemType &e){
	if(Q.front==Q.rear){
		return ERROR;
	}
	e=Q.front->next->data;
	return OK;
}

int main(){
	LinkQueue Q;
	InitQueue(Q);
	//入队6个元素 
	QElemType e; 
	cout<<"请输入入队的6个元素"<<endl;
	for(int i=0;i<=5;i++){
		cin>>e;
		EnQueue(Q,e);
	}
	// 遍历输出队列中的元素（不改变队列结构）
	QueuePtr p = Q.front->next;  // p 指向第一个有效节点
	cout << "当前队列为：";
	while (p != NULL) {
    	cout << p->data << " ";
    	p = p->next;  
	}
	cout << endl;

	//出队两个元素
	DeQueue(Q,e);
	DeQueue(Q,e);
	p = Q.front->next;  // p 指向第一个有效节点
	cout << "出队两个元素之后的队列为：";
	while (p != NULL) {
    	cout << p->data << " ";
    	p = p->next;  
	}
	cout << endl;
	
	//求队列头元素
	int k;
	GetHead(Q,k) ;
	cout<<"队列头元素为："<<k<<endl;
	
	return 0;
	
} 


 
 
