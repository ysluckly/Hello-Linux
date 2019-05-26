/*************************************************************************
	> File Name:    Day4.cpp
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Sun 26 May 2019 03:59:34 AM PDT
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

int main()
{
    int w , h ,res=0;
    cin >> w >> h;

    vector< vector<int> > v;
    v.resize(w);

    for(auto & e : v)
    {
        e.resize(h,1);
    }

    for(int i = 0 ; i< w; ++i)
    {
        for(int j = 0; j<h; ++j)
        {
            if(v[i][j] == 1)
            {
                res++;
                if(i+2 < w )
                {
                    v[i+2][j] = 0;
                }

                if(j+2 < h)
                {
                    v[i][j+2] = 0;
                }

            }
        }
    }
    cout << res << endl;
    return 0;
}
