#include "../container_tester.hpp"

int main () {
	std::cout << "1" << std::endl;
  ACCESS::vector<int> myvector;
  for (int i=0; i<10; i++)
  	myvector.push_back(i);                                                  
  ACCESS::vector<int>::iterator from (myvector.begin());                                                                
  ACCESS::vector<int>::iterator until (myvector.end());                                           
  ACCESS::vector<int>::reverse_iterator rev_until (from); 
  ACCESS::vector<int>::reverse_iterator rev_from (until); 
  int i = 1;
  while (rev_from != rev_until)
  {
    std::cout << ' ' << *rev_from << std::endl;
	rev_from++;
	i++;
  }
  std::cout << '\n';
  return 0;
}
