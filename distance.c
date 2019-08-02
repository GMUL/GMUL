#include <graph.h>

int distance_graph(GRAPH *grp,int inode,int jnode) {
	int i,j,dd,idx;
	int nmax;
	int *queue,*d;
	int head,tail,queue_size,maxsize;

	nmax=grp->nnode;
	if (inode==jnode) return 0;
	if (inode>=nmax || grp->kout[inode]==0) return -1;
	if (jnode>=nmax || grp->kin[jnode]==0) return -1;

	d=(int *)malloc(nmax*sizeof(int));
	for (i=0;i<nmax;i++) d[i]=-1;
	d[inode]=0;

	maxsize=grp->nnode;
	queue=(int *)malloc(maxsize*sizeof(int));
	head=0;
	tail=0;
	queue_size=0;

	queue[tail++]=inode;
	tail=MOD(tail,maxsize);
	queue_size++;
	while(queue_size!=0) {
		i=queue[head++];
		head=MOD(head,maxsize);
		queue_size--;
		for (j=0;j<grp->kout[i];j++) {
			idx=grp->Adj[i][j];
			if (d[idx] < 0) {
				queue[tail++]=idx;
				tail=MOD(tail,maxsize);
				queue_size++;
				d[idx]=d[i]+1;
				if (idx==jnode) {
					dd=d[idx];
					free(d);
					free(queue);
					return dd;
				}
			}
		}
	}
	free(d);
	free(queue);
	return -1; 
}

int* distance_graph_all(GRAPH *grp,int inode,int *d) {
	int i,j,idx;
	int nmax;
	int *queue;
	int head,tail,queue_size,maxsize;

	nmax=grp->nnode;
	for (i=0;i<nmax;i++) d[i]=-1;
	d[inode]=0;
	if (inode>=nmax || grp->kout[inode]==0) return d;

	maxsize=grp->nnode;
	queue=(int *)malloc(maxsize*sizeof(int));
	head=0;
	tail=0;
	queue_size=0;

	queue[tail++]=inode;
	tail=MOD(tail,maxsize);
	queue_size++;
	while(queue_size!=0) {
		i=queue[head++];
		head=MOD(head,maxsize);
		queue_size--;
		for (j=0;j<grp->kout[i];j++) {
			idx=grp->Adj[i][j];
			if (d[idx] < 0) {
				queue[tail++]=idx;
				tail=MOD(tail,maxsize);
				queue_size++;
				d[idx]=d[i]+1;
			}
		}
	}
	free(queue);
	return d; 
}

double distance_graph_sum(GRAPH *grp) {
	int i,j,idx,inode;
	int nmax;
	int *queue,*d;
	int head,tail,queue_size,maxsize;
	double dsum;

	nmax=grp->nnode;
	d=(int *)malloc(nmax*sizeof(int));
	maxsize=grp->nnode;
	queue=(int *)malloc(maxsize*sizeof(int));
	head=0;
	tail=0;
	queue_size=0;
	dsum=0.0;

	for (inode=0;inode<nmax;inode++) {
		if (grp->kout[inode]==0) continue;
		for (i=0;i<nmax;i++) d[i]=-1;
		d[inode]=0;
		queue[tail++]=inode;
		tail=MOD(tail,maxsize);
		queue_size++;
		while(queue_size!=0) {
			i=queue[head++];
			head=MOD(head,maxsize);
			queue_size--;
			for (j=0;j<grp->kout[i];j++) {
				idx=grp->Adj[i][j];
				if (d[idx] < 0) {
					queue[tail++]=idx;
					tail=MOD(tail,maxsize);
					queue_size++;
					d[idx]=d[i]+1;
					dsum+=(double)d[idx];
				}
			}
		}
	}
	free(queue);
	free(d);
	return dsum; 
}
