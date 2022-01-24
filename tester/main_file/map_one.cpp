#include "../container_tester.hpp"

int main ()
{
	ACCESS::map<int, std::string> v;

	std::cout << v.insert(ACCESS::make_pair(1, "A5")).first->first << std::endl;
	std::cout << v.insert(ACCESS::make_pair(12, "I2")).first->first << std::endl;
	std::cout << v.insert(ACCESS::make_pair(13, "D3")).first->first << std::endl;
	std::cout << v.insert(ACCESS::make_pair(14, "C4")).first->first << std::endl;
	std::cout << v.insert(ACCESS::make_pair(15, "B1")).first->first << std::endl;
	std::cout << v.insert(ACCESS::make_pair(16, "B1")).first->first << std::endl;
	std::cout << v.insert(ACCESS::make_pair(130, "B1")).first->first << std::endl;
	std::cout << "range: " << ((v.equal_range(1)).first)->first <<  " and " << ((v.equal_range(1)).first)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(3)).first)->first <<  " and " << ((v.equal_range(3)).first)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(4)).first)->first <<  " and " << ((v.equal_range(4)).first)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(6)).first)->first <<  " and " << ((v.equal_range(6)).first)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(10)).first)->first <<  " and " << ((v.equal_range(10)).first)->second << std::endl;
	
	std::cout << "range: " << ((v.equal_range(1)).second)->first <<  " and " << ((v.equal_range(1)).second)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(3)).second)->first <<  " and " << ((v.equal_range(3)).second)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(4)).second)->first <<  " and " << ((v.equal_range(4)).second)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(6)).second)->first <<  " and " << ((v.equal_range(6)).second)->second << std::endl;
	std::cout << "range: " << ((v.equal_range(10)).second)->first <<  " and " << ((v.equal_range(10)).second)->second << std::endl;




	ACCESS::map<int, char> first;

	std::cout << first.insert(ACCESS::make_pair(1, 'a')).first->first << std::endl;
	std::cout << first.insert(ACCESS::make_pair(12, 'b')).first->first << std::endl;
	std::cout << first.insert(ACCESS::make_pair(13, 'c')).first->first << std::endl;
	std::cout << first.insert(ACCESS::make_pair(14, 'd')).first->first << std::endl;
	std::cout << first.insert(ACCESS::make_pair(15, 'e')).first->first << std::endl;

	
	ACCESS::map<int, char> second;
	std::cout << second.insert(ACCESS::make_pair(1, 'f')).first->first << std::endl;
	std::cout << second.insert(ACCESS::make_pair(12, 'g')).first->first << std::endl;
	std::cout << second.insert(ACCESS::make_pair(13, 'h')).first->first << std::endl;
	std::cout << second.insert(ACCESS::make_pair(14, 'i')).first->first << std::endl;
	std::cout << second.insert(ACCESS::make_pair(15, 'j')).first->first << std::endl;
	ACCESS::map<int, char>::iterator it = first.begin();
	ACCESS::map<int, char>::iterator ite = first.end();
	while(it != ite)
	{
		std::cout << "*it = : " << (*it).first << " and ite = " << (*it).second << std::endl;
		it++;
	}
	ACCESS::map<int, char>::iterator it2 = second.begin();
	ACCESS::map<int, char>::iterator ite2 = second.end();
	while(it2 != ite2)
	{
		std::cout << "*it2 = : " << (*it2).first << " and ite2 = " << (*it2).second << std::endl;
		it2++;
	}
	second.size();
	first.size();
	second.swap(first);
	it = first.begin();
	ite = first.end();
	while(it != ite)
	{
		std::cout << "*it = : " << (*it).first << " and ite = " << (*it).second << std::endl;
		it++;
	}
	it2 = second.begin();
	ite2 = second.end();
	while(it2 != ite2)
	{
		std::cout << "*it2 = : " << (*it2).first << " and ite2 = " << (*it2).second << std::endl;
		it2++;
	}
	second.size();
	first.size();
}