#include "Cluster.hh"
#include "Area_Espera.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <map>
#include <string>
#endif

using namespace std;

int main() {
    map<int, Proceso> procesos;
    vector<map<int, Proceso>::iterator> a(10, procesos.end());
    cout << true << ' ' << false << endl;
    for (int i = 0; i < a.size(); ++i) {
        if(a[i] != procesos.end()) cout << 1;
        else cout << 0;
    }
}
