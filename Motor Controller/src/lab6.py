import matplotlib.pyplot as plt


def plot_position(samples, target=None):
    """Visualize a captured UART stream of motor-position samples."""
    plt.plot(samples, label="measured position")
    if target is not None:
        plt.axhline(target, color="tab:red", linestyle="--", label="target")
    plt.xlabel("sample")
    plt.ylabel("encoder position")
    plt.title("Closed-loop motor-position response")
    plt.grid(True)
    plt.legend()
    plt.show()
