#include <stdio.h>
#include <bits/stdc++.h>
//#include <iostream>
#include <limits> //used for clearing wrong inputs
#include <sstream> //used for conversion to string
using namespace std;

//make code compatible for all algos introduced

int tracks[100], travelled[100]; //tracks input, travelled output
int firstTrack, lastTrack; //input

int travelCount = -1, nooftracks = 0, seekcount = 0; //counter for tracking

int from; //tracking flag;

void rawprintarray()
{
    for (int i = 0; i < 5; i++) {
        cout << tracks[i] << "\t";
    }

    cout << "\n";
}

int getMax()
{
    int maxi = -999;
    for (int i = 0; i < nooftracks; i++) {
        if (maxi < tracks[i]) {
            maxi = tracks[i];
        }
    }

    return maxi;
}

int getMin()
{
    int mini = 9999999;
    for (int i = 0; i < nooftracks; i++) {
        if (mini > tracks[i]) {
            mini = tracks[i];
        }
    }

    return mini;
}

int nonnegintInput(string message) //include limits
{
    cout << message << ": ";
    int input;
    cin >> input;
    while (true) {
        if (cin.fail()) {
            printf("OOPS! Wrong input! Try again: ");
            cout << message << ": ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> input;
        }

        if (!cin.fail()) {
            if (input < 0) {
                printf("Input needs to be positive integer! Enter again: ");
                cout << message << ": ";
                cin >> input;
            }
            else {
                break;
            }
        }
    }

    return input;
}

bool checkInArray(int n)
{
    for (int i = 0; i < nooftracks; i++) {
        if (tracks[i] == n) {
            return true;
        }
    }

    return false;
}

int uniqueInput(string message)
{
    bool inarr;
    int a;
    do {
        a = nonnegintInput(message);
        inarr = checkInArray(a);
        if (inarr) {
            cout << "\nShould be unique!\n";
        }
    }

    while (inarr == true);
    return a;
}

int inputFromArray(string message)
{
    bool inarr;
    int a;
    do {
        a = nonnegintInput(message);
        inarr = checkInArray(a);
        if (!inarr) {
            cout << "\nShould be in array!\n";
        }
    }

    while (inarr == false);
    return a;
}

int maxInput(string message)
{
    bool ismax = false;
    int a;
    do {
        a = nonnegintInput(message);
        if (a >= getMax()) {
            ismax = true;
        }
        else {
            cout << "\nCannot be smaller than the smallest from the sequence.\n";
        }
    }

    while (ismax != true);
    return a;
}

int minInput(string message)
{
    bool ismin = false;
    int a;
    do {
        a = nonnegintInput(message);
        if (a <= getMin()) {
            ismin = true;
        }
        else {
            cout << "\nCannot be bigger than the smallest from the sequence.\n";
        }
    }

    while (ismin != true);
    return a;
}

void initTracks()
{
    for (int i = 0; i < nooftracks; i++) {
        tracks[i] = -999;
    }
}

void init()
{
    travelled[++travelCount] = from;
}

void fin()
{
    travelled[++travelCount] = from;
}

void printTrack()
{
    cout << "\n";
    for (int i = 0; i < nooftracks; i++) {
        cout << tracks[i] << "\t";
    }

    cout << "\n";
}

void printTravelled()
{
    cout << "\n";
    for (int i = 0; i < travelCount; i++) {
        cout << travelled[i] << "\t";
    }

    cout << "\n";
}

void deleteTrack(int item)
{
    for (int i = 0; i < nooftracks; i++) {
        if (tracks[i] == item) {
            for (int j = i; j < (nooftracks - 1); j++) {
                //cout<<"shifted "<<tracks[j+1]<<endl;
                tracks[j] = tracks[j + 1];
                tracks[j + 1] = -999;
            }

            break;
        }
    }

    nooftracks--;
}

int distbetween(int to)
{
    int dist = from - to;
    if (dist < 0) {
        return -dist;
    }

    return dist;
}

