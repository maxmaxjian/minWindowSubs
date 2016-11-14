#include <iostream>
#include <string>
#include <map>
#include <set>
#include <climits>
#include <algorithm>

class solution {
  public:
    std::string minWindow(const std::string & s, const std::string & t) {
        std::set<char> chars(t.begin(), t.end());
        std::map<char,size_t> found;
        std::map<size_t,char> exist;
        size_t begin = 0, end = INT_MAX;
        size_t idx = 0;
        while (idx < s.size()) {
            while (idx < s.size() && found.size() < chars.size()) {
                if (chars.find(s[idx]) != chars.end()) {
                    exist[idx] = s[idx];
                    found[s[idx]] = idx;
                }
                idx++;
            }

            std::cout << "begin_new = " << exist.begin()->first << ", end_new = " << exist.rbegin()->first << std::endl;
            if (exist.rbegin()->first-exist.begin()->first < end-begin) {
                begin = exist.begin()->first;
                end = exist.rbegin()->first;
            }

            auto it = std::min_element(found.begin(), found.end(),
                                       [](const std::pair<char,size_t> & p1, const std::pair<char,size_t> & p2){
                                           return p1.second < p2.second;
                                       });
            size_t minmax = it->second;
            for (auto ite = found.begin(); ite != found.end(); ) {
                if (ite->second <= minmax)
                    ite = found.erase(ite);
                else
                    ++ite;
            }
            for (auto ite = exist.begin(); ite != exist.end(); ) {
                if (ite->first <= minmax)
                    ite = exist.erase(ite);
                else
                    ++ite;
            }            
        }

        return s.substr(begin, end-begin+1);
    }
};

int main() {
    std::string s{"ADOBECODEBANC"}, t{"ABC"};

    solution soln;
    auto minStr = soln.minWindow(s, t);
    std::cout << "The minimum window in " << s << " that contains " << t << " is:\n"
              << minStr << std::endl;
}
