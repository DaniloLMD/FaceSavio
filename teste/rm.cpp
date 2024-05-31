#include <iostream>
using namespace std;

int main(){

    system("rm usuarios/Name/posts/* -rf");
    
    string arq1 = "usuarios/totalPosts.txt";
    string arq2 = "usuarios/Name/quantidadePosts.txt";
    
    FILE* ptr = fopen(arq1.c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    ptr = fopen(arq2.c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    
    return 0;
}