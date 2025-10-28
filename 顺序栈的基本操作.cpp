//2025.10.28

#include<iostream>
#include<stdlib.h>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int SElemType;

typedef struct{
	SElemType *top;
	SElemType *base;
	int stacksize;
}SqStack;

//构造一个空栈 
int InitStack(SqStack &S){
	//在内存中找一块能存放MAXSIZE个元素的内存，并让base指针指向这块空间的首地址（等价于指向这块空间） 
	S.base=new SElemType[MAXSIZE];
	//C语法：S.base=(SElemType*)malloc(MAXSIZE*sizeof(SElemType));
	if(!S.base){
		cout<<"空间分配失败"<<endl;
		exit(1);
	} 
	S.top=S.base;
	S.stacksize=MAXSIZE;
	cout<<"内存分配成功"<<endl;
	return OK; 
}

//判断顺序栈是否为空(空栈条件为top指针等于base指针) 
bool StackEmpty(SqStack S){
	if(S.top==S.base){
		return true;
	}else{
		return false;
	}
} 

//求顺序栈的长度（top指针减base指针即为顺序栈的长度）
int StackLength(SqStack S){
	return S.top-S.base;
}

//清空顺序栈（保留空间）（不需要把每个元素都置为空，让top指针=base指针就行（把栈当成空的））
int ClearStack(SqStack &S){
	if(S.base){		//先判断栈存不存在，不存在就不用清空 
	S.top==S.base;
	}
	return OK;
} 

//销毁顺序栈（元素和空间都没了） 
int DestroyStack(SqStack &S){
	if(S.base){	//同样先判断栈是否存在 
		delete S.base;	//删除栈底指针（只是把内存释放掉，其实指针还在）
		S.stacksize=0;
		S.base=S.top=NULL; //把指针设为空（防止base和top成为野指针） 
	}
	return OK;
}

//顺序栈的入栈（先判断栈是否满了，满了则报错，没满则把元素e存到top指针位置,top指针上移）
int Push(SqStack &S,SElemType e){
	if(S.top-S.base==S.stacksize){
		return ERROR;
	}
	*S.top=e;
	S.top++;
	//*S.top++=e;
}

//顺序栈的出栈（先判断栈是否空了，空了则出错，没空则先将top指针下移，再将top指针所指的元素出栈） 
int Pop(SqStack &S,SElemType &e){
	if(S.top==S.base){
		return ERROR;
	}
	S.top--;
	e=*S.top;
	//e=*--S.top; 
	return OK;
}

int main(){
	SqStack S;
	int k;
	InitStack(S);
	if(StackEmpty(S)){
		cout<<"栈为空"<<endl;
	}else{
		cout<<"栈不为空"<<endl;
	}
	k=StackLength(S);
	cout<<"栈的长度为"<<k<<endl;
	return 0;
}
