list=input().split()
x=max(int(list[0]),int(list[1]))
def gcd(a,b):
    if b==0:
        return a
    return gcd(b,a%b)
a=6-x+1
b=6
print("%d/%d"%(a//gcd(a,b),b//gcd(a,b)))