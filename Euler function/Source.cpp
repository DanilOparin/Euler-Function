#include <iostream>
#include <thread>
#include <cmath>
#include <vector>

void print_vector(std::vector<int>& set)
{
	for (std::vector<int>::iterator i = set.begin(); i != set.end(); i++)
	{
		std::cout << *i << std::endl;
	}
}

void Euler_function(int n)
{
	std::vector<int>set_of_divisors;
	std::vector<int>set_of_divisors2;
	std::vector<int>set_of_divisors3;
	std::vector<int>set_of_divisors4;
	
	

	std::cout << "делители числа N" << std::endl;
	std::thread thread1([&]()
	{
		for (int i = 2; i <= n / 4; i++)
		{
			if (n % i == 0)
			{
				set_of_divisors2.push_back(i);
			}
		}
			
	});
	
	for (int i = n/2; i > n / 4; i--)
	{
		if (n % i == 0)
		{
			set_of_divisors3.push_back(i);
		}
	}
	thread1.join();



	//два получившихс€ вектора из делителей соедин€ем в один чтобы потом упростить
	std::thread thread2([&]()
	{
		for (int i1 = 0; i1 < set_of_divisors2.size(); i1++)
		{
			std::vector<int>::iterator j1 = set_of_divisors.begin() + i1;
			set_of_divisors.insert(j1, set_of_divisors2[i1]);

		}
	});
	

	for (int i2 = 0; i2 < set_of_divisors3.size(); i2++)
	{
		std::vector<int>::iterator j2 = set_of_divisors.end()-i2;
		set_of_divisors.insert(j2, set_of_divisors3[i2]);
		
	}
	thread2.join();


	print_vector(set_of_divisors);
	//убираем все числа которые не нужны
	std::cout << "упрощение..." << std::endl;
	for (std::vector<int>::iterator i = set_of_divisors.begin(); i != set_of_divisors.end(); i++)
	{
		for (std::vector<int>::iterator j = i + 1; j != set_of_divisors.end(); j++)
		{
			if (*(j) % *(i) == 0)
			{

				j = set_of_divisors.erase(j);
				j -= 1;

			}
		}
	}

	print_vector(set_of_divisors);


	// ‘ункци€ Ёйлера от натурального числа
	for (int i = 0; i < set_of_divisors.size(); i++)
	{
		int n2 = n;
		int degree = 0;
		while (n2 % set_of_divisors[i]==0)
		{
			degree++;
			n2 = n2 / set_of_divisors[i];
		}
		
		int fi_x = pow(set_of_divisors[i], degree);
		set_of_divisors4.push_back(fi_x - pow(set_of_divisors[i],degree-1));
		
	}
	

	int phi = 1;
	for (int i = 0; i < set_of_divisors4.size(); i++)
	{
		phi = phi * set_of_divisors4[i];


	}
	std::cout <<"phi"<< phi;
}



int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n;
	std::cin >> n;



	Euler_function(n);
	

	return 0;
}