c,q=0,lambda i,j,t=0:print("?!"[t],i,j)or t and exit()or input()=='1'
for i in 2,4:[((c:=c+1)==4 or q(i,j))and q(i-q(i-1,j),j-q(i,j-1),1)for j in[2,4]]
