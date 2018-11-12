#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<string.h>
#include<fstream>
#include<cmath>
#include<omp.h>

using namespace std;

void calc_rank(long n)
{
	long in_node,out_node,node,i,j,k;
	double sum,damping_factor,donation,init_rank,rank_sum,rank_average;
	init_rank = 1/(double)n;
	vector<long>outdegree(n,0);
	vector<double>rank(n,init_rank);
	vector<vector<long> > mymap(n);
	char file_name[30];
	string str;
	str = to_string(n);
	strcpy(file_name,str.c_str());
	strcat(file_name,"_nodes.txt");
	
	ifstream file_read;
	file_read.open(file_name);

	while(file_read>>out_node>>in_node)
	{
		outdegree[out_node]++;
		mymap[in_node].push_back(out_node);
	}

	damping_factor = 0.85;
	for(k = 1 ; k >0 ; k++)
	{
		rank_sum = 0;
		for(i = 0;i<n;i++)
		{
			sum = 0;
			for(j = 0;j<mymap[i].size();j++)
			{
				node = mymap[i][j];
				donation = rank[node]/outdegree[node];
				sum += donation; 
			}
			rank[i] = (1-damping_factor) + damping_factor*sum;
			rank_sum += rank[i];
		}
		rank_average = rank_sum/n;
		rank_average = rank_average*1000;
		if(round(rank_average) == 1000)
			break;
	}

	for(i=0;i<n;i++)
	{
		cout<<i<<" : "<<rank[i]<<"\n";
	}
	cout<<"Average = "<<rank_average/1000;
	cout<<"No of iterations = "<<k<<"\n";


}

int main()
{
	double t1, t2;
    double cpu_time_used;
	long n = 500;
	t1 = omp_get_wtime();
	calc_rank(n); 
	t2 = omp_get_wtime();
	cpu_time_used = t2-t1;
	cout<<"\n\n Time = "<<cpu_time_used;
}