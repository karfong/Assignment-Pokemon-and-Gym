#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <cctype>
#include <windows.h>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
/***************************************************** Structs *****************************************************/
struct Pokemon
{
    string name;
    string type;
    int cp;
    string dateCaptured;
    float height;
    float weight;

    Pokemon(string name, string type, int cp, string dateCaptured, float height, float weight)
    {
        this->name = name;
        this->type = type;
        this->cp = cp;
        this->dateCaptured = dateCaptured;
        this->height = height;
        this->weight = weight;
    }
    void display(int i)
    {
        cout << setw(0) << i << ".  " << name << setw(16) << type << setw(14) << cp << setw(13) << dateCaptured << setw(12) << height << setw(12) << weight << endl;
    }
};
struct Pokemon_Stops
{
    string date;
    string time;
    string items;

    Pokemon_Stops(string date, string time, string items)
    {
        this->date = date;
        this->time = time;
        this->items = items;
    }

    void display(int i)
    {
        cout << setw(0) << i << ".  "
             << date << setw(15)
             << time << setw(21)
             << items << endl;
    }
};
struct Raid
{
    string date;
    string time;
    string venue;

    Raid(string date, string time, string venue)
    {
        this->date = date;
        this->time = time;
        this->venue = venue;
    }

    void display(int i)
    {
        cout << setw(0) << i << ".  "
             << date << setw(15)
             << time << setw(20)
             << venue << endl;
    }
};
struct Hunter
{
    string firstName;
    string lastName;
    int level;
    string gender;
    string teamType;
    //vector is and unlimited array
    //Inside Hunter, there are 3 vector which store the pokemon data, pokestop data and raid data for the hunter
    vector<Pokemon> pokemon;
    vector<Pokemon_Stops> pStop;
    vector<Raid> pRaid;

    Hunter(string firstName, string lastName, int level, string gender, string teamType, vector<Pokemon> pokemon, vector<Pokemon_Stops> pStop, vector<Raid> pRaid)
    {
        this->firstName = firstName;
        this->lastName = lastName;
        this->level = level;
        this->gender = gender;
        this->teamType = teamType;
        this->pokemon = pokemon;
        this->pStop = pStop;
        this->pRaid = pRaid;
    }
    void sortPokemon() //Sort the pokemon
    {
        sort(pokemon.begin(), pokemon.end(), [](const Pokemon &i, const Pokemon &j) {
            return i.cp > j.cp;
        });
    }
    void displayDetails(int i) //Display the Output/Details of a Hunter
    {

        string line = "-------------------------------------------------------------------------------------------";
        string asterisk = "**************************************************************************************";

        cout << asterisk << endl; // ************
        cout << setw(40) << i << " "
             << "Hunter"
             << " " << i << endl; // 1   Hunter   1
        cout << asterisk << endl; // ************

        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Level: " << level << endl;
        cout << "Gender: " << gender << endl;
        cout << "Team Type: " << teamType << endl;

        cout << "************************************** Pokemon ***************************************" << endl;
        cout << setw(8) << "Name" << setw(22)
             << "Type" << setw(12)
             << "CP" << setw(18)
             << "Date Captured" << setw(12)
             << "Height" << setw(12)
             << "Weight" << endl;

        int k = 0;
        for (auto &p : pokemon)
        {
            k++;
            p.display(k);
        }
        cout << endl;

        cout << "************************************ Pokemon Stop ************************************" << endl;
        cout << setw(8) << "Date" << setw(20)
             << "Time" << setw(22)
             << "Item" << endl;

        k = 0;
        for (auto &ps : pStop)
        {
            k++;
            ps.display(k);
        }
        cout << endl;

        cout << "**************************************** Raid *****************************************" << endl;
        cout << setw(8) << "Date" << setw(20)
             << "Time" << setw(21)
             << "Venue" << endl;

        k = 0;
        for (auto &pr : pRaid)
        {
            k++;
            pr.display(k);
        }
        cout << endl;

        cout << asterisk << endl; // ************
        cout << endl
             << endl
             << endl;
    }

