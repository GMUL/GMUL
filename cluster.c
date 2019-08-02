#include <graph.h>
#include <time.h>

int isconnected(GRAPH *grp) {
	int i,j,l,s,nnode,nnode_cluster;
	int nmax;
	int *queue,*id;
	int head,tail,queue_size,maxsize;

	maxsize=grp->nnode;
	nmax=grp->nnode;
	nnode=0;
	if (nmax==0 || maxsize==0) return 0;
	queue=(int *)malloc(maxsize*sizeof(int));
	id=(int *)malloc(nmax*sizeof(int));
	for (i=0;i<nmax;i++) { 
		id[i]=0;
		if (grp->kout[i]>0 || grp->kin[i]>0) nnode++;
	}

	srand48(time(NULL));
	do {
		s=(int)(((double)(nmax+1))*drand48());
	} while(grp->kn[s]==0);

	head=0;
	tail=0;
	queue_size=0;
	nnode_cluster=0;
	queue[tail++]=s;
	tail=MOD(tail,maxsize);
	queue_size++;
	nnode_cluster++;
	id[s]=1;
	while(queue_size!=0) {
		j=queue[head++];
		head=MOD(head,maxsize);
		queue_size--;
		for (l=0;l<grp->kout[j];l++) {
			if (id[grp->Adj[j][l]]==0) {
				queue[tail++]=grp->Adj[j][l];
				tail=MOD(tail,maxsize);
				queue_size++;
				nnode_cluster++;
				id[grp->Adj[j][l]]=1;
			}
		}
	}
	free(queue);
	free(id);
	if (nnode!=nnode_cluster) return 0;
	return 1;
}

int clusterid(GRAPH *grp,int* id) {
	int i,j,k=0,l;
	int nmax;
	int *queue;
	int head,tail,queue_size,maxsize;
	nmax=grp->nnode;
	maxsize=grp->nnode;
	if (nmax==0 || maxsize==0) return k;
	queue=(int *)malloc(maxsize*sizeof(int));
	for (i=0;i<nmax;i++) id[i]=-1;
	for (i=0;i<nmax;i++) {
		if (grp->kn[i]==0 || id[i]!=-1) continue;
		head=0;
		tail=0;
		queue_size=0;
		queue[tail++]=i;
		tail=MOD(tail,maxsize);
		queue_size++;
		id[i]=k;
		while(queue_size!=0) {
			j=queue[head++];
			head=MOD(head,maxsize);
			queue_size--;
			for (l=0;l<grp->kn[j];l++) {
				if (id[grp->Adj[j][l]] < 0) {
					queue[tail++]=grp->Adj[j][l];
					tail=MOD(tail,maxsize);
					queue_size++;
					id[grp->Adj[j][l]]=k;
				}
			}
		}
		k++;
	}
	free(queue);
	return k; 
}

int largest_cluster_size(GRAPH *grp) {
	int i,nc,Gsize;
	int *id;
	int *cluster_size;
	if (grp->nnode==0) return 0;
	id=(int *)malloc(grp->nnode*sizeof(int));
	nc=clusterid(grp,id);
	if (nc==0) return 0;
	cluster_size=(int *)malloc(nc*sizeof(int));
	for (i=0;i<nc;i++) cluster_size[i]=0;
	for (i=0;i<grp->nnode;i++) if (id[i]!=-1) cluster_size[id[i]]++;
	Gsize=0;
	for (i=0;i<nc;i++) if (Gsize<cluster_size[i]) Gsize=cluster_size[i];
	free(id);
	free(cluster_size);
	return Gsize;
}

GRAPH* extract_largest_cluster(GRAPH *grp) {
	int i,j,idx,nc;
	int *id,*cluster_size;
	GRAPH *GG;
	if (grp->nnode==0) return NULL;
	id=(int *)malloc(grp->nnode*sizeof(int));
	nc=clusterid(grp,id);
	if (nc==0) return NULL;
	cluster_size=(int *)malloc(nc*sizeof(int));
	for (i=0;i<nc;i++) cluster_size[i]=0;
	for (i=0;i<grp->nnode;i++) if (id[i]!=-1) cluster_size[id[i]]++;
	idx=0;
	for (i=1;i<nc;i++) if (cluster_size[idx]<cluster_size[i]) idx=i;
	GG=initialize_graph(grp->max_graph_size);
	GG->nnode=grp->nnode;
	for (i=0;i<grp->nnode;i++) {
		if (id[i]==idx) {
			GG->Adj[i]=(int *)malloc(grp->kn[i]*sizeof(int)); 
			for (j=0;j<grp->kn[i];j++)
				GG->Adj[i][j]=grp->Adj[i][j];
			GG->kn[i]=grp->kn[i];
			GG->kout[i]=grp->kout[i];
			GG->kin[i]=grp->kin[i];
			GG->nlink+=grp->kout[i];
		} else {
			GG->kn[i]=0;
			GG->kout[i]=0;
			GG->kin[i]=0;
		}
	}
	free(cluster_size);
	free(id);
	return GG;
}
