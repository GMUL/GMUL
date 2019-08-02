#include <graph.h>

void input_graph_console(GRAPH *grp) {
	int nResult,from,to;
	while(1) {
		nResult=scanf("%d %d",&from,&to);
		if (nResult==EOF) break;
		addlink_graph(grp,from,to); 
	}
}

void input_graph_file(GRAPH *grp,const char *fname) {
	int nResult,from,to;
	FILE *fp;
	fp=fopen(fname,"r");
	while(1) {
		nResult=fscanf(fp,"%d %d",&from,&to);
		if (nResult==EOF) break;
		addlink_graph(grp,from,to);
	}
	fclose(fp);
}

void output_graph_console(GRAPH *grp) {
	int i,j;
	for (i=0;i<grp->nnode;i++)
		for (j=0;j<grp->kout[i];j++)
			printf("%d %d\n",i,grp->Adj[i][j]);
}

void output_graph_file(GRAPH *grp,const char *fname) {
	int i,j;
	FILE *fp;
	fp=fopen(fname,"w");
	for (i=0;i<grp->nnode;i++)
		for (j=0;j<grp->kout[i];j++)
			fprintf(fp,"%d %d\n",i,grp->Adj[i][j]);
	fclose(fp);
}
