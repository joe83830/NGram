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
#include "random.h"

using namespace std;

Map<string, Vector<string> > BuildCollection(int &N, ifstream &in);
string GenerateRandom(Map<string, Vector<string> > &Col, int &N2, int &N);

int main() {

    ifstream in;
    while (true){

        in.open(trim(toLowerCase(getLine("Input file name? "))));

        if (in.is_open()){
            break;
        } else if (in.fail()){

            cout << "Unable to open file, try again " <<endl;
        }

    }

    string Number = getLine("N = ? ");
    int N = stringToInteger(Number);

    //Call BuildCollection
    Map<string, Vector<string> > Col;
    Col = BuildCollection(N, in);

    string Number2 = getLine("# of random words to generate (0 to quit)? ");
    int N2 = stringToInteger(Number2);

    //Call GenerateRandom
    cout << ". . ." << GenerateRandom(Col, N2, N) << ". . ." << endl;

    return 0;
}

Map<string, Vector<string> > BuildCollection(int &N, ifstream &in){

    Map<string, Vector<string> > Collection;
    string word;
    Vector<string> Window;

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


        cout << "Window is now: " << Window.toString() << endl;

        Window.remove(0);
        in >> word;
        Window.add(word);

        cout << "Keys in Collection " << Collection.keys().toString() << endl;
        cout << "Values in Collection" << Collection.values().toString() << endl;


        //How to wrap around?
        if (in.fail()){

            break;
        }

    }

    return Collection;
}

string GenerateRandom (Map<string, Vector<string> > &Col, int &N2, int &N){


    Vector<string> KeyVec = Col.keys();  //got a vector of the keys of Col
    int shuffle = randomInteger(0, KeyVec.size()-1);  //Generate a random index number
    string start = KeyVec.get(shuffle);    //picked a random key out of the vector of keys
    string final;

    for (int j = 0; j < N2-N; j++){  //j needs to be changed

        Vector<string> Begin = Col.get(start);  //extracted the value(which is a vector) associated with the key
        int shuffle2 = randomInteger(0, Begin.size()-1); //generate a random index number
        string next = Begin.get(shuffle2); //take a random string from the vector(which is the value of the map)

        Vector<string> purify = stringSplit(start, ", ");  //starts with these words

        for (int i = 0; i < purify.size()-1; i++){
            final = final + " " + purify[i];
        }
        final = final + " " + next;
        Begin.remove(0);
        Begin.add(next);
    }
    ///////////////////////////////////

    return final;
}


