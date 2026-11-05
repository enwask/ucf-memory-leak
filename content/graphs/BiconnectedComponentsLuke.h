/**
 * Author: Luke Videckis
 * Date: 2025-08-06
 * Source: https://github.com/programming-team-code/programming_team_code
 * Description: Calls f(nodes) for each biconnected component (block).
 * nodes.back() is the block's top vertex. Isolated nodes get no call.\\
 * Cut vertex iff in >=2 blocks.\\
 * On simple graph, bridges = blocks with 2 nodes.\\
 * For 2ECCs, DSU.join nodes in each block with sz >= 3.\\
 * Block-vertex tree: new node n+id for each block, with edges to all nodes in the block.
 * Usage: bcc_callback(adj, [\&](const vi\& nodes) { ... });
 * Time: O(N + M)
 */
void bcc_callback(const auto& adj, auto f) {
  int n = sz(adj), q = 0, s = 0;
  vi t(n), st(n);
  auto dfs = [&](auto&& self, int v) -> int {
    int l = t[v] = ++q;
    for (int u : adj[v]) {
      int siz = s, lu = 0;
      l = min(l, t[u] ?: (lu = self(self, st[s++] = u)));
      if (lu >= t[v]) {
        st[s++] = v;
        f({siz + all(st) - n + s});
        s = siz;
      }
    }
    return l;
  };
  rep(i, 0, n) if (!t[i]) dfs(dfs, i);
}
