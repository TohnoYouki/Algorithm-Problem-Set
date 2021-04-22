#include<map>
#include<set>
#include<vector>
#include<iostream>
using namespace std;

constexpr long long MOD = 1000000007;
constexpr int UPPER_LIMIT = 200002;
int g_FirstPrimeFactor[UPPER_LIMIT];
map<int, int> g_PrimeCount;
map<int, int> g_PrimeOrder[UPPER_LIMIT];

void InitialPrimeFactor()
{
    vector<int> primes;
    for (int i = 0; i < UPPER_LIMIT; i++) { g_FirstPrimeFactor[i] = i; }
    for (int i = 2; i < UPPER_LIMIT; i++)
    {
        if (g_FirstPrimeFactor[i] == i) { primes.push_back(i); }
        for (int j = 0; j < primes.size(); j++)
        {
            if (primes[j] > g_FirstPrimeFactor[i]) { break; }
            if (primes[j] * i >= UPPER_LIMIT) { break; }
            g_FirstPrimeFactor[primes[j] * i] = primes[j];
        }
    }
}

void AddNumber(int index, int number, int n, long long * gcd)
{
    while (g_FirstPrimeFactor[number] > 1)
    {
        int prime = g_FirstPrimeFactor[number];
 
        auto findIter = g_PrimeOrder[index].find(prime);
        int value = findIter == g_PrimeOrder[index].end() ? 0 : findIter->second;
        g_PrimeOrder[index][prime] = value + 1;

        if (g_PrimeCount.find(prime) == g_PrimeCount.end()) { g_PrimeCount[prime] = 0; }
        if (value == 0) { g_PrimeCount[prime]++; }
        
        if (g_PrimeCount[prime] == n)
        {
            for (int i = 0; i < n; i++)
            {
                g_PrimeOrder[i][prime] -= 1;
                if (g_PrimeOrder[i][prime] == 0) { g_PrimeCount[prime]--; }
            }
            *gcd = (*gcd * prime) % MOD;
        }
        number /= prime;
    }
}

int main()
{
    int n, q;
    long long gcd = 1;
    cin >> n >> q;
    InitialPrimeFactor();
    for (int i = 0; i < n; i++) 
    {
        int a;
        cin >> a;
        AddNumber(i, a, n, &gcd);
    }
    for (int i = 0; i < q; i++)
    {
        int x, j;
        cin >> j >> x;
        AddNumber(j - 1, x, n, &gcd);
        cout << gcd << endl;
    }
    return 0;
}