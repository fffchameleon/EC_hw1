import pandas as pd
import matplotlib.pyplot as plt

def plot_data(filename):
    data = pd.read_csv(filename)

    plt.figure(figsize=(12, 7))
    plt.plot(data["Binary"], label="Binary Fitness")
    plt.plot(data["Real"], label="Real Fitness")
    plt.xlabel("Generation")
    plt.ylabel("Fitness")
    plt.title("Fitness per Generation")
    plt.legend()
    plt.grid(True)
    plt.savefig("data/fitness_plot.png")  # Save the figure to a file
    plt.show()

if __name__ == "__main__":
    plot_data("data/fitness.csv")
