/*************************************************************************
    > File Name:    test.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Thu 11 Apr 2019 10:55:20 PM CST
 ************************************************************************/

#include <bits/stdc++.h>
using namespace std;

const int process_nums = 5;
const int resource_nums = 3;
enum {
    RUNNING = 0,
    SLEEP
};

struct Process
{
    Process(int id):pid(id), state(SLEEP){}
    int pid;
    int state;
};

void print(const vector<int>& available,
           const vector<vector<int>>& max_request,
           const vector<vector<int>>& need,
           const vector<vector<int>>& allocation)
{
    printf("available:  ");
    for(int i = 0; i < resource_nums; i++)
        printf("%d  ", available[i]);
    printf("\n");
    printf("proc max_request allocation   need    \n");
    for(int i = 0; i < process_nums; i++){
        printf("p%d:   ", i);
        for(int j = 0; j < resource_nums; j++)
            printf("%d ", max_request[i][j]);
        for(int j = 0; j < resource_nums; j++)
            printf("%d ", allocation[i][j]);
        for(int j = 0; j < resource_nums; j++)
            printf("%d ", need[i][j]);
        printf("\n");        
    }
}
void init(vector<int>& available,
          vector<vector<int>>& max_request,
          vector<vector<int>>& need,
          vector<vector<int>>& allocation)
{   
    cout << "available:" << endl;
    for(int j = 0; j < resource_nums; j++){
        cout << "resource:No." << j << "   ";
        cin >> available[j];
        cout << endl;
    }                                                                     
    for(int i = 0; i < process_nums; i++){
        cout << "process(pid=" << i << "):"<< endl;
        cout << "max_request:" << endl;
        for(int j = 0; j < resource_nums; j++){
            cout << "resource:No." << j << "   " ;
            cin >> max_request[i][j];
        }
        cout << endl;
        cout << "allocation:" << endl;
        for(int j = 0; j < resource_nums; j++){
            cout << "resource:No." << j << "   ";
            cin >> allocation[i][j];
            need[i][j] = max_request[i][j] - allocation[i][j];
        }
        cout << endl;

    }
} 

bool inline isNeedResource(int now_running_process, const vector<vector<int>>& need)
{
    for(int i = 0; i < resource_nums; i++){
        if(need[now_running_process][i] != 0)
            return true;
    }
    return false;
}
bool isSomeProcessNeedResource(const vector<vector<int>>& need)
{
    for(int i = 0; i < process_nums; i++){
        if(isNeedResource(i, need))
            return true;
    }
    return false;
}
int scheProcess(const vector<vector<int>>& need)
{
    // default_random_engine rand;
    // int now_running_process;
    // do{
    //     now_running_process = rand()%process_nums;
    // }while(!isNeedResource(now_running_process, need));

    // return now_running_process;
    return 1;
}
void inline getRequest(int now_running_process, vector<vector<int>>& request)
{
    cout << "input now process(pid = "<< now_running_process << ") request:" << endl;
    for(int i = 0; i < resource_nums; i++){
        cout << "resource No." << i << "    ";
        cin >> request[now_running_process][i];
    }
}
bool judgeNeed(const vector<int>& process_need, const vector<int>& work)
{
    for(int i = 0; i < resource_nums; i++){
        if(process_need[i] > work[i])
            return false;
    }
    return true;
}
int judgeSecurity(const vector<int>& available, 
                  const vector<vector<int>>& need, 
                  const vector<Process>& process,
                  const vector<vector<int>> &allocation)
{
    vector<int> work(available);
    vector<bool> finish(process_nums, false);
    vector<int> security_list;
    int p_nums = process_nums;
    while(p_nums){
        int s = p_nums;
        for(int i = 0; i < process_nums; i++){
            if(finish[i] == false && judgeNeed(need[i], work)){
                finish[i] = true;
                p_nums--;
                security_list.push_back(i);
                for(int j = 0; j < resource_nums; j++)
                    work[j] += allocation[i][j];
            }
        }
        if(s == p_nums)
            return -1;
    }
    cout << "security_list is :"<< endl;
    for(auto i : security_list)
        cout << "p" << i << "->";
    cout << "end" << endl;
    return 0;
}
int main()
{
    freopen("banker-in", "r", stdin);
	vector<int> available(resource_nums, 0);
	vector<vector<int>> max_request(process_nums, vector<int>(resource_nums, 0));
    vector<vector<int>> allocation(max_request), need(max_request), request(max_request);
    vector<Process> process;
    for(int i = 0; i < process_nums; i++)
        process.push_back(Process(i));
    init(available, max_request, need, allocation);
    cout << "-------------------------------------" << endl;
    print(available, max_request, need, allocation);
    int now_running_process = 0;

    int debug = 1;
    while(debug--){

    // while(isSomeProcessNeedResource(need)){
        now_running_process = scheProcess(need);
        process[now_running_process].state = RUNNING;
        getRequest(now_running_process, request);
        for(int i = 0; i < resource_nums; i++){
            if(request[now_running_process][i] > need[now_running_process][i]){
                cout << "request error" << endl;
                return -1;
            }
            if(request[now_running_process][i] > available[i]){
                process[now_running_process].state = SLEEP;
                break;
            }
        }
        if(process[now_running_process].state == RUNNING){
            for(int i = 0; i < resource_nums; i++){
                available[i] -= request[now_running_process][i];
                allocation[now_running_process][i] += request[now_running_process][i];
                need[now_running_process][i] -= request[now_running_process][i];                
            }

            print(available, max_request, need ,allocation);

            if(judgeSecurity(available, need, process, allocation) == -1){
                for(int i = 0; i < resource_nums; i++){
                    available[i] += request[now_running_process][i];
                    allocation[now_running_process][i] -= request[now_running_process][i];
                    need[now_running_process][i] += request[now_running_process][i];                     
                }
                cout << "now is not security" << endl;
            } else{
                cout << "now is security" << endl;
            }
            process[now_running_process].state = SLEEP;
             
        }
    }

	return 0;
}
