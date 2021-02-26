#include <bits/stdc++.h>
using namespace std;

//define fast_io ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)

unsigned long long iter = 1000000;

class Graph{
    private:
        long int nodes;
        long double** a;
        vector<long int> tour;
        long double cost;
        long double T = 1000;
    
    public:
        Graph(long int n,long double** arr): nodes(n),a(arr)
        {}

        void formGraph(){
            for(long int i=0;i<nodes;i++){
                for(long int j=0;j<nodes;j++){
                    if(a[i][j]==-1){
                        a[i][j]=0;
                    }
                }
            }
        }

        void allocateCost(vector< pair<long int, long int> > coord){
            long int x=0;
            for(auto i: coord) {
                long int y=0;
                for(auto j: coord) {
                    long double d = sqrt(pow(i.first - j.first, 2) + pow(i.second - j.second, 2));
                    a[x][y] = d;
                    y++;
                }
                x++;
            }
        }

        void getGraph(){
            for(long int i=0;i<nodes;i++){
                for(long int j=0;j<nodes;j++){
                    cout<<"| "<<a[i][j]<<" |";
                }
                cout<<"\n";
            }
        }

        long double getTemp(){
            return T;
        }

        //random starting tour:
        void tour_gen(){
            cost=0;
            tour.push_back(0);
            long double f[nodes] = {0};
            f[0] = 1;
            for(long int i=1;i<nodes;i++){
                long int temp;
                do{
                    temp = rand()%nodes;
                }
                while(f[temp]!=0);
                f[temp] = 1;
                cost+=a[*(tour.end()-1)][temp];
                tour.push_back(temp);
            }
        }

        void getTour(){
            for(long int i=0;i<tour.size();i++){
                cout<<tour[i]<<" --> ";
            }
            cout<<0<<endl;
        }

        long double returnCost(){
            return cost;
        }

        long double getCost(vector<long int> t){
            long double c=0;
            for(long int i=0;i<t.size()-1;i++){
                c+=a[t[i]][t[i+1]];
            }
            return c;
        }

        vector<long int> generateChild(vector<long int> t){
            vector<long int> temp;
                long int one,two;
                //calculate two random nodes:
                do{
                    one = rand()%nodes;
                    two = rand()%nodes;
                }
                while(one==two||one==0||two==0);

                temp = t;

                long int ex;
                ex = temp[one];
                temp[one] = temp[two];
                temp[two] = ex;

                return temp;
        }

        void anneling(){
            while(iter > 0){
                //generate child:
                vector<long int> temp = generateChild(tour);
                //calculate cost:

                //annealate:
               
                //calculate probability:
                long double newCost = getCost(temp);
                long double diff = abs(newCost - cost);
                long double r = diff/T;
                long double p = exp(-r);

                if(newCost < cost){
                    //select
                    tour = temp;
                    cost = newCost;
                    //getTour();
                }
                else{
                    long double prob = 1 / rand();
                    if(p > prob){
                        //select
                        tour = temp;
                        cost = newCost;
                    }
                }
                T *= 0.75;
                iter--;
                cout<<cost<<" ";
            }    
        }
};


int main() {
    srand(time(0));
    //fast_io;
    long int n;
    cin>>n;

    long int optCost;
    cin>>optCost;

    long double** a = new long double*[n];
    long double ex[5] = {0};
    for(long int i=0;i<n;i++){
        a[i] = new long double[n];
        for(long int j=0;j<n;j++){
            a[i][j] = -1;
        }
        
    }

    vector< pair<long int, long int> > coord;
    for(long int i=0; i<n; i++) {
        long int num, x, y;
        cin >> num >> x >> y;
        coord.push_back(make_pair(x, y));
    }

    Graph g(n,a);
    
    cout<<"Initial Temperature = "<<g.getTemp()<<endl;
    cout<<"Number of Iterations = "<<iter<<endl;
    cout<<"Optimum Cost = "<<optCost<<endl;
    g.formGraph();
    g.allocateCost(coord);
    // cout<<"Genrated graph is:\n";
    // g.getGraph();
    // cout<<"\n";
    g.tour_gen();
    cout<<"Initaial tour is:\n";
    g.getTour();
    cout<<"initial cost is:\n"<<g.returnCost()<<endl;
    g.anneling();
    g.tour_gen();
    cout<<"Final tour is:\n";
    g.getTour();
    cout<<"Final cost is:\n"<<g.returnCost()<<endl;

    return 0;
}
