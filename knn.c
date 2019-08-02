#include <graph.h>

double knn_out(GRAPH *grp, int inode) {
	int i,ksum,k;
	k=grp->kn[inode];
	ksum=0;
	for (i=0;i<k;i++) ksum+=grp->kout[grp->Adj[inode][i]];
	return (double)(ksum)/(double)k;
}

double knn_in(GRAPH *grp, int inode) {
	int i,ksum,k;
	k=grp->kn[inode];
	ksum=0;
	for (i=0;i<k;i++) ksum+=grp->kin[grp->Adj[inode][i]];
	return (double)(ksum)/(double)k;
}