    void display(int i)
    {
        cout << setw(10) << i << setw(10) << firstName << setw(10) << lastName << setw(10) << level << setw(10) << gender << setw(10) << teamType << endl;
    }
};

/**************************************************** TRIM ***************************************************/
//This function is to cut the whitespace from the user input to prevent the system crash
const string WHITESPACE = " \n\r\t\f\v";
string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}
string rtrim(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
string trim(const string &s)
{
    return rtrim(ltrim(s));
}

/**************************************************** HUNTER ***************************************************/
void readHunter(vector<Hunter> &hunter)
{
    string data;
    bool state = true;

    string firstName;
    string lastName;
    int level;
    string gender;
    string teamType;

    vector<Pokemon> pokemon;
    string pName;
    string pType;
    int pCP;
    string pDateCaptured;
    float pHeight;
    float pWeight;

    vector<Pokemon_Stops> pStop;
    string sDate;
    string sTime;
    string sItems;

    vector<Raid> pRaid;
    string rDate;
    string rTime;
    string rVenue;

    ifstream readFile;
    try
    {
        readFile.open("Hunters.txt", ios::in);

        while (!readFile.eof())
        {
            getline(readFile, data); //
            getline(readFile, data); //
            getline(readFile, data); // *******
            getline(readFile, data); // 1 Hunter 1
            getline(readFile, data); // *******

            readFile >> data;        // First
            readFile >> data;        // Name
            readFile >> data;        // :
            getline(readFile, data); // Yeoh Xuan
            firstName = trim(data);

            readFile >> data;        // Last
            readFile >> data;        // Name
            readFile >> data;        // :
            getline(readFile, data); // Kok Eugene
            lastName = trim(data);

            readFile >> data; // Level
            readFile >> data; // :
            readFile >> data; // 15
            level = stoi(data);

            readFile >> data;   // Gender
            readFile >> data;   // :
            readFile >> gender; // Male

            readFile >> data;     // Team
            readFile >> data;     // Type
            readFile >> data;     // :
            readFile >> teamType; // Fire

            getline(readFile, data); //
            getline(readFile, data); //
            getline(readFile, data); // ****** Pokemon ******
            getline(readFile, data); // Name Type CP Date Captured Height Weight
            while (readFile >> data)
            {
                if (data.find("****") != string::npos)
                {
                    break;
                }
                else
                {
                    string cp, ht, wt;
                    readFile >> pName;
                    readFile >> pType;
                    readFile >> cp;

                    readFile >> pDateCaptured;
                    readFile >> ht;
                    readFile >> wt;
                    try
                    {
                        pCP = stoi(cp);     //stoi (string to integer) because CP is declare as string
                        pHeight = stof(ht); //stof (string to float)
                        pWeight = stof(wt);
                    }
                    catch (...)
                    {
                    }
                    Pokemon poke = Pokemon(pName, pType, pCP, pDateCaptured, pHeight, pWeight);
                    pokemon.push_back(poke);
                }
            }

            getline(readFile, data); // Stops ********
            getline(readFile, data); // Date Time Item
            while (readFile >> data)
            {
                if (data.find("****") != string::npos)
                {
                    break;
                }
                else
                {
                    readFile >> sDate;
                    readFile >> sTime;
                    readFile >> sItems;

                    Pokemon_Stops stop = Pokemon_Stops(sDate, sTime, sItems);
                    pStop.push_back(stop);
                }
            }

            getline(readFile, data); // Raids ******
            getline(readFile, data); // Date Time Venue
            while (readFile >> data)
            {
                if (data.find("****") != string::npos)
                {
                    break;
                }
                else
                {
                    readFile >> rDate;
                    readFile >> rTime;
                    getline(readFile, data);
                    rVenue = trim(data);

                    Raid raid = Raid(rDate, rTime, rVenue);
                    pRaid.push_back(raid);
                }
            }

            Hunter hunt = Hunter(firstName, lastName, level, gender, teamType, pokemon, pStop, pRaid);
            hunt.sortPokemon();
            hunter.push_back(hunt);
            pokemon.clear();
            pStop.clear();
            pRaid.clear();
        }
    }
    catch (...)
    {
        cout << "! Error !" << endl;
        cout << "Unable to read the file either due to the " << endl;
        cout << "File does not exist or the structure of the file is not the same as the program computed" << endl;
        cout << "New file will be created upon saving \n\nProceeding to Main Menu..." << endl;
    }

    readFile.close();
}
void writeHunter(vector<Hunter> hunter)
{
    FILE *pFile;
    pFile = fopen("Hunters.txt", "w");

    string asterisk = "**********************************************************************************************";

    int i = 0;
    for (auto &h : hunter)
    {
        //fprintf is to write data into the file

        fprintf(pFile, "\n\n");
        i++;
        fprintf(pFile, "%s \n", asterisk.c_str()); // ***********
        //fprintf is write data into pFile, set the position and write
        //"%39d %9s %3s %-40d\n" (This is the position)
        //i, "Hunter", " ", i (This is the data)
        //The Number of position is according to the number of data, if have 3 position, that's mean it have 3 data
        fprintf(pFile, "%39d %9s %3s %-40d\n", i, "Hunter", " ", i); // 1  Hunter  1
        fprintf(pFile, "%s \n", asterisk.c_str());                   // ***********
        fprintf(pFile, "%5s %-12s: %-25s\n", " ", "First Name", h.firstName.c_str());
        fprintf(pFile, "%5s %-12s: %-25s\n", " ", "Last Name", h.lastName.c_str());
        fprintf(pFile, "%5s %-12s: %-25d\n", " ", "Level", h.level);
        fprintf(pFile, "%5s %-12s: %-25s\n", " ", "Gender", h.gender.c_str());
        fprintf(pFile, "%5s %-12s: %-25s\n\n", " ", "Team Type", h.teamType.c_str());

        fprintf(pFile, "%-39s %10s %3s %-40s\n", "**************************************", "Pokemon", " ", "***************************************");
        fprintf(pFile, "%5s %-15s %-15s %-10s %-20s %-15s %-15s\n", " ", "Name", "Type", "CP", "Date Captured", "Height", "Weight");

        vector<Pokemon> pokemon = h.pokemon;
        int k = 0;
        for (auto &p : pokemon)
        {
            k++;
            fprintf(pFile, "%-5d %-15s %-15s %-10d %-20s %-15.1f %-15.1f\n", k, p.name.c_str(), p.type.c_str(), p.cp, p.dateCaptured.c_str(), p.height, p.weight);
        }
        fprintf(pFile, "\n");

        fprintf(pFile, "%-39s %9s %4s %-40s\n", "**************************************", "Stops", " ", "***************************************");
        fprintf(pFile, "%5s %-15s %-15s %-10s \n", " ", "Date", "Time", "Item");

        vector<Pokemon_Stops> pStop = h.pStop;
        k = 0;
        for (auto &ps : pStop)
        {
            k++;
            fprintf(pFile, "%-5d %-15s %-15s %-15s\n", k, ps.date.c_str(), ps.time.c_str(), ps.items.c_str());
        }
        fprintf(pFile, "\n"); //

        fprintf(pFile, "%-39s %9s %4s %-40s\n", "**************************************", "Raids", " ", "***************************************");
        fprintf(pFile, "%5s %-15s %-15s %-10s \n", " ", "Date", "Time", "Venue");

        vector<Raid> pRaid = h.pRaid;
        k = 0;
        for (auto &pr : pRaid)
        {
            k++;
            fprintf(pFile, "%-5d %-15s %-15s %-15s\n", k, pr.date.c_str(), pr.time.c_str(), pr.venue.c_str());
        }
        fprintf(pFile, "\n"); //

        fprintf(pFile, "%s", asterisk.c_str()); // ************
    }
    fclose(pFile);
}
void displayHuntersDetails(vector<Hunter> hunter)
{
    if (hunter.empty())
    {
        cout << "There is no hunter registered yet" << endl;

        return;
    }
    int i = 0;
    for (auto &h : hunter)
    {
        i++;
        h.displayDetails(i);
    }
    system("pause");
}
void displayHunters(vector<Hunter> hunter)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    string line = "----------------------------------------------------------------------------------------------";

    cout << line << endl;
    cout << "                                         Hunters                                          " << endl;
    cout << line << endl;

    int i = 0;
    for (auto &h : hunter)
    {
        i++;

        h.display(i);
    }

    cout << endl;
}
void searchHunter(vector<Hunter> &hunter, string searchBy, string input)
{
    vector<Hunter> result;

    if (searchBy == "firstName")
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string firstName = h.firstName;
            transform(firstName.begin(), firstName.end(), firstName.begin(), ::tolower);
            if (firstName == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "lastName")
    {
        //Convert the user input to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string lastName = h.lastName;
            //Convert The Last Name To Lowercase
            transform(lastName.begin(), lastName.end(), lastName.begin(), ::tolower);
            if (lastName == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "teamType")
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string teamType = h.teamType;
            transform(teamType.begin(), teamType.end(), teamType.begin(), ::tolower);
            if (teamType == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "gender")
    {
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (auto &h : hunter)
        {
            string gender = h.gender;
            transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
            if (gender == input)
            {
                result.push_back(h);
            }
        }
    }
    else if (searchBy == "level")
    {

        int lvl;
        bool state = true;
        do
        {

            try //run and test the code to see got error or not
            {
                lvl = stoi(input);
                state = false;
            }
            catch (...) //if there is error in try then it will run this function
            {
                cout << "Please enter a valid integer : ";
                cin >> input;
                cout << "\n";
                continue;
            }
        } while (state);

        for (auto &h : hunter)
        {
            if (h.level == lvl)
            {
                result.push_back(h);
            }
        }
    }

    if (result.empty())
    {
        cout << "No result is found.\n"
             << endl;
    }
    else
    {
        displayHunters(result);
        bool state = true;
        do
        {
            string input;
            cout << "Please select a hunter to view his/her details (number):";
            cin >> input;
            cout << "\n";
            try
            {
                int i = stoi(input);
                i--;
                Hunter hunter = result.at(i);
                hunter.displayDetails(++i);
                system("pause");
                cout << endl;
                state = false;
            }
            catch (...)
            {
                cout << "Error !" << endl;
                cout << " There is no such selection" << endl;
                continue;
            }
        } while (state);
    }
}

/**************************************************** Selection ***************************************************/
int selectHunter(vector<Hunter> hunter)
{
    displayHunters(hunter);

    int i = 0;
    bool state = true;
    do
    {
        string input;
        cout << "Please select a Hunter by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Hunter selectedHunter = hunter.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            cout << "! Error !" << endl;
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);

    return i;
}
int selectPokemon(vector<Pokemon> pokemon)
{

    string line = "----------------------------------------------------------------------------------------------";
    cout << line << endl;
    cout << "\t\t\t                                           POKEMONS                                           " << endl;
    cout << line << endl;
    cout << "\t\t\t%5s %-15s %-15s %-10s %-20s %-15s %-15s\n", " ", "Name", "Type", "CP", "Date Captured", "Height", "Weight";
    cout << line << endl;
    ;

    int i = 0;
    for (auto &p : pokemon)
    {
        i++;
        p.display(i);
    }
    cout << "\n";

    bool state = true;
    do
    {
        string input;
        cout << "Please select a Pokemon by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Pokemon selectedPokemon = pokemon.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            cout << "! ERROR ! " << endl;
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);
    return i;
}
int selectStop(vector<Pokemon_Stops> pStop)
{

    string line = "----------------------------------------------------------------------------------------------";
    cout << line << endl;
    cout << "\t\t\t                                          Stops                                           " << endl;
    cout << line << endl;
    cout << "\t\t\t%-5s %-15s %-15s %-15s\n", " ", "Date", "Time", "Item";
    cout << line << endl;

    int i = 0;
    for (auto &ps : pStop)
    {
        i++;
        ps.display(i);
    }
    cout << "\n";

    bool state = true;
    do
    {
        string input;
        cout << "Please select a Stop by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Pokemon_Stops selectedStop = pStop.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            cout << "! ERROR !" << endl;
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);
    return i;
}
int selectRaid(vector<Raid> pRaid)
{
    string line = "----------------------------------------------------------------------------------------------";
    cout << line << endl;
    cout << "                                          Raids                                           " << endl;
    cout << line << endl;
    cout << "\t\t\t%-5s %-15s %-15s %-15s\n", " ", "Date", "Time", "Venue";
    cout << line << endl;

    int i = 0;
    for (auto &pr : pRaid)
    {
        i++;
        pr.display(i);
    }
    cout << "\n";

    bool state = true;
    do
    {
        string input;
        cout << "Please select a Raid by number : ";
        cin >> input;
        try
        {
            i = stoi(input);
            i--;
            Raid selectedRaid = pRaid.at(i);
            cout << endl;
            state = false;
        }
        catch (...)
        {
            cout << "! ERROR !" << endl;
            cout << " There is no such selection" << endl;
            continue;
        }
    } while (state);
    return i;
}

/**************************************************** Add New Entry ***************************************************/
void addHunter(vector<Hunter> &hunter)
{

    string s;
    string firstName;
    string lastName;
    int level;
    string gender;
    string teamType;
    vector<Pokemon> pokemon;
    vector<Pokemon_Stops> pStop;
    vector<Raid> pRaid;

    cout << "--------Filling up the Hunter details--------\n";
    cin.clear();

    cout << "First Name: ";
    cin >> firstName;
    cout << "Last Name: ";
    cin >> lastName;

    cout << "Level: ";
    cin >> level;

    cout << "Gender: ";
    cin >> gender;

    cout << "Team Type: ";
    cin >> teamType;

    do
    {
        string input;
        cout << "\n[1] --Adding a Pokemon details for this hunter? (Y/N) : ";

        cin >> input;
        cin.clear();

        if (input == "Y" || input == "y")
        {

            string name;
            string type;
            int cp;
            string dateCaptured;
            float height;
            float weight;

            cout << "Pokemon Name: ";
            cin >> name;

            cout << "Pokemon Type: ";
            cin >> type;

            cout << "Pokemon CP: ";
            cin >> cp;

            cout << "Date Captured (dd-mm-yyyy): ";
            cin >> dateCaptured;

            cout << "Height: ";
            cin >> height;

            cout << "Weight: ";
            cin >> weight;

            Pokemon poke = Pokemon(name, type, cp, dateCaptured, height, weight);
            pokemon.push_back(poke); // Add new pokemon at the end
        }
        else
        {
            break;
        }

    } while (true);

    do
    {
        string input;

        cout << "\n[2] --Adding a Stop details for this hunter? (Y/N) : ";
        cin >> input;

        if (input == "Y" || input == "y")
        {
            string date;
            string time;
            string items;

            cout << "Stop Date (dd-mm-yyy): ";
            cin >> date;

            cout << "Stop Time (hh:mm): ";
            cin >> time;

            cout << "Stop Item: ";
            cin >> items;

            Pokemon_Stops poke = Pokemon_Stops(date, time, items);
            pStop.push_back(poke);
        }
        else
        {
            break;
        }

    } while (true);

    cin.clear();
    do
    {
        string input;
        cout << "\n[3] --Adding a Raid details for this hunter? (Y/N) : ";
        cin >> input;

        if (input == "Y" || input == "y")
        {
            string date;
            string time;
            string venue;

            cout << "Raid Date (dd-mm-yyy): ";
            cin >> date;

            cout << "Raid Time (hh:mm): ";
            cin >> time;
            cin.clear();

            cout << "Raid Venue: ";
            cin >> venue;
            getline(cin, venue);

            Raid poke = Raid(date, time, venue);
            pRaid.push_back(poke);
        }
        else
        {
            break;
        }

    } while (true);

    Hunter hunt = Hunter(firstName, lastName, level, gender, teamType, pokemon, pStop, pRaid);
    hunt.sortPokemon();
    hunter.push_back(hunt);
    writeHunter(hunter);

    cout << "\n* Hunter %s %s has successfully registered into the Journal *\n"
         << firstName.c_str() << lastName.c_str();
}
void addPokemonToHunter(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        cout << "There is no hunter registered yet " << endl;
        return;
    }
    int i = selectHunter(hunter);
    Hunter added = hunter.at(i);

    string name;
    string type;
    int cp;
    string dateCaptured;
    float height;
    float weight;

    cout << "------ Adding new Pokemon to Hunter %s ------\n"
         << added.lastName.c_str();

    cout << "Pokemon Name: ";
    cin >> name;
    cout << "Pokemon Type: ";
    cin >> type;
    cout << "CP: ";
    cin >> cp;
    cout << "Date Captured (dd-mm-yyy): ";
    cin >> dateCaptured;
    cout << "Height: ";
    cin >> height;
    cout << "Weight: ";
    cin >> weight;

    Pokemon poke = Pokemon(name, type, cp, dateCaptured, height, weight);
    hunter.at(i).pokemon.push_back(poke);
    hunter.at(i).sortPokemon();

    added = hunter.at(i);
    added.displayDetails(++i);
    writeHunter(hunter);

    cout << "\n* Added new Pokemon %s to Hunter %s *\n"
         << poke.name.c_str() << added.lastName.c_str();
}
void addStopToHunter(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        cout << "\n* There is no hunter registered yet *\n";
        return;
    }
    int i = selectHunter(hunter);
    Hunter added = hunter.at(i);

    string date;
    string time;
    string items;

    cout << "------ Adding new Stop to Hunter %s ------\n"
         << added.lastName.c_str();

    cout << "Date (dd-mm-yyy): ";
    cin >> date;
    cout << "Time (hh:mm): ";
    cin >> time;
    cout << "Item: ";
    cin >> items;

    Pokemon_Stops stop = Pokemon_Stops(date, time, items);
    hunter.at(i).pStop.push_back(stop);

    added = hunter.at(i);
    added.displayDetails(++i);
    writeHunter(hunter);

    cout << "\n* Added new Stop to Hunter %s *\n"
         << added.lastName.c_str();
}
void addRaidToHunter(vector<Hunter> &hunter)
{
    if (hunter.empty())
    {
        cout << "\n* There is no hunter registered yet *\n";
        return;
    }
    int i = selectHunter(hunter);
    Hunter added = hunter.at(i);

    string date;
    string time;
    string venue;

    cout << "------ Adding new Raid to Hunter %s ------\n"
         << added.lastName.c_str();

    cout << "Date (dd-mm-yyy): ";
    cin >> date;
    cout << "Time (hh:mm): ";
    cin >> time;
    cout << "Venue: ";
    cin >> venue;

    Raid raid = Raid(date, time, venue);
    hunter.at(i).pRaid.push_back(raid);

    added = hunter.at(i);
    added.displayDetails(++i);
    writeHunter(hunter);

    cout << "\n* Added new Raid at %s to Hunter %s *\n"
         << raid.venue.c_str() << added.lastName.c_str();
}

