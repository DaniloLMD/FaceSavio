#include <iostream>
#include <queue>
using namespace std;

struct post{
    int id;
    string user;
    string texto;

    bool operator<(post x) const
    {
        return id < x.id;
    }
};

int main(){

    priority_queue<post> pq;

    pq.push({5, "a", "cinco"});
    pq.push({3, "c", "tres"});
    pq.push({2, "d", "dois"});
    pq.push({4, "b", "quatro"});
    pq.push({1, "e", "um"});

    while(pq.size()){
        cout << pq.top().id << " " << pq.top().user << " " << pq.top().texto << "\n";
        pq.pop();
    }


    return 0;
}