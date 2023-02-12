#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int M=1e5+5;
ll T,n,x,a[M],b[M],ans;
int main() {
	scanf("%lld",&T);
	while(T--) {
		scanf("%lld%lld",&n,&x);
		ll p=0,low=1e9;
		for(ll i=1;i<=n;i++) {
			b[i]=0;
			scanf("%lld",&a[i]);
			ll k=a[i];
			while(k%x==0) {
				b[i]++;
				k/=x;
			}
			if(b[i]<low) {
				low=b[i];
				p=i;
			}
		}
		ans=0;
		for(ll i=1;i<=n;i++) {
			ans+=a[i]*(low+1);
			if(i<p) ans+=a[i];
		}
		printf("%lld\n",ans);
	}
    return 0;
}

