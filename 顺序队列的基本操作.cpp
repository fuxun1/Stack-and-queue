//2025.11.1
//顺序队列的数据结构及基本操作

#include<iostream>
#include<stdlib.h>
using namespace std; 

#define MAXQSIZE 100	//最大队列长度
#define OK 1
#define ERROR 0	
typedef int QElemType;

//顺序队列数据结构 ---base[MAXQSIZE] 
typedef struct{
	//初始化的动态分配存储空间，如果用静态数组就可以直接定义QElemType base[大小]，这里用动态数组 
	QElemType *base;	//base指针指向这个队列的首元素地址（基地址）
	//说白了就是指向一段连续分配的存储空间（base数组）的首地址 
	//至于base数组有多大，后面初始化再给他分配具体大小的空间 
	int front;	//头指针，称作指针但是不是指针变量，而是队头下标（数组下标） 
	int rear; 	//尾指针，... ，而是队尾下标 （数组下标）
}SqQueue; 

//操作1：队列的初始化
int InitQueue(SqQueue &Q){
	//在堆区分配一块连续内存空间
	Q.base=new QElemType[MAXQSIZE];	//分配数组空间（下标从0到MAXQSIZE-1） （C++写法） 
	//C语法：Q.base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType))
	//base是一个指向 QElemType类型的指针，所以强制类型转换为QElemType* 
	if(!Q.base){
		exit(1);
	}
	Q.front=Q.rear=0;
	return OK;
} 

//操作2：求队列的长度
int QueueLength(SqQueue Q){
	return((Q.rear-Q.front+MAXQSIZE)%MAXQSIZE);
	//实际就是(MAXQSIZE - front) + rear，然后为了保证一般情况（即rear>=front）也适用于此公式就再对MAXQSIZE取模
	//因为当rear>=front时，rear-front就已经得到元素个数，再加MAXQSIZE就多了，所以再通过%MAXQSIZE去掉 
	//总之，Q.rear-Q.front+MAXQSIZE其实就已经得到结果，%MAXQSIZEW只是为了统一两种情况 
} 

//操作3：循环队列的入队
int EnQueue(SqQueue &Q,QElemType e){
	if((Q.rear+1)%MAXQSIZE==Q.front){	//判断队列是否已满 
		return ERROR;
	}
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;		//队尾指针rear指向下一个位置
	return OK; 
} 

//操作4：循环队列的出队
//还是一样，因为是把队头元素赋值给了e方便后续使用，改变了e的实际值，所以要传地址&e
int DeQueue(SqQueue &Q,QElemType &e){
	//先判断队列是否为空
	if(Q.front==Q.rear) {
		return ERROR;
	}
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;	//队头指针+1 
	return OK;
}

//操作5：取队头元素
//与出队的区别在于队列本身并不改变，只是把队头元素复制一份再拿出来，所以不用传队列的地址 
QElemType GetHead(SqQueue Q){
	if(Q.rear!=Q.front){
		return Q.base[Q.front];
	} 
	else{
		return ERROR;
	} 
} 

//操作6：销毁队列，释放内存 
int DestoryQueue(SqQueue &Q) {
	if(Q.base){
		delete[] Q.base;	//释放 base指针所指向的堆区空间，但指针本身仍然存在（此时为野指针）
		Q.base=NULL;	//所以还需将base指针置空，不然base指针就成为了野指针
		Q.front=Q.rear=0; 
	}
	return OK;
}

int main(){
	SqQueue Q;
	InitQueue(Q);
	QElemType e; 
	//往队列中入队6个元素 
	cout<<"输入要入队的6个元素"<<endl;
	for(int i=0;i<=5;i++){
		cin>>e;
		EnQueue(Q,e);
	}
	//出队一个元素
	DeQueue(Q,e);
	cout<<"出队的元素是："<<e<<endl;
	//取队头元素
	QElemType k=GetHead(Q);
	cout<<"此时队头元素是："<<k<<endl;
	
	int n=QueueLength(Q);
	cout<<"此时队列长度为："<<n<<endl; 
	
	//销毁队列，释放内存
	DestoryQueue(Q); 
	
	return 0;
	
} 





