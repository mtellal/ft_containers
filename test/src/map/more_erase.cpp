
#include "std_header.hpp"


#define T1 int
#define T2 std::string
typedef NAMESPACE::map<T1, T2>::value_type T3;

static int iter = 0;

template <typename MAP>
void	ft_erase(MAP &mp, const T1 param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

void		test(void)
{
	NAMESPACE::map<T1, T2> mp;

	mp[42] = "lol";

	mp[50] = "mdr";
	mp[25] = "funny";

	mp[46] = "bunny";
	mp[21] = "fizz";
	mp[30] = "buzz";
	mp[55] = "fuzzy";

	mp[18] = "bee";
	mp[23] = "coconut";
	mp[28] = "diary";
	mp[35] = "fiesta";
	mp[44] = "hello";
	mp[48] = "world";
	mp[53] = "this is a test";
	mp[80] = "hey";

	mp[12] = "no";
	mp[20] = "idea";
	mp[22] = "123";
	mp[24] = "345";
	mp[27] = "27";
	mp[29] = "29";
	mp[33] = "33";
	mp[38] = "38";

	mp[43] = "1";
	mp[45] = "2";
	mp[47] = "3";
	mp[49] = "4";
	mp[51] = "5";
	mp[54] = "6";
	mp[60] = "7";
	mp[90] = "8";

	printSize(mp);


	ft_erase(mp, 25); // right != NULL; left != NULL
	ft_erase(mp, 55); // right != NULL; left != NULL

	ft_erase(mp, 24); // right != NULL; left != NULL
	ft_erase(mp, 54); // right != NULL; left != NULL


	ft_erase(mp, 22); // right == NULL; left == NULL
	ft_erase(mp, 51); // right == NULL; left == NULL

	ft_erase(mp, 21); // right == NULL; left != NULL
	ft_erase(mp, 53); // right != NULL; left == NULL

	ft_erase(mp, 20); // right == NULL; left != NULL

	ft_erase(mp, 23); // right != NULL; left != NULL

	ft_erase(mp, 42); // right != NULL; left != NULL; parent == NULL
	ft_erase(mp, 38); // right != NULL; left != NULL; parent == NULL

	ft_erase(mp, 35); // right != NULL; left != NULL; parent == NULL

	ft_erase(mp, 33); // right != NULL; left != NULL; parent == NULL

}

int main()
{
	test();	
}
