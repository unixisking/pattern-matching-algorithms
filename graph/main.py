import os
import subprocess
import matplotlib.pyplot as plt
import numpy as np
import pprint


BASE_DIR = "../gen/"
ALPHABET_FOLDERS = ["alph-2", "alph-4", "alph-20", "alph-70"]
SIMPLIFIED_ALPHABET_FOLDERS = ["alph-2", "alph-70"]
PATTERN_LENGTHS = [4, 5, 6, 7, 8, 9, 10, 15, 20, 30, 40, 50]

ALGORITHMS = ["bm", "hp", "qs", "kmp","mp", "hf3", "bf3"]

COLOR_MAP = {
    "bm-alph-2": "#1f77b4",
    "bm-alph-70": "#ff7f0e",
    "hp-alph-2": "#2ca02c",
    "hp-alph-70": "#d62728",
    "qs-alph-2": "#9467bd",
    "qs-alph-70": "#8c564b",
    "kmp-alph-2": "#e377c2",
    "kmp-alph-70": "#7f7f7f",
    "mp-alph-2": "#bcbd22",
    "mp-alph-70": "#17becf",
    "hf3-alph-2": "#aec7e8",
    "hf3-alph-70": "#ffbb78",
    "bf3-alph-2": "#98df8a",
    "bf3-alph-70": "#ff9896"
}


def run_algorithm(algo, text_file, wordlist_file, pattern_length):
    """Runs the specified algorithm and returns the time taken."""
    try:
        result = subprocess.run(
            ["../search", "-a", algo, "-t", text_file, "-w", wordlist_file, "-m", str(pattern_length)],
                capture_output=True,
                text=True,
                check=True
        )
        return float(result.stdout.strip())
    except Exception as e:
        print(f"Error running {algo} with {wordlist_file}: {e}")
        return None

    
def collect_and_plot(filename, simplified=False):
    """
    Collects data for all algorithms and alphabets and plots it.
    :param filename: filename of plot that is saved in graph folder
    :param simplified: If True, only collects data for SELECTED_ALPHABET_FOLDERS.
    """
    data = {algo: {alph: [] for alph in ALPHABET_FOLDERS} for algo in ALGORITHMS}
    alphabet_folders = SIMPLIFIED_ALPHABET_FOLDERS if simplified else ALL_ALPHABET_FOLDERS

    for alph in alphabet_folders:
        text_file = os.path.join(BASE_DIR, alph, "text.txt")
        for m in PATTERN_LENGTHS:
            wordlist_file = os.path.join(BASE_DIR, alph, f"wordlist-{m}.txt")
            for algo in ALGORITHMS:
                print(f"Collecting data for algo {algo} in {alph} with pattern length: {m}...\n")
                time_taken = run_algorithm(algo, text_file, wordlist_file, m)
                if time_taken is not None:
                    data[algo][alph].append((m, time_taken))

    handles_2 = []
    handles_70 = []

    print(f"Plotting data and saving it: graph {filename}")
    plt.figure(figsize=(10, 6))

    for algo in ALGORITHMS:
        for alph in alphabet_folders:
            x = [entry[0] for entry in data[algo][alph]]
            y = [entry[1] for entry in data[algo][alph]]
            label = f"{algo.upper()} - {alph}"
            color = COLOR_MAP[f"{algo}-{alph}"]
            line, = plt.plot(x, y, marker='o', label=label, color=color)

            if alph == "alph-2":
                handles_2.append(line)
            elif alph == "alph-70":
                handles_70.append(line)

        # Add separate legends
    legend1 = plt.legend(handles=handles_2, title="Alphabet 2", loc="upper left", bbox_to_anchor=(1.05, 1))
    legend2 = plt.legend(handles=handles_70, title="Alphabet 70", loc="lower left", bbox_to_anchor=(1.05, 0))
    
    # Add the first legend back to the plot
    plt.gca().add_artist(legend1)

    plt.title("Pattern Length (M) vs. Time")
    plt.xlabel("Pattern Length (M)")
    plt.ylabel("Time (s)")
    # plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', fontsize='small')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(filename)

    return data

def collect_bar_data(alphabet, pattern_length):
    """
    Collects data for bar graph for a specific alphabet and pattern length.
    """
    text_file = os.path.join(BASE_DIR, alphabet, "text.txt")
    wordlist_file = os.path.join(BASE_DIR, alphabet, f"wordlist-{pattern_length}.txt")
    times = []

    for algo in ALGORITHMS:
        time_taken = run_algorithm(algo, text_file, wordlist_file, pattern_length)
        times.append(time_taken if time_taken is not None else 0)

    return times

def plot_bar_graph(times_2, times_70, pattern_length):
    """
    Plots a bar graph for efficiency breakdown.
    """
    bar_width = 0.35
    x = np.arange(len(ALGORITHMS))  # The label locations

    plt.figure(figsize=(10, 6))

    # Bars for alph-2 and alph-70
    plt.bar(x - bar_width / 2, times_2, bar_width, label="Alphabet 2", color="#1f77b4")
    plt.bar(x + bar_width / 2, times_70, bar_width, label="Alphabet 70", color="#ff7f0e")

    plt.title(f"Efficiency Breakdown for Pattern Length {pattern_length}")
    plt.xlabel("Algorithms")
    plt.ylabel("Time (s)")
    plt.xticks(x, [algo.upper() for algo in ALGORITHMS])
    plt.legend()
    plt.grid(axis="y", linestyle="--", alpha=0.7)
    plt.tight_layout()

    # Save and show the plot
    plt.savefig(f"efficiency_breakdown_pattern_{pattern_length}.png")

if __name__ == "__main__":
    print(collect_and_plot("comparison_plot.png", True))

    # Uncomment this code if you would like to generate a bar graph for pattern length 10 

    # pattern_length = 10
    # times_2 = collect_bar_data("alph-2", pattern_length)
    # times_70 = collect_bar_data("alph-70", pattern_length)
    # plot_bar_graph(times_2, times_70, pattern_length)



 


