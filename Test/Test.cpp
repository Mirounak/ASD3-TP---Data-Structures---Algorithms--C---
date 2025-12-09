#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// ---- Example algorithm to test ----
// Replace this with the algorithm you want to measure.
// It uses the input vector and does some work.
void algorithm_to_test(vector<int>& a) {
    // Example: simple linear pass
    volatile long long s = 0; // volatile to prevent optimization-away
    for (int x : a) s += x;
    (void)s;
}

// ---- Helper: generate input of size n ----
vector<int> make_input(int n) {
    vector<int> v(n);
    // deterministic input (or randomize if needed)
    for (int i = 0; i < n; ++i) v[i] = i;
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define sizes to test (customize)
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};

    // Number of trials per size (increase for more stable averages)
    const int trials = 10;

    // Output CSV file
    ofstream out("results.csv");
    if (!out) {
        cerr << "Cannot open results.csv for writing\n";
        return 1;
    }

    // CSV header: n,avg_us,stdev_us,trial1_us,trial2_us,...
    out << "n,avg_us,stdev_us";
    for (int t = 1; t <= trials; ++t) out << ",trial" << t << "_us";
    out << '\n';

    for (int n : sizes) {
        // Optionally warm up the CPU/cache (run once and discard)
        {
            auto input = make_input(n);
            algorithm_to_test(input);
        }

        vector<long long> trial_times_us;
        trial_times_us.reserve(trials);

        for (int t = 0; t < trials; ++t) {
            auto input = make_input(n); // create input for this trial

            auto t0 = high_resolution_clock::now();
            algorithm_to_test(input);
            auto t1 = high_resolution_clock::now();

            long long us = duration_cast<microseconds>(t1 - t0).count();
            trial_times_us.push_back(us);
        }

        // compute average and stdev (microseconds)
        double sum = 0;
        for (auto v : trial_times_us) sum += v;
        double avg = sum / trial_times_us.size();

        double sq = 0;
        for (auto v : trial_times_us) sq += (v - avg) * (v - avg);
        double stdev = sqrt(sq / trial_times_us.size());

        // write row
        out << n << ',' << fixed << setprecision(3) << avg << ',' << stdev;
        for (auto v : trial_times_us) out << ',' << v;
        out << '\n';

        // optional: print progress
        cerr << "Done n=" << n << " avg=" << avg << "us stdev=" << stdev << "us\n";
    }

    out.close();
    cerr << "Results written to results.csv\n";
    return 0;
}
