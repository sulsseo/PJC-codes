//
// Created by Jakub Trmal on 26/12/2017.
//

#include <iostream>
#include <vector>

using namespace std;

int data[] = {1, 2, 4, 6, 8, 10, 16};

std::pair<size_t, bool> binarySearch(size_t l, size_t r, int x)
{
    size_t mid;
    if (r >= l)
    {
        mid = l + (r - l)/2;

        if (data[mid] == x) return {mid, true};

        if (data[mid] > x) return binarySearch(l, mid-1, x);

        return binarySearch(mid+1, r, x);
    }

    return {mid, false};
}

int* bin_search2(size_t l, size_t r, int x)
{
    if (r >= l)
    {
        size_t mid = l + (r - l)/2;

        if (data[mid] == x) return {&data[mid]};

        if (data[mid] > x) return bin_search2(l, mid-1, x);

        return bin_search2(mid+1, r, x);
    }

    return {&data[7]};
}

int main() {
//    std::pair<int, bool> ret = binarySearch(0, 7, 16);
//    cout << ret.first << " " << ret.second;
    std::vector<int>::iterator it;
    std::vector<int> m_data({1,2,2,3,4,5,5,5,5,6,7,8,8,10,11,12});

    it = std::unique(m_data.begin(), m_data.end());
//    m_data.resize((std::distance(m_data.begin(), it)));
    for (int i = 0; i < m_data.size(); ++i) {
        cout << m_data[i] << " ";
    }
    cout << endl;

    m_data.resize((std::distance(m_data.begin(), it)));
    for (int i = 0; i < m_data.size(); ++i) {
        cout << m_data[i] << " ";
    }
    cout << endl;

    cout << ("a" < "");

    std::vector<std::string> str({ "abc", "def", "ghi" });
    cout<<std::distance(str.begin(), str.end());

    std::vector<int> range(m_data.begin(), m_data.end());
    cout << "a";


}