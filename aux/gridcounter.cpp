#include <iostream>
#include <vector>
#define N 4
#define M 5
using namespace std;
typedef unsigned long long ull;
vector<vector<int > > grid(N+2, vector<int> (N+2,0));

ull dfs(int i, int j, int d) {
  if (grid[i][j]==0) return 0;
  if (d==M) return 1;
  ull ans=1;
  grid[i][j]=0;
  for (int k=-1; k<=1; k++) 
    for (int l=-1; l<=1; l++) 
      ans += dfs(i+k, j+l, d+1);
      
  grid[i][j]=1;
  return ans;
}

int main() {
  ull ans=0;
  //inicializa os caminhos validos na grid
  for (int k=1; k<=N; k++)
    for (int l=1; l<=N; l++)
      grid[k][l]=1;

  //computa o resultado
  for (int i=1; i<=N; i++)
    for (int j=1; j<=N; j++)
      ans += dfs(i,j,1);
  
  cout << "There are " << ans << " paths with lenght <= " << M << " in a " << N << " by " << N << " grid" << endl;
}
