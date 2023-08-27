//Filip Stenegren
//DTATG_HT20
//Introduktion till programmering
//Exam.cpp
//08-03-2021

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <cctype>
#include <stdio.h>
#include <string.h>
#include <functional>
#include <limits>

using namespace std;

//for the add function
string name;
string postadress;
string epost;
string tfnnr;
string bday;
string other;
// for search 
vector<string> searchvector;
vector<string> kontaktlistvector;
// for delete 
vector <string> infovector;


vector<string>listvector;
int i;

int val;
int ADD();
int SEARCH();
int REMOVE();
int valfunk ();
bool program();

int main()  
{
    program ();
    return 0;
}

int valfunk()
{
    cout <<"Vad vill du göra, skriv det nummer som associeras med det du vill göra!"<< endl;
    cout <<"'1' för att LÄGGA till en kontakt."<< endl << "'2' för att SÖKA en existerande kontakt."<< endl
    <<"'3' för att TA BORT en existerande kontakt."<< endl <<"'4' för att avsluta programmet."<<endl<<endl;
    cout << "Ange nummer här: ";
    if (!(cin >> val) || val > 4)  // kollar att användaren matade in ett acceptabelt värde i variabeln.
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // den här gör att när man trycker på enter för att ange variabeln så kommer den inte 
        // att ignorera en rad. dvs utan den kan vissa kommandon komma att skippas eller inte visas.
    }
    cout << endl;
    return val;
}

bool program()
{
    bool done = false;
    while (!done)
    {
        val = valfunk();
        switch (val)
        {
            case 1:
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ADD();
                
               
                break;
            }
            case 2:
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                SEARCH();
                break;
            }
            case 3:
            {   
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                REMOVE();
                break;
            }
            case 4:
            {   
                cout << "den här skiten ska avsluta programmet" << endl;
                cout << "Hörs då"<<endl;
                //funktion som avslutar hela programmet 
                
                done = true;
                break;
                return 0;
            }
            default:    
            {
                // default sker när ingen annan case händer alltså
                //alltså om det inte blir en siffra mellan 1-4!!!!!
                cout << "Var vänlig skriv endast in ett tal mellan 1-4"<<endl<<endl;
                break;
            }
        }
    }
    return 0;
}

int ADD()
{
    ofstream utmatn ("kontaktlista.txt", ios::app);
    string name;
    string postadress;
    string epost;
    string tfnnr;
    string bday;
    string other;
    string counter;

    cout <<"DU LÄGGER TILL EN KONTAKT:" <<endl <<endl <<endl;
    cout <<"Namn: ";
    getline(cin, name);
    cout <<endl;
    infovector.push_back(name);

    cout <<"Adress: ";
    getline(cin, postadress);
    infovector.push_back(postadress);
    cout <<endl;

    cout <<"E-post: ";
    getline(cin, epost);
    infovector.push_back(epost);
    cout <<endl;

    cout <<"Telefonnummer: ";
    getline(cin, tfnnr);
    infovector.push_back(tfnnr);
    cout <<endl;

    cout <<"Födelsedatum (yyyy-mm-dd): ";
    getline(cin, bday);
    infovector.push_back(bday);
    cout <<endl;

    cout <<"Övriga kommentarer: ";
    getline(cin, other);
    infovector.push_back(other);
    cout <<endl <<endl;
    
    auto iter = infovector.begin();
    utmatn <<"Namn: "  <<*iter <<" ¶";
    iter++;
    utmatn <<"Adress: "  <<*iter  <<" ¶";
    iter++;
    utmatn <<"E-post: "  <<*iter  <<" ¶";
    iter++;
    utmatn <<"Nummer: "  <<*iter   <<" ¶";
    iter++;
    utmatn <<"Födelsedatum: "  <<*iter <<" ¶";
    iter++;
    utmatn <<"Övriga kommentarer: "  <<*iter  <<" ¶¶"<<endl<< endl;
    iter++;
    infovector.clear();
    utmatn.close();
    return 0;
}

