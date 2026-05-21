#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <set>
#include <algorithm>

typedef double d;
using namespace std;

class DecisionTree
{
private:
    d best_information_gain;
    d best_threshold;
    vector<vector<d>> data_points; // class labels
    long long n;

public:
    DecisionTree(vector<vector<d>> data)
    {
        best_information_gain = 0.0;
        best_threshold = 0.0;
        n = data.size();
        data_points = data;
        sort(data_points.begin(), data_points.end());
    }
    d getThreshold()
    {
        return best_threshold;
    }
    vector<d> calculateEntropy(vector<vector<d>> &nums)
    {
        long long p1 = 0;
        long long p0 = 0;
        long long ns = nums.size();
        if (ns == 0)
            return {0.0, 0.0, 0.0};

        for (int i = 0; i < ns; i++)
        {
            if (nums[i][1] == 0)
                p0++;
            else
                p1++;
        }

        d entropy = 0.0;
        if (p0 > 0)
        {
            d prob0 = (p0 * 1.0) / ns;
            entropy -= prob0 * log2(prob0);
        }
        if (p1 > 0)
        {
            d prob1 = (p1 * 1.0) / ns;
            entropy -= prob1 * log2(prob1);
        }

        return {entropy, p0 * 1.0, p1 * 1.0};
    }
    vector<d> bestDecision()
    {
        set<d> thresholdValues;
        for (int i = 1; i < n; i++)
        {
            thresholdValues.insert((data_points[i][0] + data_points[i - 1][0]) / 2.0);
        }
        // sorted inputted the threshold values
        d parentH = calculateEntropy(data_points)[0];
        for (const auto &element : thresholdValues)
        {
            vector<vector<d>> checkArrayLeft;
            vector<vector<d>> checkArrayRight;
            long long ls = 0;
            long long rs = 0;
            // calculate left entropy
            for (int i = 0; i < n; i++)
            {
                if (data_points[i][0] < element)
                {
                    checkArrayLeft.push_back(data_points[i]);
                    ls++;
                }
                else
                {
                    checkArrayRight.push_back(data_points[i]);
                    rs++;
                }
            }
            d leftEntropy = calculateEntropy(checkArrayLeft)[0];
            d rightEntropy = calculateEntropy(checkArrayRight)[0];
            d informationGain = parentH - (((ls * 1.0) / n) * leftEntropy + rightEntropy * ((rs * 1.0) / n));
            if (informationGain > best_information_gain)
            {
                best_information_gain = informationGain;
                best_threshold = element;
            }
        }
        return {best_information_gain, best_threshold};
    }
};
int main()
{
    vector<vector<d>> data = {{1, 0}, {2, 1}, {3, 0}, {4, 1}, {5, 1}};
    DecisionTree dr(data);
    d best_information_gain = dr.bestDecision()[0];
    d best_threshold = dr.getThreshold();
    cout << "The best information gain is " << best_information_gain << " and the threshold is " << best_threshold << endl;
    return 0;
}