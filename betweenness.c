#include <graph.h>

void betweenness(GRAPH *grp, double *D, double *B, double **L) {
	int i,j,k,idx,nvertex,nmax,maxsize;
	int stack_size,queue_size,head,tail;
	int *d;
	int *stack,*queue;
	int ***plist,*pi;
	double f;
	double *sigma;
	double *delta;

	nmax=grp->nnode;
	maxsize=grp->nlink;

	stack=(int *)malloc(maxsize*sizeof(int));
	queue=(int *)malloc(maxsize*sizeof(int));
	sigma=(double *)malloc(nmax*sizeof(double));
	delta=(double *)malloc(nmax*sizeof(double));
	d=(int *)malloc(nmax*sizeof(int));
	pi=(int *)malloc(nmax*sizeof(int));
	plist=(int ***)malloc(nmax*sizeof(int **));

	for(i=0;i<nmax;i++) {
		k=grp->kin[i];
		if (k!=0) {
			plist[i]=(int **)malloc(k*sizeof(int *));
			for (j=0;j<k;j++) 
				plist[i][j]=(int *)malloc(2*sizeof(int));
		}
		pi[i]=0;
		B[i]=0.0;
		D[i]=0.0;
		for (j=0;j<grp->kout[i];j++) L[i][j]=0.0;
	}

	for (i=0;i<nmax;i++) {
		if (grp->kout[i]==0) continue; 
		for (j=0;j<nmax;j++) {
			sigma[j]=0.0;
			delta[j]=1.0;
			d[j]=-1;
			pi[j]=0;
		}
		delta[i]=0.0;
		sigma[i]=1.0;
		d[i]=0;
		head=0;
		tail=0;
		queue_size=0;
		stack_size=0;
		queue[tail++]=i;
		tail=MOD(tail,maxsize);
		queue_size++;
		while(queue_size!=0) {
			j=queue[head++];
			head=MOD(head,maxsize);
			queue_size--;
			stack[stack_size++]=j;
			for (k=0;k<grp->kout[j];k++) {
				idx=grp->Adj[j][k];
				if (d[idx] < 0) {
					queue[tail++]=idx;
					tail=MOD(tail,maxsize);
					queue_size++;
					d[idx]=d[j]+1;
					sigma[idx]+=sigma[j];
					plist[idx][pi[idx]][0]=j;
					plist[idx][pi[idx]][1]=k;
					pi[idx]++;
				} else if (d[idx]==(d[j]+1)) {
					sigma[idx]+=sigma[j];
					plist[idx][pi[idx]][0]=j;
					plist[idx][pi[idx]][1]=k;
					pi[idx]++;
				}
			}
		}
		nvertex=stack_size;
		while (stack_size!=0) {
			j=stack[--stack_size];
			while (pi[j]!=0) {
				--pi[j];
				idx=plist[j][pi[j]][0];
				f=sigma[idx]/sigma[j]*delta[j];
				L[idx][plist[j][pi[j]][1]]+=f;
				delta[idx]+=f;
			}
			B[j]+=delta[j];
			if (j!=i) D[i]+=(double)d[j];
		}
		D[i]=D[i]/(double)(nvertex-1);
	}
	free(stack);
	free(queue);
	free(sigma);
	free(delta);
	free(d);
	free(pi);
	for (i=0;i<nmax;i++) { 
		k=grp->kin[i];
		if (k!=0) {
			for (j=0;j<k;j++) free(plist[i][j]);
			free(plist[i]);
		}
	}
	free(plist);
}