int SEARCH()
{
    ofstream utmatn ("kontaktlista.txt", ios::app);
    ifstream inmatn ("kontaktlista.txt");
    int searchcounter = 1;
    string keyword;
    string search;
    string tempstring;
    string token;
    string fakestring = "Namn: namn: Namn namn"
    "Adress: adress: Adress adress" 
    "E-post: e-post: Epost: epost: E-post e-post Epost epost "
    "Nummer: nummer: Nummer nummer "
    "Födelsedatum: födelsedatum Födelsedatum födelsedatum "
    "Övriga kommentarer: övriga kommentarer: Övriga kommentarer övriga kommentarer ¶";

    //den här stora stringen är för att man inte ska kunna söka på varenda kontakt genom att söka på tex namn 
    //eftersom alla kontakter har just ordet namn i sig.

    cout <<"DU SÖKER EN KONTAKT:" <<endl <<endl <<endl;
    cout <<"Ange kontaktens namn: ";
    getline(cin, keyword);      //lägg in sökordet i en variabeln keyword.
    cout <<keyword <<endl;
    cout <<endl;        //allt relaterat namnet på personen man söker i bland listan

      
    while (!inmatn.eof())
    {
        getline(inmatn, search); //stoppar in inmatn in i search och sen in i vectorn
        searchvector.push_back(search);

    }

    
    if (fakestring.find(keyword) != string::npos)// det här är för att undvika så att folk kan söka på namn namn: Namn osv    
    {                                            // för att få alla kontakter
        cout << "Skriv endast ett namn som du vill söka! "<<endl;
    }
    else 
    { 
        for (auto searchiter = searchvector.begin(); searchiter != searchvector.end(); *searchiter++)
        {
            if ( searchiter->find(keyword) != string::npos)
            {
                
                kontaktlistvector.push_back(*searchiter);
                //stoppar in hittade resultat ifrån textfilen till en vector
            }
        }
    }

    if (kontaktlistvector.empty())
    {
        cout << "Kunda inte hitta en kontakt med det givna sökordet!" <<endl;
    }
    else
    {
        for (auto kontaktiter = kontaktlistvector.begin(); kontaktiter != kontaktlistvector.end(); *kontaktiter++)
        {
            tempstring = *kontaktiter; 
            string delimiter = "¶";// hitta ordet i kontaktlistan som gör att den delar upp den i ett mer läsligt format.
            size_t pos = 0;
            token = tempstring.substr(0, tempstring.find(delimiter)); 
            //token börjar på Namn: och blir större och större tills den hittar delimiter

            cout <<"--- "<<searchcounter<<" ---"<<endl;
            while ((pos = tempstring.find(delimiter)) != string::npos)
            {
                token = tempstring.substr(0, pos);
                cout << token << endl;
                tempstring.erase(0, pos + delimiter.length());
            }    
            searchcounter++; //anger numret på kontakten
        }
    }
    searchvector.clear();
    kontaktlistvector.clear(); 
    //clearar sökvectorn eftersom om programmet fortfarande 
    //exekveras kommer gamla sökningar ligga kvar!!

    inmatn.close();
    utmatn.close();
    return 0;
}  

int REMOVE()
{
    ifstream inmatn ("kontaktlista.txt");
    string search;
    int TaBortnr;

    cout <<"DU TAR BORT EN KONTAKT:" <<endl<<endl<<endl;


    while (!inmatn.eof())
    {
        getline(inmatn, search); //stoppar in inmatn in i search och sen in i vectorn
        if (search.empty())
        {   
        }
        else 
        {
            listvector.push_back(search);
        }
        //denna ifsats gör så att den inte stoppar in tomma rader som en kontakt så ifall
        //man har en kontakt på rad 7 och nästa på 9 kommer den inte stoppa in den tomma raden 8
    }
    ofstream utmatn ("kontaktlista.txt");
    //den här utan ios::app gör så att textfilen rensas 
    
    int kontaktnummer = 1;
    for (auto terminaliter = listvector.begin(); terminaliter != listvector.end(); terminaliter++)
    {
        cout <<"--- "<<kontaktnummer<<" ---"<<endl;
        cout << *terminaliter<<endl<<endl;
        kontaktnummer++;
    }
    
    //borde ha som i searchfunktionen där ja tar bort ¶ i terminalen för användarvänlighet.

    cout <<endl; 
    
    cout <<"vilket kontakt vill du ta bort? skriv nummret associerat med elementet!"<<endl;
    cout <<"=================="<<endl;
    cin >> TaBortnr;
    cout <<"=================="<<endl<<endl;

    int countnr = 1;

    if (cin.fail())
    {
        cout <<"var vänlig skriv endast in ett kontaktnummer!"<<endl;
    }
    else if ( TaBortnr > listvector.size())
    {
        cout <<"skriv endast in ett ett tal som inte går över antalet kontakter"<<endl;
    }
    else
    {   
        for (auto removeiter = listvector.begin(); removeiter != listvector.end(); removeiter++)
        {
            if (countnr == TaBortnr)
            {
                listvector.erase(removeiter);
            }
            if (removeiter == listvector.end())
            {
                break;
            }
            utmatn << *removeiter<<endl;
            countnr++;
        } 
    }
    inmatn.close();
    utmatn.close();
    cout <<"du valde att ta bort kontakt "<<TaBortnr<<endl<<endl;

    listvector.clear();

    
    return 0;
}  