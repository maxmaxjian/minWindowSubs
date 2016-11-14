#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <climits>

class solution {
public:
  std::string minWindows(const std::string & s, const std::string & t) {
    std::unordered_set<char> chars(t.begin(), t.end());
    std::unordered_map<char,std::deque<size_t>> found;

    size_t begin = 0, end = INT_MAX;
    
    size_t idx = 0;
    while (idx < s.size()) {
      while (idx < s.size() && found.size() < chars.size()) {
	if (chars.find(s[idx]) != chars.end()) {
	  if (found.find(s[idx]) == found.end())
	    found[s[idx]] = std::deque<size_t>();
	  found[s[idx]].push_back(idx);
	}
	idx++;
      }

      auto it1 = std::min_element(found.begin(), found.end(),
				  [](const std::pair<char, std::deque<size_t>> & q1, const std::pair<char,std::deque<size_t>> & q2){
				    return q1.second.front() < q2.second.front();
				  });
      auto it2 = std::max_element(found.begin(), found.end(),
				  [](const std::pair<char, std::deque<size_t>> & q1, const std::pair<char,std::deque<size_t>> & q2){
				    return q1.second.back() < q2.second.back();
				  });

      // std::cout << "begin_new = " << it1->second.front() << ", end_new = " << it2->second.back() << std::endl;
      if (it2->second.back()-it1->second.front() < end-begin) {
	begin = it1->second.front();
	end = it2->second.back();
      }
    
      std::cout << "begin = " << begin << ", end = " << end << std::endl;
      // std::cout << s.substr(begin, end-begin+1) << std::endl;

      auto it = std::min_element(found.begin(), found.end(),
				 [](const std::pair<char, std::deque<size_t>> & p1, const std::pair<char, std::deque<size_t>> & p2){
				   return p1.second.back() < p2.second.back();
				 });
    
      size_t minmax = it->second.back();
      // std::cout << "minmax = " << minmax << std::endl;
      for (auto ite = found.begin(); ite != found.end();) {
	while (!ite->second.empty() && ite->second.front() <= minmax)
	  ite->second.pop_front();
	if (ite->second.empty())
	  ite = found.erase(ite);
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
  auto minSubs = soln.minWindows(s, t);
  std::cout << "The minimum window that contains " << t << " is:\n"
	    << minSubs << std::endl;
}
