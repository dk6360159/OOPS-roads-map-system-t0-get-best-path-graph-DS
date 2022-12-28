#include <bits/stdc++.h>
#define bikespeed 600
#define carspeed 850
#define busspeed 1000
#define footspeed 100
using namespace std;
map<int, vector<vector<int>>> mp;
map<int, string> names;

void DFS(int startpincode, int destpincode, int ctime, int &mintime, vector<int> &res, vector<int> temp, map<int, bool> tmap, int i)
{
    if (tmap[startpincode])
    {
        return;
    }

    if (ctime > mintime)
    {
        return;
    }
    temp.push_back(startpincode);
    if (startpincode == destpincode)
    {
        if (ctime < mintime)
        {
            mintime = ctime;
            res = temp;
        }
        return;
    }
    tmap[startpincode] = true;
    for (auto v : mp[startpincode])
    {
        if (tmap[v[0]])
        {
            continue;
        }

        // vtemp.push_back(v[0]);
        DFS(v[0], destpincode, ctime + v[i], mintime, res, temp, tmap, i);
    }
}

class City
{
    string Name;
    int Pincode;

public:
    City(int pincode, string name)
    {
        Pincode = pincode;
        Name = name;
        names[pincode] = name;
    }
    int getPincode()
    {
        return Pincode;
    }
};
class Admin
{
public:
    void Link2Cities(City c1, City c2, int distm)
    {
        int c1pincode = c1.getPincode();
        int c2pincode = c2.getPincode();
        vector<int> v;
        v.push_back(c2pincode);
        v.push_back(distm);
        v.push_back(distm / bikespeed);
        v.push_back(distm / carspeed);
        v.push_back(distm / busspeed);
        v.push_back(distm / footspeed);
        mp[c1pincode].push_back(v);
        vector<int> v1;
        v1.push_back(c1pincode);
        v1.push_back(distm);
        v1.push_back(distm / bikespeed);
        v1.push_back(distm / carspeed);
        v1.push_back(distm / busspeed);
        v1.push_back(distm / footspeed);

        mp[c2pincode].push_back(v1);
    }
    void BestPath(City c1, City c2, string vehicle)
    {
        int c1pincode = c1.getPincode();
        int c2pincode = c2.getPincode();
        map<int, bool> visited;
        vector<int> res;
        vector<int> temp;
        int mintime = INT_MAX;
        int i;
        if (vehicle == "none")
        {
            i = 1;
        }
        else if (vehicle == "bike")
        {
            i = 2;
        }
        else if (vehicle == "car")
        {
            i = 3;
        }
        else if (vehicle == "bus")
        {
            i = 4;
        }
        else
        {
            i = 5;
        }

        DFS(c1pincode, c2pincode, 0, mintime, res, temp, visited, i);
        if (mintime == INT_MAX)
        {
            cout << "NO path exist" << endl;
        }
        else
        {
            if (vehicle == "none")
            {
                cout << "Minimum path distance is :: " << mintime << endl;
                cout << "optimal path is::" << endl;
                for (int i = 0; i < res.size(); i++)
                {
                    cout << names[res[i]] ;
                    if(i!=res.size()-1){

                    cout <<"-->" ;
                    }

                }
            }
            else
            {
                cout << "Minimum time by  :: " << vehicle << " " << mintime << endl;
                cout << "optimal path is::" << endl;
                for (int i = 0; i < res.size(); i++)
                {
                    cout << names[res[i]];
                     if(i!=res.size()-1){

                    cout <<"-->" ;
                    }
                }
            }
        }
    }
};

int main()
{
     City c1 = City(101, "alwar");
    City c2 = City(102, "hisar");
    City c3 = City(103, "kanpur");
    City c4 = City(104, "hanumangarh");
    City c5 = City(105, "delhi");
    City c6 = City(106, "mumbai");
    City c7 = City(107, "Ganganagar");
    City c8 = City(108, "Bhopal");
    City c9 = City(109, "Lakhnau");
    Admin Dinesh;
    Dinesh.Link2Cities(c1, c2, 1000);
    Dinesh.Link2Cities(c1, c4, 3000);
    Dinesh.Link2Cities(c2, c3, 4000);
    Dinesh.Link2Cities(c5, c4, 1000);
   Dinesh.Link2Cities(c1, c6, 1000);
   Dinesh.Link2Cities(c6, c7, 2000);
    Dinesh.Link2Cities(c7, c8, 3000);
    Dinesh.Link2Cities(c8, c9, 4000);
    Dinesh.Link2Cities(c6, c9, 15000);
    Dinesh.BestPath(c1, c9,"bike");
    return 0;
}
