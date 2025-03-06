void matrixRotation(vector<vector<int>> matrix, int r) {
    int n = matrix.size();
    int m = matrix[0].size();

    for (int k = 0; k < min(n, m) / 2; k++) {
        vector<int> layer;
        int rotation = r % (2 * (n + m - 2 - 4 * k));        
        for (int i = k; i < m - k; i++) layer.push_back(matrix[k][i]);
        for (int i = k + 1; i < n - k - 1; i++) layer.push_back(matrix[i][m - k - 1]);
        for (int i = m - k - 1; i >= k; i--) layer.push_back(matrix[n - k - 1][i]);
        for (int i = n - k - 2; i > k; i--) layer.push_back(matrix[i][k]);
        
        int l = 0;
        for (int i = k; i < m - k; i++) matrix[k][i] = layer[(l + rotation) % layer.size()], l++;
        for (int i = k + 1; i < n - k - 1; i++) matrix[i][m - k - 1] = layer[(l + rotation) % layer.size()], l++;
        for (int i = m - k - 1; i >= k; i--) matrix[n - k - 1][i] = layer[(l + rotation) % layer.size()], l++;
        for (int i = n - k - 2; i > k; i--) matrix[i][k] = layer[(l + rotation) % layer.size()], l++;
    }
    
    for (const auto &row : matrix) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
}
