#include <iostream>
#include <cassert>
const int MX = 1e5 +10;
using namespace std;
int arr[MX], n;
 
int query(int i){
  cout << "? 2 " << i << " " << i + 1 << " 1" << endl; 
  int d; cin >> d;
  if(d == 1){
    return i;
  } 
  if(d == 2){
    cout << "? 2 " << i + 1 << " " << i << " 1" << endl;
    cin >> d;
    if(d == 1) return i + 1;
  }
  return 0;
}
 
 
int findmin(){
  for(int i = 1; i<=n-1; i+=2){
    int x = query(i);
    if(x > 0) return x;
  }
  return n;
}
 
 
 
int main(){
  cin.tie(0) -> sync_with_stdio(0);
  int T; cin >> T;
  while(T--){
    cin >> n;
    int m = findmin();
    for(int i = 1; i<=n; i++){
      if(i == m) continue;
      cout << "? 1 " << m << " " << i << " " << n - 1 << endl;
      cin >> arr[i];
    }
    arr[m] = 1;
    cout << "!";
    for(int i = 1; i<=n; i++) cout << " " << arr[i]; cout << endl;
  }
  return 0;
}

