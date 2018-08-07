#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>

using namespace std;

class knapsack{
private:
    vector<int> weight;
    vector<int> value;
    int limit;
    int n;
    void make_weights(int e){
        srand((unsigned int) time(0));
        for(int i = 0; i<e; i++){
            weight.push_back(rand()%15);
        }
    }
    void make_values(int e){
        srand((unsigned int) time(0));
        for(int i = 0; i<e; i++){
            value.push_back(rand()%15);
        }
    }

public:
//    knapsack(){
//        limit = 10;
//        n = 4;
//        weight.push_back(5);
//        weight.push_back(2);
//        weight.push_back(3);
//        weight.push_back(2);
//
//        value.push_back(6);
//        value.push_back(6);
//        value.push_back(3);
//        value.push_back(8);
//    }
    knapsack(int max, int elements){
        limit = max;
        n = elements;
        make_weights(elements);
        make_values(elements);
    }
    ~knapsack(){
        cout << "PojemnoĹÄ plecaka: " << limit << endl;
        cout << "Liczba elementĂłw: " << n << endl;
    }
    void print(){
        cout << "Wagi: ";
        for(int i = 0; i<n; i++){
            cout << weight[i] << ", ";
        }
        cout << endl << "Ceny: ";
        for(int i = 0; i<n; i++){
            cout << value[i] << ", ";
        }
        cout << endl;
    }
    vector<int> dynamic(){
        int solution[n+1][limit+1];
        for(int i = 0; i<=n; i++){
            for(int j = 0; j<=limit; j++){
                if(i == 0 || j == 0){
                    solution[i][j] = 0;
                } else if(j < weight[i]){
                    solution[i][j] = solution[i-1][j];
                } else {
                    solution[i][j] = max(solution[i-1][j], (value[i] + solution[i-1][j-weight[i]]));
                }
            }
        }
        vector<int> out;
        int i = n;
        int j = limit;
        while (i !=0){
            if(solution[i][j] != solution[i-1][j]){
                out.push_back(i);
                j -= weight[i];
                i --;
            } else{
                i--;
            }
        }
        return out;
    }
    vector<int> brute_force(){
        int solution[n];
        int candidate[n];
        for(int i = 0; i<n; i++){
            solution[i] = 0;
            candidate[i] = 0;
        }
        candidate[n] = 1;
        for(int i = 0; i < pow(2.0,n); i++){
            int w = 0;
            int v = 0;
            int best_w = 0;
            for(int j = 0; j<n; j++){
                if(candidate[j] == 1){
                    w += weight[j];
                    v += value[j];
                }
                if(solution[j] == 1){
                    best_w += weight[j];
                }
            }
            if(w <= limit && v > best_w){
               for(int j = 0; j<n; j++){
                   solution[j] = candidate[j];
               }
            }
            int remember = 1;
            for(int j = n-1; j >= 0; j--){
                if(candidate[j] + remember == 2){
                    candidate[j] = 0;
                    remember = 1;
                } else if(candidate[j] + remember == 1){
                    candidate[j] = 1;
                    remember = 0;
                }
            }
        }
        vector<int> out;
        for(int i = 0; i<n; i++){
            if(solution[i] == 1){
                out.push_back(i+1);
            }
        }
        return out;
    }
};

int main() {

    vector<int> solution;
    ofstream results;
    results.open("/home/azrith/CLionProjects/knapsack_problem/time.csv");
    // wzrost elementĂłw
    for(int i = 0; i<20; i++) {
        knapsack* a = new knapsack(25, i+1);
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        a->dynamic();
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        long duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        results << duration << ",";

        t1 = chrono::high_resolution_clock::now();
        a->brute_force();
        t2 = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        results << duration << ",";
        results << endl;
        delete(a);
    }
    results << endl << endl;

    // wzrost pojemnoĹci plecaka
    for(int i = 0; i<20; i++) {
        knapsack* a = new knapsack(5+i, 10);
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        a->dynamic();
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        long duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        results << duration << ",";

        t1 = chrono::high_resolution_clock::now();
        a->brute_force();
        t2 = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        results << duration << ",";
        results << endl;
        delete(a);
    }
    results.close();

    return 0;

// TESTY
//    knapsack* wsk = new knapsack();
//    wsk->print();
//    vector<int> solution_d = wsk->dynamic();
//    vector<int> solution_brute = wsk->brute_force();
//    cout << "Do placaka wkĹadamy przedmioty(dynamicznie): " << endl;
//    for(int i = 0; i < solution_d.size(); i++){
//        cout << solution_d[i] << " ";
//    }
//    cout << endl << "Do placaka wkĹadamy przedmioty(brute force): " << endl;
//    for(int i = 0; i < solution_brute.size(); i++){
//        cout << solution_brute[i] << " ";
//    }
//    cout << endl;
//    delete(wsk);
}