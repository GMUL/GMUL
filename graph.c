#include <graph.h>
#include <stdlib.h>

int* push_head(int *array, int *nsize, int data);
int* push_tail(int *array, int *nsize, int data);
void swap(int *array, int p1, int p2);
int* remove_data(int *array, int *nsize, int data);
int* remove_pos(int *array, int *nsize, int pos);
int find(int *array, int nsize, int data);

GRAPH* initialize_graph(int max_size) {
	GRAPH *grp;
	grp=(GRAPH *)malloc(sizeof(GRAPH));
	grp->max_graph_size=max_size;
	grp->nnode=0;
	grp->nlink=0;
	grp->Adj=(int **)malloc(grp->max_graph_size*sizeof(int *));
	grp->kout=(int *)malloc(grp->max_graph_size*sizeof(int));
	grp->kin=(int *)malloc(grp->max_graph_size*sizeof(int));
	grp->kn=(int *)malloc(grp->max_graph_size*sizeof(int));
	return grp;
}

void free_graph(GRAPH *grp) {
	int i;
	for (i=0;i<grp->nnode;i++) if (grp->kn[i]!=0) free(grp->Adj[i]);
	free(grp->Adj);
	free(grp->kout);
	free(grp->kin);
	free(grp->kn);
	grp->nnode=0;
	grp->nlink=0;
	free(grp);
}

void clear_graph(GRAPH *grp) {
	int i;
	for (i=0;i<grp->nnode;i++) {
		if (grp->kn[i]!=0) free(grp->Adj[i]);
		grp->kout[i]=0;
		grp->kin[i]=0;
		grp->kn[i]=0;
	}
	grp->nnode=0;
	grp->nlink=0;
}

int addlink_graph(GRAPH *grp,int from,int to) {
	int i,j,pout,pin;

	/* increase capacity */
	i=MAX(from+1,to+1);
	if (grp->nnode<i) {
		for (j=grp->nnode;j<i;j++) {
			grp->kout[j]=0;
			grp->kin[j]=0;
			grp->kn[j]=0;
		}
		grp->nnode=i;
	} 

	if (from==to) return 0;
	pout=find(grp->Adj[from],grp->kn[from],to);
	pin=find(grp->Adj[to],grp->kn[to],from);
	if (pout >= 0 && pout < grp->kout[from]) return 0;

	grp->nlink++;
	if (pout == -1 || pout == grp->kn[from]) {
	grp->Adj[from]=push_head(grp->Adj[from],&(grp->kn[from]),to);
	grp->Adj[to]=push_tail(grp->Adj[to],&(grp->kn[to]),from);
	grp->kout[from]++;
	grp->kin[to]++;
	return 1;
	}

	if (pout >= grp->kout[from]) {
	swap(grp->Adj[from],pout,grp->kout[from]);
	swap(grp->Adj[to],pin,grp->kn[to]-grp->kin[to]-1);
	grp->kout[from]++;
	grp->kin[to]++;
	return 1;
	}
}

int islinked_graph(GRAPH *grp,int from,int to) {
	int i;
	if (from >= grp->nnode || to >= grp->nnode) return 0;
	i=find(grp->Adj[from],grp->kn[from],to);
	if (i>=0 && i < grp->kout[from]) return 1;
	return 0;
}

int invert_link(GRAPH *grp,int from,int to) {
	int i;
	if (from >= grp->nnode || to >= grp->nnode) return -1;
	i=find(grp->Adj[to],grp->kn[to],from);
	if (i>=0 && i < grp->kout[to]) return i;
	return -1;
}

int delete_link_graph(GRAPH *grp,int from,int to) {
	int i,j,pout,pin;

	if (from >= grp->nnode || to >= grp->nnode) return 0;

	pout=find(grp->Adj[from],grp->kn[from],to);
	pin=find(grp->Adj[to],grp->kn[to],from);
	if (pout < 0 || pout >= grp->kout[from]) return 0;

	if (pout >= (grp->kn[from]-grp->kin[from])) {
	swap(grp->Adj[from],pout,grp->kout[from]-1);
	swap(grp->Adj[to],pin,(grp->kn[to]-grp->kin[to]));
	} else {
	grp->Adj[from]=remove_pos(grp->Adj[from],&(grp->kn[from]),pout);
	grp->Adj[to]=remove_pos(grp->Adj[to],&(grp->kn[to]),pin);
	}
	grp->kout[from]--;
	grp->kin[to]--;
	grp->nlink--;
	return 1;
}
	
