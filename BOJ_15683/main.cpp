#include <algorithm>
#include <bit>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vs = vector<string>;

int N, M;
vvi bd;
vii cctv;

int ans;

int check(const vvi& now) {
	auto ret = 0;

	for (const auto& r : now) {
		for (const auto& x : r) {
			if (0 == x) {
				++ret;
			}
		}
	}

	return ret;
}

void place1(vvi& cp, int d, int y, int x) {
	if (0 == d) { // --r
		for (auto r = y - 1; 0 <= r; --r) {
			if (6 == cp[r][x]) {
				break;
			}

			if (0 == cp[r][x]) {
				cp[r][x] = 9;
			}
		}
	}
	else if (1 == d) { // ++r
		for (auto r = y + 1; r < N; ++r) {
			if (6 == cp[r][x]) {
				break;
			}

			if (0 == cp[r][x]) {
				cp[r][x] = 9;
			}
		}
	}
	else if (2 == d) { // --c
		for (auto c = x - 1; 0 <= c; --c) {
			if (6 == cp[y][c]) {
				break;
			}

			if (0 == cp[y][c]) {
				cp[y][c] = 9;
			}
		}
	}
	else if (3 == d) { // ++c
		for (auto c = x + 1; c < M; ++c) {
			if (6 == cp[y][c]) {
				break;
			}

			if (0 == cp[y][c]) {
				cp[y][c] = 9;
			}
		}
	}
}

void place2(vvi& cp, int d, int y, int x) {
	if (0 == d) { // -+r
		place1(cp, 0, y, x);
		place1(cp, 1, y, x);
	}
	else if (1 == d) { // -+c
		place1(cp, 2, y, x);
		place1(cp, 3, y, x);
	}
}

void place3(vvi& cp, int d, int y, int x) {
	if (0 == d) { // --r, ++c
		place1(cp, 0, y, x);
		place1(cp, 3, y, x);
	}
	else if (1 == d) { // ++c, ++r
		place1(cp, 3, y, x);
		place1(cp, 1, y, x);
	}
	else if (2 == d) { // ++r, --c
		place1(cp, 1, y, x);
		place1(cp, 2, y, x);
	}
	else if (3 == d) { // --c, --r
		place1(cp, 2, y, x);
		place1(cp, 0, y, x);
	}
}

void place4(vvi& cp, int d, int y, int x) {
	for (auto e = 0; e < 4; ++e) {
		if (d == e) {
			continue;
		}

		place1(cp, e, y, x);
	}
}

void place5(vvi& cp, int y, int x) {
	for (auto d = 0; d < 4; ++d) {
		place1(cp, d, y, x);
	}
}

void solve(const vvi& now, int ct) {
	if (cctv.size() == ct) {
		const auto t = check(now);

		if (t < ans) {
			/*for (const auto& r : now) {
				for (const auto& x : r) {
					cout << x;
				}
				cout << endl;
			}
			cout << endl;*/

			ans = t;
		}

		return;
	}

	const auto& [y, x] = cctv[ct];
	if (1 == bd[y][x]) {
		for (auto d = 0; d < 4; ++d) {
			auto cp = vvi(now);
			place1(cp, d, y, x);
			solve(cp, ct + 1);
		}
	}
	else if (2 == bd[y][x]) {
		for (auto d = 0; d < 2; ++d) {
			auto cp = vvi(now);
			place2(cp, d, y, x);
			solve(cp, ct + 1);
		}
	}
	else if (3 == bd[y][x]) {
		for (auto d = 0; d < 4; ++d) {
			auto cp = vvi(now);
			place3(cp, d, y, x);
			solve(cp, ct + 1);
		}
	}
	else if (4 == bd[y][x]) {
		for (auto d = 0; d < 4; ++d) {
			auto cp = vvi(now);
			place4(cp, d, y, x);
			solve(cp, ct + 1);
		}
	}
	else if (5 == bd[y][x]) {
		auto cp = vvi(now);
		place5(cp, y, x);
		solve(cp, ct + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> N >> M;

	bd = vvi(N, vi(M));
	cctv = vii{};
	for (auto r = 0; r < N; ++r) {
		for (auto c = 0; c < M; ++c) {
			cin >> bd[r][c];
			if (1 <= bd[r][c] && bd[r][c] <= 5) {
				cctv.push_back({ r, c });
			}
		}
	}

	ans = numeric_limits<int>::max();
	solve(bd, 0);

	cout << ans;

	return 0;
}