void plusMinus(vector<int> arr) {
    int n = arr.size();
    int positive_count = 0, negative_count = 0, zero_count = 0;
    
    for (int num : arr) {
        if (num > 0) {
            positive_count++;
        } else if (num < 0) {
            negative_count++;
        } else {
            zero_count++;
        }
    }
    
    cout << fixed << setprecision(6);
    cout << (double)positive_count / n << "\n";
    cout << (double)negative_count / n << "\n";
    cout << (double)zero_count / n << "\n";
}
