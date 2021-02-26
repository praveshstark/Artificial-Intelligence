from math import log1p,inf
T=4
N=2
M=3

A_mat=[[0.7,0.3],[0.4,0.2]]
B_mat=[[0.5,0.3,0.8],[0.8,0.3,0.2]]


pi=[0.6,0.4]
PP=[[0 for i in range(N)]for i in range(T)]
max_iter=10
iters=0

O=[0,1,0,2]
c=[0 for i in range(T)]

global log_prob
log_prob=0

def EM():
    for i in range(0,N):
        PP[0][i]=pi[i]*B_mat[i][0]
    for t in range(1,T):
        c[t]=0
        for i in range(N):
            PP[t][i]=0
            for j in range(N):
                PP[t][i]+=PP[t-1][j]*A_mat[j][i]
            PP[t][i]=PP[t][i]*B_mat[i][O[t]]
            c[t]+=PP[t][i]
        c[t]=1/c[t]
        for i in range(N):
            PP[t][i]=c[t]*PP[t][i]

    beta=[[0 for i in range(N)]for i in range(T)]

    for i in range(N):
        beta[T-1][i]=c[T-1]
    for t in range(T-2,0,-1):
        for i in range(N-1):
            beta[t][i]=0
            for j in range(N):
                beta[t][i]+=A_mat[i][j]*B_mat[j][O[t+1]]*beta[t+1][j]
            beta[t][i]=c[t]*beta[t][i]


#compute yt and yt(i,j)
    y_dash = [[ [0 for i in range(N)] for col in range(N)] for row in range(T)]
    y=[[0 for i in range(N)]for i in range(T)]


    for t in range(T-1):
        for i in range(N):
            y[t][i]=0
            for j in range(N):
                y_dash[t][i][j]=(PP[t][i]*A_mat[i][j]*B_mat[j][O[t+1]]*beta[t+1][j])
                y[t][i]+=y_dash[t][i][j]

    for i in range(N):
        y[T-1][i]=PP[T-1][i]

    for i in range(N):
        pi[i]=y[0][i]

    for i in range(N):
        denom=0
        for t in range(T-1):
            denom+=y[t][i]
        for j in range(N):
            numer=0
            for t in range(T-1):
                numer+=y_dash[t][i][j]
            A_mat[i][j]=numer/denom
    for i in range(N):
        denom=0
        for t in range(T):
            denom+=y[t][i]
        for j in range(M):
            numer=0
            for t in range(T):
                if (O[t]==j):
                    numer+=y[t][i]
            B_mat[i][j]=numer/denom



    log_prob=0
    for i in range(T):
        log_prob+=log1p(c[i])
    log_prob=-log_prob

EM()
#print(log_prob)
iters=iters+1
oldlog_prob= -inf
while (iters<max_iter):
    if log_prob>oldlog_prob:
        oldlog_prob=log_prob
        EM()
    else:
        print("The pi matrix is:\n",pi)
        print("The A MAtrix is:\n",A_mat)
        print("The B matrix is:\n",B_mat)
        break