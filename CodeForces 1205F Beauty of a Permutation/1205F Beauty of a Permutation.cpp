#include<iostream>
#include<string>
using namespace std;
bool exist[101][51 * 101];
int last[101][51 * 101];
bool order[101][51 * 101];
void permutation(int n, int k, int base, bool coutOrder) {
	int number = last[n][k];
	if (n == 1) {
		cout << base + 1;
		return;
	}
	if (coutOrder && order[n][k]) {
		for (int i = 1; i < number; i++) cout << base + i << " ";
		permutation(n + 1 - number, k + 1 - number * (number + 1) / 2, base + number - 1, !coutOrder);
	}
	else if (!coutOrder && order[n][k]) {
		permutation(n + 1 - number, k + 1 - number * (number + 1) / 2, base + number - 1, !coutOrder);
		for (int i = number - 1; i >= 1; i--) cout << " " << base + i;
	}
	else if (coutOrder && !order[n][k]) {
		if (n % 2 == 0) {
			for (int i = n - 1; i >= 1; i = i - 2) cout << base + i << " ";
			permutation(n + 1 - number, k - number, base + number - 1, !coutOrder);
			for (int i = n - 2; i >= 2; i = i - 2) cout << " " << base + i;
		}
		else {
			for (int i = n - 1; i >= 2; i = i - 2) cout << base + i << " ";
			permutation(n + 1 - number, k - number, base + number - 1, !coutOrder);
			for (int i = 1; i <= n - 2; i = i + 2) cout << " " << base + i;
		}
	}
	else if (!coutOrder && !order[n][k]) {
		if (n % 2 == 0) {
			for (int i = 2; i <= n - 2; i = i + 2) cout << base + i << " ";
			permutation(n + 1 - number, k - number, base + number - 1, !coutOrder);
			for (int i = 1; i <= n - 1; i = i + 2)cout << " " << base + i;
		}
		else {
			for (int i = n - 2; i >= 1; i = i - 2) cout << base + i << " ";
			permutation(n + 1 - number, k - number, base + number - 1, !coutOrder);
			for (int i = 2; i <= n - 1; i = i + 2) cout << " " << base + i;
		}
	}
}
int main()
{
	for (int i = 1; i <= 100; i++)
		for (int j = 1; j <= i * (i + 1) / 2; j++)
			exist[i][j] = false;
	for (int i = 1; i <= 100; i++) {
		exist[i][i*(i + 1) / 2] = true;
		last[i][i*(i + 1) / 2] = i;
		order[i][i*(i + 1) / 2] = true;
		if (i >= 4) { exist[i][i + 1] = true; last[i][i + 1] = i; order[i][i + 1] = false; }
		for (int j = i + 2; j < i * (i + 1) / 2; j++) {
			for (int k = 2; k <= i - 1; k++) 
				if (j + 1 - k * (k + 1) / 2 > i + 1 - k && exist[i + 1 - k][j + 1 - k * (k + 1) / 2]) {
					exist[i][j] = true;
					last[i][j] = k;
					order[i][j] = true;
					break;
				}
			if (!exist[i][j])
				for (int k = 4; k <= i - 1; k++)
					if (j > i + 1 && exist[i + 1 - k][j - k]) {
						exist[i][j] = true;
						last[i][j] = k;
						order[i][j] = false;
						break;
					}
		}
	}
	int q, n, k;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		cin >> n >> k;
		if (exist[n][k]) cout << "YES" << endl; else cout << "NO" << endl;
		if (exist[n][k]) {
			permutation(n, k, 0, true); 
			cout << endl;
		}
	}
	return 0;
}