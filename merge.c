#include <graph.h>

void merge_graph(GRAPH *grp,int n1,int n2) {
	int i,j,k,from,to;
	for (i=0;i<grp->kout[n2];i++) {
		to=grp->Adj[n2][i];
		if (to!=n1) addlink_graph(grp,n1,to);
	}
	for (i=0;i<grp->kin[n2];i++) { 
		from=grp->Adj[n2][grp->kn[n2]-grp->kin[n2]+i];
		if (from!=n1) addlink_graph(grp,from,n1);
	}
/* test routine
	for (i=0;i<grp->kn[n2];i++) {
		for (j=0;j<grp->kn[n1];j++) 
			if (grp->Adj[n2][i]==grp->Adj[n1][j]) break;
		if (j==grp->kn[n1]) {
			printf("ERROR\n");
			printf("%d (%d,%d,%d) :",n1,grp->kn[n1],grp->kout[n1],grp->kin[n1]);
			for (k=0;k<grp->kn[n1];k++) 
				printf(" %d",grp->Adj[n1][k]);
			printf("\n");
			printf("%d %d,%d,%d :",n2,grp->kn[n2],grp->kout[n2],grp->kin[n2]);
			for (k=0;k<grp->kn[n2];k++) 
				printf(" %d",grp->Adj[n2][k]);
			printf("\n");
			exit(0);
		}
	}
*/
	delete_node_graph(grp,n2);
}
