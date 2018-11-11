#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<string.h>
#include<fstream>
#include<cmath>
#include<sys/time.h>

using namespace std;

int mat_mul(vector<vector<double> > M_mat, vector<double> &rank,int n)
{
    vector<double> new_rank(n,0);
    long flag,a,b;

    #pragma omp_set_num_threads(4);
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


void calc_rank(long n, vector<double> &rank)
{
    long in_node, out_node, node, weight, i, j, k;
    double sum,donation,init_rank,rank_sum,rank_average,damping_factor;
    damping_factor = 0.85;
    init_rank = 1/(double)n;
    vector<long>outdegree(n,0);
    vector<vector<double> > A_mat(n, vector<double>(n,0));
    vector<vector<double> > B_mat(n, vector<double>(n,init_rank));
    vector<vector<double> > M_mat(n, vector<double>(n,init_rank));

    char file_name[30];
    string str;
    str = to_string(n);
    strcpy(file_name,str.c_str());
    strcat(file_name,"_regions.txt");

    ifstream file_read;
    file_read.open(file_name, ios::in);

    while(file_read>>out_node>>in_node>>weight)
    {
        outdegree[out_node] += weight;
    }
    file_read.clear();
    file_read.seekg(0);

    while(file_read>>out_node>>in_node>>weight)
    {
        A_mat[in_node][out_node] += weight/double(outdegree[out_node]);
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
        int ret_val = mat_mul(M_mat,rank,n);
        if(ret_val == 1)
            break;
    }
    rank_sum = 0;
    ofstream file_rank;
    file_rank.open("rank_update.csv",ios::app);

    for(i = 0 ; i < n ; i++)
    {
        rank_sum += rank[i];
        cout<<i<<" "<<rank[i] <<"\n";
        file_rank<<i<<" "<<rank[i]<<"\n";
    }
    cout<<"rank_sum = "<<rank_sum<<"\n";
    cout<<" k  = "<<k<<"\n";
    file_rank.close();
}


void traffic_prediction(int n, vector<double> importance_matrix, vector< vector<long> >adj_list, vector<long> &vehicle_count) {
    int i, j;
    long current_vehicle_count, vehicle_transfer_count;
    double total_rank;
    ofstream file_write,file_output;
    file_write.open("9_regions.txt",ios::out);
    file_output.open("output.csv",ios::app);

    for (i = 0; i < adj_list.size(); i++) {
        total_rank = 0;
        for (j = 0; j < adj_list[i].size(); j++) {
            total_rank += importance_matrix[adj_list[i][j]];
        }
        current_vehicle_count = vehicle_count[i];
        for (j = 0; j < adj_list[i].size(); j++) {
            vehicle_transfer_count = (importance_matrix[adj_list[i][j]] / total_rank) * current_vehicle_count;
            vehicle_count[i] -= vehicle_transfer_count;
            vehicle_count[adj_list[i][j]] += vehicle_transfer_count;
            file_write<<i<<" "<<adj_list[i][j]<<" "<<vehicle_transfer_count<<"\n";
        }
    }



    for (int k = 0; k < n ; ++k) {
        cout<<k<<" "<<vehicle_count[k]<<"\n";
        file_output<<k<<" "<<vehicle_count[k]<<"\n";
    }
    file_output.close();
    file_write.close();
}


int main()
{

    long n = 9, num_of_vehicles;
    long in_node, out_node, node, weight,region;
    int i;
    double init_rank;
    string file_name;
    string str;
    vector<vector<long> >adj_list(n);
    struct timeval start, end;
    gettimeofday(&start, NULL);

    init_rank = 1/(double)n;
    vector<double> page_rank(n, init_rank);
    vector<long> vehicle_count(n);

    calc_rank(n, page_rank);

    str = to_string(n);
    file_name = str + "_regions.txt";
    ifstream file_read;
    file_read.open(file_name.c_str(), ios::in);
    while(file_read>>out_node>>in_node>>weight){
        adj_list[out_node].push_back(in_node);
    }

    file_read.close();

    file_name = str + "_traffic.txt";
    file_read.open(file_name, ios::in);
    while(file_read>>region>>num_of_vehicles){
        vehicle_count[region] = num_of_vehicles;
    }

    file_read.close();

    for(i = 0; i < 5; i++){
        traffic_prediction(n, page_rank, adj_list, vehicle_count);
        calc_rank(n,page_rank);
    }

    gettimeofday(&end, NULL);

    cout<<"\n\n Time = "<< (((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6);
}