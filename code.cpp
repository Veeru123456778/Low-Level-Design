// // Online C++ compiler to run C++ program online
// #include <bits/stdc++.h>
// using namespace std;


// int findBoss(int x,int k,int heightOfTree, vector<vector<int>>& parentList){

//     int boss = x;
//     int val = k;
//     int p = 0;
//     while(val>0){
//         if(val & 1){
//             boss = parentList[boss][p];
//             if(boss==-1){
//                 return -1;
//             }
//         }
//         p++;
//         val = val>>1;
//     }
    
//     return boss;
// }

// void dfs(int node,int currDepth,vector<int>& depth,vector<vector<int>>& adjList,int parent,vector<int>& parentArr){
//     depth[node] = currDepth;
//     parentArr[node] = parent;

//     for(int neigh:adjList[node]){
//         if(neigh!=parent){
//         dfs(neigh,currDepth+1,depth,adjList,node,parentArr);
//         }
//     }
// }

// int lca(int u,int v,int heightOfTree, vector<vector<int>>& parentList,vector<int>& depth){
//   if(depth[u]>depth[v]){
//       swap(u,v);
//   }  
//   int heightDifference = depth[v]-depth[u];
//   v = findBoss(v,heightDifference,heightOfTree,parentList);
//     if (u == v) return u;

//   for(int p=heightOfTree;p>=0;p--){
//       if(parentList[u][p]!=parentList[v][p]){
//           u = parentList[u][p];
//           v = parentList[v][p];
//       }
//   }
//   if(u==v){
//     return u;
//   }
//   return parentList[u][0];
// }

// int main() {
//     int n, q;
//     cin>>n>>q;
//     vector<vector<int>> adjList(n+1);
//     vector<int> parent(n+1,-1);
    
//     for(int i=2;i<=n;i++){
//         int u,v;
//         cin>>u>>v;
//         adjList[v].push_back(u);
//         adjList[u].push_back(v);
//     }
//     vector<vector<int>> queries;
//     for(int i=0;i<q;i++){
//         int x,k;
//         cin>>x>>k;
//         queries.push_back({x,k});
//     }
//     int heightOfTree = ceil(log2(n));
//     vector<vector<int>> parentList(n+1,vector<int>(heightOfTree+1,-1));
//     vector<int> depth(n+1);
//     dfs(1,0,depth,adjList,-1,parent);


//     for(int i=2;i<=n;i++){
//        parentList[i][0] = parent[i]; 
//     }
//     for(int p=1;p<=heightOfTree;p++){
//         for(int i=2;i<=n;i++){
//             int halfWayParent = parentList[i][p-1];
//             parentList[i][p] = (halfWayParent==-1)?-1:parentList[halfWayParent][p-1];
//         }
//     }
    
   
    
//     for(auto& q:queries){
//         int x = q[0],k = q[1];
//         int ans = lca(x,k,heightOfTree,parentList,depth);
//         int dist = depth[x]+depth[k]-2*depth[ans];
//         cout<<dist<<endl;
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int findBoss(int x,int k,int heightOfTree, vector<vector<int>>& parentList){
    int boss = x;
    int val = k;
    int p = 0;
    while(val>0){
        if(val & 1){
            boss = parentList[boss][p];
            if(boss==-1) return -1;
        }
        p++;
        val >>= 1;
    }
    return boss;
}

void dfs(int node,int currDepth,vector<int>& depth,vector<vector<int>>& adjList,int parent,vector<int>& parentArr){
    depth[node] = currDepth;
    parentArr[node] = parent;
    for(int neigh:adjList[node]){
        if(neigh!=parent){
            dfs(neigh,currDepth+1,depth,adjList,node,parentArr);
        }
    }
}

int lca(int u,int v,int heightOfTree, vector<vector<int>>& parentList,vector<int>& depth){
    if(depth[u]>depth[v]) swap(u,v);
    int heightDifference = depth[v]-depth[u];
    v = findBoss(v,heightDifference,heightOfTree,parentList);
    if (u == v) return u;
    for(int p=heightOfTree;p>=0;p--){
        if(parentList[u][p]!=parentList[v][p]){
            u = parentList[u][p];
            v = parentList[v][p];
        }
    }
    return parentList[u][0];
}

int main() {
    int n, q;
    cin>>n>>q;
    vector<vector<int>> adjList(n+1);
    vector<int> parent(n+1,-1);

    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<vector<int>> queries;
    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        queries.push_back({a,b});
    }

    int heightOfTree = ceil(log2(n));
    vector<vector<int>> parentList(n+1,vector<int>(heightOfTree+1,-1));
    vector<int> depth(n+1);
    dfs(1,0,depth,adjList,-1,parent);

    for(int i=1;i<=n;i++) parentList[i][0] = parent[i];
    for(int p=1;p<=heightOfTree;p++){
        for(int i=1;i<=n;i++){
            int half = parentList[i][p-1];
            parentList[i][p] = (half==-1)?-1:parentList[half][p-1];
        }
    }

    for(auto& q:queries){
        int a=q[0], b=q[1];
        int ancestor = lca(a,b,heightOfTree,parentList,depth);
        int dist = depth[a]+depth[b]-2*depth[ancestor];
        cout<<dist<<"\n";
    }
    return 0;
}
