#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int M=3e5+5;
ll T,n,m,c[M],ans;
int k[M];
int main() {
	scanf("%lld",&T);
	while(T--) {
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++) scanf("%d",&k[i]);
		for(int i=1;i<=m;i++) scanf("%lld",&c[i]);
		sort(k+1,k+1+n);
		int p=0;
		ans=0;
		for(int i=n;i;i--) {
			if(k[i]>=p+1) ans+=c[++p];
			else ans+=c[k[i]];
		}
		printf("%lld\n",ans);
	}
    return 0;
}

