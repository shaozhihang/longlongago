#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int M=1e5+5;
int T,n,x,a[M]; 
ll sum,ans;
int main() {
	scanf("%d",&T);
	while(T--) {
		sum=0;
		ans=0;
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			sum+=(ll)a[i];
			if(a[i]%x==0) ans+=(ll)a[i]/x;
			else ans+=(ll)a[i]/x+1;
		}
		if(sum%(ll)x==0) printf("%lld ",sum/(ll)x);
		else printf("%lld ",sum/(ll)x+1);
		printf("%lld\n",ans);
	}
    return 0;
}

