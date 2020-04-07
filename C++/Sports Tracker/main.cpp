#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <stdio.h>
#define INPATH "../vstupnidata/"
#define OUTPATH "../vystupnidata/"

using namespace std;

struct Aktivita{
    /*! @brief jedinecne ID kazdeho zaznamu*/
    int id;
    /*! @brief den aktivity, soucast vysledneho data, interval 1-31*/
    int den;
    /*! @brief mesic aktivity, soucast vysledneho data, interval 1-12*/
    int mesic;
    /*! @brief rok aktivity, soucast vysledneho data, interval 2000-systémové datum*/
    int rok;
    /*! @brief typ aktivity*/
    string typ;
    /*! @brief urazena vzdalenost pri konani aktivity*/
    double vzdalenost;
    /*! @brief kolik minut aktivita trvala*/
    int minuty;
    /*! @brief kolik kalorii byo spaleno pri konani aktivity*/
    double spaleno;
};

/*!
Vycisti cin od prebytecnych znaku po chybnem vstupu
@param[in] kontrola kontrolni promenna volajici funkce
*/
void clearCin(bool &kontrola){
    cin.clear();
    cin.ignore ( 100 , '\n' );
    kontrola = false;
    return;
}
/*!
Smaze predane pole
@param p pole
*/
void deleteArray(Aktivita *p){
    delete[] p;
    p = nullptr;
}

/*!
Pocita pocet radku v zaznamovem souboru
@param srcFileName zaznamovy soubor
@return N pocet radku
*/
int pocetRadku(const string srcFileName){
    ifstream file;
    string line;
    file.open(srcFileName);
    int N = 0;
    while(!file.eof() && getline(file,line)){
        N++;
    }
    file.close();
    if(file.bad()){
        return -1;
    }
    else
        return N;
}

/*!
Hleda maximalni a minimalni zaznamenany rok
@param N pocett radku
@param p pole
@param minRok minimalni rok
@param maxRok maximalni rok
*/
void extRok(int N, Aktivita *p, int &minRok, int &maxRok){
    minRok = p[0].rok;
    maxRok = p[0].rok;
    for(int i = 0; i < N; i++){
        if(p[i].rok < minRok)
            minRok = p[i].rok;
        if(p[i].rok > maxRok)
            maxRok = p[i].rok;
    }
}

/*!
Kontroluje nove zadany zaznam
@param radek nove zadany zaznam
*/
bool kontrolaVstupu(Aktivita radek){

    time_t t = time(NULL);
	tm* timePtr = localtime(&t);

    if(radek.den <= 0 || radek.den > 31 || radek.mesic <=0 || radek.mesic > 12){
        return false;
    }

    if(radek.rok <= 2000 || radek.rok > timePtr->tm_year + 1900){
        return false;
    }

    if(radek.typ != "chuze" && radek.typ != "beh" && radek.typ != "kolo" && radek.typ != "inline"){
        return false;
    }

    if(radek.vzdalenost <= 0 || radek.minuty <= 0 || radek.spaleno <= 0){
        return false;
    }

    return true;

}

/*!
Pta se, jestli chce uzivatel vytvorit novou tabulku
@return true uzivatel chce vytvorit tabulku
*/
bool tableDecide(){
    char volba;
    cout << "Chcete vytvorit novou tabulku? (a/n): ";
    cin >> volba;

    do{
        if(cin.fail() || (tolower(volba) != 'a' && tolower(volba) != 'n'))
            cout << "Nespravny vstup!" << endl;
    }while(cin.fail() || (tolower(volba) != 'a' && tolower(volba) != 'n'));

    return (volba == 'a') ? true : false;
}

/*!
Pocita souhrny pro dany typ aktivity
@param N pocet radku
@param pole vstupni pole
@param mesic
@param rok
@param minuty
@param vzdalenost
@param spaleno
@param typ pro ktery typ aktivity se souhrn pocita
*/
void souhrny(const int N, Aktivita *p, const int mesic, const int rok, int &minuty, double &vzdalenost, double &spaleno, string typ){
    minuty = 0;
    vzdalenost = 0;
    spaleno = 0;
    for(int i = 0; i < N; i++){
        if(p[i].mesic == mesic && p[i].rok == rok && p[i].typ == typ){
            minuty += p[i].minuty;
            vzdalenost += p[i].vzdalenost;
            spaleno += p[i].spaleno;
        }
    }
    return;
}

