#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class LinearRegression {
    private:
    double m, c;
    public :
    LinearRegression()
    {
        m = 0;
        c = 0;
    }
    void fit(vector<double> x, vector<double> y)
    {
        int n =x.size();
        if(n!= y.size())
        {
            throw length_error("both sets length should be same");
        }
        double x_mean = 0.0;
        for(double xi : x)
        {
            x_mean+=xi;
        }
        x_mean/=(n*1.0);
        double y_mean = 0.0;
        for(double yi :y)
        {
            y_mean+=yi;
        }
        y_mean/=(n*1.0);
        double normal_num = 0.0;
        for(int i = 0;i <n;i++)
        {
            double prod = (x[i]-x_mean)*(y[i]-y_mean);
            normal_num += prod;
        }
        double normal_den = 0.0;
        for(int i = 0;i <n;i++)
        {
            double prod = (x[i]-x_mean);
            prod*=prod;
            normal_den += prod;
        }
        m = normal_num/normal_den;
        c = y_mean - m*x_mean;
    }
    double getWeight(void)
    {
        return m;
    }
    double getBias(void)
    {
        return c;
    }
};
int main()
{
    LinearRegression lr;
    vector <double>  x = {1.0, 2.0, 3.0, 4.0 ,5.0};
    vector <double> y ={2.0 ,4.0, 5.0, 4.0, 6.0};
    lr.fit(x,y);
    cout << "The Weight and Bias of the resultant equation is " << lr.getWeight() << "x + " <<lr.getBias()<<endl;
}