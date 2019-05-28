#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define empty -1

typedef struct Vertex
{
	int state;
	int info;
	struct Vertex *nextVertex; /*next vertex in the linked list of vertices*/
	struct Edge *firstEdge; /*first Edge of the adjacency list of this
				  vertex*/
}Vertex;
typedef struct Edge
{
	struct Vertex *destVertex; /*Destination vertex of the Edge*/
	struct Edge *nextEdge; /*next Edge of the adjacency list*/
}Edge;

Vertex *head=NULL;

Vertex *findVertex(int u);
int insertVertex(int u);
void insertEdge(int u,int v);
int enqueue(int [],int *,int*,int);
int dequeue(int [],int *,int*);
void display();
int bfs(int);

int main()
{
	int choice,u,origin,destin,vertex;
	printf("Enter no.of vertex to be inserted : ");
	scanf("%d",&u);
	for(int i=0;i<u;i++)
	{
		scanf("%d",&vertex);
		insertVertex(vertex);
	}
	printf("Enter an Edge to be inserted (exit: 0 0): ");
	scanf("%d %d",&origin,&destin);
	while(origin)
	{
		insertEdge(origin,destin);
		printf("Enter an Edge to be inserted (exit: 0 0): ");
		scanf("%d %d",&origin,&destin);
	}
	display();
	printf("starting node:");
	scanf("%d",&u);
	bfs(u);
}
int insertVertex(int u)
{
       	Vertex *new,*ptr;
	new =(Vertex*) malloc(sizeof(Vertex));
	if(NULL==new)
	{
		printf("MAF");
		exit(0);
	}
	memset(new,0,sizeof(Vertex));
	new->state=1;
	new->info = u;
	new->nextVertex = NULL;
	new->firstEdge = NULL;
	if(head == NULL)
	{
		head = new;
		return 1;
	}
	ptr = head;
	while(ptr->nextVertex!=NULL)
		ptr = ptr->nextVertex;
	ptr->nextVertex = new;
}

Vertex *findVertex(int u)
{
        Vertex *ptr;
	ptr = head;
	while(ptr!=NULL)
	{
		if(ptr->info == u )
		{
			return ptr;
		}
		else
			ptr = ptr->nextVertex;
	}
	return NULL;
}
void insertEdge(int u,int v)
{
	Vertex *locu,*locv;
	locu = findVertex(u);
	locv = findVertex(v);
	if(locu == NULL )
	{
		printf("Start vertex not present, first insert vertex %d\n",u);
		return;
	}
	if(locv == NULL )
	{
		printf("End vertex not present, first insert vertex %d\n",v);
		return;
	}
	Edge *ptr,*new;
	new =(Edge*) malloc(sizeof(struct Edge));
	if(NULL==new)
	{
		printf("MAF\n");
		exit(0);
	}
	memset(new,0,sizeof(Edge));
	new->destVertex = locv;
	new->nextEdge = NULL;
	if(locu->firstEdge == NULL)
	{
		locu->firstEdge = new;
		return;
	}
	ptr = locu->firstEdge;
	while(ptr->nextEdge!=NULL)
		ptr = ptr->nextEdge;
	ptr->nextEdge = new;
}
void display()
{
	Vertex *ptr;
	Edge *q;
	ptr = head;
	while(ptr!=NULL)
	{
		printf("%d ->",ptr->info);
		q = ptr->firstEdge;
		while(q!=NULL)
		{
			printf(" %d",q->destVertex->info);
			q = q->nextEdge;
		}
		printf("\n");
		ptr = ptr->nextVertex;
	}
}

int bfs(int u)
{
	int queue[10];
	memset(queue,0,10*sizeof(int));
	int front= empty,traverse, rear= empty;

	struct Vertex *ptr, *loc;
	struct Edge *r;
	ptr=findVertex(u);

	enqueue(queue,&front,&rear,ptr->info);
	ptr->state=2;
	while((empty!=front)&&(empty!=rear))
	{
		traverse=dequeue(queue,&front,&rear);
		printf("%d  ",traverse);
		loc=findVertex(traverse);
		if(NULL!=loc)
		{
			r=loc->firstEdge;
			while(NULL!=r)
			{			
				if(r->destVertex->state==1)
				{
					enqueue(queue,&front,&rear,r->destVertex->info);
					r->destVertex->state=2;
				}
				r=r->nextEdge;
			}
		}
	}
}

int enqueue(int queue[],int *front,int *rear,int item)
{
	if((*rear+1)%10==*front)
	{
		printf("overflow");
		exit(0);
	}
	if(empty == *front)
	{
		*front=0;
		*rear=0;
	}
	else
		*rear=(*rear+1)%10;
	queue[*rear]=item;
}

int dequeue(int queue[],int *front,int *rear)
{
	int item;
	if(empty==*front)
	{
		printf("underflow");
		exit(0);
	}
	item=queue[*front];
	if(*front==*rear)
	{
		*front = empty;
		*rear=empty;
	}
	else
		*front=(*front+1)%10;
	return item;
}
