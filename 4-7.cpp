#include <iostream>
#include <vector>

using std::vector;              using std::string;
using std::cin;                 using std::istream;
using std::cout;
using std::endl;

double average(vector<double>& data)
{
    int sizeData = 0;
    double sum = 0;

    sizeData = data.size();
    for(vector<double>::iterator it = data.begin(); it < data.end(); it++) {
        sum += *it;
    }

    return sum / sizeData;
}

int main()
{
    vector<double> gameAverages = {.25, .333, .75, .00, .25};
    double playoffAverage = 0;

    playoffAverage = average(gameAverages);

    cout << "Baseball player's playoff batting average is " << playoffAverage << endl;

    return 0;
}