void betweenness2(GRAPH *grp, double *D, double *B) {
	int i,j,k,idx,nvertex,nmax,maxsize;
	int stack_size,queue_size,head,tail;
	int *d;
	int *stack,*queue;
	int **plist,*pi;
	double *sigma;
	double *delta;

	nmax=grp->nnode;
	maxsize=grp->nlink;

	stack=(int *)malloc(maxsize*sizeof(int));
	queue=(int *)malloc(maxsize*sizeof(int));
	sigma=(double *)malloc(nmax*sizeof(double));
	delta=(double *)malloc(nmax*sizeof(double));
	d=(int *)malloc(nmax*sizeof(int));
	pi=(int *)malloc(nmax*sizeof(int));
	plist=(int **)malloc(nmax*sizeof(int *));

	for(i=0;i<nmax;i++) {
		k=grp->kin[i];
		if (k!=0) plist[i]=(int *)malloc(k*sizeof(int));
		pi[i]=0;
		B[i]=0.0;
		D[i]=0.0;
	}

	for (i=0;i<nmax;i++) {
		if (grp->kout[i]==0) continue; 
		for (j=0;j<nmax;j++) {
			sigma[j]=0.0;
			delta[j]=1.0;
			d[j]=-1;
			pi[j]=0;
		}
		delta[i]=0.0;
		sigma[i]=1.0;
		d[i]=0;
		head=0;
		tail=0;
		queue_size=0;
		stack_size=0;
		queue[tail++]=i;
		tail=MOD(tail,maxsize);
		queue_size++;
		while(queue_size!=0) {
			j=queue[head++];
			head=MOD(head,maxsize);
			queue_size--;
			stack[stack_size++]=j;
			for (k=0;k<grp->kout[j];k++) {
				idx=grp->Adj[j][k];
				if (d[idx] < 0) {
					queue[tail++]=idx;
					tail=MOD(tail,maxsize);
					queue_size++;
					d[idx]=d[j]+1;
					sigma[idx]+=sigma[j];
					plist[idx][pi[idx]++]=j;
				} else if (d[idx]==(d[j]+1)) {
					sigma[idx]+=sigma[j];
					plist[idx][pi[idx]++]=j;
				}
			}
		}
		nvertex=stack_size;
		while (stack_size!=0) {
			j=stack[--stack_size];
			while (pi[j]!=0) {
				idx=plist[j][--pi[j]];
				delta[idx]+=sigma[idx]/sigma[j]*delta[j];
			}
			B[j]+=delta[j];
			if (j!=i) D[i]+=(double)d[j];
		}
		D[i]=D[i]/(double)(nvertex-1);
	}
	free(stack);
	free(queue);
	free(sigma);
	free(delta);
	free(d);
	free(pi);
	for (i=0;i<nmax;i++) { 
		if (grp->kin[i]!=0) free(plist[i]);
	}
	free(plist);
}

void betweenness3(GRAPH *grp, int **D, double *B) {
	int i,j,k,idx,nvertex,nmax,maxsize;
	int stack_size,queue_size,head,tail;
	int *stack,*queue;
	int **plist,*pi;
	double *sigma;
	double *delta;

	nmax=grp->nnode;
	maxsize=grp->nlink;

	stack=(int *)malloc(maxsize*sizeof(int));
	queue=(int *)malloc(maxsize*sizeof(int));
	sigma=(double *)malloc(nmax*sizeof(double));
	delta=(double *)malloc(nmax*sizeof(double));
	pi=(int *)malloc(nmax*sizeof(int));
	plist=(int **)malloc(nmax*sizeof(int *));

	for(i=0;i<nmax;i++) {
		k=grp->kin[i];
		if (k!=0) plist[i]=(int *)malloc(k*sizeof(int));
		pi[i]=0;
		B[i]=0.0;
	}

	for (i=0;i<nmax;i++) {
		if (grp->kout[i]==0) continue; 
		for (j=0;j<nmax;j++) {
			sigma[j]=0.0;
			delta[j]=1.0;
			D[i][j]=-1;
			pi[j]=0;
		}
		delta[i]=0.0;
		sigma[i]=1.0;
		D[i][i]=0;
		head=0;
		tail=0;
		queue_size=0;
		stack_size=0;
		queue[tail++]=i;
		tail=MOD(tail,maxsize);
		queue_size++;
		while(queue_size!=0) {
			j=queue[head++];
			head=MOD(head,maxsize);
			queue_size--;
			stack[stack_size++]=j;
			for (k=0;k<grp->kout[j];k++) {
				idx=grp->Adj[j][k];
				if (D[i][idx] < 0) {
					queue[tail++]=idx;
					tail=MOD(tail,maxsize);
					queue_size++;
					D[i][idx]=D[i][j]+1;
					sigma[idx]+=sigma[j];
					plist[idx][pi[idx]++]=j;
				} else if (D[i][idx]==(D[i][j]+1)) {
					sigma[idx]+=sigma[j];
					plist[idx][pi[idx]++]=j;
				}
			}
		}
		nvertex=stack_size;
		while (stack_size!=0) {
			j=stack[--stack_size];
			while (pi[j]!=0) {
				idx=plist[j][--pi[j]];
				delta[idx]+=sigma[idx]/sigma[j]*delta[j];
			}
			B[j]+=delta[j];
		}
	}
	free(stack);
	free(queue);
	free(sigma);
	free(delta);
	free(pi);
	for (i=0;i<nmax;i++) { 
		if (grp->kin[i]!=0) free(plist[i]);
	}
	free(plist);
}
