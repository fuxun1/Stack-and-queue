//2025.10.28
#include<iostream>
#include<stdlib.h>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int SElemType;

//定义链栈节点类型
typedef struct StackNode{
	SElemType data;
	struct StackNode *next;	//next指针指向下一个节点（栈中an的下一个节点是a(n-1)） 
}StackNode,*LinkStack; //节点类型，指针类型（可用 LinkStack定义指针） 

//LinkStack S;	创建一个头指针S指向一个链栈的栈顶元素，S也代指这个栈 

//链栈的初始化（构造一个空栈）
int InitStack(LinkStack &S){
	S=NULL;
	return OK;
} 

//判断链栈是否为空
bool StackEmpty(LinkStack S){
	if(S==NULL){
		return true;
	}else{
		return false;
	}
}

/*链栈的入栈操作： 
创建一个指针p并给它分配一个节点大小的空间，让p->data为要入栈的元素，再把原栈顶元素的地址赋值给p->next
让p的next指针指向原来的栈顶元素，而原栈顶元素的地址其实就在S指针里存着，所以这一步为：p->next=S 
再让S指向现在新的栈顶元素（即p所指的元素），即S=p 
*/ 
int Push(LinkStack &S,SElemType e){
	LinkStack p;
	p=new StackNode;	//生成新节点p（p既指新节点也指的指向这个新节点的指针） 
	p->data=e;
	p->next=S;
	S=p;
	return OK; 
}

/*链栈的出栈操作： 
将栈顶节点的data放到e里（弹出操作），然后把S节点地址复制一份给p，让S指向它的下方节点，
这样上面的原栈顶节点就可以释放了，即删除p（p指向的还是原来的栈顶元素，但是S已经更新到下方节点了，
这时候如果还写删除S就相当于删除了栈顶节点的下方节点，所以写删除S就不行，
也体现了将原先的S即栈顶元素地址复制一份给p的作用） 
*/
int Pop(LinkStack &S,SElemType &e){
	if(S==NULL){
		return ERROR;
	}
	LinkStack p;
	e=S->data;
	p=S;
	S=S->next;
	delete p;
	return OK;
} 

//取栈顶元素
SElemType GetTop(LinkStack S){
	if(S!=NULL){
		return S->data;
	}
} 


int main(){
	LinkStack S;
	SElemType e;
	InitStack(S);
	Push(S,1);
	Push(S,2);
	Push(S,3);
	cout<<"取栈顶元素，栈顶元素为"<<GetTop(S)<<endl; 
	Pop(S,e);	//把3（栈顶元素）弹出 
	if(StackEmpty(S)){
		cout<<"链栈为空"<<endl;
	}else{
		cout<<"链栈不为空"<<endl;
		while(S!=NULL){
		cout<<S->data<<endl;
		S=S->next;	//链表节点的地址在内存中是不连续的，不能通过--运算符直接移动到上一个节点
		}
	}
	return 0;
}
