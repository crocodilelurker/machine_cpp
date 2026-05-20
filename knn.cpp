#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
typedef double d;
using namespace std;

class KNearestNeighbours {
    private:
    vector<vector<d>> data_points;
    vector<d>labels;
    public:
    KNearestNeighbours(vector<vector<d>>dp,vector<d>lab)
    {
        data_points = dp;
        labels= lab;
        if(dp.size()!=lab.size())
        {
            throw length_error("Same Size data points and labels should be provided (supervised learning)");
        }
    }
    void predict(vector<d>point) // x , y , z
    {
        int n = data_points.size();
        int dimension = point.size();
        vector <vector<d>> resultScores;
        for(int i =0 ;i< n;i++)
        {
            d resultScore = 0.0;
            for(int j =0 ;j<dimension;j++)
            {
                resultScore += (data_points[i][j] - point[j])*(data_points[i][j] - point[j]);
            }
            resultScore = sqrt(resultScore);
            resultScores.push_back({resultScore,labels[i]});
        }
        sort(resultScores.begin(),resultScores.end());
        //assuming k = 3 
        // i would create a map where label and votes will store and the maximum label will be choosen
        map<d,long> mp; //label and score 
        for(int i = 0; i<3;i++)
        {
            mp[resultScores[i][1]]++;
        }
        long most_voted = 0;
        d label_win =0.0;
        for(const auto& pair : mp)
        {
            if(pair.second > most_voted)
            {
                most_voted = pair.second;
                label_win = pair.first;
            }
        }
        cout << "The Predicted Point belongs to class label "<< label_win <<endl;
    }

};

int main()
{
    vector <vector<d>> dp= { {1.0,1.0},{2.0,2.0},{5.0,4.0},{6.0,6.0},{7.0,6.0}, {7.0,7.0}};
    vector <d> lb= {0,0,0,1,1,1};
    KNearestNeighbours knn(dp,lb);
    knn.predict({5.0,5.0});
    knn.predict({1.0,7.5});
    return 0;
}


// we can improve working by just directly not pushing but passing it through a function that arranges it in asc manner 