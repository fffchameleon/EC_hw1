import os
import sys
import pandas as pd
import matplotlib.pyplot as plt

# out_name = sys.argv[1]
# filename_pattern = sys.argv[2]
# title = sys.argv[3]

folder_path = 'data'

conditions = [
    # ('uniform'),
    # ('binary', 'cross_prob'),
    # ('real', 'cross_prob'),
    # ('binary', 'mut_prob'),
    # ('real', 'mut_prob'),
    # ('binary', 'p_select',),
    # ('real', 'p_select',),
    # ('binary', 'p_size',),
    # ('real', 'p_size',),
    # ('binary', 'term',),
    # ('real', 'term',),
]

def plot_condition(condition):
    plt.figure()
    found = False
    for file in os.listdir(folder_path):
        if all(c in file for c in condition):
            found = True
            df = pd.read_csv(os.path.join(folder_path, file))
            _, var = file.split()
            var, _ = var.split('.')
            # label = '_'.join(file.split('_')[:2])
            plt.plot(df, label=file[:-4])
            # plt.plot(df, label=f'binary_n_point_{var}')
            # plt.plot(df, label=label)

    if not found:
        plt.close()
        return

    title = ' '.join(condition)
    plt.title(title)
    plt.xlabel('Generation')
    plt.ylabel('Fitness')
    plt.legend(loc='best')
    plt.savefig(os.path.join("showbuffer", f"{'_'.join(condition)}.png"))
    plt.close()


for condition in conditions:
    plot_condition(condition)


# plt.figure(figsize=(12, 8))

# for file in csv_files:
#     file_path = os.path.join(folder_path, file)
#     data = pd.read_csv(file_path)
    
#     name, val = file.split()
#     plt.plot(data['Binary'], label=f'Binary_{name}_{val}')
#     plt.plot(data['Real'], label=f'Real_{name}_{val}')
    
    
# plt.title(f'{title}')
# plt.xlabel('Generation')
# plt.ylabel('SCH function(fitness) (avg 30 trials)')
# plt.legend()
# plt.savefig(output_file)
# plt.show()