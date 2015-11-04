/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//http://www.spoj.com/problems/DOTAA/

#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

#define sp system("pause")
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define FORD(i,a,b) for(int i=a;i>=b;--i)
#define REP(i,n) FOR(i,0,(int)n-1)
#define DB(format,...) fprintf(stderr,format, ##__VA_ARGS__)
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define MS0(x) memset(x,0,sizeof(x))
#define MS1(x) memset(x,1,sizeof(x))
#define SORT(a,n) sort(begin(a),begin(a)+n)
#define REV(a,n) reverse(begin(a),begin(a)+n)
#define ll long long
#define pii pair<int,int>
#define MOD 1000000007

int main(){

	int t, n, m, d;
	scanf("%d", &t);
	REP(tc, t){
		scanf("%d%d%d", &n, &m, &d);
		priority_queue<int> pq;
		REP(i, n) {
			int x;
			scanf("%d", &x);
			pq.push(x);
		}
		int possible = 1;
		while (m--) {
			int lead = pq.top();
			pq.pop();
			lead -= d;
			if (lead<=0) {
				possible = 0;
				break;
			}
			pq.push(lead);
		}
		puts(possible?"YES":"NO");
	}
	sp;
	return 0;
}

//Solved