int delete_node_graph(GRAPH *grp,int inode) {
	int i,j,tg;
	if (inode>=grp->nnode) return 0;
	if (grp->kn[inode]==0) return 0; 
	j=grp->kn[inode]-grp->kin[inode];
	// remove outgoing links
	for (i=0;i<j;i++) {
	tg=grp->Adj[inode][i];
	grp->Adj[tg]=remove_data(grp->Adj[tg],&(grp->kn[tg]),inode);
	grp->kin[tg]--;
	}
	// remove bidirectional links
	for (i=j;i<grp->kout[inode];i++) {
	tg=grp->Adj[inode][i];
	grp->Adj[tg]=remove_data(grp->Adj[tg],&(grp->kn[tg]),inode);
	grp->kout[tg]--;
	grp->kin[tg]--;
	}
	// remove incoming links
	for (i=grp->kout[inode];i<grp->kn[inode];i++) {
	tg=grp->Adj[inode][i];
	grp->Adj[tg]=remove_data(grp->Adj[tg],&(grp->kn[tg]),inode);
	grp->kout[tg]--;
	}
	// remove the node;
	free(grp->Adj[inode]);
	grp->nlink-=(grp->kout[inode]+grp->kin[inode]);
	grp->kout[inode]=0;
	grp->kin[inode]=0;
	grp->kn[inode]=0;
	return 1;
}

void copy_graph(GRAPH *grp0, GRAPH *grp1) {
	int i,j;
	clear_graph(grp1);
	grp1->nnode=grp0->nnode;
	grp1->nlink=grp0->nlink;
	grp1->max_graph_size=grp0->max_graph_size;
	for (i=0;i<grp1->nnode;i++) {
		grp1->kout[i]=grp0->kout[i];
		grp1->kin[i]=grp0->kin[i];
		grp1->kn[i]=grp0->kn[i];
		grp1->Adj[i]=(int *)malloc(grp1->kn[i]*sizeof(int));
		for (j=0;j<grp1->kn[i];j++) grp1->Adj[i][j]=grp0->Adj[i][j];
	}
}

int* push_head(int *array, int *nsize, int data) {
	int i,*newarray;
	newarray=(int *)malloc((*nsize+1)*sizeof(int));
	newarray[0]=data;
	for (i=0;i<*nsize;i++) newarray[i+1]=array[i];
	if (*nsize!=0) free(array);
	(*nsize)++;
	return newarray;
}

int* push_tail(int *array, int *nsize, int data) {
	int i,*newarray;
	newarray=(int *)malloc((*nsize+1)*sizeof(int));
	newarray[*nsize]=data;
	for (i=0;i<*nsize;i++) newarray[i]=array[i];
	if (*nsize!=0) free(array);
	(*nsize)++;
	return newarray;
}

void swap(int *array, int p1, int p2) {
	int tmp;
	tmp=array[p1];
	array[p1]=array[p2];
	array[p2]=tmp;
}

int find(int *array, int nsize, int data) {
	int i;
	if (nsize==0) return -1;
	for (i=0;i<nsize;i++) if (array[i]==data) break;
	return i;
}

int* remove_data(int *array, int *nsize, int data) {
	int i,pos,*newarray;
	pos=find(array,*nsize,data);
	if (pos==-1) return NULL;
	if (pos==*nsize) return array;
	if (*nsize==1) {
		free(array);
		(*nsize)--;
		return NULL;
	}
	newarray=(int *)malloc((*nsize-1)*sizeof(int));
	for (i=0;i<pos;i++) newarray[i]=array[i];
	for (i=pos+1;i<*nsize;i++) newarray[i-1]=array[i];
	free(array);
	(*nsize)--;
	return newarray;
}

int* remove_pos(int *array, int *nsize, int pos) {
	int i,*newarray;
	if (pos>=*nsize) return array;
	if (*nsize==0) return array;
	if (*nsize==1) {
		free(array);
		(*nsize)--;
		return NULL;
	}
	newarray=(int *)malloc((*nsize-1)*sizeof(int));
	for (i=0;i<pos;i++) newarray[i]=array[i];
	for (i=pos+1;i<*nsize;i++) newarray[i-1]=array[i];
	free(array);
	(*nsize)--;
	return newarray;
}

