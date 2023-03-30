import os
import pandas as pd
import matplotlib.pyplot as plt

folder_path = 'data'
output_file = 'show/tournament.png'
filename_pattern = 'avgfitness_p_select'
csv_files = [f for f in os.listdir(folder_path) if f.startswith(filename_pattern)]

plt.figure(figsize=(12, 8))

for file in csv_files:
    file_path = os.path.join(folder_path, file)
    data = pd.read_csv(file_path)
    
    # var = float(file.split('_')[-1].split('.')[0] + '.' + file.split('_')[-1].split('.')[1])
    var = int(file.split('_')[-1].split('.')[0])

    plt.plot(data['Binary'], label=f'binary_{var}')
    plt.plot(data['Real'], label=f'real_{var}')

plt.title('Independent variable: tournament select n')
plt.xlabel('Generation')
plt.ylabel('Avg Fitness (30 trials)')
plt.legend()
plt.savefig(output_file)
plt.show()