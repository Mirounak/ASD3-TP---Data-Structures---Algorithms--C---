from pathlib import Path
import sys

import pandas as pd
import matplotlib.pyplot as plt

# Try to locate results.csv robustly
candidates = [
    Path('results.csv'),
    Path(__file__).with_name('results.csv'),
    Path(r'd:\Vs codes\ASD3 TP\results.csv')
]

csv_path = None
for p in candidates:
    if p.exists():
        csv_path = p
        break

if csv_path is None:
    tried = "\n".join(str(p) for p in candidates)
    sys.exit(f"results.csv not found. Tried:\n{tried}\n\nTip: run the generator first or run this script from the folder containing results.csv.")

# Load CSV
print(f"Loading: {csv_path}")
df = pd.read_csv(csv_path)

# Basic plot: n vs avg time (microseconds)
plt.figure(figsize=(8, 5))
plt.plot(df['n'], df['avg_us'], marker='o', label='avg')
if 'stdev_us' in df.columns:
    import numpy as np
    lo = np.maximum(0, df['avg_us'] - df['stdev_us'])
    hi = df['avg_us'] + df['stdev_us']
    plt.fill_between(df['n'], lo, hi, alpha=0.2, label='avg ± stdev')

plt.xscale('log')  # try linear too if preferred
plt.yscale('log')  # optional
plt.xlabel('n (input size)')
plt.ylabel('avg time (µs)')
plt.title('Algorithm performance')
plt.grid(True, which='both', ls='--', alpha=0.4)
plt.legend()
plt.tight_layout()
plt.show()
