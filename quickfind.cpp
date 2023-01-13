#include <iostream>

using namespace std;
// we will make weighted and path compression algorithm

class percolation
{
private:
    int *id;
    int *size;
    int n;
    // i have made them pointers so that we can dynamically allocate
    // since i am particulary making this for precolation problem
    // so instead of making array of size n^2 i will make it of size  n^2 +2
public:
    percolation(int N, int vac[]) // vacancy array will be of size n^2+2
    {
        n = N;
        id = new int[(N * N) + 2];
        size = new int[(N * N) + 2];
        for (int i = 0; i < (N * N) + 2; i++)
        {
            id[i] = i;
            size[i] = 1;
        }
        for (int i = 0; i < n * n; i++)
        {
            int x = vac[i];
            if (vac[i]==1 && vac[i+1]==1 && (i == 0 || (i+1) % (n) != 0))
                connect(i, i + 1);
            if (vac[i]==1 && vac[i+n]==1 && i >= 0 && i < ((n * n)-n - 1))
                connect(i, i + n);
        }
        for(int i = 0 ;  i < n; i++)
        {
            connect(i,n*n);
            connect(i+(n*n)-n,n*n+1);

        }
    }
    // bool isvacant(int i)
    // {
    //     return vac[i] == i;
    // }
    int root(int i)
    {

        while (i != id[i])
        {
            id[i] = id[id[i]];
            i = id[i];
        }

        return i;
    }

    bool find(int i, int j)
    {
        // if(!isvacant(i) || !isvacant(j)) return 0;
        int ri = root(i);
        int rj = root(j);

        return ri == rj;
    }

    void connect(int i, int j)
    {
        int iroot = root(i);
        int jroot = root(j);
       
            if (size[iroot] > size[jroot])
            {
                id[jroot] = iroot;
                size[iroot] += size[jroot];
            }
            else
            {
                id[iroot] = jroot;
                size[jroot] += size[iroot];
            }
        
    }
    

    bool percolate()
    {
        return find(n * n, (n * n) + 1);
    }
    
};
int main()
{
    int vac[27] = {1,1,0,1,0
    ,0,0,0,1,0
    ,0,1,0,1,1
    ,1,0,1,1,0
    ,1,1,0,1,1
    ,1,1};
    for(int i = 0 ;  i < 25; i++)
    {
        if(vac[i]==0) cout<<"#";
        else cout<<".";
        if((i+1)%5==0 && i!=0) cout<<endl;
    }
    
    percolation trial(5, vac);
    // trial.connectAll();
    if (trial.percolate())
        cout << "yes it does" << endl;
    else
        cout << "not it doesnt" << endl;

      
}