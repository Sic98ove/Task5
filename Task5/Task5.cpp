#include "pch.h"
using namespace std;

vector<costAreaPair> getCosts(const map<string, costAreaPair>& dictionary)
{
    vector<costAreaPair> values;

    for (const auto& pair : dictionary)
    {
        values.push_back(pair.second);
    }

    return values;
}

string keyByValue(const map<string, costAreaPair>& dictionary, const costAreaPair& costArea)
{
    for (const auto& pair : dictionary)
    {
        if (pair.second.area == costArea.area && pair.second.cost == costArea.cost)
            return pair.first;
    }

    return "NULL";
}

int main()
{
    const size_t max_area = 2000;

    map<string, costAreaPair> dictionary
    {
        {"couch_s",                 costAreaPair(300,75)},
        {"couch_b",                 costAreaPair(500,80)},
        {"bed",                     costAreaPair(400,100)},
        {"closet",                  costAreaPair(200,50)},
        {"bed_s",                   costAreaPair(200,40)},
        {"desk",                    costAreaPair(200,70)},
        {"table",                   costAreaPair(300,80)},
        {"tv_table",                costAreaPair(200,30)},
        {"armchair",                costAreaPair(100,30)},
        {"bookshelf",               costAreaPair(200,60)},
        {"cabinet",                 costAreaPair(150,20)},
        {"game_table",              costAreaPair(150,30)},
        {"hammock",                 costAreaPair(250,45)},
        {"diner_table_with_chairs", costAreaPair(250,70)},
        {"stools",                  costAreaPair(150,30)},
        {"mirror",                  costAreaPair(100,20)},
        {"instrument",              costAreaPair(300,70)},
        {"plant_1",                 costAreaPair(25,10)},
        {"plant_2",                 costAreaPair(30,20)},
        {"plant_3",                 costAreaPair(45,25)},
        {"sideboard",               costAreaPair(175,30)},
        {"chest_of_drawers",        costAreaPair(25,40)},
        {"guest_bed",               costAreaPair(250,40)},
        {"standing_lamp",           costAreaPair(20,30)},
        {"garbage_can",             costAreaPair(30,35)},
        {"bar_with_stools",         costAreaPair(200,40)},
        {"bike_stand",              costAreaPair(100,80)},
        {"chest",                   costAreaPair(150,25)},
        {"heater",                  costAreaPair(100,25)}
    };

    auto pairs = getCosts(dictionary);
    int N = pairs.size();
    int A = max_area;

    int** table = new int* [N + 1];

    for (int i = 0; i < N + 1; i++)
    {
        table[i] = new int[A + 1];

        for (int a = 0; a < A + 1; a++)
        {
            if (a == 0 || i == 0)
            {
                table[i][a] = 0;
            }
            else if (pairs[i - 1].area <= a)
            {
                table[i][a] = max(pairs[i - 1].cost + table[i - 1][a - pairs[i - 1].area], table[i-1][a]);
            }
            else
            {
                table[i][a] = table[i - 1][a];
            }
        }
    }

    int n = pairs.size();
    int res = table[n][A];
    int a = A;
    map<string, costAreaPair> items;

    for (int i = n; i >= 0; i--)
    {
        if (res <= 0)
            break;
        else if (res == table[i - 1][a])
            continue;
        else
        {
            items.insert(pair<string, costAreaPair>(keyByValue(dictionary, pairs[i - 1]), pairs[i - 1]));
            res -= pairs[i - 1].cost;
            a -= pairs[i - 1].area;
        }
    }

    int a_sum = 0;
    int c_sum = 0;

    for (const auto& i : items)
    {
        a_sum += i.second.area;
        c_sum += i.second.cost;
        cout << 
            left << setw(40) << i.first << 
            left << setw(15) << i.second.area <<
            left << setw(40) << i.second.cost << endl;
    }

    cout << endl << "Total area " << a_sum << ". most benefit solution " << c_sum << endl;
}
