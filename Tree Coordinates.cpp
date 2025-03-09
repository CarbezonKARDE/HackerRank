#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstdlib>
#include <ctime>
#include <deque>
using namespace std;
#define N 200000

int fa[N][21], dep[N], L[N], R[N], Time, n, m;
vector <int> ve[N], ve1[N];
bool used[N];
int zx, sz;
int sum[N], l[N], c[N];
int ans;
int ma1[N], ma2[N], c1[N], c2[N];
int zhan[N], zhan1[N];

void dfs1(int k, int f) {
	fa[k][0] = f;
	dep[k] = dep[f] + 1;
	for (int i = 1; i <= 20; i++)
		fa[k][i] = fa[fa[k][i - 1]][i - 1];
	L[k] = ++Time;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (ve[k][i] != f)
			dfs1(ve[k][i], k);
	R[k] = Time;
}
void dfs_size(int k) {
	sum[k] = 1;
	used[k] = true;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			dfs_size(ve[k][i]);
			sum[k] += sum[ve[k][i]];
		}
	used[k] = false;
}
void dfs_zx(int k) {
	bool ok = (sz - sum[k] <= sz / 2);
	used[k] = true;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			if (sum[ve[k][i]] > sz / 2)
				ok = false;
			dfs_zx(ve[k][i]);
		}
	used[k] = false;
	if (ok)
		zx = k;
}
void dfs_l(int k) {
	used[k] = true;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			l[ve[k][i]] = l[k] + 1;
			dfs_l(ve[k][i]);
		}
	used[k] = false;
}
void dfs_c(int k) {
	used[k] = true;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			c[ve[k][i]] = c[k];
			dfs_c(ve[k][i]);
		}
	used[k] = false;
}
bool cmp_c(pair<int, int> x, pair<int, int> y) {
	return c[x.first] < c[y.first];
}

