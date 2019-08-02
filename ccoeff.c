#include <graph.h>

double ccoeff(GRAPH *grp, int k) {
	int i,j,n,cmu,idx1,idx2;
	cmu=0;
	if (grp->kn[k] < 2) return 0.0;
	for (i=0;i<grp->kn[k]-1;i++) {
		idx1=grp->Adj[k][i];
		for (j=i+1;j<grp->kn[k];j++) {
			idx2=grp->Adj[k][j];
			for (n=0;n<grp->kn[idx2];n++)
				if (grp->Adj[idx2][n]==idx1) {
					cmu++;
					break;
				}
		}
	}
	return (double)cmu/(0.5*(double)(grp->kn[k]*(grp->kn[k]-1)));
}

double ccoeff_global(GRAPH *grp) {
	int i,j,k,l,m,idx1,idx2,tri=0;
	double csum=0.0;
	for (i=0;i<grp->nnode;i++) {
		k=grp->kn[i];
		if (k<=1) continue;
		csum+=(double)(k*(k-1)/2);
		for (j=0;j<k-1;j++) {
			idx1=grp->Adj[i][j];
			for (l=j+1;l<k;l++) {
				idx2=grp->Adj[i][l];
				for (m=0;m<grp->kn[idx2];m++) {
					if (grp->Adj[idx2][m]==idx1) {
						tri++;
						break;
					}
				}
			}
		}
	}
	return (double)tri/csum;
}

