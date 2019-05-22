#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Result {
   public:
       Result(vector<long> inone, long intwo) {
           one = inone;
           two = intwo;
       }
       vector<long> one;
       long two;
};

void print(std::vector<long> v)
{
    for (auto it = v.begin(); it != v.end(); ++it)
        std::cout << *it << ' ';

    std::cout << '\n';
}

Result *merge_data(vector<long> left, vector<long> right) {
    vector<long> result;
    long inv_count = 0;
    //cout << "printing..." << endl;
    //print(left);
    //print(right);
    while(left.size() > 0 or right.size() > 0) {
        if(left.size() > 0 and right.size() > 0) {
            if (left[0] < right[0]) {
                result.push_back(left[0]); 
                left.erase(left.begin());
            } else {
                result.push_back(right[0]);
                right.erase(right.begin());
                inv_count += left.size(); 
            }
        } else if (left.size() > 0){
            result.push_back(left[0]);
            left.erase(left.begin());
        } else if (right.size() > 0) {
            result.push_back(right[0]);
            right.erase(right.begin());
        }
    }
    return new Result(result, inv_count);
}

Result *sort_data(vector<long> data) {

    if (data.size() <= 1) {
        //cout << "returning ";
        //print(data);
        return new Result(data, 0);
    }

    vector<long> left;
    vector<long> right;
    vector<long>::iterator middleItr(data.begin() + data.size() / 2);

    for (auto it = data.begin(); it != data.end(); ++it) {
        if (std::distance(it, middleItr) > 0)
            left.push_back(*it);
        else
            right.push_back(*it);
    }


    Result *r1 = sort_data(left);
    Result *r2 = sort_data(right);
    //cout << "r1 is ";
    //print(r1->one);
    //cout << "r2 is ";
    //print(r2->one);

    Result *m  = merge_data(r1->one, r2->one);

    return new Result(m->one, r1->two+r2->two+m->two);
}

int main() {
    vector<long> data;
    long temp;
    cin >> temp;
    while(!cin.eof()) {
        data.push_back(temp);
        cin >> temp;
    }
    Result *r = sort_data(data);

    cout << r->two << endl;
    return 0;
}
