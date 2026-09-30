#!/usr/bin/env python3
import subprocess
import re
import csv
import matplotlib.pyplot as plt

def run_command(cmd):
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return result.stdout, result.returncode

def parse_time(output):
    match = re.search(r"Elapsed Execution Time:\s+([0-9\.]+)\s+seconds", output)
    if match:
        return float(match.group(1))
    return None

def main():
    print("Compiling executables...")
    run_command("make all")

    procs = [1, 2, 4, 8]
    runs = 3

    results_sum = {}
    results_pi = {}

    print("\n--- Benchmarking Exercise 2 (Parallel Sum 1 to 10,000,000) ---")
    for p in procs:
        times = []
        for r in range(runs):
            out, code = run_command(f"mpirun -n {p} ./exercise2_sum")
            t = parse_time(out)
            if t is not None:
                times.append(t)
        avg_time = sum(times) / len(times) if times else 0.0
        results_sum[p] = avg_time
        print(f"Processes: {p} -> Avg Time: {avg_time:.6f}s (Runs: {times})")

    print("\n--- Benchmarking Exercise 3 (Monte Carlo Pi 10,000,000 Trials) ---")
    for p in procs:
        times = []
        for r in range(runs):
            out, code = run_command(f"mpirun -n {p} ./exercise3_pi")
            t = parse_time(out)
            if t is not None:
                times.append(t)
        avg_time = sum(times) / len(times) if times else 0.0
        results_pi[p] = avg_time
        print(f"Processes: {p} -> Avg Time: {avg_time:.6f}s (Runs: {times})")

    # Compute speedup
    speedup_sum = {p: results_sum[1] / results_sum[p] if results_sum[p] > 0 else 0 for p in procs}
    speedup_pi = {p: results_pi[1] / results_pi[p] if results_pi[p] > 0 else 0 for p in procs}

    # Save to CSV
    csv_filename = "benchmark_results.csv"
    with open(csv_filename, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Processes", "Sum_Time_s", "Sum_Speedup", "Pi_Time_s", "Pi_Speedup", "Ideal_Speedup"])
        for p in procs:
            writer.writerow([
                p,
                f"{results_sum[p]:.6f}",
                f"{speedup_sum[p]:.3f}",
                f"{results_pi[p]:.6f}",
                f"{speedup_pi[p]:.3f}",
                p
            ])
    print(f"\nSaved benchmark metrics to {csv_filename}")

    # Plotting
    plt.rcParams['font.size'] = 10

    # 1. Plot Time vs Number of Processors
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(13, 5.5), dpi=300)

    # Sum plot
    ax1.plot(procs, [results_sum[p] for p in procs], 'o-', color='#1f77b4', linewidth=2.5, markersize=8, label='Parallel Sum')
    ax1.set_title("Parallel Sum: Time vs Processors", fontsize=13, fontweight='bold', pad=12)
    ax1.set_xlabel("Number of Processors (Nodes/Cores)", fontsize=11)
    ax1.set_ylabel("Execution Time (seconds)", fontsize=11)
    ax1.set_xticks(procs)
    ax1.grid(True, linestyle='--', alpha=0.6)
    for p in procs:
        ax1.annotate(f"{results_sum[p]:.4f}s", (p, results_sum[p]), textcoords="offset points", xytext=(0, 10), ha='center', fontweight='bold', fontsize=9)
    ax1.legend(loc='upper right')

    # Pi plot
    ax2.plot(procs, [results_pi[p] for p in procs], 's-', color='#d62728', linewidth=2.5, markersize=8, label='Monte Carlo Pi')
    ax2.set_title("Monte Carlo Pi: Time vs Processors", fontsize=13, fontweight='bold', pad=12)
    ax2.set_xlabel("Number of Processors (Nodes/Cores)", fontsize=11)
    ax2.set_ylabel("Execution Time (seconds)", fontsize=11)
    ax2.set_xticks(procs)
    ax2.grid(True, linestyle='--', alpha=0.6)
    for p in procs:
        ax2.annotate(f"{results_pi[p]:.4f}s", (p, results_pi[p]), textcoords="offset points", xytext=(0, 10), ha='center', fontweight='bold', fontsize=9)
    ax2.legend(loc='upper right')

    plt.tight_layout()
    plt.savefig("time_vs_processors.png", dpi=300)
    plt.close()
    print("Generated plot: time_vs_processors.png")

    # 2. Plot Speedup vs Number of Processors
    fig, ax = plt.subplots(figsize=(8, 6), dpi=300)
    ideal = procs
    ax.plot(procs, ideal, '--', color='#7f7f7f', linewidth=2, label='Ideal Linear Speedup')
    ax.plot(procs, [speedup_sum[p] for p in procs], 'o-', color='#1f77b4', linewidth=2.5, markersize=8, label='Parallel Sum Speedup')
    ax.plot(procs, [speedup_pi[p] for p in procs], 's-', color='#d62728', linewidth=2.5, markersize=8, label='Monte Carlo Pi Speedup')

    ax.set_title("Exercise 4: Speedup vs Number of Processors", fontsize=14, fontweight='bold', pad=15)
    ax.set_xlabel("Number of Processors (P)", fontsize=12)
    ax.set_ylabel("Speedup S(P) = T(1) / T(P)", fontsize=12)
    ax.set_xticks(procs)
    ax.set_ylim(bottom=0)
    ax.grid(True, linestyle='--', alpha=0.6)

    for p in procs:
        ax.annotate(f"{speedup_sum[p]:.2f}x", (p, speedup_sum[p]), textcoords="offset points", xytext=(-15, 8), color='#1f77b4', fontweight='bold', fontsize=9)
        ax.annotate(f"{speedup_pi[p]:.2f}x", (p, speedup_pi[p]), textcoords="offset points", xytext=(10, -12), color='#d62728', fontweight='bold', fontsize=9)

    ax.legend(loc='upper left', frameon=True)
    plt.tight_layout()
    plt.savefig("speedup_vs_processors.png", dpi=300)
    plt.close()
    print("Generated plot: speedup_vs_processors.png")

if __name__ == "__main__":
    main()
