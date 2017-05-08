// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "map.h"

using namespace std;

int main() {
    Map<string, Vector<string> > Collection;
    ifstream in;
    while (true){

        in.open(trim(toLowerCase(getLine("Input file name? "))));

        if (in.is_open()){
            break;
        } else if (in.fail()){

            cout << "Unable to open file, try again " <<endl;
        }

    }

    string word;
    Vector<string> Window;
    string Number = getLine("N = ? ");
    int N = stringToInteger(Number);

    for (int i = 0; i < N; i++){

        in >> word;
        Window.add(word);
    }

    while (true){
        //stuff into Map

        Vector<string> BigWindow = Window.subList(0, N-1);
        Vector<string> SmallWindow = Window.subList(N-1,1);
        Vector<string> Retreive;

        if (!Collection.containsKey(BigWindow.toString())){

            Collection.put(BigWindow.toString(), SmallWindow);
        } else {
            Retreive = Collection.get(BigWindow.toString());
            Retreive.add(SmallWindow.toString());
            Collection.put(BigWindow.toString(), Retreive);
        }

        cout << "Window is now: " << Window.toString() << endl;

        Window.remove(0);
        in >> word;
        Window.add(word);

        cout << "Keys in Collection " << Collection.keys().toString() << endl;


        if (in.fail()){

            break;
        }

    }
    Vector<string> temp = Collection.keys();
    //cout << "The keys are" << temp.toString() << endl;

    //Loop thru the vector and stuff the words into a map.


    cout << "Exiting." << endl;

    return 0;
}

