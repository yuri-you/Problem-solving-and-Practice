import matplotlib.pyplot as plt
X=[-5.0,-4.0,-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0,4.0,5.0]
Y=[0.0385,0.0588,0.1,0.2,0.5,1.0,0.5,0.2,0.1,0.0588,0.0385]
Z_lagrange=[]
Z_Newton=[]
size=len(X)
for i in range(size):
    z=1.0
    for j in range(size):
        if j!=i:
            z*=X[i]-X[j]
    Z_lagrange.append(Y[i]/z)
Y_tmp=Y
for i in range(size-1):
    Z_Newton.append(Y_tmp[0])
    for j in range(size-i-1):
        Y_tmp[j]=(Y_tmp[j+1]-Y_tmp[j])/(i+1)
Z_Newton.append(Y_tmp[0])
def Origin_function(a):
    return (1/(1+a*a))
def Lagrange_function(a):
    all=1.0
    ans=0.0
    for i in range(size):
        all=1.0
        for j in range(size):
            if i!=j:
                all*=(a-X[j])
        ans+=all*(Z_lagrange[i])
    #for i in range(size):
    #    if (a-X[i])!=0:
    #        ans+=all/(a-X[i])*(Z_lagrange[i])
    return ans
def Newton_function(a):
    all=1.0
    ans=0.0
    for i in range(size):
        ans+=all*Z_Newton[i]
        all*=(a-X[i])
    return ans
x=[]
for i in range(0,2000,1):
        x.append(-10+0.01*i)
Origin=[]
Lagrange=[]
Newton=[]
for i in x:
    Origin.append(Origin_function(i))
    Lagrange.append(Lagrange_function(i))
    Newton.append(Newton_function(i))
l1, =plt.plot(x, Origin,linewidth = 1.5,c='red')
l2, =plt.plot(x, Lagrange,linewidth = 5,c='yellow')
l3, =plt.plot(x, Newton,linewidth = 1.5,c='black')
plt.title("Interpolating Polynomials Emulation", fontdict={'family' : 'Times New Roman', 'size'   : 26})
plt.xlabel("X", fontproperties = 'Times New Roman',fontsize=22)
plt.ylabel("Y", fontproperties = 'Times New Roman',fontsize=22)
plt.tick_params(axis='both', labelsize=15)
plt.legend(handles = [l1,l2,l3], labels = ['Origin','Lagrange','Newton'],loc = 'upper left', prop={'family' : 'Times New Roman', 'size'   : 12})
plt.grid()
plt.show()
#a=-1.0
#print(Origin_function(a))
#print('\n');
#print(Newton_function(a))
#print('\n');
#print(Lagrange_function(a))