/*!
Cte vstupni soubor a nacita jej do struktury
@param srcFileName zaznamovy soubor
@param pole pole aktivit
@return true vrati, jestli byla prace se souborm uspesna

*/
bool readFile(const string srcFileName, Aktivita *pole){
    string firstLine;
    ifstream input;
    int N = pocetRadku(srcFileName);
    if(N == -1){
        return false;
    }
    else{
        input.open(srcFileName);

        for(int i = 0; i < N; i++){
            input >> pole[i].id;                //id
            input.get();
            input >> pole[i].den;               //den
            input.get();
            input >> pole[i].mesic;             //mesic
            input.get();
            input >> pole[i].rok;               //rok
            input.get();
            getline(input, pole[i].typ,';');    //typ
            input >> pole[i].vzdalenost;        //vzdalenost
            input.get();
            input >> pole[i].minuty;            //minuty
            input.get();
            input >> pole[i].spaleno;           //spaleno
            input.get();
        }
        input.close();
        if(input.bad()){
            return false;
        }
        else
            return true;
    }
}

/*!
Zapise do zaznamoveho souboru novy zaznam
@return true vrati, jestli byla prace se souborm uspesna
*/
bool zapisNovyZaznam(Aktivita radek, const string dstFileName){
    ofstream file;
    file.open(dstFileName, ofstream::app);

    file << radek.id << ";";
    file << radek.den << ";";
    file << radek.mesic << ";";
    file << radek.rok << ";";
    file << radek.typ << ";";
    file << radek.vzdalenost << ";";
    file << radek.minuty << ";";
    file << radek.spaleno << endl;

    file.close();

    if(file.bad()){
        return false;
    }
    else
        return true;
}

/*!
Komunikuje s uzivatelem pri zadavani noveho zaznamu
@param dstFileName zaznamovy soubor
@return true vrati, jestli byla prace se souborm uspesna
*/
bool novyZaznam(const string dstFileName){
    int N = 0;
    Aktivita radek;
    string volba = "a";
    bool kontrola;
    while(volba == "a"){                        //opakování celého procesu
        //clearCin(kontrola);
        do{                                     //opakování pokud !kontrola
            do{                                 //opakování pokud uživatel zadal špatnou volbu
                N = pocetRadku(dstFileName);
                kontrola = true;
                cout << "Pocet Radku v souboru: " << N << endl;
                cout << "Chcete zadat novy zaznam? (a/n): ";
                getline(cin,volba);
                if(volba != "a" && volba != "n"){
                    cout << "Nespravny vstup!" << endl;
                }
            }while(volba != "a" && volba != "n");

            if(volba == "a"){
                    radek.id = N;
                    cout << "Den: ";
                    cin >> radek.den;
                    if(cin.fail()){
                        clearCin(kontrola);
                    }
                    cout << "Mesic: ";
                    cin >> radek.mesic;
                    if(cin.fail()){
                        clearCin(kontrola);
                    }
                    cout << "Rok: ";
                    cin >> radek.rok;
                    if(cin.fail()){
                        clearCin(kontrola);
                    }
                    cout << "Typ aktivity: ";
                    cin >> radek.typ;
                    if(cin.fail()){
                        clearCin(kontrola);
                    }
                    cout << "Vzdalenost: ";
                    cin >> radek.vzdalenost;
                    if(cin.fail()){
                        clearCin(kontrola);
                    }
                    cout << "Minuty: ";
                    cin >> radek.minuty;
                    if(cin.fail()){
                        clearCin(kontrola);
                    }
                    cout << "Spaleno: ";
                    cin >> radek.spaleno;
                    if(cin.fail()){
                        clearCin(kontrola);
                    }

                    if(!kontrolaVstupu(radek) || !kontrola){
                        cout << "Nespravny vstup!" << endl;
                        cout << "------------------------------------------------" << endl;
                        kontrola = false;
                    }
            }
            else if(volba == "n"){
                return true;
            }
            cin.clear();
            cin.ignore ( 100 , '\n' );
        }while(!kontrola);

        if(!zapisNovyZaznam(radek, dstFileName)){
            cout << "Chyba prace se souborem!" << endl;
            return false;
        }
        else{
            cout << "Uspesne zapsano!" << endl;
            cout << "------------------------------------------------" << endl;
        }

    }
    return true;
}