int travel(int to)
{
    cout << from << " -> " << to << "\n";
    seekcount += distbetween(to);
    deleteTrack(from);
    travelled[++travelCount] = to;
    return to;
}

int getShortest()
{
    //'from' excluded
    int tempTo;
    int mindist = 9999;
    int toreturn;
    for (int i = 0; i < nooftracks; i++) {
        if (tracks[i] != from) {
            tempTo = tracks[i];
            if (distbetween(tempTo) < mindist) {
                mindist = distbetween(tempTo);
                toreturn = tempTo;
            }
        }
    }

    return toreturn;
}

void SSTF()
{
    //mindist(from)
    while (nooftracks > 1) {
        int to = getShortest();
        from = travel(to);
    }
}

int getIndexFromTracks(int n)
{
    int i;
    for (i = 0; i < nooftracks; i++) {
        if (tracks[i] == n) {
            return i;
        }
    }

    return 0;
}

void SCAN()
{
    tracks[++nooftracks] = 0;
    sort(tracks, tracks + nooftracks);
    int a = getIndexFromTracks(from);
    int sizear1 = a + 1;
    int sizear2 = nooftracks - (a + 1);
    int ar1[sizear1], ar2[sizear2];

    for (int i = 0; i < sizear1; i++) {
        ar1[i] = tracks[i];
    }

    sort(ar1, ar1 + sizear1, greater<int>());

    int j = 0;
    for (int i = sizear1; i < nooftracks; i++) {
        ar2[j] = tracks[i];
        j++;
    }

    for (int i = 1; i < sizear1; i++) {
        from = travel(ar1[i]);
    }

    for (int i = 0; i < sizear2; i++) {
        from = travel(ar2[i]);
    }
}

void CLOOK()
{
    sort(tracks, tracks + nooftracks);
    int a = getIndexFromTracks(from);
    int sizear1 = a + 1;
    int sizear2 = nooftracks - (a + 1);
    int ar1[sizear1], ar2[sizear2];

    for (int i = 0; i < sizear1; i++) {
        ar1[i] = tracks[i];
    }

    sort(ar1, ar1 + sizear1, greater<int>());

    int j = 0;
    for (int i = sizear1; i < nooftracks; i++) {
        ar2[j] = tracks[i];
        j++;
    }

    sort(ar2, ar2 + sizear2, greater<int>());

    for (int i = 1; i < sizear1; i++) {
        from = travel(ar1[i]);
    }

    deleteTrack(from);
    from = ar2[0];
    for (int i = 1; i < sizear2; i++) {
        from = travel(ar2[i]);
    }
}

void CSCAN()
{
    tracks[nooftracks] = firstTrack;
    nooftracks++;
    tracks[nooftracks] = lastTrack;
    nooftracks++;
    CLOOK();
}

int main()
{
    nooftracks = nonnegintInput("Enter number of tracks");
    initTracks();
    for (int i = 0; i < nooftracks; i++) {
        stringstream ss;
        string temp;
        ss << i + 1;
        ss >> temp;
        string tempmessage = "Enter track ";
        tempmessage.append(temp);
        tracks[i] = uniqueInput(tempmessage);
    }

    firstTrack = minInput("\nEnter the first track on the entire disc");
    lastTrack = maxInput("\nEnter the last track on the entire disc");
    from = inputFromArray("\nEnter the track to start from");

    int choice = nonnegintInput("1. SSTF\n2. SCAN\n3. CSCAN\n4. CLOOK\nSelect choice");
    cout << "\n\n";
    init();
    switch (choice) {
    case (1):
        SSTF();
        break;
    case (2):
        SCAN();
        break;
    case (3):
        CSCAN();
        break;
    case (4):
        CLOOK();
        break;
    default:
        cout << "Incorrect choice";
    }

    fin();
    printTravelled();
    cout << "Seeked " << seekcount << " tracks.";
}
