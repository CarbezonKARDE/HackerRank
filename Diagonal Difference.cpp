int diagonalDifference(vector<vector<int>> arr) {
    int i, j, size, diag1, diag2;
    i = j = diag1 = diag2 = 0;
    size = arr.size();
    j = size - 1;
    while (i < size) {
        diag1 += arr[i][i];
        diag2 += arr[i][j];
        ++i;
        --j;
    }
    return abs(diag1 - diag2);
}
