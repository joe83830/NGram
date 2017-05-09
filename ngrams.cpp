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

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

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

    string Number;
    while (true){
        Number = getLine("N = ? ");
        if (is_number(Number)){
            break;
        } else{

            cout << "Please enter an Integer " << endl;
        }
    }
    int N = stringToInteger(Number);

    //Call BuildCollection
    Map<string, Vector<string> > Col;
    Col = BuildCollection(N, in);

    while (true){

        string Number2;
        while (true){
            Number2 = getLine("# of random words to generate (0 to quit)? ");
            if (is_number(Number2)){
                break;
            } else {

                cout << "Please enter an Integer " << endl;
            }
        }
        int N2 = stringToInteger(Number2);

        if (N2 == 0){
            break;
        }
        //Call GenerateRandom
        cout << ". . ." << GenerateRandom(Col, N2, N) << ". . ." << endl;
    }

    return 0;
}

Map<string, Vector<string> > BuildCollection(int &N, ifstream &in){

    Map<string, Vector<string> > Collection;
    string word;
    Vector<string> Window;

    Vector<string> ManyWords;
    while (true){

        string NewWord;
        in >> NewWord;

        if (NewWord.length() == 0){

            break;
        }
        ManyWords.add(NewWord);
    }

    for (int i = 0; i < N; i++){

        Window.add(ManyWords[i]);

    }

    for (int j = 0; j < ManyWords.size(); j++){

        Vector<string> SmallWindow = Window.subList(N-1,1);

        string temporary = Window[0];

        for (int extract = 1; extract < N-1; extract++){

            temporary = temporary + ", " + Window[extract];
        }

        if (!Collection.containsKey(temporary)){

            Collection.put(temporary, SmallWindow);

        } else {

            Vector<string> Retreive;
            Retreive = Collection.get(temporary);
            Retreive.add(Window[N-1]);
            Collection.put(temporary, Retreive);
        }

        Window.remove(0);

        Window.add(ManyWords[(j + N) % ManyWords.size()]);

    }

    return Collection;
}

string GenerateRandom (Map<string, Vector<string> > &Col, int &N2, int &N){

    Vector<string> Keys = Col.keys();
    int shuffle = randomInteger(0, Keys.size()-1);
    string FirstKey = Keys.get(shuffle);
    //stuff first key into the result first
    Vector<string> DividedFirstKey = stringSplit(FirstKey, ", ");
    string result;
    for (int i = 0; i < DividedFirstKey.size(); i++){

        result = result + " " + DividedFirstKey[i];
    }

    //Find next value
    for (int j = 0; j < N2-N; j++){

        Vector<string> GetValues = Col.get(FirstKey);
        int shuffle2 = randomInteger(0, GetValues.size()-1);

        string next = GetValues.get(shuffle2);

        //Add next to result
        result = result + " " + next;
        //remove the first item in devidedfirstkey

        DividedFirstKey.remove(0);
        DividedFirstKey.add(next);
        //rebuild firstkey from devidedfirstkey

        FirstKey = DividedFirstKey[0];
        for (int k = 1; k < DividedFirstKey.size(); k++){

            FirstKey = FirstKey + ", " + DividedFirstKey[k];
        }

    }

    return result;
}


