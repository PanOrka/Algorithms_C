# **Sorts_C**
## **Including:**
* **Insertion Sort** + _stats_
* **Merge Sort** + _stats_
* **Quick Sort** + _stats_
* **Dual Pivot Quick Sort** + _stats_
* **Hybrid Merge-Insertion Sort** + _stats_
* **Hybrid Quick-Insertion Sort** + _stats_
* **Hybrid Merge-Quick Sort** + _stats_
* **Hybrid Quick-Merge Sort** + _stats_
* **DataAnalyzer.py** - program for drawing charts of statistics, can draw up to 3 charts of statistics done with --stat option. Matplotlib and python needed (done on 3.6.9). After run program reads amount and path of files.

Automated compilation with run.c. After compilation we can choose algorithm run options.<br>
**Options:**
* **--type** - _insert_, _merge_, _quick_, _dpquick_, _hybridmi_, _hybridqi_, _hybridmq_, _hybridqm_ (type of sort, needed to compile)
* **--comp** - _"<="_, _">="_ (sort order, needed to compile, **with hybrid only --comp defined**)
* **--stat** - _filename_, _k_ (sort statistics in k tests with n*100 sized array 1<=n<=100 saved to filename, optional)

**Example:** _./run --type merge --comp "<=" --stat ./statistics/data.txt 10_<br><br>
I used permuted congruential generator here for --stat option to randomly generate arrays to avoid cycles of random numbers. Files: pcg_basic.c and pcg_basic.h were downloaded from site: https://www.pcg-random.org/ and are not mine.
