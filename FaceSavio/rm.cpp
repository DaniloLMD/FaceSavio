#include <iostream>
using namespace std;

int main(){

    system("rm usuarios/Danilo/posts/* -rf");
    system("rm usuarios/Caio/posts/* -rf");
    system("rm usuarios/Tiago/posts/* -rf");

    string arq1 = "usuarios/totalPosts.txt";
    string arq2 = "usuarios/Danilo/quantidadePosts.txt";
    string arq3 = "usuarios/Caio/quantidadePosts.txt";
    string arq4 = "usuarios/Tiago/quantidadePosts.txt";

    FILE* ptr = fopen(arq1.c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    ptr = fopen(arq2.c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    ptr = fopen(arq3.c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    ptr = fopen(arq4.c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    return 0;
}