bool cmp_L(int x, int y) {
	return L[x] < L[y];
}
int dist(int x, int y) {
	int ans = 0;
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (dep[fa[x][i]] >= dep[y])
			ans += (1 << i), x = fa[x][i];
	if (x == y)
		return ans;
	for (int i = 20; i >= 0; i--)
		if (fa[x][i] != fa[y][i])
			ans += 1 << (i + 1), x = fa[x][i], y = fa[y][i];
	return ans + 2;
}
int lca(int x, int y) {
	int ans = 0;
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (dep[fa[x][i]] >= dep[y])
			ans += (1 << i), x = fa[x][i];
	if (x == y)
		return x;
	for (int i = 20; i >= 0; i--)
		if (fa[x][i] != fa[y][i])
			ans += 1 << (i + 1), x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void dfs_d(int k) {
	for (int i = 0; i < (int) ve1[k].size(); i++) {
		int t = ve1[k][i];
		dfs_d(t);
		ma1[t] += dep[t] - dep[k];
		ma2[t] += dep[t] - dep[k];
		if (c1[k] != c1[t] || !c1[k] || !c1[t])
			ans = max(ans, ma1[k] + ma1[t]);
		if (c1[k] != c2[t] || !c1[k] || !c2[t])
			ans = max(ans, ma1[k] + ma2[t]);

		if (c2[k] != c1[t] || !c2[k] || !c1[t])
			ans = max(ans, ma2[k] + ma1[t]);

		if (c2[k] != c2[t] || !c2[k] || !c2[t])
			ans = max(ans, ma2[k] + ma2[t]);
		
		if (ma1[t] > ma1[k]) {
			if (c1[t] == c1[k])
				ma1[k] = ma1[t];
			else {
				ma2[k] = ma1[k];
				c2[k] = c1[k];
				ma1[k] = ma1[t];
				c1[k] = c1[t];
			}
		}else if (ma1[t] > ma2[k] && c1[t] != c1[k]) {
			ma2[k] = ma1[t];
			c2[k] = c1[t];
		}
		if (ma2[t] > ma1[k]) {
			if (c2[t] == c1[k])
				ma1[k] = ma2[t];
			else {
				ma2[k] = ma1[k];
				c2[k] = c1[k];
				ma1[k] = ma2[t];
				c1[k] = c2[t];
			}
		}else if (ma2[t] > ma2[k] && c2[t] != c1[k]) {
			ma2[k] = ma2[t];
			c2[k] = c2[t];
		}
	}
}

void doit(vector <pair<int, int> > V) {
	int len = 0;
	for (int i = 0; i < (int) V.size(); i++) {
		zhan[++len] = V[i].second;
		if (c[V[i].first] != c1[V[i].second] || !c[V[i].first] || !c1[V[i].second]) {
			ans = max(ans, ma1[V[i].second] + l[V[i].first]);
		}
		if (c[V[i].first] != c2[V[i].second] || !c[V[i].first] || !c2[V[i].second]) {
			ans = max(ans, ma2[V[i].second] + l[V[i].first]);
		}
		if (l[V[i].first] > ma1[V[i].second]) {
			if (c[V[i].first] != c1[V[i].second]) {
				ma2[V[i].second] = ma1[V[i].second];
				c2[V[i].second] = c1[V[i].second];
				ma1[V[i].second] = l[V[i].first];
				c1[V[i].second] = c[V[i].first];
			}else {
				ma1[V[i].second] = l[V[i].first];
			}
		}else if (l[V[i].first] > ma2[V[i].second] && c[V[i].first] != c1[V[i].second]) {
			ma2[V[i].second] = l[V[i].first];
			c2[V[i].second] = c[V[i].first];
		}
	}
	sort(zhan + 1, zhan + len + 1, cmp_L);

	for (int i = len; i > 1; i--) {
		zhan[++len] = lca(zhan[i - 1], zhan[i]);
	}
	sort(zhan + 1, zhan + len + 1, cmp_L);
	for (int i = 1; i < len; i++) {
		ve1[zhan[i]].clear();
	}

	int len1 = 0;
	zhan1[len1 = 1] = zhan[1];
	for (int i = 2; i <= len; i++)
		if (zhan[i] != zhan[i - 1]) {
			while (len1 > 0 && R[zhan1[len1]] < L[zhan[i]])
				len1 --;
			zhan1[++len1] = zhan[i];
			ve1[zhan1[len1 - 1]].push_back(zhan1[len1]);
		}
	dfs_d(zhan[1]);
	for (int i = 1; i <= len; i++) {
		ma1[zhan[i]] = ma2[zhan[i]] = -1000000000;
	}
}

void doit1(vector <pair<int, int> > V) {
	for (int i = 0; i < (int) V.size(); i++)
		for (int j = 0; j < i; j++)
				ans = max(ans, dist(V[i].first, V[j].first) + dist(V[i].second, V[j].second));
}

void dfs(int k, vector <pair<int, int> > V) {
	if (V.size() <= 1)
		return ;
	if (V.size() <= 100) {
		doit1(V);
		return ;
	}
	dfs_size(k);
	sz = sum[k];
	dfs_zx(k);
	k = zx;
	l[k] = 0;
	dfs_l(k);
	c[k] = 0;
	used[k] = true;
	int tot = 0;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			tot += 1;
			c[ve[k][i]] = tot;
			dfs_c(ve[k][i]);
		}
	used[k] = false;
	doit(V);
	sort(V.begin(), V.end(), cmp_c);
	int q = 0;
	used[k] = true;
	vector <int> vv;
	for (int i = 0; i <= tot; i++) {
		while (q < (int) V.size() && c[V[q].first] <= i)
			q += 1;
		vv.push_back(q);
	}
	tot = 0;
	for (int i = 0; i < (int) ve[k].size(); i++)
		if (!used[ve[k][i]]) {
			tot += 1;
			vector <pair<int, int> > V1;
			for (int j = vv[tot - 1]; j < vv[tot]; j++)
				V1.push_back(V[j]);
			dfs(ve[k][i], V1);
		}
	used[k] = false;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		ve[x].push_back(y);
		ve[y].push_back(x);
	}
	vector <pair<int, int> > V;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		V.push_back(make_pair(x, y));
	}
	dfs1(1, 0);
	for (int i = 1; i <= n; i++)
		ma1[i] = ma2[i] = -1000000000;
	dfs(1, V);
	printf("%d\n", ans);
}
