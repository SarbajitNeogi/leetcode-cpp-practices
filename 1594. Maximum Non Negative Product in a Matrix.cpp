//dfs with memorization
//Runtime: 24 ms, faster than 16.04% of C++ online submissions for Maximum Non Negative Product in a Matrix.
//Memory Usage: 15.1 MB, less than 5.04% of C++ online submissions for Maximum Non Negative Product in a Matrix.
class Solution {
public:
    int m, n;
    long long maxprod;
    vector<vector<vector<long long>>> memo;
    
    void dfs(vector<vector<int>>& grid, int r, int c, long long prod){
        prod *= grid[r][c];
        // cout << r << ", " << c << endl;
        if(r == m-1 && c == n-1){
            // cout << prod << endl;
            maxprod = max(maxprod, prod);
        }else{
            if(r+1 < m){
                dfs(grid, r+1, c, prod);
            }
            
            if(c+1 < n){
                dfs(grid, r, c+1, prod);
            }
        }
    };
    
    vector<long long> dfs_back(vector<vector<int>>& grid, int endr, int endc){
        // cout << endr << ", " << endc << endl; //", " << pos << endl;
        if(endr == 0 && endc == 0){
            return memo[0][0] = {grid[0][0], grid[0][0]};
        }else if(memo[endr][endc][0] != std::numeric_limits<long long>::lowest()){
            return memo[endr][endc];
        }else{
            long long maxres = std::numeric_limits<long long>::lowest();
            long long minres = std::numeric_limits<long long>::max();
            // res = grid[endr][endc];
            
            // bool newpos = pos;
            // if(grid[endr][endc] < 0) newpos = !newpos;
            
            bool pos = grid[endr][endc] > 0;
            if(endr-1 >= 0){
                vector<long long> ret = dfs_back(grid, endr-1, endc);
                maxres = max(maxres, pos ? ret[1] * grid[endr][endc] : ret[0] * grid[endr][endc]);
                minres = min(minres, pos ? ret[0] * grid[endr][endc] : ret[1] * grid[endr][endc]);
            }
            if(endc-1 >= 0){
                vector<long long> ret = dfs_back(grid, endr, endc-1);
                maxres = max(maxres, pos ? ret[1] * grid[endr][endc] : ret[0] * grid[endr][endc]);
                minres = min(minres, pos ? ret[0] * grid[endr][endc] : ret[1] * grid[endr][endc]);
            }
            
            return memo[endr][endc] = {minres, maxres};
        }
    };
    
    int maxProductPath(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        maxprod = std::numeric_limits<long long>::lowest();
        memo = vector<vector<vector<long long>>>(m, vector<vector<long long>>(n, vector<long long>(2, std::numeric_limits<long long>::lowest())));
        
        int MOD = 1e9 + 7;
        
        long long prod = 1LL;
        // dfs(grid, 0, 0, prod);
        // if(maxprod < 0) return -1;
        // return maxprod % MOD;
        
        vector<long long> res = dfs_back(grid, m-1, n-1);
        
//         for(int i = 0; i < m; ++i){
//             for(int j = 0; j < n; ++j){
//                 cout << memo[i][j][0] << " ";
//             }
//             cout << endl;
//         }
        
//         for(int i = 0; i < m; ++i){
//             for(int j = 0; j < n; ++j){
//                 cout << memo[i][j][1] << " ";
//             }
//             cout << endl;
//         }
        
        if(res[1] < 0) return -1;
        return res[1] % MOD;
    }
};
