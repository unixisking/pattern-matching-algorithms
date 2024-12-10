# Pattern Matching Algorithms
## Project Overview

The project analyzes the performance of pattern-matching algorithms on pseudo-randomly generated texts of 500,000 characters. Tests were conducted using alphabets of sizes 2 and 70, with pattern lengths varying from 4 to 50.

## Project Structure

The repository is organized as follows:

### Directories and Files

- **`Gen/`**: Contains the generated text, alphabets, and word lists for testing.
  - Subdirectories like `alph-x/` correspond to different alphabet sizes (e.g., `2`, `70`).
  - Files include `alphabet.txt`, `text.txt`, and `wordlist-m.txt` where `m` is the pattern length.

- **`Graph/`**: Contains a Python script (`main.py`) and a virtual environment for generating performance graphs.
  - Python 3.12.3 is used with `numpy` and `matplotlib`.

- **`generator.c`**: Generates text, alphabets, and word lists based on specified parameters.

- **`gen.sh`**: Shell script to automate the generation process.

- **`algos.c`**: Contains implementations of the pattern-matching algorithms.

- **`search.c`**: Executes the algorithms from `algos.c`.

## Algorithms Implemented

The following algorithms are implemented in `algos.c`:

- **Brute Force**:
  - `bruteFS1`: Without fast loop or sentinel.
  - `bruteFS2`: With fast loop, without sentinel.
  - `bruteFS3`: With fast loop and sentinel.
- **Helper Function Variants**:
  - `searchWithHelperFunc1`: Uses `strncmp`, without fast loop or sentinel.
  - `searchWithHelperFunc2`: Uses `strncmp`, with fast loop, without sentinel.
  - `searchWithHelperFunc3`: Uses `strncmp`, with fast loop and sentinel.
- **Classic Algorithms**:
  - Morris-Pratt (MP)
  - Knuth-Morris-Pratt (KMP)
  - Boyer-Moore (BM)
  - Horspool (HP)
  - Quick Search (QS)

## Running the Project

### Generating Data

Run the following commands to generate the required data:

1. Generate the alphabet:
```bash
  ./generator -m g -a 4
 ```
2. Generate the text:
```bash
  ./generator -m t -a 4 -l 500000 -i ./gen/alph-4/alphabet.txt > ./gen/alph-4/text.txt
```
3. Generate a wordlist that contains 100 words, 8 characters each with an alphabet of size 4:
```bash
  ./generator -m w -a 4 -l 8 -n 100 -i ./gen/alph-4/alphabet > wordlist-8.txt
```

The characters used in the alphabet are randomly generated from ASCII printable characters (character codes 32-127)

## Running the project
1. Compile and execute the search program:

```bash
  ./search -a algo -t text_file -w wordlist_file -m pattern_length
  cd Graph/
  python -m venv env
  . env/bin/activate
  pip install -r matplotlib numpy
  python main.py
```

## Benchmarks and Observations
![Benchmarks for each algorithm with an alphabet of size 2 and 70](graph/comparison_plot.png "Benchmarks for each algorithm with an alphabet of size 2 and 70")

### Performance with an Alphabet of Size 2

- **Boyer-Moore (BM):**  
  BM exhibits relatively longer execution times for smaller alphabets, particularly with shorter patterns. This is because its heuristics (the bad character rule and the good suffix rule) are less effective when the number of unique characters is small. This behavior aligns with its average-case theoretical complexity of $O\left(\frac{n}{m} + m\right)$.

- **Horspool (HP) and Quick Search (QS):**  
  Horspool's simplified heuristic results in slower performance with smaller alphabets, as the limited diversity of characters reduces effective shifts. Its worst-case complexity is $O(n \cdot m)$. Quick Search follows a similar trend but with slightly different shift mechanisms.

- **Knuth-Morris-Pratt (KMP) and Morris-Pratt (MP):**  
  These algorithms exhibit constant performance regardless of alphabet size, consistent with their $O(n + m)$ complexity. However, with smaller alphabets, they are less efficient due to the limited diversity of characters, which reduces their ability to make large jumps.

- **HF3 and BF3 (Brute Force Variants):**  
  Brute-force variants with a complexity of $O(n \cdot m)$ that use fast loops and sentinels perform less effectively with small alphabets due to the lack of character diversity. Frequent matches of the initial characters that do not lead to a full pattern match limit the algorithm's efficiency in skipping comparisons until the first character match.

### Performance with an Alphabet of Size 70

- **Boyer-Moore (BM):**  
  BM demonstrates exceptional performance with larger alphabets and patterns, leveraging its heuristics to make larger jumps after mismatches. This aligns with its average-case complexity of $O\left(\frac{n}{m} + m\right)$. For larger alphabets, BM's heuristics become more effective, significantly reducing the number of comparisons.

- **Horspool (HP) and Quick Search (QS):**  
  Horspool and Quick Search perform better with larger alphabets and shorter patterns because their simplified heuristics result in larger average jumps.

- **Knuth-Morris-Pratt (KMP) and Morris-Pratt (MP):**  
  KMP and MP maintain consistent linear performance but are less efficient than BM, Horspool, and Quick Search for both small and large alphabets. Their $O(n + m)$ complexity ensures stable performance, but their ability to exploit heuristics is less effective compared to BM, Horspool, and Quick Search, especially with large alphabets.

- **HF3 and BF3 (Brute Force Variants):**  
  Traditional brute force methods generally degrade in performance as pattern length increases, given their $O(n \cdot m)$ complexity. This is especially evident with larger alphabets, where character mismatches require more exhaustive comparisons. However, this is mitigated here due to the use of fast loops and sentinels, enabling the algorithms to perform well with larger alphabets. The diversity of characters and the ability of the algorithm to skip comparisons until the first character match significantly improve efficiency.



##  Conclusion