/**************************************************** Delete Entry ***************************************************/
void deleteHunter(vector<Hunter> &hunter)
{
    if (hunter.empty()) //if the hunter is empty
    {
        cout << "\n* There is no hunter registered yet *\n";
    }
    else
    {

        int i = selectHunter(hunter);
        Hunter deletedHunter = hunter.at(i);
        hunter.erase(hunter.begin() + i);
        writeHunter(hunter);

        cout << "\n* Hunter %s %s has successfully deleted from the journal *\n"
             << deletedHunter.firstName.c_str() << deletedHunter.lastName.c_str();
    }
}
void deletePokemon(vector<Hunter> &hunter)
{
    if (hunter.empty()) //if the hunter is empty
    {
        cout << "There is no hunter registered yet" << endl;
        return;
    }
    //delete hunter
    int i = selectHunter(hunter);
    vector<Pokemon> pokemon = hunter.at(i).pokemon;
    Hunter hunt = hunter.at(i);

    if (pokemon.empty()) //if the pokemon is empty
    {
        cout << "\n* Hunter %s does not own any Pokemon yet *\n"
             << hunt.lastName.c_str();
    }
    else //delete pokemon from hunter
    {
        int k = selectPokemon(pokemon);
        Pokemon deletedPokemon = hunter.at(i).pokemon.at(k);
        pokemon.erase(pokemon.begin() + k);
        hunter.at(i).pokemon = pokemon;

        writeHunter(hunter);

        cout << "\n* Pokemon %s has successfully deleted from the Hunter %s *\n"
             << deletedPokemon.name.c_str() << hunt.lastName.c_str();
    }
}
void deleteStop(vector<Hunter> &hunter)
{
    if (hunter.empty()) //if the hunter is empty
    {
        cout << "\n* There is no hunter registered yet *\n";
        return;
    }

    int i = selectHunter(hunter);
    vector<Pokemon_Stops> stop = hunter.at(i).pStop;
    Hunter hunt = hunter.at(i);

    if (stop.empty()) //if the PokeStop is empty
    {
        cout << "\n* Hunter %s has not been to any Stop yet *\n"
             << hunt.lastName.c_str();
    }
    else //delete PokeStop from hunter
    {

        int k = selectStop(stop);
        Pokemon_Stops deletedStop = hunter.at(i).pStop.at(k);
        stop.erase(stop.begin() + k);
        hunter.at(i).pStop = stop;
        writeHunter(hunter);

        cout << "\n* Stop on %s at %s has successfully deleted from the Hunter %s *\n"
             << deletedStop.date.c_str() << deletedStop.time.c_str() << hunt.lastName.c_str();
    }
}
void deleteRaid(vector<Hunter> &hunter)
{
    if (hunter.empty()) //if hunter is empty
    {
        cout << "There is no hunter registered yet";
        return;
    }

    int i = selectHunter(hunter);
    vector<Raid> raid = hunter.at(i).pRaid;
    Hunter hunt = hunter.at(i);

    if (raid.empty()) //if raid is empty
    {
        cout << "Hunter has not been to any Raid yet" << hunt.lastName;
    }
    else //delete raid from hunter
    {

        int k = selectRaid(raid);
        Raid deletedRaid = hunter.at(i).pRaid.at(k);
        raid.erase(raid.begin() + k);
        hunter.at(i).pRaid = raid;
        writeHunter(hunter);

        cout << "Raid has successfully deleted from the Hunter " << deletedRaid.date << deletedRaid.venue << hunt.lastName;
    }
}

