#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<string.h>
#include<fstream>
#include<cmath>

using namespace std;

int mat_mul(vector<vector<double> > M_mat, vector<double> &rank,int n)
{
	vector<double> new_rank(n,0);
	long flag,a,b;

	for(int i=0;i<n;i++)
	{
		for(int j =0;j<n;j++)
		{
			new_rank[i] += M_mat[i][j]*rank[j];
		}
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
	// for(i=0;i<n;i++)
	// {
	// 	for(j=0;j<n;j++)
	// 	{
	// 		cout<<M_mat[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }

	k = 0;
	while(1)
	{	
		k++;	
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
	// damping_factor = 0.85;
	// for(k = 1 ; k >0 ; k++)
	// {
	// 	rank_sum = 0;
	// 	for(i = 0;i<n;i++)
	// 	{
	// 		sum = 0;
	// 		for(j = 0;j<mymap[i].size();j++)
	// 		{
	// 			node = mymap[i][j];
	// 			donation = rank[node]/outdegree[node];
	// 			sum += donation; 
	// 		}
	// 		rank[i] = (1-damping_factor) + damping_factor*sum;
	// 		rank_sum += rank[i];
	// 	}
	// 	rank_average = rank_sum/n;
	// 	rank_average = rank_average*1000;
	// 	if(round(rank_average) == 1000)
	// 		break;
	// }
	// cout<<"No of iterations = "<<k<<"\n";

	// for(i=0;i<n;i++)
	// {
	// 	cout<<i<<" : "<<rank[i]<<"\n";
	// }
	// cout<<"Average = "<<rank_average/1000;
	}

int main()
{
	long n = 1000;
	calc_rank(n); 
}