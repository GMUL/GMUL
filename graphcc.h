#include <iostream>
#include <string>
#include <graph.h>

using namespace std;

class Graph;

class Graph {
	public:
		GRAPH *grp;
		int **OUT;
		int *kout;
		int *kin;
		int *kn;
		int maxnode;
		int nlink;

		Graph(int max_size=1000000) { 
			grp=initialize_graph(max_size); 
			maxnode=grp->nnode;
			nlink=grp->nlink;
			OUT=grp->Adj;
			kout=grp->kout;
			kin=grp->kin;
			kn=grp->kn;
		};
		~Graph() { free_graph(grp); };


		void Clear();
		void Copy(Graph &);
		bool AddLink(int,int);
		void Merge(int,int);
		bool IsLinked(int,int);
		int InvertLink(int,int);
		bool Delete(int,int);
		bool Delete(int);
		int IN(int i,int j) { return OUT[i][kn[i]-kin[i]+j]; };
};

inline bool Graph::AddLink(int i,int  j) {
	bool tf;
	tf=addlink_graph(grp,i,j);
	maxnode=grp->nnode;
	nlink=grp->nlink;
	return tf;
}

inline void Graph::Merge(int i,int j) {
	merge_graph(grp,i,j);
	maxnode=grp->nnode;
	nlink=grp->nlink;
}

inline bool Graph::IsLinked(int i,int j) {
	return islinked_graph(grp,i,j);
}

inline int Graph::InvertLink(int i,int j) {
	return invert_link(grp,i,j);
}

inline bool Graph::Delete(int i,int j) {
	bool tf;
	tf=delete_link_graph(grp,i,j);
	maxnode=grp->nnode;
	nlink=grp->nlink;
	return tf;
}

inline bool Graph::Delete(int i) {
	bool tf;
	tf=delete_node_graph(grp,i);
	maxnode=grp->nnode;
	nlink=grp->nlink;
	return tf;
}

inline void Graph::Clear() {
	clear_graph(grp);
	maxnode=grp->nnode;
	nlink=grp->nlink;
}

inline void Graph::Copy(Graph &G0) {
	Clear();
	copy_graph(G0.grp,grp);
	maxnode=grp->nnode;
	nlink=grp->nlink;
}


inline void InputGraph(Graph &G) {
	input_graph_console(G.grp);
	G.maxnode=G.grp->nnode;
	G.nlink=G.grp->nlink;
};
inline void InputGraph(Graph &G,string fname) {
	input_graph_file(G.grp,fname.c_str());
	G.maxnode=G.grp->nnode;
	G.nlink=G.grp->nlink;
};
inline void OutputGraph(Graph &G) {
	output_graph_console(G.grp);
};
inline void OutputGraph(Graph &G,string fname) {
	output_graph_file(G.grp,fname.c_str());
};

inline void Betweenness(Graph &G,double *D,double *B,double **L) {
	betweenness(G.grp,D,B,L);
};

inline void Betweenness(Graph &G,double *D,double *B) {
	betweenness2(G.grp,D,B);
};

inline void Betweenness(Graph &G,int **D,double *B) {
	betweenness3(G.grp,D,B);
};

inline bool IsConnected(Graph &G) { 
	int i;
	i=isconnected(G.grp); 
	if (i==1) return true;
	if (i==0) return false;
};

inline int ClusterID(Graph &G,int *id) {
	return clusterid(G.grp,id);
};

inline int Largest_Cluser_Size(Graph &G) {
	return largest_cluster_size(G.grp);
};

inline void Extract_Largest_Cluster(Graph &G0, Graph &G1) {
	free_graph(G1.grp);
	G1.grp=extract_largest_cluster(G0.grp);
	G1.OUT=G1.grp->Adj;
	G1.kout=G1.grp->kout;
	G1.kin=G1.grp->kin;
	G1.kn=G1.grp->kn;
	G1.maxnode=G1.grp->nnode;
	G1.nlink=G1.grp->nlink;
};

inline int distance(Graph &G,int i,int j) { 
	return distance_graph(G.grp,i,j); 
};
inline int* distance(Graph &G,int i,int *d) { 
	return distance_graph_all(G.grp,i,d); 
};
inline double distance(Graph &G) { 
	return distance_graph_sum(G.grp); 
};

inline double clustering_coefficient(Graph &G,int i) {
	return ccoeff(G.grp,i);
};

inline double clustering_coefficient(Graph &G) {
	return ccoeff_global(G.grp);
};

inline double Knn_out(Graph &G,int i) { 
	return knn_out(G.grp,i); 
};
inline double Knn_in(Graph &G,int i) { 
	return knn_in(G.grp,i); 
};

inline int check_nnode(Graph &G) { 
	return check_nnode_graph(G.grp); 
};
inline int check_directed(Graph &G) { 
	return check_directed_graph(G.grp); 
};
