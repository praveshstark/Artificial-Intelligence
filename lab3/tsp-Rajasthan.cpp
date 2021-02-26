#include <bits/stdc++.h>
using namespace std;
#define ll long long
vector<string> cities = { "Bundi", "Bikaner", "Ajmer", "Pushkar", "Udaipur", "Mount Abu","Jaisalmer","Alwar", "Pali", "Jhalawar", "Churu", "Kota", "Sikar", "Chittorgarh", "Hanumangarh", "Jaipur", "Jodhpur", "Bhim", "Bharatpur",  "Jhunjhunu"};
unsigned long long iter = 100000;//no. of iteration
class Graph{ //created a graph where nodes are cities and edge shows distance between them.
    private:
        ll nodes;
        ll** a;
        vector<ll> tour;
        ll cost;
        long double T = 1000;
    
    public:
        Graph(ll n,ll** arr): nodes(n),a(arr)
        {}

        void buildGraph(){  //thia function building a graph 
            for(int i=0;i<nodes;i++){
                for(int j=0;j<nodes;j++){
                    if(a[i][j]==-1){
                        if(i==j)
                            a[i][j]=0;
                        else
                            a[i][j] = rand()%400+1;
                            a[j][i] = a[i][j];
                    }
                }
            }
        }

        void printGraph(){  //this function print graph
            for(ll i=0;i<nodes;i++){
                for(ll j=0;j<nodes;j++){
                    cout<<"| "<<a[i][j]<<" |";
                }
                cout<<"\n";
            }
        }
        

         void start_travel(){ //this function for travelling from random cities 
            cost=0;
            tour.push_back(0);
            ll f[nodes] = {0};
            f[0] = 1;
            for(ll i=1;i<nodes;i++){
                ll temp;
                do{
                    temp = rand()%nodes;
                }
                while(f[temp]!=0);
                f[temp] = 1;
                cost+=a[*(tour.end()-1)][temp];
                tour.push_back(temp);
            }
        }

        void cities_travelled(){  //this function prints the cities travelled
            for(int i=0;i<tour.size();i++){
                cout<<cities[tour[i]]<<"-->";
            }
            cout<<cities[0]<<endl;
        }

        long double returnCost(){
            
            return cost;
        }


        ll calculate_cost(vector<ll> t){ //this function calculate cost which is poportional to the ditance between edges
            ll c=0;
            for(int i=0;i<t.size()-1;i++){
                c+=a[t[i]][t[i+1]];
            }
            return c;
        }

        vector<ll> generateChild(vector<ll> t){
            vector<ll> temp;
                ll one,two;
                do{
                    one = rand()%nodes;
                    two = rand()%nodes;
                }
                while(one==two||one==0||two==0);

                temp = t;

                ll ex;
                ex = temp[one];
                temp[one] = temp[two];
                temp[two] = ex;

                return temp;
        }

        

        void anneling(){
            while(iter>0){
                 vector<ll> temp = generateChild(tour);
                 ll newCost = calculate_cost(temp);
                ll diff = newCost - cost;
                long double r = diff/T;
                long double p = 1/(1+exp(-r));
                if(diff<0){
                    tour = temp;
                    cost = newCost;
                    T*=0.2;
                }
                else{
                    long double prob = 1 / rand();
                    if(prob > p){
                        tour = temp;
                        cost = newCost;
                        T*=0.2;
                    }
                }
                iter--;
            }    
        }
};


int main() {
    srand(time(0));

    ll n = 20;

    ll** a = new ll*[n];
    ll ex[5] = {0};
    for(ll i=0;i<n;i++){
        a[i] = new ll[n];
        for(ll j=0;j<n;j++){
            a[i][j] = -1;
        }
    }
    Graph g(n,a);
    cout<<"Total number of iteration taken = "<<iter<<endl;
    cout<<"\n20 Tourist location in State Rajasthan :"<<endl;
    for(auto i: cities){
        cout<<"| "<<i<<" ";
    }
    cout<<endl;
    g.buildGraph();
    cout<<"Graph is:\n";
    g.printGraph();
    g.start_travel();      
    cout<<"Initial Cost for travelling is:\n"<<g.returnCost()<<endl;
    g.anneling();  
    cout<<"Lowest total cost possible is:\n"<<g.returnCost()<<endl;
    cout<<" Cities travelled with low cost:\n";
    g.cities_travelled();   
    return 0;
}
