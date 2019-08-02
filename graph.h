#include <stdio.h>
#include <stdlib.h>

/* the definition of graph structure */

typedef struct graph_ {
	int nnode;
	int nlink;
	int **Adj;
	int *kout;
	int *kin;
	int *kn;
	int max_graph_size;
} GRAPH;

/* elementary operations of graph structure */

GRAPH* initialize_graph(int max_size);
void free_graph(GRAPH *grp);
void clear_graph(GRAPH *grp);
int addlink_graph(GRAPH *grp,int from,int to);
int islinked_graph(GRAPH *grp,int from,int to);
int invert_link(GRAPH *grp,int from,int to);
int delete_link_graph(GRAPH *grp,int from,int to);
int delete_node_graph(GRAPH *grp,int inode);
void copy_graph(GRAPH *grp0,GRAPH *grp1);

/* graphio.c */
void input_graph_console(GRAPH *grp);
void input_graph_file(GRAPH *grp,const char *fname);
void output_graph_console(GRAPH *grp);
void output_graph_file(GRAPH *grp,const char *fame);

/* ccoeff.c */
double ccoeff(GRAPH *grp,int i);
double ccoeff_global(GRAPH *grp);

/* knn.c */
double knn_out(GRAPH *grp,int i);
double knn_in(GRAPH *grp,int i);

/* check.c */
int check_nnode_graph(GRAPH *grp);
int check_directed_graph(GRAPH *grp);

/* betweenness.c */
void betweenness(GRAPH *grp,double *D,double *B,double **L);
void betweenness2(GRAPH *grp,double *D,double *B);
void betweenness3(GRAPH *grp,int **D,double *B);

/* distance.c */
int distance_graph(GRAPH *grp,int from,int to);
int* distance_graph_all(GRAPH *grp,int i,int *d);
double distance_graph_sum(GRAPH *grp);

/* cluster.c */
int isconnected(GRAPH *grp);
int clusterid(GRAPH *grp,int *id);
int largest_cluster_size(GRAPH *grp);
GRAPH* extract_largest_cluster(GRAPH *grp);

/* merge.c */
void merge_graph(GRAPH *grp,int n1,int n2);

#define NNODE(grp) ((grp)->nnode)
#define NLINK(grp) ((grp)->nlink)
#define ADJ(grp) ((grp)->Adj)
#define KOUT(grp) ((grp)->kout)
#define KIN(grp) ((grp)->kin)
#define KN(grp) ((grp)->kn)
#define MAX(a,b) (a>=b ? a : b)
#define MIN(a,b) (a<b ? a : b)
#define MOD(a,b) (a<b ? a : a-b)