/*!
Vytvari tabulku do vystupniho souboru
@param p pole aktivit
@param N pocet radku
@param dstFileName vystupni soubor
@return true vrati, jestli byla prace se souborm uspesna
*/
bool createTable(Aktivita *p,const int N,const string dstFileName){
    ofstream file;
    int minRok, maxRok;
    int sumMinuty;
    double sumVzdalenost;
    double sumSpalenot;
    string mesice[] = {"leden","unor","brezen","duben","kveten","cerven","cervenec","srpen","zari","rijen","listopad","prosinec"};
    extRok(N,p,minRok,maxRok);
    file.open(dstFileName);
    file << "<!DOCTYPE html>" << endl;
    file << "<html>" << endl;
        file << "<head>" <<endl;
        file << "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\">" << endl;
        file << "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>" << endl;
        file << "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\"></script>" << endl;
        file << "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\"></script>" << endl;
        file << "</head>" << endl;
        file << "<body>" << endl;
            file << "<div class=\"container\">" << endl;

            if(N == 0){
                file << "<h1>Jeste tady nic neni</h1>" << endl << "<h2>Pro vytvoreni tabulek pridejte alespon jeden zaznam</h2>" << endl;
                file.close();
                if(file.bad()){
                    return false;
                }
                else
                    return true;
                }

            file << "<table class = \"table table-striped table-bordered table-sm\">" << endl;
            file << "<tr>" << endl;
                file << "<th>ID</th>" << endl;
                file << "<th>Datum</th>" << endl;
                file << "<th>Typ aktivity</th>" << endl;
                file << "<th>Vzdalenost</th>" << endl;
                file << "<th>Minuty</th>" << endl;
                file << "<th>Spáleno kalorií</th>" << endl;
            file << "</tr>" << endl;
            for(int i = 0; i < N; i++){
                file << "<tr>" << endl;
                    file << "<td>" << p[i].id << "</td>" << endl;
                    file << "<td>" << p[i].den << "." << p[i].mesic << "." << p[i].rok << "</td>" << endl;
                    file << "<td>" << p[i].typ << "</td>" << endl;
                    file << "<td>" << p[i].vzdalenost << "</td>" << endl;
                    file << "<td>" << p[i].minuty << "</td>" << endl;
                    file << "<td>" << p[i].spaleno << "</td>" << endl;
                file << "</tr>" << endl;
            }
            file << "</table>" << endl;
            file << "<h1>Souhrny</h1>" << endl;

            while(maxRok >= minRok){
                file << "<hr>" << endl;
                file << "<h2>Rok " << maxRok << "</h2>"<< endl;
                file << "<h3>Chuze</h3>" << endl;
                file << "<table class=\" table table-primary table-striped table-bordered table-sm\">" << endl;
                file << "<tr>" << endl;
                    file << "<th></th>";
                    for(int i = 0; i < 12; i++){
                        file << "<th>" << mesice[i] << "</th>";
                    }
                file << "</tr>" << endl;
                file << "<tr>" << endl;
                file << "<td>Vzdalenost</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"chuze");
                        file << "<td><span style=font-weight:normal>" << sumVzdalenost << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Minuty</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"chuze");
                        file << "<td><span style=font-weight:normal>" << sumMinuty << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Spaleno</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"chuze");
                        file << "<td><span style=font-weight:normal>" << sumSpalenot << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;
                file << "</table>" << endl;




                file << "<h3>Beh</h3>" << endl;
                file << "<table class=\" table table-success table-striped table-bordered table-sm\">" << endl;
                    file << "<tr>" << endl;
                    file << "<th></th>";
                    for(int i = 0; i < 12; i++){
                        file << "<th>" << mesice[i] << "</th>";
                    }
                file << "</tr>" << endl;
                file << "<tr>" << endl;
                file << "<td>Vzdalenost</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"beh");
                        file << "<td><span style=font-weight:normal>" << sumVzdalenost << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Minuty</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"beh");
                        file << "<td><span style=font-weight:normal>" << sumMinuty << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Spaleno</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"beh");
                        file << "<td><span style=font-weight:normal>" << sumSpalenot << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;
                file << "</table>" << endl;




                file << "<h3>Kolo</h3>" << endl;
                file << "<table class=\" table table-danger table-striped table-bordered table-sm\">" << endl;
                file << "<thead>" << endl;
                file << "<tr>" << endl;
                    file << "<th></th>";
                    for(int i = 0; i < 12; i++){
                        file << "<th>" << mesice[i] << "</th>" << endl;
                    }
                file << "</tr>" << endl;
                file << "</thead>" << endl;
                file << "<tr>" << endl;
                file << "<td>Vzdalenost</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"kolo");
                        file << "<td><span style=font-weight:normal>" << sumVzdalenost << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Minuty</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"kolo");
                        file << "<td><span style=font-weight:normal>" << sumMinuty << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Spaleno</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"kolo");
                        file << "<td><span style=font-weight:normal>" << sumSpalenot << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;
                file << "</table>" << endl;




                file << "<h3>Inline brusle</h3>" << endl;
                file << "<table class=\" table table-warning table-striped table-bordered table-sm\">" << endl;
                file << "<tr>" << endl;
                    file << "<th></th>";
                    for(int i = 0; i < 12; i++){
                        file << "<th>" << mesice[i] << "</th>";
                    }
                file << "</tr>" << endl;
                file << "<tr>" << endl;
                file << "<td>Vzdalenost</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"inline");
                        file << "<td><span style=font-weight:normal>" << sumVzdalenost << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Minuty</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"inline");
                        file << "<td><span style=font-weight:normal>" << sumMinuty << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;

                file << "<tr>" << endl;
                file << "<td>Spaleno</td>" << endl;
                    for(int i = 0; i < 12; i++){
                        souhrny(N,p,i+1,maxRok,sumMinuty,sumVzdalenost,sumSpalenot,"inline");
                        file << "<td><span style=font-weight:normal>" << sumSpalenot << "</span></td>" << endl;
                    }
                file << "</tr>" << endl;
                file << "</table>" << endl;


            maxRok--;
            }

        file << "</div>" << endl;
        file << "</body>" << endl;
    file << "</html>" << endl;




    file.close();
    if(file.bad()){
        return false;
    }
    else
        return true;
}

