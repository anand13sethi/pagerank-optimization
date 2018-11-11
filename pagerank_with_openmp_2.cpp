#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<string.h>
#include<fstream>
#include<cmath>
#include<time.h>

using namespace std;

int mat_mul(vector<vector<double> > M_mat, vector<double> &rank,int n)
{
	vector<double> new_rank(n,0);
	long flag,a,b;
	#pragma omp parallel for schedule(static)
	
	for(int i=0;i<n;i++)
	{
		double temp = 0;
		for(int j =0;j<n;j++)
		{
			temp += M_mat[i][j]*rank[j];
		}
		new_rank[i] = temp;
	}

	flag = 0;
	for(int i=0;i<n;i++)
	{	
		a = rank[i] * 1000000;
		b = new_rank[i] * 1000000;
		if(a != b)
		{
			flag = 1;
			break;
		}
	}	

	if(flag == 0)
		return 1;
	for(int i=0;i<n;i++)
	{	
		rank[i] = new_rank[i];
	}

	return 0;
}

void calc_rank(long n)
{
	long in_node,out_node,node,i,j,k;
	double sum,donation,init_rank,rank_sum,rank_average,damping_factor;
	damping_factor = 0.85;
	init_rank = 1/(double)n;
	vector<long>outdegree(n,0);
	vector<double>rank(n,init_rank);
	vector<vector<double> > A_mat(n, vector<double>(n,0));
	vector<vector<double> > B_mat(n, vector<double>(n,init_rank));
	vector<vector<double> > M_mat(n, vector<double>(n,init_rank));
	
	char file_name[30];
	string str;
	str = to_string(n);
	strcpy(file_name,str.c_str());
	strcat(file_name,"_nodes.txt");
	
	ifstream file_read;
	file_read.open(file_name, ios::in);

	while(file_read>>out_node>>in_node)
	{
		outdegree[out_node]++;
	}
	file_read.clear();
	file_read.seekg(0);

	while(file_read>>out_node>>in_node)
	{
		A_mat[in_node][out_node] += 1/double(outdegree[out_node]);
	}
	file_read.close();


	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			M_mat[i][j] = (damping_factor * A_mat[i][j]) + ((1 - damping_factor) * B_mat[i][j]);
		}
	}


	k = 0;
	while(1)
	{	
		k++;	
		cout<<k<<" ";
		int ret_val = mat_mul(M_mat,rank,n);
		if(ret_val == 1)
			break;
	}
	rank_sum = 0;
	for(i = 0 ; i < n ; i++)
	{
		rank_sum += rank[i];
		cout<<rank[i] <<"\n";
	}
	cout<<"rank_sum = "<<rank_sum<<"\n";
	cout<<k;
}

int main()
{	
	clock_t start, end;
    double cpu_time_used;
	long n = 1000;
	start = clock();
	calc_rank(n); 
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"\n\n Time = "<<cpu_time_used;
}
