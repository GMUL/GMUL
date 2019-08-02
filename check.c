#include <graph.h>

int check_nnode_graph(GRAPH *grp) {
	int i,n;
	n=0;
	for (i=0;i<grp->nnode;i++) {
		if (grp->kout[i]==0 && grp->kin[i]==0) continue;
		n++;
	}
	return n;
}

int check_directed_graph(GRAPH *grp) {
	int i,j;
	for (i=0;i<grp->nnode;i++) 
		for (j=0;j<grp->kout[i];j++) 
			if (!islinked_graph(grp,grp->Adj[i][j],i)) return 1;
	return 0;
}
