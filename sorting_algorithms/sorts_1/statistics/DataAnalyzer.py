from matplotlib import pyplot as plt
from math import log


def analyze_data():
    amount = int(input("Welcome to DataAnalyzer, insert amount of data files(max 3): "))
    if amount > 3 or amount < 1:
        print("Bad amount of files")
        return
    data = ({}, {}, {})
    for k in range(amount): # setting data dictionaries
        for i in range(1, 101):
            data[k][i*100] = [0, 0, 0, 0, 0] # SIZE_OF_ARRAY : [time_clicks;time_sec;comparisions;transpositions; and last element is how many data we took]

    files_lst = []
    for _ in range(amount):
        files_lst += [input()]

    index = 0
    for files in files_lst: # taking from file and storage
        with open(files) as f:
            f.readline()
            for lines in f:
                str_data = lines.split(";")
                arr_size = int(str_data[0])
                for i in range(4):
                    if i == 1:
                        data[index][arr_size][i] += float(str_data[i+1])
                    else:
                        data[index][arr_size][i] += int(str_data[i+1]) # int to store huge values
                data[index][arr_size][4] += 1
        index += 1
    for i in range(amount): # counting average
        for dic in data[i]:
            for k in range(4):
                if k == 1:
                    data[i][dic][k] /= data[i][dic][4]
                else:
                    data[i][dic][k] //= data[i][dic][4]
    
    # plot in matplotlib
    str_options = ["Time clicks", "Time secs", "Comparisions", "Transpositions"]
    option = int(input("Choose data represented on chart:\n1." + str_options[0] + "\n2." + str_options[1] + "\n3." + str_options[2] + "\n4." + str_options[3] + "\n"))
    if 1 <= option <= 4:
        y_axis = [[], [], []]
        for i in range(amount):
            for dic in data[i]:
                y_axis[i] += [data[i][dic][option-1]]
        x_axis = [dic for dic in data[i]]
        color1 = ["r", "b", "g"]
        for i in range(amount):
            plt.plot(x_axis, y_axis[i], color1[i], label=files_lst[i])

        if option == 3:
            log_axis_x = [i for i in range(1, 10001)]
            log_axis_y = [x*log(x) for x in log_axis_x]
            plt.plot(log_axis_x, log_axis_y, "k", label="nlog(n)")
            k = 1.8
            # dla quick sort k ~ 1.69, k ~ 1.695, k ~ 1.7
            # dla dual pivot quick sort k ~ 1.55, k ~ 1.6
            # 1.8 nlog(n) + O(n)
            klog_axis_y = [k*x*log(x) for x in log_axis_x]
            plt.plot(log_axis_x, klog_axis_y, "m", label=str(k) + "nlog(n)")
        plt.legend(loc='upper left')
        plt.xlabel("Array Size")
        plt.ylabel(str_options[option-1])
        plt.show()
    else:
        print("There's no option", option)


if __name__ == "__main__":
    analyze_data()