#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class Post{
    public:
        
        Post(int id, string user, string texto) : id(id), user(user), texto(texto) {};

        // bool operator<(Post x) const
        // {
        //     return id > x.id;
        // }

        int getID() { return id; }
    private:
        int id;
        string user;
        string texto;
};

bool comp(Post* p1, Post* p2){
    return p1->getID() > p2->getID();
}

int main(){

    vector<Post*> pq;

    Post* p1 = new Post(5251, "a", "1");
    Post* p2 = new Post(2, "b", "2");
    Post* p3 = new Post(1125, "c", "3125015");

    pq.push_back(p1);
    pq.push_back(p2);
    pq.push_back(p3);

    sort(pq.begin(), pq.end(), comp);

    // pq.push({5, "a", "cinco"});
    // pq.push({3, "c", "tres"});
    // pq.push({2, "d", "dois"});
    // pq.push({4, "b", "quatro"});
    // pq.push({1, "e", "um"});

    for(auto x: pq){
        cout << x->getID() << "\n";
    }


    // while(pq.size()){
    //     // cout << pq.top().id << " " << pq.top().user << " " << pq.top().texto << "\n";
    //     cout << pq.top()->getID() << "\n";
    //     pq.pop();
    // }


    return 0;
}