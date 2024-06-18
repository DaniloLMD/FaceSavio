#include <bits/stdc++.h>

using namespace std;

int main(){

    system("rm usuarios/cadastrados/* -rf");
    system("rm usuarios/posts/* -rf");

    system("rm obj/* -rf");

    FILE* f = fopen("usuarios/login_data.txt", "w");
    fclose(f);
    f = fopen("usuarios/totalPosts.txt", "w");
    fprintf(f, "0\n");
    fclose(f);

    return 0;
}