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

        //Vector<string> BigWindow = Window.subList(0, N-1);
        Vector<string> SmallWindow = Window.subList(N-1,1);
        Vector<string> Retreive;

        string temporary = Window[0];

        for (int extract = 1; extract < N-1; extract++){

            temporary = temporary + ", " + Window[extract];
        }

        if (!Collection.containsKey(temporary)){


            Collection.put(temporary, SmallWindow);

        } else {
            Retreive = Collection.get(temporary);
            Retreive.add(Window[N-1]);
            Collection.put(temporary, Retreive);
        }


//        cout << "Window is now: " << Window.toString() << endl;

        Window.remove(0);
        in >> word;
        Window.add(word);

//        cout << "Keys in Collection " << Collection.keys().toString() << endl;
//        cout << "Values in Collection" << Collection.values().toString() << endl;


        if (in.fail()){

            break;
        }

    }
    Vector<string> temp = Collection.keys();
    //cout << "The keys are" << temp.toString() << endl;

    //Loop thru the vector and stuff the words into a map.

    cout << "The value of to be is: " << Collection.get("to, be").toString() << endl;
    cout << "Exiting." << endl;

    return 0;
}


