int facsum(int n){
	int i,sum=0;
	for(i=1;i<n;i++){
		if(n%i==0){
		sum+=i;              //求500以内每个数的因子并求和 
		}
	}
	return sum;
}