/**************************************************** Loops ***************************************************/
void searchHunterLoop(vector<Hunter> hunter)
{
    // system("CLS");
    int input4 = 0;
    string search;
    do
    {
        cout << "\n------Search Hunter By------" << endl;
        cout << "1) First Name" << endl;
        cout << "2) Last Name" << endl;
        cout << "3) Level" << endl;
        cout << "4) Gender" << endl;
        cout << "5) Team Type" << endl;
        cout << "6) Back to Main Menu\n\n";

        cout << "Option : ";
        cin >> input4;
        cout << "\n";

        switch (input4)
        {
        case 1:
            getline(cin, search);
            cout << "Search Hunters by first name : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "firstName", search);
            break;
        case 2:
            getline(cin, search);
            cout << "Search Hunters by last name : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "lastName", search);
            break;
        case 3:
            getline(cin, search);
            cout << "Search Hunters by level : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "level", search);
            break;
        case 4:
            getline(cin, search);
            cout << "Search Hunters by gender : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "gender", search);
            break;
        case 5:
            getline(cin, search);
            cout << "Search Hunters by team type : ";
            getline(cin, search);
            cout << endl;
            search = trim(search);
            searchHunter(hunter, "teamType", search);
            break;
        case 6:
            break;
        default:
            cout << "*Please enter the available option*\n";
            break;
        }
    } while (input4 != 6);
}
void addNewEntryLoop(vector<Hunter> &hunter)
{

    int input2 = 0;
    do
    {
        cout << "\n----------Add new entry----------" << endl;
        cout << "1) Register a new Hunter" << endl;
        cout << "2) Add new Pokemon to an existing Hunter" << endl;
        cout << "3) Add new Stop to an existing Hunter" << endl;
        cout << "4) Add new Raid to an existing Hunter" << endl;
        cout << "5) Back to Main Menu \n\n";

        cout << "Option : ";
        cin >> input2;
        cout << "\n";
        switch (input2)
        {
        case 1:
            // Register a new hunter
            addHunter(hunter);
            break;
        case 2:
            // Add new pokemon
            addPokemonToHunter(hunter);
            break;
        case 3:
            // Add new stop
            addStopToHunter(hunter);
            break;
        case 4:
            // Add new raid
            addRaidToHunter(hunter);
            break;
        case 5:
            // Return back to Main Menu
            break;
        default:
            cout << "*Please enter the available option*\n";
            break;
        }

    } while (input2 != 5);
}
void deleteEntryLoop(vector<Hunter> &hunter)
{
    int input3 = 0;
    do
    {
        cout << "\n----------Delete Entry----------" << endl;
        cout << "1) Delete an existing Hunter" << endl;
        cout << "2) Delete a Pokemon from a Hunter" << endl;
        cout << "3) Delete a Stop from a Hunter" << endl;
        cout << "4) Delete a Raid from a Hunter" << endl;
        cout << "5) Back to Main Menu\n\n";

        cout << "Option : ";
        cin >> input3;
        cout << "\n";

        switch (input3)
        {
        case 1:
            deleteHunter(hunter);
            break;
        case 2:
            deletePokemon(hunter);
            break;
        case 3:
            deleteStop(hunter);
            break;
        case 4:
            deleteRaid(hunter);
            break;
        case 5:
            break;
        default:
            cout << "*Please enter the available option*\n";
            break;
        }

    } while (input3 != 5);
}

/**************************************************** MAIN***************************************************/
int main()
{
    vector<Hunter> hunter;
    readHunter(hunter);
    bool state = true;
    int input = 0;

    do
    {
        // system("CLS");
        //Create a list and let user to choose
        system("CLS");
        cout << "\n\n WELCOME to Pokemon Journal \n\n";
        cout << "---------Main Menu---------" << endl;
        cout << "1) Show all Hunters details" << endl;
        cout << "2) Add new entry" << endl;
        cout << "3) Delete an entry" << endl;
        cout << "4) Search Hunters" << endl;
        cout << "5) Exit The Program\n\n";
        cout << "Option: ";
        cin >> input;
        switch (input)
        {
        case 1:
            displayHuntersDetails(hunter);
            break;
        case 2:
            addNewEntryLoop(hunter);
            break;
        case 3:
            deleteEntryLoop(hunter);
            break;
        case 4:
            searchHunterLoop(hunter);
            break;
        case 5:
            writeHunter(hunter);
            cout << "Saving data and exiting the program...";
            break;

        default:
            cout << "Please enter the available option.";
            break;
        }
    } while (input != 5);
    return 0;
}
