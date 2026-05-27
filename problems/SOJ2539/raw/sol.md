考虑求出

$$FWT(B)[s]= \prod FWT(A_i)[s] = \prod (1+(-1)^{|s\ \text{AND}\ i|}\times a_i)$$

使用类似 FWT 的分治求出每一项的值。

记 $U[s]=\prod (1+(-1)^{|s\ \text{AND}\ i|}\times a_i),V[s]=\prod (1+(-1)^{|s\ \text{AND}\ i|+1}\times a_i)$，则最后要求的是 $U[s]$。

设分治左部区间的答案为 $U_l,V_l$，右部区间的答案为 $U_r,V_r$，则有 $U=U_lU_r+U_lV_r,V=V_lV_r+V_lU_r$（此处加号为拼接）。

```cpp
for(int len=1;len<(1<<n);len<<=1){
	for(int i=0;i<(1<<n);i+=(len<<1)){
		for(int j=0;j<len;j++){
			int ul=u[i+j],vl=v[i+j],ur=u[i+j+len],vr=v[i+j+len];
			u[i+j]=1ull*ul*ur%mod,v[i+j]=1ull*vl*vr%mod;
			u[i+j+len]=1ull*ul*vr%mod,v[i+j+len]=1ull*vl*ur%mod;
		}
	}
}
```