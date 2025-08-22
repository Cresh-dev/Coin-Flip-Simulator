# 🎲 Coin Flip Simulator

A **C** program that simulates coin flips and analyzes the results.  
It generates random flips and provides statistics, including counts of consecutive sequences of **heads** and **tails**.

---

## 📌 Features

- Generate a customizable number of coin flips (up to 100,000).
- Display results in a formatted table:
  - Flip number
  - Numeric value (0 = HEADS, 1 = TAILS)
  - Text representation (`HEADS` / `TAILS`)
- Compute statistics:
  - Percentage distribution of heads and tails
  - Count sequences of **5 consecutive identical results** (heads or tails)
- Interactive menu for easy navigation.

---

## 🛠️ Compilation

Make sure you have a C compiler installed (e.g., `gcc`).

```bash
# Compile
gcc main.c -o coinflip

# Run
./coinflip
```

---

## 📜 License

This project is licensed under the MIT License.
See the [LICENSE](LICENSE) file for details.

- 👨 Author: Alessio Crescenzio
- 📅 Date: August 22, 2025
- 🔖 Version: 1.0.0
