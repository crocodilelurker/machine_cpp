#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
typedef double d;
using namespace std;
class LogisticRegression 
{
    private:
    d w;
    d c;
    d n;
    public:
    LogisticRegression()
    {
        w = 0.001;
        c = 0.001;
        n = 0;
    }
    void fit(vector<d>x, vector<d>y, int epoch, d lr)
    {
        int n = x.size();
        if(n!=y.size())
        {
            throw length_error("Same Size Sets should be provided");
        }
        for(int ev = 1; ev <= epoch;ev++)
        {
            d w_diff = 0.0;
            d b_diff = 0.0;
            for(int i = 0;i< n;i++)
            {
                d z= w*x[i] + c;
                d yib = 1 / (1 + exp(-z));
                d t = yib- y[i];
                w_diff += t* x[i];
                b_diff += t;
            }
            w_diff/= n;
            b_diff/= n;
            //cout << "For Epoch no "<<ev<<" the weight loss "<<w_diff <<" and the bias loss "<<b_diff <<endl;
            w -= lr*w_diff;
            c -= lr*b_diff;
        }
        cout << "The parting line equation is y = " << w<< "x + "<<c<<endl;
    }
    d getBias(void)
    {   
        return c;
    }
    d getWeight(void)
    {
        return w;
    }
};

int main()
{
    LogisticRegression lr;
    vector<d>x = {1.0,2.0,3.0,4.0,5.0};
    vector<d>y= {0,0,0,1,1};

    lr.fit(x,y,10000,0.1);
    d eq_bias = lr.getBias();
    d eq_weight = lr.getWeight();
    return 0;
}