/*!
Kontroluje spravne zadani vstupniho souboru
@param in nazev vstupniho souboru
@return true vrati, jestli je vstupni soubor zadan spravne
*/
bool inputCheck(string in){
    int dots = 0;
    int dotPos = 0;
    for(int i = 0; i < (int)in.size(); i++){
        if(!isalnum(in[i]) && in[i] != '.'){
            return false;
        }
        if(in[i] == '.'){
            dots++;
            dotPos = i;
        }
    }

    if(dots != 1 || dotPos+4 != (int)in.size()){
        return false;
    }

    if((in[dotPos+1] == 'c' && in[dotPos+2] == 's' && in[dotPos+3] == 'v') ||
        (in[dotPos+1] == 't' && in[dotPos+2] == 'x' && in[dotPos+3] == 't')
        ){
        return true;
    }
    else
        return false;
}

/*!
Kontroluje spravne zadani vystupniho souboru
@param in nazev vystupniho souboru
@return true vrati, jestli je vystupni soubor zadan spravne
*/
bool outputCheck(string in){
    int dots = 0;
    int dotPos = 0;
    for(int i = 0; i < (int)in.size(); i++){
        if(!isalnum(in[i]) && in[i] != '.'){
            return false;
        }
        if(in[i] == '.'){
            dots++;
            dotPos = i;
        }
    }

    if(dots != 1 || dotPos+5 != (int)in.size()){
        return false;
    }

    if(in[dotPos+1] == 'h' && in[dotPos+2] == 't' && in[dotPos+3] == 'm' && in[dotPos+4] == 'l'){
        return true;
    }
    else
        return false;
}

/*!
Komunikace s uzivatelem pri zadavani vstupniho souboru
@param input nazev vstupniho souboru
@return true vrati, jestli je vstupni soubor zadan spravne
*/
bool inputFile(string &input){
    string in = "";
    input = INPATH;
    cout << "Zadej nazev zaznamoveho souboru (.csv nebo .txt): ";
    getline(cin,in);
    if(in == "" || (int)in.size() <= 4 || !inputCheck(in)){
        return false;
    }
    else{
        input += in;
        return true;
    }


}
/*!
Komunikace s uzivatelem pri zadavani vystupniho souboru
@param output vystupni soubor
@return true vrati, jestli byl vystupni soubor spravne zadan
*/
bool outputFile(string &output){
    string in = "";
    output = OUTPATH;
    cin.clear();
    cin.ignore ( 100 , '\n' );
    cout << "Zadejte nazev vystupniho souboru (.html): ";
    getline(cin,in);
    if(in == "" || (int)in.size() <= 5 || !outputCheck(in)){
        return false;
    }
    else{
        output += in;
        return true;
    }


}

/*!
Hlavni smycka main
*/
int main()
{
    string input;
    string output;
    string outputVypis;
    if(inputFile(input)){
        novyZaznam(input);
        if(tableDecide()){
            Aktivita *aktivity = new Aktivita[pocetRadku(input)];
            if(readFile(input,aktivity)){
                if(outputFile(output)){
                    if(createTable(aktivity, pocetRadku(input), output)){
                        cout << "Vystupni soubor byl uspesne vytvoren." << endl;
                        deleteArray(aktivity);
                    }
                    else{
                        cout << "Chyba prece se souborem!" << endl;
                        deleteArray(aktivity);
                    }
                }
                else{
                    cout << "Nespravny vstup!" << endl;
                    deleteArray(aktivity);
                }
            }
            else{
                cout << "Chyba prace se souborem!" << endl;
                deleteArray(aktivity);
            }
        }
    }
    else{
        cout << "Nespravny vstup!" << endl;
    }
    return 0;
}
