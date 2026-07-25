// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    vector<vector<int>> adjList(n+1);
    vector<int> degree(n+1,0);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(degree[i]==1){
            q.push(i);
        }
    }
    vector<bool> visited(n+1,false);
     int ans = 0;
     
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(int neigh:adjList[node]){
            if(!visited[neigh] && !visited[node]){
                ans++;
                visited[node] = true;
                visited[neigh] = true;
            }
            if(!visited[neigh]){
                q.push(neigh);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}